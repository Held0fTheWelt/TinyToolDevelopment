# Technical Overview

This overview is for maintainers who need to understand how the plugin is put together.

## Modules

### AsyncSplineBuilder

Runtime module. Contains:

- `ASplineGeneratingActor`
- spline mesh generation
- async build state machine
- ground wall and drop wall generation
- data asset save/load
- runtime-safe trace and cleanup helpers

### AsyncSplineBuilderEditor

Uncooked editor module. Contains:

- workflow-first Slate panel
- landscape height deformation
- editor selection ignore-list helpers
- module startup binding of editor delegates

The runtime module does not directly depend on the editor module.

## Main Types

- `ASplineGeneratingActor`: main actor and build orchestrator.
- `FTrackSplineData`: per-segment road, extra mesh, and wall configuration.
- `FGroundWallSettings`: per-segment procedural wall configuration.
- `FTrackSegmentPlan`: immutable segment decision used during a build.
- `FTrackBuildPlan`: array of segment plans computed before generation.
- `USplinePointListAsset`: data asset for spline point persistence.
- `SAsyncSplineBuilderPanel`: editor-only workflow panel for normal setup and build actions.

## Editor UI Flow

The editor module registers a hidden nomad tab and exposes it through **Tools > Track Tools > Async Spline Builder**. The panel talks to the selected or created `ASplineGeneratingActor` through editor-only facade methods on the actor.

The UI is intentionally workflow-shaped:

1. resolve or create the actor
2. assign core meshes
3. validate before destructive rebuilds
4. choose synchronous or batched generation
5. prepare per-segment data rows
6. assign landscape and run manual height deformation

Advanced raw configuration remains in the Details panel.

## Build Flow

```mermaid
flowchart TD
    A["BuildTrack or RebuildTrack"] --> B["RequestBuild"]
    B --> C["ValidateBuildSettings"]
    C -->|errors| D["Abort without clearing"]
    C -->|ok| E["ClearGeneratedComponents"]
    E --> F["BuildArrayOfSplineSegments"]
    F --> G["ComputeBuildPlan"]
    G --> H{"Async?"}
    H -->|no| I["AddRoadAndExtraMeshesToSpline"]
    H -->|yes editor| J["Tick BuildNextSegments"]
    H -->|yes runtime| K["RuntimeBuildPump next tick"]
    J --> L["FinishBuild_Internal"]
    K --> L
    I --> M["UpdateSpline and Debug"]
    L --> M
    M --> N{"Ground walls enabled?"}
    N -->|yes| O["BuildGroundWalls and BuildDropCliffWalls"]
    N -->|no| P["ClearGroundWalls"]
```

## Validation Contract

`ValidateBuildSettings()` returns `FBuildValidationResult`.

Blocking errors stop builds before old generated components are cleared. Warnings are logged but allow the build to continue.

Examples of blocking errors:

- missing `MainMesh`
- ground walls enabled without trace object types
- landscape snapping enabled without trace object types
- invalid gap or drop ranges

## Build Plan Contract

`ComputeBuildPlan()` is the single source of truth for:

- segment start/end distances
- selected road mesh
- piece count
- piece length
- jump gap status
- drop status and height
- extra mesh count

Road generation, extra mesh generation, wall width lookup, and landscape deformation should use the plan when possible.

## Component Ownership

Generated components are tagged with:

- `AsyncSplineBuilder.Generated`
- a role tag such as `RoadMesh`, `ExtraMesh`, `GroundWall`, `DropWall`, or `DebugText`

Cleanup scans components by tag. This protects against stale transient arrays after construction, load, hot reload, or partial rebuilds.

## Async Model

The plugin does not create components from worker threads.

Instead:

- editor builds are debounced and pumped through actor tick
- runtime builds are pumped through `SetTimerForNextTick`
- each pump calls `BuildNextSegments(SegmentsPerTick)`

This keeps component registration on the game thread while still avoiding one large build spike.

## Ground Wall Model

Ground walls are procedural mesh strips. They are sampled along spline distance and split whenever a segment is invalid, disabled, too short, below `MinWallHeight`, or inside a jump gap.

Triangle generation uses previous/current sample pairs. This prevents forward references and invalid triangles at strip boundaries.

## Drop Wall Model

Drop walls are generated between adjacent non-gap segments when their boundary heights differ. They form a vertical quad across the road width at the boundary distance.

## Landscape Deformation Model

Landscape deformation is editor-only. The actor exposes `FLandscapeDeformParams`; the editor module consumes it. The deformer samples the road spline, projects candidate landscape samples to the closest point on the sampled route, and blends height according to road width plus falloff.

Additive global landscape layer weight painting is implemented in the editor module (`PaintLandscapeLayerNow`). The workflow panel exposes `PaintLayer`, `PaintHalfWidth`, `PaintFallOff`, and the **Paint Layer** action. `PaintFallOff = 0` is a hard edge. Weight-blended layer infos reduce other layers under the road; `bNoWeightBlend` layer infos are warned about because they do not guarantee that reduction. Replace/clear and per-segment paint are not implemented.

## Packaging

The runtime module is cross-platform for Win64, Linux, and Mac according to the `.uplugin`. The editor module is `UncookedOnly`.

Packaged games should not reference editor-only landscape deformation symbols.

## Maintenance Notes

- Keep generated-component role tags precise.
- Do not put editor-only landscape APIs in the runtime module.
- Do not create components off the game thread.
- Keep validation blocking only for states that would make the build destructive or meaningless.
- Add automation tests when changing build-plan, cleanup, gap/drop, or wall behavior.

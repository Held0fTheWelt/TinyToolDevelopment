# Code Documentation

This document maps the source code and explains the contracts that should stay stable.

## Source Layout

```text
Source/
  AsyncSplineBuilder/
    AsyncSplineBuilder.Build.cs
    Public/
      AsyncSplineBuilder.h
      RoadSplineInterface.h
      SplineGeneratingActor.h
      SplinePointListAsset.h
      TrackSplineData.h
    Private/
      AsyncSplineBuilder.cpp
      SplineGeneratingActor.cpp
  AsyncSplineBuilderEditor/
    AsyncSplineBuilderEditor.Build.cs
    Public/
      AsyncSplineBuilderEditor.h
    Private/
      AsyncSplineBuilderEditor.cpp
      IgnoreListEditorActions.h/.cpp
      LandscapeDeformer.h/.cpp
      SAsyncSplineBuilderPanel.h/.cpp
      Tests/AsyncSplineBuilderTests.cpp
```

## Runtime Module Responsibilities

The runtime module owns anything that can be needed in PIE or packaged builds:

- actor construction
- road spline mesh components
- extra spline mesh components
- generated component cleanup
- runtime async build pump
- ground wall procedural mesh sections
- drop wall procedural mesh sections
- spline point data asset I/O
- trace helper functions that do not require editor-only APIs

## Editor Module Responsibilities

The editor module owns:

- the workflow-first Slate panel
- landscape height deformation
- editor selection ignore-list actions
- automation tests

The editor module binds delegates exposed by the runtime actor, so the runtime actor can request editor-only work without linking against editor-only classes.

## Editor Workflow UI Contract

`SAsyncSplineBuilderPanel` is the task-first editor surface registered by `FAsyncSplineBuilderEditorModule`.

Keep the panel focused on common workflow decisions:

- actor selection and creation
- start, main, and end mesh assignment
- validation, build, rebuild, cancel, and async batch size
- closed-loop and debug display toggles
- segment row preparation and bulk gap/drop cleanup
- selected landscape assignment and manual height deformation
- actor-level ground wall enablement

Do not mirror every raw Details property in the panel. Detailed per-segment arrays, trace object arrays, UV settings, collision settings, materials, and experimental fields should remain in the Details panel until they need a dedicated structured editor.

The panel uses editor-only facade methods on `ASplineGeneratingActor`. Those methods should stay behind `WITH_EDITOR` and should only wrap validated editor actions, simple property updates, and transaction-friendly helper operations.

## Main Runtime Files

### SplineGeneratingActor.h

Declares the main actor, build plan structs, validation result, user-facing settings, and private helper contracts.

The header should document:

- what each public setting means
- which fields are runtime-safe
- which fields are editor-only
- which functions are build entry points
- which helpers are test-only

### SplineGeneratingActor.cpp

Implements the generation pipeline.

Important regions:

- trace helpers
- component creation
- construction and post-load behavior
- road and extra mesh generation
- validation
- async state machine
- generated-component registry
- cleanup
- ground walls
- drop walls
- gap/drop helpers
- data asset I/O

### TrackSplineData.h

Defines per-segment data and ground wall settings. This is the primary user-facing configuration struct for segment-specific behavior.

## Build Plan Contract

`FTrackBuildPlan` is computed before generation. Treat it as a snapshot of build decisions.

Do not re-derive important values independently in road, extra mesh, wall, or landscape code unless there is a documented reason. Shared values prevent systems from disagreeing about segment length, piece count, gap state, or selected mesh.

## Component Tag Contract

Every generated component must get:

- `GeneratedTag`
- exactly one meaningful role tag when possible

Role tags:

- `RoadMeshTag`
- `ExtraMeshTag`
- `GroundWallTag`
- `DropWallTag`
- `DebugTextTag`

Cleanup, tests, and registry rebuilds depend on these tags.

## Validation Contract

`ValidateBuildSettings()` separates errors from warnings.

Errors:

- abort before clearing old generated geometry
- should represent states where a build cannot produce useful output

Warnings:

- log but continue
- should represent suspicious but usable settings

## Async Contract

Component creation must remain on the game thread. Async means batched game-thread work, not worker-thread component registration.

Editor path:

- request
- debounce
- actor tick
- `BuildNextSegments`

Runtime path:

- request
- `SetTimerForNextTick`
- `RuntimeBuildPump`
- re-arm while building

## Ground Wall Contract

Ground wall code must:

- sample spline distance
- resolve segment data per sample
- skip jump gaps
- flush strips at invalid samples
- only create triangles between previous and current valid sample pairs
- respect per-segment `TraceLength`, `TrackHalfWidth`, `MinWallHeight`, `MaxWallHeight`, and side enable

## Drop Wall Contract

Drop wall code should only create walls where both adjacent segments have road and their boundary heights differ. It should not bridge over jump gaps.

## Landscape Contract

Runtime actor exposes a parameter snapshot (`FLandscapeDeformParams`). Editor deformer applies height changes (`Deform`) and additive layer weight paint (`PaintLayer`). Shared footprint math lives in `AsyncSplineLandscape` so height deformation and layer painting use the same closest-polyline projection and falloff semantics.

`PaintFallOff = 0` is a true hard edge. Weight-blended layer infos reduce other layers under the road; `bNoWeightBlend` layer infos are diagnosed because target-layer paint can be written without reducing the other layers.

Do not introduce editor-only landscape edit dependencies into the runtime module.

## Automation Tests

Tests live in:

```text
Source/AsyncSplineBuilderEditor/Private/Tests/AsyncSplineBuilderTests.cpp
```

They cover:

- open spline build
- closed loop segment count
- extra mesh start behavior
- extra mesh not tagged as road
- jump gap suppression
- cleanup with stale generated arrays
- data asset round trip
- segment length planning
- validation blocking
- ground wall strip validity
- drop wall count
- closed-loop seam drop-wall boundaries
- editor track data expansion
- runtime async completion
- landscape falloff and paint footprint helper behavior
- degenerate landscape footprint input

## Extension Points

Good extension points:

- additional build-plan fields
- new role tags for new generated component families
- material assignment policies
- richer landscape deformation options
- replace/clear layer paint mode in the editor module
- new automation tests around per-segment behavior

Risky extension points:

- changing tag semantics
- bypassing `ComputeBuildPlan`
- creating components from worker threads
- adding editor-only includes to runtime code
- clearing generated components before validation

## Build Notes

The project has multiple modules with similar anonymous namespace helpers. Keep unity settings conservative for modules that define many repeated local helper names.

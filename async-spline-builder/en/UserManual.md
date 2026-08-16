<!-- doc-provenance: product-facts.yml reconciled 2026-07-15; source AKDB:plugins/AsyncSplineBuilder/architecture.md -->
# User Manual

This manual explains how to use Async Spline Builder in the Unreal Editor and how the main features fit together.

## Purpose

Async Spline Builder creates generated components from an editable spline. The typical output is a road or track made from `USplineMeshComponent` sections, with optional extra spline meshes and procedural wall meshes.

The actor can rebuild synchronously or in batches. Batching keeps the editor responsive on long tracks and is also available at runtime through a next-tick timer pump.

## Opening And Enabling

1. Open **Edit > Plugins**.
2. Enable **AsyncSplineBuilder**.
3. Restart the editor if prompted.
4. Open or create a level.
5. Open **Tools > Track Tools > Async Spline Builder**.

The plugin contains both runtime and editor modules. The actor is runtime-capable; the workflow panel and landscape deformation tools are editor-only.

## Workflow Panel

The Async Spline Builder panel is the recommended way to configure normal tracks. It avoids scattering the common workflow across several Details categories.

The panel is organized into tabs:

- **Build**: actor selection, mesh setup, validate/build/rebuild/cancel, async batching, closed loop, debug point or segment labels, and optional layout-connector endpoint labels.
- **Segments**: per-segment `TrackSplineData`, segment row creation, jump gaps, and stunt drops.
- **Terrain**: landscape snapping, landscape assignment, layer paint settings, height deformation, additive layer paint, and ground walls.

Use the Details panel for advanced arrays and uncommon settings that are intentionally not duplicated in the workflow panel.

## Basic Actor Setup

1. In the workflow panel, press **Create Actor** or select an existing `ASplineGeneratingActor` and press **Use Selection**.
2. In **Setup**, assign `MainMesh`.
3. Optionally assign `StartMesh` and `EndMesh`.
4. Move spline points in the viewport.
5. Press **Validate**.
6. Press **Build Now** or **Rebuild**.

`MainMesh` is required. Validation blocks builds without it so existing generated geometry is not cleared and replaced with nothing.

## Mesh Authoring Expectations

Road meshes should:

- Tile along local X.
- Have a sensible Y extent because mesh bounds are used to derive road half-width.
- Use consistent pivots.
- Avoid hidden collision complexity unless collision is needed.

If mesh bounds are not representative, set `GroundWallSettings.TrackHalfWidth` manually.

## Editing The Spline

Use the standard Unreal spline editing tools. Useful fields:

- `bClosedLoop`: connects the last point to the first point.
- `SplinePointType`: controls point interpolation behavior.
- `SplineZOffset`: offsets the spline component.
- `bShowPointNumbers`: displays point indices.
- `bShowSegmentNumbers`: displays segment indices.
- `bShowSplineVisualizationWidth`: displays a wider editor spline.

Point and segment numbers are generated debug components and are cleaned up by the same tag system used for generated geometry.

## Track Shape Editor

Open **Tools > Track Tools > Track Shape Editor** when you need a compact multi-layout authoring surface instead of editing only the actor's raw spline points. The editor works on a native `track_shape.v1` document and can apply compiled main, pit-lane, alternate, or service-road layouts to the selected `ASplineGeneratingActor`.

The **Designer Tools** section provides the day-to-day editing controls:

- add pit-lane, alternate, or service-road layouts
- duplicate or delete the selected non-main layout
- change layout kind and closed-loop state
- select previous or next layout, anchor, or segment
- edit selected anchor X/Y coordinates
- add, insert, or delete anchors while preserving a valid minimum anchor count
- add or delete explicit segments, switch selected segments between line and bezier, or rebuild sequential segments for the selected layout

The viewport supports direct anchor selection and dragging. The layout list and inspector reflect the same selection, and the JSON section can still import or export the underlying document for review or source control.

Use **Validate** before applying complex edits. Use **Apply** only after selecting or creating the target actor, because apply mutates the actor's editable spline/layout state.

## Building

Use:

- **Build Now** / `BuildTrack`: synchronous full build.
- **Rebuild** / `RebuildTrack`: async if `bUseAsyncBuild` is true, otherwise synchronous.
- **Cancel** / `CancelAsyncBuild`: cancels an active or pending async build.

The actor rebuilds from a computed `FTrackBuildPlan`. The plan decides segment ranges, piece counts, drop status, jump gaps, selected road mesh, and extra mesh count before generation begins.

## Async Build

Settings:

- `bUseAsyncBuild`: enable batch building.
- `SegmentsPerTick`: number of generated road/extra mesh pieces processed per tick.
- `bAutoRebuildOnConstruction`: schedule rebuilds when construction changes occur.

Editor worlds debounce construction changes before clearing or preparing generated components, which keeps existing spline geometry editable while you drag points. Runtime worlds use a next-tick timer pump. Both paths call the same piece-level builder, so behavior stays aligned without letting one long spline segment monopolize a frame.

## Per-Segment Data

`TrackSplineData` configures each segment. If there are fewer entries than spline segments, index `0` is used as fallback.

Important fields:

- `RoadMesh`: optional segment-specific road mesh.
- `MeshInstances`: exact number of mesh pieces for the segment.
- `RoadMeshLength`: desired road piece length.
- `SegmentLength`: fallback spacing when `RoadMeshLength` is unset.
- `ExtraMeshStart`, `ExtraMesh`, `ExtraMeshEnd`: extra spline meshes.
- `ExtraMeshOffset`: lateral offsets for extra mesh slots.
- `GroundWallSettings`: per-segment ground wall behavior.

## Extra Meshes

Extra meshes follow the same spline piece interval as the road piece. They are useful for rails, curbs, fences, and decorative side objects.

Start, middle, and end arrays allow different meshes at segment boundaries. Extra meshes are tagged with `AsyncSplineBuilder.ExtraMesh`, not `AsyncSplineBuilder.RoadMesh`.

## Gaps

Add entries to `JumpGapsByPoints` to suppress road and extra mesh generation for point-index ranges.

Ranges are segment ranges:

```text
[StartPointIndex, EndPointIndex)
```

For example, `StartPointIndex = 2`, `EndPointIndex = 4` suppresses segments `2` and `3`.

## Drops

Add entries to `StuntDropsByPoints` to move segment ranges downward or to a constant world Z.

Fields:

- `DropHeight`: relative Z offset. Negative values move the road down.
- `bUseConstantGapHeight`: use absolute world Z instead of offset.
- `ConstantGapWorldZ`: absolute height when enabled.

If two adjacent non-gap segments meet at different heights, the actor creates a drop wall between them.

## Ground Walls

Enable `bGenerateGroundWalls` to generate procedural wall strips down from the road edge.

Ground walls:

- Use mesh-derived or override road width.
- Respect per-segment wall settings.
- Split strips at jump gaps and invalid samples.
- Can be one-sided or two-sided.
- Use UVs based on distance and real wall height.

See [LandscapeAndWalls.md](LandscapeAndWalls.md) for detailed setup.

## Landscape Snapping

Mesh snapping:

- `bSnapMeshesToLandscape`
- `ObjectsToHitForLandscapeLineTrace`
- `LineTraceLength`

Point snapping:

- `bSnapPointsToLandscape`
- `bTangentPointsUpdate`

Use `ActorsToIgnoreForGenerationTraces` to exclude helper meshes or temporary objects from trace queries.

## Landscape Deformation

Editor-only deformation is run with `DeformLandscapeNow`.

Requirements:

- `Landscape` assigned.
- A valid spline.
- Sensible `FallOff` and `NumberOfSubdivisionsForDeform`.
- `bRaiseHeights` and/or `bLowerHeights` enabled.

Height: `DeformLandscapeNow` or panel **Deform Height**. Layer paint: assign `PaintLayer`, tune `PaintHalfWidth` / `PaintFallOff` in the panel, then `PaintLandscapeLayerNow` or panel **Paint Layer**. Paint is additive; it does not clear prior wider bands when you shrink falloff. `PaintFallOff = 0` is a hard edge. If the selected layer info uses `bNoWeightBlend`, the panel/validation warns that other landscape layers are not guaranteed to be reduced under the road.

## When To Use Details

The workflow panel is intentionally focused. Use the Details panel when you need to edit:

- per-segment `ExtraMeshStart`, `ExtraMesh`, `ExtraMeshEnd`, and `ExtraMeshOffset` arrays
- detailed `FGroundWallSettings`, including trace, UV, material, collision, and width overrides
- trace object arrays for landscape snapping and wall generation
- spline point data asset read/write fields
- advanced debug and construction settings

## Layout Connectors

The Build tab includes a **Layout Connectors** section for passive route metadata. A connector links a source layout/distance to a target layout/distance and stores a semantic kind such as `PitEntry`, `PitExit`, `Link`, or `ServiceAccess`. You can also type a custom kind; custom non-empty kinds validate as warnings rather than errors.

Use **Pit Entry** to add a default connector from `Main` to the first pit-lane layout. Use **Pit Exit** to add a default connector from the first pit-lane layout back to `Main`. **Validate** in this section runs connector-only validation.

Connector edits do not rebuild the road and do not delete generated geometry. They also do not create automatic transition meshes, cut splines, expand terrain deformation to pit lanes, or enable a special pit-lane renderer.

Enable **Show Connector Debug** to place visual-only text markers at valid connector endpoints. A marker identifies the connector index and kind, whether it is the `From` or `To` endpoint, its layout, and its distance. Each endpoint is resolved independently, so one valid endpoint can remain visible when the other is invalid. Missing layouts and distances outside a spline's range are skipped rather than drawn at a false location; use **Validate** to inspect those connector problems.

The markers use `UTextRenderComponent` debug output and do not add road, extra-mesh, ground-wall, or drop-wall geometry. Editing connectors refreshes the markers while the checkbox is enabled. Disable **Show Connector Debug** to remove only the connector labels. Toggling or refreshing these labels does not rebuild the track, change road component counts, expand terrain behavior, or affect the build-validation gate.

## Data Asset Workflow

Assign a `USplinePointListAsset` to `SplinePointList`.

Use:

- `WriteSplineToDataAsset`: saves current spline points.
- `ReadSplineFromDataAsset`: loads spline points.

This is useful for preserving track layouts separately from generated components.

## Recommended Production Workflow

1. Build a short test spline.
2. Validate road mesh bounds and tiling.
3. Add segment data.
4. Add extra meshes.
5. Add gaps and drops.
6. Configure ground wall tracing.
7. Run landscape deformation only after the road shape is stable.
8. Run automation tests before release.
9. Test the level in PIE and packaged runtime.

## What The Plugin Does Not Do

- It does not provide replace/clear or per-segment landscape paint modes.
- It does not author meshes for you.
- It does not guarantee perfect terrain shoulders on every landscape.
- It does not generate connector transition road meshes automatically.
- It does not replace manual art direction for final track polish.

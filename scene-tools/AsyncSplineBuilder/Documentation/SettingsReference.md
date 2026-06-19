# Settings Reference

This reference describes the settings most users need when configuring `ASplineGeneratingActor`.

## Workflow Panel Mapping

Open **Tools > Track Tools > Async Spline Builder** for the task-first UI. The panel is split into **Build**, **Segments**, and **Terrain** tabs. It covers actor selection, mesh setup, validation, build and rebuild commands, async batching, closed-loop state, debug labels, segment row helpers, jump gaps, stunt drops, landscape assignment, layer paint settings, height deformation, snapping toggles, and actor-level ground walls.

Use this reference when a setting is only exposed in the Details panel or when you need exact field behavior. Per-segment mesh arrays, detailed ground wall settings, trace object arrays, collision flags, UV controls, and data asset fields remain advanced Details-panel settings.

## Mesh Setup

### StartMesh

Optional mesh used for the first generated road piece on an open track. If unset, the selected segment road mesh is used.

### MainMesh

Required fallback road mesh. Validation blocks generation when this is missing.

### EndMesh

Optional mesh used for the final generated road piece on an open track. If unset, the selected segment road mesh is used.

## TrackTools

### bEditSpline

When enabled, generated components are cleared and only spline/debug editing remains active during construction. Use this when shaping the spline without rebuilding meshes.

### bShowSegmentNumbers / bShowPointNumbers

Creates debug text components for segment or point indices. These are tagged and cleaned up with other generated components.

### bShowSplineVisualizationWidth / SplineVisualizationWidth

Controls the editor spline visualization width.

### bSnapPointsToLandscape

Moves spline points to trace hits. Requires `ObjectsToHitForLandscapeLineTrace`.

### bTangentPointsUpdate

Updates tangents after snapping points to landscape.

### bMirrorExtraMesh

Mirrors extra meshes by flipping their X scale.

### SplinePointType

The spline point type applied during spline updates. `CurveCustomTangent` is a good default for roads.

### SplineZOffset

Applies a vertical offset to the spline component.

### TrackSplineData

Per-segment data. If no entry exists for a segment, entry `0` is used as fallback.

## TrackSplineData

### RoadMesh

Optional road mesh for the segment. Falls back to `MainMesh`.

### MeshInstances

Exact number of road pieces in the segment. When greater than zero, it overrides automatic length-based count.

### SegmentLength

Spacing fallback when `RoadMeshLength` is not set. Values greater than `1` are used.

### RoadMeshLength

Explicit desired road mesh coverage length. Use this when mesh bounds do not match visual tile length.

### ExtraMeshStart / ExtraMesh / ExtraMeshEnd

Optional arrays of extra meshes for first, middle, and final pieces.

### ExtraMeshOffset

Lateral offset per extra mesh slot.

### GroundWallSettings

Per-segment wall generation, trace, width, collision, and UV settings.

## Options

### bClosedLoop

Connects the final spline point back to the first.

### bEnableCollision

Enables collision for generated road and procedural wall components.

### bCastShadow / bCastContactShadow

Controls generated spline mesh shadow flags.

### bMirrorMesh

Mirrors road mesh scale.

### bSnapMeshesToLandscape

Snaps generated road and extra mesh endpoints to trace hits. Requires trace object types.

## Landscape

### Landscape

Landscape proxy used by editor-only deformation.

### ActorsToIgnoreForGenerationTraces

Actors ignored by snap and wall traces.

### bSnapTraceLandscapeOnly

If true, snap traces only accept landscape hits.

### ObjectsToHitForLandscapeLineTrace

Object types used by mesh and point snapping. Required when snapping is enabled.

### FallOff

Distance outside the road width over which height deformation blends back to existing terrain.

### NumberOfSubdivisionsForDeform

Spline sampling resolution for landscape deformation. Higher values can improve fit but increase cost.

### bRaiseHeights / bLowerHeights

Controls whether deformation can raise and/or lower landscape samples.

### PaintHalfWidth

Full-weight half-width for layer painting (cm). `0` uses the road half-width at each deform sample.

### PaintFallOff

Smoothstep falloff distance for layer painting (cm). Independent from height `FallOff`. `0` gives a hard edge with no soft band outside `PaintHalfWidth`.

### PaintLayer

`ULandscapeLayerInfoObject` painted along the road by `PaintLandscapeLayerNow` / panel **Paint Layer**. Must be registered on the target landscape. If the layer info uses `bNoWeightBlend`, the target layer can still receive paint, but other material layers are not guaranteed to be reduced under the road.

### LandscapeEditLayerName

Edit layer name used for landscape height edits where supported by the landscape setup.

### LineTraceLength

Trace depth for landscape snapping.

## Async Build

### bUseAsyncBuild

Enables batched rebuilds.

### SegmentsPerTick

Number of async work units processed per tick. One work unit is one generated road or extra mesh piece, so a long spline segment with many pieces is spread across multiple ticks instead of being generated all at once. Start low for responsiveness and increase after testing.

### bAutoRebuildOnConstruction

Schedules rebuilds after construction changes.

## Ground Walls

### bGenerateGroundWalls

Enables procedural ground wall generation.

### GroundWallSubdivisions

Number of wall samples along the spline. Higher values produce smoother walls and more geometry.

### GroundWallOutset

Additional horizontal offset beyond derived road half-width.

### GroundWallFallbackDepth

Depth used when a wall trace misses.

### bGroundWallsDoubleSided

Adds reverse triangles so walls render from both sides.

### GroundWallObjectsToHitForLineTrace

Default trace object types for ground walls when per-segment trace settings are empty.

## GroundWallSettings

### bGenerateGroundWalls

Per-segment wall enable.

### bGenerateBothSides

If false, the left side is suppressed for that segment.

### TrackHalfWidth

Manual half-width override. Leave `0` to derive width from the selected road mesh bounds.

### MinWallHeight / MaxWallHeight

Skips tiny walls and clamps very large walls.

### bCreateCollision

Controls procedural wall collision, also gated by actor `bEnableCollision`.

### TraceSettings

Per-segment trace object types, trace length, and trace complexity.

### UVSettings

Per-segment wall UV tiling and flips.

## Drop Walls

### DropWallMaterial

Material applied to generated drop walls.

### DropWallUVWorldUnitsU / DropWallUVWorldUnitsV

World-unit UV tiling for drop walls.

## Recommended Baseline

- `bUseAsyncBuild = true`
- `SegmentsPerTick = 24`
- `bAutoRebuildOnConstruction = true`
- `MainMesh` assigned
- `RoadMeshLength = 0` unless mesh bounds are wrong
- `TrackHalfWidth = 0` unless mesh bounds are wrong
- Ground wall trace object types configured before enabling walls
- Landscape deformation run manually after the road shape is stable

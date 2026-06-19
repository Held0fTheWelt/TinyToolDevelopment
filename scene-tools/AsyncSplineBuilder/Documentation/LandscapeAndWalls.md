# Landscape, Ground Walls, Gaps, And Drops

This document explains the terrain-facing parts of Async Spline Builder.

## Separate Systems

The plugin has four related but separate systems:

- Mesh snapping: generated spline mesh endpoints trace to surfaces.
- Point snapping: spline control points trace to surfaces.
- Landscape deformation: editor-only height editing around the road.
- Landscape layer paint: editor-only additive weight painting along the road footprint.
- Procedural walls: generated mesh geometry down from road edges or between drop heights.

Keeping these systems separate matters. Snapping changes generated component positions. Deformation changes landscape height. Walls create new procedural mesh components.

## Mesh Snapping

Use mesh snapping when road pieces should follow existing terrain.

Required fields:

- `bSnapMeshesToLandscape = true`
- `ObjectsToHitForLandscapeLineTrace` contains at least one object type

Useful fields:

- `bSnapTraceLandscapeOnly`
- `ActorsToIgnoreForGenerationTraces`
- `LineTraceLength`

The builder traces the start and end point of each road or extra mesh piece. If a valid hit is found, that endpoint is moved to the hit.

## Point Snapping

Use point snapping when you want the spline itself moved onto a surface.

Required fields:

- `bSnapPointsToLandscape = true`
- `ObjectsToHitForLandscapeLineTrace` configured

Optional:

- `bTangentPointsUpdate = true`

Point snapping runs before mesh generation. This can produce a cleaner source spline, but it also changes authored spline points.

## Landscape Height Deformation

Use `DeformLandscapeNow` to stamp height around the road spline.

The editor module receives a snapshot from the runtime actor:

- target `Landscape`
- optional `EditLayerName`
- `FallOff`
- `NumberOfSubdivisionsForDeform`
- raise/lower flags
- road half-width sampled from the actor

The deformer samples the spline, projects landscape samples to the closest point on the sampled polyline, and blends height based on distance to road center and falloff.

## Landscape Layer Weight Painting (additive)

Use `PaintLandscapeLayerNow` (Details) or **Paint Layer** in the Async Spline Builder panel to weight-paint the configured `PaintLayer` along the road footprint. This is separate from height deformation (`DeformLandscapeNow`).

- `PaintHalfWidth` — full-weight half-width in cm; `0` follows the road half-width at each sample.
- `PaintFallOff` — smoothstep fade outside the full-weight band (independent from height `FallOff`); `0` is a hard edge.
- Writes are **additive** (`max` with existing weight in the band); vertices outside the band are untouched.
- Weight-blended layer infos reduce other layers under the road. If the selected layer info uses `bNoWeightBlend`, the target layer may paint, but other layers are not guaranteed to be reduced; the operation warns about this.

**Not implemented:** replace/clear paint mode, per-segment paint layers, or automatic removal when you shrink `PaintFallOff` / `PaintHalfWidth` after a wider paint pass.

## Ground Wall Generation

Ground walls are procedural mesh strips generated down from road edges.

Generation steps:

1. Walk the spline segment by segment.
2. Sample each segment, always including its start and end boundaries.
3. Skip if the segment is a jump gap or the side is disabled.
4. Compute road edge from spline location, right vector, road half-width, and `GroundWallOutset`.
5. Apply drop height if the segment is dropped.
6. Trace down using per-segment or actor wall trace settings.
7. Create top/bottom sample vertices.
8. Connect current sample to the previous valid sample.
9. Flush the strip at invalid samples, tiny wall heights, and every segment boundary.

This avoids triangles bridging across gaps, invalid trace sections, or abrupt drop-height changes at spline points.

## Ground Wall Width

Road half-width is resolved in this order:

1. `TrackSplineData[Segment].GroundWallSettings.TrackHalfWidth` if greater than zero.
2. Selected segment road mesh bounds on Y.
3. `MainMesh` bounds on Y.
4. Zero if no mesh is available.

Use a manual width override only when mesh bounds do not match visual road width.

## Ground Wall Trace Settings

Per-segment trace settings are preferred when present:

- `TraceSettings.ObjectsToHit`
- `TraceSettings.TraceLength`
- `TraceSettings.bTraceComplex`

Actor-level `GroundWallObjectsToHitForLineTrace` acts as fallback for object types.

## Ground Wall UVs

Ground wall UVs use:

- U: distance along the spline divided by `UVWorldSizeU`
- V: real wall height divided by `UVWorldSizeV`

This reduces texture stretching on tall walls.

## Double-Sided Walls

`bGroundWallsDoubleSided` adds reverse winding triangles to ground walls and drop walls. This is useful for thin wall surfaces that must be visible from both sides without requiring a two-sided material.

## Jump Gaps

`JumpGapsByPoints` suppresses road and extra meshes for segment ranges. Ground wall strips also flush at gaps so geometry does not bridge the missing road.

Range semantics:

```text
[StartPointIndex, EndPointIndex)
```

## Drops

`StuntDropsByPoints` applies relative or absolute height changes to segment ranges.

Use relative mode for arcade-style drops:

```text
DropHeight = -300
```

Use constant mode when a section must align to a known world Z.

## Drop Walls

Drop walls are generated where two adjacent non-gap segments meet at different heights. They use road width at the boundary and create a vertical quad across the road. If no dedicated drop-wall material is assigned, the builder falls back to the ground-wall material so caps do not render with the default material by surprise.

Drop walls are tagged separately from ground walls:

- `AsyncSplineBuilder.DropWall`
- `AsyncSplineBuilder.GroundWall`

## Practical QA

Always test:

- open track
- closed loop
- one jump gap
- one drop section
- ground walls with and without both sides
- trace misses
- collision on/off
- mesh bounds that differ from visual width

For final maps, inspect tight curves and steep terrain manually.

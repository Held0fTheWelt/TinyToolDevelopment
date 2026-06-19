# Async Spline Builder Buyer Guide

Async Spline Builder is an Unreal Engine plugin for building spline-driven roads, tracks, pipes, rails, walls, and side-object layouts with less editor blocking. It is aimed at developers who want a practical production tool rather than a one-off Blueprint demo.

## Who It Is For

Use it when you need:

- Race tracks or roads made from repeatable mesh pieces.
- Long splines that should rebuild without freezing the editor for every segment.
- Extra spline-following meshes such as guard rails, barriers, fences, posts, pipes, or trim.
- Procedural wall geometry down from road edges to terrain.
- Stunt-like gaps or drops along the route.
- A reusable C++ actor that can also be driven from Blueprints.
- Editor-only landscape height stamping around a road spline.

It is not a replacement for a full road material painting suite or a complete terrain authoring package.

## What You Get

- `ASplineGeneratingActor`, the main actor placed in a level.
- `TrackSpline`, an editable spline component.
- `FTrackSplineData`, per-segment data for road meshes, mesh lengths, extra meshes, and wall settings.
- Runtime and editor build paths.
- Procedural mesh ground walls and drop walls.
- Data asset save/load for spline points.
- Editor-only landscape deformation bridge.
- Content examples and starter meshes/materials.
- Automation tests covering the most fragile integration points.
- Documentation for setup, settings, troubleshooting, QA, and source structure.

## Recommended First Run

1. Open a test level.
2. Open **Tools > Track Tools > Async Spline Builder**.
3. Press **Create Actor** or select an existing `ASplineGeneratingActor`.
4. Assign `MainMesh` in **Setup**.
5. Move the spline points into a short visible road.
6. Press **Build Now**.
7. Toggle **Closed Loop** and rebuild.
8. Use **Create Segment Rows** before editing per-segment settings.
9. Add one `FTrackSplineData` entry with `SegmentLength = 500`.
10. Rebuild and confirm that the road splits into more pieces.
11. Add one extra mesh and confirm it is generated as an extra component, not a road component.

This confirms the basic mesh, spline, data, tag, and cleanup paths.

## Main Editor Workflow

The normal workflow is centered around the dedicated **Async Spline Builder** panel under **Tools > Track Tools**. The panel exposes common controls through three tabs:

- **Build**: actor selection, mesh setup, validation, build/rebuild/cancel, async batching, closed loop, and debug labels.
- **Segments**: per-segment editing, row creation, jump gaps, and stunt drops.
- **Terrain**: landscape snapping, selected landscape assignment, layer paint settings, height deformation, additive layer paint, and ground walls.

The Unreal Details panel remains available for advanced raw configuration:

- **Mesh Setup**: start, main, and end road meshes.
- **TrackTools**: build buttons, spline editing, data asset I/O, async settings, and display options.
- **Options**: closed loop, collision, shadow, mirroring, and mesh snapping.
- **Landscape**: trace objects, landscape assignment, height deformation settings, layer paint settings, and ignore list helpers.
- **AsyncSpline|GroundWalls**: procedural wall generation below road edges.
- **AsyncSpline|Drop Walls**: material and UV settings for vertical walls between drop sections.
- **Stunt Track|Gaps / Drops**: point-index ranges that suppress or offset road sections.

## Workflow: Road Or Race Track

1. Use a mesh that tiles along local X.
2. Assign it to `MainMesh`.
3. Set the spline point type to `CurveCustomTangent` for smoother curves.
4. Edit the spline path.
5. Use `BuildTrack`.
6. Use `RoadMeshLength` when you know the mesh's true coverage length.
7. Use `SegmentLength` when you want fixed spacing and mesh bounds are not enough.
8. Use `MeshInstances` when you want exact per-segment piece counts.

Priority order for piece planning:

1. `MeshInstances` if greater than zero.
2. `RoadMeshLength` if greater than zero.
3. `SegmentLength` if greater than one.
4. Selected road mesh bounds along X.

## Workflow: Guard Rails And Extras

Extra meshes are configured per `FTrackSplineData` entry:

- `ExtraMeshStart`: mesh used on the first piece in the segment.
- `ExtraMesh`: mesh used on middle pieces.
- `ExtraMeshEnd`: mesh used on the final piece in the segment.
- `ExtraMeshOffset`: lateral offset per extra mesh slot.

Extra meshes are tagged separately from road meshes so cleanup, tests, and future tooling can distinguish them.

## Workflow: Ground Walls

Enable `bGenerateGroundWalls` and configure object types to trace against. Ground walls build two procedural mesh strips by sampling the spline, finding the road edge, tracing downward, and creating quads between valid samples.

Use this for:

- Raised road shoulders.
- Track edges on uneven terrain.
- Arcade-style walls down from floating track pieces.

Do not use it as a full terrain-retopology system. It creates supporting geometry; it does not sculpt the landscape by itself.

## Workflow: Gaps And Drops

`JumpGapsByPoints` suppresses road and extra mesh generation for segment ranges.

`StuntDropsByPoints` offsets a range of segments down or to a constant world Z. When two adjacent non-gap road segments meet at different heights, the actor generates a drop wall at the boundary.

## Landscape Capabilities

The plugin supports three separate landscape-related workflows:

- Mesh snapping: generated spline mesh endpoints can trace to landscape.
- Point snapping: spline points can be moved onto a landscape.
- Deformation: `DeformLandscapeNow` edits landscape height around the spline in the editor module.

Editor landscape workflow: height deformation (`DeformLandscapeNow`) and **additive global** weight paint for one configured `PaintLayer` (`PaintLandscapeLayerNow` / panel **Paint Layer**). The panel exposes `PaintLayer`, `PaintHalfWidth`, and `PaintFallOff`. Replace/clear and per-segment paint are not included.

## Strengths

- Practical async behavior for long splines.
- Runtime-capable mesh and wall generation.
- Clear component ownership through tags.
- A single build plan shared by road, extra mesh, wall width, and deformation logic.
- Conservative validation that blocks destructive bad builds.
- Stronger automation coverage than a typical small spline plugin.

## Known Boundaries

- Landscape layer paint is additive global only (no replace/clear or per-segment layers).
- `bNoWeightBlend` landscape layers are diagnosed and do not guarantee reduction of other layers under the road.
- Tight terrain-road blending still needs manual art review.
- Complex meshes must be authored consistently along local X.
- Very high subdivision counts or collision-heavy wall sections can still be expensive.
- A product map should be manually tested in editor, PIE, and packaged runtime.

## Included Documentation

Start with [UserManual.md](UserManual.md) for day-to-day use, then [SettingsReference.md](SettingsReference.md) for exact fields, and [LandscapeAndWalls.md](LandscapeAndWalls.md) for terrain-facing work.

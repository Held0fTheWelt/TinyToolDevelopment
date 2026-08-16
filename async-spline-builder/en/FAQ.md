<!-- doc-provenance: product-facts.yml reconciled 2026-07-15; source AKDB:plugins/AsyncSplineBuilder/architecture.md -->
# FAQ

## What is Async Spline Builder used for?

It builds spline-following meshes such as roads, race tracks, rails, pipes, barriers, and procedural support walls. Its main advantage is async batching, so long splines can rebuild without one large editor stall.

## Does it work at runtime?

Yes. Road meshes, extra meshes, ground walls, drop walls, and the async runtime pump live in the runtime module. Editor-only landscape height deformation is not available in packaged builds.

## What mesh direction should my road mesh use?

Author repeatable road meshes along local X. The builder uses mesh bounds on X for length fallback and bounds on Y for width fallback.

## Can I use different meshes per segment?

Yes. Add entries to `TrackSplineData` and set `RoadMesh`, `RoadMeshLength`, `SegmentLength`, `MeshInstances`, and extra mesh arrays per segment. Missing segment data falls back to entry `0`.

## Where do I configure the plugin?

Use **Tools > Track Tools > Async Spline Builder** for the normal workflow. It gives you actor selection, mesh setup, validation, build controls, async settings, spline display toggles, segment helpers, landscape actions, and ground wall enablement in one panel. Use the Details panel for advanced per-segment arrays and detailed trace, wall, collision, UV, and data asset fields.

## What is the difference between BuildTrack and RebuildTrack?

`BuildTrack` is synchronous and immediate. `RebuildTrack` uses async batching when `bUseAsyncBuild` is enabled.

## Does async generation use worker threads?

No. It batches work across ticks. This keeps Unreal component creation on the game thread, which is the correct place for registering `UActorComponent` instances.

## Can it create guard rails or side meshes?

Yes. Use `ExtraMeshStart`, `ExtraMesh`, `ExtraMeshEnd`, and `ExtraMeshOffset` in `FTrackSplineData`.

## Can it create jumps or missing road sections?

Yes. Use `JumpGapsByPoints`. Gaps suppress road and extra meshes for segment ranges.

## Can it create height drops?

Yes. Use `StuntDropsByPoints`. Adjacent non-gap segments at different heights create drop walls.

## Can it create walls down to the ground?

Yes. Enable `bGenerateGroundWalls` and configure trace object types. The procedural wall strips trace from road edges down to configured object types.

## Does it deform landscapes?

Yes, in the editor. Use `DeformLandscapeNow` for height and `PaintLandscapeLayerNow` (or panel **Paint Layer**) for additive weight painting when `PaintLayer` is assigned.

## Does it paint landscape layers?

Yes, for a single global `PaintLayer` using additive `max` painting. Set `PaintLayer` on the actor, assign the landscape, then run **Paint Layer**. Weight-blended layer infos reduce other layers under the road. `bNoWeightBlend` layer infos can paint the target layer, but do not guarantee that other layers are reduced. Not supported: replace/clear mode, per-segment paint layers, or shrinking the paint band automatically clearing old weights.

## Why did validation block my build?

The actor blocks builds for destructive misconfiguration, such as missing `MainMesh` or enabled trace-based features without trace object types. This protects existing generated geometry from being cleared before a valid replacement can be made.

## Why are my walls missing?

Common causes are missing trace object types, no trace hits, `MinWallHeight` too high, jump gaps cutting the strip, or `bGenerateGroundWalls` disabled in per-segment settings.

## Does it clean up generated components safely?

Yes. Generated components get stable tags, and cleanup scans tags rather than trusting only transient arrays.

## Can I save the spline layout?

Yes. Assign `SplinePointList` and use `WriteSplineToDataAsset` / `ReadSplineFromDataAsset`.

## Can I use it for Fab products or commercial games?

Yes, subject to the product license. The plugin does not grant rights to third-party meshes, materials, or content you use with it.

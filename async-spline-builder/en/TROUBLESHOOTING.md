<!-- doc-provenance: product-facts.yml reconciled 2026-07-15; source AKDB:plugins/AsyncSplineBuilder/architecture.md -->
# Troubleshooting

## The Actor Builds Nothing

Check:

- `MainMesh` is assigned.
- The spline has at least two points.
- Validation did not block the build.
- `bEditSpline` is not intentionally clearing generated components.
- The generated meshes are not hidden by level visibility or actor visibility.

## Build Is Blocked By Validation

Validation blocks destructive bad builds. Common causes:

- `MainMesh` is missing.
- Ground walls are enabled but no ground wall trace object types are configured.
- Landscape snapping is enabled but no landscape trace object types are configured.
- Jump gap or drop ranges are invalid.

Fix the setting and run `RebuildTrack` again.

## Connector Validation Reports Issues

Connector Validation Reports Issues when a passive layout connector points at a missing actor, an unknown layout id, an invalid spline distance, or incomplete connector metadata.

Fix the connector record in the workflow panel or Details panel, then run `Validate Layout Connectors` again. Connector validation is intentionally separate from geometry generation: connector records describe route intent and do not create transition mesh by themselves.

## A Connector Endpoint Label Is Missing

Enable **Show Connector Debug** in the panel's **Layout Connectors** section. If only one side of a connector appears, run **Validate Layout Connectors** and correct the missing layout or out-of-range distance reported for the hidden endpoint. Endpoints are resolved independently and invalid positions are intentionally skipped.

Connector labels are visual-only. You do not need to rebuild the track to create or refresh them, and correcting a label does not add connector road geometry or change terrain behavior.

## Workflow Panel Does Not Open

Open it through **Tools > Track Tools > Async Spline Builder**. If the menu entry is missing:

- rebuild the editor target
- confirm the `AsyncSplineBuilderEditor` module is enabled
- restart the editor after enabling the plugin
- check the Output Log for `AsyncSplineBuilderEditor` startup errors

The panel is editor-only and is not available in packaged builds.

## The Editor Freezes During Rebuild

Use async settings:

- `bUseAsyncBuild = true`
- lower `SegmentsPerTick`
- disable expensive wall collision while iterating
- reduce `GroundWallSubdivisions`

Very large component counts can still be expensive because Unreal component registration happens on the game thread.

## Extra Meshes Appear In The Wrong Place

Check:

- mesh pivot and local axes
- `ExtraMeshOffset`
- `bMirrorExtraMesh`
- segment data fallback to index `0`
- whether start/middle/end arrays contain different meshes

Extra meshes use the same spline interval as the road piece.

## Road Meshes Stretch Too Much

Set one of:

- `MeshInstances` for exact count
- `RoadMeshLength` for explicit piece length
- `SegmentLength` for automatic count from desired spacing

If all are unset, mesh bounds X are used.

## The Closed Loop Has A Bad Seam

Check:

- first and last spline point positions/tangents
- mesh pivot and tile length
- `StartMesh` usage on closed loops
- tangent smoothing settings

Closed loops build a wrap segment to the spline length.

## Ground Walls Do Not Appear

Check:

- `bGenerateGroundWalls` enabled on actor
- per-segment `GroundWallSettings.bGenerateGroundWalls`
- `GroundWallObjectsToHitForLineTrace`
- per-segment `TraceSettings.ObjectsToHit`
- trace length
- `MinWallHeight`
- jump gaps

If traces miss, fallback depth is used. If wall height is still below `MinWallHeight`, no section is created.

## Ground Walls Bridge Over Gaps

They should not. If you see this, confirm the gap range uses segment semantics:

```text
[StartPointIndex, EndPointIndex)
```

Also run the automation suite; `GroundWallGapStripValid` covers the basic strip split behavior.

## Ground Wall Width Is Wrong

Width is derived from the selected road mesh bounds on Y unless `TrackHalfWidth` is greater than zero. If the mesh bounds are not representative, set `TrackHalfWidth` manually.

## Drop Walls Do Not Appear

Check:

- both neighboring segments have road
- the boundary is not inside a jump gap
- the adjacent segments resolve to different world Z values
- `DropHeight` or constant Z is set on one side

Run `AsyncSplineBuilder.DropWallCount` for the basic drop-wall behavior.

## Landscape Snapping Does Nothing

Check:

- `bSnapMeshesToLandscape` or `bSnapPointsToLandscape` is enabled
- `ObjectsToHitForLandscapeLineTrace` has object types
- the landscape collision object type matches the query
- `ActorsToIgnoreForGenerationTraces` does not include the target
- trace length reaches the surface

## Landscape Deformation Does Nothing

Check:

- `Landscape` is assigned
- editor module is loaded
- spline has valid points
- `NumberOfSubdivisionsForDeform` is greater than zero
- at least one of `bRaiseHeights` or `bLowerHeights` is enabled
- the road overlaps the landscape area

Remember: deformation is a manual editor action through `DeformLandscapeNow`.

## Landscape Material Layer Is Not Painted

Height deformation (`DeformLandscapeNow`) and layer weight paint (`PaintLandscapeLayerNow`) are separate actions. Layer paint requires a valid `PaintLayer` registered on the landscape. Undo is owned by the deformer transaction; test undo on panel, CallInEditor, and with an active landscape edit layer.

If the selected layer info uses `bNoWeightBlend`, the operation should warn. In that setup the target layer may receive paint, but the usual "other layers are reduced under the road" behavior is not guaranteed.

## Generated Geometry Duplicates After Rebuild

Generated components are tag-cleaned. If duplicates appear:

- inspect whether custom code creates components without `GeneratedTag`
- check whether a modified component was duplicated manually
- run `CleanupRemovesAllTagged` automation

## Runtime Async Does Not Finish

Check:

- `bUseAsyncBuild = true`
- world timer manager is ticking
- actor is valid and not destroyed
- `SegmentsPerTick` is at least `1`
- validation did not abort before starting

The runtime pump re-arms itself with `SetTimerForNextTick` while building.

## BuildPlugin Or Build Fails With Unity Collisions

Some modules define similarly named anonymous-namespace helpers. If unity grouping combines those files, MSVC can report duplicate definitions. The affected module should use non-unity build settings such as `bUseUnity = false`.

## Automation Finds No Tests

Check:

- editor target was built
- development automation tests are enabled
- command uses `Automation RunTests AsyncSplineBuilder`
- tests are compiled into the editor module

## Logs Are Too Noisy

Search the log for:

```text
AsyncSplineBuilder
Result={Fail}
Result={Success}
TEST COMPLETE
```

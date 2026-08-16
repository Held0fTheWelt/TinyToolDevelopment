# Automation And QA

This document describes how to verify Async Spline Builder after code, asset, or documentation changes.

## Editor Build

```text
D:\Engines\UE_5.4\Engine\Build\BatchFiles\Build.bat PluginProjectEditor Win64 Development -Project=D:\PluginProjectGit\PluginProject.uproject -WaitMutex -FromMsBuild -architecture=x64
```

Use this before running editor automation tests.

## Runtime Build

```text
D:\Engines\UE_5.4\Engine\Build\BatchFiles\Build.bat PluginProject Win64 Development -Project=D:\PluginProjectGit\PluginProject.uproject -WaitMutex -FromMsBuild -architecture=x64
```

Use this to confirm packaged/runtime-safe code paths still compile.

## Automation Command

```text
D:\Engines\UE_5.4\Engine\Binaries\Win64\UnrealEditor-Cmd.exe D:\PluginProjectGit\PluginProject.uproject -unattended -nop4 -nosplash -NullRHI -ExecCmds="Automation RunTests AsyncSplineBuilder; Quit" -log
```

Expected result:

- tests are discovered under `AsyncSplineBuilder`
- every test completes with `Result={Success}`
- final automation exit code is `0`

## Current Test Coverage

The automation suite covers these paths:

- `AsyncSplineBuilder.OpenSplineBuilds`
- `AsyncSplineBuilder.ClosedSplineWrapSegment`
- `AsyncSplineBuilder.LayoutContractRecords`
- `AsyncSplineBuilder.ConnectorKindsCanonical`
- `AsyncSplineBuilder.LayoutConnectorFacade`
- `AsyncSplineBuilder.LayoutConnectorEmptyKindError`
- `AsyncSplineBuilder.LayoutConnectorUnknownKindWarning`
- `AsyncSplineBuilder.ConnectorValidationNeverBlocksBuild`
- `AsyncSplineBuilder.LayoutConnectorValidationMissingLayout`
- `AsyncSplineBuilder.LayoutConnectorValidationDistanceBounds`
- `AsyncSplineBuilder.LayoutConnectorDisabledLayoutWarning`
- `AsyncSplineBuilder.LayoutConnectorPitEntryExitSemantics`
- `AsyncSplineBuilder.MultiLayoutBuildTags`
- `AsyncSplineBuilder.RebuildSingleLayoutKeepsMain`
- `AsyncSplineBuilder.EditorLayoutFacade`
- `AsyncSplineBuilder.EditorAddPitLaneLayout`
- `AsyncSplineBuilder.TrackShape.JsonRoundTrip`
- `AsyncSplineBuilder.TrackShape.MainLengthScale`
- `AsyncSplineBuilder.TrackShape.ApplyMainAndPit`
- `AsyncSplineBuilder.TrackShape.DesignerOperations`
- `AsyncSplineBuilder.TrackShape.PanelActions`
- `AsyncSplineBuilder.LayoutConnectorReadJson`
- `AsyncSplineBuilder.LayoutConnectorApplyTool`
- `AsyncSplineBuilder.LayoutConnectorRemoveTool`
- `AsyncSplineBuilder.ConnectorEditDoesNotDeleteGeneratedComponents`
- `AsyncSplineBuilder.ConnectorDebugCreatesEndpointLabels`
- `AsyncSplineBuilder.ConnectorDebugCleanupKeepsRoadGeometry`
- `AsyncSplineBuilder.ConnectorDebugSkipsInvalidEndpoints`
- `AsyncSplineBuilder.ExtraMeshStartOnly`
- `AsyncSplineBuilder.ExtraMeshTagNotRoad`
- `AsyncSplineBuilder.JumpGapSuppressesRoad`
- `AsyncSplineBuilder.CleanupRemovesAllTagged`
- `AsyncSplineBuilder.DataAssetRoundTrip`
- `AsyncSplineBuilder.SegmentLengthPlan`
- `AsyncSplineBuilder.ValidationBlocksBadBuild`
- `AsyncSplineBuilder.GroundWallGapStripValid`
- `AsyncSplineBuilder.GroundWallDropBoundarySplit`
- `AsyncSplineBuilder.DropWallCount`
- `AsyncSplineBuilder.ClosedLoopSeamDropWallFirstSegment`
- `AsyncSplineBuilder.ClosedLoopSeamDropWallLastSegment`
- `AsyncSplineBuilder.EditorTrackDataExpand`
- `AsyncSplineBuilder.RuntimeAsyncBuildCompletes`
- `AsyncSplineBuilder.RuntimeAsyncBuildPumpsByPiece`
- `AsyncSplineBuilder.RuntimeAsyncMultiLayoutBuilds`
- `AsyncSplineBuilder.EditorAsyncDebounceKeepsExistingBuild`
- `AsyncSplineBuilder.FalloffWeight`
- `AsyncSplineBuilder.ResolvePaintHalfWidth`
- `AsyncSplineBuilder.ClosestOnPolyline`
- `AsyncSplineBuilder.FalloffWeightHardEdge`
- `AsyncSplineBuilder.ClosestOnPolylineDegenerate`

## What The Tests Prove

They prove:

- road mesh counts are deterministic for simple open and closed splines
- extra meshes do not accidentally count as road meshes
- jump gaps suppress road geometry
- generated component cleanup is tag-based enough to recover from stale arrays
- data asset save/load preserves spline point count
- segment length planning affects piece count
- validation blocks a destructive bad build
- ground walls can survive a gap without invalid empty sections
- drop regions create exactly one boundary wall in the simple case
- closed-loop drop walls are generated across the seam from last segment to first segment
- editor facade data expansion is safe for segment rows
- multi-layout build tags, single-layout rebuild isolation, editor layout facade behavior, and pit-lane layout creation stay covered
- native Track Shape Editor JSON, compile scale, actor apply, designer model operations, and panel action seams stay covered
- runtime async path can finish through the shared build pump, pump by generated piece, handle multi-layout queues, and preserve existing geometry during editor debounce
- connector kinds, facade mutation, validation, MCP read/apply/remove, and non-destructive connector edits stay covered
- connector debug creates independently resolved `UTextRenderComponent` endpoint labels with generated/debug/connector, row, role, and layout ownership tags but no segment tags
- invalid connector endpoints are skipped, and connector-debug refresh or cleanup leaves road component counts unchanged
- landscape footprint helpers produce deterministic falloff, paint width resolution, and closest-polyline results
- degenerate landscape sample input does not index out of bounds

## What The Tests Do Not Fully Prove

Manual QA is still required for:

- final visual quality on production landscapes
- material UV appearance on long walls
- collision behavior with project-specific pawn/vehicle classes
- all supported platforms
- real PIE timer-world behavior without test hooks
- landscape edit layer interactions in complex landscape setups
- Unreal's real weightmap write behavior for layer paint; pure automation covers the math, not `SetAlphaData`

## Manual QA Checklist

For each release candidate:

1. Build an open two-point road.
2. Build a four-point closed loop.
3. Add `RoadMeshLength` and confirm piece count.
4. Add `SegmentLength` and confirm fallback behavior.
5. Add start, middle, and end extra meshes.
6. Add a jump gap and confirm no road or extra mesh bridges it.
7. Add a drop and confirm the boundary wall.
8. Enable ground walls and inspect both sides.
9. Disable one side in per-segment wall settings.
10. Test trace misses and fallback depth.
11. Toggle collision and inspect collision in editor.
12. Run `DeformLandscapeNow` on a disposable landscape.
13. Run **Paint Layer** with a registered weight-blended `PaintLayer` (two-layer landscape): coverage, `PaintHalfWidth` override, weight adjust, undo via panel, CallInEditor, named edit layer, and `PaintFallOff = 0` hard edge.
14. Repeat **Paint Layer** with a `bNoWeightBlend` layer info and verify the warning/caveat: the target layer may paint, but other layers are not guaranteed to be reduced.
15. Open **Track Shape Editor**, add pit-lane, alternate, and service-road layouts, duplicate a layout, edit anchor coordinates, add/delete anchors, add/delete segments, switch line/bezier, validate, and apply to a disposable actor.
16. Add **Pit Entry** and **Pit Exit** connectors in the panel, validate them, rebuild, and confirm generated road output is unchanged except for explicit rebuild output.
17. Enable **Show Connector Debug**, inspect the `From` and `To` endpoint labels, edit a connector and confirm the labels refresh without a rebuild, then enter an invalid endpoint and confirm it is skipped while validation reports the problem. Disable the checkbox and confirm connector labels disappear while road, extra mesh, ground wall, and drop wall components remain intact.
18. Read the actor through MCP/UCM and confirm `connector_count`, `connectors[]`, per-row errors/warnings, and world endpoints for resolved connectors.
19. Test PIE.
20. Test a packaged development build.

## Log Locations

Automation logs are written under:

```text
Saved\Logs\PluginProject.log
Saved\Automation\
```

UnrealBuildTool logs are written under:

```text
C:\Users\<User>\AppData\Local\UnrealBuildTool\Log.txt
```

## Release Gate

Do not ship when:

- editor build fails
- runtime build fails
- AsyncSplineBuilder automation fails
- new generated components lack tags
- connector debug markers lack connector/row/role/layout ownership tags, carry segment tags, or affect road/terrain/rebuild behavior
- validation allows a known destructive misconfiguration
- docs overclaim layer paint (replace/clear, per-segment, or manual QA on real landscape not done)
- docs imply `bNoWeightBlend` layers reduce other landscape layers

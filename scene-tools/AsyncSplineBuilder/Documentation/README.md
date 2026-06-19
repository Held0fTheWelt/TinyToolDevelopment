# Async Spline Builder Documentation

Async Spline Builder generates road, race-track, pipe, rail, wall, and side-object spline meshes without forcing large editor stalls. It supports synchronous builds, editor async batching, runtime async batching, per-segment mesh plans, optional ground walls, stunt gaps, drop walls, spline point data assets, and editor-only landscape height deformation plus additive layer paint.

This folder contains the documentation delivered with the plugin.

## Start Here

- [BuyerGuide.md](BuyerGuide.md): product-level overview, workflows, strengths, and limitations.
- [UserManual.md](UserManual.md): complete editor workflow from first actor placement to rebuilds.
- [FAQ.md](FAQ.md): Fab-ready questions and answers.

## Reference

- [SettingsReference.md](SettingsReference.md): every important actor setting and recommended baseline.
- [LandscapeAndWalls.md](LandscapeAndWalls.md): snapping, height deformation, ground walls, gaps, and drop walls.
- [TechnicalOverview.md](TechnicalOverview.md): maintainer-level architecture and build flow.
- [CodeDocumentation.md](CodeDocumentation.md): source layout, code contracts, risky paths, and extension points.
- [AutomationAndQA.md](AutomationAndQA.md): build commands, automation tests, and release QA expectations.
- [Troubleshooting.md](Troubleshooting.md): common setup, build, trace, and geometry issues.
- [ReleaseChecklist.md](ReleaseChecklist.md): pre-release and Fab submission checklist.
- [AsyncSplineBuilder_Technical_Audit.md](AsyncSplineBuilder_Technical_Audit.md): implementation audit and remediation notes.
- [CompletionPlan.md](CompletionPlan.md): remaining landscape paint hardening, QA gates, and documentation alignment.

Legacy documentation:

- [AsyncSplineTrackBuilder_Readme.txt](AsyncSplineTrackBuilder_Readme.txt): original long-form readme kept for compatibility.

## Quick Workflow

1. Enable the plugin and restart the editor if required.
2. Open **Tools > Track Tools > Async Spline Builder**.
3. Place or select an `ASplineGeneratingActor` from the workflow panel.
4. Assign `MainMesh` in the panel setup section.
5. Edit the `TrackSpline` points in the viewport.
6. Use **Build Now** for an immediate build or **Rebuild** for async batching.
7. Use the segment helpers to create per-segment rows before advanced per-segment edits.
8. Optional: enable ground walls and configure trace object types in the Details panel.
9. Optional: assign a landscape, run **Deform Height**, then **Paint Layer** (requires `PaintLayer` on the actor) for additive weight painting.

## Main Features

- Road or track mesh generation along a spline.
- Async editor rebuilds with `SegmentsPerTick`.
- Runtime async rebuilds using a next-tick timer pump.
- Per-segment mesh selection and mesh length planning.
- Start, middle, and end extra meshes for rails, barriers, fences, pipes, or detail meshes.
- Stunt gaps that suppress road and side meshes.
- Drop regions and procedural drop walls between height steps.
- Procedural ground walls that trace down to terrain or other configured object types.
- Tag-based generated component cleanup that survives stale arrays and construction rebuilds.
- Spline point save/load through `USplinePointListAsset`.
- Editor-only landscape height deformation plus additive global layer paint.
- Automation tests for the highest-risk behaviors.

## Supported Runtime Position

The runtime module contains the actor, spline mesh generation, ground wall generation, drop wall generation, data asset access, and runtime async pump.

The editor module contains the workflow panel, editor-only landscape deformation and layer paint, and editor selection helpers. Packaged games can build the spline meshes and procedural walls, but landscape height/weight edits and the workflow panel are editor-only.

## Editor Workflow Panel

The primary editor surface is **Tools > Track Tools > Async Spline Builder**. It groups the common workflow into **Build**, **Segments**, and **Terrain** tabs so day-to-day tasks stay compact without hiding validation status.

Use the panel for day-to-day work. Use the Unreal Details panel for advanced raw fields such as per-segment extra mesh arrays, detailed wall UV settings, trace object arrays, custom collision settings, and experimental fields.

## Important Limitations

- Landscape: height deformation plus **additive global** layer weight paint when `PaintLayer` is set (`PaintLandscapeLayerNow` or panel **Paint Layer**). Replace/clear paint mode is not implemented. See [CompletionPlan.md](CompletionPlan.md) for the remaining manual landscape QA gate and the documented no-weight-blend caveat.
- Landscape deformation is a one-shot editor operation, not an automatic part of every track rebuild.
- Complex production landscapes still need manual QA, especially tight curves, very steep terrain, and mixed per-segment wall settings.
- Runtime async automation is covered through a deterministic test hook; a full PIE timer-world integration pass is still recommended for release maps.

## Quick Build And Test Commands

Editor build:

```text
D:\Engines\UE_5.4\Engine\Build\BatchFiles\Build.bat PluginProjectEditor Win64 Development -Project=D:\PluginProjectGit\PluginProject.uproject -WaitMutex -FromMsBuild -architecture=x64
```

Runtime/game build:

```text
D:\Engines\UE_5.4\Engine\Build\BatchFiles\Build.bat PluginProject Win64 Development -Project=D:\PluginProjectGit\PluginProject.uproject -WaitMutex -FromMsBuild -architecture=x64
```

Automation:

```text
D:\Engines\UE_5.4\Engine\Binaries\Win64\UnrealEditor-Cmd.exe D:\PluginProjectGit\PluginProject.uproject -unattended -nop4 -nosplash -NullRHI -ExecCmds="Automation RunTests AsyncSplineBuilder; Quit" -log
```

## Recommended First Production Pass

Use a short open test spline first, then a closed loop, then the real track. Keep `bUseAsyncBuild` enabled, start with `SegmentsPerTick = 2`, and only raise it after confirming editor responsiveness. Configure trace object types before enabling snapping or ground walls, because validation intentionally blocks builds that would otherwise destroy old geometry and produce no valid replacement.

## Legal Note

Async Spline Builder is provided under the license terms included with the product distribution. The plugin does not grant rights to third-party meshes, materials, landscapes, or content used with generated tracks.

# Release Checklist

Use this checklist before publishing or packaging Async Spline Builder.

## Product Identity

- Plugin name is correct in `.uplugin`.
- Version and version name are updated.
- Description matches current features.
- Marketplace/Fab URL is correct.
- Documentation folder is included.
- Icon is present.

## Documentation

- `README.md` links to every major document.
- Buyer guide explains what the plugin does and does not do.
- User manual covers the workflow panel and first-run workflow.
- Settings reference covers the main actor properties.
- FAQ is buyer-ready and written in product-page language.
- Troubleshooting covers build, snapping, walls, drops, and landscape issues.
- Technical overview and code documentation are current.
- Docs describe additive global layer paint accurately (not replace/clear or per-segment).

## Source Code

- Public structs and properties have clear comments or tooltips.
- Runtime code does not include editor-only landscape edit APIs.
- Generated component role tags are still distinct.
- Cleanup scans tags rather than only transient arrays.
- Build plan is consumed by road, extra mesh, wall width, and deformation paths.
- Validation blocks destructive misconfiguration before clearing geometry.

## Assets

- Example meshes load.
- Example materials load.
- Example map opens.
- Demo content does not rely on missing project-only assets.

## Editor Build

Run:

```text
D:\Engines\UE_5.4\Engine\Build\BatchFiles\Build.bat PluginProjectEditor Win64 Development -Project=D:\PluginProjectGit\PluginProject.uproject -WaitMutex -FromMsBuild -architecture=x64
```

Pass criteria:

- build succeeds
- no new compile warnings from AsyncSplineBuilder

## Runtime Build

Run:

```text
D:\Engines\UE_5.4\Engine\Build\BatchFiles\Build.bat PluginProject Win64 Development -Project=D:\PluginProjectGit\PluginProject.uproject -WaitMutex -FromMsBuild -architecture=x64
```

Pass criteria:

- build succeeds
- editor-only module is not required by runtime target

## Automation

Run:

```text
D:\Engines\UE_5.4\Engine\Binaries\Win64\UnrealEditor-Cmd.exe D:\PluginProjectGit\PluginProject.uproject -unattended -nop4 -nosplash -NullRHI -ExecCmds="Automation RunTests AsyncSplineBuilder; Quit" -log
```

Pass criteria:

- all AsyncSplineBuilder tests succeed
- exit code is `0`

## Manual Editor QA

- Place actor in a clean level.
- Assign `MainMesh`.
- Build open spline.
- Build closed loop.
- Test async rebuild while moving points.
- Test extra meshes.
- Test jump gaps.
- Test drops and drop walls.
- Test ground walls.
- Test landscape snapping.
- Test landscape height deformation on a disposable landscape.
- Test landscape layer weight paint: assign a weight-blended `PaintLayer`, run **Paint Layer**, verify fade/`PaintHalfWidth`, other layers reduced under road, undo (panel + CallInEditor + active edit layer), and `PaintFallOff = 0` hard edge.
- Test a `bNoWeightBlend` paint layer and verify the warning/caveat is visible: target-layer paint may be written, but other layers are not guaranteed to be reduced.
- Open **Tools > Track Tools > Async Spline Builder**.
- Create or select an actor through the panel.
- Run panel validation, synchronous build, async rebuild, cancel, segment row creation, and landscape assignment.

## Manual Runtime QA

- Open the test map in PIE.
- Trigger runtime rebuild.
- Confirm async build completes.
- Confirm generated road and wall components appear.
- Confirm collision setting behaves as expected.
- Package a development build when the release target requires it.

## Fab Submission Notes

- Screenshots or videos should show the actual road/track result.
- Product text should mention async batching, runtime generation, extra meshes, ground walls, gaps, drops, landscape height deformation, and **additive global** layer weight paint (when `PaintLayer` is set).
- Do not claim replace/clear paint, per-segment paint layers, or automated weightmap tests.
- Include the documentation folder in the packaged plugin.
- Include support contact information.

## Final Gate

Do not release if:

- build fails
- automation fails
- docs are stale
- docs overclaim layer paint (replace/clear, per-segment, or untested undo on edit layers)
- docs imply `bNoWeightBlend` layers behave like normal weight-blended layers
- generated components duplicate after rebuild
- runtime target depends on editor-only code

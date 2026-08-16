# Release Checklist

Use this checklist before publishing or handing off a Performance Preset Wizard build.

## Source Validation

- Run isolated plugin build with strict includes.
- Confirm there are no unresolved compiler warnings introduced by the plugin.
- Confirm public headers include all types they expose.
- Confirm public module dependencies match public header usage.
- Confirm private dependencies are not accidentally required by public headers.
- Confirm startup delegate cleanup is balanced on module shutdown.
- Confirm settings registration and unregistration are balanced.
- Confirm detail customization registration and unregistration are balanced.

## Functional Validation

- Enable the plugin in a clean project.
- Restart the editor.
- Open **Tools > Performance > Performance Preset Wizard**.
- Verify sample presets are discoverable.
- Select each sample preset and confirm details render.
- Apply at least one low, mid, high, VR, and cinematic preset.
- Confirm apply status includes CVar counters.
- Test an unknown CVar and confirm it is reported but does not block valid entries.
- Test an empty CVar name/value and confirm it is counted invalid.
- Use **Restore Previous** after applying a preset.
- Confirm restore is unavailable again after the restore point is consumed.
- Configure a startup preset.
- Restart the editor and confirm startup application.

## Preset Asset Validation

- Display names are clear and human-readable.
- Descriptions explain target hardware or workflow.
- Target platform values match the intended use.
- Quality levels stay in `0..4`.
- CVar lists are short and intentional.
- Editor-only flags are correct.
- Sample presets do not contain stale or project-specific CVars that confuse buyers.

## Documentation Validation

- `Documentation/README.md` links to every guide.
- Buyer guide matches the current feature set.
- User manual matches the current UI labels.
- Settings reference lists every setting and asset field.
- Sample presets reference lists each shipped preset asset.
- Preset authoring guide describes all supported CVar syntax.
- Automation and CI guide includes the current strict BuildPlugin command.
- Technical overview reflects current module responsibilities.
- Code documentation reflects current source layout.
- Troubleshooting covers the most likely support cases.
- FAQ includes marketplace-relevant buyer questions.
- Screenshots/diagrams render correctly in Markdown preview.
- `Config/FilterPlugin.ini` includes `/Documentation/...`.

## Packaging Validation

- Packaged plugin contains `Readme.pdf`.
- Packaged plugin contains `PerformancePresetWizard_Changelog.txt`.
- Packaged plugin contains the `Documentation` folder.
- Packaged plugin contains sample content assets.
- Packaged plugin contains `Resources/Icon128.png`.
- Packaged plugin can be copied into a clean project and enabled.

## Fab Submission Review

- Product description does not imply automatic benchmarking or hardware detection.
- Documentation explains editor-focused scope.
- Screenshots demonstrate actual workflow, not only marketing copy.
- Changelog is current.
- Version number in `.uplugin` is current.
- License headers are present in source files.
- No temporary build output is included in the plugin folder.

## Recommended Build Command

```powershell
Engine\Build\BatchFiles\RunUAT.bat BuildPlugin -Plugin="D:\PluginProjectGit\Plugins\PerformancePresetWizard\PerformancePresetWizard.uplugin" -Package="D:\PluginProjectGit\Saved\PerformancePresetWizardBuildCheck" -TargetPlatforms=Win64 -StrictIncludes
```

Delete the temporary package folder after validation if it was created only as a local build check.

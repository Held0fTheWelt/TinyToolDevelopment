# Release Checklist

Use this checklist before packaging LogLevelEditor for Fab or a project release.

## Documentation

- [ ] `Documentation/README.md` is current.
- [ ] `BuyerGuide.md` describes current value and limitations.
- [ ] `UserManual.md` matches the current UI labels.
- [ ] `SettingsReference.md` lists every user-facing setting.
- [ ] `TechnicalOverview.md` matches module behavior.
- [ ] `CodeDocumentation.md` matches source layout.
- [ ] `FAQ.md` answers likely buyer questions.
- [ ] `Troubleshooting.md` includes common support cases.
- [ ] Legacy `Readme.pdf` is still accurate or clearly superseded.
- [ ] Changelog lists user-facing behavior changes.

## Source Documentation

- [ ] Public headers have Doxygen-style comments on classes, structs, and important functions.
- [ ] Non-obvious `.cpp` flows explain why they exist.
- [ ] Startup retry behavior is documented.
- [ ] Console command success/failure behavior is documented.
- [ ] DataAsset override semantics are documented.

## Functional Checks

- [ ] Plugin enables in a clean UE 5.4 project.
- [ ] Editor opens without startup warnings.
- [ ] Tool opens from **Tools → Log Tools → Log Level Editor** or the toolbar shortcut.
- [ ] Project source categories are discovered.
- [ ] Plugin source categories are discovered.
- [ ] Default verbosity values are detected for common macros.
- [ ] Changing a category executes the correct console command.
- [ ] Failed commands do not update UI/DataAsset state.
- [ ] Selecting the detected default removes persistent overrides.
- [ ] Startup replay reapplies saved overrides.

## Data And Config

- [ ] Default DataAsset exists and loads.
- [ ] Auto-save setting behaves as documented.
- [ ] Temporary hide settings are not persisted.
- [ ] Permanent hide settings are persisted.
- [ ] FilterPlugin includes documentation and changelog files.

## Build And Tests

- [ ] `RunUAT BuildPlugin` succeeds for Win64.
- [ ] Automation tests compile.
- [ ] Automation tests run in an editor test environment.
- [ ] `git diff --check -- Plugins/LogLevelEditor` is clean.

## Fab Packaging

- [ ] `.uplugin` description is buyer-friendly.
- [ ] VersionName is updated.
- [ ] DocsURL is current.
- [ ] SupportURL is current.
- [ ] MarketplaceURL is current when known.
- [ ] Screenshots/video match current behavior.
- [ ] No temporary local debug files are packaged.

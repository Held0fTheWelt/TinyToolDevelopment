# Technical Overview

This document describes the internal architecture of Performance Preset Wizard for maintainers and reviewers.

## Modules

The plugin is split into a runtime module and an editor module.

`PerformancePresetWizard` is the runtime module. It owns stable asset classes, preset data types, the low-level applier, runtime subsystem, backup state, storage provider, runtime settings, and the simple runtime selector widget.

Responsibilities:

- Keep `UPerformancePresetAsset` class paths stable.
- Apply scalability and CVar settings without Slate or UnrealEd dependencies.
- Capture and restore previous scalability/CVar state.
- Persist active runtime preset state and backup history.
- Expose Blueprint-callable runtime APIs through `UPerformancePresetRuntimeSubsystem`.
- Provide `LogPerformancePresetRuntime`.

`PerformancePresetWizardEditor` is the editor module. It integrates with editor UI systems, the asset registry, Project Settings, the property editor, and editor startup behavior.

Responsibilities:

- Register and unregister the wizard tab/menu entry.
- Register the `UPerformancePresetAsset` detail customization.
- Register editor startup settings under Project Settings.
- Apply the configured editor startup preset after the editor engine is ready.
- Keep startup delegates and module shutdown cleanup balanced.

## Source Layout

| File | Responsibility |
| --- | --- |
| `PerformancePresetWizard.Build.cs` | Module dependencies and strict include support. |
| `PerformancePresetWizardEditor.Build.cs` | Editor-only dependencies for Slate wizard, menus, settings, and details customization. |
| `Public/PerformancePresetAsset.h` | Data asset schema for presets. |
| `Public/PerformancePresetTypes.h` | Target platform enum and CVar override struct. |
| `Public/PerformancePresetApplier.h` | Public apply/restore API and result struct. |
| `Private/PerformancePresetApplier.cpp` | Scalability application, CVar writes, direct restore snapshot, persistent backup capture/restore. |
| `Public/PerformancePresetRuntimeSubsystem.h` | GameInstance subsystem for runtime apply, active preset state, backup history, and storage provider override. |
| `Public/PerformancePresetRuntimeTypes.h` | Runtime backup snapshots, CVar backup values, and persisted state structs. |
| `Public/PerformancePresetStorageProvider.h` | Pluggable persistence interface and default GameUserSettings ini storage. |
| `Public/PerformancePresetRuntimeSettings.h` | Runtime preset library, history limit, and default storage provider class. |
| `Public/PerformancePresetRuntimeSelectorWidget.h` | Simple UMG/Slate runtime selector widget. |
| `PerformancePresetWizardEditor/Public/SPerformancePresetWizardWidget.h` | Editor Slate widget public/private interface. |
| `PerformancePresetWizardEditor/Private/SPerformancePresetWizardWidget.cpp` | Wizard UI, asset registry discovery, notifications, status text. |
| `PerformancePresetWizardEditor/Public/PerformancePresetAssetCustomization.h` | Details customization interface. |
| `PerformancePresetWizardEditor/Private/PerformancePresetAssetCustomization.cpp` | Quality dropdowns and bulk CVar editor. |
| `Public/PerformancePresetWizardSettings.h` | Editor per-project user settings. |
| `Public/PerformancePresetWizard.h` | Module class declaration. |
| `Private/PerformancePresetWizard.cpp` | Runtime module startup/shutdown and log category definitions. |
| `PerformancePresetWizardEditor/Private/PerformancePresetWizardEditor.cpp` | Editor module startup/shutdown, menu, settings, customization registration, and editor startup preset. |

## Data Model

`UPerformancePresetAsset` contains:

- Localized display name and description.
- Target platform classification.
- Integer quality fields for UE5 scalability buckets.
- A list of `FPerformanceCVarOverride` entries.

The asset intentionally stores CVar values as strings. Unreal CVars can be integer, float, bool, or string-like, and preserving the raw author-provided value keeps the asset format simple.

## Apply Flow

The applier uses this sequence:

1. Return a zero-result if the preset pointer is null.
2. Resolve `IConsoleManager`.
3. Capture a restore snapshot before any writes happen.
4. Build a `Scalability::FQualityLevels` structure.
5. Clamp each preset quality value to `0..4`.
6. Apply the quality structure with `Scalability::SetQualityLevels`.
7. Iterate CVar overrides.
8. Trim name and value.
9. Count empty entries as invalid.
10. Skip editor-only entries outside editor contexts.
11. Find each registered CVar.
12. Report missing CVars and continue.
13. Apply found CVars with `ECVF_SetByConsole`.
14. Return counters to the UI.

## Restore Flow

The restore snapshot stores:

- A copy of `Scalability::FQualityLevels` captured before the last apply.
- Previous values for the specific CVars that the preset was about to overwrite.

The direct editor restore path stores one immediate snapshot. Applying a second preset replaces that direct restore point. Runtime applies additionally store a persisted backup history through `UPerformancePresetRuntimeSubsystem`.

Restore is best-effort:

- Scalability is restored first.
- CVars that still exist are restored.
- CVars that disappeared after apply are skipped.
- The snapshot is cleared after a successful restore attempt.

## Runtime Subsystem Flow

`UPerformancePresetRuntimeSubsystem` is a `UGameInstanceSubsystem`. It loads persisted state during subsystem initialization, but it does not auto-apply a saved preset.

Runtime apply sequence:

1. Validate the preset pointer.
2. Capture a persistent backup entry before writes.
3. Call `PerformancePreset::ApplyPreset`.
4. Insert the backup newest-first when apply succeeds.
5. Trim the backup history to the configured limit.
6. Store the active preset path.
7. Save runtime state through the current storage provider.

Runtime restore sequence:

1. Resolve the latest backup or a backup by id.
2. Restore scalability and captured CVar values.
3. Set the active preset path back to the previous active preset path.
4. Remove the restored entry and all newer entries.
5. Save the reduced history.

## Runtime Storage

`UPerformancePresetStorageProvider` is the replaceable persistence contract. The default implementation, `UPerformancePresetGameUserSettingsStorage`, writes runtime state into `GameUserSettings` ini data.

Projects can set a storage provider class in `UPerformancePresetRuntimeSettings` or install an instance at runtime through `SetStorageProvider`.

## Widget Flow

`SPerformancePresetWizardWidget` owns the editor-facing workflow:

- Query the asset registry for preset assets.
- Build a stable list of `FAssetData` entries.
- Preserve selection by soft object path during refresh.
- Load the selected asset only when needed for details or apply.
- Display status feedback from apply and restore operations.
- Trigger editor notifications for visible feedback.

The widget stores summary strings as cached `FText` values. This keeps the Slate tree simple and avoids reformatting long CVar lists on every paint.

## Details Customization Flow

`FPerformancePresetAssetCustomization` improves asset authoring:

- It presents scalability integers as quality dropdowns.
- It includes all UE5 quality buckets exposed by the asset.
- It hides the raw CVar array behind a bulk text editor.
- It uses transactions when applying parsed text back to the asset.
- It reports malformed and unknown lines through editor notifications.

The customization favors authoring feedback over hard failure. Unknown CVars can be intentional when assets are shared across projects or engine versions, so they are visible but not destructive.

## Startup Preset Flow

Startup settings are stored in `UPerformancePresetWizardSettings` using `EditorPerProjectUserSettings`.

On module startup:

1. Settings are registered with `ISettingsModule`.
2. The module checks whether startup application is enabled.
3. If enabled, application is deferred until editor engine initialization.
4. The soft pointer is loaded.
5. The loaded preset is passed to `PerformancePreset::ApplyPreset`.

The deferred approach avoids applying scalability before editor systems are ready.

## Error Handling Philosophy

Performance preset application should be resilient. One bad CVar should not prevent the rest of the preset from applying. The plugin therefore:

- Logs missing CVars.
- Counts invalid entries.
- Keeps applying valid entries.
- Reports partial success to the user.
- Provides a restore point captured before writes.

This model is better for iterative production work than a fail-fast model where one stale CVar blocks all useful settings.

## Packaging Notes

`Config/FilterPlugin.ini` includes the user-facing documentation folder so marketplace packages contain the Markdown guides and diagrams. Keep this file updated when adding new documentation or support files.

## Validation

The release validation command should include strict includes:

```powershell
Engine\Build\BatchFiles\RunUAT.bat BuildPlugin -Plugin="D:\PluginProjectGit\Plugins\PerformancePresetWizard\PerformancePresetWizard.uplugin" -Package="D:\PluginProjectGit\Saved\PerformancePresetWizardBuildCheck" -TargetPlatforms=Win64 -StrictIncludes
```

Strict includes are important because editor modules can accidentally compile through transitive includes in a full project build.


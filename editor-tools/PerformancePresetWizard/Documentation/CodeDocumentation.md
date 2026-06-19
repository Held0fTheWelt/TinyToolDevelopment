# Code Documentation

This document records the source-level contracts and extension points for Performance Preset Wizard. It complements the inline comments in the headers and implementation files.

## Public API Surface

## `UPerformancePresetAsset`

`UPerformancePresetAsset` is the preset data contract. It should remain stable because preset assets are user-authored content.

Key guarantees:

- Quality fields are editable in the editor and readable from Blueprints.
- Quality fields use `ClampMin`, `ClampMax`, `UIMin`, and `UIMax` metadata for the `0..4` scalability range.
- Display fields use tooltips so users understand how they appear in the wizard.
- CVar overrides are applied after scalability.

When adding a new quality bucket:

1. Add the field to `UPerformancePresetAsset`.
2. Add a tooltip and clamp metadata.
3. Add the property handle to the details customization.
4. Add a dropdown row.
5. Add it to the wizard detail summary.
6. Add it to `PerformancePreset::ApplyPreset`.
7. Update documentation.

## `EPerformanceTargetPlatform`

The target platform enum is descriptive, not restrictive. It should not be used as a hard gate unless a future feature explicitly adds filtering or recommendation logic.

When adding enum values, prefer names that describe a production workflow rather than a single device model.

## `FPerformanceCVarOverride`

The override struct stores a console variable name, value, and editor-only flag.

Important details:

- Values are strings by design.
- The applier trims names and values before use.
- Empty names or values are counted as invalid.
- Editor-only entries are skipped when the current context is not editor.

Do not introduce type-specific fields unless the plugin also gains explicit typed validation and migration support.

## `FPerformancePresetApplyResult`

This struct lets UI code report partial success without parsing logs.

The result intentionally contains counters rather than a long list of individual failures. Detailed failure information belongs in logs and editor notifications; the result struct is for compact user feedback.

## `PerformancePreset::ApplyPreset`

The apply function is the central behavior contract.

Expected behavior:

- Null preset is a no-op and returns a zero result.
- A restore snapshot is captured before writes.
- Scalability is applied using Unreal's `Scalability::FQualityLevels`.
- Quality values are clamped.
- CVar overrides are processed independently.
- Missing CVars are logged and counted.
- Valid CVars still apply even if other entries fail.

The function should stay deterministic and free of UI dependencies so it can be reused by startup application and future commandlet or automation features.

## `PerformancePreset::RestorePreviousSettings`

Restore is intentionally one-level deep.

Expected behavior:

- Return false when no snapshot exists.
- Restore scalability first.
- Restore captured CVar values if the CVars still exist.
- Clear the snapshot after restore.

Runtime multi-step history is implemented separately in `UPerformancePresetRuntimeSubsystem` so the direct editor restore path remains simple and immediate.

## `UPerformancePresetRuntimeSubsystem`

The runtime subsystem is the packaged-game entry point. It is a `UGameInstanceSubsystem` and must stay free of editor-only module dependencies.

Key behavior:

- `ApplyRuntimePreset` captures a persistent backup before applying the preset.
- `RestoreLatestBackup` restores the newest backup entry.
- `RestoreBackupById` restores a specific backup and discards that entry plus newer entries.
- `GetActivePreset` loads the currently recorded active preset path.
- `GetBackupHistory` returns persisted backups newest-first.
- `SetStorageProvider` lets projects replace the default ini storage.
- No preset is auto-applied on subsystem initialization.

## `UPerformancePresetStorageProvider`

Storage providers own persistence for `FPerformancePresetRuntimeState`.

The default implementation writes active preset path and backup history into `GameUserSettings` ini data. Project-specific subclasses can redirect state to a save game, backend profile, platform settings layer, or custom project config.

## `UPerformancePresetRuntimeSelectorWidget`

The runtime selector widget is a small UMG-facing widget, not a full game options framework.

Important behavior:

- It can read presets from its own `PresetLibrary`.
- If empty, it can fall back to the runtime subsystem's configured preset library.
- It exposes apply and restore-latest actions.
- It is intended to be replaced or subclassed by games with their own UI.

## `SPerformancePresetWizardWidget`

The Slate widget owns user interaction and display state.

Important state:

- `PresetAssetDataList`: discovered asset registry results.
- `PresetListView`: visual list of preset entries.
- `SelectedPreset`: weak pointer to the selected loaded asset.
- Cached `FText` summaries for display name, description, scalability, CVars, and status.

Design notes:

- Use asset registry data for listing to avoid loading every preset eagerly.
- Load the selected asset only when details or apply behavior requires it.
- Preserve selection by soft object path across refresh.
- Keep the right-hand detail pane text cached for predictable Slate behavior.

## `FPerformancePresetAssetCustomization`

The details customization is an authoring tool, not the runtime contract. It can evolve more freely than the asset schema.

Important behavior:

- Hide the raw CVar array when presenting the bulk editor.
- Wrap text-to-array changes in a transaction for undo/redo.
- Use property handles where possible so editor state remains consistent.
- Report malformed lines and unknown CVars clearly.

## Module Startup And Shutdown

`FPerformancePresetWizardModule` owns runtime module startup and log category definitions.

`FPerformancePresetWizardEditorModule` must keep editor registrations balanced:

- Register tab spawner on startup and unregister on shutdown.
- Register menu entries through ToolMenus.
- Register settings through Settings module and unregister them on shutdown.
- Register custom class layout and unregister it on shutdown.
- Remove deferred startup preset delegates if shutdown occurs before they fire.

Balanced cleanup matters because editor modules can be hot-reloaded or disabled during development.

## Build Dependencies

Runtime public dependencies include modules needed by runtime public headers:

- `Core`
- `CoreUObject`
- `Engine`
- `DeveloperSettings`
- `UMG`
- `Slate`
- `SlateCore`

Runtime private dependencies include:

- `InputCore`

Editor public/private dependencies include editor implementation details:

- `AssetRegistry`
- `PropertyEditor`
- `UnrealEd`
- `ToolMenus`
- `LevelEditor`
- `Settings`

Keep dependencies close to the file that needs them. If a public header includes a type from a module, that module belongs in public dependencies.

## Extension Points

Useful future extensions:

- Preset filtering by target platform.
- Comparison view between current settings and selected preset.
- Optional benchmark notes or FPS targets per preset.
- Import/export of preset definitions to text or JSON.
- Commandlet for validating preset CVar names in CI.
- Per-project documentation links from preset assets.

When adding features, keep `PerformancePreset::ApplyPreset` and `UPerformancePresetRuntimeSubsystem` independent from UnrealEd, ToolMenus, PropertyEditor, and editor notifications.

## Test And Verification Checklist

- Isolated `BuildPlugin` with `-StrictIncludes`.
- Open editor and verify menu entry.
- Open the wizard and confirm preset discovery.
- Select every sample preset.
- Apply a preset and verify status counters.
- Restore previous settings.
- Open a preset asset and test quality dropdowns.
- Export and re-apply CVar text.
- Add an unknown CVar and verify warning behavior.
- Enable startup preset and restart editor.
- Build a non-editor target and verify `ApplyRuntimePreset`.
- Verify runtime backup persistence and `RestoreLatestBackup`.
- Verify `RestoreBackupById` discards the restored entry plus newer entries.
- Verify custom storage provider replacement.


# Runtime Usage

Performance Preset Wizard now supports runtime target presets authored and reviewed in the editor. Presets remain `UPerformancePresetAsset` data assets, but packaged games can apply them manually through C++ or Blueprint.

Runtime usage is explicit in V1: the subsystem loads persisted state, but it does not auto-apply a saved preset during `GameInstance` startup.

## Blueprint API

Use `UPerformancePresetRuntimeSubsystem` from the current `GameInstance`.

| Function | Purpose |
| --- | --- |
| `ApplyRuntimePreset(Preset)` | Applies scalability values and non-editor-only CVar overrides, then stores a backup entry. |
| `RestoreLatestBackup()` | Restores the newest persisted backup entry. |
| `RestoreBackupById(BackupId)` | Restores a specific backup and removes that entry plus all newer entries. |
| `GetActivePreset()` | Loads and returns the currently recorded active preset asset. |
| `GetActivePresetPath()` | Returns the persisted active preset path without loading the asset. |
| `GetBackupHistory()` | Returns backup entries newest-first. |
| `ClearBackupHistory()` | Removes stored backup entries while keeping the active preset path. |
| `SetAvailablePresets(Presets)` | Overrides the preset list exposed to the default runtime selector widget. |
| `SetStorageProvider(Provider)` | Installs a project-specific persistence provider. |

## Backup History

Before every successful runtime apply, the subsystem captures:

- Current Unreal scalability values.
- Previous values for existing CVars that the preset is about to change.
- Previous active preset path.
- Applied preset path, backup id, and UTC timestamp.

Backups are persisted newest-first. The default history limit is `10` entries and can be changed in **Project Settings > Plugins > Performance Preset Wizard Runtime**.

Restoring an older entry behaves like an undo stack: the restored entry and all newer entries are discarded. This keeps the remaining history consistent with the restored state.

## Storage Provider

Out of the box, runtime state is stored in `GameUserSettings` ini data through `UPerformancePresetGameUserSettingsStorage`.

Projects can replace storage by subclassing `UPerformancePresetStorageProvider` and implementing:

- `LoadState`
- `SaveState`
- `ClearState`

Set the provider class in **Performance Preset Wizard Runtime** settings, or call `SetStorageProvider` on the runtime subsystem.

## Runtime Selector Widget

The plugin includes `UPerformancePresetRuntimeSelectorWidget` as a simple UMG entry point. It provides:

- Preset selection.
- Active apply action.
- Restore latest action.
- Compact status feedback.

The widget is intentionally small. It is suitable for internal test menus, development builds, and project-specific options screens that want a replaceable starting point.

## C++ Example

```cpp
if (UGameInstance* GameInstance = GetGameInstance())
{
    if (UPerformancePresetRuntimeSubsystem* Subsystem = GameInstance->GetSubsystem<UPerformancePresetRuntimeSubsystem>())
    {
        FPerformancePresetApplyResult Result = Subsystem->ApplyRuntimePreset(PresetAsset);
        if (Result.MissingCVarCount > 0)
        {
            UE_LOG(LogTemp, Warning, TEXT("Preset applied with missing CVars."));
        }
    }
}
```

## Runtime Boundaries

Performance Preset Wizard does not benchmark hardware, choose a preset automatically, or replace Device Profiles. Device Profiles remain the right place for platform policy. Runtime presets are best for explicit user choices, internal test flows, QA scenarios, and project-specific performance modes.

Editor-only CVar overrides are skipped outside editor contexts. Missing or invalid CVars are reported in the apply result and do not stop valid settings from being applied.

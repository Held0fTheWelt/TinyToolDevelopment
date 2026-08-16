# Code Documentation

This page documents the source layout and main code contracts of LogLevelEditor. It complements the inline Doxygen-style comments in the plugin headers.

## Source Layout

```text
Source/LogLevelEditor/
  LogLevelEditor.Build.cs
  Public/
    LogLevelEditorModule.h
    LogLevelEditorWidget.h
    LogLevelEditor_Settings.h
    LogLevelDataAsset.h
  Private/
    LogLevelEditorModule.cpp
    LogLevelEditorWidget.cpp
    LogLevelEditorCommands.h
    LogLevelEditorCommands.cpp
    LogChannelScanner.h
    LogChannelScanner.cpp
    LogLevelEditorVerbosity.h
    LogLevelEditorVerbosity.cpp
    Tests/
      LogLevelEditorTests.cpp
```

## Main Classes And Files

| Class/File | Responsibility |
| --- | --- |
| `FLogLevelEditorModule` | Module lifecycle, settings registration, startup replay, menu and tab wiring. |
| `SLogLevelEditorWidget` | Slate UI state, list rows, filtering, applying selected verbosity, DataAsset updates. |
| `FLogChannelScanner` | Asynchronous source scanner and duplicate filtering. |
| `LogLevelEditorVerbosity.*` | Shared verbosity list, conversion helpers, and console command execution. |
| `ULogLevelEditor_Settings` | Config-backed settings for scan scope, hidden channels, and DataAsset reference. |
| `ULogLevelDataAsset` | Persistent override asset. |
| `LogLevelEditorTests.cpp` | Automation coverage for scanner and verbosity helper behavior. |

## Module Lifecycle

`StartupModule` performs editor integration:

1. Register commands.
2. Register menu/toolbar entries.
3. Register the settings object.
4. Register the dockable tab entry point.
5. Schedule saved verbosity replay.

`ShutdownModule` unregisters integration points and removes ticker callbacks.

## Scanner Contract

`FLogChannelScanner` owns scan state.

Important functions:

- `StartIncrementalScan`: begins a new async scan and increments generation state.
- `DequeueCategory`: returns raw discovered categories.
- `DequeueFilteredCategory`: returns categories after hide-list filtering.
- `GetScanProgress`: exposes processed and total source-file counts.
- `ScanForLogCategories_Blocking`: synchronous wrapper for tests or non-UI callers.

Threading contract:

- Worker threads enqueue discovered categories.
- UI code dequeues on the game thread.
- Duplicate category names are protected by `SeenCategoriesCS`.
- Scan generation prevents stale output from older scans.

## Verbosity Contract

`LogLevelEditorVerbosity` centralizes mapping and command execution.

Important functions:

- `GetLogVerbosityNames`
- `TryGetLogVerbosityFromString`
- `GetStringForLogVerbosity`
- `GetFallbackLogVerbosity`
- `TryGetRuntimeLogCategoryVerbosity`
- `ShouldReapplySavedLogVerbosity`
- `ExecuteConsoleCommand`
- `SetLogCategoryVerbosity`

All UI and startup replay paths should use this helper instead of hand-building console commands or guessing runtime state from defaults.

## Widget Contract

The widget should treat Unreal's queried runtime verbosity as the source of truth for the `Current` label. Runtime reads must use read-only `Log list` output or another non-mutating API; `Log [cat]` is a toggle command and must not be used for reads. Successful console command execution gates state changes, and the widget should query the runtime value again after applying a change when possible.

When changing a row:

1. Request command execution through `SetLogCategoryVerbosity`.
2. If it fails, keep the previous UI/DataAsset state.
3. Query the runtime value again and show that result when available.
4. If it succeeds and the selected level differs from the detected default, write/update an override.
5. If it succeeds and matches default, remove any override.
6. Save the DataAsset when auto-save is enabled.

## DataAsset Contract

`ULogLevelDataAsset::LogLevelVerbosity` stores persistent overrides.

It should not be used as a complete database of all scanned categories. The scanner is responsible for discovery. The asset is responsible for user intent.

## Settings Contract

`ULogLevelEditor_Settings` stores:

- Scan scope preferences.
- Hide lists.
- Auto-save behavior.
- DataAsset reference.

Temporary hide settings are transient by design.

## Important Implementation Comments

The code should explain the non-obvious decisions:

- Why scan output is incremental.
- Why old scan generations are ignored.
- Why comments are stripped before macro detection.
- Why `Current` comes from Unreal runtime query output.
- Why runtime reads use read-only `Log list` snapshots.
- Why command success gates UI and DataAsset writes.
- Why default-matching entries are removed from the DataAsset.
- Why startup replay uses ticker retries.

## Testing Notes

Existing automation tests compile with the plugin build and cover verbosity mapping, runtime-output parsing, scanner macro coverage, scan-generation filtering, command registration, settings viewer integration, tab spawner behavior, and saved-override reapply decisions. Useful areas to expand:

- Comment-stripping edge cases.
- Default level extraction.
- DataAsset override add/update/remove rules.
- Startup replay failure and retry behavior.

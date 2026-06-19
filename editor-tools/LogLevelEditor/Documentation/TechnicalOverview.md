# Technical Overview

This page documents how LogLevelEditor is structured internally.

## Module

The plugin module is `FLogLevelEditorModule`.

Responsibilities:

- Register commands.
- Register menu and toolbar entries.
- Register the settings object.
- Open the Slate UI.
- Apply saved verbosity overrides after editor startup.

The module is editor-only and should not be required by packaged games.

## Main Components

| Component | Responsibility |
| --- | --- |
| `FLogLevelEditorModule` | Editor integration, startup replay, and tab creation. |
| `SLogLevelEditorWidget` | Slate dashboard for listing, filtering, hiding, and changing categories. |
| `FLogChannelScanner` | Background source scanner for Unreal log category declarations. |
| `LogLevelEditor::Verbosity` helpers | Shared mapping between int values, Unreal verbosity names, and console commands. |
| `ULogLevelEditor_Settings` | Config-backed scan and persistence settings. |
| `ULogLevelDataAsset` | Asset-backed persistent verbosity override list. |

## Scan Flow

The scanner:

1. Builds a list of source files from project and plugin paths.
2. Optionally adds engine plugin/source paths.
3. Processes `.h`, `.hpp`, `.cpp`, and `.inl` files.
4. Strips comments before matching macros.
5. Detects common Unreal log category macros.
6. Queues discovered categories for the UI.

Recognized macro families include:

- `DECLARE_LOG_CATEGORY_EXTERN`
- `DECLARE_LOG_CATEGORY_CLASS`
- `DEFINE_LOG_CATEGORY`
- `DEFINE_LOG_CATEGORY_STATIC`

The scanner uses a generation counter so stale worker output from an older scan cannot pollute a newer scan.

## UI Update Flow

The widget consumes scanner output incrementally. This keeps the editor responsive while large projects are scanned.

The visible list is filtered by:

- Search text.
- Permanent hidden channel list.
- Temporary hidden channel list.
- Current scan scope.

For each discovered category, the widget queries Unreal's current runtime verbosity before populating the `Current` label. Runtime reads use Unreal's read-only `Log list` output, not the mutating `Log [cat]` toggle command. If no runtime state can be queried, the row shows `Unavailable` instead of falling back to a guessed default.

After the source scan finishes, the widget keeps a lightweight active timer and periodically captures one runtime verbosity snapshot for all discovered rows. This keeps external console changes visible without re-running the source scanner.

When a discovered category has a saved DataAsset override, the widget re-applies that override only when Unreal has no current value or the current value differs. The row is then updated from the runtime query again, so the displayed value reflects the engine state after any intentional reapply.

## Verbosity Apply Flow

When the user changes a row:

1. The selected value is converted to a canonical Unreal verbosity string.
2. The plugin builds a console command.
3. The command is executed through the engine.
4. The UI is updated only if command execution succeeds.
5. The DataAsset is updated only when a persistent override is needed.
6. If the selected value equals the detected default, the override is removed.

This avoids a common UI bug where the list displays a value that was never accepted by Unreal.

## Startup Replay Flow

At startup the module loads valid entries from the configured DataAsset into a pending replay queue and tries to apply each saved verbosity value independently.

Because Unreal can register editor modules before `GEngine` can process console commands, replay is retried through `FTSTicker`. Successfully applied entries are removed from the pending queue, invalid entries are skipped, and entries for categories that are not registered yet can keep retrying until the attempt limit is reached.

## Data Model

`FLogLevelWidgetData` contains:

- `Name`: category name.
- `LogLevel`: integer verbosity value.

Integer values map to Unreal verbosity:

```text
0 NoLogging
1 Fatal
2 Error
3 Warning
4 Display
5 Log
6 Verbose
7 VeryVerbose
```

## Persistence Rules

The DataAsset represents overrides, not a full scan cache.

Important behavior:

- Default-matching values are not kept as overrides.
- Temporary hide settings are transient.
- Auto-save can be enabled to persist DataAsset changes immediately.

## Failure Handling

The plugin logs failures when:

- The DataAsset cannot be loaded.
- A console command cannot be executed.
- Startup replay happens too early and must be retried.
- A runtime verbosity query cannot be resolved for a row.
- A scanned category has no valid verbosity mapping.

## Extension Points

Useful future extension points:

- Add export/import of presets.
- Add a commandlet for support-log setup.
- Add named profiles in the DataAsset.
- Add test fixtures for scanner macro parsing.
- Add UI badges for source scope and override source.

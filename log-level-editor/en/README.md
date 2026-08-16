<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/LogLevelEditor/architecture.md -->
# LogLevelEditor Documentation

LogLevelEditor is an Unreal Engine editor plugin for discovering log categories and changing their verbosity from a focused editor dashboard. It helps teams reduce noisy logs during daily work, temporarily raise diagnostic channels while debugging, and persist intentional overrides in a DataAsset.

Core actions are **Scan**, **Set Verbosity**, and **Hide Category**.

This folder contains the complete documentation delivered with the plugin.

## Start Here

- [BUYER_GUIDE.md](BUYER_GUIDE.md): buyer-friendly overview, fit, and practical value.
- [UserManual.md](UserManual.md): complete editor workflow from setup to applying overrides.
- [FAQ.md](FAQ.md): Fab-ready buyer questions and answers.

## Reference

- [SettingsReference.md](SettingsReference.md): every setting, default behavior, and recommended baseline.
- [TechnicalOverview.md](TechnicalOverview.md): maintainer-level architecture and runtime behavior.
- [CodeDocumentation.md](CodeDocumentation.md): source layout, code contracts, and extension points.
- [Troubleshooting.md](Troubleshooting.md): common problems and fixes.
- [ReleaseChecklist.md](ReleaseChecklist.md): validation steps before shipping a Fab update.

## Included Assets

- `../Readme.pdf`: legacy packaged readme.
- `../LogLevelEditor_Changelog.txt`: release notes.
- `../Content/DA_LogLevelVerbosity.uasset`: default DataAsset used for persistent verbosity overrides.
- `../Content/Map_Tutorial_LogLevelEditor.umap`: tutorial/demo content.

## Quick Workflow

1. Enable the plugin and restart the editor when prompted.
2. Open the Log Level Editor tab from **Tools → Log Tools → Log Level Editor** or the optional toolbar shortcut.
3. Let the scanner discover project and plugin log categories.
4. Use search and hide settings to focus on the channels that matter.
5. Change a category verbosity from the row's verbosity buttons.
6. Persist overrides in the configured `ULogLevelDataAsset` when the change is intentional.
7. Reset a category to its detected default by selecting the detected default value again.

## What The Tool Changes

The plugin applies Unreal console commands in the form:

```text
Log <CategoryName> <VerbosityName>
```

It does not modify the source declaration of a log category. Persistent changes are stored in the configured DataAsset and replayed by the editor module after the engine is ready to accept console commands.

## Supported Verbosity Names

The shared verbosity helper supports Unreal's standard log levels:

- `NoLogging`
- `Fatal`
- `Error`
- `Warning`
- `Display`
- `Log`
- `Verbose`
- `VeryVerbose`

The editor intentionally uses the same names shown by Unreal log configuration so users can map UI changes to console command behavior.

## Safety Model

LogLevelEditor avoids silently lying to the user:

- The `Current` label is populated from Unreal's runtime state when the category can be queried.
- UI state is updated only after a console command succeeds.
- Persistent overrides are removed when the selected value matches the detected default.
- Temporary hide settings remain transient and are not written to config.
- Saved overrides are applied with per-category retry logic during startup because the editor is not always ready for console commands at module startup.

## Typical Uses

- Reduce spam from a noisy plugin while keeping the plugin enabled.
- Temporarily raise a gameplay, build, asset, or editor subsystem to `Verbose`.
- Restore clean defaults after investigating an issue.
- Share a team DataAsset with intentional project-wide verbosity overrides.
- Keep engine and project categories separated by settings so scans remain fast and relevant.

## Important Limitations

- Log categories must exist in source or already be registered by runtime/editor modules.
- Source scanning can only infer defaults from common Unreal macros.
- Runtime code can still change verbosity after the editor applies saved overrides.
- Shipping builds are not affected by this editor plugin.

## Legal Note

LogLevelEditor is an editor productivity tool. It does not change Unreal Engine logging semantics, engine source, or project licensing terms.

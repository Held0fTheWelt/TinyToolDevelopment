<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/LogLevelEditor/architecture.md -->
# Quick Start

This guide takes you from install to a **real result**: a log category's verbosity changed and saved
as a persistent override that survives editor restarts. Log Level Editor works on its own — no other
plugin is required.

## What You'll Have After This Guide

The tool open with your project's log categories listed, one category's verbosity changed, and that
override persisted in the plugin DataAsset.

## Requirements

- Unreal Engine 5 editor.
- No third-party software, account, or runtime. See [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md).

## 1. Install And Enable

1. Add **LogLevelEditor** from your Fab library to the project (or install to the engine).
2. Open **Edit → Plugins**, enable **LogLevelEditor**, and restart when asked.

## 2. Open The Tool (First Result)

1. Open **Tools → Log Tools → Log Level Editor**. A dockable tab opens and scans your project (and
   project-plugin) source for log categories.
2. Each row shows the **category name** (e.g. `LogTemp`), its **detected default**, the **current
   level**, and the **source path** when available.

You now see every discovered log category and its live verbosity.

## 3. A Real Worked Example: Change A Category's Verbosity

1. Use the search box to find `LogTemp`.
2. Click the **Warning** verbosity button on that row.

**Expected output:** the plugin runs the matching Unreal console command, the row updates to
`Warning`, and the change is written as a persistent override in the plugin DataAsset (so it is
replayed on the next editor startup).

3. To undo: select the row's **detected default** verbosity. When the selected value matches the
   detected default, the plugin removes the persistent override automatically, keeping the DataAsset
   focused on real overrides.

## 4. Where Overrides Live

Persistent overrides are stored in the configured `ULogLevelDataAsset` (set via
**LogLevelDataAsset** in settings). Saved overrides are replayed during editor startup once the
engine can accept console commands.

## 5. Settings

Open the plugin settings (Project/Editor settings → Log Level Editor) to control:

- `LogLevelDataAsset`, `bAutoSaveLogLevelDataAsset`
- `bShowToolbarButton`
- `bAlsoListEnginePluginChannels`, `bAlsoListEngineSourceChannels` (engine scans are expensive)
- `LogChannelsToHide`, `LogChannelsToHideTemporary`

See [SettingsReference.md](SettingsReference.md).

## 6. Next Steps

- Full workflow (persistent vs temporary hides, team workflow, startup apply):
  [UserManual.md](UserManual.md).
- Problems: [Troubleshooting.md](Troubleshooting.md) and [FAQ.md](FAQ.md).

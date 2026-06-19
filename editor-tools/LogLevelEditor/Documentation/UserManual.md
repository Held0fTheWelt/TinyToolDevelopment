# User Manual

This manual explains the day-to-day editor workflow for LogLevelEditor.

## Installation

1. Add the plugin to your project's `Plugins` folder or install it through Fab.
2. Enable **LogLevelEditor** in **Edit > Plugins**.
3. Restart the editor if Unreal asks for a restart.
4. Confirm that the plugin content is visible if you want to inspect the default DataAsset.

## Opening The Tool

Open LogLevelEditor from **Tools → Log Tools → Log Level Editor** or the optional toolbar shortcut. The plugin opens as a dockable editor tab so it stays with the rest of the editor workspace.

## First Scan

When the tool opens, it scans configured locations for log categories.

By default it focuses on:

- Project source files.
- Project plugin source files.

Optional settings can include:

- Engine plugin source files.
- Engine source files.

Engine scans can be expensive. Enable them only when you really need engine categories in the dashboard.

## Reading The List

Each row represents one log category.

Important fields:

- Category name: the Unreal log category name, for example `LogTemp`.
- Detected default: the default verbosity inferred from the declaration/definition macro when possible.
- Current level: the verbosity Unreal currently reports for the registered category. If Unreal cannot report it yet, the row shows `Unavailable`; in that case the preset control highlights the detected default as orientation. After the initial scan, this value is refreshed periodically from Unreal runtime state, so console changes made outside the widget can become visible without a manual rescan.
- Source path: where the scanner found the category, when available.

## Changing Verbosity

1. Find the category using search/filtering.
2. Choose a verbosity value from the row's verbosity buttons.
3. The plugin executes the Unreal console command.
4. The row and DataAsset are updated only when command execution succeeds.

Common choices:

- `Warning`: reduce noise while keeping important issues.
- `Log`: common default for normal output.
- `Verbose`: useful for diagnosis.
- `VeryVerbose`: very detailed output and usually temporary.
- `NoLogging`: silence a category as much as Unreal allows.

## Restoring Defaults

When the selected verbosity matches the detected default, the plugin removes the persistent override for that category. This keeps the DataAsset focused on real overrides instead of duplicating defaults.

If no default was detected, treat the row as informational and reset manually to the value your project expects.

## Persistent Overrides

Persistent values are stored in the configured `ULogLevelDataAsset`.

Recommended workflow:

1. Keep project-wide intentional overrides in the default DataAsset.
2. Let the asset be versioned only if those overrides are team policy.
3. Avoid saving temporary debugging noise into shared source control.
4. Use temporary hide settings for personal UI focus.

## Startup Apply

Saved overrides are replayed during editor startup. The module waits until the engine can accept console commands and retries a small number of times when startup is too early.

Replay is tracked per category: entries that apply successfully are cleared from the pending queue, while categories that are not registered yet can keep retrying without blocking already-applied overrides.

## Hiding Categories

Permanent hide list:

- Stored in config.
- Useful for categories that should rarely appear in the tool.

Temporary hide list:

- Stored transiently.
- Useful for local focus during one editor session.
- Not written to config.

## Settings

Open the plugin settings under the editor settings/project settings location registered by the plugin.

Key settings:

- `LogLevelDataAsset`: DataAsset used to store persistent overrides.
- `bAutoSaveLogLevelDataAsset`: save the asset automatically after intentional override changes.
- `bShowToolbarButton`: show or hide the Level Editor toolbar shortcut.
- `bAlsoListEnginePluginChannels`: include engine plugin categories in scans.
- `bAlsoListEngineSourceChannels`: include engine source categories in scans.
- `LogChannelsToHide`: permanent hidden categories.
- `LogChannelsToHideTemporary`: session-only hidden categories.

## Recommended Team Workflow

For team use:

1. Keep the default DataAsset in source control.
2. Save only stable project policy overrides.
3. Do not commit local temporary hides.
4. Document support/debug presets in your project wiki.
5. Use `Verbose` and `VeryVerbose` intentionally because they can produce large logs.

## Removing The Plugin

Before removing the plugin:

1. Reset any temporary log verbosity changes you care about.
2. Remove or ignore the plugin DataAsset if it is no longer used.
3. Disable the plugin and restart the editor.

The plugin does not modify log category source declarations, so removal does not require C++ cleanup.

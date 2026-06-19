# Changelog

All notable changes to this plugin will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/de/1.0.0/),
and this plugin adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

## [1.1.4] - 2026-06-16

### Added
- Added a UCM/MCP administration surface for describing tools, reading log-category state, executing scan/query/verbosity/hide actions, and listing/querying editor job history.
- Added a plugin-local `Config/UnrealCapabilityMesh` setup with capability, endpoint, route, schema, project-profile, and config-target manifests.
- Added editor-job history records for runtime verbosity changes, hide/unhide operations, and hidden-category clearing.

### Changed
- Exported selected classes via the module `*_API` macro so automation modules can link against them; no functional change to the shipped plugin.
- Added an exported `AreLogLevelEditorPluginCommandsRegistered()` helper used by the automation test module to verify command registration.
- Widened the permanent-hide column and clarified the **Hide permanently** action label in the category table.

## [1.1.3] - 2026-06-10

### Changed
- Bumped patch version as part of release housekeeping.
- Updated execute-side metadata alignment for MCP-capable tools where applicable.

## [1.1.2] - 2026-06-08

### Changed
- Replaced the verbosity Set buttons with stable toggle presets and highlighted the detected default when Unreal runtime state is not available yet.
- Moved the toolbar shortcut out of the mode toolbar into the later Level Editor user toolbar area and added a setting to hide it.
- Updated plugin release metadata to version `1.1.2`.

## [1.1.1] - 2026-06-01

### Added
- Added automation coverage for read-only runtime query construction, runtime verbosity parsing, snapshot parsing, saved-reapply decisions, command registration, tab-spawner registration, and stale scanner generations.
- Added this changelog to track release history.

### Changed
- Hardened settings module loading so the settings panel opens reliably from the editor widget.
- Populates row Current values from Unreal's queried runtime verbosity through read-only log list output instead of guessing from defaults or saved DataAsset values.
- Periodically refreshes displayed Current values after scanning so external console changes become visible without a manual rescan.
- Reworked the row layout into a compact tab-focused dashboard with readable status fields, shortened source paths, wrapped verbosity controls, and shorter hide actions.
- Re-applies saved DataAsset overrides when categories are discovered in the UI, then refreshes displayed state from Unreal runtime output.
- Changed startup replay to track saved overrides per category, so invalid or unavailable entries no longer block already-applied entries.
- Wired the settings command through the module command list, command-backed menu and toolbar entries, and the widget settings button.
- Aligned documentation wording with the current row-based verbosity buttons.
- Updated documentation to describe the reopened-window behavior.

### Fixed
- Added the missing Settings module dependency for the editor module.
- Fixed an issue where reopening the Log Level Editor window could show an empty list of log categories.
- Reused and focused an existing window instance instead of spawning a second broken window instance.

### Removed
- Removed the standalone Log Level Editor window command; menu and toolbar entry now open the dockable tab.

## [1.1.0] - 2025-11-21

### Added
- Added asynchronous scanning for large projects and engine codebases.
- Added support for scanning project source, project plugin source, engine plugins, and engine source code.
- Added permanent hidden channels that remain hidden across sessions.
- Added live scanning status updates.

### Changed
- Generalized and hardened how saved log categories and their verbosity levels are applied at startup.
- Updated documentation for async scanning, hidden channels, and setup workflows.

## [1.0.0] - 2025-11-17

### Added
- Added synchronous scanning for log categories in project source and project plugin source.
- Added persistent per-category log verbosity storage in a dedicated data asset.
- Added temporarily hidden channels for decluttering the list during a session.
- Added the first Log Level Editor UI for reviewing categories and adjusting verbosity levels.


# Changelog

All notable changes to this plugin will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/de/1.0.0/),
and this plugin adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

## [1.1.2] - 2026-06-16

### Added
- Added a UCM/MCP administration surface for describing tools, reading preset/scalability state, applying/restoring presets, and listing/querying editor job history.
- Added a plugin-local `Config/UnrealCapabilityMesh` setup with capability, endpoint, route, schema, project-profile, and config-target manifests.
- Added editor-job history records for preset apply and restore operations.
- Added automation linkage for the PerformancePresetWizard MCP job endpoint contract.

### Fixed
- Included the concrete storage-provider header in the MCP bridge so runtime settings using `TSubclassOf<UPerformancePresetStorageProvider>` compile reliably from automation modules.

## [1.1.1] - 2026-06-10

### Changed
- Bumped patch version as part of release housekeeping.
- Updated execute-side metadata alignment for MCP-capable tools where applicable.

## [1.1.0] - 2026-06-07

### Added
- Split the plugin into a runtime module and an editor module while keeping preset asset class paths stable.
- Added `UPerformancePresetRuntimeSubsystem` for manual runtime apply, restore, active preset lookup, backup history, and custom storage providers.
- Added persisted runtime backup history with a configurable limit and newest-first undo-stack restore behavior.
- Added a default GameUserSettings ini-backed storage provider.
- Added a simple `UPerformancePresetRuntimeSelectorWidget` for project menus and development builds.

### Changed
- Updated product wording from editor-only performance profiles to runtime target presets authored and reviewed in the editor.
- Moved Slate wizard, menus, detail customization, asset registry scan, and editor startup preset behavior into `PerformancePresetWizardEditor`.
- Exported the low-level `PerformancePreset` apply/restore API for cross-module use.

## [1.0.1] - 2026-06-01

### Changed
- Updated the plugin metadata and packaged changelog baseline for the current maintenance release.

## [1.0.0] - 2025-11-24

### Added
- Added the Performance Preset Wizard editor tab for managing and applying performance profiles.
- Added `UPerformancePresetAsset` data assets to store scalability settings and CVar overrides.
- Added detail customization for presets with Low, Medium, High, Epic, and Cinematic quality-level dropdowns.
- Added scalability coverage for Global Illumination, Reflections, Shading, and Landscape.
- Added a bulk CVar editor with import and export via plain text in the Details panel.
- Added CVar parsing feedback for malformed, missing, and editor-only overrides.
- Added Restore Previous support for scalability state and CVar values captured before the latest preset apply.
- Added an Editor startup preset option to automatically apply a selected preset when the editor launches.
- Added sorting and filtering of presets by target platform and display name in the wizard UI.
- Added logging and feedback when applying presets and startup configuration changes.
- Added Markdown documentation, diagrams, troubleshooting, code documentation, and a release checklist.


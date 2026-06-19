# Changelog

All notable changes to this plugin will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/de/1.0.0/),
and this plugin adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

## [1.0.3] - 2026-06-16

### Added
- Added a UCM/MCP administration surface for describing tools, reading active editor-lightweight state, executing mode/profile changes, and listing/querying editor job history.
- Added a plugin-local `Config/UnrealCapabilityMesh` setup with capability, endpoint, route, schema, project-profile, and config-target manifests.
- Added editor-job history records for mutating mode, profile, startup, and refresh operations.

### Changed
- Exported selected classes via the module `*_API` macro so automation modules can link against them; no functional change to the shipped plugin.

## [1.0.2] - 2026-06-10

### Changed
- Bumped patch version as part of release housekeeping.
- Updated execute-side metadata alignment for MCP-capable tools where applicable.

## [1.0.1] - 2026-06-01

### Changed
- Updated the plugin metadata and packaged changelog baseline for the current maintenance release.

## [1.0.0] - 2025-11-24

### Added
- Added the Lightweight Editor Mode dockable editor tab for quickly toggling a performance-friendly editor configuration.
- Added `ULightweightEditorModeSettings` with Mild, Balanced, Aggressive, and Extreme profiles.
- Added safe scalability and CVar backup and restore for rendering options such as Lumen GI, reflections, virtual shadows, volumetric fog, and fog.
- Added viewport management that can force Unlit view mode and disable realtime rendering while the mode is active.
- Added a persistent fallback view mode for restoring layouts after editor restarts.
- Added an Enable on Editor startup option that applies the selected profile when the editor launches.
- Added a Project Settings panel under Plugins > Lightweight Editor Mode.
- Added structured logging for applied changes, restored values, and viewport adjustments.
- Added documentation for user workflows, settings, technical behavior, troubleshooting, tuning, QA, packaging, and release checks.


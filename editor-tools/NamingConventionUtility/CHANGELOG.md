# Changelog

All notable changes to this plugin will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/de/1.0.0/),
and this plugin adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

## [1.0.3] - 2026-06-16

### Added
- Added a UCM/MCP administration surface for describing tools, reading state, executing naming actions, and listing/querying editor job history.
- Added a plugin-local `Config/UnrealCapabilityMesh` setup with capability, endpoint, route, schema, project-profile, and config-target manifests.
- Added editor-job history records for preview/apply folder runs, DataTable conversion, default convention population, and convention clearing.

### Changed
- Exported selected classes via the module `*_API` macro so automation modules can link against them; no functional change to the shipped plugin.

## [1.0.2] - 2026-06-10

### Changed
- Bumped patch version as part of release housekeeping.
- Updated execute-side metadata alignment for MCP-capable tools where applicable.

## [1.0.1] - 2026-06-01

### Added
- Added Content Browser folder actions for applying naming conventions to selected asset folders.
- Added DataAsset-driven naming rules with default Unreal naming families for textures, materials, meshes, Blueprints, widgets, effects, data, and curves.
- Added rename plan generation, preview, validation, skip reasons, and confirmation before applying changes.
- Added texture subtype detection based on compression settings and name tokens.
- Added DataTable and CSV/JSON reference assets for configuring convention data.
- Added documentation for user workflows, settings, technical behavior, troubleshooting, and release checks.

### Changed
- Hardened the safety model around invalid names, missing rules, duplicate targets, existing packages, overlapping folder selections, and unsupported asset types.

## [1.0.0] - 2025-11-17

### Added
- Added the initial Naming Convention Utility editor plugin for enforcing asset naming standards.


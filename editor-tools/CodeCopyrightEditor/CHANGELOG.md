# Changelog

All notable changes to this plugin will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/de/1.0.0/),
and this plugin adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

## [1.0.2] - 2026-06-16

### Added
- Added a UCM/MCP administration surface for describing tools, reading copyright settings/state, executing scan/apply/report operations, and listing/querying editor job history.
- Added a plugin-local `Config/UnrealCapabilityMesh` setup with capability, endpoint, route, schema, project-profile, and config-target manifests.
- Added editor-job history records for codebase scans, codebase/file apply operations, project notice updates, and compliance report writes.
- Added automation linkage for the CodeCopyrightEditor MCP job endpoint contract.

## [1.0.1] - 2026-06-10

### Changed
- Bumped patch version as part of release housekeeping.
- Updated execute-side metadata alignment for MCP-capable tools where applicable.

## [1.0.0] - 2026-05-31

### Added
- Added the Code Copyright Editor tab for configuring project and source-file notice templates.
- Added source scanning that classifies files before writing and exposes status, metadata, and preview information.
- Added selected-file rewrite actions for applying consistent copyright, license, owner, product, module, and file metadata.
- Added headless commandlet support for local checks and CI runs.
- Added JSON, SPDX-style, and REUSE-style report generation.
- Added PowerShell, shell, and GitHub Actions starter automation assets.
- Added documentation for editor use, template tokens, commandlet usage, reports, compliance, troubleshooting, and release checks.

### Security
- Kept ownership and license review explicit by preserving protected third-party notices unless the user selects an allowed rewrite path.


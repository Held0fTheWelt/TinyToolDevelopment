# Changelog

All notable changes to this plugin will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this plugin adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [1.1.2] - 2026-07-19

### Changed
- Reconciled the public documentation with the current standalone journal lifecycle and Unreal Engine 5.4-and-later compatibility floor.
- Clarified that imported evidence and provider output remain reviewable candidates until an explicit human promotion; external producers never gain journal-governance authority.

## [1.1.1] - 2026-07-12

### Added
- Imported rich APM/PIO envelope fields into practice candidates while preserving compact input, outcome, and content-packaging provenance.

### Changed
- Envelope imports prefer authored practice text and use deterministic generic text only when an optional field is absent.

### Fixed
- Enabled the guide-referenced promotion, repository-list, and practice-read routes and synchronized the BPJ Capability Mesh manifests.

## [1.1.0] - 2026-07-02

### Added
- Added the MCP-closable journal lifecycle with candidate import, approval-gated promotion, repository reads, honest evolution counts, and UBI/PIO provider inboxes.

## [1.0.0] - 2026-06-30

### Added
- Added `BPJCapabilityMeshEndpoints` and plugin-local `Config/UnrealCapabilityMesh` manifests for evidence gathering, candidate extraction, repository validation, artifact import, evolution-graph export, application-brief workflows, implementation-outcome import, and editor-job routes.
- Registered the BPJ route package in the project Capability Mesh profile and expanded automation coverage for the new endpoint surface.

### Changed
- Promoted descriptor `VersionName` from `0.1.0` to `1.0.0` and `Version` from `1` to `2` to mark the first stable release of the Current Implementation surface.
- Reconciled the product documentation and release metadata with the `1.0.0` descriptor state.

## [0.1.0] - 2026-06-16

### Added
- Added the initial Best Practices Journal runtime, editor, and developer-tool modules.
- Added practice, evidence, application-brief, review, integration-status, redaction, guardrail, schema-validation, import, export, and outcome data contracts.
- Added the editor evidence workflow, practice-candidate persistence, evidence-to-candidate extraction, structured artifact import, report redaction/boundary gate, and the completed workbench panel with ecosystem file-bridge support.
- Added editor access through the Best Practices Journal panel for project-local practice governance workflows.
- Added commandlet entry points for schema validation, artifact import, sample export, and repository validation workflows.
- Added project-local resource metadata and packaging filters for Tiny Tool Development governance plugins.

# Changelog

All notable changes to this plugin will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this plugin adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

## [1.0.0] - 2026-06-30

### Added
- Added `BPJCapabilityMeshEndpoints` and plugin-local `Config/UnrealCapabilityMesh` manifests for evidence gathering, candidate extraction, repository validation, artifact import, evolution-graph export, application-brief workflows, implementation-outcome import, and editor-job routes.
- Registered the BPJ route package in the project Capability Mesh profile and expanded automation coverage for the new endpoint surface.

### Changed
- Promoted descriptor `VersionName` from `0.1.0` to `1.0.0` and `Version` from `1` to `2` to mark the first stable release of the Current Implementation surface.
- Updated the SAD version reference and the internal Fab listing review file to the `1.0.0` descriptor state.

## [0.1.0] - 2026-06-16

### Added
- Added the initial Best Practices Journal runtime, editor, and developer-tool modules.
- Added practice, evidence, application-brief, review, integration-status, redaction, guardrail, schema-validation, import, export, and outcome data contracts.
- Added the editor evidence workflow, practice-candidate persistence, evidence-to-candidate extraction, structured artifact import, report redaction/boundary gate, and the completed workbench panel with ecosystem file-bridge support.
- Added editor access through the Best Practices Journal panel for project-local practice governance workflows.
- Added commandlet entry points for schema validation, artifact import, sample export, and repository validation workflows.
- Added project-local resource metadata and packaging filters for Tiny Tool Development governance plugins.

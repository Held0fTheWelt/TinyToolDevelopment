# Changelog

All notable changes to this plugin will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/de/1.0.0/),
and this plugin adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

## [1.1.2] - 2026-06-16

### Added
- Added `FAsyncSplineBuilderMcpInterface`, exposing spline-builder actions (actor create/list/read/rebuild/validate, live spline apply, point-list asset read, track-settings apply) through Capability Mesh MCP routes.

### Changed
- Updated `IRoadSplineInterface` Blueprint events to comply with ADR-EDT-0004 (`BlueprintNativeEvent` + `BlueprintCallable` pattern).
- Exported the editor `LandscapeDeformer` via the module `*_API` macro to support automation linkage.

## [1.1.1] - 2026-06-10

### Changed
- Bumped patch version as part of release housekeeping.
- Updated execute-side metadata alignment for MCP-capable tools where applicable.

## [1.1.0] - 2026-06-01

### Added
- Added the Async Spline Builder editor workflow panel with compact Build, Segments, and Terrain tabs.
- Added editor-only landscape height deformation and additive landscape layer painting when a paint layer is configured.
- Added automation coverage for high-risk spline generation, cleanup, async, and terrain workflows.
- Added expanded documentation for user workflows, landscape and wall behavior, automation, troubleshooting, and release QA.

### Changed
- Hardened async editor and runtime rebuild flows around configurable segment batching.
- Improved generated component cleanup so stale arrays and construction rebuilds are handled more reliably.
- Clarified the runtime/editor split between packaged spline generation and editor-only landscape tooling.

## [1.0.0] - 2025-11-17

### Added
- Added spline-based road, race-track, pipe, rail, wall, and side-object mesh generation.
- Added synchronous and asynchronous build paths for editor responsiveness.
- Added per-segment mesh planning, extra meshes, stunt gaps, drop regions, drop walls, and procedural ground walls.
- Added spline point save and load support through `USplinePointListAsset`.


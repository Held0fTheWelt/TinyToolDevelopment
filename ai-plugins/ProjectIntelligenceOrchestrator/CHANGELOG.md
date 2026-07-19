# Project Intelligence Orchestrator Changelog

## [1.0.5] - 2026-07-19

### Added

- Added the review-only translation-evidence lane to `pio.bp_to_cpp_port_blueprint.v1`: UBI deep export and in-memory compiler diagnostics flow through UII's source/target C++ and reflection bundle into UCI.

### Changed

- PIO explicitly binds the deep-export and compiler-diagnostic artifacts to UII, defaults the diagnostic route to `refresh_compilation:true`, and records translation-evidence availability in the run report.
- Workflow manifests can bind boolean route inputs after caller-provided JSON is assembled, making safety-critical node semantics immutable for that workflow execution.
- Reconciled the shipped product documentation with the `1.0.5` descriptor, the implemented workflow families, route-owner authority boundaries, and the Unreal Engine 5.4-and-later compatibility floor.

### Fixed

- The BPJ handoff contains only a reviewable Evidence Reference candidate; PIO neither extracts original sources nor promotes journal content.
- The content-packaging `verify_pins` node now always invokes the APM execute route with `verify_only:true`, while `execute_plan` always binds `verify_only:false`; caller input can no longer turn verification into mutation or execution into a verification-only no-op.

## [1.0.4] - 2026-07-18

### Added

- Added the deterministic `uge.composition.v1` contract, evidenced mirror skips, draft compilation, approval-gated execution, data-driven materialization, findings-bearing verification, variant comparison, and commandlet routes.

### Changed

- Added a distinct `dry_run:true` preflight that writes evidence without target transfer or wiring materialization.
- Required valid reviewed manifests, owner-held mutation routes, measured same-family with/without variants, and explicit degraded states for unavailable evidence.
- Established Unreal Engine 5.4 as the compatibility floor for the composition family.

### Fixed

- Aligned wiring requests with APM and UBI contracts, rejected empty-green verification, preserved content-only mirror evidence, and prevented preflight from mutating the target.

## [1.0.3] - 2026-07-12

### Added

- Added the machine-readable plugin guide, review-only content-packaging planning, approval-gated content-packaging execution, BPJ candidate transfer, IIS provenance, and optional LLM advice.

### Changed

- Allowed explicitly approval-gated workflow manifests while keeping mutating routes out of review-only workflows.

## [1.0.2] - 2026-07-02

### Added

- Added System Dossier, IIS import, BPJ provider handoff, target-root commandlet support, and cumulative artifact routing to the Blueprint-to-C++ workflow.

### Fixed

- Declared the required Unreal Capability Mesh plugin dependency and repaired commandlet discovery and headless route execution.

## [1.0.1] - 2026-06-21

### Added

- Added the initial deterministic runner, workflow validation, reconstructable journals, Blueprint-to-C++ Port Blueprint, Project Health Brief, handoffs, evidence evaluation, UCM route invoker, and commandlet.

### Fixed

- Repaired the Unreal Engine 5.4 version-ladder build for the initial plugin scaffold.

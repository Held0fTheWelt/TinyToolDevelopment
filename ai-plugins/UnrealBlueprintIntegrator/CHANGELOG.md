# Changelog

All notable changes to Unreal Blueprint Integrator are documented here.

## [1.2.4] - 2026-07-19

### Changed

- Added `ubi.translation.diagnostics.v1` to the machine-readable primary evidence workflow so agents capture compiler facts before UII correlation instead of inferring missing translation details by hand.
- Made UBI permission evaluation fail closed: unknown profiles, non-UBI routes, unsupported or missing required flags, and incomplete mutation policies are denied. Preview accepts only `ubi.mutation_preview` or the stronger `ubi.mutation_apply`; apply and rollback require `ubi.mutation_apply` together with `AllowAssetMutation` and `RequiresUserApproval`.
- Reconciled the shipped product documentation with the `1.2.4` descriptor, the standalone evidence and governed-mutation workflows, and the Unreal Engine 5.4-and-later compatibility floor.

## [1.2.3] - 2026-07-18

### Added

- Added `ubi.translation.diagnostics.v1`, a read-only UCM route that emits versioned, scoped Blueprint compiler status, counts, and tokenized messages.

### Changed

- `refresh_compilation:true` refreshes compilation in memory only; the route never saves a package or mutates Blueprint content.

## [1.2.2] - 2026-07-18

### Added

- Added governed `add_variable`, `set_cdo_property`, and `upsert_data_asset` mutation operations.
- Added target-project validation and backup or absence-marker based rollback.

### Fixed

- Added internal recovery after failed asset operations and fail-closed preview validation for unsupported or incompatible changes.
- Preserved Unreal Engine 5.4 compatibility while supporting UE 5.8 shared-string JSON storage.

## [1.2.1] - 2026-07-12

### Added

- Added the machine-readable plugin guide for agent orientation.

## [1.2.0] - 2026-07-02

### Changed

- Aggregated ubiquitous BPJ findings into a project-level candidate and added target-root aliases for scoped scans and exports.

### Fixed

- Added explicit failure text for unavailable subsystems and unreadable or unwritable artifacts.

## [1.1.1] - 2026-07-01

### Added

- Added construction-script and nested AnimBlueprint graph traversal with stable graph identity and live editor coverage.

### Changed

- Removed stale blanket incomplete reasons for supported construction and animation graph bodies.

## [1.1.0] - 2026-07-01

### Added

- Added structured deterministic classifier claims, confidence policy, graph scan helpers, and the versioned classifier vocabulary.

### Changed

- Added claims to analysis fingerprints and upgraded reports and neutral BPJ candidates to the 1.1.0 analysis schema.

## [1.0.0] - 2026-06-30

### Added

- Added deterministic deep graph export, evidence indexing, reports, neutral BPJ candidates, comparisons, UCM routing, permission profiles, JSONL audit, and preview/apply/rollback safety.

### Changed

- Promoted the descriptor to the stable `1.0.0` release line and reconciled the package documentation with the implemented evidence and mutation surface.

## [0.2.0] - 2026-06-21

### Added

- Added the deterministic export-core facade, local analysis core, scoped output directories, mounted-content evidence, stable record fingerprints, and route-vocabulary ownership guard.

## [0.1.0] - 2026-06-20

### Added

- Added Blueprint inventory scanning, the deterministic `ubi.export` envelope, Asset Registry evidence, configurable roots, and project-local output.

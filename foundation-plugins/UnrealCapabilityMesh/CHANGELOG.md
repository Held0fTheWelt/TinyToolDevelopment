# Changelog

All notable changes to this plugin will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/de/1.0.0/),
and this plugin adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

### Added
- Documented the TTER route-projection boundary: UCM routes are discoverable as projected TTER tools without product changes.

### Changed
- Kept UCM as the sole route-planning, rules, approval, dry-run, transform, and execution authority. TTER projected-route invocation delegates to `FCapabilityMeshService::ExecuteRoute` rather than invoking endpoints or products directly.
- Defined the lifecycle split for later slices: TTER owns invocation records, progress, cancellation, and rich results while UCM continues to own route governance and execution reports.
- Documented the effective setup-root model: UCM merges its bundled profile, plugin-local profiles from enabled provider plugins, and an optional project override.
- Clarified that a project-local setup copy is only required when the project intentionally overrides or composes provider-owned manifests.
- The optional Tiny Tool Execution Integration Bridge reloads UCM setup before TTER discovery so plugin-local routes are projected at editor startup.
- UCM functionality targets Unreal Engine 5.4 and later.

### Fixed
- Kept runtime and game targets free of editor-only DataTable serialization APIs while preserving the editor administration path behind compile-time guards.
- Preserved `CanContainContent: true` on later engine branches so packaged editor content and administration assets remain supported.

## [1.0.6] - 2026-07-12

### Added
- Added the Capability Mesh Agent Orientation surface with read-only routes for `capability_mesh.orientation.welcome.v1`, `capability_mesh.plugin_guides.list.v1`, `capability_mesh.plugin_guide.read.v1`, and `capability_mesh.route_warnings.analyze.v1`.
- Added plugin-guide discovery for `capability_mesh.plugin_guide.v1` manifests, including buyer docs, agent docs, workflow route references, route-rule references, and guide/document drift warnings.
- Added a Route Health overview in the UCM control panel showing `Group / Enabled / Loadable / Missing / Warnings / Guide` for enabled route manifests.
- Added the `UCMRoute` commandlet for headless setup reload, route listing, dry-run, execution, endpoint invocation, and experimental self-approval configuration, with JSON file/stdout responses and explicit provider-module loading.

### Changed
- Missing enabled route manifests now produce `enabled_route_manifest_missing` warnings instead of generic route-load errors.
- Updated bundled/project UCM profiles with the orientation manifests and current APM route names.
- Reduced the project override profile to root-owned APM and cross-plugin composite routes, leaving plugin-local profiles as the source of truth for plugin-owned routes.
- Disabled the project-level experimental all-route self-approval override in the default profile so route health reports no longer carry the self-approval warning by default.
- Allowed the approval-gated `apm.content_packaging.execute_plan.v1` route through the default project-mutation deny rule's explicit exception list.

### Fixed
- Synchronized the central Best Practices Journal UCM manifests with the plugin-local BPJ setup so guide-referenced BPJ routes can be loaded and cataloged.
- Removed obsolete active sample route/provider registration from the bundled default profile.
- Repaired unloadable-route warnings caused by duplicate project-level copies of plugin-owned manifests overriding plugin-local route definitions.
- Added live setup coverage for Asset Loader Studio and Geo Provider Store plugin profiles so their guide workflow dependencies resolve during MCP route warning analysis.

## [1.0.5] - 2026-06-17

### Added
- Added plugin-local `Config/UnrealCapabilityMesh` manifests for Best Practices Journal, Procedural Generated Structures, Smart Content Diet, Internal Index Service, LLM Store, Project Restructure Service, Unified MCP Server, and Unreal Integration Intelligence, including expanded project and bundled capability/endpoint/route/schema profiles.
- Added `ProceduralGeneratedStructuresCapabilityMeshEndpoints` and PGS actor/data-asset read, rebuild preview/apply, validate, and async-status routes.

### Changed
- Route MCP annotations now expose `x-ucm-has_mutating_side_effects` and `x-ucm-has_open_world_side_effects` separately from client approval gating, and experimental self-approval bypass semantics no longer require the dry-run plan to be allowed before taking effect.

### Fixed
- Clarified experimental self-approval bypass naming and descriptions so approval-gated routes report accurate effective approval requirements when EXPERIMENTAL self automatic approval is enabled.

## [1.0.4] - 2026-06-16

### Added
- Added UCM capability, endpoint, and route manifests for NamingConventionUtility, LightweightEditorMode, PerformancePresetWizard, CodeCopyrightEditor, and LogLevelEditor editor-job listing/status.
- Added plugin-local `Config/UnrealCapabilityMesh` roots for those five governance tools, including describe/read/execute routes, job routes, schemas, project profiles, and config-target declarations.
- Added editor job UCM routes for IIS, SCD, LLMStore, and UMCP (`*.editor.jobs.list.v1`, `*.editor.jobs.status.v1`) with shared `editor_jobs_schemas.json`, capability/endpoint manifests, and project-profile registration.
- Added AsyncSplineBuilder MCP routes — actor create/list/read/rebuild/validate, live spline apply, point-list asset read, and track-settings apply — with matching schemas and capability/endpoint definitions.

### Changed
- Refreshed project and bundled UCM profiles so the governance tools are available through both project-level and plugin-local discovery contexts.
- Refreshed the bundled capability config, default rules, and project profile.

### Fixed
- Corrected MCP route resolution and execution wiring across the gateway subsystem, route executor, and rule engine.

## [1.0.3] - 2026-06-13

### Added
- Route Catalog on the Routes page: plugin-grouped scrollable table with expand/collapse, route detail rows, and a dedicated approval column for **EXPERIMENTAL** self automatic approval.
- **Approve all at own risk** global switch in the Route Catalog column header; per-plugin and per-route toggles for approval-gated routes; `n/a` with tooltips for routes that do not require approval.

### Changed
- Removed the separate **Experimental Self Automatic Approval** section from the Routes page; controls now live in the Route Catalog approval column.
- Status banner, route-result messages, and approval tooltips describe concrete risks (asset mutation, project mutation, config writes, skipped confirmation prompts) instead of generic own-risk language.
- Editor branding uses **Unreal Capability Mesh** consistently in the Tools menu and control panel title.

## [1.0.2] - 2026-06-10

### Changed
- Bumped patch version as part of release housekeeping.
- Updated execute-side metadata alignment for MCP-capable tools where applicable.

## [1.0.1] - 2026-06-09

### Added
- Added full Fab-ready documentation set covering buyer scope, quick start, user manual, manifest reference, C++ code map, integration points, troubleshooting, and release review.
- Added explicit publisher and intended publication year headers to UCM source files, build scripts, and the Capability Mesh gate script.
- Added Fab technical information and third-party software notes for review packaging.

### Changed
- Updated `Config/FilterPlugin.ini` to list all extra packaged files and folders outside the default BuildPlugin structure: `Config`, `Documentation`, `README.md`, `CHANGELOG.md`, and `TestFixtures`.
- Confirmed all UCM modules use C++20 build settings for UE 5.6 compatibility while retaining UE 5.4 as the minimum supported engine version.

## [1.0.0] - 2026-06-08

### Added
- Added setup-driven capability discovery through JSON manifests.
- Added runtime registries for capabilities, endpoints, schemas, routes, transforms, rules, and adapters.
- Added rule-based route dry-run planning with side-effect policy evaluation.
- Added generic invocation routing for reflection, file contract, and modular feature endpoint modes.
- Added local diagnostics under `Saved/UnrealCapabilityMesh`.
- Added editor control panel for reload, discovery, diagnostics, route dry runs, and adapter creation.
- Added developer automation fixtures and anti-hardcoding validation gate.


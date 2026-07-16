# Changelog

All notable changes to this plugin will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/de/1.0.0/),
and this plugin adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

### Fixed
- Kept BuildPlugin-generated precompile metadata in packaged output so an installed Unreal Engine can load the precompiled Smart Content Diet modules.
- Clarified that Smart Content Diet functionality targets Unreal Engine 5.4 and later; later engine branches contain compatibility adjustments rather than separate product behavior.

## [1.0.5] - 2026-07-12

### Added
- Added agent-orientation plugin guide (capability_mesh.plugin_guide.v1).
- Added plugin-local `Config/UnrealCapabilityMesh` manifests for the full SCD capability surface: scan, findings, health, governance, similarity, optimization, migration-advice, and editor-job routes with matching schemas and project profile registration.

## [1.0.4] - 2026-06-16

### Added
- Added a deterministic preset and fix-recipe core (`FSmartFixRecipe`, `FSmartRecipeSelection`) on top of the Safe Optimization Queue, with role-defaulted autonomy, built-in Run&Go recipes, project overrides, and analyzer/optimize-panel wiring.
- Added a pure tag-reading seam (`FSmartAssetTagReader`) for texture metadata.
- Added a per-asset metadata cache with timestamp/version invalidation.
- Added material-instance alpha analysis (`SCDMaterialAlpha`) and a duplicate-compare helper (`SCDDuplicateCompare`).
- Added an editor job-status contract, editor commands, tool-menu registration, and UCM editor job endpoints (`BuildEditorJobsListJson` / `BuildEditorJobStatusJson`) for the analyzer panel (part of the cross-plugin editor-UI job contract).

### Changed
- Asset scan now queries candidates once and compares tag-first, deep-loading only survivors; the read-only tag comparison stage runs in parallel.
- Texture duplicate detection now buckets its index and caches folder asset loads.
- Removed compile-time dependency on `UnifiedMcpServerInterface`; editor job history APIs renamed to `RecordJob` / `GetRecentJobs`.
- UMCP aggregated job lookups honor the configured max job history count instead of a fixed 500-entry scan.

### Fixed
- Hardened the asset-scan pipeline for correctness and performance (Plans 05/06): MI alpha detection, duplicate-index reuse, and the reduction early-out now align with fingerprint duplicate keys.
- Closed hardening gaps in the analyzer widget and settings.

### Removed
- Removed `FSCDUmcpJobStatusProvider` and `UnifiedMcpServerInterface` from the SmartContentDiet module build.

## [1.0.3] - 2026-06-11

### Added
- Expanded the Unreal Capability Mesh (UCM) surface from 1 to **12 dependency-free SCD capabilities**, each a read-only or approval-gated UCM route — no peer plugin is linked or required:
  - Provider (read-only): `scd.scan.run`, `scd.findings.get`, `scd.findings.explain`, `scd.health.snapshot`, `scd.health.evidence`, `scd.governance.snapshot`.
  - Similarity (read-only): `scd.similarity.groups` (surface computed groups) and `scd.similarity.ingest_groups` (accept externally-computed groups at a higher provider tier).
  - Optimization: `scd.optimize.preview_safe` (read-only); `scd.optimize.apply_safe` and `scd.optimize.apply_fix` (project/asset mutation, **UCM approval-gated** — `requires_user_approval: true`).
- Shared response envelope schema `smart_content_diet.capability_mesh_endpoint.v1` (`status` ok/degraded/error, `success`, `messages[]`, optional `mode`/`enrichment_hint`/`result`) so every capability degrades gracefully instead of failing hard.
- Example chained route `scd_ingest_from_iis.v1` (`iis.search.hybrid → scd.similarity.ingest_groups` via a schema transform) demonstrating cross-plugin routing **without** SCD declaring any IIS dependency; the route is simply unavailable when InternalIndexService is absent.

### Fixed
- Editor scan depth selection (Quick Safe / Full / Deep) is now wired through to `FSmartAnalysisOrchestrator` for every editor analyzer run (closes the known gap from 1.0.2): the governance/findings analysis honors the header depth selector and the status line names the depth used. Commandlet depth flags are unchanged.

### Changed
- Bumped patch version as part of release housekeeping.
- Updated execute-side metadata alignment for MCP-capable tools where applicable.
- Relocated automation tests out of the shipped plugin; the packaged plugin now ships docs only.
- `Config/FilterPlugin.ini`: removed PerformancePresetWizard leftovers and documented that no test sources are packaged.

## [1.0.2] - 2026-06-08

### Added
- Safe Optimization Queue product loop: **Optimize** shell tab, bucketed queue view model, Preview Safe / Apply Safe runner, and conservative destructive rejection.
- Before/after apply metrics via `FSmartOptimizationQueueDelta` with panel summary and JSON report under `Saved/SmartContentDiet/OptimizationQueue/<timestamp>/`.
- Header scan depth selector (Quick Safe / Full / Deep) with dynamic scan button label and depth hints.
- Safety badges on finding detail recommended actions; automatic re-scan after single-asset fix or Apply Safe.
- Commandlet flags `-ApplySafeQueue`, `-DeepScan`, and expanded `-OptimizationQueueReport` integration.
- Documentation: `Resources/OPTIMIZATION_QUEUE.md` and overhauled `Documentation/README.md`.

### Changed
- Beginner shell now includes Overview, Optimize, Findings, and Settings; Preset and Governance require advanced role/mode.
- Updated plugin release metadata to version `1.0.2`.

### Known gaps
- Editor scan depth selection is not yet fully wired to `FSmartAnalysisOrchestrator` on every scan; commandlet depth flags are authoritative for CI.

## [1.0.1] - 2026-06-04

First public ecosystem release cut: live health snapshot seam, role-tiered UI shell (overview, findings, preset, trend, governance, redundancy), similarity/redundancy slot with honest funnel states, read-only content-health evidence export, and `run_scd_gate.py` release validation.

### Added
- Added explicit own-risk safety notices across SmartContentDiet docs, editor UI, QuickFix confirmations, reduction dialogs, commandlet usage, and mutating API comments.
- Added editor-side Governance UI for Trend, Debt, Budget, Ownership, and Material Deep Scan workflows.
- Added `FSmartGovernanceViewModel` to connect current scan data with trend metrics, reduction debt, budget checks, ownership mappings, snapshots, and baselines.
- Added optional `FSmartDeepScanService` for compiled material shader statistics, including pixel/vertex instruction counts, texture sample counts, sampler usage, result caching, and analyzer findings.
- Added automation coverage for Governance settings persistence and Deep Scan disabled-state reporting.
- Added Texture Optimizer quick fixes for texture group assignment, data-texture sRGB correction, and large-texture streaming correction.
- Added Static Mesh Hygiene quick fixes for lightmap UV generation, lightmap resolution normalization, collision complexity simplification, material slot cleanup, LOD screen-size normalization, Nanite disable, and Nanite fallback optimization.
- Added FindingType-based QuickFix matching so actionable fixes no longer depend only on localized/user-facing message text.
- Added reviewed QuickFixes for redirector fixup, similar LOD cleanup, overlapping lightmap UV regeneration, mesh geometry cleanup, convex collision generation, semantic material graph simplification, exact duplicate texture/material-instance consolidation, animation data cleanup, and ORM mask-packing asset creation.
- Added reviewed follow-up QuickFixes for texture addressing normalization, texture mip-generation normalization, inappropriate virtual-texture streaming disable, static-mesh CPU-access disable, generated lightmap coordinate-index normalization, duplicate simple-collision primitive cleanup, and tiny static-mesh distance-field disable.
- Added reviewed extended QuickFixes for additional no-op material graph rewrites, material sampler-type normalization, texture build hygiene normalization, same-folder packed-mask material rewiring, lightmap build-settings repair, duplicate animation notify cleanup, strict duplicate static-mesh consolidation, static-mesh bounds/build-scale normalization, decorative collision removal, and governance review metadata creation.
- Added reviewed follow-up QuickFixes for material static/base-property override cleanup, dependency-aware alpha stripping, normal-map profile normalization, static/skeletal LOD hygiene, empty debug animation-curve cleanup, physics asset cleanup, sound-wave profile normalization, and Niagara budget metadata normalization.
- Extended conservative material semantic simplification with double `OneMinus`, double `Saturate`, and redundant `Clamp(Saturate(x), 0, 1)` rewrites.
- Added analyzer findings, dimension mappings, QuickFix catalog entries, UI apply mappings, reduction rules, governance labels, and automation coverage for the expanded QuickFix catalog.
- Added `FSmartAudienceContext` and `SSmartAudienceSelector` for settings-backed audience role and explanation depth (UI-A0).
- Added role-aware UI shell with health overview, findings table, explainability detail, preset weights, and trend regression panels (ECO-A3).
- Added `FSmartHealthSnapshotBuilder` and live `PushHealthSnapshotToSubsystem` wiring after governance analysis (ECO-A2).
- Added `SmartContentDietInterface` module with read-only similarity and content-health provider contracts.
- Added `Tools/scd_gate/run_scd_gate.py` release validation gate (autark BuildPlugin, automation, provider guardrails).

### Changed
- Material analysis now emits `HighInstructionCount` and `TooManyTextureSamples` only from measured Deep Scan stats, while heuristic material warnings remain `ExpensiveMaterialFeature`.
- Texture, geometry, LOD, UV, animation, material, cross-asset, and Nanite analyzers now emit more concrete optimization findings with matching reduction actions.
- Replaced legacy Scan/View/Settings/Governance tab switcher with role-aware shell tabs (Overview, Findings, Preset, Trend, Assets, Governance, Redundancy, Settings).

## [1.0.0] - 2026-06-01

### Added
- Added the SmartContentDiet editor plugin for scanning project assets and identifying optimization candidates.
- Added batched Asset Registry scanning with progress callbacks and cancellation.
- Added asset size, class, path, referencer count, map referencer count, and recommendation result models.
- Added recommendation categories for large assets, very large assets, unreferenced assets, and assets not referenced by maps.
- Added analyzer infrastructure for geometry, LOD, material, memory, Nanite, texture, UV, animation, cross-asset, and trend dimensions.
- Added reduction rules, quick fixes, preset composition, impact matrix, release gate, CI policy, result conversion, result view, and export support.
- Added editor widgets for analysis, reduction review, and main plugin workflow.
- Added commandlet and automation coverage for reduction engine behavior.


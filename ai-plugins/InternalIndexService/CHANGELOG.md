# Changelog

All notable changes to this plugin will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/de/1.0.0/),
and this plugin adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

### Fixed
- Kept BuildPlugin-generated precompile metadata in packaged output so an installed Unreal Engine can load the precompiled IIS modules.
- Clarified that IIS functionality targets Unreal Engine 5.4 and later; later engine branches contain compatibility adjustments rather than separate product behavior.

## [1.0.7] - 2026-07-12

### Added
- Added agent-orientation plugin guide (capability_mesh.plugin_guide.v1).

## [1.0.6] - 2026-07-02

### Added
- Inline canonical agent responses on `iis.agent.search.v1`, `iis.agent.get_context_pack.v1`, and `iis.agent.explain_blueprint.v1` (payload plus `response_path`).
- Index status truth fields: `catalog_exists`, `chunk_store_records`, and `vector_records` on `iis.index.status.v1`.

### Changed
- `iis.import.prepared_chunks.v1` now surfaces `import_report_path` on the route output.

## [1.0.5] - 2026-06-16

### Added
- Added plugin-local `Config/UnrealCapabilityMesh` manifests for agent search/context routes, diagnostics, index control, performance benchmark, import/rebuild/status routes, and editor-job listing with shared schemas and project-profile registration.
- Added runtime control surface: live observe, tune, and act over `FIISControlSurface` with transient-by-default tuning, master mutation gate (`bEnableRuntimeControlMutations`), `persist`/`reset`, live `efSearch`/int8-kernel re-apply hooks, opt-in recent-diagnostics ring buffer, index act-verbs, `UIISControlEndpoints` reflected JSON facade (one UFUNCTION per verb), typed `UIISSubsystem` control methods, and `iis.control.*` / `iis.perf.*` / `iis.index.*` console commands.
- Added performance self-check and benchmark budgets: shared `FIISPerfBench` core over a seeded synthetic HNSW corpus (warmup + median/p95) with workloads `WL_VectorSearch`, `WL_KernelRatio` (AVX2 absent reports n/a, not a failure), and `WL_IncrementalRatio`. Shipped `UIISSubsystem::RunPerfSelfCheck()` judges against steerable `Vector Index|Performance` settings and broadcasts `OnPerfSelfCheckDeviation` per breach. Automation can emit perf JSON with ratios and optional rolling baselines.
- Integrated a persistent vector index service with an incremental HNSW backend into the indexing pipeline, including module wiring and lifecycle management.
- Added a size-based vector backend router that automatically selects the JSONL brute-force or HNSW backend, configurable through `UIISSettings`/vector index developer settings.
- Added ISPC vector-math kernels (cosine/normalize) with a scalar double-precision fallback behind a build gate.
- Added vector index partitioning by provider/model/dimension/route so embeddings from different routes no longer collide.
- Added a SQLite-backed embedding job store and queue persistence so embedding jobs survive editor restarts, plus async cancellation support.
- Added UCM editor job endpoints (`UIISEditorJobsEndpoints`) with routes `iis.editor.jobs.list.v1` and `iis.editor.jobs.status.v1`, merging panel job history with recent SQLite embedding-job rows.
- Added `IModularFeatures`-based embedding executor discovery (`FIISEmbeddingDiscovery`) as the primary executor seam, decoupling IIS from a hard LLM Store dependency.
- Added a shared editor job-status contract, editor commands, panel view model, and tool-menu registration for the Control Panel (part of the cross-plugin editor-UI job contract).
- Added a configurable HNSW vector storage policy: int8 scalar quantization with per-vector scale remains the compact default, Float32 is available for high-fidelity/debug runs, and the recall-risk global-scale int8 mode is gated behind an experimental setting. Manifest format versions detect incompatible persisted layouts and rebuild them by default.
- Added `EmbeddingExecutorId` to IIS settings so optional bridge plugins can select a registered embedding executor at runtime. Empty keeps IIS on normal executor discovery; the IIS LLM Store Bridge sets this value to `llmstore` while loaded.
- Added tombstone compaction for the HNSW backend: a partition is rebuilt from its live records once deleted entries exceed 30% of its size, keeping search on hnswlib's fast path.
- Added HNSW tuning settings to `UIISSettings` (`HnswM`, `HnswEfConstruction`, `HnswEfSearch`) for recall/latency trade-offs on large projects.
- Added an in-run embedding cache: identical chunk text on the same route is embedded once per indexing run, skipping redundant executor calls. The cache is local to IIS, so it adds no cross-plugin dependency.
- Added an `Int8 Kernel Override` setting (Auto/Scalar/ISPC/AVX2) to select the active HNSW int8 distance kernel; Auto picks the best available at startup, and forcing an unavailable tier falls back to the best available.
- Added structured per-query diagnostics (`FIISQueryDiagnostics` on `FIISSearchResponse`): per-stage latency (lexical/vector/merge/total), the vector backend, effective HNSW `efSearch`, resolved storage format, and the active int8 kernel (HNSW-only). Categorical fields are `FName` so the always-on path adds no per-query heap allocation; a human-readable summary is available on demand via `ToSummary()`. The vector backend `Search` gained an optional `FIISVectorSearchDiag` out-parameter so the effective `efSearch`/backend id are reported by the backend rather than guessed. Opt-in recall estimation (`FIISSearchQuery::bEstimateRecall`) compares the approximate top-k against a transient exact brute-force reference (`FIISVectorIndexService::EstimateRecallAtK`, O(N·dim), no graph build) and is excluded from the measured query latency. An explicit `FIISQueryDiagnosticsReport` aggregates records to a Saved JSON (per-stage p50/p95, backend/kernel/format distribution, mean recall); ordinary search never writes per-query files.

### Changed
- Moved the Control Panel entry under the shared **Tiny Tools** menu and added editor settings for menu placement and visibility.
- Documented MCP access through project Capability Mesh routes (`iis.agent.*.v1`) instead of a dedicated IIS UMCP bridge plugin.
- IIS agent contracts and governance UI now describe UCM route ids; local `iis_*` contract names remain for in-engine JSON invocation.
- Vector upsert/remove is now O(1) via a `ChunkId`→index map in both backends.
- HNSW inserts are incremental (resize/replace-deleted) instead of triggering a full index rebuild; updates now reuse tombstoned slots (`replace_deleted=true`) so re-embedding the same chunk no longer grows the index.
- HNSW partition builds run across worker threads (`ParallelFor` over `addPoint`).
- Index and manifest persistence uses atomic temp-file + move writes.
- HNSW index save/load is wide-path-safe: bytes are read/written through UE IO (stream overloads) instead of hnswlib's narrow `std::ofstream`, so non-ASCII project paths no longer corrupt or lose the index.
- Internal identity/cache keys now use `FIoHash`.
- Redundant vector sync work is skipped via no-op upsert detection and delta sync, with partition metadata included in the vector sync key.
- Vector index reads/writes are guarded by a read/write lock; a lock-free `SearchLocked` path was extracted and `EnsureBuilt` added.
- Enforced autark module boundaries between IIS and peer plugins; removed compile-time dependency on `UnifiedMcpServerInterface`.
- Embedding executor lookups now resolve solely through `IModularFeatures` discovery; the internal ownership map no longer acts as a second, independently consulted registry.
- Editor job history APIs renamed to `RecordJob` / `GetRecentJobs`; MCP exposure is through UCM routes only.
- UMCP aggregated job lookups honor the configured max job history count instead of a fixed 500-entry scan.
- Exported selected runtime/editor classes via module `*_API` macros to support automation linkage.
- The HNSW int8 distance kernel is now SIMD-accelerated (hand-written AVX2 when the CPU supports it, ISPC otherwise, scalar floor), detected once at startup and switchable at runtime; results are bit-identical to the previous scalar kernel, so search ordering is unchanged. The Float32 vector space now uses hnswlib's native SIMD inner-product instead of a scalar dot.

### Fixed
- HNSW `Search` is now strictly read-only and never rebuilds or writes the index on query.
- The JSONL brute-force backend is now locked for parity with the HNSW backend under concurrent search/upsert.
- Hardened embedding executor discovery and legacy registry upsert behavior.
- Closed hardening gaps across the embedding queue, async cancellation, and settings.
- The editor Cancel action now cancels the active async index job (via `IISAsyncCancellation::RequestCancel`) even when no Control Panel is open, and records the cancellation in editor job history.
- The vector index service no longer rebuilds the whole backend on every record-count change, so incremental upsert/remove now actually take effect on the sync and embedding paths instead of being discarded.
- Incremental vector updates (upsert/remove) now persist correctly across editor restarts; the partition manifest records explicit label/chunk pairs. Indices written by older versions are rebuilt once on first load.

### Removed
- Removed `FIISUmcpJobStatusProvider` and `UnifiedMcpServerInterface` from the editor module build; job visibility for agents uses UCM routes instead.
- Recover orphaned `Running` embedding jobs by rehydrating them to `Pending` at execute start and cancelling `Running` jobs on abort.
- Invalidate the SQLite embedding job store when a snapshot replace fails so loads no longer prefer stale rows over fresh JSONL.

## [1.0.4] - 2026-06-10

### Changed
- Bumped patch version as part of release housekeeping.
- Updated execute-side metadata alignment for MCP-capable tools where applicable.

## [1.0.3] - 2026-06-09

### Added
- Added full Fab-ready documentation set covering buyer scope, quick start, user manual, settings reference, C++ code map, integration points, troubleshooting, and release review.
- Added explicit publisher and intended publication year headers to IIS source files, build scripts, validation tooling, and bundled third-party headers.

### Changed
- Updated IIS modules to C++20 for UE 5.6 engine-header compatibility while retaining UE 5.4 as the minimum supported engine version.

## [1.0.2] - 2026-06-08

**Compatibility note:** the embedded MCP server is removed from IIS. MCP access now comes from
the standalone **Unified MCP Server** plugin together with the **InternalIndexServiceUMCPBridge**.
Migration: install both plugins. IIS's six agent tools are published unchanged as
`iis_*` tools (e.g. `iis_search`); no agent-side change beyond pointing the client at
the Unified MCP Server endpoint.

### Changed
- MCP access moved out of IIS into the standalone Unified MCP Server plugin. IIS now exposes its agent tools through the `InternalIndexServiceUMCPBridge` instead of an embedded loopback endpoint.

### Removed
- Embedded MCP endpoint, MCP server manager, and the bundled Python stdio proxy (`Tools/mcp_proxy`). This removes IIS's runtime dependency on a system Python and the `mcp` PyPI package.
- The `bEnableMcpEndpoint` and `McpPort` settings, the editor MCP lifecycle API (`StartMcp`/`StopMcp`/`RotateMcpToken`), the MCP dashboard/governance UI, and the `HTTPServer` editor module dependency.

## [1.0.0] - 2026-06-07

First public release: local indexing, retrieval, context packs, usage-graph find-usages,
Blueprint explanation, MCP agent access, Control Panel v2, incremental index with HNSW
vector backend, and release validation gate tooling.

### Added
- Added Fab third-party software declaration notes for bundled `hnswlib`.
- Added `UIISSettings` (`UDeveloperSettings`) as the project-settings surface for vector backend and MCP endpoint configuration (Plugins → Internal Index Service).
- Added Control Panel v2 host chrome: retrieval-only header badge, global Refresh, and active-state tab styling.
- Added dashboard-first Control Panel landing tab with health cards for Index, MCP Server, and Integrations (`IISCapturePanelStatus`, `SIISStatusCard`, `SIISDashboard`).
- Added editor-module MCP lifecycle API (`StartMcp`, `StopMcp`, `RotateMcpToken`) so the dashboard can start and stop the loopback endpoint from the UI.
- Added incremental-index lifecycle helpers, vector-store rewrite on prune, and HNSW index cleanup when vectors are removed.
- Added release validation gate tooling (`run_iis_gate.py`) with `release` profile stages (`automation_full`, `sample_scan`, `mutation_flags`) and local override example config.
- Added automation coverage for settings defaults, panel status, dashboard/widgets, MCP lifecycle, and incremental conflict/rollback scenarios.
- Added Control Panel v2 **Governance** tab (retrieval-only invariant display, MCP security, data locality, bridge health, agent transparency).
- Added in-panel **Settings** tab mirroring `UIISSettings` with Project Settings shortcut.
- Added grouped tabs: Dashboard | Index | Use | Agents | Governance | Diagnostics | Settings.
- Added dashboard work row (Import shortcut, quick Search, open index folder) with explicit refresh/update actions.
- Added optional `IndexRoot` on `UIISSettings` (empty = default `Saved/InternalIndexService`).
- Slimmed **Tools → AI → Internal Index Service** menu to Open panel + quick actions (Build Index, Open Index Folder).

### Changed
- Updated `Config/FilterPlugin.ini` to include the `Tools/...` folder in packaged Fab builds while excluding local Python cache/config artifacts.
- MCP endpoint and vector backend resolution now read from `UIISSettings` instead of ad-hoc `GConfig` access in editor/runtime paths.
- `FIISStoragePaths::GetDefaultIndexRoot()` respects `UIISSettings::IndexRoot` when set.
- Search and catalog operations filter non-active chunk lifecycle states consistently.
- Dashboard health cards now use persistent widgets and text-only updates; they refresh on open, explicit Refresh, and dashboard actions, removing the remaining visible flicker path.
- Dashboard chunk status now reads the canonical catalog build report from the index folder, with legacy report-folder fallback.
- Replaced non-portable status/header glyphs and cached localized UI labels with direct plain-text labels so unsupported fonts do not show replacement characters.

## [0.1.0] - 2026-05-31

### Added
- Added interface, runtime, and editor modules for local indexing, retrieval, and context-pack workflows.
- Added public contracts for chunks, symbols, assets, Blueprint graph records, search queries, search results, imports, context packs, and agent access.
- Added local storage path handling for project-local Internal Index Service artifacts.
- Added UII evidence import and prepared chunk import support.
- Added chunk catalog and local index service foundations for lexical search and context-pack assembly.
- Added an embedding job queue that delegates provider, model, route, and governance decisions to LLM Store.
- Added durable vector output artifacts, embedding run reports, editor menu actions, and Python bridge functions for embedding operations.

### Changed
- Defined plugin boundaries so IIS owns indexing and retrieval while UII owns Unreal evidence extraction and LLM Store owns model routing and secrets.


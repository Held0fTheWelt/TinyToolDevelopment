# Changelog

## [Unreleased]

### Added
- Added plugin-local `Config/UnrealCapabilityMesh` manifests for server lifecycle, policy snapshot, access-guard read/update, token rotation, and editor-job routes with shared schemas and project-profile registration.

### Changed
- `execute_route` MCP tool annotations now reflect global EXPERIMENTAL self automatic approval when enabled, and route metadata exposes explicit mutating/open-world side-effect flags separate from client approval gating.

## [1.0.7] - 2026-06-16

### Added
- Added aggregation entries for NamingConventionUtility, LightweightEditorMode, PerformancePresetWizard, CodeCopyrightEditor, and LogLevelEditor editor-job routes.
- Added automation coverage that smoke-tests the five governance-tool `editor.jobs.list` and `editor.jobs.status` endpoints through the UMCP job contract.
- Added UCM editor job routes (`umcp.editor.jobs.list.v1`, `umcp.editor.jobs.status.v1`) and `UUmcpCapabilityMeshEndpoints` for UMCP panel job history.
- Added `FUmcpJobsRouteAggregator` so aggregated `jobs_list` / `jobs_status` MCP tools call UCM gateway routes instead of in-process provider registration.
- Added an editor jobs surface: shared job-status contract, jobs tool provider, editor commands, panel view model, and a Control Panel jobs view (part of the cross-plugin editor-UI job contract).

### Changed
- Aggregated job tools now include governance utility providers exposed through UCM routes, so MCP administration can inspect cross-plugin job history from one surface.
- Aggregated job tools now merge results from fixed UCM route ids (`iis`, `scd`, `llmstore`, `umcp`) via `ExecuteRouteJson`; per-plugin `mesh_route_*_editor_jobs_*` tools remain available when Capability Mesh is enabled.
- Tool DTOs are now typed behind `InvokeTool` via `FUmcpJsonAdapter`, while the protocol-edge JSON wire format is kept unchanged.
- Job-status lookups honor the configured max job history count instead of a fixed 500-entry scan.
- Marked `IUmcpJobStatusProvider` as deprecated; tool plugins must expose job history through UCM routes, not modular-feature registration.

### Removed
- Removed `FUmcpEditorJobStatusProvider` and direct `IUmcpJobStatusProvider` registration from the editor module (UMCP-native jobs are served through UCM routes).

### Fixed
- Closed hardening gaps in editor settings and job-status tooling.
- Restored Fab autarky by eliminating compile-time `UnifiedMcpServerInterface` coupling from peer tool plugins.

## [1.0.6] - 2026-06-13

### Added
- Runtime Access Guard for temporary in-editor tool blocks without changing persistent provider, profile, allowlist, or blocklist settings.
- Token/tool runtime blocks are enforced for both `tools/list` and `tools/call`; stopping the server clears runtime blocks.
- Access Journal for `tools/call` requests with timestamp, token id, client hint, tool name, argument keys, outcome, error code, and latency.
- Secret-safe argument redaction for access diagnostics. Secret-looking keys are omitted, redacted JSONL is bounded, and sanitized RAM entries are capped.
- Control Panel Access Activity tab with recent access entries, runtime-block counts, refresh, token/tool block/unblock, and clear-runtime-block actions.
- Blueprint/editor diagnostics for recent access entries and runtime guard actions.

### Changed
- `initialize` now reports server version `1.0.6`.
- Request handling performs a static registry access precheck before provider invocation so blocked tools cannot execute provider code.

## [1.0.5] - 2026-06-13

### Added
- Scoped session tokens on the single local endpoint: `default`, `read_only`, `automation`, and `experimental_admin`.
- Handshake `tokens` object alongside the legacy `token` field so existing clients keep working while newer clients can choose a scoped token.
- Token-aware policy enforcement for `tools/list` and `tools/call`; scoped tokens force their profile while provider toggles, allowlists, and blocklists still apply.
- Status snapshots now include token count for editor diagnostics and Blueprint status.

### Changed
- Token rotation now regenerates all active session tokens and rewrites the handshake file.
- Control Panel labels now reflect multiple bearer tokens.

## [1.0.4] - 2026-06-13

### Added
- Profile system: `Default`, `Read Only`, `Automation`, and `Experimental` provide high-level exposure modes without splitting providers across ports.
- Annotation-derived tool groups for policy evaluation, including `read_only`, `non_destructive`, `idempotent`, `risky`, `destructive`, `open_world`, and `unclassified`.
- Optional group allow/block lists so teams can govern tools by behavior class as well as by exposed tool name.

### Changed
- Control Panel tool details now include derived groups next to MCP annotation hints, making profile decisions easier to inspect.
- Documentation now positions profiles as the policy layer used by 1.0.5 scoped tokens.

## [1.0.3] - 2026-06-13

### Added
- Provider access control: provider IDs can be disabled from UMCP settings or the Control Panel without changing provider plugin registration.
- Tool access policy: optional exposed-tool allowlists/blocklists hide tools from `tools/list` and block direct `tools/call` execution.
- Control Panel access status: connected functions now show whether a tool is exposed, blocked, hidden by allowlist, or unavailable.
- Control Panel annotation hints: read-only, destructive, idempotent, and open-world MCP annotations are surfaced in tool descriptions.

### Changed
- `tools/list` and `tools/call` now share the same access-policy evaluation, so hidden tools cannot be invoked by name.
- Control Panel provider groups include an enable/disable action for single-provider groups.

## [1.0.2] - 2026-06-13

### Added
- Connected Functions control panel: plugin-grouped tree (`Plugin → Tool → Input/Output schema`) with per-plugin and per-tool expand/collapse.
- Incremental UI refresh: expand/collapse updates only the affected plugin group or tool row instead of rebuilding the full list.
- Async connected-function loading on a background thread, with snapshot fingerprint caching, mesh JSON caching, and parsed schema caching for faster repeat visits.
- Dynamic column header in Connected Functions: four columns (`Provider`, `Ready`, `Tool`, `Description`) when all tools in a plugin are collapsed; six columns when any tool in that plugin is expanded.

### Changed
- Flattened UCM route tools (`mesh_route_*`) are grouped under the owning plugin from Capability Mesh capability metadata, not under the mesh host provider.
- Mesh host provider display name in the editor UI is **Unreal Capability Mesh** (removed legacy *The Plug* prefix from UMCP-facing strings).
- Connected Functions layout: wrapped tool and parameter names, narrower **Type** column, wider **Input**/**Output** columns in expanded rows, and wrapped **Ready** status text.
- Collapsed tool rows use a wide **Description** column aligned with the collapsed header; expanded rows use the full six-column schema layout.

### Fixed
- Control panel no longer triggers a full connected-function rebuild on every tool expand/collapse click.

## [1.0.1] - 2026-06-09

### Added
- Added explicit publisher and intended publication year headers to UMCP source files and build scripts for Fab review compliance.

### Changed
- Updated `Config/FilterPlugin.ini` to list only the additional packaged folders/files outside the default BuildPlugin structure: `Config`, `Documentation`, and `CHANGELOG.md`.
- Moved lifecycle menu actions to **Tools → AI → Universal MCP** instead of a flat Tools list entry.

## [1.0.0] - 2026-06-08

### Added
- Standalone Unified MCP Server: loopback JSON-RPC 2.0 MCP-over-HTTP server.
- `IUmcpToolProvider` modular-feature contract; tools attach at runtime.
- Provider registry with `<providerId>_<tool>` namespacing and live attach/detach.
- Opt-in settings, bearer-token auth, handshake file, request log, Tools menu.
- `UUmcpEditorBlueprintLibrary` for editor-only lifecycle/diagnostics (start/stop/rotate, endpoint JSON, status).
- Zero bundled executables; no third-party runtime.
- Full packaged documentation set for setup, usage, integration, troubleshooting, and release review.
- UE 5.6-compatible C++20 build settings for UMCP modules.

### Security
- The handshake file carries the bearer token, so it is written owner-only on
  POSIX (0700 directory / 0600 file) and deleted when the server stops.

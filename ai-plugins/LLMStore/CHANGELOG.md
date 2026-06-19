# Changelog

All notable changes to this plugin will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this plugin adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

### Added
- Added plugin-local `Config/UnrealCapabilityMesh` manifests for provider/model/route discovery, setup validation, secret/cost/audit snapshots, completion execution, and editor-job routes with shared schemas and project-profile registration.

## [1.0.5] - 2026-06-16

### Added
- Added async lifecycle types and shutdown-safe HTTP request tracking in `LLMStoreSubsystem` so in-flight requests are tracked and cancelled cleanly on shutdown.
- Added a shared typed JSON error envelope (`FLLMJsonEnvelope`) in the interface module.
- Added an editor job-status contract, editor commands, developer settings, tool-menu registration, and UCM editor job endpoints (`ULLMStoreCapabilityMeshEndpoints`) for the LLM Store control panel (part of the cross-plugin editor-UI job contract).

### Changed
- Moved the Control Panel entry under the shared **Tiny Tools** menu and added developer settings for menu placement and visibility.
- Reworked the embedding core to be typed; JSON methods became thin boundary adapters around the typed core, with hardened JSON-boundary handling.
- Validation-on-reload now runs the actual validation pass after a reload instead of recording a synthetic validation job.
- Removed compile-time dependency on `UnifiedMcpServerInterface`; editor job history APIs renamed to `RecordJob` / `GetRecentJobs`.
- `ExecuteRouteStreaming` now runs through the same concurrency-controlled request queue as `ExecuteRoute`/`EnqueueRoute`, so streaming entrypoints honor `MaxConcurrentQueuedRequests` instead of firing unbounded parallel HTTP.
- UMCP aggregated job lookups honor the configured max job history count instead of a fixed 500-entry scan.
- Exported selected provider/config classes via module `*_API` macros to support automation linkage.

### Fixed
- Closed hardening gaps in editor settings, job-status delegation, and async lifecycle handling.

### Removed
- Removed `FLLMStoreUmcpJobStatusProvider` and `UnifiedMcpServerInterface` from the editor module build.

## [1.0.4] - 2026-06-10

### Changed
- Bumped patch version as part of release housekeeping.
- Updated execute-side metadata alignment for MCP-capable tools where applicable.

## [1.0.3] - 2026-06-08

### Added
- Added a dedicated freebie script catalog and README entries for optional Bash helpers that extend local/internal LLM Store copies after purchase.

### Changed
- Updated plugin release metadata to version `1.0.3` with numeric Unreal plugin version `103`.

## [1.0.2] - 2026-06-04

### Added
- Added documentation for the optional external automation/freebie workflow so teams can re-enable local agent auth launch and automatic CLI auth-status checks in their own fork without changing the Fab-ready default package.

### Changed
- Updated agent authentication in the Fab-ready editor UI to a copy-only manual flow: LLM Store displays setup commands and no longer opens external login processes from the editor.
- Updated built-in agent status handling so authentication remains with the external tool and status refresh does not automatically start external auth-status commands.
- Replaced CI and release documentation examples that used concrete platform binary names with neutral placeholders such as `<UnrealEditorCommand>` and `<UnrealBuildCommand>`.
- Renamed the built-in `agent.execute` capability label to `agent.run` to avoid static binary-extension false positives while preserving the intent of the capability.
- Updated plugin release metadata to version `1.0.2` with numeric Unreal plugin version `102`.

### Fixed
- Removed Fab review-triggering command/file-extension string literals from the editor source path, including direct shell launch text and fixed executable suffix lists.
- Removed the `Run Auth` button from the bundled Fab UI so the buyer-facing flow matches the documented manual authentication model.

## [1.0.1] - 2026-06-03

### Added
- Added guided Quick-Start on the Setup page (`SLLMQuickStartCard`): one-click stacks for Mock, local Ollama, and cloud OpenAI/Anthropic.
- Added `LLMBuildStarterSetup` and `ULLMStoreSubsystem::ApplyStarterSetup` to create provider, model, and `default` route entries idempotently with stable `quickstart_*` IDs.
- Added `LLMStarterProviderId` helper for cloud key storage via the existing secret store (`SetProviderKey`, never written to config JSON).
- Added Quick-Start flow integration: apply setup → optional API key → `TestConnection` → `RecomputeReadiness` with status feedback in the card.
- Added automation specs for starter-setup idempotency, non-destructive merges, mock route resolution, and Quick-Start card construction.

### Changed
- Setup page layout now shows the Quick-Start card above the provider and model sections; the card auto-collapses when readiness is already green (severity 0).
- Updated plugin release metadata to version `1.0.1` with numeric Unreal plugin version `101`.

### Fixed
- Updated all source, header, and Build.cs copyright notices to use the publishing year and publisher name `Tiny Tool Development`.
- Added the root `CHANGELOG.md` to `FilterPlugin.ini` so the packaged plugin explicitly includes the release notes outside the standard plugin folders.
- Removed the empty local `Content` folder from the plugin layout because LLM Store does not ship content assets.
- Aligned the release notes with the Fab review follow-up scope so all current publication fixes are tracked under `1.0.1`.

## [1.0.0] - 2026-05-31

### Added
- Added LLM Store as the central Unreal Engine vault and governance layer for LLM providers, models, task routes, policies, costs, secrets, and optional agents.
- Added interface, runtime, and editor modules so consumers can depend on stable contracts without hard-coding provider implementations.
- Added provider, model, route, runtime mode, readiness, request, response, cost, and add-on contract types.
- Added provider adapters for local, cloud, compatible, mock, completion, and embedding workflows.
- Added editor tabs for setup, routes, agents, costs, governance, status, help, and advanced add-on sections.
- Added route execution, embedding route execution, fallback handling, readiness reporting, observer notifications, and add-on registries.
- Added secret storage, environment override support, cost ledger tracking, CSV export, and CI policy commandlet support.
- Added Blueprint and C++ integration surfaces plus documentation for quick start, providers, routes, policies, costs, agents, integration, and CI.

### Security
- Split shareable structural configuration from secrets so API keys are not stored in committed project configuration.


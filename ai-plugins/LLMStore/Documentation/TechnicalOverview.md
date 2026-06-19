# Technical Overview

This page describes the technical architecture of LLM Store for maintainers and technical buyers. For code-level details, see [CodeDocumentation.md](CodeDocumentation.md). For configuration fields, see [SettingsReference.md](SettingsReference.md).

## Architecture Goal

LLM Store is a self-contained infrastructure plugin. It must not depend on project-specific tools such as asset inspectors, RAG systems, or studio integration layers. Instead, it provides stable interfaces that those tools can use.

Core principles:

- The store owns providers, models, routes, policies, secrets, costs, health, and agents.
- Domain tools provide context or call routes.
- Add-ons extend the store through interfaces.
- C++ and Blueprint receive equivalent integration paths.
- Cloud usage is explicitly governable.
- Local usage works without external services.

## Modules

```text
Source/LLMStoreInterface
Source/LLMStore
Source/LLMStoreEditor
```

| Module | Responsibility |
| --- | --- |
| `LLMStoreInterface` | Public types, facade interface, provider contracts, add-on contracts, Blueprint base classes. |
| `LLMStore` | Engine subsystem, configuration, routing, HTTP execution, policies, secrets, cost ledger, agent bridge. |
| `LLMStoreEditor` | Slate UI for setup, routes, agents, costs, governance, status, help, and advanced add-ons. |

## Data Flow

```text
Feature Tool
  -> FLLMRequest(TaskKind)
  -> ULLMStoreSubsystem
  -> ResolveRouteChecked
  -> Provider + Model + Policy + Secret
  -> Provider Adapter
  -> HTTP / local mock / agent bridge
  -> FLLMResponse
  -> Audit + Cost Ledger + Health
```

## Route Resolution

Route resolution is the stable core:

1. Find an enabled route by `TaskKind`.
2. Respect `bUseMock`.
3. Choose the preferred model.
4. Consider fallback models.
5. Load the referenced provider.
6. Check provider and model state.
7. Load the secret only in memory.
8. Apply route policy.
9. Apply registered policy add-ons.
10. Return `FLLMResolvedRoute`.

The feature tool does not need provider keys.

JSON-facing helpers are boundary adapters around typed core operations. Internal embedding callers should use typed route resolution/execution, while `...Json` entrypoints parse, validate, and serialize at the edge so existing JSON consumers keep the same wire shape.

## Provider Adapters

Provider adapters translate the generic store request into provider-specific HTTP.

A provider implements:

```text
GetProviderType
BuildHttpRequest
ParseHttpResponse
```

OpenAI-compatible providers may share logic while still keeping provider-specific defaults, tests, and base URLs.

## Streaming

LLM Store exposes:

```text
ExecuteRouteStreaming
```

Providers with real streaming emit multiple `FLLMStreamChunk` events. Providers without streaming may emit one final chunk. Callers can still use one API.

Streaming requests now enter the same concurrency-controlled request queue as regular `ExecuteRoute` and queued `EnqueueRoute` work. The subsystem active-request limit therefore applies to streaming HTTP/local calls as well, which keeps slow local inference or parallel cloud streams from bypassing project governance.

## Embeddings and Reranking

Embeddings use dedicated routes:

```text
FLLMStoreEmbeddingRoute
FLLMStoreEmbeddingRequest
FLLMStoreEmbeddingResponse
```

RAG plugins can embed documents, assets, or source code without managing provider details directly.

Reranking is represented as a request operation and can be implemented by provider adapters or add-ons.

## Context Packs

`FLLMContextPack` is the neutral bridge for context providers.

Possible context providers:

- project source code
- UAsset metadata
- Blueprint summaries
- local documentation
- external knowledge bases

LLM Store does not own this domain logic. It receives standardized context packs and can turn them into regular LLM requests.

## Agent Bridge

Agents are optional adapters for tools such as Codex, Claude, Cursor, or studio assistants.

The store manages:

- status
- capabilities
- authentication guidance
- supported task kinds
- request/response contracts
- safety flags for file writes and shell execution

The store does not blindly run shell commands. Adapters must honor policies and request flags.

## Editor Jobs And Autark Integration

The editor module records recent panel jobs through `RecordJob` / `GetRecentJobs` and exposes read-only UCM endpoints:

```text
llmstore.editor.jobs.list.v1
llmstore.editor.jobs.status.v1
```

These routes are the integration surface for Unified MCP Server job aggregation. LLM Store does not depend on `UnifiedMcpServerInterface` to publish job history, preserving standalone Fab packaging.

## Secret Flow

```text
GetProviderKey
  -> environment variable
  -> configured backend
  -> empty string when missing
```

Supported backends:

- `EncryptedFile`
- `WindowsCredentialManager`
- `MacOSKeychain`
- `OnePassword`
- `AzureKeyVault`

Keys are not serialized to `Config/LLMStore.json`. For external backends, `Flush` is intentionally a no-op because persistence belongs to the backend.

## Cost Flow

Each executed request records an audit event. If provider usage data exists, it is used. Otherwise the store estimates tokens.

```text
FLLMAuditEvent
  -> FLLMUsageStats
  -> FLLMCostRule
  -> FLLMCostReport
```

Ledger path:

```text
Saved/LLMStore/CostLedger.json
```

CSV reports:

```text
Saved/LLMStore/CostReports/
```

## Governance

Governance has multiple layers:

- route policies
- build rules
- provider health
- audit log
- cost ledger
- presets
- setup JSON export, validation, and import
- CI policy commandlet

This lets a team allow cloud in development while requiring local or mock routes for shipping.

## Setup JSON Flow

The editor can export the current setup to any user-selected JSON file. The exported file contains metadata and a nested `Config` object. No provider API keys are written.

Import uses the same validation path exposed by the subsystem:

```text
ValidateSetupJsonFile
  -> parse wrapper or raw config JSON
  -> validate ids and references
  -> report errors and warnings
  -> ImportSetupJson applies only when valid
```

Validation blocks malformed JSON, duplicate ids, missing provider references, and missing model references in enabled routes. Embedding routes can warn rather than fail when they point to add-on-owned providers or models.

## UI Architecture

The editor remains a store UI, not a feature suite.

| Tab | Purpose |
| --- | --- |
| `Setup` | Quick-Start card (`ApplyStarterSetup` / `LLMBuildStarterSetup`), then providers and models. |
| `Routes` | Task routes, fallbacks, policies, tests. |
| `Agents` | External AI agents, auth dialog, status. |
| `Costs` | Cost ledger, reports, CSV export. |
| `Governance` | Health, presets, audit, cache. |
| `Status` | Readiness, blockers, settings state. |
| `Help` | In-editor explanation for buyers and team members. |
| `Advanced` | Optional UI sections contributed by add-ons. |

## Packaging

`Config/FilterPlugin.ini` should include:

```text
/Documentation/...
```

This ensures buyers receive the manual, references, diagrams, and CI examples in packaged plugin builds.

## Boundary With Connected Tools

LLM Store owns:

- providers
- models
- routes
- secrets
- policies
- costs
- health
- audit
- agent contracts
- C++ and Blueprint interfaces

Other plugins are the better home for:

- concrete asset explanations
- Blueprint-specific analysis
- automatic project documentation
- RAG indexes over project-specific data
- workflow-specific UI

Those tools can use LLM Store without making LLM Store depend on them.


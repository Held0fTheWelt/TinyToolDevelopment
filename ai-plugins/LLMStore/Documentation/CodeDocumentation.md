# Code Documentation

This page documents the source layout and main code contracts of LLM Store. It is written for buyers, maintainers, and plugin authors who need to understand how the store is built, where to extend it, and which parts are intentionally kept independent from project-specific AI tools. It complements the Doxygen-style comments in the public headers.

## Source Layout

```text
Source/LLMStoreInterface/
  LLMStoreInterface.Build.cs
  Public/
    Types/
      LLMStoreTypes.h
    Interfaces/
      LLMStoreInterface.h
      LLMProviderInterface.h
      LLMEmbeddingProviderInterface.h
      LLMAddOnInterfaces.h
      LLMBlueprintAddOnInterfaces.h
      LLMStoreObserverInterface.h
    LLMStoreInterfaceModule.h
  Private/
    LLMBlueprintAddOnInterfaces.cpp
    LLMStoreInterfaceModule.cpp

Source/LLMStore/
  LLMStore.Build.cs
  Public/
    LLMStarterSetup.h
    LLMStoreSubsystem.h
    LLMStoreConfig.h
    LLMSecretStore.h
    LLMStoreCIPolicyCommandlet.h
    LLMStoreModule.h
  Private/
    LLMStoreSubsystem.cpp
    LLMStoreConfig.cpp
    LLMSecretStore.cpp
    LLMStoreCIPolicyCommandlet.cpp
    LLMStoreModule.cpp
    Providers/
      LLMOpenAIProvider.*
      LLMOpenAICompatibleProvider.*
      LLMOllamaProvider.*
      LLMLlamaCppProvider.*
      LLMAnthropicProvider.*
      LLMGeminiProvider.*
      LLMAzureOpenAIProvider.*
      LLMMockProvider.*
      LLMMockEmbeddingProvider.*
    Tests/

Source/LLMStoreEditor/
  LLMStoreEditor.Build.cs
  Public/
    ILLMStoreUIExtension.h
    LLMStoreEditorModule.h
  Private/
    LLMStoreEditorModule.cpp
    SLLMStorePanel.h/.cpp
    Widgets/
      SLLMQuickStartCard.*
      SLLMProviderSection.*
      SLLMRouteSection.*
      SLLMAgentSection.*
      SLLMCostTrackingSection.*
      SLLMGovernanceSection.*
      SLLMSettingsStatusSection.*
      SLLMRuntimeModesSection.*
      SLLMReadinessBanner.*
      SLLMHelpSection.*
```

## Main Classes and Structs

| Class/Struct | File | Responsibility |
| --- | --- | --- |
| `ULLMStoreSubsystem` | `LLMStoreSubsystem.h/.cpp` | Engine subsystem and central facade for config, routing, provider execution, secrets, readiness, cost tracking, cache, setup JSON, agents, and add-ons. Exposes `ApplyStarterSetup` for the Quick-Start card. |
| `ELLMStarterKind` / `LLMBuildStarterSetup` | `LLMStarterSetup.h/.cpp` | Pure, in-memory starter config builder (idempotent `quickstart_*` IDs). |
| `SLLMQuickStartCard` | `Widgets/SLLMQuickStartCard.*` | Setup-tab guided first run: apply starter, optional `SetProviderKey`, `TestConnection`, `RecomputeReadiness`. |
| `ILLMStore` | `Interfaces/LLMStoreInterface.h` | Consumer-facing route interface that keeps feature plugins independent from concrete providers and keys. |
| `FLLMStoreConfig` | `LLMStoreConfig.h/.cpp` | JSON-serialized project governance config stored in `Config/LLMStore.json`; secrets are deliberately excluded. |
| `FLLMSecretStore` | `LLMSecretStore.h/.cpp` | Per-provider key store with environment overrides and backend-specific persistence. |
| `ILLMProvider` | `Interfaces/LLMProviderInterface.h` | C++ provider adapter contract for chat, structured output, rerank, and other HTTP-shaped requests. |
| `ILLMStoreEmbeddingProvider` | `Interfaces/LLMEmbeddingProviderInterface.h` | C++ embedding provider contract for vector/RAG workflows. |
| `ILLMContractAddOn` | `Interfaces/LLMAddOnInterfaces.h` | C++ contract hook used by readiness and model validation. |
| `ILLMPolicyAddOn` | `Interfaces/LLMAddOnInterfaces.h` | C++ runtime policy hook used by `ResolveRouteChecked`. |
| `ILLMContextProviderAddOn` | `Interfaces/LLMAddOnInterfaces.h` | C++ context hook that supplies neutral context packs without making LLM Store depend on asset/source/RAG plugins. |
| `ILLMAgentAddOn` | `Interfaces/LLMAddOnInterfaces.h` | C++ adapter contract for external agents such as Codex, Claude, Cursor, or studio tools. |
| `ULLMBlueprint*AddOn` classes | `Interfaces/LLMBlueprintAddOnInterfaces.h` | Blueprint equivalents for provider, embedding, contract, policy, test, context, and agent add-ons. |
| `FLLMReadiness` | `Types/LLMStoreTypes.h` | Readiness snapshot used by the Status tab, observers, and release checks. |
| `FLLMResolvedRoute` | `Types/LLMStoreTypes.h` | Provider/model/endpoint/key result produced by route resolution. |
| `FLLMAuditEvent` | `Types/LLMStoreTypes.h` | Raw execution event used by health, audit, and cost reporting. |
| `FLLMConfigJsonValidationResult` | `Types/LLMStoreTypes.h` | Blueprint-readable result for setup JSON validation/import. |
| `ULLMStoreCIPolicyCommandlet` | `LLMStoreCIPolicyCommandlet.h/.cpp` | Headless build-governance commandlet for CI and release checks. |
| `SLLMStorePanel` | `SLLMStorePanel.h/.cpp` | Top-level editor panel that hosts setup, routes, agents, costs, governance, status, help, and advanced add-on sections. |

## Implementation Files

| File | Implementation focus |
| --- | --- |
| `LLMStoreSubsystem.cpp` | Runtime core: config lifecycle, route resolution, policy checks, HTTP execution, retry/fallback chains, cache, cost ledger, provider health, setup JSON, context packs, embeddings, agents, Blueprint adapter registration, and observer notifications. |
| `LLMStoreConfig.cpp` | Pretty JSON serialization, config path resolution, default load behavior, and config file persistence. |
| `LLMSecretStore.cpp` | Environment-variable lookup, encrypted-file backend, OS/CLI secret backend adapters, and provider-key naming. |
| `LLMStoreCIPolicyCommandlet.cpp` | Command-line parsing, config/readiness checks, build-rule evaluation, and CI exit-code policy. |
| `Providers/*.cpp` | Provider-specific request construction and response parsing. OpenAI-compatible local/server providers share common wire-format logic while keeping their provider type and defaults distinct. |
| `Tests/*.cpp` | Automation coverage for config, routing, provider parsing, readiness, secret backends, embeddings, context, agents, cost tracking, observer behavior, and add-on registration. |
| `LLMStoreEditorModule.cpp` | Editor menu/tab/style registration and built-in agent adapter registration. |
| `SLLMProviderSection.cpp` | Provider editor, default base URLs, key handling through secret store, provider tests. |
| `SLLMModelSection.cpp` | Model editor, provider selection, model tests. |
| `SLLMRouteSection.cpp` | Route editor, fallback/mock/policy fields, route tests. |
| `SLLMAgentSection.cpp` | Agent status cards and authentication dialog with copy-only manual auth command workflow. |
| `SLLMCostTrackingSection.cpp` | Cost report summaries, provider/model/task breakdowns, CSV export, ledger clearing. |
| `SLLMGovernanceSection.cpp` | Provider health, audit log, cache clearing, setup JSON export/validation/import. |
| `SLLMSettingsStatusSection.cpp` | Read-only loaded-settings diagnostics, config path, runtime/governance summary, attention list, health details. |
| `SLLMHelpSection.cpp` | In-editor help for buyers and team members. |

## Module Lifecycle

`LLMStoreInterface` is the lowest dependency layer. It contains only types, interfaces, Blueprint base classes, and lightweight module glue.

`LLMStore` owns the runtime subsystem. `ULLMStoreSubsystem::Initialize` loads configuration, creates the secret store, registers built-in providers, registers the mock embedding provider, loads the cost ledger, and computes readiness. `Deinitialize` flushes store-owned state and clears runtime registries.

`LLMStoreEditor` is editor-only. It registers the `Tools -> LLM Store` entry, the nomad tab, the plugin icon/style, built-in optional agent adapters, and add-on UI extension slots.

Feature plugins should depend on `LLMStoreInterface` whenever possible. They should depend on `LLMStore` only when they need subsystem-only features such as config persistence, secret updates, setup JSON, cost export, or Blueprint add-on registration. They should not depend on `LLMStoreEditor` unless they are contributing editor UI.

## Implementation Comments

The source uses inline comments around the non-obvious implementation decisions:

- why provider keys are loaded only into transient resolved routes
- why `Config/LLMStore.json` excludes secrets
- how fallback chains and mock models are chosen
- why policy add-ons are evaluated by `ResolveRouteChecked`
- how provider health and circuit-breaker state are recorded
- why setup JSON import validates first and applies only on success
- why embedding routes can warn, not fail, when an add-on owns the provider/model
- how context packs keep project-specific RAG or asset logic outside LLM Store
- why Blueprint add-ons are wrapped by C++ adapters before entering core registries
- why agent adapters must honor file-write and shell-execution request flags
- how cost rows merge currencies and cache-hit data
- why commandlet checks are release/governance checks rather than provider live tests

## Configuration Contract

`FLLMStoreConfig` is the committed project source of truth for store governance.

Important groups:

- `Providers`: provider id, type, base URL, timeout, retry, circuit breaker, metadata, enabled state.
- `Models`: model id, provider id, wire name, role, structured-output flag, timeout, enabled state.
- `Routes`: task kind, preferred model, fallback models, mock model, prompt template, workflow scope, route policy.
- `EmbeddingRoutes`: route id, task kind, provider/model ids, dimensions, batch size, fallback route id.
- `RoutePolicies`: reusable route policy entries.
- `PromptTemplates`: reusable template ids and text.
- `CostRules`: token pricing used by cost reports.
- `BuildRules`: development/test/shipping governance checks.
- `SecretBackend`: backend selection and backend-specific addressing.
- `Modes`: runtime profile labels broadcast to observers and consumed by add-ons.

The config is intended to be reviewed and shared with a team. Provider keys belong in the configured secret backend or in environment variables.

## Route Resolution Flow

Feature code calls a route by stable task name, not by provider/model name.

```text
FLLMRequest(TaskKind)
  -> ULLMStoreSubsystem::ResolveRouteChecked
  -> find enabled route
  -> build preferred/fallback/mock model candidate chain
  -> resolve model
  -> resolve provider
  -> load transient secret
  -> apply route policy
  -> apply registered policy add-ons
  -> FLLMResolvedRoute
```

`ResolveRoute` performs structural route resolution. `ResolveRouteChecked` also evaluates policy add-ons and should be used for actual execution.

## Execution Flow

Normal request execution uses:

```text
ExecuteRoute
  -> PrepareRequestForRoute
  -> RenderPromptTemplate
  -> TryGetCachedResponse
  -> ExecuteRouteCandidateChain
  -> ExecuteResolvedRouteWithRetry
  -> Provider.BuildHttpRequest
  -> HTTP request
  -> Provider.ParseHttpResponse
  -> ValidateStructuredOutput
  -> FillUsageAndCost
  -> StoreCachedResponse
  -> AppendAuditEvent
  -> RecordProviderHealth
```

`ExecuteRouteStreaming` exposes the same request model with chunk callbacks. Providers without real streaming may emit one final chunk. Streaming execution and `EnqueueRoute` both pass through the shared request queue, so the subsystem active-request limit applies to streaming and non-streaming route execution consistently.

## Provider Contract

Providers are deliberately small. They translate between store-neutral request/response structs and one provider's wire format:

```cpp
FString GetProviderType() const;
void BuildHttpRequest(...);
FLLMResponse ParseHttpResponse(...);
```

LLM Store owns routing, provider selection, policy, secrets, retries, cache, health, audit, and cost tracking. Providers own only provider-specific HTTP shape and parsing.

## Blueprint Provider Contract

Every buyer-facing C++ extension path has a Blueprint path.

Blueprint provider classes:

- `ULLMBlueprintProviderAddOn`
- `ULLMBlueprintEmbeddingProviderAddOn`
- `ULLMBlueprintContractAddOn`
- `ULLMBlueprintPolicyAddOn`
- `ULLMBlueprintTestAddOn`
- `ULLMBlueprintContextProviderAddOn`
- `ULLMBlueprintAgentAddOn`

The subsystem stores Blueprint objects as UPROPERTY references and wraps them in C++ adapters before registering them with the same internal registries used by C++ add-ons. This keeps runtime behavior consistent.

## Embedding and RAG Flow

Embeddings are separate from chat routes because dimensions, batching, fallback routes, and vector-store expectations are different.

```text
FLLMStoreEmbeddingRequest
  -> ResolveEmbeddingRouteInternal
  -> ValidateEmbeddingRouteGovernance
  -> ILLMStoreEmbeddingProvider::ExecuteEmbedding
  -> optional fallback route
  -> FLLMStoreEmbeddingResponse
```

Project-specific RAG plugins should provide indexing, asset parsing, source parsing, or vector storage. LLM Store supplies governed route/provider execution and neutral request/response structs.

## Context Contract

Context providers return neutral data:

```text
FLLMContextQuery
FLLMContextPack
FLLMContextChunk
FLLMContextReference
```

The store can turn a context pack into a normal request with `MakeContextRequest`. The store does not need to know whether the context came from assets, Blueprints, source files, docs, a local index, or a cloud system.

## Agent Contract

Agents are optional adapters for tools such as Codex, Claude, Cursor, or studio assistants.

Main methods:

```text
GetStatus
GetAuthenticationDescriptor
SupportsAgentTask
ExecuteAgentTask
```

`FLLMAgentRequest` carries explicit safety flags:

- `bAllowFileWrites`
- `bAllowShellExecution`
- `bRequireDiffPreview`

Adapters must honor these flags. LLM Store exposes status, authentication guidance, and routing contracts; it does not make the store depend on any one external agent.

## Secret Flow

Provider key lookup is:

```text
GetProviderKey
  -> LLMSTORE_<PROVIDER_ID>_KEY environment variable
  -> configured backend
  -> empty string when missing
```

Supported backend modes are represented in config by `FLLMSecretBackendConfig`:

- `EncryptedFile`
- `WindowsCredentialManager`
- `MacOSKeychain`
- `OnePassword`
- `AzureKeyVault`

Environment variables take priority for CI, local overrides, and temporary testing.

## Setup JSON Import and Export

The subsystem exposes a portable setup workflow:

```text
ExportSetupJson
ValidateSetupJsonFile
ImportSetupJson
```

`ExportSetupJson` writes a wrapped JSON object:

```json
{
  "Format": "LLMStoreSetup",
  "FormatVersion": 1,
  "SetupName": "LLM Store Setup",
  "ExportedUtc": "2026-06-01T00:00:00Z",
  "Config": {}
}
```

`ValidateSetupJsonFile` accepts either this wrapper or raw `FLLMStoreConfig` JSON. Validation checks JSON parseability, schema conversion, duplicate ids, empty ids, provider references, model references, enabled routes without models, embedding route identity, and route-policy references. Warnings are used when embedding providers/models may be supplied by add-ons.

`ImportSetupJson` validates first and calls `SetConfig` only when the file is valid.

## Cost Tracking

Every executed route appends an `FLLMAuditEvent`. Cost reports aggregate those events by provider, model, and task kind.

```text
FLLMAuditEvent
  -> FLLMUsageStats
  -> FLLMCostRule
  -> FLLMCostReport
```

Important files:

```text
Saved/LLMStore/CostLedger.json
Saved/LLMStore/CostReports/LLMStoreCostReport.csv
```

The CSV export path is user-selectable in the editor.

## UI State

The editor widgets keep transient UI state only. They do not own provider execution or config validation logic.

| Widget | State and responsibility |
| --- | --- |
| `SLLMStorePanel` | Active page, summary text, top-level workflow navigation. |
| `SLLMProviderSection` | Working provider list, provider filter, selected provider, type options, secret field, provider status text. |
| `SLLMModelSection` | Working model list, provider options, selected model, model test status. |
| `SLLMRouteSection` | Working route list, model combo options, selected route, policy fields, route test status. |
| `SLLMAgentSection` | Agent cards, authentication dialog actions, refreshed status list. |
| `SLLMCostTrackingSection` | Cost summary text, CSV export status, clear-ledger action. |
| `SLLMGovernanceSection` | Health/audit readouts, setup JSON status, cache clear action. |
| `SLLMSettingsStatusSection` | Read-only config path, loaded settings summary, warnings/blockers, health status. |
| `SLLMRuntimeModesSection` | Runtime mode edit fields and save status. |
| `SLLMReadinessBanner` | Cached readiness snapshot, severity color, blocker/inventory lists. |
| `SLLMHelpSection` | In-editor buyer guidance and workflow explanation. |

Editor actions delegate back to `ULLMStoreSubsystem` for config persistence, validation, tests, cost export, secret handling, and cache/ledger mutations.

## Commandlet Flow

`ULLMStoreCIPolicyCommandlet::Main` performs governance checks without opening the editor UI:

1. Parse command-line switches.
2. Load `FLLMStoreConfig`.
3. Recompute readiness-like structural checks.
4. Evaluate build rules for the requested or current build configuration.
5. Report blockers and warnings.
6. Return a failing exit code when policy requires it.

See [CommandletAndCI.md](CommandletAndCI.md) for invocation examples and GitHub Actions setup.

## Tests

Automation tests run through:

```text
Automation RunTests LLMStore
```

Coverage areas:

- config JSON round-trips and setup JSON validation
- provider response parsing
- route resolution and fallback behavior
- readiness blockers and warnings
- secret backend behavior
- embedding routes
- context packs
- agent contracts
- cost aggregation
- observer notifications
- C++ and Blueprint add-on registration

## Extension Points

When adding a new provider:

1. Implement `ILLMProvider`.
2. Register it from the subsystem initialization path or through an add-on.
3. Add provider defaults/base URL behavior in the editor where appropriate.
4. Add parse/request tests.
5. Document it in [ProviderReference.md](ProviderReference.md).

When adding a new config field:

1. Add the field to `FLLMStoreConfig` or one of the public structs.
2. Add Doxygen comments and Blueprint metadata where applicable.
3. Update JSON validation when references or invariants are involved.
4. Update [SettingsReference.md](SettingsReference.md).
5. Add or update automation tests.

When adding a new buyer-facing C++ API:

1. Add the C++ method.
2. Add the Blueprint equivalent.
3. Keep the Blueprint category and display name predictable.
4. Document the behavior in this file and, if user-facing, in [UserManual.md](UserManual.md).
5. Add focused tests when the method changes persisted config, policies, routes, secrets, cost tracking, or import/export behavior.

When adding a new editor action:

1. Put UI state in the widget.
2. Put business logic in the subsystem or a provider/add-on contract.
3. Add tooltips.
4. Update the Help tab when the workflow matters to buyers.
5. Update [UserManual.md](UserManual.md).

## Documentation Maintenance Rules

LLM Store documentation should stay at least as complete as Code Copyright Editor:

- every shipped workflow has a buyer-facing explanation
- every config field group is covered in settings/reference docs
- every source-facing contract has Doxygen-style comments
- every new provider has provider reference text and expected base URL behavior
- every governance feature has a user workflow and technical flow
- every commandlet has local and CI usage examples
- every C++ integration path has a Blueprint counterpart or an explicit reason why not
- release notes and checklist entries are updated before Fab submission


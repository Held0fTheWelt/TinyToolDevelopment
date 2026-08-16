<!-- doc-provenance: AKDB:plugins/LLMStore/architecture.md; docs/architecture/plugins/LLMStore/product-facts.yml; reconciled 2026-06-20 -->
# User Manual

This manual describes LLM Store from the perspective of a buyer, technical artist, Blueprint developer, or tools programmer. It explains the editor workflows and points to deeper technical references where useful.

## Plugin Goal

LLM Store is a central AI control layer for Unreal Engine projects. Other plugins and tools should not need to know whether a prompt goes to Ollama, llama.cpp, OpenAI, Claude, Gemini, Azure OpenAI, Mistral, OpenRouter, or a mock. They call a stable task route such as:

```text
docs.summarize
asset.explain
naming.review
rag.embed
agent.patch
```

The route decides provider, model, fallback, policy, cost rule, and secret backend.

## Open the Editor

Open:

```text
Tiny Tools -> LLM Store
```

The tab is designed for daily use. It does not expose only raw settings; it guides setup, routes, status, help, agents, costs, and governance.

## First Setup

### Quick-Start card (fastest path)

1. Open `Tiny Tools -> LLM Store`.
2. Go to `Setup`. The **Quick Start — get running in one click** section is at the top.
3. Choose one of:
   - **Just try it (Mock)** — fully offline; no API key; ideal for CI and first contact.
   - **Local (Ollama)** — creates `quickstart_ollama` at `localhost:11434`; start Ollama before testing.
   - **Create OpenAI** or **Create Anthropic** — paste an API key in the password field, then click the vendor button. The key is stored only in the secret backend.
4. Read the status line under the buttons and the readiness banner above the tabs.
5. If readiness is green, expand the Quick-Start area again only when you need another starter stack (existing `quickstart_*` entries are not duplicated; your own `default` route is never overwritten).

Starter stacks use stable IDs (`quickstart_mock`, `quickstart_ollama`, `quickstart_openai`, `quickstart_anthropic`) and always wire a `default` task route unless you already defined one.

### Manual setup (full control)

1. Open `Tiny Tools -> LLM Store`.
2. Go to `Setup` (below the Quick-Start card).
3. Create a provider, for example `ollama`, `llamacpp`, `openai`, or `anthropic`.
4. Confirm that the base URL default is appropriate.
5. Create a model for the provider.
6. Go to `Routes`.
7. Create a route, for example `docs.summarize`.
8. Choose the preferred model.
9. Click `Test Route`.
10. Check `Status` for warnings or blockers.

## Provider Setup

A provider describes the technical service, not the model itself.

| Field | Meaning |
| --- | --- |
| `Id` | Stable project-local id, for example `local-ollama`. |
| `DisplayName` | Human-readable name in UI and reports. |
| `Type` | Provider type such as `ollama`, `llamacpp`, or `openai`. |
| `BaseUrl` | HTTP endpoint. Known providers receive useful defaults. |
| `Enabled` | Disables the provider without deleting its settings. |
| `RetryCount` | Retry attempts for transient errors. |
| `TimeoutSeconds` | Provider-specific timeout. |
| `CircuitBreaker...` | Protection against repeated failures or hanging servers. |

Local providers normally need no key. Cloud providers normally need a key in the secret store.

## Known Providers

| Provider type | Default base URL | Typical use |
| --- | --- | --- |
| `ollama` | `http://localhost:11434` | Local models through Ollama. |
| `llamacpp` | `http://localhost:8080` | Local llama.cpp server inference. |
| `lmstudio` | `http://localhost:1234/v1` | Local LM Studio models. |
| `vllm` | `http://localhost:8000/v1` | High-performance local or server inference. |
| `tgi` | `http://localhost:8080` | Hugging Face Text Generation Inference. |
| `openai` | `https://api.openai.com/v1` | OpenAI API. |
| `anthropic` | `https://api.anthropic.com` | Claude API. |
| `gemini` | `https://generativelanguage.googleapis.com/v1beta` | Google Gemini API. |
| `azure-openai` | project-specific | Azure endpoint and deployment logic. |
| `mistral` | `https://api.mistral.ai/v1` | Mistral API. |
| `openrouter` | `https://openrouter.ai/api/v1` | Router for many cloud models. |
| `mock` | empty | Tests, UI development, CI, and offline work. |

## Models

A model belongs to one provider.

| Field | Meaning |
| --- | --- |
| `Id` | Stable project-local model id. |
| `Name` | Provider wire name, for example `llama3.1:8b` or `gpt-4o-mini`. |
| `ProviderId` | Provider that serves the model. |
| `Role` | Optional role such as `fast`, `reasoning`, `embedding`, or `local`. |
| `Structured` | Marks models expected to handle JSON/schema output well. |
| `TimeoutSeconds` | Model-specific timeout. |
| `Enabled` | Disables the model without deleting routes. |

## Routes

Routes are the most important store concept. A feature asks for a task, not a model.

Example:

```text
TaskKind: docs.summarize
PreferredModelId: local-fast
FallbackModelIds:
  - cloud-reasoning
  - mock-docs
Policy: local-only for shipping
```

Benefits:

- features stay stable when models change
- policies can be applied per task
- fallback chains can mix local, cloud, and mock models
- cost can be analyzed by task
- CI can validate route policy without knowing every tool

## Test a Route

Use `Test Route` in the `Routes` tab. The test checks:

- route exists
- route is enabled
- model exists
- provider exists
- provider is enabled
- required key exists
- provider responds to a small request

Errors appear in the status area and provider health dashboard.

## Policies

Policies decide whether a route may be used.

Typical rules:

- forbid cloud for sensitive data
- allow only local models for shipping
- set a maximum context size
- set a maximum cost per request
- allow or deny specific provider types

Policies belong in LLM Store. Another plugin may supply context or call a route, but the central governance decision stays in the store.

## Agents

The `Agents` tab shows optional adapters such as Codex, Claude, Cursor, or custom studio tools.

| Status | Meaning |
| --- | --- |
| `NotInstalled` | Tool was not found. |
| `Installed` | Tool exists, authentication is unclear or missing. |
| `AuthRequired` | Authentication must be completed. |
| `Available` | Tool is usable. |
| `Disabled` | Adapter is disabled. |
| `Error` | Adapter reports an error. |

The `Authenticate...` button opens a dialog with command, instructions, help link, and a copy action for manual terminal use. LLM Store does not store external tool credentials.

## Cost Analysis

The `Costs` tab collects and analyzes the cost ledger.

It shows:

- total events
- successful events
- cache hits
- prompt tokens
- completion tokens
- estimated cost
- breakdown by provider, model, and route
- CSV export

Costs are only as accurate as the provider usage data and configured cost rules. Local models can be free or assigned internal hardware cost.

## Secret Store

API keys do not belong in `Config/LLMStore.json`.

Supported backends:

- encrypted local file
- Windows Credential Manager
- macOS Keychain
- 1Password CLI
- Azure Key Vault through Azure CLI

Environment variables take precedence:

```text
LLMSTORE_<PROVIDER_ID>_KEY
```

Example:

```text
LLMSTORE_OPENAI_MAIN_KEY
```

## Status Tab

The `Status` tab answers: "Is my store usable right now?"

It shows:

- global readiness
- blockers
- warnings
- provider inventory
- missing keys
- disabled providers or models
- route problems

Use this tab before sharing settings with a team, running CI, or packaging a release.

## Setup JSON Export, Validation, and Import

The `Governance` tab includes setup JSON actions for sharing or moving complete LLM Store setups.

Available actions:

| Action | Purpose |
| --- | --- |
| `Export Setup JSON` | Choose any folder and file name, then write the current setup as JSON. Secrets are not included. |
| `Validate JSON` | Choose a JSON file and validate schema, provider ids, model references, routes, and warnings without applying it. |
| `Import JSON` | Choose a JSON file, validate it, and apply it only when validation passes. |

The importer accepts both the wrapped LLM Store setup format and a raw `FLLMStoreConfig` JSON object. This makes it suitable for presets, backups, team handoff files, and manually reviewed config snapshots.

## Help Tab

The `Help` tab explains directly in the editor:

- what a provider is
- what a model is
- why routes are used instead of direct model names
- how local and cloud providers work together
- how policies and build rules apply
- what cost tracking measures
- how agents are connected

The help section is included in the plugin so buyers do not need to jump between a website, README, and editor UI for basic concepts.

## Blueprint Usage

Important integration points are available in Blueprints.

| Class | Purpose |
| --- | --- |
| `ULLMBlueprintProviderAddOn` | Connect a provider from Blueprint. |
| `ULLMBlueprintEmbeddingProviderAddOn` | Connect an embedding provider from Blueprint. |
| `ULLMBlueprintContractAddOn` | Validate model contracts. |
| `ULLMBlueprintPolicyAddOn` | Allow or reject routes at runtime. |
| `ULLMBlueprintTestAddOn` | Add setup or status tests. |
| `ULLMBlueprintContextProviderAddOn` | Provide project context as context packs. |
| `ULLMBlueprintAgentAddOn` | Connect external CLIs or editor assistants. |

## C++ Usage

C++ users get the store from the engine subsystem:

```cpp
ULLMStoreSubsystem* Store = GEngine->GetEngineSubsystem<ULLMStoreSubsystem>();
```

Then routes can be resolved, requests executed, context packs built, agents called, and cost reports read.

See [INTEGRATION.md](INTEGRATION.md) and [CodeDocumentation.md](CodeDocumentation.md).

## Recommended Workflows

### Local Development

1. Create `ollama` or `llamacpp` provider.
2. Add a local model.
3. Point routes to the local model.
4. Disable cloud through policy.
5. Keep a `mock` path for tests.

### Hybrid Development

1. Use local models for fast tasks.
2. Add cloud fallback for harder tasks.
3. Set cost limits.
4. Review cost tracking regularly.
5. Keep shipping build rules local/mock only.

### Team Setup

1. Commit `Config/LLMStore.json`.
2. Do not commit keys.
3. Document the secret backend.
4. Export a preset.
5. Check the `Status` tab.
6. Enable CI policy checks.

## Boundaries

LLM Store is not a finished asset explanation tool, Blueprint review tool, or RAG product. It provides routes, providers, policies, cost tracking, secrets, and interfaces. Concrete feature tools can connect to it without making LLM Store depend on those tools.


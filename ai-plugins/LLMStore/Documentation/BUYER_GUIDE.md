# LLM Store Buyer Guide

This guide explains LLM Store for buyers, technical directors, tools programmers, and teams evaluating the plugin for a real Unreal Engine project.

## What Is LLM Store?

LLM Store is a central governance and routing layer for AI access inside Unreal Engine. Instead of embedding OpenAI, Ollama, llama.cpp, Claude, Gemini, or other providers directly into every tool, a project defines neutral routes such as `asset.explain`, `docs.summarize`, or `naming.review`. LLM Store resolves those routes to the provider, model, fallback chain, policy, key, and cost rule that are valid for the current project.

The plugin is intentionally self-contained. It does not require IIS, a project index, a RAG system, or any other studio infrastructure as a hard dependency. When such systems exist, they can connect through interfaces.

## Why This Matters

Without a central layer, AI usage often spreads across plugins, Blueprints, scripts, and editor widgets. That makes provider changes, cost analysis, privacy rules, and shipping restrictions hard to manage.

LLM Store centralizes:

- provider and model configuration
- local and cloud model access
- task routes instead of hard-coded model names
- API keys outside committed configuration
- per-route cloud and local-only policies
- cost tracking by provider, model, and task
- retry, timeout, health, and circuit breaker behavior
- prompt templates and structured output settings
- optional agent integrations
- C++ and Blueprint extension points

## What Is Included?

The plugin contains three modules:

| Module | Included functionality |
| --- | --- |
| `LLMStoreInterface` | Public types, C++ interfaces, and Blueprint add-on base classes. |
| `LLMStore` | Runtime subsystem, routing, providers, secrets, policies, audit log, cost ledger, and agents. |
| `LLMStoreEditor` | Editor UI under `Tools -> LLM Store`. |

The editor UI includes setup, routes, agents, costs, governance, status, help, and advanced add-on sections.

## What Is Not Included?

LLM Store does not ship language models, provider accounts, or cloud credits. For cloud providers you need your own API keys. For local providers you need the relevant local server, such as Ollama, llama.cpp, LM Studio, vLLM, or TGI.

LLM Store is also not a finished project-wide RAG product. It provides context-provider interfaces so a project-specific RAG, asset analysis, Blueprint documentation, or source-index plugin can connect cleanly.

## Typical Workflow

1. Create a provider, for example `ollama`, `llamacpp`, `openai`, or `anthropic`.
2. Create a model for that provider.
3. Create a route such as `docs.summarize`, `asset.explain`, or `naming.review`.
4. Test the provider, model, and route.
5. Configure route policies and cost rules.
6. Let other plugins or Blueprints call only the route.
7. Analyze usage in the `Costs` tab.
8. Check release readiness in the `Status` and `Governance` tabs.

## Local Models

Local providers are well suited for sensitive project data, offline workflows, tests, and shipping-adjacent tools.

Supported local or self-hosted provider types:

| Provider | Default base URL | Notes |
| --- | --- | --- |
| `ollama` | `http://127.0.0.1:11434` | Local Ollama API. |
| `llamacpp` | `http://127.0.0.1:8080` | llama.cpp `llama-server` style workflow. |
| `lmstudio` | `http://127.0.0.1:1234/v1` | LM Studio OpenAI-compatible server. |
| `vllm` | `http://127.0.0.1:8000/v1` | High-performance local/server inference. |
| `tgi` | `http://127.0.0.1:8080/v1` | Hugging Face Text Generation Inference. |
| `mock` | empty | Tests, demos, offline UI, and CI. |

These providers do not require API keys by default.

## Cloud Providers

Cloud providers are useful for high-quality output, large context windows, strong reasoning models, or teams with existing provider contracts.

Supported cloud provider types:

- `openai`
- `anthropic`
- `gemini`
- `azure-openai`
- `mistral`
- `openrouter`

Keys are stored in the secret backend, not in `Config/LLMStore.json`.

## Secret Backends

Supported backends:

- encrypted local file
- Windows Credential Manager
- macOS Keychain
- 1Password CLI
- Azure Key Vault through Azure CLI

Environment variables always override the configured backend, which is useful for CI:

```text
LLMSTORE_<PROVIDER_ID>_KEY
```

## Routes Instead of Direct Providers

Routes are the main design idea.

Feature code should call:

```text
docs.summarize
asset.explain
naming.review
rag.embed
```

It should not call a specific provider model directly. The project can later move a route from local to cloud, from cloud to local, or to a fallback model without changing every tool.

## Blueprint and C++

All important integration points are available for both C++ and Blueprint use.

Examples:

- provider add-ons
- embedding provider add-ons
- policy add-ons
- contract add-ons
- test add-ons
- context provider add-ons
- agent add-ons
- route execution and readiness APIs

See [INTEGRATION.md](INTEGRATION.md).

## Cost Tracking

LLM Store records AI usage in a ledger. The `Costs` tab shows requests, tokens, cache hits, estimated cost, and breakdowns by provider, model, and route.

Useful questions:

- Which route causes the most cost?
- Which provider is used most often?
- Which models are expensive but rarely needed?
- Is the response cache effective?
- Does local/cloud usage match the project policy?

See [COST_TRACKING.md](COST_TRACKING.md).

## Agents

The `Agents` tab shows optional adapters for external tools such as Codex, Claude, Cursor, or a studio-specific assistant. Agents are explicit integrations. LLM Store can show status, capabilities, authentication instructions, and route tasks to an adapter.

The `Authenticate...` dialog displays the relevant login command and lets the user copy it for manual execution. Credentials remain with the external tool.

Security model:

- reading status is low-risk
- external execution is an explicit action
- file writes and shell execution are opt-in request flags
- diff preview can be required by the caller

## Optional Freebie Scripts

LLM Store can include optional Bash helpers that extend a buyer's local project copy or internal source fork after purchase. These are documented separately so teams can decide deliberately whether a script fits their workflow.

The current freebie script catalog includes:

| Script | Category | Purpose |
| --- | --- | --- |
| [`../enable_agent_automation.sh`](../enable_agent_automation.sh) | Local source customization | Re-enables editor-side agent auth launch and automatic CLI auth-status checks in a local/internal source copy. |

Freebie scripts are not required for the default Fab-ready plugin. If a script patches source files, review the changes before committing them and do not upload the patched local customization as the default Fab package.

See [FREEBIE_SCRIPTS.md](FREEBIE_SCRIPTS.md).

## Governance

LLM Store helps teams control AI usage:

- local-only routes for sensitive data
- cloud only in development
- maximum cost per route
- maximum context size
- provider health and last errors
- audit log for traceability
- presets for local, cloud, and hybrid setups
- CI policy checks for shipping builds

## Recommended First Configuration

Safe local start:

```text
Provider Id: ollama-local
Provider Type: ollama
BaseUrl: http://127.0.0.1:11434

Model Id: local-chat
Model Name: llama3.1
ProviderId: ollama-local

Route: docs.summarize
PreferredModelId: local-chat
```

Then add a cloud fallback only if project policy allows it.

## Documentation Map

- [README.md](README.md): overview and feature map
- [FREEBIE_SCRIPTS.md](FREEBIE_SCRIPTS.md): optional Bash helpers for local/internal source customization
- [UserManual.md](UserManual.md): full editor workflow manual
- [TechnicalOverview.md](TechnicalOverview.md): architecture, modules, and data flow
- [CodeDocumentation.md](CodeDocumentation.md): source layout and API contracts
- [SettingsReference.md](SettingsReference.md): configuration field reference
- [ProviderReference.md](ProviderReference.md): provider defaults and setup notes
- [RoutePolicyReference.md](RoutePolicyReference.md): routes, fallbacks, policies, and build rules
- [CommandletAndCI.md](CommandletAndCI.md): CI policy and automation
- [FAQ.md](FAQ.md): common buyer and team questions
- [ReleaseChecklist.md](ReleaseChecklist.md): release and Fab readiness checklist
- [QUICKSTART.md](QUICKSTART.md): first working route
- [INTEGRATION.md](INTEGRATION.md): C++ and Blueprint integration
- [COST_TRACKING.md](COST_TRACKING.md): cost analysis
- [SECRET_BACKENDS.md](SECRET_BACKENDS.md): secret backends and CI overrides
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md): common setup and runtime issues

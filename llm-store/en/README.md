<!-- doc-provenance: AKDB:plugins/LLMStore/architecture.md; docs/architecture/plugins/LLMStore/product-facts.yml; reconciled 2026-06-20 -->
# LLM Store

LLM Store is an Unreal Engine plugin for centrally managing AI providers, models, task routes, policies, costs, secrets, and optional external agents. It is designed as an infrastructure plugin: editor tools and runtime systems should not need to know whether a request is served by Ollama, llama.cpp, OpenAI, Claude, Gemini, Azure OpenAI, Mistral, OpenRouter, or a mock provider. They call a stable route such as `asset.explain`, `docs.summarize`, or `naming.review`.

## Who Is It For?

LLM Store is useful when a project has more than one AI feature and those features should not hard-code provider credentials, model names, cloud rules, or cost logic.

Typical use cases:

- use local models for development, tests, CI, or shipping-adjacent workflows
- allow cloud models in development but block them for shipping builds
- route AI tasks through stable task names instead of direct model names
- evaluate costs by provider, model, and route
- keep API keys out of committed project configuration
- expose the same integration surface to C++ and Blueprint teams
- connect optional agents such as Codex, Claude, Cursor, or studio-specific tools
- let project-specific plugins provide context without making LLM Store depend on them
- expose editor job history through UCM routes without depending on Unified MCP Server

## Modules

| Module | Purpose |
| --- | --- |
| `LLMStoreInterface` | Public structs, facade interface, provider contracts, add-on contracts, and Blueprint base classes. |
| `LLMStore` | Engine subsystem, routing, execution, governance, secrets, cost ledger, and agent bridge. |
| `LLMStoreEditor` | Editor tab for setup, routes, status, help, agents, costs, and governance. |

## Key Concepts

| Concept | Meaning |
| --- | --- |
| Provider | Technical service or local server, for example `ollama`, `llamacpp`, or `openai`. |
| Model | A concrete model served by one provider. |
| Route | Stable task name that resolves to a model, fallback chain, and policy. |
| Policy | Rule for cloud access, local-only behavior, context budget, provider allow/deny lists, and cost limits. |
| Cost Rule | Pricing rule used to estimate request cost from prompt and completion tokens. |
| Agent | Optional adapter to an external tool such as Codex, Claude, Cursor, or a studio assistant. |
| Context Provider | Add-on that supplies neutral context packs from project sources, assets, docs, or other systems. |

## Editor UI

Open the plugin through:

```text
Tiny Tools -> LLM Store
```

Main tabs:

- `Setup`: **Quick-Start** one-click first run (Mock / Ollama / cloud), then create providers and models, edit base URLs, set keys, and test connectivity.
- `Routes`: configure task routes, fallback chains, mock models, prompt templates, and policies.
- `Agents`: inspect Codex, Claude, Cursor, and custom agent adapters; open authentication dialogs.
- `Costs`: analyze requests, tokens, estimated cost, cache hits, and export CSV reports.
- `Governance`: inspect health, audit events, presets, cache state, and build policies.
- `Status`: read the current settings status, warnings, blockers, and inventory.
- `Help`: in-editor explanation of concepts and intended workflows.
- `Advanced`: optional UI sections contributed by add-ons.

## Quick Start

1. Open `Tiny Tools -> LLM Store`.
2. On **Setup**, use the **Quick-Start** card (Mock, Local Ollama, or cloud OpenAI/Anthropic) to get a working `default` route in one click.
3. Or create a provider and model manually, then add routes in the `Routes` tab.
4. Test the provider, model, and route; confirm the readiness banner turns green.
5. Add cost rules if cloud or budget analysis matters.
6. Run a request and inspect the `Costs` and `Status` tabs.

See [QUICKSTART.md](QUICKSTART.md) for step-by-step detail (Quick-Start card and manual setup).

## Local Providers

Supported local or self-hosted provider types:

- `ollama`
- `llamacpp`
- `lmstudio`
- `vllm`
- `tgi`
- `mock`

These providers do not require API keys by default.

## Cloud Providers

Supported cloud provider types:

- `openai`
- `anthropic`
- `gemini`
- `azure-openai`
- `mistral`
- `openrouter`

Cloud providers normally require API keys. Keys are stored in the configured secret backend, never in `Config/LLMStore.json`.

## Blueprint and C++

Consumer-facing functionality is available from both C++ and Blueprints.

Blueprint base classes:

- `ULLMBlueprintProviderAddOn`
- `ULLMBlueprintEmbeddingProviderAddOn`
- `ULLMBlueprintContractAddOn`
- `ULLMBlueprintPolicyAddOn`
- `ULLMBlueprintTestAddOn`
- `ULLMBlueprintContextProviderAddOn`
- `ULLMBlueprintAgentAddOn`

See [INTEGRATION.md](INTEGRATION.md) and [CodeDocumentation.md](CodeDocumentation.md).

Streaming and non-streaming route execution share one concurrency-controlled queue. Use `EnqueueRoute` for long local jobs; `ExecuteRouteStreaming` follows the same active-request guard while still returning stream chunks through its callback API.

## Agent Authentication

The `Agents` tab can show an `Authenticate...` button for each agent. The dialog displays the login command, instructions, help link, and actions to run or copy the command. Credentials stay with the external tool; LLM Store stores only status and instructions.

See [AGENT_AUTHENTICATION.md](AGENT_AUTHENTICATION.md).

## Cost Tracking

LLM Store estimates cost from:

- provider-reported or store-estimated prompt tokens
- provider-reported or store-estimated completion tokens
- matching `FLLMCostRule` entries

The cost ledger is stored at:

```text
Saved/LLMStore/CostLedger.json
```

CSV exports default to:

```text
Saved/LLMStore/CostReports/LLMStoreCostReport.csv
```

See [COST_TRACKING.md](COST_TRACKING.md).

## Privacy and Security

- API keys do not belong in `Config/LLMStore.json`.
- Local providers are the preferred default for sensitive project data.
- Policies can restrict cloud usage per route.
- Build rules can block cloud providers for shipping builds.
- Agent execution is explicit and controlled by request flags.

See [SECRET_BACKENDS.md](SECRET_BACKENDS.md) for encrypted local files, Windows Credential Manager, macOS Keychain, 1Password, and Azure Key Vault.

## Start Here

- [BUYER_GUIDE.md](BUYER_GUIDE.md): buyer-friendly overview, value proposition, and practical workflows.
- [QUICKSTART.md](QUICKSTART.md): first working provider/model/route setup.
- [UserManual.md](UserManual.md): complete editor workflow and UI usage.
- [FAQ.md](FAQ.md): Fab-ready buyer questions and answers.

## Reference

- [SettingsReference.md](SettingsReference.md): configuration fields, defaults, setup JSON files, and recommended baselines.
- [ProviderReference.md](ProviderReference.md): supported local/cloud provider types, base URLs, and notes.
- [RoutePolicyReference.md](RoutePolicyReference.md): route policies, cloud/local restrictions, budget rules, and build policy.
- [COST_TRACKING.md](COST_TRACKING.md): cost ledger, cost rules, CSV export, and analysis workflow.
- [SECRET_BACKENDS.md](SECRET_BACKENDS.md): encrypted local store and external secret backend behavior.
- [AGENT_AUTHENTICATION.md](AGENT_AUTHENTICATION.md): Codex/Claude/Cursor-style agent adapters and authentication dialog behavior.
- [INTEGRATION.md](INTEGRATION.md): C++ and Blueprint integration patterns for other plugins.
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md): common problems and fixes.
- [TechnicalOverview.md](TechnicalOverview.md): maintainer-level architecture overview.

## Included Assets

- [Screenshots/](Screenshots): documentation screenshots and visual workflow diagrams.

## Visual Overviews

- [Screenshots/01-workflow-overview.svg](Screenshots/01-workflow-overview.svg)
- [Screenshots/02-editor-tabs.svg](Screenshots/02-editor-tabs.svg)
- [Screenshots/03-agent-cost-governance.svg](Screenshots/03-agent-cost-governance.svg)

## Quick Setup JSON Workflow

1. Open `Tiny Tools -> LLM Store`.
2. Configure providers, models, routes, policies, and cost rules.
3. Open `Governance`.
4. Use `Export Setup JSON` to write the current setup to any chosen file.
5. Use `Validate JSON` to inspect a setup file without applying it.
6. Use `Import JSON` only after validation passes.

Secrets are never written into setup JSON. Reconnect provider keys through the secret backend or environment variables after importing a shared setup.

## UCM Job Visibility

LLM Store publishes read-only editor job history through `llmstore.editor.jobs.list.v1` and `llmstore.editor.jobs.status.v1` when Unreal Capability Mesh is enabled. Unified MCP Server can aggregate those routes through `jobs_list` / `jobs_status`; LLM Store itself remains autark and does not require a UMCP compile-time dependency.

## Commandlet

Run the CI policy checks from a local terminal or automation runner:

```powershell
<UnrealEditorCommand> "D:\PluginProjectGit\PluginProject.uproject" -run=LLMStoreCIPolicy -unattended -nop4 -nosplash -NoShaderCompile
```

`<UnrealEditorCommand>` is the command-line Unreal Editor target for your local engine installation.

The commandlet checks configured providers, models, routes, policies, and build rules. It is intended for release governance, not for live provider benchmarking.

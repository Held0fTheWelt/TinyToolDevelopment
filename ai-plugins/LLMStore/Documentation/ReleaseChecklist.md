# Release Checklist

Use this checklist for plugin releases, Fab uploads, and internal team approvals.

## Source Build

- [ ] Unreal Editor closed or Live Coding disabled.
- [ ] Full C++ build succeeds.
- [ ] UHT generation completes without errors.
- [ ] No new compiler warnings in changed files.
- [ ] `git diff --check` is clean.

Recommended build:

```text
Build.bat PluginProjectEditor Win64 Development -Project=PluginProject.uproject -NoLiveCoding
```

## Automation Tests

- [ ] `Automation RunTests LLMStore` succeeds.
- [ ] Mock provider tests pass.
- [ ] Route resolution tests pass.
- [ ] Blueprint add-on tests pass.
- [ ] Secret store tests pass.
- [ ] Cost tracking tests pass.
- [ ] Agent contract tests pass.

## Provider Smoke Matrix

Before a larger release, test at least:

| Provider | Required | Notes |
| --- | --- | --- |
| `mock` | yes | Must always work offline. |
| `ollama` | recommended | Standard local setup. |
| `llamacpp` | recommended | Important for GGUF/llama.cpp users. |
| `lmstudio` | optional | OpenAI-compatible local server. |
| `openai` | optional | Requires test key. |
| `anthropic` | optional | Requires test key. |
| `gemini` | optional | Requires test key. |

Not every cloud provider has to be live-tested in every CI run. Structural tests plus documented manual smoke tests are acceptable.

## UI Review

- [ ] `Tools -> LLM Store` opens the tab.
- [ ] Icon appears in the Tools menu.
- [ ] Setup tab is understandable without prior knowledge.
- [ ] New providers receive useful base URL defaults.
- [ ] Important buttons and fields have tooltips.
- [ ] Help tab explains goals, concepts, and workflows.
- [ ] Status tab shows settings state and problems.
- [ ] Agents tab shows the authentication dialog.
- [ ] Costs tab shows ledger and analysis.
- [ ] Text does not overlap in common editor sizes.

## Documentation

- [ ] `README.md` is current.
- [ ] `BUYER_GUIDE.md` explains value and limits.
- [ ] `UserManual.md` describes UI workflows.
- [ ] `TechnicalOverview.md` describes architecture.
- [ ] `CodeDocumentation.md` describes source contracts.
- [ ] `SettingsReference.md` documents config fields.
- [ ] `ProviderReference.md` documents providers.
- [ ] `RoutePolicyReference.md` documents policies.
- [ ] `CommandletAndCI.md` describes CI.
- [ ] `FAQ.md` answers common buyer questions.
- [ ] `TROUBLESHOOTING.md` covers new failure modes.
- [ ] Screenshots and diagrams are included.

## Governance

- [ ] Shipping build rule exists or is intentionally unnecessary.
- [ ] Cloud usage is traceable per route.
- [ ] Cost rules exist for production cloud routes.
- [ ] Secret backend is documented.
- [ ] Audit/cost ledger location is known.
- [ ] Presets can be imported and exported.

## Blueprint Parity

- [ ] Each buyer-facing C++ function has a Blueprint path.
- [ ] Provider add-ons work in Blueprint.
- [ ] Embedding provider add-ons work in Blueprint.
- [ ] Context provider add-ons work in Blueprint.
- [ ] Agent add-ons work in Blueprint.
- [ ] Policy/test/contract add-ons work in Blueprint.

## Packaging

- [ ] `Config/FilterPlugin.ini` includes `Documentation/...`.
- [ ] No local secrets are included in the plugin package.
- [ ] No cost ledgers or private test data are included.
- [ ] Optional freebie scripts are listed in `FREEBIE_SCRIPTS.md` with usage, safety notes, and packaging rules.
- [ ] Any patched output from a freebie script is excluded from the default Fab upload unless explicitly intended for that release.
- [ ] Fab description matches the buyer guide.
- [ ] Version and changelog are current.

## Release Decision

A release is reasonable when:

- build and automation tests pass
- mock and at least one local provider work
- cloud providers are structurally tested or clearly documented as requiring accounts
- documentation, UI, and source comments allow buyers to understand the plugin without external help


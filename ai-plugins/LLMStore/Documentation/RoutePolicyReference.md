# Route and Policy Reference

This reference explains how LLM Store uses routes, fallbacks, policies, and build rules.

## Why Routes?

Routes separate feature code from model decisions.

Hard to maintain:

```text
Feature calls gpt-4o-mini directly
```

Better:

```text
Feature calls docs.summarize
LLM Store chooses model and provider
```

Teams can then change models, limit costs, block cloud, or add local fallbacks without rewriting every feature.

## Route Names

Recommended naming pattern:

```text
domain.action
```

Examples:

| Route | Purpose |
| --- | --- |
| `docs.summarize` | Summarize documents. |
| `docs.generate` | Generate documentation. |
| `asset.explain` | Explain asset context. |
| `blueprint.explain` | Describe Blueprint structure. |
| `naming.review` | Review naming conventions. |
| `rag.embed` | Embed text or assets. |
| `rag.rerank` | Rerank search results. |
| `agent.patch` | Send a task to a patch-capable agent. |

## Fallback Chains

A route can use multiple models:

```text
PreferredModelId: local-fast
FallbackModelIds:
  - local-reasoning
  - cloud-reasoning
  - mock-safe
```

Recommended order:

- local first
- stronger local model second
- cloud only if policy allows it
- mock for tests or offline cases

## Mock Usage

`bUseMock` forces `MockModelId`.

Useful for:

- UI development
- automation tests
- CI without external servers
- reproducible demo workflows

## Route Policy

A route can have its own policy.

### Local Only

```text
bLocalOnly = true
bAllowCloud = false
```

Useful for:

- source code
- confidential project data
- customer data
- shipping-adjacent workflows

### Hybrid With Cost Limit

```text
bAllowCloud = true
MaxEstimatedCost = 0.05
```

Useful for:

- optional developer assistance
- manual review tasks
- non-sensitive documentation

### Provider Whitelist

```text
AllowedProviderTypes = ollama, llamacpp, mock
```

Useful for:

- teams with a clear provider allow list
- CI rules
- offline products

## Global Route Policies

`FLLMStoreConfig.RoutePolicies` can contain general or task-specific rules.

An empty `TaskKind` can be interpreted by tooling as a global rule. A populated `TaskKind` applies to that route.

## Policy Add-ons

C++:

```text
ILLMPolicyAddOn
```

Blueprint:

```text
ULLMBlueprintPolicyAddOn
```

Add-ons can make runtime decisions such as:

- project is in offline mode
- user is not approved for cloud use
- asset is marked confidential
- route is forbidden in the current workflow

## Build Rules

Build rules validate a configuration.

Example:

| BuildConfiguration | bAllowCloud | bRequireLocalOrMock |
| --- | --- | --- |
| `Development` | true | false |
| `Test` | false | true |
| `Shipping` | false | true |

This lets CI prevent a shipping build from requiring cloud routes.

## CI Policy

Commandlet:

```text
UnrealEditor-Cmd.exe Project.uproject -run=LLMStoreCIPolicy -Config=Shipping
```

It validates configured rules and exits with failure when routes violate policy.

See [CommandletAndCI.md](CommandletAndCI.md).

## Cost Policies

`MaxEstimatedCost` depends on:

- token estimation
- provider usage data
- configured cost rules

If no cost rule exists, a cloud request cannot be priced reliably. Production cloud routes should always have cost rules.

## Recommendations

- Use stable route names.
- Do not write model names into feature code.
- Test every production route.
- Set `bLocalOnly` for sensitive routes.
- Protect cloud routes with cost rules.
- Validate shipping builds through build rules.
- Document fallback chains.
- Keep a mock model for CI.


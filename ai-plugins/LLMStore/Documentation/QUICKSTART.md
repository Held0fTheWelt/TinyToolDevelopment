# Quick Start

This guide walks through the first working LLM Store route.

## 1. Open the Editor Tab

Open:

```text
Tools -> LLM Store
```

The top area summarizes loaded providers, models, routes, embedding routes, readiness state, and estimated cost information.

## 2. Create a Local Provider

A local provider is the easiest first test because no API key is required.

### Option A: Ollama

1. Start Ollama locally.
2. Pull a model:

```text
ollama pull llama3.1
```

3. In `Setup`, create a provider:

```text
Id: ollama-local
DisplayName: Ollama Local
Type: ollama
BaseUrl: http://127.0.0.1:11434
Enabled: true
```

4. Create a model:

```text
Id: local-chat
Name: llama3.1
DisplayName: Local Chat
ProviderId: ollama-local
Role: fast
Enabled: true
```

### Option B: llama.cpp

Start a local llama.cpp server:

```text
llama-server -m C:\Models\model.gguf --host 127.0.0.1 --port 8080
```

Then create:

```text
Provider:
  Id: llamacpp-local
  Type: llamacpp
  BaseUrl: http://127.0.0.1:8080

Model:
  Id: local-llamacpp
  Name: local-model
  ProviderId: llamacpp-local
```

## 3. Create a Cloud Provider

Cloud providers usually require an API key. The key is stored in the secret backend, not in `Config/LLMStore.json`.

Example:

```text
Provider:
  Id: openai-main
  Type: openai
  BaseUrl: https://api.openai.com/v1

Model:
  Id: openai-fast
  Name: gpt-4o-mini
  ProviderId: openai-main
```

Then set the key in the provider section or through an environment variable:

```text
LLMSTORE_OPENAI_MAIN_KEY
```

## 4. Create a Route

Create a route in the `Routes` tab:

```text
TaskKind: docs.summarize
PreferredModelId: local-chat
FallbackModelIds:
  - openai-fast
MockModelId: mock-docs
bUseMock: false
```

If you started with llama.cpp, use `local-llamacpp` as the preferred model.

## 5. Add a Policy

For a safe local-first route:

```text
bAllowCloud: false
bLocalOnly: true
MaxContextTokens: 0
MaxEstimatedCost: 0
AllowedProviderTypes:
  - ollama
  - llamacpp
  - mock
```

For a hybrid development route, allow cloud and add a cost limit:

```text
bAllowCloud: true
bLocalOnly: false
MaxEstimatedCost: 0.05
```

## 6. Test Provider, Model, and Route

Use the test buttons in the editor.

If the route does not resolve, check:

- provider enabled?
- model enabled?
- model references the correct provider?
- route uses the correct model id?
- API key set for cloud provider?
- local server running?
- policy allows the selected provider type?

## 7. Add Cost Rules

The `Costs` tab becomes useful once price rules exist.

Example:

```text
ProviderType: openai
ModelId: openai-fast
InputCostPer1KTokens: 0.00015
OutputCostPer1KTokens: 0.00060
Currency: USD
```

Local providers can remain at `0` or use an internal cost model.

## 8. Run a Request

After a request, the `Costs` tab shows:

- event count
- success count
- cache hits
- prompt tokens
- completion tokens
- estimated cost
- provider/model/task breakdowns
- recent events

Use `Export CSV` to write reports to:

```text
Saved/LLMStore/CostReports
```

## 9. Check Status

Open the `Status` tab. The most important section is `Attention`, because it shows missing keys, broken routes, disabled providers, and policy issues.

## 10. Optional Agent Setup

To connect Codex, Claude, Cursor, or a custom agent:

1. Open the `Agents` tab.
2. Select an agent.
3. Click `Authenticate...`.
4. Click `Copy Command`, run the command manually in your preferred terminal, and complete the external login.
5. Refresh the status.

Examples:

```text
codex login
claude auth login
```

LLM Store does not store agent credentials.

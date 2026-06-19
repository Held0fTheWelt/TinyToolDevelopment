# FAQ

## Is LLM Store a chatbot?

No. LLM Store is infrastructure for providers, models, routes, policies, secrets, cost tracking, and agents. A chatbot or asset assistant can use LLM Store, but it is a separate tool.

## Why should I use routes instead of model names?

Routes keep feature code stable. If a tool calls `docs.summarize`, the team can later switch from Ollama to llama.cpp or OpenAI without changing the tool code.

## Can I run everything locally?

Yes. Use providers such as `ollama`, `llamacpp`, `lmstudio`, `vllm`, `tgi`, or `mock`, set policies to local-only, and block cloud through build rules.

## Is llama.cpp supported?

Yes. The `llamacpp` provider type is intended for local llama.cpp servers. The typical base URL is:

```text
http://localhost:8080
```

## Are API keys stored in the project file?

No. `Config/LLMStore.json` stores providers, models, routes, and policies, but not keys. Keys live in the secret store or environment variables.

## Which secret backend should I use?

For single-developer setup, `EncryptedFile` is simple. For teams, Windows Credential Manager, macOS Keychain, 1Password, or Azure Key Vault are usually better.

## Can Blueprint do everything C++ can do?

The important consumer-facing integration points have Blueprint versions. This includes providers, embeddings, policies, tests, context providers, agents, and subsystem facade functions.

## Can I connect Codex, Claude, or Cursor?

Yes, through agent add-ons. The store can unify status, authentication guidance, and task execution. The concrete tool integration remains an adapter and must honor safety rules.

## Does LLM Store automatically run shell commands?

Only when an agent adapter explicitly implements execution and the request flags allow it. `bAllowShellExecution`, `bAllowFileWrites`, and `bRequireDiffPreview` communicate the caller's safety requirements.

## How accurate is cost tracking?

Accuracy depends on provider usage data and `CostRules`. If a provider does not return token counts, the store estimates tokens. Provider billing remains the source of truth for invoices.

## Can I assign costs to local models?

Yes. Local models can cost `0` or use internal accounting values such as approximate GPU cost per 1000 tokens.

## What does not belong directly in LLM Store?

Concrete feature tools such as asset explanation, Blueprint documentation, naming review, or project RAG should use LLM Store but usually live in separate plugins or add-ons. LLM Store remains self-contained.

## What happens if a provider is offline?

The store updates provider health, can attempt fallbacks, and records errors in the audit log. Circuit breaker settings prevent repeated expensive or hanging attempts.

## Can I use LLM Store in CI?

Yes. Use the `LLMStoreCIPolicy` commandlet and automation tests. A GitHub Actions example is included in `Documentation/CI`.

## Do I need to live-test cloud providers?

Not always. For release safety, mock tests, config validation, and optional manual provider smoke tests are often sufficient. Cloud tests should run only with intentionally configured secrets.

## Which files should I commit?

Commit:

- `Config/LLMStore.json`
- optional presets
- team documentation for production routes

Do not commit:

- API keys
- local secret files
- cost ledger files if they contain sensitive operational data

## Can I export and import complete setups?

Yes. The Governance tab can export the current setup to any JSON file, validate a JSON file without applying it, and import a JSON setup only after validation passes. Exported setup files do not include API keys.


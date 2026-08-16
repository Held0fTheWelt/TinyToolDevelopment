<!-- doc-provenance: AKDB:plugins/LLMStore/architecture.md; docs/architecture/plugins/LLMStore/product-facts.yml; reconciled 2026-06-20 -->
# Troubleshooting

This guide lists common LLM Store setup, runtime, UI, policy, and build issues.

## The LLM Store Menu Entry Is Missing

Check:

- Plugin is enabled.
- Editor has been restarted after enabling the plugin.
- `LLMStoreEditor` module is compiled.
- You are running the Unreal Editor, not a cooked runtime build.

Expected location:

```text
Tiny Tools -> LLM Store
```

## Provider Is Not Reachable

Check:

- provider is enabled
- base URL is correct
- local server is running
- firewall or proxy is not blocking the request
- timeout is long enough
- provider type matches the server

Common local defaults:

| Provider | Default |
| --- | --- |
| `ollama` | `http://127.0.0.1:11434` |
| `llamacpp` | `http://127.0.0.1:8080` |
| `lmstudio` | `http://127.0.0.1:1234/v1` |
| `vllm` | `http://127.0.0.1:8000/v1` |
| `tgi` | `http://127.0.0.1:8080/v1` |

Use `Test Provider` first, then `Test Model`, then `Test Route`.

## Route Does Not Resolve

Check:

- route `TaskKind` is spelled exactly as requested
- route is enabled
- preferred model exists
- model is enabled
- model references an existing provider
- provider is enabled
- cloud key exists if required
- route policy allows the provider type
- build/runtime mode does not reject the route

If `bUseMock` is enabled, check that `MockModelId` exists.

## Missing API Key

Keys are not stored in `Config/LLMStore.json`.

Use one of:

- provider key field in the editor
- environment variable override
- configured secret backend

Environment variable format:

```text
LLMSTORE_<PROVIDER_ID>_KEY
```

Example:

```text
ProviderId: openai-main
Variable: LLMSTORE_OPENAI_MAIN_KEY
```

## Environment Variable Is Ignored

Check:

- variable name uses normalized provider id
- editor process was restarted after setting it
- the variable is visible to the process that launches Unreal
- there are no hidden spaces in the value

On Windows, environment changes made through system settings often require restarting the launcher or terminal.

## Windows Credential Manager Does Not Work

Check:

- running on Windows
- `Advapi32` is linked by the plugin build
- credential target name matches the generated provider secret name
- user account has permission
- provider id did not change

If in doubt, set a temporary environment variable to confirm the rest of the provider setup.

## macOS Keychain Does Not Work

Check:

- `security` command is available
- keychain is unlocked
- the process has permission to read the item
- generated secret name matches the expected value

## 1Password Backend Does Not Work

Check:

- `op` CLI is installed
- `op whoami` succeeds in the same terminal context
- `Vault` is set, or `SecretBackend.Meta` contains a full `op://...` reference
- provider-specific override points to the correct item and field

## Azure Key Vault Backend Does Not Work

Check:

- `az` CLI is installed
- `az account show` succeeds
- `Vault` is the correct Key Vault name
- current identity has secret get/set/delete permissions
- provider-specific override matches the secret name

## Cloud Provider Fails but Local Provider Works

Check:

- API key is present
- base URL matches provider documentation
- provider model name is correct
- account has access to the model
- request is not blocked by organization policy
- route cost policy does not reject the request

Look at Provider Health and the latest audit event.

## llama.cpp Does Not Respond

Check:

- `llama-server` is running
- host and port match `BaseUrl`
- server exposes an OpenAI-compatible endpoint
- model is loaded
- request timeout is long enough

Typical start:

```text
llama-server -m C:\Models\model.gguf --host 127.0.0.1 --port 8080
```

Provider:

```text
Type: llamacpp
BaseUrl: http://127.0.0.1:8080
```

## Ollama Does Not Respond

Check:

```text
ollama list
ollama serve
```

Make sure the model in `FLLMModelConfig.Name` exists in Ollama.

## Structured JSON Is Invalid

Check:

- route uses a model suitable for structured output
- `bStructured` is set on the model if your workflow requires it
- `FLLMStructuredOutputSpec.bRequireJson` is true only when needed
- schema is valid JSON
- prompt does not ask for prose around the JSON

Some local models need stricter prompts to produce valid JSON.

## Tool Calls Are Missing

Check:

- provider supports tool calling
- `FLLMToolSpec.ParametersJsonSchema` is valid
- model supports tools
- provider adapter maps tool specs to the provider's wire format

## Streaming Emits Only One Chunk

Some providers do not support native streaming or the current adapter may parse only full responses. This is allowed. The streaming API still emits a final chunk so callers can use one code path.

## Costs Are Zero

Check:

- cost rules exist
- provider type matches the rule
- model id matches the rule or the rule model id is empty
- provider reports usage or token estimation is enabled
- request was not served entirely by a zero-cost local model

## Cost Report Looks Too High

Check:

- cost units are per 1000 tokens
- input and output values are not swapped
- currency is consistent
- model-specific rule is not duplicated by a broader rule
- provider usage data is not already in a different unit

## Agent Is Not Installed

Check:

- CLI or IDE is installed
- tool command is on `PATH`
- Unreal was launched from an environment that can see the tool command
- adapter status check knows the correct command name

Use the `Authenticate...` dialog for setup instructions.

## Agent Auth Does Not Work

Try:

1. Click `Copy Command`.
2. Run the command in a normal terminal.
3. Complete the login.
4. Restart Unreal or refresh agent status.

LLM Store does not store the credentials. It only displays and copies the external login command.

## Agent Refuses File Writes

Check `FLLMAgentRequest`:

```text
bAllowFileWrites
bAllowShellExecution
bRequireDiffPreview
```

Adapters should reject writes or shell commands when the request does not allow them.

## Shipping Policy Fails

Check:

- `BuildRules` for `Shipping`
- route policies
- cloud provider usage
- local or mock fallback availability
- provider allow lists

Run the commandlet locally:

```text
<UnrealEditorCommand> Project.uproject -run=LLMStoreCIPolicy -Config=Shipping -Unattended -NoSplash -NoSound
```

## Settings Status Is Unclear

Open the `Status` tab. It summarizes providers, models, routes, blockers, warnings, missing keys, and inventory.

If the status looks stale:

- click reload if available
- close and reopen the tab
- restart the editor
- check whether `Config/LLMStore.json` was edited manually

## Build Fails Because Live Coding Is Active

Unreal Live Coding can block a full external build while the editor is running. Close the editor or disable Live Coding before a full command-line build.

This does not affect normal UI usage, but it can block CI-style builds or UHT validation.

## Useful References

- First setup: [QUICKSTART.md](QUICKSTART.md)
- Provider details: [ProviderReference.md](ProviderReference.md)
- Route policies: [RoutePolicyReference.md](RoutePolicyReference.md)
- Secrets: [SECRET_BACKENDS.md](SECRET_BACKENDS.md)
- Costs: [COST_TRACKING.md](COST_TRACKING.md)
- Integration: [INTEGRATION.md](INTEGRATION.md)
- CI: [CommandletAndCI.md](CommandletAndCI.md)

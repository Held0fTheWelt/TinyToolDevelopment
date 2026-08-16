# Provider Reference

This reference describes provider types, defaults, and setup notes.

## Provider Matrix

| Type | Default base URL | Key required | Local | Notes |
| --- | --- | --- | --- | --- |
| `mock` | empty | no | yes | Tests, CI, demos, and offline workflows. |
| `ollama` | `http://localhost:11434` | no | yes | Local Ollama API. |
| `llamacpp` | `http://localhost:8080` | no | yes | llama.cpp server-compatible endpoints. |
| `lmstudio` | `http://localhost:1234/v1` | no | yes | LM Studio OpenAI-compatible local server. |
| `vllm` | `http://localhost:8000/v1` | optional | local/server | High-performance OpenAI-compatible inference. |
| `tgi` | `http://localhost:8080` | optional | local/server | Hugging Face Text Generation Inference. |
| `openai` | `https://api.openai.com/v1` | yes | no | OpenAI API. |
| `anthropic` | `https://api.anthropic.com` | yes | no | Claude API. |
| `gemini` | `https://generativelanguage.googleapis.com/v1beta` | yes | no | Google Gemini API. |
| `azure-openai` | project-specific | yes | no | Azure endpoint and deployment details are project-specific. |
| `mistral` | `https://api.mistral.ai/v1` | yes | no | Mistral API. |
| `openrouter` | `https://openrouter.ai/api/v1` | yes | no | Router for many cloud models. |

## Base URL Defaults

When known providers are created in the editor, LLM Store attempts to set a useful base URL. This is a convenience default, not a hard requirement. Teams can override any base URL.

## Local Providers

Local providers are ideal for:

- sensitive project data
- offline development
- shipping-adjacent workflows
- CI smoke tests with mock or local servers
- cost control

### Ollama

Typical setup:

```text
ollama pull llama3.1
ollama serve
```

Create provider:

```text
Type: ollama
BaseUrl: http://localhost:11434
```

Model name should match `ollama list`.

### llama.cpp

Typical setup:

```text
llama-server -m model.gguf --host 127.0.0.1 --port 8080
```

Create provider:

```text
Type: llamacpp
BaseUrl: http://localhost:8080
```

Depending on server version, the model name may be free-form or server-defined.

### LM Studio

LM Studio usually exposes an OpenAI-compatible local server:

```text
http://localhost:1234/v1
```

LLM Store still uses a separate provider type so defaults, tests, and buyer-facing labels are clearer.

### vLLM

vLLM is suitable for larger local or server setups. Many deployments are OpenAI-compatible:

```text
http://server:8000/v1
```

### TGI

Hugging Face Text Generation Inference can run locally or on servers. Streaming and usage fields can differ by deployment, so run provider and route tests.

## Cloud Providers

Cloud providers need keys. Store them in the secret backend, not in JSON config.

### OpenAI

Default:

```text
https://api.openai.com/v1
```

Key:

```text
LLMSTORE_<PROVIDER_ID>_KEY
```

or configured secret backend.

### Anthropic

Default:

```text
https://api.anthropic.com
```

Claude-specific headers and response formats are handled by the provider adapter.

### Gemini

Default:

```text
https://generativelanguage.googleapis.com/v1beta
```

Gemini endpoints can vary by API version and model name.

### Azure OpenAI

Azure is deployment-specific. Typical values belong in `BaseUrl` and `Meta`.

Possible `Meta` values:

| Key | Purpose |
| --- | --- |
| `Deployment` | Azure deployment name. |
| `ApiVersion` | Azure API version. |
| `ResourceName` | Optional resource name for UI/reports. |

### Mistral

Default:

```text
https://api.mistral.ai/v1
```

### OpenRouter

Default:

```text
https://openrouter.ai/api/v1
```

OpenRouter is useful when a project wants to test many cloud models through one router. Governance should still document which model classes are allowed for each route.

## Test Recommendations

Before productive use:

1. Run `Test Provider`.
2. Run `Test Model`.
3. Run `Test Route`.
4. Check the `Status` tab.
5. Add a cost rule.
6. Execute one small real request.
7. Check the cost ledger.

## Provider Add-ons

Custom providers can be connected in C++ or Blueprint.

C++:

```text
ILLMProvider
```

Blueprint:

```text
ULLMBlueprintProviderAddOn
```

A good provider add-on should include:

- stable provider type
- request builder
- response parser
- helpful error messages
- testability through the store UI


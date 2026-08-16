<!-- doc-provenance: AKDB:plugins/LLMStore/architecture.md; docs/architecture/plugins/LLMStore/product-facts.yml; reconciled 2026-06-20 -->
# Third-Party Software

LLM Store **bundles no third-party source code, runtime binaries, AI models, Node.js, Python, or
standalone executables**. It is a C++ Unreal Engine plugin that uses Unreal Engine modules and
standard Unreal HTTP/JSON APIs.

## Optional Provider Integrations (buyer-supplied, not bundled)

LLM Store is a vault and routing layer in front of LLM providers. You choose which provider, if
any, to connect. None is required to install the plugin, and the built-in **Mock** provider runs
fully offline with no account or download.

| Provider | What it is | How to integrate |
| --- | --- | --- |
| Mock | Built-in offline provider | None — works out of the box. |
| Ollama | Local LLM server you install and run | Install Ollama, run it (default `http://localhost:11434`), then add an `ollama` provider. See [QUICKSTART.md](QUICKSTART.md) §3. |
| llama.cpp | Local `llama-server` you run | Start `llama-server`, then add a `llamacpp` provider. See [QUICKSTART.md](QUICKSTART.md) §3. |
| OpenAI | Cloud API (your account) | Create an `openai` provider and paste your API key (stored in the secret backend, never in config). See [QUICKSTART.md](QUICKSTART.md) §4 and [SECRET_BACKENDS.md](SECRET_BACKENDS.md). |
| Anthropic | Cloud API (your account) | Create an `anthropic` provider and paste your API key. See [QUICKSTART.md](QUICKSTART.md) §4. |

These providers are external software/services owned by their respective vendors and are obtained
directly from them. LLM Store does not redistribute them. API keys and agent credentials are your
own; see [SECRET_BACKENDS.md](SECRET_BACKENDS.md) and [AGENT_AUTHENTICATION.md](AGENT_AUTHENTICATION.md).

**Fab third-party software declaration:** no bundled third-party software.

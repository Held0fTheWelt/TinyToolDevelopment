<!-- doc-provenance: AKDB:plugins/LLMStore/architecture.md; docs/architecture/plugins/LLMStore/product-facts.yml; reconciled 2026-06-20 -->
# 第三方软件

LLM Store **不包含第三方源代码、运行时二进制文件、AI 模型、Node.js、Python 或独立的执行文件**。它是一个 C++ 虚幻引擎插件，使用虚幻引擎自身的模块和标准的虚幻 HTTP/JSON API。

## 可选的提供商集成（由买家提供，未包含）

LLM Store 是位于 LLM 提供商前端的保险库和路由层。由您选择连接哪个提供商（如果有）。安装插件不需要其中任何一个，并且内置的 **Mock** 提供商无需账户或下载即可完全离线工作。

| 提供商 | 简介 | 如何集成 |
| --- | --- | --- |
| Mock | 内置离线提供商 | 无需任何操作 — 开箱即用。 |
| Ollama | 需要安装并运行的本地 LLM 服务器 | 安装 Ollama，运行它（默认 `http://localhost:11434`），然后添加一个 `ollama` 提供商。请参阅 [QUICKSTART.md](QUICKSTART.md) §3。 |
| llama.cpp | 需要运行的本地 `llama-server` | 启动 `llama-server`，然后添加一个 `llamacpp` 提供商。请参阅 [QUICKSTART.md](QUICKSTART.md) §3。 |
| OpenAI | 云端 API（您的个人账户） | 创建一个 `openai` 提供商并粘贴您的 API 密钥（保存到密钥后端，绝不包含在配置中）。请参阅 [QUICKSTART.md](QUICKSTART.md) §4 和 [SECRET_BACKENDS.md](SECRET_BACKENDS.md)。 |
| Anthropic | 云端 API（您的个人账户） | 创建一个 `anthropic` 提供商并粘贴您的 API 密钥。请参阅 [QUICKSTART.md](QUICKSTART.md) §4。 |

这些提供商代表由其各自供应商所有的外部软件/服务，并直接从他们那里获取。LLM Store 不会重新分发它们。API 密钥和代理凭据属于买家；请参阅 [SECRET_BACKENDS.md](SECRET_BACKENDS.md) 和 [AGENT_AUTHENTICATION.md](AGENT_AUTHENTICATION.md)。

**面向 Fab 的第三方软件声明：** 未包含第三方软件。

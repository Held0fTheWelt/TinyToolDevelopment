<!-- doc-provenance: AKDB:plugins/LLMStore/architecture.md; docs/architecture/plugins/LLMStore/product-facts.yml; reconciled 2026-06-20 -->
# 常见问题解答 (FAQ)

## 是否包含首次设置向导？

是的。**Setup** 标签页包含一个 **Quick-Start** 卡片。它可以一键创建完整的模拟、Ollama 或 OpenAI/Anthropic 云端堆栈（提供商、模型和 `default` 路由），运行连接测试并更新就绪状态。它不会覆盖先前创建的提供商，也不会覆盖您配置的 `default` 路由。

## LLM Store 是一个聊天机器人吗？

不是。LLM Store 是面向提供商、模型、路由、策略、密钥、成本追踪和代理的基础架构。聊天机器人或资产助手可以使用 LLM Store，但它们是独立的工具。

## 为什么应该使用路由而不是模型名称？

路由能保持功能代码的稳定。如果某个工具调用 `docs.summarize`，团队以后可以在不修改工具代码的情况下，从 Ollama 切换到 llama.cpp 或 OpenAI。

## 我可以完全在本地运行吗？

可以。使用 `ollama`、`llamacpp`、`lmstudio`、`vllm`、`tgi` 或 `mock` 等提供商，将策略设置为仅限本地，并通过构建规则拦截云端。

## 是否支持 llama.cpp？

支持。`llamacpp` 提供商类型专门用于本地 llama.cpp 服务器。典型的基准 URL 为：

```text
http://localhost:8080
```

## API 密钥会存储在项目文件中吗？

不会。`Config/LLMStore.json` 存储提供商、模型、路由和策略，但不存储密钥。密钥保留在密钥存储或环境变量中。

## 我应该使用哪个密钥后端？

对于单个开发者的设置，`EncryptedFile` 简单易用。对于团队，Windows Credential Manager、macOS Keychain、1Password 或 Azure Key Vault 通常是最佳选择。

## Blueprint 能完成 C++ 能做的所有事情吗？

面向买家的主要集成点都提供了 Blueprint 版本。这包括提供商、嵌入、策略、测试、上下文提供商、代理和子系统外观函数。

## 我可以连接 Codex、Claude 或 Cursor 吗？

可以，通过代理插件连接。商店可以统一状态、身份验证指导和任务执行。具体的工具集成保持为适配器，且必须遵循安全规则。

## LLM Store 会自动运行 Shell 命令吗？

仅当代理适配器显式实现了执行且请求标志允许时才会运行。`bAllowShellExecution`、`bAllowFileWrites` 和 `bRequireDiffPreview` 用于传达调用方的安全要求。

## 成本追踪有多准确？

准确度取决于提供商的用量数据和配置的 `CostRules`。如果提供商未返回 Token 数量，商店会估算 Token。对于账单而言，提供商的结算数据始终是首要事实来源。

## 我可以为本地模型指定成本吗？

可以。本地模型的成本可以设置为 `0`，也可以使用内部会计值（例如每 1000 Token 的估算 GPU 成本）。

## 哪些内容不直接属于 LLM Store？

具有具体功能（如资产解答、Blueprint 文档化、命名规范审查或项目 RAG）的工具应当使用 LLM Store，但它们通常位于独立的插件或扩展中。LLM Store 本身保持自洽。

## 如果提供商离线会发生什么？

商店会更新提供商的健康状态，可以尝试降级路由，并将错误记录到审计日志中。熔断器（circuit breaker）设置可以防止高成本或卡死的重复尝试。

## 我可以在 CI 中使用 LLM Store 吗？

可以。使用 `LLMStoreCIPolicy` 命令行工具和自动化测试。`Documentation/CI` 中包含针对 GitHub Actions 的示例。

## 我必须在线测试云端提供商吗？

不一定。对于版本发布安全，模拟测试、配置验证以及针对提供商的可选手动冒烟测试通常就足够了。云端测试仅应在有意配置了密钥的情况下运行。

## 我应该提交哪些文件到版本库？

请提交：

- `Config/LLMStore.json`
- 可选预设
- 生产路由的团队文档

请勿提交：

- API 密钥
- 本地密钥文件
- 包含敏感运营数据时的成本账本文件

## 我可以导出和导入完整的配置吗？

可以。治理标签页可以将当前配置导出到任何 JSON 文件中，在不应用的情况下验证 JSON 文件，并且仅在验证成功后导入 JSON 配置。导出的配置文件不包含 API 密钥。

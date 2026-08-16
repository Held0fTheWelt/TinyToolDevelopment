<!-- doc-provenance: AKDB:plugins/LLMStore/architecture.md; docs/architecture/plugins/LLMStore/product-facts.yml; reconciled 2026-06-20 -->
# LLM Store

LLM Store 是一个虚幻引擎（Unreal Engine）插件，用于集中管理 AI 提供商（providers）、模型（models）、任务路由（task routes）、策略（policies）、成本（costs）、密钥（secrets）以及可选的外部代理（agents）。它被设计为一个基础架构插件：编辑器工具和运行时系统无需关心请求是由 Ollama、llama.cpp、OpenAI、Claude、Gemini、Azure OpenAI、Mistral、OpenRouter 还是模拟（mock）提供商处理的。只需调用一个稳定的路由名称，如 `asset.explain`、`docs.summarize` 或 `naming.review`。

## 适用对象

当项目包含多个 AI 功能，且这些功能不应硬编码提供商凭据、模型名称、云端规则或成本逻辑时，LLM Store 非常有用。

典型使用场景：

- 在开发、测试、CI 或与发布相关的工作流中使用本地模型
- 允许在开发期间使用云端模型，但在发布（shipping）构建中予以拦截
- 通过稳定的任务名称而不是直接的模型名称来路由 AI 任务
- 按提供商、模型和路由评估成本
- 避免将 API 密钥提交到项目的版本控制配置文件中
- 为 C++ 和 Blueprint 团队提供相同的集成界面
- 连接可选的代理，如 Codex、Claude、Cursor 或工作室专属工具
- 允许特定于项目的插件提供上下文，而无需 LLM Store 依赖它们
- 通过 UCM 路由公开编辑器的任务历史记录，而无需依赖 Unified MCP Server

## 模块构成

| 模块 | 用途 |
| --- | --- |
| `LLMStoreInterface` | 公共结构体、外观接口、提供商契约、插件契约以及 Blueprint 基类。 |
| `LLMStore` | 引擎子系统、路由、执行、治理、密钥、成本账本（cost ledger）以及代理桥接。 |
| `LLMStoreEditor` | 用于设置、路由、状态、帮助、代理、成本和治理的编辑器标签页。 |

## 核心概念

| 概念 | 含义 |
| --- | --- |
| 提供商 (Provider) | 技术服务或本地服务器，例如 `ollama`、`llamacpp` 或 `openai`。 |
| 模型 (Model) | 由提供商提供的具体模型。 |
| 路由 (Route) | 解析为模型、降级（fallback）链和策略的稳定任务名称。 |
| 策略 (Policy) | 云端访问、仅限本地行为、上下文预算、提供商允许/拒绝列表以及成本上限的规则。 |
| 成本规则 (Cost Rule) | 用于根据提示词（prompt）和完成（completion）Token 估算请求成本的定价规则。 |
| 代理 (Agent) | 用于 Codex、Claude、Cursor 或工作室助手等外部工具的可选适配器。 |
| 上下文提供商 | 从项目源码、资产、文档或其他系统提供中立上下文包的插件。 |

## 编辑器界面

从以下位置打开插件：

```text
Tiny Tools -> LLM Store
```

主要标签页：

- `Setup`: 首次使用时的一键 **Quick-Start**（Mock / Ollama / 云端），随后进行提供商和模型的创建、基准 URL 编辑、密钥设置以及连接测试。
- `Routes`: 配置任务路由、降级链、模拟模型、提示词模板和策略。
- `Agents`: 检查 Codex、Claude、Cursor 以及自定义代理适配器，启动身份验证对话框。
- `Costs`: 分析请求、Token、估算成本、缓存命中并导出 CSV 报告。
- `Governance`: 检查状态、审计事件、预设、缓存状态和构建规则。
- `Status`: 读取当前配置状态、警告、拦截项和清单。
- `Help`: 编辑器内对概念和预期工作流的解答。
- `Advanced`: 由插件贡献的可选编辑器 UI 部分。

## 快速入门

1. 打开 `Tiny Tools -> LLM Store`。
2. 在 **Setup** 标签页中，使用 **Quick-Start** 卡片（Mock、本地 Ollama 或 OpenAI/Anthropic 云端），一键获取可用的 `default` 路由。
3. 或手动创建提供商和模型，然后在 `Routes` 标签页中添加路由。
4. 测试提供商、模型和路由，确认就绪状态横幅变为绿色。
5. 如果云端或预算分析很重要，添加成本规则。
6. 发起请求并检查 `Costs` 和 `Status` 标签页。

有关详细的分步说明（Quick-Start 卡片和手动设置），请参阅 [QUICKSTART.md](QUICKSTART.md)。

## 本地提供商

支持的本地或自托管提供商类型：

- `ollama`
- `llamacpp`
- `lmstudio`
- `vllm`
- `tgi`
- `mock`

这些提供商默认不需要 API 密钥。

## 云端提供商

支持的云端提供商类型：

- `openai`
- `anthropic`
- `gemini`
- `azure-openai`
- `mistral`
- `openrouter`

云端提供商通常需要 API 密钥。密钥存储在配置的密钥后端中，绝不写入 `Config/LLMStore.json`。

## Blueprint 与 C++

面向使用者的功能在 C++ 和 Blueprint 中均可使用。

Blueprint 基类：

- `ULLMBlueprintProviderAddOn`
- `ULLMBlueprintEmbeddingProviderAddOn`
- `ULLMBlueprintContractAddOn`
- `ULLMBlueprintPolicyAddOn`
- `ULLMBlueprintTestAddOn`
- `ULLMBlueprintContextProviderAddOn`
- `ULLMBlueprintAgentAddOn`

请参阅 [INTEGRATION.md](INTEGRATION.md) 和 [CodeDocumentation.md](CodeDocumentation.md)。

带有和不带有流式传输（streaming）的路由执行共享一个受并发控制的队列。对于长时间运行的本地任务，使用 `EnqueueRoute`；`ExecuteRouteStreaming` 遵循相同的生活任务保护，同时通过其回调 API 返回流式数据块。

## 代理身份验证

`Agents` 标签页可以为每个代理显示 `Authenticate...` 按钮。对话框包含登录命令、说明、帮助链接以及运行或复制命令的操作。凭据保留在外部工具端，LLM Store 仅保留状态和说明。

请参阅 [AGENT_AUTHENTICATION.md](AGENT_AUTHENTICATION.md)。

## 成本追踪

LLM Store 根据以下内容估算成本：

- 提供商报告或商店估算的提示词 Token
- 提供商报告或商店估算的完成 Token
- 匹配的 `FLLMCostRule` 条目

成本账本存储在：

```text
Saved/LLMStore/CostLedger.json
```

CSV 导出默认保存到：

```text
Saved/LLMStore/CostReports/LLMStoreCostReport.csv
```

请参阅 [COST_TRACKING.md](COST_TRACKING.md)。

## 隐私与安全

- API 密钥不得包含在 `Config/LLMStore.json` 中。
- 本地提供商是敏感项目数据的首选默认项。
- 策略可以按路由限制云端的使用。
- 构建规则可以拦截发布构建中的云端提供商。
- 代理的执行是显式的，并由请求标志控制。

有关加密本地文件、Windows Credential Manager、macOS Keychain、1Password 和 Azure Key Vault 的信息，请参阅 [SECRET_BACKENDS.md](SECRET_BACKENDS.md)。

## 从这里开始

- [BUYER_GUIDE.md](BUYER_GUIDE.md): 面向买家的概述、价值主张和实用工作流。
- [QUICKSTART.md](QUICKSTART.md): 首个可用的提供商/模型/路由设置。
- [UserManual.md](UserManual.md): 完整的编辑器工作流和 UI 使用指南。
- [FAQ.md](FAQ.md): 面向 Fab 买家的问答。

## 参考指南

- [SettingsReference.md](SettingsReference.md): 配置字段、默认值、配置 JSON 和推荐基线。
- [ProviderReference.md](ProviderReference.md): 支持的本地/云端提供商类型、基准 URL 和说明。
- [RoutePolicyReference.md](RoutePolicyReference.md): 路由策略、云端/本地限制、预算规则和构建规则。
- [COST_TRACKING.md](COST_TRACKING.md): 成本账本、成本规则、CSV 导出和分析工作流。
- [SECRET_BACKENDS.md](SECRET_BACKENDS.md): 加密本地存储和外部密钥后端的行为。
- [AGENT_AUTHENTICATION.md](AGENT_AUTHENTICATION.md): Codex/Claude/Cursor 风格的代理适配器和身份验证对话框行为。
- [INTEGRATION.md](INTEGRATION.md): 面向其他插件的 C++ 和 Blueprint 集成模式。
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md): 常见问题与解决方案。
- [TechnicalOverview.md](TechnicalOverview.md): 维护者级别的架构概述。

## 包含的资产

- [Screenshots/](Screenshots): 文档截图和可视化工作流图。

## 视觉说明

- [Screenshots/01-workflow-overview.svg](Screenshots/01-workflow-overview.svg)
- [Screenshots/02-editor-tabs.svg](Screenshots/02-editor-tabs.svg)
- [Screenshots/03-agent-cost-governance.svg](Screenshots/03-agent-cost-governance.svg)

## 配置 JSON 快速工作流

1. 打开 `Tiny Tools -> LLM Store`。
2. 配置提供商、模型、路由、策略和成本规则。
3. 打开 `Governance`。
4. 使用 `Export Setup JSON` 将当前配置保存到选择的任何文件中。
5. 使用 `Validate JSON` 在不应用的情况下检查配置文件。
6. 仅在验证成功后使用 `Import JSON`。

密钥绝不会写入配置 JSON。在导入共享配置后，通过密钥后端或环境变量重新连接提供商密钥。

## UCM 任务可见性

当启用了 Unreal Capability Mesh 时，LLM Store 会通过 `llmstore.editor.jobs.list.v1` 和 `llmstore.editor.jobs.status.v1` 以只读方式公开编辑器的任务历史记录。Unified MCP Server 可以通过 `jobs_list` / `jobs_status` 聚合这些路由；LLM Store 本身保持自洽，不需要对 UMCP 的编译时依赖。

## 命令行工具 (Commandlet)

从本地终端或自动化运行器运行 CI 策略检查：

```powershell
<UnrealEditorCommand> "D:\PluginProjectGit\PluginProject.uproject" -run=LLMStoreCIPolicy -unattended -nop4 -nosplash -NoShaderCompile
```

`<UnrealEditorCommand>` 是针对本地引擎安装的虚幻编辑器命令行目标。

该命令行工具会检查配置的提供商、模型、路由、策略和构建规则。它旨在用于版本发布治理，而不是实时提供商基准测试。

<!-- doc-provenance: AKDB:plugins/LLMStore/architecture.md; docs/architecture/plugins/LLMStore/product-facts.yml; reconciled 2026-06-20 -->
# 用户手册

本手册从买家、技术美术、Blueprint 开发者或工具程序员的角度介绍 LLM Store。它解释了编辑器的工作流，并在需要时指向更深入的技术参考。

## 插件目标

LLM Store 是虚幻引擎项目的中枢 AI 控制层。其他插件和工具无需关心提示词是发送到 Ollama、llama.cpp、OpenAI、Claude、Gemini、Azure OpenAI、Mistral、OpenRouter 还是模拟测试。它们只需调用稳定的任务路由，例如：

```text
docs.summarize
asset.explain
naming.review
rag.embed
agent.patch
```

路由决定了提供商、模型、降级（fallback）、策略、成本规则和密钥后端。

## 打开编辑器

打开：

```text
Tiny Tools -> LLM Store
```

该标签页旨在满足日常使用需求。它不仅显示基础设置，还引导完成安装、路由、状态、帮助、代理、成本和治理。

## 首次设置

### Quick-Start 卡片（最快路径）

1. 打开 `Tiny Tools -> LLM Store`。
2. 转到 `Setup`。顶部的 **Quick Start — get running in one click** 区域即可见。
3. 选择一个选项：
   - **Just try it (Mock)** — 完全离线；无需 API 密钥；非常适合 CI 和首次体验。
   - **Local (Ollama)** — 在 `localhost:11434` 上创建 `quickstart_ollama`；测试前请启动 Ollama。
   - **Create OpenAI** 或 **Create Anthropic** — 将 API 密钥粘贴到密码字段中并点击提供商按钮。密钥仅保存到密钥后端。
4. 阅读按钮下方的状态行和标签页上方的就绪状态横幅。
5. 如果就绪状态为绿色，仅当您需要另一个初始堆栈时才再次展开 Quick-Start 区域（现有的 `quickstart_*` 条目不会重复，您自己的 `default` 路由也绝不会被覆盖）。

初始堆栈使用稳定的 ID（`quickstart_mock`、`quickstart_ollama`、`quickstart_openai`、`quickstart_anthropic`），并且除非已经定义，否则始终连接 `default` 任务路由。

### 手动设置（完全控制）

1. 打开 `Tiny Tools -> LLM Store`。
2. 转到 `Setup`（位于 Quick-Start 卡片下方）。
3. 创建一个提供商，例如 `ollama`、`llamacpp`、`openai` 或 `anthropic`。
4. 确认默认的基准 URL 是否合适。
5. 为提供商创建模型。
6. 转到 `Routes`。
7. 创建一个路由，例如 `docs.summarize`。
8. 选择首选模型。
9. 点击 `Test Route`。
10. 检查 `Status` 以确认警告或拦截。

## 提供商配置

提供商描述的是技术服务，而不是模型本身。

| 字段 | 含义 |
| --- | --- |
| `Id` | 项目本地稳定的 ID，例如 `local-ollama`。 |
| `DisplayName` | UI 和报告中可读的显示名称。 |
| `Type` | 提供商类型，例如 `ollama`、`llamacpp` 或 `openai`。 |
| `BaseUrl` | HTTP 端点。已知提供商会获得有用的默认值。 |
| `Enabled` | 在不删除配置的情况下禁用提供商。 |
| `RetryCount` | 针对临时错误的重试次数。 |
| `TimeoutSeconds` | 提供商特定的超时限制。 |
| `CircuitBreaker...` | 针对重复故障或卡死服务器的熔断保护。 |

本地提供商通常不需要密钥。云端提供商通常需要在密钥存储中提供密钥。

## 已知提供商

| 提供商类型 | 默认基准 URL | 主要用途 |
| --- | --- | --- |
| `ollama` | `http://localhost:11434` | 通过 Ollama 使用本地模型。 |
| `llamacpp` | `http://localhost:8080` | 使用 llama.cpp 服务器进行本地推理。 |
| `lmstudio` | `http://localhost:1234/v1` | 来自 LM Studio 的本地模型。 |
| `vllm` | `http://localhost:8000/v1` | 高性能本地或服务器推理。 |
| `tgi` | `http://localhost:8080` | Hugging Face Text Generation Inference。 |
| `openai` | `https://api.openai.com/v1` | OpenAI API。 |
| `anthropic` | `https://api.anthropic.com` | Claude API。 |
| `gemini` | `https://generativelanguage.googleapis.com/v1beta` | Google Gemini API。 |
| `azure-openai` | 特定于项目 | Azure 端点和部署逻辑。 |
| `mistral` | `https://api.mistral.ai/v1` | Mistral API。 |
| `openrouter` | `https://openrouter.ai/api/v1` | 多个云端模型的路由器。 |
| `mock` | 空 | 测试、UI 开发、CI 和离线工作。 |

## 模型

一个模型属于单个提供商。

| 字段 | 含义 |
| --- | --- |
| `Id` | 项目本地稳定的模型 ID。 |
| `Name` | 提供商端的网络名称，例如 `llama3.1:8b` 或 `gpt-4o-mini`。 |
| `ProviderId` | 提供该模型的提供商。 |
| `Role` | 可选角色，例如 `fast`、`reasoning`、`embedding` 或 `local`。 |
| `Structured` | 标记预期能很好地处理 JSON / 架构输出的模型。 |
| `TimeoutSeconds` | 模型特定的超时限制。 |
| `Enabled` | 在不删除路由的情况下禁用模型。 |

## 路由

路由是商店中最核心的概念。功能请求的是任务，而不是模型。

示例：

```text
TaskKind: docs.summarize
PreferredModelId: local-fast
FallbackModelIds:
  - cloud-reasoning
  - mock-docs
Policy: local-only for shipping
```

优势：

- 当模型更改时，功能代码保持稳定
- 可以按任务应用策略
- 降级链可以结合本地、云端和模拟模型
- 可以按任务分析成本
- CI 可以在无需了解每个工具的情况下验证路由策略

## 测试路由

在 `Routes` 标签页中使用 `Test Route`。测试会检查：

- 路由是否存在？
- 路由是否已启用？
- 模型是否存在？
- 提供商是否存在？
- 提供商是否已启用？
- 所需的密钥是否存在？
- 提供商是否响应简短提示词？

错误会显示在状态区域和提供商的健康面板中。

## 策略 (Policies)

策略决定了路由是否可以使用。

典型规则：

- 禁止在敏感数据上使用云端
- 发布构建中仅允许本地模型
- 设置最大上下文预算
- 设置每次请求的最大成本
- 允许或拒绝特定的提供商类型

策略应在 LLM Store 中配置。另一个插件可以提供上下文或调用路由，但集中治理的决策保留在商店内。

## 代理

`Agents` 标签页显示可选的适配器，例如 Codex、Claude、Cursor 或自定义工作室工具。

| 状态 | 含义 |
| --- | --- |
| `NotInstalled` | 未找到工具。 |
| `Installed` | 工具存在，身份验证不确定或缺失。 |
| `AuthRequired` | 必须完成身份验证。 |
| `Available` | 工具已准备就绪。 |
| `Disabled` | 适配器已被禁用。 |
| `Error` | 适配器报告错误。 |

`Authenticate...` 按钮会打开一个包含命令、说明、帮助链接以及手动作业复制操作的对话框。LLM Store 不会存储外部工具的凭据。

## 成本分析

`Costs` 标签页收集并分析成本账本（cost ledger）。

它显示：

- 总事件数
- 成功事件数
- 缓存命中数
- 提示词（prompt）Token
- 完成（completion）Token
- 估算成本
- 按提供商、模型和路由划分的明细
- CSV 导出

成本的精确度取决于提供商的用量数据和配置的成本规则。本地模型可以保持为免费，也可以分配内部硬件成本。

## 密钥存储 (Secret Store)

API 密钥不得包含在 `Config/LLMStore.json` 中。

支持的后端：

- 加密的本地文件
- Windows Credential Manager
- macOS Keychain
- 1Password CLI
- 通过 Azure CLI 使用 Azure Key Vault

环境变量具有优先权：

```text
LLMSTORE_<PROVIDER_ID>_KEY
```

示例：

```text
LLMSTORE_OPENAI_MAIN_KEY
```

## Status 标签页

`Status` 标签页回答了：“目前可以使用我的商店吗？”

它显示：

- 全局就绪状态
- 拦截项
- 警告
- 提供商清单
- 缺失的密钥
- 禁用的提供商或模型
- 路由问题

在与团队共享配置、运行 CI 或打包版本之前，请检查此标签页。

## 导出、验证与导入配置 JSON

`Governance` 标签页包含配置 JSON 操作，用于共享或迁移完整的 LLM Store 配置。

可用操作：

| 操作 | 用途 |
| --- | --- |
| `Export Setup JSON` | 选择任何文件夹和文件名，将当前配置保存为 JSON。不包含密钥。 |
| `Validate JSON` | 选择一个 JSON 文件，在不应用的情况下检查架构、提供商 ID、模型引用、路由和警告。 |
| `Import JSON` | 选择一个 JSON 文件，仅在验证成功后进行验证并应用。 |

导入器同时接受 LLM Store 的包覆配置格式和解包的 `FLLMStoreConfig` JSON 对象。这使其非常适合预设、备份、团队间交接文件以及手动审查的配置快照。

## Help 标签页

`Help` 标签页在编辑器内直接解答：

- 什么是提供商
- 什么是模型
- 为什么使用路由而不是直接的模型名称
- 本地和云端提供商如何协同工作
- 策略和构建规则如何应用
- 成本追踪衡量什么
- 代理如何连接

帮助部分内置于插件中，买家无需在网站、README 和编辑器 UI 之间切换即可理解基本概念。

## 在 Blueprint 中使用

面向使用者的核心集成点在 Blueprint 中均可用。

| 类 | 用途 |
| --- | --- |
| `ULLMBlueprintProviderAddOn` | 从 Blueprint 连接提供商。 |
| `ULLMBlueprintEmbeddingProviderAddOn` | 从 Blueprint 连接嵌入提供商。 |
| `ULLMBlueprintContractAddOn` | 验证模型契约。 |
| `ULLMBlueprintPolicyAddOn` | 在运行时允许或拒绝路由。 |
| `ULLMBlueprintTestAddOn` | 添加设置测试或健康检查。 |
| `ULLMBlueprintContextProviderAddOn` | 将项目上下文作为上下文包提供。 |
| `ULLMBlueprintAgentAddOn` | 连接外部 CLI 或编辑器助手。 |

## 在 C++ 中使用

C++ 用户从引擎子系统获取商店：

```cpp
ULLMStoreSubsystem* Store = GEngine->GetEngineSubsystem<ULLMStoreSubsystem>();
```

随后可以解析路由、执行请求、创建上下文包、调用代理和读取成本报告。

请参阅 [INTEGRATION.md](INTEGRATION.md) 和 [CodeDocumentation.md](CodeDocumentation.md)。

## 推荐工作流

### 本地开发

1. 创建 `ollama` 或 `llamacpp` 提供商。
2. 添加本地模型。
3. 将路由指向本地模型。
4. 通过策略禁用云端。
5. 保留一个 `mock` 路由用于测试。

### 混合开发

1. 对快速任务使用本地模型。
2. 对更复杂的任务添加云端降级。
3. 设置成本上限。
4. 定期检查成本追踪。
5. 将发布构建规则保持为仅限本地/模拟。

### 团队设置

1. 将 `Config/LLMStore.json` 提交到版本库。
2. 不要提交密钥。
3. 记录密钥后端。
4. 导出预设。
5. 检查 `Status` 标签页。
6. 启用 CI 策略检查。

## 限制

LLM Store 不是一个完成的资产解答工具、Blueprint 审查工具或 RAG 产品。它提供路由、提供商、策略、成本追踪、密钥和接口。具有具体功能的工具可以连接到它，而无需 LLM Store 依赖它们。

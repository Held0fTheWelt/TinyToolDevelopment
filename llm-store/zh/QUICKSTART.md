<!-- doc-provenance: AKDB:plugins/LLMStore/architecture.md; docs/architecture/plugins/LLMStore/product-facts.yml; reconciled 2026-06-20 -->
# 快速入门

本指南介绍如何在 LLM Store 中配置首个可用的路由。

## 1. 打开编辑器标签页

打开：

```text
Tiny Tools -> LLM Store
```

顶部区域会汇总显示已加载的提供商、模型、路由、嵌入路由、就绪状态以及估算成本信息。

## 2. 使用 Quick-Start 卡片（首次使用推荐）

在 **Setup** 标签页中，**Quick Start** 卡片会显示在提供商和模型区域上方。选择一个选项：

| 按钮 | 创建内容 | API 密钥 |
| --- | --- | --- |
| **Just try it (Mock)** | 离线模拟提供商、模型和 `default` 路由 | 无 |
| **Local (Ollama)** | 位于 `http://localhost:11434` 的 Ollama，默认模型 `llama3`，`default` 路由 | 无（Ollama 必须正在运行） |
| **Create OpenAI** | OpenAI 提供商，模型 `gpt-4o-mini`，`default` 路由 | 粘贴密钥到字段中（仅保存到密钥存储） |
| **Create Anthropic** | Anthropic 提供商，模型 `claude-3-5-haiku-latest`，`default` 路由 | 粘贴密钥到字段中（仅保存到密钥存储） |

点击按钮后，LLM Store 会：

1. 幂等应用初始集合（稳定的 `quickstart_*` ID；绝不会覆盖您现有的提供商或您配置的 `default` 路由）。
2. 如果提供了云端 API 密钥，则通过 `SetProviderKey` 保存（绝不写入 `Config/LLMStore.json`）。
3. 运行 **Test Connection** 并更新就绪状态横幅。

当就绪状态已经是绿色时，卡片会折叠，显示简短标题“ready — expand to run Quick-Start again”。

对于自定义 URL、额外模型或特定任务的路由，请继续执行下面的手动步骤。

## 3. 创建本地提供商（手动）

本地提供商是最简单的初始测试，因为它不需要 API 密钥。

### 选项 A: Ollama

1. 在本地启动 Ollama。
2. 拉取模型：

```text
ollama pull llama3.1
```

3. 在 `Setup` 中创建提供商：

```text
Id: ollama-local
DisplayName: Ollama Local
Type: ollama
BaseUrl: http://127.0.0.1:11434
Enabled: true
```

4. 创建模型：

```text
Id: local-chat
Name: llama3.1
DisplayName: Local Chat
ProviderId: ollama-local
Role: fast
Enabled: true
```

### 选项 B: llama.cpp

启动本地 llama.cpp 服务器：

```text
llama-server -m C:\Models\model.gguf --host 127.0.0.1 --port 8080
```

然后创建：

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

## 4. 创建云端提供商（手动）

云端提供商通常需要 API 密钥。密钥保存在密钥后端中，而不是 `Config/LLMStore.json`。

示例：

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

然后在提供商区域设置密钥，或通过环境变量设置：

```text
LLMSTORE_OPENAI_MAIN_KEY
```

## 5. 创建路由

在 `Routes` 标签页中创建路由：

```text
TaskKind: docs.summarize
PreferredModelId: local-chat
FallbackModelIds:
  - openai-fast
MockModelId: mock-docs
bUseMock: false
```

如果从 llama.cpp 开始，请使用 `local-llamacpp` 作为首选模型。

## 6. 添加策略 (Policy)

对于本地优先的安全路由：

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

对于混合开发路由，允许云端并添加成本限制：

```text
bAllowCloud: true
bLocalOnly: false
MaxEstimatedCost: 0.05
```

## 7. 测试提供商、模型和路由

使用编辑器中的测试按钮。

如果路由无法解析，请检查：

- 提供商是否已启用？
- 模型是否已启用？
- 模型是否引用了正确的提供商？
- 路由是否使用了正确的模型 ID？
- 是否为云端提供商设置了 API 密钥？
- 本地服务器是否正在运行？
- 策略是否允许选定的提供商类型？

## 8. 添加成本规则

定义定价规则后，`Costs` 标签页非常有用。

示例：

```text
ProviderType: openai
ModelId: openai-fast
InputCostPer1KTokens: 0.00015
OutputCostPer1KTokens: 0.00060
Currency: USD
```

本地提供商可以保持为 `0` 或使用内部成本模型。

## 9. 发起请求

发起请求后，`Costs` 标签页会显示：

- 事件数量
- 成功数量
- 缓存命中数
- 提示词 Token
- 完成 Token
- 估算成本
- 按提供商/模型/任务划分的明细
- 最近的事件

使用 `Export CSV` 将报告保存到：

```text
Saved/LLMStore/CostReports
```

## 10. 检查状态

打开 `Status` 标签页。`Attention` 区域最为重要，因为它会显示缺失的密钥、损坏的路由、禁用的提供商和策略问题。

## 11. 可选的代理设置

要连接 Codex、Claude、Cursor 或自定义代理：

1. 打开 `Agents` 标签页。
2. 选择代理。
3. 点击 `Authenticate...`。
4. 使用 `Copy Command` 并手动在终端中运行该命令。
5. 刷新状态。

示例：

```text
codex login
claude auth login
```

LLM Store 不会存储代理凭据。

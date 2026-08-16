<!-- doc-provenance: AKDB:plugins/LLMStore/architecture.md; docs/architecture/plugins/LLMStore/product-facts.yml; reconciled 2026-06-20 -->
# 故障排除

本指南列出了与 LLM Store 的配置、运行时、UI、策略和构建相关的常见问题。

## 未显示 LLM Store 菜单项

检查项：

- 插件已启用
- 启用插件后重启了编辑器
- `LLMStoreEditor` 模块已编译
- 您正在运行 Unreal Editor 而不是烘焙（cooked）的运行时构建

预期的位置：

```text
Tiny Tools -> LLM Store
```

## 提供商无法访问

检查项：

- 提供商已启用
- 基准 URL 正确
- 本地服务器正在运行
- 防火墙或代理未拦截请求
- 超时设置足够长
- 提供商类型与服务器匹配

常见的本地默认值：

| 提供商 | 默认值 |
| --- | --- |
| `ollama` | `http://127.0.0.1:11434` |
| `llamacpp` | `http://127.0.0.1:8080` |
| `lmstudio` | `http://127.0.0.1:1234/v1` |
| `vllm` | `http://127.0.0.1:8000/v1` |
| `tgi` | `http://127.0.0.1:8080/v1` |

请先尝试 `Test Provider`，接着尝试 `Test Model`，最后尝试 `Test Route`。

## 路由无法解析

检查项：

- 路由的 `TaskKind` 拼写与要求完全一致
- 路由已启用
- 首选模型存在
- 模型已启用
- 模型引用了存在的提供商
- 提供商已启用
- 如有需要，云端密钥存在
- 路由策略允许该提供商类型
- 构建/运行时模式未拒绝该路由

如果启用了 `bUseMock`，请确认 `MockModelId` 存在。

## 缺失 API 密钥

密钥不会保存在 `Config/LLMStore.json` 中。

请使用以下方式之一：

- 编辑器中的提供商密钥字段
- 环境变量覆盖
- 配置的密钥后端

环境变量格式：

```text
LLMSTORE_<PROVIDER_ID>_KEY
```

示例：

```text
ProviderId: openai-main
Variable: LLMSTORE_OPENAI_MAIN_KEY
```

## 环境变量被忽略

检查项：

- 变量名使用了正规化的提供商 ID
- 设置变量后重启了编辑器进程
- 启动虚幻引擎的进程可以看到该变量
- 值中没有隐藏的空格

在 Windows 上，通过系统设置修改环境变量通常需要重启启动器或终端。

## Windows Credential Manager 无法工作

检查项：

- 在 Windows 上运行
- 插件构建链接了 `Advapi32`
- 凭据目标名称与生成的提供商密钥名称匹配
- 用户账户拥有权限
- 提供商 ID 未发生更改

如有疑问，请设置临时环境变量以确认提供商的其余配置。

## macOS Keychain 无法工作

检查项：

- `security` 命令可用
- 钥匙串已解锁
- 进程拥有读取该条目的权限
- 生成的密钥名称与预期的值匹配

## 1Password 后端无法工作

检查项：

- `op` CLI 已安装
- 在同一终端上下文里 `op whoami` 成功
- `Vault` 已设置或 `SecretBackend.Meta` 包含完整的 `op://...` 引用
- 特定于提供商的覆盖项指向了正确的条目和字段

## Azure Key Vault 后端无法工作

检查项：

- `az` CLI 已安装
- `az account show` 成功
- `Vault` 是正确的 Key Vault 名称
- 当前身份拥有密钥的 get/set/delete 权限
- 特定于提供商的覆盖项与密钥名称匹配

## 云端提供商失败但本地提供商成功

检查项：

- API 密钥存在
- 基准 URL 与提供商文档匹配
- 提供商端的模型名称正确
- 账户拥有该模型的访问权限
- 请求未被组织策略拦截
- 路由的成本策略未拒绝该请求

检查提供商的健康状态和最近的审计事件。

## llama.cpp 无响应

检查项：

- `llama-server` 正在运行
- 主机和端口与 `BaseUrl` 匹配
- 服务器暴露了兼容 OpenAI 的端点
- 模型已加载
- 请求超时时间足够长

典型启动方式：

```text
llama-server -m C:\Models\model.gguf --host 127.0.0.1 --port 8080
```

提供商配置：

```text
Type: llamacpp
BaseUrl: http://127.0.0.1:8080
```

## Ollama 无响应

检查项：

```text
ollama list
ollama serve
```

确保 `FLLMModelConfig.Name` 中的模型存在于 Ollama 中。

## 结构化 JSON 无效

检查项：

- 路由使用了适合结构化输出的模型
- 工作流需要时在模型上设置了 `bStructured`
- 仅在必要时 `FLLMStructuredOutputSpec.bRequireJson` 为 true
- 架构是有效的 JSON
- 提示词未要求在 JSON 周围包含纯文本

某些本地模型需要更严格的提示词才能生成有效的 JSON。

## 缺失工具调用 (Tool Calls)

检查项：

- 提供商支持工具调用
- `FLLMToolSpec.ParametersJsonSchema` 有效
- 模型支持工具
- 提供商适配器将工具规范映射到了提供商的网络格式

## 流式传输仅输出单个数据块

某些提供商不支持原生流式传输，或者当前的适配器只能解析完整的响应。这是被允许的。流式 API 会发出单个最终数据块，从而允许用户使用单一的代码路径。

## 成本显示为零

检查项：

- 存在成本规则
- 提供商类型与规则匹配
- 模型 ID 与规则匹配或规则中的模型 ID 为空
- 提供商报告了用量或启用了 Token 估算
- 请求未完全由零成本的本地模型处理

## 成本报告看起来过高

检查项：

- 成本单位是每 1000 Token
- 输入和输出值未颠倒
- 货币保持一致
- 模型特定规则未与更通用的规则重复
- 提供商用量数据未以另一种单位表示

## 代理未安装

检查项：

- CLI 或 IDE 已安装
- 工具命令存在于 `PATH` 中
- 虚幻引擎是从能够看到该命令的环境中启动的
- 适配器健康检查知道正确的命令名称

有关设置说明，请使用 `Authenticate...` 对话框。

## 代理身份验证无法工作

请尝试以下步骤：

1. 点击 `Copy Command`。
2. 在常规终端中运行该命令。
3. 完成登录。
4. 重启虚幻引擎或刷新代理状态。

LLM Store 不会存储凭据。它仅展示并复制外部登录命令。

## 代理拒绝文件写入

检查 `FLLMAgentRequest`：

```text
bAllowFileWrites
bAllowShellExecution
bRequireDiffPreview
```

当请求不允许时，适配器必须拒绝写入或 Shell 命令。

## 发布（Shipping）策略失败

检查项：

- 针对 `Shipping` 的 `BuildRules`
- 路由策略
- 云端提供商的使用情况
- 本地或模拟降级的可用性
- 提供商允许列表

在本地运行命令行工具：

```text
<UnrealEditorCommand> Project.uproject -run=LLMStoreCIPolicy -Config=Shipping -Unattended -NoSplash -NoSound
```

## 配置状态不明确

打开 `Status` 标签页。它会汇总提供商、模型、路由、拦截项、警告、缺失的密钥和清单。

如果状态看起来已过期：

- 如果可用，点击重新加载
- 关闭并重新打开标签页
- 重启编辑器
- 检查 `Config/LLMStore.json` 是否被手动修改过

## 因 Live Coding 激活导致构建失败

在虚幻引擎中，当编辑器正在运行时，Live Coding 可能会拦截完整的外部构建。在从命令行执行完整构建之前，请关闭编辑器或禁用 Live Coding。

这不会影响 UI 的正常使用，但可能会拦截 CI 类型的构建或 UHT 验证。

## 实用参考

- 首次设置：[QUICKSTART.md](QUICKSTART.md)
- 提供商详情：[ProviderReference.md](ProviderReference.md)
- 路由策略：[RoutePolicyReference.md](RoutePolicyReference.md)
- 密钥：[SECRET_BACKENDS.md](SECRET_BACKENDS.md)
- 成本：[COST_TRACKING.md](COST_TRACKING.md)
- 集成：[INTEGRATION.md](INTEGRATION.md)
- CI：[CommandletAndCI.md](CommandletAndCI.md)

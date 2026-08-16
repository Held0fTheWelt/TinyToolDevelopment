<!-- doc-provenance: AKDB:plugins/LLMStore/architecture.md; docs/architecture/plugins/LLMStore/product-facts.yml; reconciled 2026-06-20 -->
# 设置参考

本参考指南描述了 LLM Store 使用的主要配置数据。

项目配置路径：

```text
Config/LLMStore.json
```

密钥不会保存保存在此文件中。

## 配置 JSON 文件

治理 UI 可以从选择的任何文件夹导出、验证和导入配置 JSON 文件。

导出的包覆格式包含：

| 字段 | 含义 |
| --- | --- |
| `Format` | `LLMStoreSetup`。 |
| `FormatVersion` | 配置 JSON 格式的版本。 |
| `SetupName` | 用户可读的配置名称。 |
| `ExportedUtc` | 导出的 UTC 时间戳。 |
| `Config` | 嵌套的 `FLLMStoreConfig` 对象。 |

导入器也接受解包的原始 `FLLMStoreConfig` JSON 对象以确保兼容性。

## FLLMStoreConfig

| 字段 | 类型 | 含义 |
| --- | --- | --- |
| `Providers` | `TArray<FLLMProviderConfig>` | 已知提供商。 |
| `Models` | `TArray<FLLMModelConfig>` | 提供商提供的模型。 |
| `Routes` | `TArray<FLLMTaskRoute>` | 对话/工具/重排序任务的路由。 |
| `EmbeddingRoutes` | `TArray<FLLMStoreEmbeddingRoute>` | 嵌入专属路由。 |
| `RoutePolicies` | `TArray<FLLMRoutePolicy>` | 全局或任务专属策略。 |
| `PromptTemplates` | `TArray<FLLMPromptTemplate>` | 可复用的提示词模板。 |
| `CostRules` | `TArray<FLLMCostRule>` | 用于成本追踪的定价规则。 |
| `BuildRules` | `TArray<FLLMBuildConfigRule>` | 用于构建配置的治理。 |
| `SecretBackend` | `FLLMSecretBackendConfig` | 当前激活的密钥后端。 |
| `Modes` | `FLLMRuntimeModes` | 运行时配置文件的标签。 |

## FLLMProviderConfig

| 字段 | 含义 |
| --- | --- |
| `Id` | 项目本地稳定的提供商键。 |
| `DisplayName` | UI 和报告中可读的显示名称。 |
| `Type` | 提供商类型，例如 `openai`、`ollama` 或 `llamacpp`。 |
| `BaseUrl` | 服务器或 API 端点。 |
| `bEnabled` | 禁用提供商而不删除它。 |
| `Meta` | 特定于提供商的元数据，例如 Azure 部署名称。 |
| `RetryCount` | 针对临时错误的重试次数。 |
| `TimeoutSeconds` | 提供商特定超时；`0` 表示使用默认值。 |
| `CircuitBreakerFailureThreshold` | 熔断器打开前的失败次数。 |
| `CircuitBreakerCooldownSeconds` | 打开后重试前的冷却时间（秒）。 |

## FLLMModelConfig

| 字段 | 含义 |
| --- | --- |
| `Id` | 项目本地稳定的模型键。 |
| `Name` | 提供商端的模型名称。 |
| `DisplayName` | UI 中可读的显示名称。 |
| `ProviderId` | 引用 `FLLMProviderConfig.Id`。 |
| `Role` | 可选角色，例如 `fast`、`reasoning`、`local` 或 `embedding`。 |
| `bStructured` | 标记预期能很好地处理结构化 JSON 输出的模型。 |
| `TimeoutSeconds` | 特定于模型的超时。 |
| `bEnabled` | 禁用模型而不删除它。 |

## FLLMTaskRoute

| 字段 | 含义 |
| --- | --- |
| `TaskKind` | 稳定的任务名称，例如 `docs.summarize`。 |
| `PreferredModelId` | 此路由首先尝试的模型。 |
| `FallbackModelId` | 传统的单个降级模型。 |
| `FallbackModelIds` | 有序的降级链。 |
| `MockModelId` | 用于模拟模式的模型。 |
| `bUseMock` | 强制使用模拟模式。 |
| `WorkflowScope` | 可选作用域，例如 `Editor`、`CI` 或 `Runtime`。 |
| `PromptTemplateId` | 此路由的默认模板。 |
| `Policy` | 特定于路由的策略。 |
| `bEnabled` | 禁用路由。 |

## FLLMRoutePolicy

| 字段 | 含义 |
| --- | --- |
| `TaskKind` | 为空时可被工具用作全局策略；否则特定于任务。 |
| `bAllowCloud` | 可以使用云端提供商类型。 |
| `bLocalOnly` | 仅允许本地或模拟提供商。 |
| `MaxContextTokens` | 最大上下文预算；`0` 表示不限制。 |
| `MaxEstimatedCost` | 每次请求的最大估算成本；`0` 表示不限制。 |
| `AllowedProviderTypes` | 提供商类型的允许列表。 |
| `DeniedProviderTypes` | 提供商类型的拒绝列表。 |

## FLLMStoreEmbeddingRoute

| 字段 | 含义 |
| --- | --- |
| `RouteId` | 稳定的嵌入路由 ID。 |
| `TaskKind` | 任务，例如 `docs.embed`。 |
| `ProviderId` | 嵌入提供商。 |
| `ModelId` | 嵌入模型。 |
| `Dimensions` | 预期的向量维度；`0` 表示使用提供商默认值。 |
| `bEnabled` | 路由是否激活。 |
| `bLocalOnly` | 倾向或要求本地执行。 |
| `bAllowFallback` | 可以使用降级路由。 |
| `FallbackRouteIds` | 嵌入的降级路由。 |
| `AllowedRuntimeModes` | 可选的运行时配置文件允许列表。 |

## FLLMCostRule

| 字段 | 含义 |
| --- | --- |
| `ProviderType` | 规则涵盖的提供商类型。 |
| `ModelId` | 可选的模型 ID；为空时广泛适用。 |
| `InputCostPer1KTokens` | 每 1000 个提示词 Token 的价格。 |
| `OutputCostPer1KTokens` | 每 1000 个完成 Token 的价格。 |
| `Currency` | 货币标签，默认为 `USD`。 |

## FLLMSecretBackendConfig

| 字段 | 含义 |
| --- | --- |
| `Backend` | `EncryptedFile`、`WindowsCredentialManager`、`MacOSKeychain`、`OnePassword` 或 `AzureKeyVault`。 |
| `Vault` | 密钥库、钥匙串或后端特定命名空间名称。 |
| `KeyPrefix` | 生成密钥名称的前缀。 |
| `Meta` | 后端特定的提供商覆盖项。 |

## FLLMBuildConfigRule

| 字段 | 含义 |
| --- | --- |
| `BuildConfiguration` | 虚幻配置，例如 `Development`、`Test` 或 `Shipping`。 |
| `bAllowCloud` | 此配置中是否允许云端提供商。 |
| `bRequireLocalOrMock` | 是否每个路由都必须包含本地或模拟路径。 |
| `AllowedProviderTypes` | 此配置中允许的提供商类型。 |

## FLLMRuntimeModes

| 字段 | 含义 |
| --- | --- |
| `GenerationMode` | 自由格式标签，例如 `Local`、`Hybrid` 或 `Cloud`。 |
| `RetrievalMode` | 用于检索/RAG 行为的自由格式标签。 |
| `ValidationMode` | 用于验证/审查行为的自由格式标签。 |
| `RuntimeProfile` | 总体配置文件，例如 `LocalOnly`、`OpenAICloud` 或 `Hybrid`。 |

## FLLMPromptTemplate

| 字段 | 含义 |
| --- | --- |
| `Id` | 模板键。 |
| `Description` | 面向 UI 和团队成员的上下文说明。 |
| `Template` | 包含变量的提示词文本。 |
| `Variables` | 预期的变量名称。 |

## 团队建议

- 将 `Config/LLMStore.json` 提交到版本库。
- 不要提交 API 密钥。
- 使用 `SecretBackend` 使团队期望保持透明。
- 使用 `BuildRules` 尽早捕获打包错误。
- 在实际使用云端之前添加 `CostRules`。
- 记录每个生产路由的负责人、用途和数据分类。

## 编辑器开发者设置

编辑器的偏好设置位于 **Editor Settings -> Plugins -> LLM Store**，并与 `Config/LLMStore.json` 分开保存。

| 字段 | 默认值 | 含义 |
| --- | --- | --- |
| `MaxJobHistoryCount` | `50` | 为编辑器历史记录和 UCM 任务端点保留的最大面板/任务记录数。 |
| `DefaultPanelPage` | `Setup` | 打开 LLM Store 时显示的面板页面。 |
| `bAutoOpenPanelOnStartup` | `false` | 编辑器模块启动时自动打开面板。 |
| `bRunValidationOnReload` | `false` | 重新加载配置后运行验证健康检查。 |

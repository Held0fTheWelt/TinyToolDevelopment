<!-- doc-provenance: SAD architecture.md sections 1,5,6,8; facts product-facts.yml; reconciled 2026-07-16 -->
# 用户手册

## 主工作流

IIS 遵循纯检索（retrieval-only）的只读工作流：

1. 导入准备好的证据。
2. 构建或刷新本地目录。
3. 需要向量搜索时构建嵌入（embedding）。
4. 搜索或构建上下文包。
5. 通过 UMCP 向代理公开相同的只读工具。

IIS 不会应用项目变更（mutation）。

## 产品功能映射表

| 规格表功能 | 面向买家的表面 |
| --- | --- |
| `ImportPreparedChunks` | 从控制面板的 Imports 选项卡或服务 API 导入准备好的 chunk JSONL。 |
| `Search` | 从 Search 选项卡和服务 API 运行词法、向量或混合检索。 |
| `BuildContextPack` | 从查询或选择的结果构建聚焦于证据的上下文包。 |
| `RunPerfSelfCheck` | 从 Blueprint/API 和控制台表面运行附带的合成性能自检。 |
| `RuntimeControlDispatch` | 通过运行时控制面分发 observe、tune、act、persist 和 reset 控制动词。 |
| `AgentRetrievalTools` | 通过本地契约和可选的 UCM/UMCP 路由提供只读代理检索操作。 |

## 控制面板

打开：

```text
Tiny Tools -> AI -> Internal Index Service -> Open Internal Index Service
```

选项卡：

| 选项卡 | 用途 |
| --- | --- |
| Dashboard | 索引健康度、集成健康度、重建快捷方式、搜索快捷方式。 |
| Index | 导入、目录构建、嵌入任务创建/执行。 |
| Use | 搜索本地证据。 |
| Agents | 代理契约和 UMCP 桥接状态。 |
| Governance | 纯检索姿态、本地路径、桥接和工具可见性。 |
| Diagnostics | 报告、概述和生成产物的路径。 |
| Settings | `UIISSettings` 的面板内视图。 |

## 导入行为

导入操作消费准备好的 chunk JSONL。每个 chunk 包含 ID、内容、源码引用、资产/符号元数据和生命周期状态。IIS 验证输入、追加接受的 chunk 并写入导入报告。

重要文件：

```text
Saved/InternalIndexService/chunks.jsonl
Saved/InternalIndexService/imports/
Saved/InternalIndexService/reports/
```

## 目录构建

目录构建读取存储的 chunk 并生成可搜索的本地结构。它会过滤非激活状态的 chunk 生命状态，并写入一份报告，以便用户审查警告。

## 搜索

搜索查询字段包括查询文本、搜索模式、最大结果数、过滤器和上下文包选项。结果包含 chunk ID、得分信息、摘要（snippets）和源码引用。

搜索模式：

| 模式 | 含义 |
| --- | --- |
| Lexical | 对 chunk 目录使用本地文本匹配。 |
| Vector | 使用持久化的嵌入和配置的向量后端。 |
| Hybrid | 结合词法和向量候选对象。 |

## 运行时控制面

IIS 附带了一个**自立式**的（autark）运行时控制面，用于在不重新加载编辑器的情况下进行 observe → tune → act。它会在内存中修改活的 `UIISSettings` 对象（默认是暂态的），并立即重新应用缓存的控制杠杆，如 HNSW `efSearch` 和激活的 int8 内核。

**无需 UCM 或 UMCP 依赖** — 该控制面可在 Blueprint、C++ 和编辑器控制台中独立工作。

### 类型化 Blueprint API (`UIISSubsystem`)

| 方法 | 目的 |
| --- | --- |
| `GetControlState` | 生效杠杆和变更门控状态的快照。 |
| `SetTuning` | 应用可选的按字段调优增量（`FIISTuningRequest`）。 |
| `PersistTuning` | 将当前覆盖写入配置（`SaveConfig`）。 |
| `ResetTuning` | 重新加载配置并还原暂态覆盖。 |
| `RunPerfSelfCheck` | 针对配置的预算运行 SYN-2 性能工作负载。 |

### 控制台命令

| 命令 | 目的 |
| --- | --- |
| `iis.control.state` | 打印生效的控制状态 JSON。 |
| `iis.control.tune {json}` | 暂态调优（例如 `{"efSearch":128}`）。 |
| `iis.control.persist` | 将覆盖持久化到配置。 |
| `iis.control.reset` | 重新加载配置 / 还原覆盖。 |
| `iis.control.diagnostics.recent` | 最近的按查询诊断（当保留开启时）。 |
| `iis.perf.run` / `iis.perf.last` | 运行或读取上次性能自检。 |
| `iis.index.sync` / `iis.index.rebuild` / `iis.index.import` | 索引维护动作动词。 |

变更动词遵循项目设置中的 **Enable Runtime Control Mutations**（默认开启）。

## 嵌入（Embeddings）

IIS 不保留提供程序凭据。嵌入路由解析和执行通过 `FIISEmbeddingDiscovery`（`IIISEmbeddingRouteExecutor` via `IModularFeatures`）进行委托，通常由在 `StartupModule` 中注册并在 `ShutdownModule` 中注销的 LLM Store 桥接提供。

嵌入流程：

1. 为需要向量的 chunk 构建任务。
2. 解析嵌入路由。
3. 通过注册的执行器执行任务。
4. 持久化向量记录。
5. 更新报告。

## 代理工具

代理工具是只读的，并返回结构化 JSON。IIS 定义了六个自治检索操作。本地契约名称对于引擎内和 JSON 文件调用保持可用：

| 本地契约 | UCM 路由 ID | 目的 |
| --- | --- | --- |
| `iis_search` | `iis.agent.search.v1` | 搜索索引的 chunk（内联 JSON 净荷加上产物路径）。 |
| `iis_get_context_pack` | `iis.agent.get_context_pack.v1` | 从搜索结果构建紧凑的上下文包（内联 JSON 净荷加上产物路径）。 |
| `iis_get_chunk` | `iis.agent.get_chunk.v1` | 按 ID 获取一个 chunk。 |
| `iis_get_source_references` | `iis.agent.get_source_references.v1` | 返回 chunk 的源码引用。 |
| `iis_find_usages` | `iis.agent.find_usages.v1` | 查找使用记录。 |
| `iis_explain_blueprint` | `iis.agent.explain_blueprint.v1` | 总结索引的 Blueprint 证据（内联 JSON 净荷加上产物路径）。 |

`iis.index.status.v1` 还会额外报告 `catalog_exists`、`chunk_store_records` 和 `vector_records`，以便代理在无需读取文件的情况下验证索引是否已填充。

MCP 传输归 Unified MCP Server 所有。IIS 本身不注册 MCP 工具；项目的 Capability Mesh 设置会为每个代理操作声明一条路由，UMCP 会将其作为通用 `mesh_route_*` 工具发布。不需要桥接插件。

## 数据与隐私

默认情况下，IIS 将生成的索引存储在项目的 `Saved` 文件夹中。如果设置了自定义索引根目录，除非您的团队故意共享生成的证据，否则请使用本地/私有路径。

仅当 LLM Store 中的嵌入执行器路由使用云提供程序时，才会发生云端暴露。

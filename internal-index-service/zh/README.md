<!-- doc-provenance: SAD architecture.md sections 1,2,7,8; facts product-facts.yml; reconciled 2026-07-16 -->
# Internal Index Service

Internal Index Service (IIS) 是一个用于**本地**索引、检索（retrieval）、上下文包和面向代理（agent）搜索的 Unreal Engine 插件。它纯粹用于检索（retrieval-only）：不会修改项目内容，也不会生成补丁。

## 模块

| 模块 | 目的 |
| --- | --- |
| `InternalIndexServiceInterface` | 用于 chunk、搜索、导入、嵌入（embedding）和代理访问的公共契约。 |
| `InternalIndexService` | 运行时引擎子系统、chunk 目录、向量后端、嵌入任务、增量索引。 |
| `InternalIndexServiceEditor` | 编辑器控制面板、Python 桥接以及 Tiny Tools 菜单项。 |

## 打开控制面板

```text
Tiny Tools -> AI -> Internal Index Service -> Open Internal Index Service
```

或者，如果您的布局中已显示该选项，请使用游牧选项卡（nomad tab）**Internal Index Service**。

控制面板组织如下：

| 选项卡 | 目的 |
| --- | --- |
| **Dashboard** | Index 和 Integrations 的健康卡片；快捷操作（重建目录）。 |
| **Overview** | 服务版本、索引根目录、目录/向量存在状态。 |
| **Imports** | UII 交接和导入报告摘要。 |
| **Catalog** | 构建目录并在 `Saved/InternalIndexService/reports` 下显示运行时目录构建摘要。 |
| **Embeddings** | 通过已检测到的 `IIISEmbeddingRouteExecutor` 构建并执行持久化的嵌入任务。 |
| **Search** | 在本地索引中进行内联词法/向量/混合搜索。 |
| **Agent/MCP** | 代理契约、UCM 路由 ID 以及通过 Unified MCP Server 提供的 MCP 访问指南。 |
| **Reports** | 报告和日志文件夹快捷方式。 |

页眉显示项目名称、纯检索标记、**Settings** 按钮和 **Refresh** 按钮。刷新会更新所有选项卡摘要，强制更新仪表板卡片，并刷新 Governance 面板。

仪表板卡片会在打开时、显式**Refresh**时以及执行仪表板操作（如 **Rebuild**）后刷新。面板不会通过定期定时器重建卡片，从而在编辑或检查面板时保持 UI 稳定。

## 项目设置

在以下位置配置 IIS：

```text
Edit -> Project Settings -> Plugins -> Internal Index Service
```

| 设置 | 默认值 | 含义 |
| --- | --- | --- |
| **Vector Backend** | `jsonl_bruteforce` | 本地向量索引实现（`jsonl_bruteforce` 或 `hnsw`），根据记录数自动进行暴力/HNSW 路由。 |
| **Index Root (optional)** | *(空)* | 覆盖磁盘上的索引根目录；为空时使用 `Saved/InternalIndexService`。 |
| **Brute Force Max Records** | `10000` | 使用 HNSW 之前的精确搜索阈值。 |
| **Embedding Executor Id** | *(空)* | 首选的嵌入执行器。为空时使用正常 IIS 发现；可选的 IIS LLM Store Bridge 在加载时会将此设置为 `llmstore`。 |
| **Vector Storage Format** | `Int8 Per-Vector Scale` | HNSW 存储策略。正常使用时保持紧凑的每个向量 int8 默认值；在极高精度/调试运行中使用 `Float32`；仅在实验关卡后使用 `Experimental Global Scale`。 |
| **Allow Experimental Vector Formats** | `false` | 启用仅用于测量的向量布局，这可能会降低召回率（recall）。 |
| **Rebuild On Vector Format Mismatch** | `true` | 重建不兼容的持久化 HNSW 分区，而不是以错误的字节布局加载它们。 |
| **Quantization Recall Gate** | `0.7` | 量化自动化测试使用的最低召回率目标；在代表性项目验证后提高此值。 |
| **HNSW M / efConstruction / efSearch** | `16` / `200` / `64` | HNSW 召回率、构建时间、内存和查询延迟调优。 |

MCP 访问由 Unified MCP Server 通过项目的 Capability Mesh 路由提供。IIS 不再随附或需要专门的 IIS UMCP 桥接。

## 集成

嵌入执行通过 `FIISEmbeddingDiscovery`（`IModularFeatures` / `IIISEmbeddingRouteExecutor`）进行委托。桥接插件在 `StartupModule` 中注册，在 `ShutdownModule` 中注销。`FIISEmbeddingRouteExecutorRegistry` 是针对旧版调用方的已弃用适配器。

仪表板 **Integrations** 卡片列出了来自 `FIISEmbeddingDiscovery::GetExecutorIds()` 的执行器 ID，以及每个集成是否处于激活状态。

编辑器任务历史记录通过 UCM 路由（`iis.editor.jobs.list.v1`，`iis.editor.jobs.status.v1`）公开，而不是通过 UMCP 编译时提供程序。列表路由将面板历史记录与最近的 SQLite 嵌入任务行合并。

## 相关文档

| 文档 | 受众 |
| --- | --- |
| [QUICKSTART.md](QUICKSTART.md) | 首次设置、导入、索引构建和搜索。 |
| [UserManual.md](UserManual.md) | 完整的编辑器工作流和运行行为。 |
| [SettingsReference.md](SettingsReference.md) | 设置、生成的文件和存储路径。 |
| [TechnicalOverview.md](TechnicalOverview.md) | 维护者级别的架构和数据流。 |
| [CodeDocumentation.md](CodeDocumentation.md) | C++ 源码映射、核心类和执行路径。 |
| [INTEGRATION.md](INTEGRATION.md) | UII、LLM Store 和 UMCP 如何桥接到 IIS。 |
| [FAQ.md](FAQ.md) | 常见的买家和审查者问题。 |
| [TROUBLESHOOTING.md](TROUBLESHOOTING.md) | 常见故障和修复方法。 |
| [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md) | 提交 Fab 的第三方源码声明细节。 |
| [../CHANGELOG.md](../CHANGELOG.md) | 发布说明。 |

## 打包

`Config/FilterPlugin.ini` 包含了 `/Documentation/...`，因此买家将在 Fab 构建中收到此文件夹。
它还在打包输出中保留了 BuildPlugin 生成的预编译元数据。将 IIS 安装到 Unreal Engine 安装目录时，请使用针对该引擎版本构建的包，并保持其生成的二进制文件和元数据完好无损。

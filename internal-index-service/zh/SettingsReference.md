<!-- doc-provenance: SAD architecture.md sections 2,8,10; facts product-facts.yml; reconciled 2026-07-16 -->
# 设置参考

IIS 设置存储在 `UIISSettings` 中。

打开：

```text
Edit -> Project Settings -> Plugins -> Internal Index Service
```

## 字段

| 设置 | 默认值 | 含义 |
| --- | --- | --- |
| Vector Backend | `jsonl_bruteforce` | 选择本地向量搜索后端。支持的值包括 `jsonl_bruteforce` 和 `hnsw`。选择 `jsonl_bruteforce` 时，IIS 会在记录数超过下方的暴力搜索记录限制时自动切换到 HNSW。 |
| Index Root | 空 | 生成的 IIS 数据的可选覆盖。为空时使用 `Saved/InternalIndexService`。 |
| Brute Force Max Records | `10000` | 达到或低于此记录数时，使用精确的暴力搜索；高于此值时使用 HNSW。 |
| Embedding Executor Id | 空 | 首选的 IIS 嵌入执行器 ID。为空时使用正常发现；可选的 IIS LLM Store Bridge 在加载时会将此设置为 `llmstore`。 |
| Vector Storage Format | `Int8 Per-Vector Scale` | HNSW 向量存储策略。`Int8 Per-Vector Scale` 是支持的紧凑默认模式；`Float32` 适用于高精度/调试运行；`Experimental Global Scale` 受关卡限制且仅用于测量。 |
| Allow Experimental Vector Formats | `false` | 启用实验性 HNSW 存储格式。禁用时，实验性选择将回退到 `Int8 Per-Vector Scale`。 |
| Rebuild On Vector Format Mismatch | `true` | 删除不兼容的持久化 HNSW 分区，以便可以从源向量重建它们，而不是以错误的字节布局进行读取。 |
| Quantization Recall Gate | `0.7` | 量化向量存储自动化关卡使用的最低召回率目标。仅在对代表性项目嵌入进行验证后提高此值。 |
| HNSW M | `16` | HNSW 图连通性。较高值可提高召回率，但会消耗更多内存和构建时间。适用于新构建的索引。 |
| HNSW efConstruction | `200` | 构建时的候选列表大小。较高值可提高图质量和召回率，但会增加构建时间。适用于新构建的索引。 |
| HNSW efSearch | `64` | 查询时的候选列表大小。较高值可提高召回率，但会增加查询延迟。在加载和重建时应用。 |
| Enable Runtime Control Mutations | `true` | 运行时控制面的主关卡。关闭时，控制台和 API 的 tune/act/persist 动词将被拒绝；读取仍然有效。 |
| Retain Recent Diagnostics | `false` | 开启时，IIS 将保留一个有限的内存环形缓冲区，存放最近按查询的诊断信息，用于 `diagnostics.recent` / 控制台检查。 |
| Recent Diagnostics Max Count | `64` | 开启 Retain Recent Diagnostics 时保留的最大诊断数。 |
| Estimate Recall By Default | `false` | 开启时，搜索将估计 recall@K，除非查询明确选择退出。这会增加一次精确参考扫描（SYN-1）。 |

> HNSW 索引默认使用 int8 标量量化（按向量缩放）进行存储，这能在保持高召回率的同时减少索引内存和磁盘占用。Float32 可作为高精度/调试策略。实验性的全局缩放 int8 被故意限制，因为它可能会在归一化的高维嵌入上浪费大部分 int8 级别。默认情况下，系统会自动检测并重建使用其他存储策略构建的索引。

## 生成路径

默认根目录：

```text
Saved/InternalIndexService
```

生成的重要区域：

| 路径 | 目的 |
| --- | --- |
| `chunks.jsonl` | 导入的 chunk 存储。 |
| `imports/` | 导入清单和报告。 |
| `reports/` | 目录、嵌入和诊断报告。 |
| `agent_contracts/` | 桥接器消费的代理工具契约和 MCP 清单。 |
| `vectors/` 或后端特定文件 | 持久化的嵌入/向量数据。 |

确切的文件名可能会因工作流和后端而异。

## MCP 设置

MCP 服务器设置不在 IIS 中。请在以下位置配置它们：

```text
Edit -> Editor Settings -> Plugins -> Unified MCP Server
```

IIS 代理访问通过项目的 Capability Mesh 路由（如 `iis.agent.search.v1`）发布。

## 密钥处理

IIS 不存储提供程序密钥。嵌入提供程序凭据属于 LLM Store 或提供程序环境。

## 推荐默认值

| 场景 | Vector Backend | Vector Storage Format | 实验格式 | Index Root |
| --- | --- | --- | --- | --- |
| 首次设置 | `jsonl_bruteforce` | `Int8 Per-Vector Scale` | 禁用 | 空 |
| 较大的本地索引 | `hnsw` | `Int8 Per-Vector Scale` | 禁用 | 空或项目本地自定义路径 |
| 高精度调试 | `hnsw` | `Float32` | 禁用 | 临时工作区路径 |
| 召回率实验 | `hnsw` | `Experimental Global Scale` | 启用 | 临时工作区路径 |
| 共享 CI 验证 | `jsonl_bruteforce` | `Int8 Per-Vector Scale` | 禁用 | 临时工作区路径 |

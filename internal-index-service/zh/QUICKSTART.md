<!-- doc-provenance: SAD architecture.md sections 1,3,6,7,8; facts product-facts.yml; reconciled 2026-07-16 -->
# 快速入门

## 1. 启用插件

在插件浏览器中启用 `Internal Index Service`。如果 Unreal 提示，请重启编辑器。

## 2. 打开控制面板

使用：

```text
Tiny Tools -> AI -> Internal Index Service -> Open Internal Index Service
```

控制面板将在 Dashboard 页面打开。

## 3. 配置设置

打开：

```text
Edit -> Project Settings -> Plugins -> Internal Index Service
```

推荐的首次设置：

| 设置 | 值 |
| --- | --- |
| Vector Backend | `jsonl_bruteforce` |
| Vector Storage Format | `Int8 Per-Vector Scale` |
| Allow Experimental Vector Formats | `false` |
| Index Root | 空 |

`Index Root` 为空意味着 IIS 使用：

```text
Saved/InternalIndexService
```

默认存储策略对 HNSW 分区使用每个向量的 int8 缩放。这是正常的紧凑模式。`Float32` 可用于高精度/调试运行；除非您正在故意测量召回率权衡，否则应保持禁用 `Experimental Global Scale`。

## 4. 导入准备好的 chunk

使用控制面板的 Imports 选项卡，或使用准备好的 chunk JSONL 文件调用服务 API。准备好的 chunk 通常来自配套的提取管道，例如 Unreal Integration Intelligence。

导入操作会在 IIS 保存的文件夹下写入报告并更新 chunk 存储。

## 5. 构建目录

使用 Dashboard **Rebuild** 操作或 Catalog 选项卡。IIS 读取导入的 chunk，规范化生命周期状态，并写入目录构建报告。

## 6. 搜索

使用 Search 选项卡：

- 词法搜索基于本地目录运行
- 向量搜索需要嵌入（embedding）
- 当向量存在时，混合搜索会结合两者

## 7. 构建嵌入（可选 – 增加向量搜索，需要 LLM Store）

词法搜索（步骤 1–6）无需其他插件即可独立工作。向量搜索和混合搜索是可选增强功能：首先配置 **LLM Store** 插件，然后 IIS 向嵌入执行器注册表请求路由、创建任务并写入嵌入报告。从 Embeddings 选项卡执行任务。即使没有 LLM Store，IIS 仍可进行导入、构建和词法搜索。

## 8. 公开代理工具（可选 – 需要 Unified MCP Server + Capability Mesh）

此步骤是可选的，仅当您希望 AI 代理调用 IIS 时才需要。安装并启用：

- Unified MCP Server
- Unreal Capability Mesh

确保项目的 Capability Mesh 配置文件包含 IIS 代理路由（例如 `iis.agent.search.v1`）。然后启动 Unified MCP Server。每个 IIS 代理功能都作为其自己的自治 UCM 路由公开，并扁平化为 `mesh_route_*` MCP 工具，例如：

```text
mesh_route_iis_agent_search_v1_<hash>
mesh_route_iis_agent_get_context_pack_v1_<hash>
mesh_route_iis_agent_get_chunk_v1_<hash>
mesh_route_iis_agent_get_source_references_v1_<hash>
mesh_route_iis_agent_find_usages_v1_<hash>
mesh_route_iis_agent_explain_blueprint_v1_<hash>
```

或者将 `route_id` 设置为路由 ID（例如 `iis.agent.search.v1`）来调用 `mesh_execute_route`。

## 9. 运行时调优（可选 - 无需额外插件）

随附的运行时控制面是**自立式**的（autark）：不需要 UCM 或 UMCP。

打开编辑器输出日志控制台并运行：

```text
iis.control.state
```

响应摘录示例（默认 `efSearch` 为 64）：

```json
{"ok":true,"errorCode":"","errorMessage":"","efSearch":64,...}
```

实时提高查询时的 `efSearch`：

```text
iis.control.tune {"efSearch":128}
```

确认更改：

```text
iis.control.state
```

调优后的示例：

```json
{"ok":true,"errorCode":"","errorMessage":"","efSearch":128,...}
```

覆盖在您运行 `iis.control.persist` 之前是**暂态的**（transient）。使用 `iis.control.reset` 从配置中重新加载。有关完整的控制台命令列表和 Blueprint API，请参阅 `UserManual.md`。

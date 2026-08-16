<!-- doc-provenance: AKDB:plugins/UnifiedMcpServer/architecture.md; docs/architecture/plugins/UnifiedMcpServer/product-facts.yml; reconciled 2026-07-04 -->
# Unified MCP Server

Unified MCP Server 是一个虚幻引擎（Unreal Engine）编辑器插件，为整个项目提供统一的本地 Model Context Protocol (MCP) 端点。其他插件通过一个轻量级的模块化功能接口挂载工具，因此服务器无需直接依赖这些插件即可公开新功能。

该插件被故意设计为纯基础架构。它不随附外部可执行文件、Node 包或 Python 运行时。它在编辑器内部托管一个本地环回 (loopback) JSON-RPC 2.0 MCP 端点，并允许提供商在运行时注册工具。

## 模块构成

| 模块 | 用途 |
| --- | --- |
| `UnifiedMcpServerInterface` | 公共 `IUmcpToolProvider` 契约以及工具描述符/结果类型。 |
| `UnifiedMcpServerEditor` | 用于服务器、设置、Token 处理、提供商注册表、状态控制面板和 Tiny Tools 菜单项的编辑器主机。 |

## 核心工作流

1. 在项目中启用该插件。
2. 打开 `Edit -> Editor Settings -> Plugins -> Unified MCP Server`。
3. 启用本地服务器并选择端口，或保持默认端口 `8732`。
4. 使用 `Tiny Tools -> AI -> Universal MCP -> Open Control Panel` 查看状态、生命周期按钮以及按插件分组的已连接功能树。
5. 从面板或通过 `Tiny Tools -> AI -> Universal MCP -> Start Unified MCP Server` 启动服务器。
6. 从 `Saved/UnifiedMcpServer/agent/mcp_endpoint.json` 读取连接数据。
7. 配置 MCP 客户端，通过 `Authorization: Bearer <token>` 调用 `http://127.0.0.1:8732/mcp`。

## 工具提供商 (Tool Providers)

提供商插件实现 `IUmcpToolProvider` 并将其注册为虚幻模块化功能。公开的工具名称使用以下格式：

```text
<providerId>_<toolName>
```

当加载了 Unreal Capability Mesh 时，内置的 mesh 提供商会公开通用工具，如 `mesh_list_capabilities`、`mesh_list_routes`、`mesh_configure_experimental_self_approval`、`mesh_dry_run_route` 和 `mesh_execute_route`。它还将设置中声明的 UCM 路由扁平化为直接的 `mesh_route_*` MCP 工具。这些路由工具发布从路由派生的 MCP `inputSchema`、`outputSchema` 和工具注解，使客户端可以在调用前检查参数和风险提示。`mesh_configure_experimental_self_approval` 是**实验性**的，且**使用风险自负**；启用需要显式的风险确认。传统的直接提供商桥接仍可注册特定于产品的工具名称，但 UCM 路由是项目首选的设置路径。

`tools/call` 将提供商 JSON 作为文本内容返回，且当结果为 JSON 对象时，同时作为 MCP `structuredContent` 返回。`initialize` 声明 `tools.listChanged`，而 `tools/list` 包含 `_meta.toolsRevision` 值，以便客户端在 UCM 设置更改后刷新缓存的工具描述符。

UMCP 1.0.3 在单一端点之上添加了访问控制。可以禁用提供商 ID，并且可以通过精确名称或通配符模式允许或拦截公开的工具名称。UMCP 1.0.4 添加了配置文件（`Default`、`Read Only`、`Automation`、`Experimental`）和派生自注解的工具组。UMCP 1.0.5 添加了作用域会话 Token，使不同的客户端可以通过同一个 `/mcp` 端点使用 `default`、`read_only`、`automation` 或 `experimental_admin` 访问。UMCP 1.0.6 添加了运行时 Access Guard 拦截和用于最近 `tools/call` 诊断的安全密钥 Access Journal。对 `tools/list` 和 `tools/call` 执行相同的策略。控制面板显示已连接的功能是已公开、已拦截、已隐藏还是不可用。

## 安全性

- 服务器仅绑定到 `127.0.0.1`。
- 服务器默认禁用。
- 请求需要握手文件中的一个 Bearer Token。
- 提供商/工具访问控制可以从 `tools/list` 中隐藏工具并拦截直接的 `tools/call` 执行。
- 运行时 Access Guard 拦截仅存在于内存中，并在服务器停止时清除。
- 可以从 **Tiny Tools -> AI -> Universal MCP** 轮换 Token。
- 握手文件在服务器停止时被删除。
- 请求元数据记录到 `Saved/UnifiedMcpServer/logs/mcp_requests.jsonl`。
- 访问诊断记录到 `Saved/UnifiedMcpServer/logs/access_audit.jsonl`，其中省略了看起来像密钥的参数键。

## 文档指南

| 文档 | 用途 |
| --- | --- |
| [BUYER_GUIDE.md](BUYER_GUIDE.md) | 产品概述、使用场景和限制。 |
| [QUICKSTART.md](QUICKSTART.md) | 首次设置和客户端连接。 |
| [UserManual.md](UserManual.md) | 编辑器中的日常使用。 |
| [TechnicalOverview.md](TechnicalOverview.md) | 架构和协议行为。 |
| [INTEGRATION.md](INTEGRATION.md) | 提供商插件如何挂载工具。 |
| [SettingsReference.md](SettingsReference.md) | 设置和保存的文件。 |
| [CodeDocumentation.md](CodeDocumentation.md) | 源码布局和契约。 |
| [FAQ.md](FAQ.md) | 买家常见问题。 |
| [TROUBLESHOOTING.md](TROUBLESHOOTING.md) | 常见故障与修复。 |
| [ReleaseChecklist.md](ReleaseChecklist.md) | 发布和 Fab 打包检查清单。 |

## 打包

`Config/FilterPlugin.ini` 包含 `/Documentation/...` 和 `/CHANGELOG.md`，以便 Fab 打包包含此文档集。

<!-- doc-provenance: AKDB:plugins/UnifiedMcpServer/architecture.md; docs/architecture/plugins/UnifiedMcpServer/product-facts.yml; reconciled 2026-07-04 -->
# 快速入门

## 1. 启用插件

在插件浏览器中启用 `Unified MCP Server`，如果虚幻引擎提示，请重启编辑器。

## 2. 启用服务器

打开：

```text
Edit -> Editor Settings -> Plugins -> Unified MCP Server
```

开启 **Enable MCP Server**。除非其他本地服务已使用该端口，否则请保持默认端口 `8732`。

## 3. 启动服务器

使用以下路径：

```text
Tiny Tools -> AI -> Universal MCP -> Start Unified MCP Server
```

要查看状态、生命周期按钮以及按插件分组的已连接功能树，请使用：

```text
Tiny Tools -> AI -> Universal MCP -> Open Control Panel
```

Connected Functions 区域按插件对工具进行分组，支持架构的延迟展开，并在访问之间缓存未更改的元数据。在 UCM 设置更改后，使用 **Refresh** 强制完全重新加载。

在 UMCP 1.0.3 及更高版本中，控制面板还会显示访问状态。禁用单个提供商组可以在 `tools/list` 中隐藏其工具，并拦截直接的 `tools/call` 执行。

如果在编辑器启动前启用了该设置，服务器还会在编辑器模块加载时尝试自动启动。

## 4. 读取握手文件

启动后，编辑器会写入：

```text
Saved/UnifiedMcpServer/agent/mcp_endpoint.json
```

结构示例：

```json
{
  "host": "127.0.0.1",
  "port": 8732,
  "token": "<default-token>",
  "tokens": {
    "default": {"token": "<default-token>", "scope": "default", "profile": "Project Settings"},
    "read_only": {"token": "<read-only-token>", "scope": "read_only", "profile": "Read Only"},
    "automation": {"token": "<automation-token>", "scope": "automation", "profile": "Automation"},
    "experimental_admin": {"token": "<experimental-token>", "scope": "experimental_admin", "profile": "Experimental"}
  }
}
```

使用兼容性 `token` 字段，或从 `tokens` 中选择一个 Token：

```text
Authorization: Bearer <选定的-token>
```

## 5. 连接客户端

支持 HTTP 的 MCP 客户端可以调用：

```text
http://127.0.0.1:8732/mcp
```

在服务器运行的情况下，打开控制面板并点击 **Copy MCP Client Config**。
这会复制一段包含实时端点 URL 和当前默认 Bearer Token 的现成 `mcp.json` 片段。将其粘贴到您的 MCP 客户端配置文件中。
在 **Rotate Tokens** 之后，请再次复制该片段，因为 Bearer Token 已发生更改。

在 `initialize` 时，UMCP 会协商 `protocolVersion`：当您的客户端请求受支持的版本（`2025-06-18`、`2025-03-26` 或 `2024-11-05`）时，服务器会返回该版本；否则返回 `2024-11-05`。客户端使用 `GET /mcp` 进行探测会返回 HTTP 405，因为 UMCP 使用的是 Streamable-HTTP JSON 响应子集，不托管服务器到客户端的 SSE 流。

仅支持 Stdio 的客户端需要用户自行安装桥接工具（如 `mcp-remote`）。该桥接工具未包含在此插件中。

## 6. 添加工具（可选）

服务器单独运行；此步骤用于添加供客户端调用的工具。您有两个独立的选项，只需选择适合您项目的选项：

- **您自己的（或任何）插件：** 注册一个 `IUmcpToolProvider` 模块化功能，其工具会自动显示为 `<providerId>_<toolName>`。不需要目录插件。请参阅 [INTEGRATION.md](INTEGRATION.md)。
- **可选 — Unreal Capability Mesh (UCM)：** 如果您同时拥有 Unreal Capability Mesh，启用它会添加设置中声明的 `mesh_*` 工具，因此调用方可以通过 `mesh_execute_route` 或生成的直接 `mesh_route_*` 工具运行配置好的 UCM 路由（例如 IIS 上下文包、PRS 放置、SCD 迁移建议和 DataAsset/DataTable 管理）。它还公开了 `mesh_configure_experimental_self_approval`；该工具是**实验性**的，启用时需要显式的风险确认，仅用于风险自负的测试工作流。

两者都是可选的 — 服务器、握手和客户端连接（步骤 1–5）在未安装提供商的情况下即可工作。

## 7. 停止或轮换

使用 Tiny Tools 菜单：

```text
Tiny Tools -> AI -> Universal MCP -> Stop Unified MCP Server
Tiny Tools -> AI -> Universal MCP -> Rotate MCP Token
```

停止操作会删除握手文件。轮换操作会使用全新的带作用域 Token 重写握手文件。这两项操作也可在控制面板中执行。

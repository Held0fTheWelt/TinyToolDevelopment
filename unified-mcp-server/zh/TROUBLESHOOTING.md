<!-- doc-provenance: AKDB:plugins/UnifiedMcpServer/architecture.md; docs/architecture/plugins/UnifiedMcpServer/product-facts.yml; reconciled 2026-07-04 -->
# 故障排除

## 客户端收到 401 Unauthorized

请检查客户端是否发送了：

```text
Authorization: Bearer <token>
```

从以下位置读取当前的兼容性 Token 或带作用域的 Token：

```text
Saved/UnifiedMcpServer/agent/mcp_endpoint.json
```

如果轮换了 Token，请更新客户端配置。

## 状态响应会暴露 Token

生命周期和状态响应仅汇报握手的存在性、路径、端口和 Token 数量。它们绝不能返回原始握手 JSON 或 Bearer Token 值。请使用本地握手文件来进行授权的客户端配置，而不是通过诊断复制密钥。

## 缺失握手文件 (handshake)

可能的原因：

- 服务器未运行
- 服务器绑定配置的端口失败
- 插件已禁用
- 编辑器尚未启动该模块

请从以下位置启动服务器：

```text
Tiny Tools -> AI -> Universal MCP -> Start Unified MCP Server
```

## 端口已被使用

在以下位置更改端口：

```text
Edit -> Editor Settings -> Plugins -> Unified MCP Server
```

然后重启服务器。

## `tools/list` 未返回任何工具

Unified MCP Server 只是主机。启用 Unreal Capability Mesh 以获取通用的 `mesh_*` 工具，或启用另一个提供商插件。同时检查提供商是否报告就绪状态并注册了其模块化功能。

检查 Editor Settings 和控制面板中的访问控制。禁用的提供商 ID、限制性的访问配置文件、非空的允许列表、拦截的工具模式或拦截的工具组都会在 `tools/list` 中有意隐藏匹配的工具。

如果显示了通用的 `mesh_*` 工具，但未显示 `mesh_route_*` 工具，请运行 `mesh_reload_setup` 或点击 Capability Mesh 面板中的 **Reload Setup**，然后刷新 MCP 客户端。路由工具是从 `Config/UnrealCapabilityMesh` 中的激活路由清单生成的。

如果显示了 `mesh_configure_experimental_self_approval`，请将其视为风险自负的**实验性**测试工具。启用需要 `acknowledge_experimental_risk: true`，并将更改选定路由或所有需要批准路由的 Capability Mesh 批准行为。

如果在 UCM Routes UI 中更改了自动自我批准，但 MCP 客户端仍显示旧的路由说明，请再次调用 `tools/list` 或重新连接/刷新客户端。UMCP 在列出路由工具前会重新加载 UCM 设置，`mesh_list_routes` 会直接返回当前的 `experimental_self_approval_*` 状态。

## 控制面板中的 Connected Functions 看起来已过期

控制面板会缓存工具元数据以加快重复访问。在更改 UCM 设置、添加提供商或重新加载路由后，请点击控制面板中的 **Refresh** 强制完全重新加载已连接的功能。启动/停止和展开/折叠在底层快照未更改时会复用缓存。

## Stdio 客户端无法直接连接

该插件提供 HTTP 传输。仅支持 Stdio 的客户端需要用户自行安装桥接工具（如 `mcp-remote`）。

## 工具调用返回未知工具

请检查 `tools/list` 中公开的名称。使用带有前缀的名称：

```text
<providerId>_<toolName>
```

请勿直接调用提供商本地的名称。

## 工具调用返回 `tool_access_denied`

工具名称存在，但被 UMCP 访问控制拦截。检查 `AccessProfile`，从 `DisabledProviderIds` 中移除提供商 ID，调整 `AllowedToolNames` 或 `AllowedToolGroups`，或从 `BlockedToolNames` 或 `BlockedToolGroups` 中移除匹配的条目。

## 在 UE 5.6 上因 C++ 标准错误导致构建失败

确保 UMCP 模块和依赖的桥接模块使用 C++20 进行编译。UE 5.6 引擎头文件在核心头文件中使用了 C++20 语法。

## 请求日志位置

请求元数据写入到：

```text
Saved/UnifiedMcpServer/logs/mcp_requests.jsonl
```

使用它来检查方法名称、状态码、延迟和错误代码。

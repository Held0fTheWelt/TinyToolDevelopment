<!-- doc-provenance: AKDB:plugins/UnifiedMcpServer/architecture.md; docs/architecture/plugins/UnifiedMcpServer/product-facts.yml; reconciled 2026-07-04 -->
# 用户手册

## 打开设置

Unified MCP Server 的配置位置为：

```text
Edit -> Editor Settings -> Plugins -> Unified MCP Server
```

设置项：

| 设置项 | 默认值 | 含义 |
| --- | --- | --- |
| Enable MCP Server | 关 | 允许编辑器模块运行本地 MCP 服务器。 |
| Server Port | 8732 | 在 `127.0.0.1` 上使用的 TCP 端口。 |
| Validate Tool Arguments | 关 | 在调用提供商前，可选地根据每个工具的 `inputSchema` 验证传入的 `tools/call` 参数。 |
| Access Profile | Default | 高级公开模式：Default、Read Only、Automation 或 Experimental。 |
| Disabled Provider IDs | 空 | 隐藏并拦截来自匹配提供商 ID 的所有工具。 |
| Allowed Tool Names | 空 | 可选的已公开工具名称或通配符模式的允许列表。为空表示允许所有未被拦截的工具。 |
| Blocked Tool Names | 空 | 隐藏并拦截已公开的工具名称或通配符模式。 |
| Allowed Tool Groups | 空 | 可选的派生自注解的组（如 `read_only`、`non_destructive` 或 `idempotent`）的允许列表。 |
| Blocked Tool Groups | 空 | 隐藏并拦截派生自注解的组（如 `risky`、`destructive` 或 `open_world`）。 |
| Enable Access Journal | 开 | 为 `tools/call` 写入安全密钥的访问诊断。 |
| Access Journal Ring Capacity | 500 | 在内存中保留的用于控制面板和 Blueprint 诊断的最近条目数。 |
| Access Journal Max File Bytes | 5242880 | 在一个文件轮换前 `access_audit.jsonl` 的最大文件字节数。 |

## Tiny Tools 菜单

编辑器在 **Tiny Tools -> AI -> Universal MCP** 下添加了生命周期和状态操作：

| 操作 | 结果 |
| --- | --- |
| Open Control Panel | 打开 UMCP 控制面板，带有生命周期按钮和按插件分组的已连接功能树。 |
| Start Unified MCP Server | 启动本地环回 HTTP 端点。 |
| Stop Unified MCP Server | 停止端点并删除握手文件。 |
| Rotate MCP Token | 生成新的带作用域 Bearer Token 并重写握手文件。 |

**AI** 区域将 Unified MCP Server 与 Tiny Tool Development 的其他 AI 插件（如 Internal Index Service）归为一组。

## 控制面板 (Control Panel)

控制面板显示：

| 区域 | 详情 |
| --- | --- |
| Status | 运行/停止状态、启动设置、端点 URL、Token 存在性/数量、请求数、提供商数、工具数和握手文件路径。 |
| Actions | 启动、停止、轮换 Token、打开代理文件夹和刷新。 |
| Tabs | 用于提供商/工具/架构的 Connected Functions，以及用于最近工具调用和运行时拦截控制的 Access Activity。 |
| Connected Functions | 可展开的插件组，带有提供商开关、工具行、访问/就绪状态、MCP 工具名称、说明和延迟加载的输入/输出架构表。 |
| Access Activity | 包含 Token/客户端/结果详情的最近工具调用、运行时拦截数、刷新、Token/工具拦截/解除拦截以及清除运行时拦截操作。 |

### Connected Functions 布局

Connected Functions 使用类似于 Capability Mesh 路由目录的层级树：

1. **插件组** — 每个插件一行，包含接口数量；当组映射到单个提供商时，带有启用/禁用访问按钮。点击箭头可显示或隐藏该插件的工具。
2. **工具行** — 每个挂载的 MCP 工具或设置中声明的 UCM 能力一行。点击箭头可显示或隐藏该工具的输入/输出架构表。

列布局取决于**每个插件组内**的展开状态：

| 状态 | 列 |
| --- | --- |
| 所有工具已折叠 | `Provider`, `Ready`, `Tool`, `Description` (较宽) |
| 任意工具已展开 | `Provider`, `Ready`, `Tool`, `Input`, `Output`, `Description` |

**提供商分组：** 直接提供商工具显示在其 `GetProviderDisplayName()` 下。扁平化的 UCM 路由工具（`mesh_route_*`）显示在来自 Capability Mesh 能力元数据的**所属插件**下（例如 Internal Index Service 或 SmartContentDiet），而不是显示在 mesh 主机条目下。通用的 mesh 主机工具（如 `mesh_list_routes` 和 `mesh_reload_setup`）保留在 **Unreal Capability Mesh** 下。

**性能：** 面板异步加载工具元数据。未更改的数据在重复打开、启动/停止和展开/折叠时从缓存提供。在 UCM 设置更改后，使用 **Refresh** 强制完全重新加载。

标记为 `Needs approval` 的行是需要批准的 UCM 能力。其工具提示指向 UCM Routes 或 `mesh_configure_experimental_self_approval` 中的**实验性**自动自我批准路径；仅在风险自负的测试中使用。

标记为 `Blocked` 或 `Hidden` 的行不会公开给 MCP 客户端。UMCP 会将其从 `tools/list` 中移除，如果客户端仍然直接调用该工具名称，则返回 `tool_access_denied`。

来自 **Access Activity** 标签页的运行时拦截是编辑器会话的临时拦截。它们不会写入编辑器设置，会为受影响的 Token 从 `tools/list` 中隐藏工具，以 `runtime_access_denied` 拒绝直接调用，并在服务器停止时清除。

当提供商发布 MCP 注解提示时，工具说明中会包含这些提示，如只读、破坏性、幂等或开放世界行为。面板还会显示配置文件和组访问策略所使用的派生组。

## 连接文件

握手文件：

```text
Saved/UnifiedMcpServer/agent/mcp_endpoint.json
```

请求日志：

```text
Saved/UnifiedMcpServer/logs/mcp_requests.jsonl
```

访问日志 (Access Journal)：

```text
Saved/UnifiedMcpServer/logs/access_audit.jsonl
```

握手文件包含本地主机、端口、兼容性 `token` 和带作用域的 `tokens`。请将其视为本地凭据。

访问日志省略了看起来像密钥的参数键，如 token、secret、password、API key、authorization 和 bearer。

## 支持的 MCP 调用

服务器处理以下 JSON-RPC 方法：

| 方法 | 行为 |
| --- | --- |
| `initialize` | 返回协议版本、工具能力和服务器信息。 |
| `notifications/initialized` | 确认客户端初始化。 |
| `ping` | 返回空结果。 |
| `tools/list` | 返回已注册提供商的所有工具，包括 `inputSchema`、可选的 `outputSchema`、可选的工具 `annotations` 以及 `_meta.toolsRevision`。 |
| `tools/call` | 将带有前缀的提供商工具名称路由到其提供商，并将 JSON 结果作为文本返回，并在可能时同时作为 `structuredContent` 返回。 |

未知方法将返回 JSON-RPC 方法未找到错误。

## 编辑器任务工具 (Editor Job Tools)

当 Unreal Capability Mesh 可用时，UMCP 会公开只读的任务聚合工具：

| 工具 | 用途 |
| --- | --- |
| `jobs_list` | 合并来自 IIS、SmartContentDiet、LLM Store 和 UMCP 的固定 UCM 路由的最近任务。可选的 `provider_id` 和 `max_count` 参数可缩小结果范围。 |
| `jobs_status` | 在同一个路由表中查找一个任务 ID，并返回匹配的源提供商 ID。 |

源插件通过 UCM 路由发布它们自己的编辑器任务列表/状态，不依赖 UMCP。如果 UCM 或某个路由不可用，聚合会跳过该路由，仍会返回来自可用提供商的任务。

## 使用提供商

Unified MCP Server 本身不包含项目工具。由提供商添加它们。提供商通过 `IUmcpToolProvider` 提供描述符、输入架构和调用逻辑。

安装提供商后，工具将显示为：

```text
provider_tool
```

例如：

```text
mesh_route_iis_agent_search_v1_<hash>
```

当加载了 Unreal Capability Mesh 时，UMCP 会公开通用的 mesh 工具：

```text
mesh_reload_setup
mesh_list_capabilities
mesh_list_routes
mesh_configure_experimental_self_approval
mesh_dry_run_route
mesh_execute_route
mesh_invoke_endpoint
```

UMCP 还将每个声明的 Capability Mesh 路由发布为扁平化的 MCP 工具：

```text
mesh_route_<sanitized_route_id>_<hash>
```

扁平化的路由工具接受 `mode: "execute"` 或 `mode: "dry_run"`。如果省略了 `input` 或 `input_json`，剩余的参数将被视为路由输入对象。对于内部绑定了序列化 `request_json` 的路由，UMCP 会自动将扁平化的参数镜像到 `request_json` 中。每个扁平化的路由工具都会发布派生自路由的 MCP `inputSchema`、`outputSchema` 以及注解（如 `readOnlyHint`、`destructiveHint` 和 `openWorldHint`）。变更性路由仍需通过 Capability Mesh 的策略和批准检查。

对变更性操作使用 `mesh_execute_route`，以便 Capability Mesh 的路由策略和批准检查保持激活状态。

`mesh_configure_experimental_self_approval` 是明确**实验性**的，且**使用风险自负**。它可以读取或更改需要批准的 UCM 路由是在全局还是按路由 ID 进行自动自我批准。启用需要 `acknowledge_experimental_risk: true`。

## 操作说明

- 每个编辑器实例使用唯一的端口。
- 在共享可能显示握手文件的日志或截图后，请轮换 Token。
- 当外部代理不再需要访问权限时，请停止服务器。
- 如果未启用提供商插件，`tools/list` 完全可以合法地返回空列表。

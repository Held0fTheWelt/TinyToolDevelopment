<!-- doc-provenance: AKDB:plugins/UnifiedMcpServer/architecture.md; docs/architecture/plugins/UnifiedMcpServer/product-facts.yml; reconciled 2026-07-04 -->
# 设置参考

设置保存在 `UUmcpSettings` 中，并存储在编辑器配置中。

打开：

```text
Edit -> Editor Settings -> Plugins -> Unified MCP Server
```

## 服务器 (Server)

| 设置项 | 配置字段 | 默认值 | 说明 |
| --- | --- | --- | --- |
| Enable MCP Server | `bEnableServer` | `false` | 默认关闭。为 true 时，编辑器模块会在启动时尝试启动服务器。 |
| Server Port | `ServerPort` | `8732` | 本地环回端点的 TCP 端口。有效范围：1-65535。 |

## 工具 (Tools)

| 设置项 | 配置字段 | 默认值 | 说明 |
| --- | --- | --- | --- |
| Validate Tool Arguments | `bValidateToolArguments` | `false` | 启用后，UMCP 会在调用提供商之前，根据每个工具的 `inputSchema` 验证传入的 `tools/call` 参数。验证是轻量级且顶层的：必需字段、`additionalProperties:false` 时的未知字段、基本类型和枚举。 |

## 访问控制 (Access Control)

| 设置项 | 配置字段 | 默认值 | 说明 |
| --- | --- | --- | --- |
| Access Profile | `AccessProfile` | `Default` | 高级公开模式。`Default` 保留传统公开方式，`Read Only` 仅公开标记为只读的工具，`Automation` 隐藏高风险/破坏性/开放世界/未分类的工具，而 `Experimental` 故意允许高风险工具，除非手动拦截。 |
| Disabled Provider IDs | `DisabledProviderIds` | 空 | 从 `tools/list` 中隐藏并在 `tools/call` 时拦截的提供商 ID。控制面板可以将单个提供商组切换到此列表中。 |
| Allowed Tool Names | `AllowedToolNames` | 空 | 可选的已公开 MCP 工具名称或通配符模式（如 `iis_search` 或 `mesh_route_*`）的允许列表。为空表示允许所有工具，除非已被禁用或拦截。 |
| Blocked Tool Names | `BlockedToolNames` | 空 | 从 `tools/list` 中隐藏并在 `tools/call` 时拦截的已公开 MCP 工具名称或通配符模式。 |
| Allowed Tool Groups | `AllowedToolGroups` | 空 | 派生自注解的组（如 `read_only`、`non_destructive`、`idempotent`、`risky`、`destructive`、`open_world` 或 `unclassified`）的可选允许列表。 |
| Blocked Tool Groups | `BlockedToolGroups` | 空 | 从 `tools/list` 中隐藏并在 `tools/call` 时拦截的派生自注解的组。 |

策略优先级依次为：禁用提供商、显式拦截工具、访问配置文件、拦截组、可选的工具/组允许列表、公开。如果任意允许列表包含条目，则当工具名称或至少一个组匹配时工具被公开。对 `tools/list` 和 `tools/call` 执行相同的策略。

从控制面板或 Blueprint 助手创建的运行时 Access Guard 拦截是会话本地的，排在永久策略之后。它们会为受影响的 Token 从 `tools/list` 中隐藏匹配的工具，以 `runtime_access_denied` 拒绝直接调用 `tools/call`，并在服务器停止时清除。

任务聚合工具是只读的，但它们仍通过与每个其他 MCP 工具相同的提供商/工具/配置文件策略。拦截 `jobs_*` 或 `jobs` 提供商会同时隐藏 `jobs_list` 和 `jobs_status`。

## 访问日志 (Access Journal)

| 设置项 | 配置字段 | 默认值 | 说明 |
| --- | --- | --- | --- |
| Enable Access Journal | `bEnableAccessJournal` | `true` | 为 `tools/call` 写入语义访问诊断。 |
| Access Journal Ring Capacity | `AccessJournalRingCapacity` | `500` | 在 RAM 中保留的用于控制面板和 Blueprint 诊断的最近条目数。 |
| Access Journal Max File Bytes | `AccessJournalMaxFileBytes` | `5242880` | 在一个文件轮换前 `access_audit.jsonl` 的最大文件字节数。 |
| Access Journal Redacted String Limit | `AccessJournalRedactedStringLimit` | `128` | 脱敏 JSONL 参数中的最大字符串长度。 |
| Access Journal Max RAM Entry Bytes | `AccessJournalMaxRamEntryBytes` | `8192` | 每条条目在内存中保留的净化后的最大参数 JSON 字节数。看起来像密钥的键会被省略。 |

## 生成的文件

| 文件 | 用途 |
| --- | --- |
| `Saved/UnifiedMcpServer/agent/mcp_endpoint.json` | 包含主机、端口、兼容性 Token 和带作用域会话 Token 的连接握手文件。 |
| `Saved/UnifiedMcpServer/logs/mcp_requests.jsonl` | 请求元数据日志。 |
| `Saved/UnifiedMcpServer/logs/access_audit.jsonl` | 用于 `tools/call` 的安全密钥的语义访问日志。 |

## 安全默认值

- 服务器默认禁用。
- 仅本地环回主机。
- 必须提供 Bearer Token。
- 可以从 **Tiny Tools -> AI -> Universal MCP** 轮换 Token。
- 握手文件在服务器停止时删除。
- UMCP 1.0.5 向握手文件中写入 `default`、`read_only`、`automation` 和 `experimental_admin` 会话 Token。传统的 `token` 字段保留作为默认 Token 以确保兼容性。
- UMCP 1.0.6 在访问诊断中省略看起来像密钥的参数键，包括 token、secret、password、API key、authorization 和 bearer。

## 端口选择

在以下情况下请使用不同的端口：

- 另一个编辑器实例已在使用 `8732`
- 本地服务已绑定到相同的端口
- 独立的项目需要独立的 MCP 端点

客户端 URL 为：

```text
http://127.0.0.1:<ServerPort>/mcp
```

<!-- doc-provenance: AKDB:plugins/UnifiedMcpServer/architecture.md; docs/architecture/plugins/UnifiedMcpServer/product-facts.yml; reconciled 2026-07-04 -->
# 常见问题解答 (FAQ)

## 该插件是否包含 AI 模型？

不包含。Unified MCP Server 是连接基础架构。它将来自提供商插件的工具公开给本地 MCP 客户端。

## 它是否包含独立的可执行文件？

不包含。服务器在虚幻编辑器内部运行，不随附外部可执行文件。

## 它是否包含 Node.js、Python 或 mcp-remote？

不包含。仅支持 Stdio 的客户端可能需要用户自行安装桥接工具（如 `mcp-remote`），但未打包随附。

## 服务器默认是否启用？

否。它默认关闭，必须在 Editor Settings 中启用或从 **Tiny Tools -> AI -> Universal MCP** 手动启动。

## 它是否在网络上进行监听？

否。它仅绑定到 `127.0.0.1`。

## 如何对请求进行身份验证？

服务器在启动时生成带作用域的 Bearer Token。客户端从 `Saved/UnifiedMcpServer/agent/mcp_endpoint.json` 读取它们，并在 `Authorization` 请求头中发送一个 Token。

## 它是否支持多个带作用域的 Token？

支持。UMCP 1.0.5 会将 `default`、`read_only`、`automation` 和 `experimental_admin` 会话 Token 写入握手文件。所有 Token 都使用相同的本地 `/mcp` 端点；作用域决定了为 `tools/list` 和 `tools/call` 强制执行哪种访问配置文件。

## 为什么我的工具列表是空的？

基础服务器只是基础架构。启用 Unreal Capability Mesh 以获取通用的 `mesh_*` 提供商，或启用注册了 `IUmcpToolProvider` 的另一个插件。同时检查 UMCP 访问控制：禁用的提供商、限制性的配置文件、激活的允许列表、拦截的工具模式或拦截的工具组都可以在 `tools/list` 中有意隐藏工具。

## 我可以隐藏或拦截特定的提供商和工具吗？

可以。UMCP 保持单一的本地端点，并在工具到达 MCP 客户端之前应用访问控制。可以禁用提供商 ID、选择访问配置文件、将精确或通配符工具名称或组添加到允许/拦截列表，或为单个提供商组使用控制面板提供商开关。对 `tools/list` 和 `tools/call` 执行相同的策略。

## 我可以在会话期间临时拦截某个工具吗？

可以。UMCP 1.0.6 添加了来自控制面板和 Blueprint 诊断的运行时 Access Guard 拦截。运行时拦截可以为带作用域的 Token 或全局隐藏工具，以 `runtime_access_denied` 拒绝直接调用，并在服务器停止时清除。

## 访问日志 (Access Journal) 是否存储密钥？

它专为安全密钥的诊断而设计。看起来像密钥的参数键（如 token、secret、password、API key、authorization 和 bearer）都会从内存和 JSONL 访问日志中省略。脱敏字符串和净化的 RAM 条目受设置限制。

## 什么是 `mesh_configure_experimental_self_approval`？

它是一个用于**实验性**自动自我批准的 Capability Mesh 提供商工具。它可以更改需要批准的 UCM 路由是在全局还是按路由 ID 进行自我批准。启用需要 `acknowledge_experimental_risk: true`，且仅用于风险自负的测试工作流。

## 多个插件可以添加工具吗？

可以。任何插件都可以注册 `IUmcpToolProvider`。工具名称带有提供商 ID 前缀。

## 客户端可以看到工具参数和风险吗？

可以。`tools/list` 包含每个工具的 `inputSchema`、可选的 `outputSchema` 和可选的工具注解。UCM 路由工具从路由绑定、架构清单、策略和副作用中派生这些内容。

## 如何在编辑器中检查挂载的工具？

打开 **Tiny Tools -> AI -> Universal MCP -> Open Control Panel**。Connected Functions 区域按插件对工具进行分组，支持输入/输出架构的延迟展开，并在访问之间缓存未更改的元数据。在 UCM 设置更改后，点击 **Refresh** 强制完全重新加载。

## 为什么 UMCP 在提供商运行前拒绝了我的工具参数？

`Validate Tool Arguments` 设置已启用。UMCP 会根据选定工具的 `inputSchema` 检查传入参数，并在缺失必需字段、不允许的未知字段、类型不匹配或枚举不匹配时返回 `invalid_tool_arguments`。

## 针对的是哪些虚幻引擎版本？

该插件专为虚幻引擎 5.x 代码插件编写，并使用 C++20 以确保当前的 UE 5.6 兼容性。

## 这是用于打包后的游戏 (Packaged Games) 吗？

不是。当前的服务器是用于本地工具和代理的编辑器基础架构。

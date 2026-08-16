<!-- doc-provenance: AKDB:plugins/UnifiedMcpServer/architecture.md; docs/architecture/plugins/UnifiedMcpServer/product-facts.yml; reconciled 2026-07-04 -->
# 第三方软件

Unified MCP Server **未随附第三方源代码、运行时二进制文件、AI 模型、Node.js、Python、`mcp-remote` 或独立的执行文件**。它是一个 C++ 虚幻引擎插件，使用标准的虚幻网络和 JSON API 托管本地 MCP-over-HTTP 服务器。

## 可选的、由用户安装的桥接工具（未随附）

| 软件 | 何时需要 | 如何集成 |
| --- | --- | --- |
| `mcp-remote` (Node.js) | 仅当您的 MCP 客户端仅支持 **Stdio** 且无法直接调用 HTTP 时 | 通过 npm 自行安装 (`npx mcp-remote …`) 并将其指向从握手文件中提取的服务器 URL。支持 HTTP 的客户端不需要它。请参阅 [QUICKSTART.md](QUICKSTART.md) §5。 |

支持 HTTP 的 MCP 客户端可以使用握手文件中的 Bearer Token 直接连接到 `http://127.0.0.1:<port>/mcp` — 不需要第三方软件。

**面向 Fab 的第三方软件声明：** 未随附第三方软件。

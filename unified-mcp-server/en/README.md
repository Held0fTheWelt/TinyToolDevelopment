<!-- doc-provenance: AKDB:plugins/UnifiedMcpServer/architecture.md; docs/architecture/plugins/UnifiedMcpServer/product-facts.yml; reconciled 2026-07-04 -->
# Unified MCP Server

Unified MCP Server is an Unreal Engine editor plugin that provides one local Model Context Protocol (MCP) endpoint for the whole project. Other plugins attach tools through a small modular-feature interface, so the server can expose new capabilities without depending on those plugins directly.

The plugin is intentionally infrastructure-only. It ships no external executable, no Node package, and no Python runtime. It hosts a loopback JSON-RPC 2.0 MCP endpoint inside the editor and lets providers register tools at runtime.

## Modules

| Module | Purpose |
| --- | --- |
| `UnifiedMcpServerInterface` | Public `IUmcpToolProvider` contract and tool descriptor/result types. |
| `UnifiedMcpServerEditor` | Editor host for the server, settings, token handling, provider registry, status control panel, and Tiny Tools menu entries. |

## Core Workflow

1. Enable the plugin in the project.
2. Open `Edit -> Editor Settings -> Plugins -> Unified MCP Server`.
3. Enable the local server and choose a port, or keep the default `8732`.
4. Use `Tiny Tools -> AI -> Universal MCP -> Open Control Panel` for status, lifecycle buttons, and the plugin-grouped connected function tree.
5. Start the server from the panel or `Tiny Tools -> AI -> Universal MCP -> Start Unified MCP Server`.
6. Read the connection data from `Saved/UnifiedMcpServer/agent/mcp_endpoint.json`.
7. Configure an MCP client to call `http://127.0.0.1:8732/mcp` with `Authorization: Bearer <token>`.

## Tool Providers

Provider plugins implement `IUmcpToolProvider` and register it as an Unreal modular feature. Exposed tool names use:

```text
<providerId>_<toolName>
```

When Unreal Capability Mesh is loaded, the built-in mesh provider exposes generic tools such as `mesh_list_capabilities`, `mesh_list_routes`, `mesh_configure_experimental_self_approval`, `mesh_dry_run_route`, and `mesh_execute_route`. It also flattens setup-declared UCM routes into direct `mesh_route_*` MCP tools. Those route tools publish route-derived MCP `inputSchema`, `outputSchema`, and tool annotations, so clients can inspect parameters and risk hints before calling them. `mesh_configure_experimental_self_approval` is **EXPERIMENTAL** and **use at your own risk**; enabling it requires explicit risk acknowledgement. Legacy direct provider bridges may still register product-specific tool names, but UCM routes are the preferred project setup path.

`tools/call` returns provider JSON as text content and, when the result is a JSON object, as MCP `structuredContent`. `initialize` advertises `tools.listChanged`, and `tools/list` includes a `_meta.toolsRevision` value so clients can refresh cached tool descriptors after UCM setup changes.

UMCP 1.0.3 adds access control on top of the single endpoint. Provider IDs can be disabled, and exposed tool names can be allowed or blocked with exact names or wildcard patterns. UMCP 1.0.4 adds profiles (`Default`, `Read Only`, `Automation`, `Experimental`) and annotation-derived tool groups. UMCP 1.0.5 adds scoped session tokens so different clients can use `default`, `read_only`, `automation`, or `experimental_admin` access through the same `/mcp` endpoint. UMCP 1.0.6 adds runtime Access Guard blocks and a secret-safe Access Journal for recent `tools/call` diagnostics. The same policy is enforced for both `tools/list` and `tools/call`. The Control Panel shows whether connected functions are exposed, blocked, hidden, or unavailable.

## Security

- The server binds to `127.0.0.1` only.
- The server is disabled by default.
- Requests require one bearer token from the handshake file.
- Provider/tool access control can hide tools from `tools/list` and block direct `tools/call` execution.
- Runtime Access Guard blocks are in-memory only and clear when the server stops.
- Tokens can be rotated from **Tiny Tools -> AI -> Universal MCP**.
- The handshake file is removed when the server stops.
- Request metadata is logged to `Saved/UnifiedMcpServer/logs/mcp_requests.jsonl`.
- Access diagnostics are logged to `Saved/UnifiedMcpServer/logs/access_audit.jsonl` with secret-looking argument keys omitted.

## Documentation

| Document | Purpose |
| --- | --- |
| [BUYER_GUIDE.md](BUYER_GUIDE.md) | Product overview, use cases, and limits. |
| [QUICKSTART.md](QUICKSTART.md) | First setup and client connection. |
| [UserManual.md](UserManual.md) | Day-to-day editor workflow. |
| [TechnicalOverview.md](TechnicalOverview.md) | Architecture and protocol behavior. |
| [INTEGRATION.md](INTEGRATION.md) | How provider plugins attach tools. |
| [SettingsReference.md](SettingsReference.md) | Settings and saved files. |
| [CodeDocumentation.md](CodeDocumentation.md) | Source layout and contracts. |
| [FAQ.md](FAQ.md) | Common buyer questions. |
| [TROUBLESHOOTING.md](TROUBLESHOOTING.md) | Common failures and fixes. |
| [ReleaseChecklist.md](ReleaseChecklist.md) | Release and Fab packaging checklist. |

## Packaging

`Config/FilterPlugin.ini` includes `/Documentation/...` and `/CHANGELOG.md` so Fab packages contain this documentation set.

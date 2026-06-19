# Unified MCP Server

Unified MCP Server is an Unreal Engine editor plugin that provides one local Model Context Protocol (MCP) endpoint for the whole project. Unreal Capability Mesh (UCM) is the preferred way to expose setup-declared cross-product routes through this endpoint. Other provider plugins can also attach tools through a small modular-feature interface, so the server can expose new capabilities without depending on those plugins directly.

The plugin is intentionally infrastructure-only. It ships no external executable, no Node package, and no Python runtime. It hosts a loopback JSON-RPC 2.0 MCP endpoint inside the editor and lets providers register tools at runtime.

## Fab Product

Unified MCP Server is available on Fab:

https://www.fab.com/listings/f5ded18c-38b5-4e12-88cb-120f484e282f

## Modules

| Module | Purpose |
| --- | --- |
| `UnifiedMcpServerInterface` | Public `IUmcpToolProvider` contract and tool descriptor/result types. |
| `UnifiedMcpServerEditor` | Editor host for the server, settings, token handling, provider registry, status control panel, and Tools menu entries. |

## Core Workflow

1. Enable the plugin in the project.
2. Open `Edit -> Project Settings -> Plugins -> Unified MCP Server`.
3. Enable the local server and choose a port, or keep the default `8732`.
4. Use `Tools -> AI -> Universal MCP -> Open Control Panel` for status, lifecycle buttons, and the plugin-grouped connected function tree.
5. Start the server from the panel or `Tools -> AI -> Universal MCP -> Start Unified MCP Server`.
6. Read the connection data from `Saved/UnifiedMcpServer/agent/mcp_endpoint.json`.
7. Configure an MCP client to call `http://127.0.0.1:8732/mcp` with `Authorization: Bearer <token>`.

## Tool Providers

Provider plugins implement `IUmcpToolProvider` and register it as an Unreal modular feature. This direct-provider path is useful for independent tool providers and no-UCM Freebie Bridges, while normal Tiny Tool Development cross-product workflows should use UCM routes. Exposed tool names use:

```text
<providerId>_<toolName>
```

When Unreal Capability Mesh is loaded, the built-in mesh provider exposes generic tools such as `mesh_list_capabilities`, `mesh_list_routes`, `mesh_configure_experimental_self_approval`, `mesh_dry_run_route`, and `mesh_execute_route`. It also flattens setup-declared UCM routes into direct `mesh_route_*` MCP tools. Those route tools publish route-derived MCP `inputSchema`, `outputSchema`, and tool annotations, so clients can inspect parameters and risk hints before calling them. `mesh_configure_experimental_self_approval` is **EXPERIMENTAL** and **use at your own risk**; enabling it requires explicit risk acknowledgement. Optional Freebie Bridges may still register product-specific tool names for no-UCM projects or adapter examples, but UCM routes are the preferred project setup path.

`tools/call` returns provider JSON as text content and, when the result is a JSON object, as MCP `structuredContent`. `initialize` advertises `tools.listChanged`, and `tools/list` includes a `_meta.toolsRevision` value so clients can refresh cached tool descriptors after UCM setup changes.

## Security

- The server binds to `127.0.0.1` only.
- The server is disabled by default.
- Requests require the bearer token from the handshake file.
- The token can be rotated from **Tools → AI → Universal MCP**.
- The handshake file is removed when the server stops.
- Request metadata is logged to `Saved/UnifiedMcpServer/logs/mcp_requests.jsonl`.

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

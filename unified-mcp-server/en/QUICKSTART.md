<!-- doc-provenance: AKDB:plugins/UnifiedMcpServer/architecture.md; docs/architecture/plugins/UnifiedMcpServer/product-facts.yml; reconciled 2026-07-04 -->
# Quick Start

## 1. Enable The Plugin

Enable `Unified MCP Server` in the Plugins browser and restart the editor if Unreal asks for it.

## 2. Enable The Server

Open:

```text
Edit -> Editor Settings -> Plugins -> Unified MCP Server
```

Turn on **Enable MCP Server**. Keep the default port `8732` unless another local service already uses it.

## 3. Start The Server

Use:

```text
Tiny Tools -> AI -> Universal MCP -> Start Unified MCP Server
```

For status, lifecycle buttons, and the plugin-grouped connected function tree, use:

```text
Tiny Tools -> AI -> Universal MCP -> Open Control Panel
```

The Connected Functions area groups tools by plugin, supports lazy schema expansion, and caches unchanged metadata between visits. Use **Refresh** after UCM setup changes to force a full reload.

In UMCP 1.0.3 and later, the control panel also shows access state. Disable a single-provider group to hide its tools from `tools/list` and block direct `tools/call` execution.

If the setting is enabled before editor startup, the server also attempts to start when the editor module loads.

## 4. Read The Handshake File

After startup, the editor writes:

```text
Saved/UnifiedMcpServer/agent/mcp_endpoint.json
```

Example shape:

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

Use the compatibility `token` field, or choose one token from `tokens`, as:

```text
Authorization: Bearer <selected-token>
```

## 5. Connect A Client

HTTP-capable MCP clients can call:

```text
http://127.0.0.1:8732/mcp
```

With the server running, open the control panel and click **Copy MCP Client Config**.
That copies a ready-to-paste `mcp.json` snippet with the live endpoint URL and the
current default bearer token. Paste it into your MCP client's configuration file.
After **Rotate Tokens**, copy the snippet again because the bearer token changed.

On `initialize`, UMCP negotiates `protocolVersion`: when your client requests a
supported version (`2025-06-18`, `2025-03-26`, or `2024-11-05`), the server echoes
that version; otherwise it responds with `2024-11-05`. A client probe of `GET /mcp`
returns HTTP 405 because UMCP uses the Streamable-HTTP JSON-response subset and does
not host a server-to-client SSE stream.

Stdio-only clients need a user-installed bridge such as `mcp-remote`. That bridge is not included with this plugin.

## 6. Add Tools (Optional)

The server runs on its own; this step adds tools for clients to call. You have two independent
options, and you only need what fits your project:

- **Your own (or any) plugin:** register an `IUmcpToolProvider` modular feature and its tools
  appear automatically as `<providerId>_<toolName>`. No catalog plugin is required. See
  [INTEGRATION.md](INTEGRATION.md).
- **Optional — Unreal Capability Mesh (UCM):** if you also own Unreal Capability Mesh, enabling it
  adds setup-declared `mesh_*` tools, so callers can run configured UCM routes (for example IIS
  context-pack, PRS placement, SCD migration-advice, and DataAsset/DataTable administration) via
  `mesh_execute_route` or the generated direct `mesh_route_*` tools. It also exposes
  `mesh_configure_experimental_self_approval`; that tool is **EXPERIMENTAL**, requires explicit
  risk acknowledgement when enabling, and is only for own-risk testing workflows.

Both are optional — the server, handshake, and client connection (steps 1–5) work with no provider
installed.

## 7. Stop Or Rotate

Use the Tiny Tools menu:

```text
Tiny Tools -> AI -> Universal MCP -> Stop Unified MCP Server
Tiny Tools -> AI -> Universal MCP -> Rotate MCP Token
```

Stopping removes the handshake file. Rotating rewrites it with fresh scoped tokens. Both actions are also available from the control panel.

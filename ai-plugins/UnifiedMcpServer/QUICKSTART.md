# Quick Start

## 1. Enable The Plugin

Enable `Unified MCP Server` in the Plugins browser and restart the editor if Unreal asks for it.

## 2. Enable The Server

Open:

```text
Edit -> Project Settings -> Plugins -> Unified MCP Server
```

Turn on **Enable MCP Server**. Keep the default port `8732` unless another local service already uses it.

## 3. Start The Server

Use:

```text
Tools -> AI -> Universal MCP -> Start Unified MCP Server
```

For status, lifecycle buttons, and the plugin-grouped connected function tree, use:

```text
Tools -> AI -> Universal MCP -> Open Control Panel
```

The Connected Functions area groups tools by plugin, supports lazy schema expansion, and caches unchanged metadata between visits. Use **Refresh** after UCM setup changes to force a full reload.

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
  "token": "<generated-token>"
}
```

Use the token as:

```text
Authorization: Bearer <generated-token>
```

## 5. Connect A Client

HTTP-capable MCP clients can call:

```text
http://127.0.0.1:8732/mcp
```

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

Use the Tools menu:

```text
Tools -> AI -> Universal MCP -> Stop Unified MCP Server
Tools -> AI -> Universal MCP -> Rotate MCP Token
```

Stopping removes the handshake file. Rotating rewrites it with a fresh token. Both actions are also available from the control panel.

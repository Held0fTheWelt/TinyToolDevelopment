# Troubleshooting

## Client Gets 401 Unauthorized

Check that the client sends:

```text
Authorization: Bearer <token>
```

Read the current token from:

```text
Saved/UnifiedMcpServer/agent/mcp_endpoint.json
```

If the token was rotated, update the client configuration.

## Handshake File Is Missing

Possible causes:

- server is not running
- server failed to bind the configured port
- plugin is disabled
- editor has not started the module yet

Start the server from:

```text
Tools -> AI -> Universal MCP -> Start Unified MCP Server
```

## Port Is Already In Use

Change the port in:

```text
Edit -> Project Settings -> Plugins -> Unified MCP Server
```

Then restart the server.

## `tools/list` Returns No Tools

Unified MCP Server is only the host. Enable Unreal Capability Mesh for generic `mesh_*` tools, or enable another provider plugin. Also check that the provider reports ready state and has registered its modular feature.

If generic `mesh_*` tools appear but no `mesh_route_*` tools appear, run `mesh_reload_setup` or click **Reload Setup** in the Capability Mesh panel, then refresh the MCP client. Route tools are generated from the active `Config/UnrealCapabilityMesh` route manifests.

If `mesh_configure_experimental_self_approval` appears, treat it as an **EXPERIMENTAL** own-risk testing tool. Enabling it requires `acknowledge_experimental_risk: true` and changes Capability Mesh approval behavior for selected routes or all approval-gated routes.

If self automatic approval was changed in the UCM Routes UI but the MCP client still shows old route descriptions, call `tools/list` again or reconnect/refresh the client. UMCP reloads UCM setup before listing route tools, and `mesh_list_routes` returns the current `experimental_self_approval_*` state directly.

## Connected Functions Look Stale In The Control Panel

The control panel caches tool metadata for faster repeat visits. After changing UCM setup, adding providers, or reloading routes, click **Refresh** in the control panel to force a full connected-function reload. Start/stop and expand/collapse reuse the cache when the underlying snapshot is unchanged.

## Stdio Client Cannot Connect Directly

The plugin exposes HTTP transport. Stdio-only clients need a user-installed bridge such as `mcp-remote`.

## Tool Call Returns Unknown Tool

Check the exposed name from `tools/list`. Use the prefixed name:

```text
<providerId>_<toolName>
```

Do not call provider-local names directly.

## Build Fails On UE 5.6 With C++ Standard Errors

Ensure the UMCP modules and dependent bridge modules compile with C++20. UE 5.6 engine headers use C++20 syntax in core headers.

## Request Log Location

Request metadata is written to:

```text
Saved/UnifiedMcpServer/logs/mcp_requests.jsonl
```

Use it to inspect method names, status codes, latency, and error codes.

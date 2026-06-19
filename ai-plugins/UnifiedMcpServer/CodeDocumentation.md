# Code Documentation

## Source Layout

```text
Source/UnifiedMcpServerInterface
Source/UnifiedMcpServerEditor
```

## Interface Module

### `IUmcpToolProvider.h`

Defines the modular-feature contract that provider plugins implement.

Important methods:

| Method | Purpose |
| --- | --- |
| `GetProviderId` | Stable prefix used in exposed tool names. |
| `GetProviderDisplayName` | Human-readable provider name. |
| `GetToolDescriptors` | Supplies provider-local tool metadata and schemas. |
| `InvokeTool` | Executes one provider-local tool. |
| `IsReady` | Optional readiness signal. |

### `UmcpToolTypes.h`

Defines:

- `FUmcpToolDescriptor`
- `FUmcpToolInvocation`
- `FUmcpToolResult`
- `EUmcpToolStatus`

`FUmcpToolDescriptor` carries provider-local name, description, `InputSchemaJson`, optional `OutputSchemaJson`, and optional MCP `AnnotationsJson`.

## Editor Module

### `UmcpServer`

Owns the HTTP route, JSON-RPC method handling, bearer-token validation, handshake file, and request log.

### `UmcpProviderRegistry`

Aggregates all registered `IUmcpToolProvider` modular features. It builds the MCP tool list and routes calls by exposed tool name.

### `UmcpServerManager`

Owns the current server instance and exposes start, stop, restart, token rotation, and status.

### `UnifiedMcpServerEditorModule`

Starts the server when settings allow it, registers **Tools → AI → Universal MCP** menu entries, and shuts the server down during module unload.

### `SUmcpControlPanel`

Editor status and lifecycle panel opened from **Tools → AI → Universal MCP → Open Control Panel**.

| Area | Implementation notes |
| --- | --- |
| Status | Live server snapshot from `FUmcpServerManager`. |
| Connected Functions | Plugin-grouped tree built from `FUmcpProviderRegistry` plus Capability Mesh gateway JSON (`list_capabilities`, `list_routes`). |
| Expand/collapse | `ExpandedToolPlugins` and `ExpandedToolRows` preserve UI state; only affected widgets refresh. |
| Caching | Snapshot fingerprint, mesh JSON cache, and parsed schema cache avoid redundant gateway calls and schema parsing. |
| UCM route grouping | `ApplyMeshRouteMetadata` assigns flattened `mesh_route_*` rows to the owning plugin via the route's primary capability `provider_id`. |

### `FCapabilityMeshUmcpToolProvider`

Soft Capability Mesh provider resolved by reflection. `GetProviderDisplayName()` returns **Unreal Capability Mesh** for generic mesh host tools. Flattened route tools inherit provider metadata from UCM capabilities during control-panel row assembly.

### `UmcpSettings`

Defines project settings for enable/disable, port selection, and optional tool argument validation.

### `UUmcpEditorBlueprintLibrary`

Optional editor-only Blueprint surface for lifecycle and diagnostics. It does **not** expose MCP tool registration or invocation.

| Function | Purpose |
| --- | --- |
| `IsUnifiedMcpEnabledByConfig` | Reads the project setting without starting the server. |
| `StartUnifiedMcpServer` / `StopUnifiedMcpServer` | Same behavior as **Tools → AI → Universal MCP** menu entries. |
| `RotateUnifiedMcpToken` | Rotates the bearer token when the server is running. |
| `IsUnifiedMcpServerRunning` | True when the loopback HTTP route is active. |
| `GetUnifiedMcpProviderCount` | Count of attached `IUmcpToolProvider` modular features. |
| `GetUnifiedMcpConfiguredPort` | Port from project settings. |
| `GetUnifiedMcpHandshakeFilePath` | Absolute path to `Saved/UnifiedMcpServer/agent/mcp_endpoint.json`. |
| `GetUnifiedMcpEndpointJson` | Reads the handshake JSON when present. |
| `GetUnifiedMcpServerStatus` | Returns `FUmcpServerBlueprintStatus`. |

Product rule: UMCP stays a C++ host plus `IUmcpToolProvider`. Blueprint is only for server lifecycle/diagnostics, never for tool implementation or provider registration.

## Request Flow

1. Client POSTs JSON-RPC to `/mcp`.
2. Server extracts `Authorization: Bearer <token>`.
3. Server validates token against the active session token.
4. JSON-RPC method is parsed.
5. Tool list/calls are resolved through `FUmcpProviderRegistry`.
6. If enabled, arguments are validated against the selected descriptor `inputSchema`.
7. Provider JSON results are returned as text content and, for JSON objects, as `structuredContent`.
8. Request metadata is appended to JSONL.
9. Response is returned as JSON.

## Error Handling

- Missing or wrong bearer token returns HTTP 401 with JSON-RPC error.
- Invalid JSON returns parse error.
- Unknown JSON-RPC methods return method-not-found.
- Unknown tool names return a `tools/call` result with `isError: true`.

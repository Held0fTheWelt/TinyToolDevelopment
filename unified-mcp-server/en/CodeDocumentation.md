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

Owns the HTTP route, JSON-RPC method handling, scoped bearer-token validation, handshake file, and request log.

### `UmcpProviderRegistry`

Aggregates all registered `IUmcpToolProvider` modular features. It builds the MCP tool list, applies UMCP provider/tool access policy, statically resolves exposed tool access before invocation, and routes calls by exposed tool name.

### `UmcpServerManager`

Owns the current server instance, runtime Access Guard, and Access Journal. Exposes start, stop, restart, token rotation, status, recent access entries, and runtime block actions.

### `UmcpAccessGuard`

In-memory runtime block layer. Blocks can be global or scoped to a session token id. The guard is checked for both `tools/list` filtering and `tools/call` before provider invocation. Server stop clears all runtime blocks.

### `UmcpAccessJournal` and `UmcpAccessRedaction`

`UmcpAccessJournal` keeps a bounded in-memory ring for editor diagnostics and writes redacted JSONL to `Saved/UnifiedMcpServer/logs/access_audit.jsonl`. `UmcpAccessRedaction` removes secret-looking keys, caps redacted disk strings, and caps sanitized RAM argument JSON.

### `UnifiedMcpServerEditorModule`

Starts the server when settings allow it, registers **Tiny Tools -> AI -> Universal MCP** menu entries, and shuts the server down during module unload.

### `SUmcpControlPanel`

Editor status and lifecycle panel opened from **Tiny Tools -> AI -> Universal MCP -> Open Control Panel**.

| Area | Implementation notes |
| --- | --- |
| Status | Live server snapshot from `FUmcpServerManager`. |
| Access Activity tab | Recent `tools/call` entries from `FUmcpAccessJournal`, plus explicit token/tool block, unblock, refresh, and clear-runtime-block controls. |
| Connected Functions | Plugin-grouped tree built from `FUmcpProviderRegistry` plus Capability Mesh gateway JSON (`list_capabilities`, `list_routes`). It shows exposed, blocked, hidden, and unavailable functions, including read-only/destructive/idempotent/open-world annotation hints and derived tool groups when providers publish them. |
| Expand/collapse | `ExpandedToolPlugins` and `ExpandedToolRows` preserve UI state; only affected widgets refresh. |
| Caching | Snapshot fingerprint, mesh JSON cache, and parsed schema cache avoid redundant gateway calls and schema parsing. |
| UCM route grouping | `ApplyMeshRouteMetadata` assigns flattened `mesh_route_*` rows to the owning plugin via the route's primary capability `provider_id`. |

### `FCapabilityMeshUmcpToolProvider`

Soft Capability Mesh provider resolved by reflection. `GetProviderDisplayName()` returns **Unreal Capability Mesh** for generic mesh host tools. Flattened route tools inherit provider metadata from UCM capabilities during control-panel row assembly.

### `UmcpSettings`

Defines editor settings for enable/disable, port selection, optional tool argument validation, access profile, disabled provider IDs, allowed/blocked tool names, and allowed/blocked tool groups.

### `UUmcpEditorBlueprintLibrary`

Optional editor-only Blueprint surface for lifecycle and diagnostics. It does **not** expose MCP tool registration or invocation.

| Function | Purpose |
| --- | --- |
| `IsUnifiedMcpEnabledByConfig` | Reads the project setting without starting the server. |
| `StartUnifiedMcpServer` / `StopUnifiedMcpServer` | Same behavior as **Tiny Tools -> AI -> Universal MCP** menu entries. |
| `RotateUnifiedMcpToken` | Rotates scoped bearer tokens when the server is running. |
| `IsUnifiedMcpServerRunning` | True when the loopback HTTP route is active. |
| `GetUnifiedMcpProviderCount` | Count of attached `IUmcpToolProvider` modular features. |
| `GetUnifiedMcpRecentAccessEntries` | Returns recent secret-redacted access journal entries. |
| `BlockUnifiedMcpTool` / `UnblockUnifiedMcpTool` | Applies or removes a runtime guard block for one tool. |
| `ClearUnifiedMcpRuntimeBlocks` | Clears all runtime guard blocks. |
| `GetUnifiedMcpConfiguredPort` | Port from editor settings. |
| `GetUnifiedMcpHandshakeFilePath` | Absolute path to `Saved/UnifiedMcpServer/agent/mcp_endpoint.json`. |
| `GetUnifiedMcpEndpointJson` | Reads the handshake JSON when present. |
| `GetUnifiedMcpServerStatus` | Returns `FUmcpServerBlueprintStatus`. |

Product rule: UMCP stays a C++ host plus `IUmcpToolProvider`. Blueprint is only for server lifecycle/diagnostics, never for tool implementation or provider registration.

## Request Flow

1. Client POSTs JSON-RPC to `/mcp`.
2. Server extracts `Authorization: Bearer <token>`.
3. Server resolves the token to the default session or a scoped profile override.
4. JSON-RPC method is parsed.
5. Tool list/calls are resolved through `FUmcpProviderRegistry`.
6. Static provider/tool access policy is applied without invoking the provider. Hidden tools are omitted from `tools/list`; blocked calls return `tool_access_denied`.
7. Runtime Access Guard blocks are applied. Runtime-blocked calls return `runtime_access_denied`.
8. If enabled, arguments are validated against the selected descriptor `inputSchema`.
9. Provider JSON results are returned as text content and, for JSON objects, as `structuredContent`.
10. Request metadata is appended to JSONL, and `tools/call` access diagnostics are appended through the redaction layer.
11. Response is returned as JSON.

## Error Handling

- Missing or wrong bearer token returns HTTP 401 with JSON-RPC error.
- Invalid JSON returns parse error.
- Unknown JSON-RPC methods return method-not-found.
- Unknown tool names return a `tools/call` result with `isError: true`.
- Tools blocked by access policy return a `tools/call` result with `isError: true` and `tool_access_denied`.
- Tools blocked by the runtime guard return a `tools/call` result with `isError: true` and `runtime_access_denied`.

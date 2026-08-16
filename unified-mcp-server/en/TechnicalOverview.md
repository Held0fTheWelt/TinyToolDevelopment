# Technical Overview

## Architecture

Unified MCP Server has two modules:

| Module | Type | Responsibility |
| --- | --- | --- |
| `UnifiedMcpServerInterface` | Runtime | Shared provider contract and tool data structs. |
| `UnifiedMcpServerEditor` | Editor | HTTP server, JSON-RPC routing, token handling, settings, request log, and menu actions. |

The server module depends on Unreal's `HTTPServer` module and binds a POST route at:

```text
/mcp
```

It listens only on `127.0.0.1` through the configured local port.

## Provider Discovery

Providers implement `IUmcpToolProvider` and register with Unreal modular features using:

```cpp
IUmcpToolProvider::GetModularFeatureName()
```

`FUmcpProviderRegistry` queries `IModularFeatures` at call time. This keeps the host decoupled from specific tools and allows provider plugins to attach or detach while the editor is running.

`UnifiedMcpServerEditor` also registers a soft Capability Mesh provider. It does not include Capability Mesh headers or require a compile-time dependency; it resolves `/Script/UnrealCapabilityMesh.CapabilityMeshMcpGatewaySubsystem` by reflection and exposes `mesh_*` tools only when the gateway is available. In addition to the generic gateway tools, it lists Capability Mesh routes through the gateway and publishes each route as a flattened MCP tool named `mesh_route_<sanitized_route_id>_<hash>`.

## Tool Naming

Provider-local tools are exposed as:

```text
<providerId>_<localToolName>
```

Provider IDs should be simple tokens without underscores. The prefix prevents name collisions between independently registered provider plugins, including no-UCM Freebie Bridges.

## Protocol Behavior

The server implements a small MCP-compatible JSON-RPC surface:

- `initialize`
- `notifications/initialized`
- `ping`
- `tools/list`
- `tools/call`

`tools/list` serializes provider descriptors into MCP tool entries after UMCP access policy is applied. Entries include `inputSchema`, optional `outputSchema`, and optional MCP tool `annotations`. Capability Mesh route descriptors reload UCM setup before listing so approval/self-approval status changes are reflected on the next `tools/list`. The server advertises `tools.listChanged: true` and includes `_meta.toolsRevision` in `tools/list`; simple HTTP clients should re-run `tools/list` or reconnect when the revision changes.

`tools/call` parses the tool prefix, applies the same UMCP access policy used by `tools/list`, optionally validates arguments against the tool `inputSchema` when `Validate Tool Arguments` is enabled, routes to the matching provider, and returns text content containing the provider result JSON. When the provider result is a JSON object, the same object is also returned as MCP `structuredContent`.

## Access Policy

Access control stays on the single UMCP endpoint rather than splitting providers across ports. `DisabledProviderIds` hides and blocks every tool from a provider. `AccessProfile` applies high-level modes: `Default`, `Read Only`, `Automation`, and `Experimental`. `BlockedToolNames` and `BlockedToolGroups` hide and block exact names, wildcard patterns, or annotation-derived groups. `AllowedToolNames` and `AllowedToolGroups` are optional; when either contains entries, matching by name or group is enough to expose the tool unless a stronger block/profile rule applies. Direct calls to hidden tools return `tool_access_denied` instead of invoking the provider.

UMCP 1.0.6 adds a runtime Access Guard on top of persistent policy. Runtime blocks are in-memory editor-session state keyed either globally or by scoped token id. They are checked after the static registry precheck and before provider invocation, so a blocked tool is removed from `tools/list` for the affected request context and direct calls return `runtime_access_denied`. `FUmcpServer::Stop` clears all runtime blocks.

Flattened Capability Mesh route tools route back through `DryRunRouteJson` or `ExecuteRouteJson` depending on their `mode` argument, so route policy and approval behavior remains owned by Capability Mesh. Their `inputSchema` is derived from route step input bindings and the UCM schema registry. Their `outputSchema` describes the gateway response envelope and the expected `report.route_output` fields. Their annotations are derived from route policy and side effects, including read-only, destructive, idempotent, and open-world hints.

The Capability Mesh provider also exposes `mesh_configure_experimental_self_approval`. This is explicitly **EXPERIMENTAL** and **use at your own risk**; it calls `ConfigureExperimentalSelfApprovalJson` to read or change UCM self automatic approval globally or for selected route ids, and enabling requires `acknowledge_experimental_risk: true`.

`mesh_list_routes` is the current route-status source. It includes `experimental_self_approval_all_routes`, `experimental_self_approved_route_ids`, per-route `experimental_self_approval_enabled`, and the route-derived schema/annotation objects used for flattened `mesh_route_*` tools. Some MCP clients cache `tools/list` descriptions, so clients may still need a tool-list refresh or reconnect to redraw cached descriptions after an external UI change.

## Control Panel UI

The **Open Control Panel** action renders `SUmcpControlPanel`:

1. Collects registry tools and Capability Mesh gateway JSON on a background thread.
2. Builds plugin-grouped rows; flattened UCM routes use capability `provider_id` / `display_name` for grouping in the UI.
3. Parses input/output schemas lazily when a tool row is expanded.
4. Skips rebuild when the snapshot fingerprint is unchanged (except when **Refresh** is clicked).
5. Switches the per-plugin column header between a four-column collapsed layout and a six-column expanded layout when the first tool in that plugin is expanded.
6. Splits the main body into Connected Functions and Access Activity tabs. Access Activity reads from the in-memory access journal and exposes explicit runtime block/unblock controls for token/tool pairs.

Generic mesh host tools remain under **Unreal Capability Mesh** in the Connected Functions tree.

## Authentication

On start, the server creates random GUID session tokens. Clients must pass one of them:

```text
Authorization: Bearer <token>
```

The default compatibility token is written as `token`; all scoped tokens are written under `tokens`:

```text
Saved/UnifiedMcpServer/agent/mcp_endpoint.json
```

On POSIX platforms, the plugin attempts to restrict the agent directory and handshake file to the owner. On Windows, the file inherits user-profile ACLs.

UMCP 1.0.5 keeps one local endpoint and issues four session tokens. `default` follows the configured `AccessProfile`; `read_only`, `automation`, and `experimental_admin` force their matching profile for `tools/list` and `tools/call`. Provider disabled settings, tool/group blocklists, and allowlists still apply to every token.

## Logging

Request metadata is appended as JSONL:

```text
Saved/UnifiedMcpServer/logs/mcp_requests.jsonl
```

Each line includes timestamp, method, HTTP status, latency, and error code.

Semantic access diagnostics are appended separately:

```text
Saved/UnifiedMcpServer/logs/access_audit.jsonl
```

The access journal records `tools/call` timestamp, scoped token id, client hint, tool name, non-secret argument keys, outcome, error code, and latency. Argument diagnostics are produced through the redaction layer: secret-looking keys are omitted, strings in disk JSONL are bounded, and the sanitized RAM copy is capped by settings. Raw arguments are not stored in the journal.

## Lifecycle

`FUnifiedMcpServerEditorModule` starts the server when the config setting is enabled, and always registers **Tiny Tools -> AI -> Universal MCP** menu actions. `FUmcpServerManager` owns the active server instance, exposes status, and handles stop/restart/token rotation.

## Build Notes

Modules use `BuildSettingsVersion.Latest` and C++20. UE 5.6 engine headers require C++20 syntax in several core headers.

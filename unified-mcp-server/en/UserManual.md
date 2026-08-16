<!-- doc-provenance: AKDB:plugins/UnifiedMcpServer/architecture.md; docs/architecture/plugins/UnifiedMcpServer/product-facts.yml; reconciled 2026-07-04 -->
# User Manual

## Opening The Settings

Unified MCP Server is configured under:

```text
Edit -> Editor Settings -> Plugins -> Unified MCP Server
```

Settings:

| Setting | Default | Meaning |
| --- | --- | --- |
| Enable MCP Server | off | Allows the editor module to run the local MCP server. |
| Server Port | 8732 | TCP port used on `127.0.0.1`. |
| Validate Tool Arguments | off | Optionally validates `tools/call` arguments against each tool `inputSchema` before provider invocation. |
| Access Profile | Default | High-level exposure mode: Default, Read Only, Automation, or Experimental. |
| Disabled Provider IDs | empty | Hides and blocks every tool from matching provider IDs. |
| Allowed Tool Names | empty | Optional allowlist of exposed tool names or wildcard patterns. Empty means allow all tools unless blocked. |
| Blocked Tool Names | empty | Hides and blocks exposed tool names or wildcard patterns. |
| Allowed Tool Groups | empty | Optional allowlist of annotation-derived groups such as `read_only`, `non_destructive`, or `idempotent`. |
| Blocked Tool Groups | empty | Hides and blocks annotation-derived groups such as `risky`, `destructive`, or `open_world`. |
| Enable Access Journal | on | Writes secret-redacted access diagnostics for `tools/call`. |
| Access Journal Ring Capacity | 500 | Recent entries kept in memory for Control Panel and Blueprint diagnostics. |
| Access Journal Max File Bytes | 5242880 | Maximum `access_audit.jsonl` size before one-file rotation. |

## Tiny Tools Menu

The editor adds lifecycle and status actions under **Tiny Tools -> AI -> Universal MCP**:

| Action | Result |
| --- | --- |
| Open Control Panel | Opens the UMCP status panel with lifecycle buttons and the plugin-grouped Connected Functions tree. |
| Start Unified MCP Server | Starts the loopback HTTP endpoint. |
| Stop Unified MCP Server | Stops the endpoint and removes the handshake file. |
| Rotate MCP Token | Generates new scoped bearer tokens and rewrites the handshake file. |

The **AI** section groups Unified MCP Server with other Tiny Tool Development AI plugins such as Internal Index Service.

## Control Panel

The control panel shows:

| Area | Details |
| --- | --- |
| Status | Running/stopped state, startup setting, endpoint URL, token presence/count, request count, provider count, tool count, and handshake file path. |
| Actions | Start, stop, rotate tokens, open the agent folder, and refresh. |
| Tabs | Connected Functions for providers/tools/schemas, and Access Activity for recent tool calls and runtime block controls. |
| Connected Functions | Expandable plugin groups with provider toggles, tool rows, access/readiness state, MCP tool names, descriptions, and lazy-loaded input/output schema tables. |
| Access Activity | Recent tool calls with token/client/outcome details, runtime block count, refresh, token/tool block/unblock, and clear-runtime-block actions. |

### Connected Functions Layout

Connected Functions uses a hierarchical tree similar to the Capability Mesh route catalog:

1. **Plugin group** — one row per plugin with an interface count and, when the group maps to one provider, an enable/disable access button. Click the arrow to show or hide that plugin's tools.
2. **Tool row** — one row per attached MCP tool or setup-declared UCM capability. Click the arrow to show or hide input/output schema tables for that tool.

Column layout depends on expansion state **within each plugin group**:

| State | Columns |
| --- | --- |
| All tools collapsed | `Provider`, `Ready`, `Tool`, `Description` (wide) |
| Any tool expanded | `Provider`, `Ready`, `Tool`, `Input`, `Output`, `Description` |

**Provider grouping:** direct provider tools appear under their `GetProviderDisplayName()`. Flattened UCM route tools (`mesh_route_*`) appear under the **owning plugin** from Capability Mesh capability metadata (for example Internal Index Service or SmartContentDiet), not under the mesh host entry. Generic mesh host tools such as `mesh_list_routes` and `mesh_reload_setup` remain under **Unreal Capability Mesh**.

**Performance:** the panel loads tool metadata asynchronously. Unchanged data is served from cache on repeat opens, start/stop, and expand/collapse. Use **Refresh** to force a full reload after UCM setup changes.

Rows marked `Needs approval` are approval-gated UCM capabilities. Their tooltip points to the **EXPERIMENTAL** self automatic approval path in UCM Routes or `mesh_configure_experimental_self_approval`; use that only for own-risk testing.

Rows marked `Blocked` or `Hidden` are not exposed to MCP clients. UMCP removes them from `tools/list` and returns `tool_access_denied` if a client still calls the tool name directly.

Runtime blocks from the **Access Activity** tab are temporary editor-session blocks. They do not write to editor settings, hide the tool from `tools/list` for the affected token, reject direct calls with `runtime_access_denied`, and are cleared when the server stops.

Tool descriptions include MCP annotation hints when providers publish them, such as read-only, destructive, idempotent, or open-world behavior. The panel also shows derived groups used by profile and group access policy.

## Connection Files

Handshake file:

```text
Saved/UnifiedMcpServer/agent/mcp_endpoint.json
```

Request log:

```text
Saved/UnifiedMcpServer/logs/mcp_requests.jsonl
```

Access journal:

```text
Saved/UnifiedMcpServer/logs/access_audit.jsonl
```

The handshake file contains the local host, port, compatibility `token`, and scoped `tokens`. Treat it like a local credential.

The access journal omits secret-looking argument keys such as token, secret, password, API key, authorization, and bearer fields.

## Supported MCP Calls

The server handles these JSON-RPC methods:

| Method | Behavior |
| --- | --- |
| `initialize` | Returns protocol version, tool capability, and server info. |
| `notifications/initialized` | Acknowledges client initialization. |
| `ping` | Returns an empty result. |
| `tools/list` | Returns all tools from registered providers, including `inputSchema`, optional `outputSchema`, optional tool `annotations`, and `_meta.toolsRevision`. |
| `tools/call` | Routes a provider-prefixed tool name to its provider and returns JSON results as text plus `structuredContent` when possible. |

Unknown methods return a JSON-RPC method-not-found error.

## Editor Job Tools

UMCP exposes read-only job aggregation tools when Unreal Capability Mesh is available:

| Tool | Purpose |
| --- | --- |
| `jobs_list` | Merges recent jobs from fixed UCM routes for IIS, SmartContentDiet, LLM Store, and UMCP. Optional `provider_id` and `max_count` arguments narrow the result. |
| `jobs_status` | Looks up one job id across the same route table and returns the matching source provider id. |

The source plugins publish their own editor job list/status through UCM routes and do not depend on UMCP. If UCM or one route is unavailable, aggregation skips that route and still returns jobs from available providers.

## Working With Providers

Unified MCP Server does not contain project tools by itself. Providers add them. A provider supplies descriptors, input schemas, and invocation logic through `IUmcpToolProvider`.

When a provider is installed, tools appear as:

```text
provider_tool
```

For example:

```text
mesh_route_iis_agent_search_v1_<hash>
```

When Unreal Capability Mesh is loaded, UMCP exposes generic mesh tools:

```text
mesh_reload_setup
mesh_list_capabilities
mesh_list_routes
mesh_configure_experimental_self_approval
mesh_dry_run_route
mesh_execute_route
mesh_invoke_endpoint
```

UMCP also publishes each declared Capability Mesh route as a flattened MCP tool:

```text
mesh_route_<sanitized_route_id>_<hash>
```

Flattened route tools accept `mode: "execute"` or `mode: "dry_run"`. If `input` or
`input_json` is omitted, remaining arguments are treated as the route input object.
For routes that internally bind a serialized `request_json`, UMCP mirrors flattened
arguments into `request_json` automatically. Each flattened route tool publishes a
route-derived MCP `inputSchema`, `outputSchema`, and annotations such as
`readOnlyHint`, `destructiveHint`, and `openWorldHint`. Mutating routes still pass
through Capability Mesh policy and approval checks.

Use `mesh_execute_route` for mutating operations so Capability Mesh route policy and approval checks stay active.

`mesh_configure_experimental_self_approval` is explicitly **EXPERIMENTAL** and **use at your own risk**. It can read or change Capability Mesh self automatic approval globally or for selected route ids. Enabling it requires `acknowledge_experimental_risk: true`.

## Operational Notes

- Use a unique port per editor instance.
- Rotate the tokens after sharing logs or screenshots that may show the handshake file.
- Stop the server when an external agent no longer needs access.
- If no provider plugins are enabled, `tools/list` can legitimately return an empty list.

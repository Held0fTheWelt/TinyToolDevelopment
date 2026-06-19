# Settings Reference

Settings live in `UUmcpSettings` and are stored in editor config.

Open:

```text
Edit -> Project Settings -> Plugins -> Unified MCP Server
```

## Server

| Setting | Config field | Default | Notes |
| --- | --- | --- | --- |
| Enable MCP Server | `bEnableServer` | `false` | Off by default. When true, the editor module attempts to start the server on startup. |
| Server Port | `ServerPort` | `8732` | Local TCP port for the loopback endpoint. Valid range: 1-65535. |

## Tools

| Setting | Config field | Default | Notes |
| --- | --- | --- | --- |
| Validate Tool Arguments | `bValidateToolArguments` | `false` | When enabled, UMCP validates incoming `tools/call` arguments against each tool `inputSchema` before invoking the provider. Validation is lightweight and top-level: required fields, unknown fields for `additionalProperties:false`, primitive types, and enums. |

## Access Control

| Setting | Config field | Default | Notes |
| --- | --- | --- | --- |
| Access Profile | `AccessProfile` | `Default` | High-level exposure mode. `Default` preserves legacy exposure, `Read Only` exposes only tools annotated as read-only, `Automation` hides risky/destructive/open-world/unclassified tools, and `Experimental` intentionally allows risky tools unless manually blocked. |
| Disabled Provider IDs | `DisabledProviderIds` | empty | Provider IDs hidden from `tools/list` and blocked at `tools/call` time. The Control Panel can toggle single-provider groups into this list. |
| Allowed Tool Names | `AllowedToolNames` | empty | Optional allowlist of exposed MCP tool names or wildcard patterns such as `iis_search` or `mesh_route_*`. Empty means all tools are allowed unless disabled or blocked. |
| Blocked Tool Names | `BlockedToolNames` | empty | Exposed MCP tool names or wildcard patterns hidden from `tools/list` and blocked at `tools/call` time. |
| Allowed Tool Groups | `AllowedToolGroups` | empty | Optional allowlist of annotation-derived groups such as `read_only`, `non_destructive`, `idempotent`, `risky`, `destructive`, `open_world`, or `unclassified`. |
| Blocked Tool Groups | `BlockedToolGroups` | empty | Annotation-derived groups hidden from `tools/list` and blocked at `tools/call` time. |

Policy order is provider disabled, explicit tool block, access profile, blocked group, optional tool/group allowlists, then exposed. If either allowlist contains entries, a tool is exposed when its name or at least one group matches. The same policy is used for `tools/list` and `tools/call`.

Runtime Access Guard blocks created from the Control Panel or Blueprint helpers are session-local and sit after persistent policy. They hide matching tools from `tools/list`, reject direct `tools/call`, and are cleared when the server stops.

Job aggregation tools are read-only, but they still pass through the same provider/tool/profile policy as every other MCP tool. Blocking `jobs_*` or the `jobs` provider hides both `jobs_list` and `jobs_status`.

## Access Journal

| Setting | Config field | Default | Notes |
| --- | --- | --- | --- |
| Enable Access Journal | `bEnableAccessJournal` | `true` | Writes semantic `tools/call` access diagnostics. |
| Access Journal Ring Capacity | `AccessJournalRingCapacity` | `500` | Recent entries kept in RAM for the Control Panel and Blueprint diagnostics. |
| Access Journal Max File Bytes | `AccessJournalMaxFileBytes` | `5242880` | Maximum `access_audit.jsonl` size before one-file rotation. |
| Access Journal Redacted String Limit | `AccessJournalRedactedStringLimit` | `128` | Maximum string length in redacted JSONL arguments. |
| Access Journal Max RAM Entry Bytes | `AccessJournalMaxRamEntryBytes` | `8192` | Maximum sanitized argument JSON retained in memory per entry. Secret-looking keys are omitted. |

## Generated Files

| File | Purpose |
| --- | --- |
| `Saved/UnifiedMcpServer/agent/mcp_endpoint.json` | Connection handshake containing host, port, compatibility token, and scoped session tokens. |
| `Saved/UnifiedMcpServer/logs/mcp_requests.jsonl` | Request metadata log. |
| `Saved/UnifiedMcpServer/logs/access_audit.jsonl` | Secret-redacted semantic access journal for `tools/call`. |

## Security Defaults

- Server disabled by default.
- Loopback host only.
- Bearer token required.
- Tokens can be rotated from **Tools → AI → Universal MCP**.
- Handshake file is deleted when the server stops.
- UMCP 1.0.5 writes `default`, `read_only`, `automation`, and `experimental_admin` session tokens. The legacy `token` field remains as the default token for compatibility.
- UMCP 1.0.6 omits secret-looking argument keys from access diagnostics, including token, secret, password, API key, authorization, and bearer fields.

## Port Selection

Use a different port if:

- another editor instance is already using `8732`
- a local service is bound to the same port
- separate projects need separate MCP endpoints

The client URL is:

```text
http://127.0.0.1:<ServerPort>/mcp
```

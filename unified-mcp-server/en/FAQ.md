<!-- doc-provenance: AKDB:plugins/UnifiedMcpServer/architecture.md; docs/architecture/plugins/UnifiedMcpServer/product-facts.yml; reconciled 2026-07-04 -->
# FAQ

## Does this plugin include an AI model?

No. Unified MCP Server is connection infrastructure. It exposes tools from provider plugins to local MCP clients.

## Does it include a standalone executable?

No. The server runs inside the Unreal Editor and ships no external executable.

## Does it include Node.js, Python, or mcp-remote?

No. Stdio-only clients may need a user-installed bridge such as `mcp-remote`, but that is not bundled.

## Is the server enabled by default?

No. It is off by default and must be enabled in Editor Settings or started manually from **Tiny Tools -> AI -> Universal MCP**.

## Does it listen on the network?

No. It binds to `127.0.0.1`.

## How are requests authenticated?

The server generates scoped bearer tokens on start. Clients read them from `Saved/UnifiedMcpServer/agent/mcp_endpoint.json` and send one token in the `Authorization` header.

## Does it support multiple scoped tokens?

Yes. UMCP 1.0.5 writes `default`, `read_only`, `automation`, and `experimental_admin` session tokens into the handshake file. All tokens use the same local `/mcp` endpoint; the scope changes which access profile is forced for `tools/list` and `tools/call`.

## Why is my tool list empty?

The base server is infrastructure. Enable Unreal Capability Mesh to get the generic `mesh_*` provider, or enable another plugin that registers an `IUmcpToolProvider`. Also check UMCP access control: disabled providers, restrictive profiles, active allowlists, blocked tool patterns, or blocked tool groups can intentionally hide tools from `tools/list`.

## Can I hide or block specific providers and tools?

Yes. UMCP keeps one local endpoint and applies access control before tools reach MCP clients. Disable provider IDs, choose an access profile, add exact or wildcard tool names or groups to allow/block lists, or use the Control Panel provider toggle for single-provider groups. The same policy is enforced for both `tools/list` and `tools/call`.

## Can I temporarily block a tool during a session?

Yes. UMCP 1.0.6 adds runtime Access Guard blocks from the Control Panel and Blueprint diagnostics. Runtime blocks can hide a tool for a scoped token or globally, reject direct calls with `runtime_access_denied`, and clear when the server stops.

## Does the Access Journal store secrets?

It is designed for secret-safe diagnostics. Secret-looking argument keys such as token, secret, password, API key, authorization, and bearer fields are omitted from the in-memory and JSONL access journal. Redacted strings and sanitized RAM entries are capped by settings.

## What is `mesh_configure_experimental_self_approval`?

It is a Capability Mesh provider tool for **EXPERIMENTAL** self automatic approval. It can change whether approval-gated UCM routes self-approve globally or by route id. Enabling requires `acknowledge_experimental_risk: true` and is only for own-risk testing workflows.

## Can multiple plugins add tools?

Yes. Any plugin can register an `IUmcpToolProvider`. Tool names are prefixed by provider ID.

## Can clients see tool parameters and risk?

Yes. `tools/list` includes each tool `inputSchema`, optional `outputSchema`, and optional tool annotations. UCM route tools derive these from route bindings, schema manifests, policy, and side effects.

## How do I inspect attached tools in the editor?

Open **Tiny Tools -> AI -> Universal MCP -> Open Control Panel**. The Connected Functions area groups tools by plugin, supports lazy input/output schema expansion, and caches unchanged metadata between visits. Click **Refresh** after UCM setup changes to force a full reload.

## Why did UMCP reject my tool arguments before the provider ran?

The `Validate Tool Arguments` setting is enabled. UMCP then checks incoming arguments against the selected tool `inputSchema` and returns `invalid_tool_arguments` for missing required fields, unknown fields where disallowed, type mismatches, or enum mismatches.

## Which Unreal Engine versions are targeted?

The plugin is authored for Unreal Engine 5.x code plugins and uses C++20 for current UE 5.6 compatibility.

## Is this for packaged games?

No. The current server is editor infrastructure for local tools and agents.

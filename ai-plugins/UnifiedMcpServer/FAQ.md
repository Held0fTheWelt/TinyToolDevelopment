# FAQ

## Does this plugin include an AI model?

No. Unified MCP Server is connection infrastructure. It exposes tools from provider plugins to local MCP clients.

## Does it include a standalone executable?

No. The server runs inside the Unreal Editor and ships no external executable.

## Does it include Node.js, Python, or mcp-remote?

No. Stdio-only clients may need a user-installed bridge such as `mcp-remote`, but that is not bundled.

## Is the server enabled by default?

No. It is off by default and must be enabled in Project Settings or started manually from **Tools → AI → Universal MCP**.

## Does it listen on the network?

No. It binds to `127.0.0.1`.

## How are requests authenticated?

The server generates a bearer token on start. Clients read it from `Saved/UnifiedMcpServer/agent/mcp_endpoint.json` and send it in the `Authorization` header.

## Why is my tool list empty?

The base server is infrastructure. Enable Unreal Capability Mesh to get the generic `mesh_*` provider, or enable another plugin that registers an `IUmcpToolProvider`.

## What is `mesh_configure_experimental_self_approval`?

It is a Capability Mesh provider tool for **EXPERIMENTAL** self automatic approval. It can change whether approval-gated UCM routes self-approve globally or by route id. Enabling requires `acknowledge_experimental_risk: true` and is only for own-risk testing workflows.

## Can multiple plugins add tools?

Yes. Any plugin can register an `IUmcpToolProvider`. Tool names are prefixed by provider ID.

## Can clients see tool parameters and risk?

Yes. `tools/list` includes each tool `inputSchema`, optional `outputSchema`, and optional tool annotations. UCM route tools derive these from route bindings, schema manifests, policy, and side effects.

## How do I inspect attached tools in the editor?

Open **Tools → AI → Universal MCP → Open Control Panel**. The Connected Functions area groups tools by plugin, supports lazy input/output schema expansion, and caches unchanged metadata between visits. Click **Refresh** after UCM setup changes to force a full reload.

## Why did UMCP reject my tool arguments before the provider ran?

The `Validate Tool Arguments` setting is enabled. UMCP then checks incoming arguments against the selected tool `inputSchema` and returns `invalid_tool_arguments` for missing required fields, unknown fields where disallowed, type mismatches, or enum mismatches.

## Which Unreal Engine versions are targeted?

The plugin is authored for Unreal Engine 5.x code plugins and uses C++20 for current UE 5.6 compatibility.

## Is this for packaged games?

No. The current server is editor infrastructure for local tools and agents.

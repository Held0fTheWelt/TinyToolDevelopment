# Buyer Guide

Unified MCP Server is for Unreal projects that want one local MCP endpoint instead of one separate server per feature plugin.

## What It Does

- Hosts a loopback MCP endpoint inside the Unreal Editor.
- Uses JSON-RPC 2.0 over HTTP at `/mcp`.
- Requires bearer-token authentication for every request.
- Lets other plugins register tools through `IUmcpToolProvider`.
- Namespaces tools as `<providerId>_<tool>`.
- Applies provider/tool access control on the same endpoint.
- Provides scoped session tokens for default, read-only, automation, and experimental/admin clients.
- Writes a handshake file for local agent configuration.
- Ships without bundled third-party executables.
- Provides an editor control panel with a plugin-grouped Connected Functions tree for inspecting attached MCP tools, schemas, and access state.

## What It Does Not Do

- It does not include an AI model or LLM provider.
- It does not bundle `mcp-remote`, Node.js, Python, or a standalone server binary.
- It does not expose project tools by itself; provider plugins or Unreal Capability Mesh supply tools.
- It is editor infrastructure, not gameplay runtime networking.

## Typical Use Cases

- Connect local AI agents to Unreal Editor tools through one endpoint.
- Let multiple plugins share one MCP server with policy-controlled auth tokens.
- Add or remove tool providers without modifying the server plugin.
- Hide or block selected providers/tools without splitting clients across ports.
- Keep agent-facing tools local to the developer machine.

## Recommended Companion Plugins

The recommended companion is Unreal Capability Mesh. It exposes setup-declared routes through generic `mesh_*` MCP tools, so projects can administer DataAssets/DataTables and run configured IIS, PRS, SCD, UII, and LLM Store workflows without enabling optional no-UCM Freebie Bridges. Its `mesh_configure_experimental_self_approval` tool is explicitly **EXPERIMENTAL** and only for own-risk testing workflows.

## Technical Summary For Fab

Editor-only loopback MCP host. Provides a Runtime interface module for provider contracts and an Editor module that serves MCP-compatible JSON-RPC over HTTP on `127.0.0.1`. Tools are registered by other plugins as Unreal modular features, filtered by provider/tool access policy, and exposed through prefixed names. Authentication uses generated scoped bearer tokens written to a project-local handshake file under `Saved/UnifiedMcpServer/agent`.

Unified MCP Server

Unified MCP Server hosts one local MCP-over-HTTP endpoint inside the Unreal Editor. It binds to 127.0.0.1, is disabled by default, and requires a generated bearer token for requests.

Other plugins attach tools by registering IUmcpToolProvider as an Unreal modular feature. Tools are exposed as <providerId>_<toolName>. The base plugin ships no AI model, no external executable, and no bundled Node/Python runtime.

Start in the editor from Tools -> AI -> Universal MCP -> Start Unified MCP Server. Connection details are written to Saved/UnifiedMcpServer/agent/mcp_endpoint.json.

Open Tools -> AI -> Universal MCP -> Open Control Panel for status, lifecycle actions, and a plugin-grouped Connected Functions tree with lazy schema inspection.

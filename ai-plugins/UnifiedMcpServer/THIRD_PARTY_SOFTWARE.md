# Third-Party Software

Unified MCP Server **bundles no third-party source code, runtime binaries, AI models, Node.js,
Python, `mcp-remote`, or standalone executables**. It is a C++ Unreal Engine plugin that hosts a
local MCP-over-HTTP server using standard Unreal networking and JSON APIs.

## Optional, User-Installed Bridge (not bundled)

| Software | When you need it | How to integrate |
| --- | --- | --- |
| `mcp-remote` (Node.js) | Only if your MCP client speaks **stdio** and cannot call HTTP directly | Install it yourself via npm (`npx mcp-remote …`) and point it at the server URL from the handshake file. HTTP-capable clients do not need it. See [QUICKSTART.md](QUICKSTART.md) §5. |

HTTP-capable MCP clients connect directly to `http://127.0.0.1:<port>/mcp` with the bearer token
from the handshake file — no third-party software required.

**Fab third-party software declaration:** no bundled third-party software.

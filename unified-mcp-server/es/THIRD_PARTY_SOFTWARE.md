<!-- doc-provenance: AKDB:plugins/UnifiedMcpServer/architecture.md; docs/architecture/plugins/UnifiedMcpServer/product-facts.yml; reconciled 2026-07-04 -->
# Software de terceros

Unified MCP Server **no incluye código fuente de terceros, binarios en tiempo de ejecución, modelos de IA, Node.js, Python, `mcp-remote` ni ejecutables independientes**. Es un plugin C++ para Unreal Engine que aloja un servidor MCP local sobre HTTP utilizando la red estándar de Unreal y las API de JSON.

## Puente opcional, instalado por el usuario (no incluido)

| Software | Cuándo se necesita | Cómo integrarlo |
| --- | --- | --- |
| `mcp-remote` (Node.js) | Solo si su cliente MCP admite exclusivamente **Stdio** y no puede llamar a HTTP directamente | Instálelo usted mismo mediante npm (`npx mcp-remote …`) y apúntelo a la URL del servidor extraída del archivo de intercambio. Los clientes compatibles con HTTP no lo necesitan. Consulte [QUICKSTART.md](QUICKSTART.md) §5. |

Los clientes MCP compatibles con HTTP se conectan directamente a `http://127.0.0.1:<puerto>/mcp` con el token Bearer extraído del archivo de intercambio — no se requiere software de terceros.

**Declaración de software de terceros para Fab:** no se incluye software de terceros.

<!-- doc-provenance: AKDB:plugins/UnifiedMcpServer/architecture.md; docs/architecture/plugins/UnifiedMcpServer/product-facts.yml; reconciled 2026-07-04 -->
# Software von Drittanbietern

Unified MCP Server **enthält keinen Quellcode von Drittanbietern, keine Laufzeit-Binärdateien, KI-Modelle, Node.js, Python, `mcp-remote` oder eigenständige ausführbare Dateien**. Es ist ein C++-Unreal-Engine-Plugin, das einen lokalen MCP-über-HTTP-Server mithilfe von Standard-Unreal-Netzwerk- und JSON-APIs hostet.

## Optionale, vom Benutzer installierte Brücke (nicht enthalten)

| Software | Wann erforderlich | Wie integrieren |
| --- | --- | --- |
| `mcp-remote` (Node.js) | Nur wenn Ihr MCP-Client ausschließlich **Stdio** spricht und HTTP nicht direkt aufrufen kann | Selbst über npm installieren (`npx mcp-remote …`) und auf die Server-URL aus der Handshake-Datei verweisen. HTTP-fähige Clients benötigen dies nicht. Siehe [QUICKSTART.md](QUICKSTART.md) §5. |

HTTP-fähige MCP-Clients verbinden sich direkt mit `http://127.0.0.1:<port>/mcp` unter Verwendung des Bearer-Tokens aus der Handshake-Datei — es ist keine Software von Drittanbietern erforderlich.

**Fab-Erklärung zu Drittanbietersoftware:** Keine mitgelieferte Drittanbietersoftware.

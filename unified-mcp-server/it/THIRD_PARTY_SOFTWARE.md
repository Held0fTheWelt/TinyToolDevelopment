<!-- doc-provenance: AKDB:plugins/UnifiedMcpServer/architecture.md; docs/architecture/plugins/UnifiedMcpServer/product-facts.yml; reconciled 2026-07-04 -->
# Software di terze parti

Unified MCP Server **non include codice sorgente di terze parti, file binari runtime, modelli di IA, Node.js, Python, `mcp-remote` o eseguibili autonomi**. È un plugin per Unreal Engine in C++ che ospita un server MCP su HTTP locale utilizzando la rete standard di Unreal e le API JSON.

## Bridge opzionale, installato dall'utente (non incluso)

| Software | Quando serve | Come integrarlo |
| --- | --- | --- |
| `mcp-remote` (Node.js) | Solo se il tuo client MCP supporta solo **Stdio** e non può chiamare direttamente HTTP | Installalo autonomamente tramite npm (`npx mcp-remote …`) e indirizzalo all'URL del server estratto dal file di handshake. I client in grado di gestire HTTP non ne hanno bisogno. Vedi [QUICKSTART.md](QUICKSTART.md) §5. |

I client MCP in grado di gestire HTTP si connettono direttamente a `http://127.0.0.1:<port>/mcp` con il token Bearer estrapolato dal file di handshake — non è richiesto alcun software di terze parti.

**Dichiarazione software di terze parti per Fab:** nessun software di terze parti incluso.

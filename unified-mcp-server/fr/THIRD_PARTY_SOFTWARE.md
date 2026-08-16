<!-- doc-provenance: AKDB:plugins/UnifiedMcpServer/architecture.md; docs/architecture/plugins/UnifiedMcpServer/product-facts.yml; reconciled 2026-07-04 -->
# Logiciels tiers

Unified MCP Server **ne fournit aucun code source tiers, aucun binaire d'exécution, aucun modèle d'IA, aucun composant Node.js, Python, `mcp-remote` ou exécutable autonome**. Il s'agit d'un plugin C++ Unreal Engine qui héberge un serveur MCP sur HTTP local en utilisant le réseau standard Unreal et les API JSON.

## Pont optionnel, installé par l'utilisateur (non fourni)

| Logiciel | Quand en avez-vous besoin | Comment l'intégrer |
| --- | --- | --- |
| `mcp-remote` (Node.js) | Uniquement si votre client MCP utilise **Stdio** et ne peut pas appeler HTTP directement | Installez-le vous-même via npm (`npx mcp-remote …`) et pointez-le vers l'URL du serveur issue du fichier de handshake. Les clients compatibles HTTP n'en ont pas besoin. Voir [QUICKSTART.md](QUICKSTART.md) §5. |

Les clients MCP compatibles HTTP se connectent directement à `http://127.0.0.1:<port>/mcp` avec le jeton Bearer du fichier de handshake — aucun logiciel tiers n'est requis.

**Déclaration de logiciels tiers pour Fab :** aucun logiciel tiers fourni.

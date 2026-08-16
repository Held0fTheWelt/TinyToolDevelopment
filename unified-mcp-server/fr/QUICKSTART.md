<!-- doc-provenance: AKDB:plugins/UnifiedMcpServer/architecture.md; docs/architecture/plugins/UnifiedMcpServer/product-facts.yml; reconciled 2026-07-04 -->
# Démarrage rapide

## 1. Activer le plugin

Activez `Unified MCP Server` dans le navigateur de plugins et redémarrez l'éditeur si Unreal le demande.

## 2. Activer le serveur

Ouvrez :

```text
Edit -> Editor Settings -> Plugins -> Unified MCP Server
```

Activez **Enable MCP Server**. Conservez le port par défaut `8732`, à moins qu'un autre service local ne l'utilise déjà.

## 3. Démarrer le serveur

Utilisez :

```text
Tiny Tools -> AI -> Universal MCP -> Start Unified MCP Server
```

Pour consulter l'état, les boutons de cycle de vie et l'arbre des fonctions connectées regroupées par plugin, utilisez :

```text
Tiny Tools -> AI -> Universal MCP -> Open Control Panel
```

La zone Connect Functions regroupe les outils par plugin, prend en charge le dépliage différé des schémas et conserve en cache les métadonnées inchangées entre les visites. Utilisez **Refresh** après des modifications de configuration UCM pour forcer un rechargement complet.

Dans UMCP 1.0.3 et ultérieur, le panneau de contrôle affiche également l'état d'accès. Désactivez un groupe de fournisseur unique pour masquer ses outils dans `tools/list` et bloquer l'exécution directe de `tools/call`.

Si le réglage est activé avant le démarrage de l'éditeur, le serveur tente également de démarrer lors du chargement du module de l'éditeur.

## 4. Lire le fichier de handshake

Après le démarrage, l'éditeur écrit :

```text
Saved/UnifiedMcpServer/agent/mcp_endpoint.json
```

Exemple de structure :

```json
{
  "host": "127.0.0.1",
  "port": 8732,
  "token": "<default-token>",
  "tokens": {
    "default": {"token": "<default-token>", "scope": "default", "profile": "Project Settings"},
    "read_only": {"token": "<read-only-token>", "scope": "read_only", "profile": "Read Only"},
    "automation": {"token": "<automation-token>", "scope": "automation", "profile": "Automation"},
    "experimental_admin": {"token": "<experimental-token>", "scope": "experimental_admin", "profile": "Experimental"}
  }
}
```

Utilisez le champ de compatibilité `token` ou choisissez un jeton dans `tokens` :

```text
Authorization: Bearer <jeton-sélectionné>
```

## 5. Connecter un client

Les clients MCP compatibles HTTP peuvent appeler :

```text
http://127.0.0.1:8732/mcp
```

Lorsque le serveur est en cours d'exécution, ouvrez le panneau de contrôle et cliquez sur **Copy MCP Client Config**.
Cela copie un extrait `mcp.json` prêt à coller avec l'URL de point d'accès en direct et le jeton Bearer par défaut actuel. Collez-le dans le fichier de configuration de votre client MCP.
Après **Rotate Tokens**, copiez à nouveau l'extrait car le jeton Bearer a changé.

Lors de `initialize`, UMCP négocie `protocolVersion` : lorsque votre client demande une version prise en charge (`2025-06-18`, `2025-03-26` ou `2024-11-05`), le serveur renvoie cette version ; sinon, il répond avec `2024-11-05`. Une vérification client par `GET /mcp` renvoie HTTP 405 car UMCP utilise le sous-ensemble de réponses JSON Streamable-HTTP et n'héberge pas de flux SSE serveur-vers-client.

Les clients prenant uniquement en charge Stdio nécessitent un pont installé par l'utilisateur tel que `mcp-remote`. Ce pont n'est pas fourni avec ce plugin.

## 6. Ajouter des outils (optionnel)

Le serveur fonctionne de manière autonome ; cette étape ajoute des outils que les clients peuvent appeler. Vous disposez de deux options indépendantes et vous n'avez besoin que de ce qui convient à votre projet :

- **Votre propre plugin (ou n'importe quel plugin) :** enregistrez une fonctionnalité modulaire `IUmcpToolProvider` et ses outils apparaissent automatiquement sous la forme `<providerId>_<toolName>`. Aucun plugin catalogue n'est requis. Voir [INTEGRATION.md](INTEGRATION.md).
- **Optionnel — Unreal Capability Mesh (UCM) :** si vous possédez également Unreal Capability Mesh, son activation ajoute les outils `mesh_*` déclarés dans la configuration. Les appelants peuvent ainsi exécuter les routes UCM configurées (par exemple paquet de contexte IIS, placement PRS, conseils de migration SCD et administration DataAsset/DataTable) via `mesh_execute_route` ou les outils directs générés `mesh_route_*`. Il expose également `mesh_configure_experimental_self_approval` ; cet outil est **EXPÉRIMENTAL**, nécessite une confirmation explicite des risques lors de son activation et est réservé aux flux de test à vos propres risques.

Les deux sont optionnels — le serveur, le handshake et la connexion client (étapes 1 à 5) fonctionnent sans aucun fournisseur installé.

## 7. Arrêter ou renouveler

Utilisez le menu Tiny Tools :

```text
Tiny Tools -> AI -> Universal MCP -> Stop Unified MCP Server
Tiny Tools -> AI -> Universal MCP -> Rotate MCP Token
```

L'arrêt supprime le fichier de handshake. Le renouvellement le réécrit avec de nouveaux jetons délimités. Ces deux actions sont également disponibles depuis le panneau de contrôle.

<!-- doc-provenance: AKDB:plugins/UnifiedMcpServer/architecture.md; docs/architecture/plugins/UnifiedMcpServer/product-facts.yml; reconciled 2026-07-04 -->
# Unified MCP Server

Unified MCP Server est un plugin d'éditeur Unreal Engine fournissant un point d'accès Model Context Protocol (MCP) local unique pour l'ensemble du projet. D'autres plugins raccordent leurs outils via une petite interface modulaire, permettant au serveur d'exposer de nouvelles capacités sans dépendre directement de ces plugins.

Le plugin est volontairement orienté infrastructure. Il ne fournit aucun exécutable externe, aucun paquet Node et aucun runtime Python. Il héberge un point d'accès MCP JSON-RPC 2.0 en boucle locale au sein de l'éditeur et permet aux fournisseurs d'enregistrer des outils au moment de l'exécution.

## Modules

| Module | Objet |
| --- | --- |
| `UnifiedMcpServerInterface` | Contrat public `IUmcpToolProvider` et types de descripteurs/résultats d'outils. |
| `UnifiedMcpServerEditor` | Hôte éditeur pour le serveur, réglages, gestion des jetons, registre de fournisseurs, panneau de contrôle d'état et entrées du menu Tiny Tools. |

## Flux de travail principal

1. Activez le plugin dans le projet.
2. Ouvrez `Edit -> Editor Settings -> Plugins -> Unified MCP Server`.
3. Activez le serveur local et choisissez un port, ou conservez le port par défaut `8732`.
4. Utilisez `Tiny Tools -> AI -> Universal MCP -> Open Control Panel` pour consulter l'état, les boutons de cycle de vie et l'arbre des fonctions connectées regroupées par plugin.
5. Démarrez le serveur depuis le panneau ou via `Tiny Tools -> AI -> Universal MCP -> Start Unified MCP Server`.
6. Lisez les données de connexion dans `Saved/UnifiedMcpServer/agent/mcp_endpoint.json`.
7. Configurez un client MCP pour appeler `http://127.0.0.1:8732/mcp` avec `Authorization: Bearer <token>`.

## Fournisseurs d'outils (Tool Providers)

Les plugins fournisseurs implémentent `IUmcpToolProvider` et l'enregistrent en tant que fonctionnalité modulaire Unreal. Les noms d'outils exposés utilisent la structure :

```text
<providerId>_<toolName>
```

Lorsque Unreal Capability Mesh est chargé, le fournisseur mesh intégré expose des outils génériques tels que `mesh_list_capabilities`, `mesh_list_routes`, `mesh_configure_experimental_self_approval`, `mesh_dry_run_route` et `mesh_execute_route`. Il aplatit également les routes UCM déclarées dans la configuration en outils MCP directs `mesh_route_*`. Ces outils de route publient des schemas `inputSchema`, `outputSchema` et des annotations d'outils MCP dérivés des routes, permettant aux clients d'examiner les paramètres et les avertissements de risque avant l'appel. `mesh_configure_experimental_self_approval` est **EXPÉRIMENTAL** et **à utiliser à vos propres risques** ; son activation nécessite une confirmation explicite des risques. Les anciens ponts directs peuvent toujours enregistrer des noms d'outils spécifiques au produit, mais les routes UCM constituent le chemin de configuration privilégié pour le projet.

`tools/call` renvoie le JSON du fournisseur sous forme de contenu textuel et, lorsque le résultat est un objet JSON, sous forme de `structuredContent` MCP. `initialize` annonce `tools.listChanged`, et `tools/list` inclut une valeur `_meta.toolsRevision` afin que les clients puissent rafraîchir les descripteurs d'outils mis en cache après des modifications de configuration UCM.

UMCP 1.0.3 ajoute le contrôle d'accès sur l'unique point d'accès. Les identifiants de fournisseurs peuvent être désactivés, et les noms d'outils exposés peuvent être autorisés ou bloqués au moyen de noms exacts ou de motifs avec caractères génériques. UMCP 1.0.4 introduit des profils (`Default`, `Read Only`, `Automation`, `Experimental`) ainsi que des groupes d'outils dérivés d'annotations. UMCP 1.0.5 ajoute des jetons de session délimités afin que différents clients puissent utiliser un accès `default`, `read_only`, `automation` ou `experimental_admin` via le même point d'accès `/mcp`. UMCP 1.0.6 apporte un Access Guard d'exécution et un journal d'accès (Access Journal) sécurisé pour les secrets destiné au diagnostic des derniers appels `tools/call`. La même politique s'applique à la fois à `tools/list` et à `tools/call`. Le panneau de contrôle indique si les fonctions connectées sont exposées, bloquées, masquées ou indisponibles.

## Sécurité

- Le serveur se lie exclusivement à `127.0.0.1`.
- Le serveur est désactivé par défaut.
- Les requêtes exigent un jeton Bearer issu du fichier de handshake.
- Le contrôle d'accès par fournisseur/outil peut masquer des outils dans `tools/list` et bloquer l'exécution directe de `tools/call`.
- Les blocages d'Access Guard au moment de l'exécution résident uniquement en mémoire et sont effacés à l'arrêt du serveur.
- Les jetons peuvent être renouvelés depuis **Tiny Tools -> AI -> Universal MCP**.
- Le fichier de handshake est supprimé lors de l'arrêt du serveur.
- Les métadonnées de requête sont consignées dans `Saved/UnifiedMcpServer/logs/mcp_requests.jsonl`.
- Les diagnostics d'accès sont consignés dans `Saved/UnifiedMcpServer/logs/access_audit.jsonl` en omettant les clés d'arguments ressemblant à des secrets.

## Documentation

| Document | Objet |
| --- | --- |
| [BUYER_GUIDE.md](BUYER_GUIDE.md) | Présentation du produit, cas d'usage et limites. |
| [QUICKSTART.md](QUICKSTART.md) | Première configuration et connexion client. |
| [UserManual.md](UserManual.md) | Utilisation quotidienne dans l'éditeur. |
| [TechnicalOverview.md](TechnicalOverview.md) | Architecture et comportement du protocole. |
| [INTEGRATION.md](INTEGRATION.md) | Comment les plugins fournisseurs raccordent des outils. |
| [SettingsReference.md](SettingsReference.md) | Réglages et fichiers enregistrés. |
| [CodeDocumentation.md](CodeDocumentation.md) | Structure du code source et contrats. |
| [FAQ.md](FAQ.md) | Questions fréquentes des acheteurs. |
| [TROUBLESHOOTING.md](TROUBLESHOOTING.md) | Panneaux courantes et solutions. |
| [ReleaseChecklist.md](ReleaseChecklist.md) | Liste de contrôle pour la publication et le paquetage Fab. |

## Paquetage

`Config/FilterPlugin.ini` inclut `/Documentation/...` et `/CHANGELOG.md` afin que les paquets Fab contiennent cet ensemble documentaire.

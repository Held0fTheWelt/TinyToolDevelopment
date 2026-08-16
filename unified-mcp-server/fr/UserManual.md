<!-- doc-provenance: AKDB:plugins/UnifiedMcpServer/architecture.md; docs/architecture/plugins/UnifiedMcpServer/product-facts.yml; reconciled 2026-07-04 -->
# Manuel de l'utilisateur

## Ouverture des réglages

Unified MCP Server se configure sous :

```text
Edit -> Editor Settings -> Plugins -> Unified MCP Server
```

Réglages :

| Réglage | Par défaut | Signification |
| --- | --- | --- |
| Enable MCP Server | désactivé | Permet au module éditeur d'exécuter le serveur MCP local. |
| Server Port | 8732 | Port TCP utilisé sur `127.0.0.1`. |
| Validate Tool Arguments | désactivé | Valide optionnellement les arguments de `tools/call` par rapport à l'`inputSchema` de chaque outil avant l'appel au fournisseur. |
| Access Profile | Default | Mode d'exposition global : Default, Read Only, Automation ou Experimental. |
| Disabled Provider IDs | vide | Masque et bloque tous les outils des identifiants de fournisseurs correspondants. |
| Allowed Tool Names | vide | Liste autorisée optionnelle de noms d'outils exposés ou de motifs avec caractères génériques. Vide signifie que tous les outils sont autorisés, sauf s'ils sont bloqués. |
| Blocked Tool Names | vide | Masque et bloque les noms d'outils exposés ou les motifs avec caractères génériques. |
| Allowed Tool Groups | vide | Liste autorisée optionnelle de groupes dérivés d'annotations tels que `read_only`, `non_destructive` ou `idempotent`. |
| Blocked Tool Groups | vide | Masque et bloque les groupes dérivés d'annotations tels que `risky`, `destructive` ou `open_world`. |
| Enable Access Journal | activé | Écrit des diagnostics d'accès sécurisés pour les secrets pour `tools/call`. |
| Access Journal Ring Capacity | 500 | Nombre d'entrées récentes conservées en mémoire pour le panneau de contrôle et les diagnostics Blueprint. |
| Access Journal Max File Bytes | 5242880 | Taille maximale de `access_audit.jsonl` avant la rotation d'un fichier. |

## Menu Tiny Tools

L'éditeur ajoute des actions de cycle de vie et d'état sous **Tiny Tools -> AI -> Universal MCP** :

| Action | Résultat |
| --- | --- |
| Open Control Panel | Ouvre le panneau de contrôle UMCP avec les boutons de cycle de vie et l'arbre des fonctions connectées regroupées par plugin. |
| Start Unified MCP Server | Démarre le point d'accès HTTP en boucle locale. |
| Stop Unified MCP Server | Arrête le point d'accès et supprime le fichier de handshake. |
| Rotate MCP Token | Génère de nouveaux jetons Bearer délimités et réécrit le fichier de handshake. |

La section **AI** regroupe Unified MCP Server avec d'autres plugins d'IA de Tiny Tool Development tels que l'Internal Index Service.

## Panneau de contrôle (Control Panel)

Le panneau de contrôle affiche :

| Zone | Détails |
| --- | --- |
| Status | État en cours/arrêté, réglage de démarrage, URL du point d'accès, présence/nombre de jetons, nombre de requêtes, nombre de fournisseurs, nombre d'outils et chemin du fichier de handshake. |
| Actions | Démarrer, arrêter, renouveler les jetons, ouvrir le dossier agent et rafraîchir. |
| Tabs | Connected Functions pour les fournisseurs/outils/schémas, et Access Activity pour les derniers appels d'outils et les commandes de blocage d'exécution. |
| Connected Functions | Groupes de plugins dépliables avec bascules de fournisseurs, lignes d'outils, état d'accès/de disponibilité, noms d'outils MCP, descriptions et tables de schémas d'entrée/sortie chargées à la demande. |
| Access Activity | Appels d'outils récents avec détails du jeton/client/résultat, nombre de blocages d'exécution, rafraîchissement, blocage/déblocage de jetons/outils et suppression des blocages d'exécution. |

### Disposition de Connected Functions

Connected Functions utilise un arbre hiérarchique similaire au catalogue de routes de Capability Mesh :

1. **Groupe de plugins** — une ligne par plugin avec le nombre d'interfaces et, lorsque le groupe correspond à un seul fournisseur, un bouton pour activer/désactiver l'accès. Cliquez sur la flèche pour tout afficher ou masquer les outils de ce plugin.
2. **Ligne d'outil** — une ligne par outil MCP raccordé ou capacité UCM déclarée dans la configuration. Cliquez sur la flèche pour afficher ou masquer les tables de schémas d'entrée/sortie de cet outil.

La disposition des colonnes dépend de l'état de dépliage **au sein de chaque groupe de plugins** :

| État | Colonnes |
| --- | --- |
| Tous les outils repliés | `Provider`, `Ready`, `Tool`, `Description` (large) |
| Au moins un outil déplié | `Provider`, `Ready`, `Tool`, `Input`, `Output`, `Description` |

**Regroupement par fournisseur :** les outils directs des fournisseurs apparaissent sous leur `GetProviderDisplayName()`. Les outils de route UCM aplatis (`mesh_route_*`) apparaissent sous le **plugin propriétaire** issu des métadonnées de capacité Capability Mesh (par exemple Internal Index Service ou SmartContentDiet), et non sous l'entrée hôte mesh. Les outils hôtes mesh génériques tels que `mesh_list_routes` et `mesh_reload_setup` restent sous **Unreal Capability Mesh**.

**Performance :** le panneau charge les métadonnées d'outils de manière asynchrone. Les données inchangées sont servies depuis le cache lors des ouvertures répétés, des démarrages/arrêts et des dépliages/repliages. Utilisez **Refresh** pour forcer un rechargement complet après des modifications de configuration UCM.

Les lignes marquées `Needs approval` sont des capacités UCM nécessitant une approbation. Leur info-bulle pointe vers le chemin d'approbation automatique autonome **EXPÉRIMENTAL** dans les routes UCM ou `mesh_configure_experimental_self_approval` ; utilisez-le uniquement pour des tests à vos propres risques.

Les lignes marquées `Blocked` ou `Hidden` ne sont pas exposées aux clients MCP. UMCP les retire de `tools/list` et renvoie `tool_access_denied` si un client appelle tout de même directement le nom de l'outil.

Les blocages d'exécution de l'onglet **Access Activity** sont des blocages temporaires de la session éditeur. Ils n'écrivent pas dans les réglages de l'éditeur, masquent l'outil dans `tools/list` pour le jeton concerné, rejettent les appels directs avec `runtime_access_denied` et sont effacés à l'arrêt du serveur.

Les descriptions d'outils incluent les annotations MCP lorsque les fournisseurs les publient, comme les comportements en lecture seule, destructeurs, idempotents ou monde ouvert. Le panneau affiche également les groupes dérivés utilisés par les politiques d'accès par profil et par groupe.

## Fichiers de connexion

Fichier de handshake :

```text
Saved/UnifiedMcpServer/agent/mcp_endpoint.json
```

Journal de requêtes :

```text
Saved/UnifiedMcpServer/logs/mcp_requests.jsonl
```

Journal d'accès (Access Journal) :

```text
Saved/UnifiedMcpServer/logs/access_audit.jsonl
```

Le fichier de handshake contient l'hôte local, le port, le `token` de compatibilité et les `tokens` délimités. Traitez-le comme un identifiant local.

Le journal d'accès omet les clés d'arguments ressemblant à des secrets telles que token, secret, password, API key, authorization et bearer.

## Appels MCP pris en charge

Le serveur gère ces méthodes JSON-RPC :

| Méthode | Comportement |
| --- | --- |
| `initialize` | Renvoie la version du protocole, les capacités d'outils et les informations du serveur. |
| `notifications/initialized` | Accuse réception de l'initialisation du client. |
| `ping` | Renvoie un résultat vide. |
| `tools/list` | Renvoie tous les outils des fournisseurs enregistrés, y compris l'`inputSchema`, l'`outputSchema` optionnel, les `annotations` optionnelles et `_meta.toolsRevision`. |
| `tools/call` | Achemine un nom d'outil préfixé par le fournisseur vers son fournisseur et renvoie les résultats JSON sous forme de texte et de `structuredContent` lorsque cela est possible. |

Les méthodes inconnues renvoient une erreur JSON-RPC de méthode non trouvée.

## Outils de tâches de l'éditeur (Editor Job Tools)

UMCP expose des outils d'agrégation de tâches en lecture seule lorsque Unreal Capability Mesh est disponible :

| Outil | Objet |
| --- | --- |
| `jobs_list` | Fusionne les tâches récentes des routes UCM fixes pour IIS, SmartContentDiet, LLM Store et UMCP. Les arguments optionnels `provider_id` et `max_count` restreignent le résultat. |
| `jobs_status` | Recherche un identifiant de tâche dans la même table de routes et renvoie l'identifiant du fournisseur source correspondant. |

Les plugins sources publient leur propre liste/état de tâches de l'éditeur via les routes UCM et ne dépendent pas d'UMCP. Si UCM ou une route est indisponible, l'agrégation ignore cette route et renvoie tout de même les tâches des fournisseurs disponibles.

## Travailler avec des fournisseurs

Unified MCP Server ne contient pas d'outils de projet en lui-même. Les fournisseurs les ajoutent. Un fournisseur fournit des descripteurs, des schémas d'entrée et une logique d'appel via `IUmcpToolProvider`.

Lorsqu'un fournisseur est installé, les outils apparaissent sous la forme :

```text
provider_tool
```

Par exemple :

```text
mesh_route_iis_agent_search_v1_<hash>
```

Lorsque Unreal Capability Mesh est chargé, UMCP expose des outils mesh génériques :

```text
mesh_reload_setup
mesh_list_capabilities
mesh_list_routes
mesh_configure_experimental_self_approval
mesh_dry_run_route
mesh_execute_route
mesh_invoke_endpoint
```

UMCP publie également chaque route Capability Mesh déclarée sous la forme d'un outil MCP aplati :

```text
mesh_route_<sanitized_route_id>_<hash>
```

Les outils de route aplatis acceptent `mode: "execute"` ou `mode: "dry_run"`. Si `input` ou `input_json` est omis, les arguments restants sont traités comme l'objet d'entrée de la route. Pour les routes qui lient en interne un `request_json` sérialisé, UMCP répercute automatiquement les arguments aplatis dans `request_json`. Chaque outil de route aplati publie un `inputSchema`, un `outputSchema` et des annotations MCP dérivés de la route, tels que `readOnlyHint`, `destructiveHint` et `openWorldHint`. Les routes mutatives passent toujours par les contrôles de politique et d'approbation de Capability Mesh.

Utilisez `mesh_execute_route` pour les opérations mutatives afin que la politique de route et les contrôles d'approbation de Capability Mesh restent actifs.

`mesh_configure_experimental_self_approval` est explicitement **EXPÉRIMENTAL** et **à utiliser à vos propres risques**. Il peut lire ou modifier l'approbation automatique autonome de Capability Mesh globalement ou pour des identifiants de routes sélectionnés. Son activation nécessite `acknowledge_experimental_risk: true`.

## Notes opérationnelles

- Utilisez un port unique par instance d'éditeur.
- Renouvelez les jetons après avoir partagé des journaux ou des captures d'écran susceptibles de montrer le fichier de handshake.
- Arrêtez le serveur lorsqu'un agent externe n'a plus besoin d'accès.
- Si aucun plugin fournisseur n'est activé, `tools/list` peut légitimement renvoyer une liste vide.

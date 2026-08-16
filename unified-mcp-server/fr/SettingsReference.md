<!-- doc-provenance: AKDB:plugins/UnifiedMcpServer/architecture.md; docs/architecture/plugins/UnifiedMcpServer/product-facts.yml; reconciled 2026-07-04 -->
# Référence des réglages

Les réglages résident dans `UUmcpSettings` et sont stockés dans la configuration de l'éditeur.

Ouvrez :

```text
Edit -> Editor Settings -> Plugins -> Unified MCP Server
```

## Serveur

| Réglage | Champ de configuration | Par défaut | Notes |
| --- | --- | --- | --- |
| Enable MCP Server | `bEnableServer` | `false` | Désactivé par défaut. Si vrai, le module éditeur tente de démarrer le serveur au démarrage. |
| Server Port | `ServerPort` | `8732` | Port TCP local pour le point d'accès en boucle locale. Plage valide : 1-65535. |

## Outils (Tools)

| Réglage | Champ de configuration | Par défaut | Notes |
| --- | --- | --- | --- |
| Validate Tool Arguments | `bValidateToolArguments` | `false` | Lorsqu'activé, UMCP valide les arguments entrants de `tools/call` par rapport à l'`inputSchema` de chaque outil avant d'invoquer le fournisseur. La validation est légère : champs requis, champs inconnus si `additionalProperties:false`, types primitifs et énumérations. |

## Contrôle d'accès (Access Control)

| Réglage | Champ de configuration | Par défaut | Notes |
| --- | --- | --- | --- |
| Access Profile | `AccessProfile` | `Default` | Mode d'exposition global. `Default` conserve le comportement historique, `Read Only` n'expose que les outils annotés comme étant en lecture seule, `Automation` masque les outils risqués/destructeurs/monde ouvert/non classés, et `Experimental` autorise volontairement les outils risqués, sauf s'ils sont bloqués manuellement. |
| Disabled Provider IDs | `DisabledProviderIds` | vide | Identifiants de fournisseurs masqués dans `tools/list` et bloqués lors de `tools/call`. Le panneau de contrôle peut basculer les groupes de fournisseurs uniques dans cette liste. |
| Allowed Tool Names | `AllowedToolNames` | vide | Liste autorisée optionnelle de noms d'outils MCP exposés ou de motifs avec caractères génériques tels que `iis_search` ou `mesh_route_*`. Vide signifie que tous les outils sont autorisés, sauf s'ils sont désactivés ou bloqués. |
| Blocked Tool Names | `BlockedToolNames` | vide | Noms d'outils MCP exposés ou motifs avec caractères génériques masqués dans `tools/list` et bloqués lors de `tools/call`. |
| Allowed Tool Groups | `AllowedToolGroups` | vide | Liste autorisée optionnelle de groupes dérivés d'annotations tels que `read_only`, `non_destructive`, `idempotent`, `risky`, `destructive`, `open_world` ou `unclassified`. |
| Blocked Tool Groups | `BlockedToolGroups` | vide | Groupes dérivés d'annotations masqués dans `tools/list` et bloqués lors de `tools/call`. |

L'ordre de priorité des politiques est : fournisseur désactivé, blocage d'outil explicite, profil d'accès, groupe bloqué, listes autorisées optionnelles d'outils/groupes, puis exposé. Si l'une des listes autorisées contient des entrées, un outil est exposé lorsque son nom ou au moins un groupe correspond. La même politique est appliquée pour `tools/list` et `tools/call`.

Les blocages d'Access Guard au moment de l'exécution créés depuis le panneau de contrôle ou les aides Blueprint s'appliquent uniquement à la session et interviennent après la politique permanente. Ils masquent les outils correspondants dans `tools/list`, rejettent les appels directs de `tools/call` et sont effacés à l'arrêt du serveur.

Les outils d'agrégation de tâches sont en lecture seule, mais passent tout de même par la même politique de fournisseur/outil/profil que tous les autres outils MCP. Le fait de bloquer `jobs_*` ou le fournisseur `jobs` masque à la fois `jobs_list` et `jobs_status`.

## Journal d'accès (Access Journal)

| Réglage | Champ de configuration | Par défaut | Notes |
| --- | --- | --- | --- |
| Enable Access Journal | `bEnableAccessJournal` | `true` | Écrit des diagnostics d'accès sémantiques pour `tools/call`. |
| Access Journal Ring Capacity | `AccessJournalRingCapacity` | `500` | Entrées récentes conservées en RAM pour le panneau de contrôle et les diagnostics Blueprint. |
| Access Journal Max File Bytes | `AccessJournalMaxFileBytes` | `5242880` | Taille maximale de `access_audit.jsonl` avant la rotation d'un fichier. |
| Access Journal Redacted String Limit | `AccessJournalRedactedStringLimit` | `128` | Longueur maximale des chaînes dans les arguments JSONL masqués. |
| Access Journal Max RAM Entry Bytes | `AccessJournalMaxRamEntryBytes` | `8192` | Taille maximale du JSON d'arguments assaini conservée en mémoire par entrée. Les clés ressemblant à des secrets sont omises. |

## Fichiers générés

| Fichier | Objet |
| --- | --- |
| `Saved/UnifiedMcpServer/agent/mcp_endpoint.json` | Handshake de connexion contenant l'hôte, le port, le jeton de compatibilité et les jetons de session délimités. |
| `Saved/UnifiedMcpServer/logs/mcp_requests.jsonl` | Journal de métadonnées des requêtes. |
| `Saved/UnifiedMcpServer/logs/access_audit.jsonl` | Journal d'accès sémantique sécurisé pour les secrets pour `tools/call`. |

## Paramètres de sécurité par défaut

- Serveur désactivé par défaut.
- Hôte en boucle locale uniquement.
- Jeton Bearer obligatoire.
- Les jetons peuvent être renouvelés depuis **Tiny Tools -> AI -> Universal MCP**.
- Le fichier de handshake est supprimé lors de l'arrêt du serveur.
- UMCP 1.0.5 écrit les jetons de session `default`, `read_only`, `automation` et `experimental_admin`. Le champ hérité `token` subsiste comme jeton par défaut à des fins de compatibilité.
- UMCP 1.0.6 omet des diagnostics d'accès les clés d'arguments ressemblant à des secrets, notamment token, secret, password, API key, authorization et bearer.

## Choix du port

Utilisez un port différent si :

- une autre instance d'éditeur utilise déjà `8732`
- un service local est lié au même port
- des projets distincts nécessitent des points d'accès MCP distincts

L'URL du client est :

```text
http://127.0.0.1:<ServerPort>/mcp
```

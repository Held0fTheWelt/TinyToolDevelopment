<!-- doc-provenance: AKDB:plugins/UnifiedMcpServer/architecture.md; docs/architecture/plugins/UnifiedMcpServer/product-facts.yml; reconciled 2026-07-04 -->
# Dépannage

## Le client reçoit 401 Unauthorized

Vérifiez que le client envoie :

```text
Authorization: Bearer <jeton>
```

Lisez le jeton de compatibilité actuel ou le jeton délimité dans :

```text
Saved/UnifiedMcpServer/agent/mcp_endpoint.json
```

Si les jetons ont été renouvelés, mettez à jour la configuration du client.

## La réponse d'état exposerait les jetons

Les réponses de cycle de vie et d'état signalent uniquement la présence du handshake, son chemin, le port et le nombre de jetons. Elles ne doivent jamais renvoyer de JSON de handshake brut ni de valeurs de jetons Bearer. Utilisez le fichier de handshake local pour une configuration client autorisée plutôt que de copier des secrets via des diagnostics.

## Le fichier de handshake est manquant

Causes possibles :

- le serveur ne fonctionne pas
- le serveur n'a pas pu se lier au port configuré
- le plugin est désactivé
- l'éditeur n'a pas encore démarré le module

Démarrez le serveur depuis :

```text
Tiny Tools -> AI -> Universal MCP -> Start Unified MCP Server
```

## Le port est déjà utilisé

Modifiez le port sous :

```text
Edit -> Editor Settings -> Plugins -> Unified MCP Server
```

Puis redémarrez le serveur.

## `tools/list` ne renvoie aucun outil

Unified MCP Server n'est que l'hôte. Activez Unreal Capability Mesh pour obtenir les outils génériques `mesh_*`, ou activez un autre plugin fournisseur. Vérifiez également que le fournisseur signale un état prêt et a enregistré sa fonctionnalité modulaire.

Vérifiez le contrôle d'accès dans les réglages de l'éditeur et le panneau de contrôle. Les identifiants de fournisseurs désactivés, les profils d'accès restrictifs, les listes autorisées non vides, les motifs d'outils bloqués ou les groupes d'outils bloqués masquent volontairement les outils correspondants de `tools/list`.

Si les outils génériques `mesh_*` apparaissent mais qu'aucun outil `mesh_route_*` n'apparaît, exécutez `mesh_reload_setup` ou cliquez sur **Reload Setup** dans le panneau Capability Mesh, puis rafraîchissez le client MCP. Les outils de route sont générés à partir des manifestes de routes actifs dans `Config/UnrealCapabilityMesh`.

Si `mesh_configure_experimental_self_approval` apparaît, traitez-le comme un outil de test **EXPÉRIMENTAL** à vos propres risques. Son activation nécessite `acknowledge_experimental_risk: true` et modifie le comportement d'approbation de Capability Mesh pour des routes sélectionnées ou toutes les routes nécessitant une approbation.

Si l'approbation automatique autonome a été modifiée dans l'interface utilisateur des routes UCM mais que le client MCP affiche toujours d'anciennes descriptions de routes, appelez à nouveau `tools/list` ou reconnectez/rafraîchissez le client. UMCP recharge la configuration UCM avant de lister les outils de routes, et `mesh_list_routes` renvoie directement l'état actuel de `experimental_self_approval_*`.

## Connected Functions semble obsolète dans le panneau de contrôle

Le panneau de contrôle met en cache les métadonnées d'outils pour accélérer les visites ultérieures. Après avoir modifié la configuration UCM, ajouté des fournisseurs ou rechargé des routes, cliquez sur **Refresh** dans le panneau de contrôle pour forcer un rechargement complet de Connected Functions. Le démarrage/l'arrêt et le dépliage/repliage réutilisent le cache lorsque l'instantané sous-jacent n'a pas changé.

## Un client Stdio ne peut pas se connecter directement

Le plugin fournit un transport HTTP. Les clients prenant uniquement en charge Stdio nécessitent un pont installé par l'utilisateur tel que `mcp-remote`.

## L'appel d'outil renvoie un outil inconnu

Vérifiez le nom exposé issu de `tools/list`. Utilisez le nom préfixé :

```text
<providerId>_<toolName>
```

N'appelez pas directement les noms locaux du fournisseur.

## L'appel d'outil renvoie `tool_access_denied`

Le nom de l'outil existe, mais le contrôle d'accès d'UMCP l'a bloqué. Vérifiez `AccessProfile`, retirez l'identifiant du fournisseur de `DisabledProviderIds`, ajustez `AllowedToolNames` ou `AllowedToolGroups`, ou retirez l'entrée correspondante de `BlockedToolNames` ou `BlockedToolGroups`.

## La compilation échoue sur UE 5.6 avec des erreurs standard C++

Assurez-vous que les modules UMCP et les modules de pont dépendants sont compilés en C++20. Les en-têtes du moteur UE 5.6 utilisent la syntaxe C++20 dans leurs en-têtes principaux.

## Emplacement du journal de requêtes

Les métadonnées de requête sont écrites dans :

```text
Saved/UnifiedMcpServer/logs/mcp_requests.jsonl
```

Utilisez-le pour inspecter les noms de méthodes, les codes d'état, la latence et les codes d'erreur.

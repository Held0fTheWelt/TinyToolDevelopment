<!-- doc-provenance: AKDB:plugins/UnifiedMcpServer/architecture.md; docs/architecture/plugins/UnifiedMcpServer/product-facts.yml; reconciled 2026-07-04 -->
# FAQ (Foire aux questions)

## Ce plugin inclut-il un modèle d'IA ?

Non. Unified MCP Server est une infrastructure de connexion. Il expose les outils des plugins fournisseurs aux clients MCP locaux.

## Inclut-il un exécutable autonome ?

Non. Le serveur s'exécute au sein d'Unreal Editor et ne fournit aucun exécutable externe.

## Inclut-il Node.js, Python ou mcp-remote ?

Non. Les clients prenant uniquement en charge Stdio peuvent nécessiter un pont installé par l'utilisateur tel que `mcp-remote`, mais celui-ci n'est pas fourni.

## Le serveur est-il activé par défaut ?

Non. Il est désactivé par défaut et doit être activé dans Editor Settings ou démarré manuellement depuis **Tiny Tools -> AI -> Universal MCP**.

## Écoute-t-il sur le réseau ?

Non. Il se lie exclusivement à `127.0.0.1`.

## Comment les requêtes sont-elles authentifiées ?

Le serveur génère des jetons Bearer délimités au démarrage. Les clients les lisent dans `Saved/UnifiedMcpServer/agent/mcp_endpoint.json` et envoient un jeton dans l'en-tête `Authorization`.

## Prend-il en charge plusieurs jetons délimités ?

Oui. UMCP 1.0.5 écrit les jetons de session `default`, `read_only`, `automation` et `experimental_admin` dans le fichier de handshake. Tous les jetons utilisent le même point d'accès local `/mcp` ; la portée modifie le profil d'accès imposé pour `tools/list` et `tools/call`.

## Pourquoi ma liste d'outils est-elle vide ?

Le serveur de base est une infrastructure. Activez Unreal Capability Mesh pour obtenir le fournisseur générique `mesh_*`, ou activez un autre plugin qui enregistre un `IUmcpToolProvider`. Vérifiez également le contrôle d'accès d'UMCP : les fournisseurs désactivés, les profils restrictifs, les listes autorisées actives, les motifs d'outils bloqués ou les groupes d'outils bloqués peuvent volontairement masquer des outils dans `tools/list`.

## Puis-je masquer ou bloquer des fournisseurs et des outils spécifiques ?

Oui. UMCP conserve un point d'accès local et applique le contrôle d'accès avant que les outils n'atteignent les clients MCP. Désactivez des identifiants de fournisseurs, choisissez un profil d'accès, ajoutez des noms d'outils exacts ou avec caractères génériques ou des groupes aux listes d'autorisation/blocage, ou utilisez la bascule de fournisseur du panneau de contrôle pour les groupes à fournisseur unique. La même politique est appliquée pour `tools/list` et `tools/call`.

## Puis-je bloquer temporairement un outil pendant une session ?

Oui. UMCP 1.0.6 ajoute des blocages d'Access Guard au moment de l'exécution depuis le panneau de contrôle et les diagnostics Blueprint. Les blocages d'exécution peuvent masquer un outil pour un jeton délimité ou globalement, rejeter les appels directs avec `runtime_access_denied` et sont effacés à l'arrêt du serveur.

## Le journal d'accès (Access Journal) stocke-t-il des secrets ?

Il est conçu pour des diagnostics sécurisés vis-à-vis des secrets. Les clés d'arguments ressemblant à des secrets telles que token, secret, password, API key, authorization et bearer sont omises en mémoire et dans le journal d'accès JSONL. Les chaînes masquées et les entrées RAM assainies sont plafonnées par des réglages.

## Qu'est-ce que `mesh_configure_experimental_self_approval` ?

Il s'agit d'un outil de fournisseur Capability Mesh d'approbation automatique autonome **EXPÉRIMENTAL**. Il permet de modifier la possibilité pour les routes UCM nécessitant une approbation de s'auto-approuver globalement ou par identifiant de route. Son activation nécessite `acknowledge_experimental_risk: true` et est réservée aux flux de test à vos propres risques.

## Plusieurs plugins peuvent-ils ajouter des outils ?

Oui. Tout plugin peut enregistrer un `IUmcpToolProvider`. Les noms d'outils sont préfixés par l'identifiant du fournisseur.

## Les clients peuvent-ils consulter les paramètres des outils et le niveau de risque ?

Oui. `tools/list` inclut l'`inputSchema` de chaque outil, l'`outputSchema` optionnel et les annotations d'outils optionnelles. Les outils de routes UCM les dérivent des liaisons de routes, des manifestes de schémas, de la politique et des effets secondaires.

## Comment inspecter les outils raccordés dans l'éditeur ?

Ouvrez **Tiny Tools -> AI -> Universal MCP -> Open Control Panel**. La zone Connected Functions regroupe les outils par plugin, prend en charge le dépliage différé des schémas d'entrée/sortie et conserve en cache les métadonnées inchangées entre les visites. Cliquez sur **Refresh** après des modifications de configuration UCM pour forcer un rechargement complet.

## Pourquoi UMCP a-t-il rejeté mes arguments d'outil avant que le fournisseur ne s'exécute ?

Le réglage `Validate Tool Arguments` est activé. UMCP vérifie alors les arguments entrants par rapport à l'`inputSchema` de l'outil sélectionné et renvoie `invalid_tool_arguments` en cas de champs requis manquants, de champs inconnus interdits, de divergences de types ou de divergences d'énumérations.

## Quelles sont les versions d'Unreal Engine ciblées ?

Le plugin est conçu pour les plugins de code Unreal Engine 5.x et utilise C++20 pour la compatibilité actuelle avec UE 5.6.

## Est-ce destiné aux jeux empaquetés (Packaged Games) ?

Non. Le serveur actuel est une infrastructure d'éditeur pour les outils locaux et les agents.

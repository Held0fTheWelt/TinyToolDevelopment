<!-- doc-provenance: AKDB:plugins/UnrealCapabilityMesh/architecture.md; docs/architecture/plugins/UnrealCapabilityMesh/product-facts.yml; reconciled 2026-07-19 -->
# FAQ

## UCM est-il un modèle ou un agent d'IA ?

Non. UCM est un hub d'interopérabilité. Il peut décrire des capacités liées à l'IA, mais il n'inclut aucun modèle, prompt, fournisseur ou runtime d'agent.

## UCM modifie-t-il les actifs ?

Pas de lui-même. Il charge uniquement des manifestes, planifie des routes, invoque des points d'entrée déclarés et rédige des diagnostics. La mutation d'actifs doit être exécutée par un point d'entrée de fournisseur et autorisée par la politique.

## L'approbation peut-elle être contournée ?

Uniquement via les commandes d'auto-approbation automatique explicitement étiquetées **EXPÉRIMENTAL** dans la colonne d'approbation du catalogue de routes de la page Routes, les champs correspondants de `project_profile.json` ou l'outil MCP `mesh_configure_experimental_self_approval`. Il s'agit d'un contournement global des politiques : les règles de refus, les contrôles de mutation d'actifs/projet, les exigences d'approbation et d'essai à blanc sont ignorés. C'est uniquement réservé aux tests ou aux flux de travail locaux à vos propres risques ; conservez **Approve all at own risk** et tous les commutateurs par route désactivés pour un usage normal.

## Pourquoi utiliser des manifestes plutôt que des dépendances C++ directes ?

Les manifestes permettent aux projets de connecter des outils sans créer de chaînes de dépendances à la compilation entre les plugins. Cela conserve un hub neutre et plus simple à empaqueter.

## Où les rapports sont-ils écrits ?

Les rapports sont écrits sous `Saved/UnrealCapabilityMesh`.

## Où les manifestes du projet sont-ils stockés ?

Les manifestes du projet sont stockés sous `Config/UnrealCapabilityMesh`.

## UCM peut-il intégrer des plugins tiers de la marketplace ?

Oui, lorsque ces plugins exposent des fonctions appelables, des contrats de fichiers ou des fonctionnalités modulaires pouvant être décrits par des manifestes ou des adaptateurs.

## UCM intègre-t-il du code tiers ?

Aucun code source tiers ni aucune dépendance d'exécution tierce n'est inclus dans le plugin.

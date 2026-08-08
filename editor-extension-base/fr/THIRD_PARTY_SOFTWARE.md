---
lang: fr
title: EditorExtensionBase Third-Party Software
audience: [end_user]
owner_ref: plugin:EditorExtensionBase
applies_to:
  component: EditorExtensionBase
contract_ref: plugin:EditorExtensionBase/third-party-software
version:
  since: "1.0"
---
# Logiciels tiers

Editor Extension Base **n'inclut aucun code source tiers, aucun binaire d'exécution, aucun modèle d'IA, Node.js, Python ni exécutable autonome**. Il s'agit d'un plugin Unreal Engine en C++ construit sur les modules de l'éditeur Unreal et les utilitaires de script d'éditeur.

## Méthode de mesure

Recherche dans `GovernanceDevelopmentPlugins/EditorExtensionBase` des termes `ThirdParty`, `LICENSE-` et des marqueurs de droits d'auteur. Les en-têtes identifient la licence EULA de Tiny Tool Development / Fab. Aucun arbre tiers intégré n'est présent.

## Dépendances du moteur (non incluses)

| Dépendance | Inclus ? | Notes |
| --- | --- | --- |
| Modules de l'éditeur Unreal Engine | Non | Fournis par l'installation du moteur. |
| Utilitaires de script d'éditeur | Non | Activés via l'entrée `Plugins` du fichier `.uplugin` ; plugin détenu par Epic. |

## Intégrations facultatives

Les plugins de fonctionnalités peuvent dépendre d'Editor Extension Base pour des widgets partagés. Ces consommateurs sont des packages distincts et ne sont pas redistribués ici.

**Déclaration de logiciels tiers de Fab :** aucune.

## Documents associés

- [README.md](README.md)
- [QUICKSTART.md](QUICKSTART.md)
- [FAQ.md](FAQ.md)

## En-têtes de droits d'auteur

Les sources de l'éditeur et d'exécution utilisent les en-têtes de licence EULA Standard de Tiny Tool Development / Fab. Aucun fichier de licence supplémentaire n'a été trouvé sous un répertoire `ThirdParty`.

## Liste de contrôle de la déclaration de l'acheteur

1. Déclarer **aucun** logiciel tiers intégré pour Fab.
2. Editor Scripting Utilities reste une dépendance du plugin du moteur Epic, et non un arbre tiers intégré.
3. Relancer la recherche après tout futur changement d'intégration avant de mettre à jour ce fichier.

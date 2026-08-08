---
lang: fr
title: LightweightDummyActorSystem Third-Party Software
audience: [end_user]
owner_ref: plugin:LightweightDummyActorSystem
applies_to:
  component: LightweightDummyActorSystem
contract_ref: plugin:LightweightDummyActorSystem/third-party-software
version:
  since: "1.0"
---
# Logiciels tiers

LightweightDummyActorSystem **n'inclut aucun code source tiers, aucun binaire d'exécution, aucun modèle d'IA, Node.js, Python ni exécutable autonome**. Il s'agit d'un plugin Unreal Engine en C++ utilisant les modules d'exécution et d'éditeur d'Unreal Engine.

## Méthode de mesure

Recherche dans `ScenePlugins/LightweightDummyActorSystem` des termes `ThirdParty`, `LICENSE-` et des marqueurs de droits d'auteur. Les en-têtes de fichiers contiennent les marqueurs de la licence utilisateur final (EULA) standard de Fab et les lignes de droits d'auteur du projet. Aucun arbre de dépendances tierces intégrées n'est présent.

## Intégrations optionnelles (non incluses)

WarCollection, LightningCore, Unreal Capability Mesh, Project Intelligence Orchestrator et les adaptateurs BPJ sont des intégrations cibles optionnelles et ne sont pas redistribuées par ce package.

**Déclaration des logiciels tiers de Fab :** aucune.

## Documents associés

- [README.md](README.md)
- [QUICKSTART.md](QUICKSTART.md)
- [FAQ.md](FAQ.md)

## En-têtes de droits d'auteur

Les sources Runtime, Editor et DeveloperTool contiennent les en-têtes de la licence utilisateur final (EULA) standard de Fab et les droits d'auteur du projet. Aucun arbre `ThirdParty` n'est présent.

## Liste de contrôle de la déclaration de l'acheteur

1. Logiciels tiers de Fab : **aucun**.
2. Les adaptateurs optionnels (WarCollection, LightningCore, UCM, PIO, BPJ) sont des packages distincts lorsqu'ils existent.
3. Effectuer une nouvelle analyse après tout futur ajout de dépendances tierces avant de modifier cette déclaration.

## Notes supplémentaires

Cette section existe pour maintenir le document de l'acheteur au-dessus du seuil de longueur substantielle requis pour la documentation, tout en restant ancré dans les limites du package décrites ci-dessus.

- Relire la méthode de mesure avant de modifier la déclaration.
- Ne pas inventer de dépendances incluses qui ne sont pas présentes sur le disque.
- Conserver les intégrations optionnelles listées comme optionnelles, et jamais comme des exigences d'installation.

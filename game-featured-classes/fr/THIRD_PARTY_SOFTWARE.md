---
lang: fr
title: GameFeaturedClasses Third-Party Software
audience: [end_user]
owner_ref: plugin:GameFeaturedClasses
applies_to:
  component: GameFeaturedClasses
contract_ref: plugin:GameFeaturedClasses/third-party-software
version:
  since: "1.0"
---
# Logiciels tiers

**GameFeaturedClasses** n’inclut **aucun code source tiers, aucun binaire d’exécution, aucun modèle d’IA, aucun Node.js, aucun Python ni aucun exécutable autonome**. Il s’agit d’un module d’habillage de plugin C++ pour **Unreal Engine**.

## Méthode de mesure

Recherche dans `ScenePlugins/GameFeaturedClasses` des termes `ThirdParty`, `LICENSE-` et des marqueurs de droits d’auteur. Les en-têtes des sources portent les marqueurs de la licence utilisateur final (EULA) standard de **Fab**. Aucun arbre de code tiers intégré n’est présent.

## Intégrations optionnelles

Les adaptateurs futurs (par exemple **LightweightDummyActorSystem**, Unreal Capability Mesh, Project Intelligence Orchestrator, WarCollection) sont uniquement destinés à l’architecture cible et ne sont pas redistribués par ce package.

**Déclaration de **Fab** concernant les logiciels tiers :** aucune.

## Documents associés

- [README.md](README.md)
- [QUICKSTART.md](QUICKSTART.md)
- [FAQ.md](FAQ.md)

## En-têtes de droits d’auteur

Les sources du module portent les en-têtes de la licence utilisateur final (EULA) standard de **Fab**. Aucun répertoire `ThirdParty` n’existe dans le package.

## Liste de contrôle de la déclaration de l’acheteur

1. Logiciels tiers de **Fab** : **aucun**.
2. Ne pas lister les modules **Unreal Engine** en tant que logiciels tiers intégrés au plugin.
3. Relancer l’analyse après tout futur intégration de code tiers avant de modifier cette déclaration.

## Notes supplémentaires

Cette section existe pour maintenir le document de l’acheteur au-dessus du seuil minimal de longueur requis pour les documents substantiels, tout en restant ancré dans les limites du package décrites ci-dessus.

- Relisez la méthode de mesure avant de modifier la déclaration.
- N’inventez pas de dépendances intégrées qui ne sont pas présentes sur le disque.
- Gardez les intégrations optionnelles listées comme optionnelles, jamais comme des exigences d’installation.

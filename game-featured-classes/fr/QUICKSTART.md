---
lang: fr
title: GameFeaturedClasses Quick Start
audience: [end_user]
owner_ref: plugin:GameFeaturedClasses
applies_to:
  component: GameFeaturedClasses
preconditions:
  - Unreal Engine project open with the plugin package available
  - Edit > Plugins can enable GameFeaturedClasses
expected_result:
  text: GameFeaturedClasses runtime module is enabled and loads after editor restart.
version:
  since: "1.0"
---
# Démarrage rapide

Ce guide installe et active **GameFeaturedClasses** et vérifie que le module d’exécution se charge correctement. La version `1.0.1` est un **coquille de module** : elle fournit le descripteur, les métadonnées d’emballage, l’icône et le journal des modifications. Elle ne propose **pas encore** de classes de jeu, d’actions Game Feature ou d’atelier d’édition.

## Ce que vous aurez après ce guide

Le plugin activé dans votre projet, avec le module d’exécution `GameFeaturedClasses` présent dans la liste des modules après le redémarrage de l’éditeur.

## Prérequis

- Unreal Engine 5.4–5.8 (matrice des versions packagées).
- Aucun autre plugin Tiny Tool n’est requis pour la coquille.
- Aucun logiciel tiers, compte ou runtime externe n’est nécessaire. Consultez [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md).

## 1. Installer et activer

1. Acquérir **GameFeaturedClasses** depuis Fab et l’ajouter au projet (ou l’installer sous le répertoire Plugins de l’engine).
2. Ouvrir **Édition → Plugins**, rechercher **GameFeaturedClasses**, l’activer et redémarrer lorsque demandé.

## 2. Confirmer la limite du module

Après le redémarrage, vérifiez que le module d’exécution est chargé (Journal de sortie / gestionnaire de modules). L’interface publique du module est `FGameFeaturedClassesModule` dans `Source/GameFeaturedClasses/Public/GameFeaturedClasses.h` avec uniquement `StartupModule` / `ShutdownModule`.

## 3. Exemple concret : vérification de base de la coquille

1. Créez ou ouvrez un projet sur Unreal Engine 5.4+.
2. Activez le plugin comme indiqué ci-dessus et redémarrez.
3. Dans le Journal de sortie, filtrez les bruits de démarrage de module pour `GameFeaturedClasses` après le chargement.

Il n’y a pas d’interface utilisateur de registre de classes vedettes ni d’action Game Feature d’exemple à exécuter dans cette version du package. Il est attendu que l’appel de menus d’atelier inexistants échoue car ces surfaces ne sont **pas encore disponibles**.

## Résultat attendu

- Le plugin apparaît comme activé sous **Édition → Plugins**.
- Le module d’exécution démarre et s’arrête sans nécessiter de plugins Tiny Tool pairs.
- Aucune ressource de classe vedette de jeu n’apparaît dans le Content Browser à partir de ce package (aucune n’est fournie).

## Prochaines étapes

- Lisez [UserManual.md](UserManual.md) pour la limite actuelle vs cible.
- Lisez [FAQ.md](FAQ.md) pour les questions de portée.
- Considérez le comportement de l’atelier GameFeature premium comme l’architecture cible jusqu’à ce qu’un package ultérieur fournisse ces classes et ces surfaces d’édition.

## Limites à retenir

- N’ajoutez pas de classes de jeu de projet dans ce dossier de plugin en espérant qu’elles soient livrées en tant que contenu GFC dans la version 1.0.1.
- N’activez pas les plugins pairs uniquement pour « débloquer » un atelier qui n’est pas encore packagé.
- Lorsqu’une version ultérieure livrera des classes vedettes, mettez à jour ce guide de démarrage rapide avec de vrais noms de classes et un exemple concret issu de cette version.

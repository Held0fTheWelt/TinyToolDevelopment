---
lang: fr
title: GameFeaturedClasses Settings Reference
audience: [end_user]
owner_ref: plugin:GameFeaturedClasses
applies_to:
  component: GameFeaturedClasses
contract_ref: plugin:GameFeaturedClasses/module-shell-settings
version:
  since: "1.0"
---
# Référence des paramètres

GameFeaturedClasses 1.0.1 ne fournit **pas** de DeveloperSettings, d'objets de configuration `.ini`, ni de descripteurs de classe mise en avant modifiables. Le module d'exécution n'expose aucune surface de paramètres `UPROPERTY` au-delà de l'interface de module vide.

## Surfaces livrées

| Nom | Type | Défaut | Effet |
| --- | --- | --- | --- |
| Activation du plugin | Interface utilisateur des plugins de l'éditeur | désactivé jusqu'à ce que l'acheteur l'active | Charge le module d'exécution `GameFeaturedClasses`. |
| `FGameFeaturedClassesModule::StartupModule` | crochet de module | invoqué par le moteur | Démarrage du module ; aucun paramètre acheteur. |
| `FGameFeaturedClassesModule::ShutdownModule` | crochet de module | invoqué par le moteur | Arrêt du module ; aucun paramètre acheteur. |

## Pas encore disponible

| Surface de paramètre attendue | Statut |
| --- | --- |
| Actifs descripteurs de classe mise en avant | pas encore disponible |
| Actifs d'ensemble de fonctionnalités | pas encore disponible |
| Paramètres de registre / résolution | pas encore disponible |
| Préférences de l'atelier de l'éditeur | pas encore disponible |
| `UGameFeaturedClassesSettings` DeveloperSettings | pas encore disponible |
| `Config/DefaultGameFeaturedClasses.ini` | non livré |

Aucune ligne de paramètre n'est inventée ici. Lorsque les versions ultérieures du package ajouteront de vrais champs `UPROPERTY` / DeveloperSettings, cette référence doit être mise à jour à partir du code source dans le même changement.

## Documents associés

- [UserManual.md](UserManual.md) — limite actuelle vs cible.
- [QUICKSTART.md](QUICKSTART.md) — vérification rapide d'activation.
- [FAQ.md](FAQ.md)

## Métadonnées d'emballage (pas des paramètres d'exécution)

Le descripteur `.uplugin` contient `Version` / `VersionName` pour l'emballage. Ces champs sont des métadonnées de plugin, pas des DeveloperSettings d'exécution, et ne doivent pas être modifiés de manière informelle depuis les flux de travail des documents acheteur.

## Règle de mise à jour

Toute future ligne de paramètre dans ce fichier doit citer le chemin de l'en-tête et le nom de la propriété depuis le code source dans le même changement de documentation.

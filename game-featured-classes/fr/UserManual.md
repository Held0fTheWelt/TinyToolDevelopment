# Manuel utilisateur

GameFeaturedClasses fournit actuellement un module d’infrastructure léger pour les classes de gameplay mises en avant spécifiques au projet.

## Comportement actuel du package

| Zone | Statut dans la version 1.0.1 |
| --- | --- |
| Module d’exécution (`GameFeaturedClasses`) | Livré — démarrage/arrêt uniquement. |
| Descripteur / packaging / icône / journal des modifications | Livré. |
| Classes de gameplay mises en avant | pas encore disponibles |
| Actions Game Feature / assets de jeu de fonctionnalités | pas encore disponibles |
| Registre d’exécution / limite d’interface | pas encore disponibles |
| Atelier d’édition / réparation / rapports de preuve | pas encore disponibles |
| Routes d’automatisation des Tiny Tools | pas encore disponibles |

<!-- image slot: gfc-module-shell -->

## Carte source

- `Source/GameFeaturedClasses/GameFeaturedClasses.Build.cs` — dépendances du module.
- `Source/GameFeaturedClasses/Public/GameFeaturedClasses.h` — interface `FGameFeaturedClassesModule`.
- `Source/GameFeaturedClasses/Private/GameFeaturedClasses.cpp` — démarrage et arrêt.

## Comment utiliser le module d’infrastructure aujourd’hui

1. Activez le plugin (voir [QUICKSTART.md](QUICKSTART.md)).
2. Conservez les classes de gameplay mises en avant spécifiques au projet dans vos propres modules jusqu’à ce que ce package les livre.
3. Ne documentez pas et ne dépendez pas des menus de l’atelier qui ne sont pas présents dans cette version.

## Architecture cible (informative, non livrée)

L’architecture interne du produit décrit un futur Atelier GameFeature premium où les auteurs déclarent les classes mises en avant et les jeux de fonctionnalités, les actions à portée de monde les enregistrent, les consommateurs les résolvent via une limite registre/interface, et les mainteneurs analysent un graphe de fonctionnalités, prévisualisent les réparations gouvernées et exportent des rapports de preuve. Ce comportement est **uniquement spécifié pour la cible** et ne doit pas être considéré comme une fonctionnalité disponible pour l’acheteur dans la version 1.0.1.

## Autarcie

Le module d’infrastructure se charge de lui-même. Les futures intégrations optionnelles avec LightweightDummyActorSystem, Unreal Capability Mesh ou Project Intelligence Orchestrator ne sont pas des exigences de configuration pour ce package.

## Documents associés

- [QUICKSTART.md](QUICKSTART.md)
- [SettingsReference.md](SettingsReference.md)
- [FAQ.md](FAQ.md)
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md)
- [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md)

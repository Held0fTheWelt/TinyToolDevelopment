<!-- doc-provenance: product-facts.yml reconciled 2026-07-15; source AKDB:plugins/AsyncSplineBuilder/architecture.md -->
# FAQ

## À quoi sert Async Spline Builder ?

Il construit des maillages suivant une spline, tels que des routes, des circuits de course, des rails, des tuyaux, des barrières et des murs de tènement procéduraux. Son principal avantage est le traitement par lots asynchrone, permettant de régénérer de longues splines sans provoquer de calage majeur de l'éditeur.

## Fonctionne-t-il au runtime ?

Oui. Les maillages de route, les maillages supplémentaires, les murs de tènement, les murs de dénivelé et la pompe asynchrone au runtime résident dans le module runtime. La déformation de hauteur de paysage réservée à l'éditeur n'est pas disponible dans les versions empaquetées.

## Quelle orientation doit utiliser mon maillage de route ?

Créez des maillages de route répétitifs le long de l'axe X local. Le générateur utilise les limites du maillages sur X pour la longueur par défaut et les limites sur Y pour la largeur par défaut.

## Puis-je utiliser des maillages différents par segment ?

Oui. Ajoutez des entrées dans `TrackSplineData` et définissez `RoadMesh`, `RoadMeshLength`, `SegmentLength`, `MeshInstances` et les tableaux de maillages supplémentaires par segment. Les données de segment manquantes se rabattent sur l'entrée `0`.

## Où puis-je configurer le plugin ?

Utilisez **Tools > Track Tools > Async Spline Builder** pour le flux de travail classique. Il vous offre la sélection d'actor, la configuration des maillages, la validation, les commandes de génération, les paramètres asynchrones, les interrupteurs d'affichage de spline, les assistants de segment, les actions de paysage et l'activation des murs de tènement dans un seul panneau. Utilisez le panneau Details pour les tableaux avancés par segment et les champs détaillés de tracé, mur, collision, UV et assets de données.

## Quelle est la différence entre BuildTrack et RebuildTrack ?

`BuildTrack` est synchrone et immédiat. `RebuildTrack` utilise le traitement par lots asynchrone lorsque `bUseAsyncBuild` est activé.

## La génération asynchrone utilise-t-elle des threads secondaires (worker threads) ?

Non. Elle fractionne le travail sur plusieurs ticks. Cela maintient la création de composants Unreal sur le thread de jeu (game thread), qui est l'emplacement approprié pour l'enregistrement des instances de `UActorComponent`.

## Peut-il créer des glissières de sécurité ou des maillages latéraux ?

Oui. Utilisez `ExtraMeshStart`, `ExtraMesh`, `ExtraMeshEnd` et `ExtraMeshOffset` dans `FTrackSplineData`.

## Peut-il créer des sauts ou des sections de route manquantes ?

Oui. Utilisez `JumpGapsByPoints`. Les interruptions neutralisent les maillages de route et supplémentaires pour des plages de segments.

## Peut-il créer des dénivelés de hauteur ?

Oui. Utilisez `StuntDropsByPoints`. Les segments adjacents sans interruption situés à des hauteurs différentes créent des murs de dénivelé.

## Peut-il créer des murs jusqu'au sol ?

Oui. Activez `bGenerateGroundWalls` et configurez les types d'objets de tracé. Les bandes de mur procédurales tracent depuis les bords de la route vers le bas jusqu'aux types d'objets configurés.

## Déforme-t-il les paysages ?

Oui, dans l'éditeur. Utilisez `DeformLandscapeNow` pour la hauteur et `PaintLandscapeLayerNow` (ou le panneau **Paint Layer**) pour la peinture de poids additive lorsque `PaintLayer` est assigné.

## Peint-il des couches de paysage ?

Oui, pour une seule couche globale `PaintLayer` en utilisant une peinture additive `max`. Définissez `PaintLayer` sur l'actor, assignez le paysage, puis exécutez **Paint Layer**. Les informations de couche avec mélange de poids réduisent les autres couches sous la route. Les informations de couche avec `bNoWeightBlend` peuvent peindre la couche cible, mais ne garantissent pas la réduction des autres couches. Non pris en charge : mode remplacement/effacement, couches de peinture par segment, ou effacement automatique des anciens poids lors de la réduction de la bande de peinture.

## Pourquoi la validation a-t-elle bloqué ma génération ?

L'actor bloque les générations en cas de mauvaise configuration destructive, telle que l'absence de `MainMesh` ou des fonctionnalités basées sur le tracé activées sans types d'objets de tracé. Cela protège la géométrie générée existante contre l'effacement avant qu'un remplacement valide puisse être effectué.

## Pourquoi mes murs sont-ils manquants ?

Les causes courantes sont des types d'objets de tracé manquants, l'absence d'impacts de tracé, un `MinWallHeight` trop élevé, des interruptions de saut coupant la bande, ou `bGenerateGroundWalls` désactivé dans les paramètres par segment.

## Nettoie-t-il les composants générés en toute sécurité ?

Oui. Les composants générés reçoivent des tags stables, et le nettoyage balaye les tags plutôt que de se fier uniquement à des tableaux temporaires.

## Puis-je sauvegarder l'agencement de la spline ?

Oui. Assignez `SplinePointList` et utilisez `WriteSplineToDataAsset` / `ReadSplineFromDataAsset`.

## Puis-je l'utiliser pour des produits Fab ou des jeux commerciaux ?

Oui, sous réserve des termes de la licence du produit. Le plugin ne concède aucun droit sur les maillages, matériaux ou contenus tiers que vous utilisez avec lui.

<!-- doc-provenance: product-facts.yml reconciled 2026-07-15; source AKDB:plugins/AsyncSplineBuilder/architecture.md -->
# Dépannage

## L'actor ne génère rien

Vérifiez :

- `MainMesh` est assigné.
- La spline possède au moins deux points.
- La validation n'a pas bloqué la génération.
- `bEditSpline` n'efface pas intentionnellement les composants générés.
- Les maillages générés ne sont pas masqués par la visibilité du niveau ou de l'actor.

## La génération est bloquée par la validation

La validation bloque les générations défectueuses et destructrices. Causes courantes :

- `MainMesh` est manquant.
- Les murs de tènement sont activés mais aucun type d'objet de tracé de mur n'est configuré.
- L'alignement sur le paysage est activé mais aucun type d'objet de tracé de paysage n'est configuré.
- Les plages d'interruptions de saut ou de dénivelé sont invalides.

Corrigez le paramètre et réexécutez `RebuildTrack`.

## La validation des connecteurs signale des problèmes

Connector Validation Reports Issues survient lorsqu'un connecteur d'agencement passif pointe vers un actor manquant, un identifiant d'agencement inconnu, une distance de spline invalide ou des métadonnées de connecteur incomplètes.

Corrigez l'enregistrement du connecteur dans le panneau de flux de travail ou le panneau Details, puis réexécutez `Validate Layout Connectors`. La validation des connecteurs est distincte de la génération géométrique : les enregistrements de connecteurs décrivent l'intention du parcours et ne créent pas de maillages de transition par eux-mêmes.

## Une étiquette d'extrémité de connecteur est manquante

Activez **Show Connector Debug** dans la section **Layout Connectors** du panneau. Si un seul côté d'un connecteur apparaît, exécutez **Validate Layout Connectors** et corrigez l'agencement manquant ou la distance hors plage signalée pour l'extrémité masquée. Les extrémités sont résolues indépendamment et les positions invalides sont intentionnellement ignorées.

Les étiquettes de connecteurs sont purement visuelles. Vous n'avez pas besoin de reconstruire la piste pour les créer ou les rafraîchir, et corriger une étiquette n'ajoute pas de géométrie de route de connecteur et ne modifie pas le comportement du terrain.

## Le panneau de flux de travail ne s'ouvre pas

Ouvrez-le via **Tools > Track Tools > Async Spline Builder**. Si l'entrée du menu est manquante :

- recompilez la cible éditeur
- confirmez que le module `AsyncSplineBuilderEditor` est activé
- redémarrez l'éditeur après avoir activé le plugin
- vérifiez l'Output Log pour y déceler des erreurs de démarrage de `AsyncSplineBuilderEditor`

Le panneau est réservé à l'éditeur et n'est pas disponible dans les versions empaquetées.

## L'éditeur gèle pendant la régénération

Utilisez des paramètres asynchrones :

- `bUseAsyncBuild = true`
- réduisez `SegmentsPerTick`
- désactivez les collisions de murs coûteuses pendant l'itération
- réduisez `GroundWallSubdivisions`

Les nombres très élevés de composants peuvent rester coûteux car l'enregistrement des composants Unreal s'effectue sur le thread de jeu (game thread).

## Les maillages supplémentaires apparaissent au mauvais endroit

Vérifiez :

- le pivot et les axes locaux du maillages
- `ExtraMeshOffset`
- `bMirrorExtraMesh`
- le secours des données de segment vers l'index `0`
- si les tableaux début/milieu/fin contiennent des maillages différents

Les maillages supplémentaires utilisent le même intervalle de spline que la pièce de route.

## Les maillages de route s'étirent trop

Définissez l'un des champs suivants :

- `MeshInstances` pour un nombre exact
- `RoadMeshLength` pour une longueur de pièce explicite
- `SegmentLength` pour un nombre automatique basé sur l'espacement souhaité

Si aucun n'est défini, la limite X du maillages est utilisée.

## La boucle fermée présente une mauvaise jonction

Vérifiez :

- les positions/tangentes du premier et du dernier point de spline
- le pivot et la longueur de répétition du maillages
- l'utilisation de `StartMesh` sur les boucles fermées
- les paramètres de lissage des tangentes

Les boucles fermées génèrent un segment d'enroulement jusqu'à la longueur de la spline.

## Les murs de tènement n'apparaissent pas

Vérifiez :

- `bGenerateGroundWalls` activé sur l'actor
- `GroundWallSettings.bGenerateGroundWalls` par segment
- `GroundWallObjectsToHitForLineTrace`
- `TraceSettings.ObjectsToHit` par segment
- la longueur de tracé
- `MinWallHeight`
- les interruptions de saut

Si les tracés échouent, la profondeur de secours est utilisée. Si la hauteur du mur reste inférieure à `MinWallHeight`, aucune section n'est créée.

## Les murs de tènement franchissent les interruptions

Ils ne le devraient pas. Si vous observez cela, confirmez que la plage d'interruption utilise la sémantique des segments :

```text
[StartPointIndex, EndPointIndex)
```

Exécutez également la suite d'automatisation ; `GroundWallGapStripValid` couvre le comportement de séparation de bande de base.

## La largeur du mur de tènement est incorrecte

La largeur est déduite des limites Y du maillages de route sélectionné, sauf si `TrackHalfWidth` est supérieur à zéro. Si les limites du maillages ne sont pas représentatives, définissez manuellement `TrackHalfWidth`.

## Les murs de dénivelé n'apparaissent pas

Vérifiez :

- les deux segments voisins possèdent une route
- la limite ne se trouve pas à l'intérieur d'une interruption de saut
- les segments adjacents se résolvent en des valeurs Z absolues différentes dans le monde
- `DropHeight` ou un Z constant est défini d'un côté

Exécutez `AsyncSplineBuilder.DropWallCount` pour le comportement de base des murs de dénivelé.

## L'alignement sur le paysage ne fait rien

Vérifiez :

- `bSnapMeshesToLandscape` ou `bSnapPointsToLandscape` est activé
- `ObjectsToHitForLandscapeLineTrace` contient des types d'objets
- le type d'objet de collision du paysage correspond à la requête
- `ActorsToIgnoreForGenerationTraces` n'inclut pas la cible
- la longueur de tracé atteint la surface

## La déformation du paysage ne fait rien

Vérifiez :

- `Landscape` est assigné
- le module éditeur est chargé
- la spline possède des points valides
- `NumberOfSubdivisionsForDeform` est supérieur à zéro
- au moins l'un de `bRaiseHeights` ou `bLowerHeights` est activé
- la route chevauche la zone du paysage

Rappelez-vous : la déformation est une action manuelle dans l'éditeur via `DeformLandscapeNow`.

## La couche de matériau du paysage n'est pas peinte

La déformation de hauteur (`DeformLandscapeNow`) et la peinture de poids de couche (`PaintLandscapeLayerNow`) sont des actions distinctes. La peinture de couche nécessite un `PaintLayer` valide enregistré sur le paysage. L'annulation est gérée par la transaction du déformateur ; testez l'annulation sur le panneau, en CallInEditor et avec une couche de modification de paysage active.

Si les informations de couche sélectionnées utilisent `bNoWeightBlend`, l'opération doit afficher un avertissement. Dans cette configuration, la couche cible peut recevoir de la peinture, mais le comportement habituel « les autres couches sont réduites sous la route » n'est pas garanti.

## La géométrie générée se duplique après une régénération

Les composants générés sont nettoyés par tags. Si des doublons apparaissent :

- vérifiez si du code personnalisé crée des composants sans `GeneratedTag`
- vérifiez si un composant modifié a été dupliqué manuellement
- exécutez l'automatisation `CleanupRemovesAllTagged`

## Le mode asynchrone au runtime ne se termine pas

Vérifiez :

- `bUseAsyncBuild = true`
- le gestionnaire de minuterie du monde fonctionne
- l'actor est valide et non détruit
- `SegmentsPerTick` est d'au moins `1`
- la validation n'a pas interrompu le processus avant le démarrage

La pompe au runtime s'arme de nouveau avec `SetTimerForNextTick` pendant la génération.

## BuildPlugin ou la compilation échoue en raison de collisions Unity

Certains modules définissent des assistants au nom similaire dans des espaces de noms anonymes. Si le regroupement Unity combine ces fichiers, MSVC peut signaler des définitions en double. Le module concerné doit utiliser des paramètres de compilation hors-Unity tels que `bUseUnity = false`.

## L'automatisation ne trouve aucun test

Vérifiez :

- la cible éditeur a été compilée
- les tests d'automatisation de développement sont activés
- la commande utilise `Automation RunTests AsyncSplineBuilder`
- les tests sont compilés dans le module éditeur

## Les journaux sont trop bruyants

Recherchez dans le journal :

```text
AsyncSplineBuilder
Result={Fail}
Result={Success}
TEST COMPLETE
```

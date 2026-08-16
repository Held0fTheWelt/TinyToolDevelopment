<!-- doc-provenance: product-facts.yml reconciled 2026-07-15; source AKDB:plugins/AsyncSplineBuilder/architecture.md -->
# Manuel utilisateur

Ce manuel explique comment utiliser Async Spline Builder dans l'éditeur Unreal et comment s'articulent les fonctionnalités principales.

## Objectif

Async Spline Builder crée des composants générés à partir d'une spline éditable. Le résultat typique est une route ou une piste composée de sections `USplineMeshComponent`, avec des maillages de spline supplémentaires optionnels et des maillages de mur procéduraux.

L'actor peut régénérer de manière synchrone ou par lots. Le traitement par lots maintient la réactivité de l'éditeur sur les longues pistes et est également disponible au runtime via une pompe à minuterie au tick suivant.

## Ouverture et activation

1. Ouvrez **Edit > Plugins**.
2. Activez **AsyncSplineBuilder**.
3. Redémarrez l'éditeur si demandé.
4. Ouvrez ou créez un niveau.
5. Ouvrez **Tools > Track Tools > Async Spline Builder**.

Le plugin contient à la fois des modules runtime et éditeur. L'actor est utilisable au runtime ; le panneau de flux de travail et les outils de déformation du paysage sont réservés à l'éditeur.

## Panneau de flux de travail

Le panneau Async Spline Builder est la méthode recommandée pour configurer des pistes normales. Il évite de disperser le flux de travail classique entre plusieurs catégories Details.

Le panneau est organisé en onglets :

- **Build** : sélection d'actor, configuration des maillages, validation/génération/régénération/annulation, traitement par lots asynchrone, boucle fermée, étiquettes de débogage de points ou segments, et étiquettes d'extrémité de connecteurs d'agencement optionnelles.
- **Segments** : `TrackSplineData` par segment, création de lignes de segments, interruptions de saut et dénivelés.
- **Terrain** : alignement sur le paysage, assignation du paysage, paramètres de peinture de couche, déformation de hauteur, peinture de couche additive et murs de tènement.

Utilisez le panneau Details pour les tableaux avancés et les paramètres rares qui ne sont pas dupliqués dans le panneau de flux de travail.

## Configuration de base de l'actor

1. Dans le panneau de flux de travail, appuyez sur **Create Actor** ou sélectionnez un `ASplineGeneratingActor` existant et appuyez sur **Use Selection**.
2. Dans **Setup**, assignez `MainMesh`.
3. Optionnellement, assignez `StartMesh` et `EndMesh`.
4. Déplacez les points de spline dans le viewport.
5. Appuyez sur **Validate**.
6. Appuyez sur **Build Now** ou **Rebuild**.

`MainMesh` est requis. La validation bloque la génération sans lui afin que la géométrie générée existante ne soit pas effacée et remplacée par rien.

## Attentes de création de maillage

Les maillages de route doivent :

- Se répéter le long de leur axe X local.
- Avoir une étendue Y cohérente car les limites du maillages sont utilisées pour déduire la demi-largeur de la route.
- Utiliser des pivots constants.
- Éviter la complexité de collision cachée sauf si la collision est nécessaire.

Si les limites du maillages ne sont pas représentatives, définissez manuellement `GroundWallSettings.TrackHalfWidth`.

## Édition de la spline

Utilisez les outils standard d'édition de spline d'Unreal. Champs utiles :

- `bClosedLoop` : relie le dernier point au premier point.
- `SplinePointType` : contrôle le comportement d'interpolation des points.
- `SplineZOffset` : applique un décalage vertical au composant spline.
- `bShowPointNumbers` : affiche les indices de points.
- `bShowSegmentNumbers` : affiche les indices de segments.
- `bShowSplineVisualizationWidth` : affiche une spline plus large dans l'éditeur.

Les numéros de points et de segments sont des composants de débogage générés et sont nettoyés par le même système de tags que celui utilisé pour la géométrie générée.

## Track Shape Editor

Ouvrez **Tools > Track Tools > Track Shape Editor** lorsque vous avez besoin d'une surface de création multi-agencements compacte plutôt que de modifier uniquement les points de spline bruts de l'actor. L'éditeur travaille sur un document natif `track_shape.v1` et peut appliquer des agencements compilés principaux, de stands, alternatifs ou de service à l'actor `ASplineGeneratingActor` sélectionné.

La section **Designer Tools** fournit les commandes d'édition quotidiennes :

- ajouter des agencements de stands, alternatifs ou de service
- dupliquer ou supprimer l'agencement non principal sélectionné
- modifier le type d'agencement et l'état de boucle fermée
- sélectionner l'agencement, l'ancre ou le segment précédent ou suivant
- modifier les coordonnées X/Y de l'ancre sélectionnée
- ajouter, insérer ou supprimer des ancres tout en préservant un nombre minimal valide d'ancres
- ajouter ou supprimer des segments explicites, basculer les segments sélectionnés entre ligne et bézier, ou reconstruire les segments séquentiels pour l'agencement sélectionné

Le viewport prend en charge la sélection directe et le glissement d'ancres. La liste d'agencements et l'inspecteur reflètent la même sélection, et la section JSON peut toujours importer ou exporter le document sous-jacent pour révision ou contrôle de version.

Utilisez **Validate** avant d'appliquer des modifications complexes. Utilisez **Apply** uniquement après avoir sélectionné ou créé l'actor cible, car l'application modifie l'état éditable de spline/agencement de l'actor.

## Génération

Utilisez :

- **Build Now** / `BuildTrack` : génération synchrone complète.
- **Rebuild** / `RebuildTrack` : asynchrone si `bUseAsyncBuild` est vrai, sinon synchrone.
- **Cancel** / `CancelAsyncBuild` : annule une génération asynchrone active ou en attente.

L'actor se régénère à partir d'un plan calculé `FTrackBuildPlan`. Le plan détermine les plages de segments, le nombre de pièces, l'état des dénivelés, les interruptions de saut, le maillage de route sélectionné et le nombre de maillages supplémentaires avant le début de la génération.

## Génération asynchrone

Paramètres :

- `bUseAsyncBuild` : active la génération par lots.
- `SegmentsPerTick` : nombre d'éléments générés de route/maillage supplémentaire traités par tick.
- `bAutoRebuildOnConstruction` : planifie les régénérations lors des modifications de construction.

Les mondes de l'éditeur temporisent les modifications de construction avant d'effacer ou de préparer les composants générés, ce qui permet de conserver la géométrie de spline existante éditable pendant que vous faites glisser des points. Les mondes runtime utilisent une pompe à minuterie au tick suivant. Les deux chemins appellent le même générateur au niveau des éléments, de sorte que le comportement reste aligné sans laisser un long segment de spline monopoliser une image.

## Données par segment

`TrackSplineData` configure chaque segment. S'il y a moins d'entrées que de segments de spline, l'index `0` est utilisé par défaut.

Champs importants :

- `RoadMesh` : maillage de route spécifique au segment optionnel.
- `MeshInstances` : nombre exact de pièces de maillage pour le segment.
- `RoadMeshLength` : longueur souhaitée de la pièce de route.
- `SegmentLength` : espacement de secours lorsque `RoadMeshLength` n'est pas défini.
- `ExtraMeshStart`, `ExtraMesh`, `ExtraMeshEnd` : maillages de spline supplémentaires.
- `ExtraMeshOffset` : décalages latéraux pour les emplacements de maillages supplémentaires.
- `GroundWallSettings` : comportement des murs de tènement par segment.

## Maillages supplémentaires

Les maillages supplémentaires suivent le même intervalle d'éléments de spline que la pièce de route. Ils sont utiles pour les glissières, trottoirs, clôtures et objets décoratifs latéraux.

Les tableaux de début, milieu et fin permettent d'utiliser des maillages différents aux limites de segments. Les maillages supplémentaires sont étiquetés avec `AsyncSplineBuilder.ExtraMesh`, et non `AsyncSplineBuilder.RoadMesh`.

## Interruptions (Gaps)

Ajoutez des entrées dans `JumpGapsByPoints` pour neutraliser la génération de route et de maillages supplémentaires pour des plages d'indices de points.

Les plages sont des plages de segments :

```text
[StartPointIndex, EndPointIndex)
```

Par exemple, `StartPointIndex = 2`, `EndPointIndex = 4` neutralise les segments `2` et `3`.

## Dénivelés (Drops)

Ajoutez des entrées dans `StuntDropsByPoints` pour déplacer des plages de segments vers le bas ou vers un Z absolu dans le monde.

Champs :

- `DropHeight` : décalage relatif en Z. Les valeurs négatives déplacent la route vers le bas.
- `bUseConstantGapHeight` : utilise un Z absolu dans le monde au lieu d'un décalage.
- `ConstantGapWorldZ` : hauteur absolue lorsque cette option est activée.

Si deux segments adjacents sans interruption se rencontrent à des hauteurs différentes, l'actor crée un mur de dénivelé entre eux.

## Murs de tènement

Activez `bGenerateGroundWalls` pour générer des bandes de mur procédurales s'étendant depuis le bord de la route vers le bas.

Murs de tènement :

- Utilisent la largeur de route déduite du maillage ou remplacée.
- Respectent les paramètres de mur par segment.
- Séparent les bandes au niveau des interruptions de saut et des échantillons invalides.
- Peuvent être à simple ou double face.
- Utilisent des UV basés sur la distance et la hauteur réelle du mur.

Voir [LandscapeAndWalls.md](LandscapeAndWalls.md) pour la configuration détaillée.

## Alignement sur le paysage

Alignement de maillages :

- `bSnapMeshesToLandscape`
- `ObjectsToHitForLandscapeLineTrace`
- `LineTraceLength`

Alignement de points :

- `bSnapPointsToLandscape`
- `bTangentPointsUpdate`

Utilisez `ActorsToIgnoreForGenerationTraces` pour exclure les maillages d'aide ou objets temporaires des requêtes de tracé.

## Déformation du paysage

La déformation réservée à l'éditeur s'exécute avec `DeformLandscapeNow`.

Exigences :

- `Landscape` assigné.
- Une spline valide.
- Valeurs cohérentes pour `FallOff` et `NumberOfSubdivisionsForDeform`.
- `bRaiseHeights` et/ou `bLowerHeights` activés.

Hauteur : `DeformLandscapeNow` ou panneau **Deform Height**. Peinture de couche : assignez `PaintLayer`, ajustez `PaintHalfWidth` / `PaintFallOff` dans le panneau, puis `PaintLandscapeLayerNow` ou panneau **Paint Layer**. La peinture est additive ; elle n'efface pas les bandes plus larges précédentes lorsque vous réduisez l'atténuation. `PaintFallOff = 0` produit un bord net. Si les informations de couche sélectionnées utilisent `bNoWeightBlend`, le panneau/la validation avertit que la réduction des autres couches du paysage sous la route n'est pas garantie.

## Quand utiliser le panneau Details

Le panneau de flux de travail est volontairement épuré. Utilisez le panneau Details lorsque vous devez modifier :

- les tableaux `ExtraMeshStart`, `ExtraMesh`, `ExtraMeshEnd` et `ExtraMeshOffset` par segment
- les paramètres détaillés `FGroundWallSettings`, y compris les remplacements de tracé, UV, matériau, collision et largeur
- les tableaux d'objets de tracé pour l'alignement sur le paysage et la génération de murs
- les champs de lecture/écriture des assets de données de points de spline
- les paramètres avancés de débogage et de construction

## Connecteurs d'agencement

L'onglet Build comprend une section **Layout Connectors** pour les métadonnées de parcours passives. Un connecteur relie un agencement/distance source à un agencement/distance cible et stocke une nature sémantique telle que `PitEntry`, `PitExit`, `Link` ou `ServiceAccess`. Vous pouvez également saisir une nature personnalisée ; les natures personnalisées non vides sont validées sous forme d'avertissements plutôt que d'erreurs.

Utilisez **Pit Entry** pour ajouter un connecteur par défaut depuis `Main` vers le premier agencement de stands. Utilisez **Pit Exit** pour ajouter un connecteur par défaut depuis le premier agencement de stands vers `Main`. **Validate** dans cette section exécute une validation réservée aux connecteurs.

Les modifications de connecteurs ne régénèrent pas la route et ne suppriment pas la géométrie générée. Elles ne créent pas non plus de maillages de transition automatiques, ne coupent pas les splines, n'étendent pas la déformation du terrain aux voies des stands et n'activent pas de rendu spécial pour les voies des stands.

Activez **Show Connector Debug** pour placer des marqueurs textuels visuels uniquement aux extrémités de connecteurs valides. Un marqueur identifie l'index et le type de connecteur, s'il s'agit de l'extrémité `From` ou `To`, son identifiant d'agencement et sa distance. Chaque extrémité est résolue indépendamment, de sorte qu'une extrémité valide peut rester visible si l'autre est invalide. Les agencements manquants et les distances hors plage d'une spline sont ignorés ; utilisez **Validate** pour inspecter ces problèmes.

Les marqueurs utilisent des sorties de débogage `UTextRenderComponent` et n'ajoutent pas de géométrie de route, de maillage supplémentaire, de mur de tènement ou de mur de dénivelé. L'édition des connecteurs rafraîchit les marqueurs tant que la case est cochée. Désactivez **Show Connector Debug** pour supprimer uniquement les étiquettes de connecteurs. Le basculement ou le rafraîchissement de ces étiquettes ne régénère pas la piste, ne modifie pas le nombre de composants de route, n'étend pas le comportement du terrain et n'affecte pas la porte de validation de génération.

## Flux de travail d'asset de données

Assignez un `USplinePointListAsset` à `SplinePointList`.

Utilisez :

- `WriteSplineToDataAsset` : sauvegarde les points de spline actuels.
- `ReadSplineFromDataAsset` : charge les points de spline.

Ceci est utile pour conserver les agencements de pistes séparément des composants générés.

## Flux de travail de production recommandé

1. Construisez une courte spline de test.
2. Validez les limites de maillages de route et la répétition.
3. Ajoutez les données par segment.
4. Ajoutez les maillages supplémentaires.
5. Ajoutez les interruptions et dénivelés.
6. Configurez le tracé des murs de tènement.
7. Exécutez la déformation du paysage seulement une fois la forme de la route stabilisée.
8. Exécutez les tests d'automatisation avant la publication.
9. Testez le niveau en PIE et en version runtime empaquetée.

## Ce que le plugin ne fait pas

- Il ne fournit pas de modes de peinture de paysage de remplacement/effacement ou par segment.
- Il ne crée pas de maillages pour vous.
- Il ne garantit pas des accotements de terrain parfaits sur tous les paysages.
- Il ne génère pas automatiquement de maillages de route de transition pour les connecteurs.
- Il ne remplace pas la direction artistique manuelle pour la finition finale de la piste.

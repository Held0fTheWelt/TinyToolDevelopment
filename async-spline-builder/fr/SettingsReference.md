<!-- doc-provenance: product-facts.yml reconciled 2026-07-15; source AKDB:plugins/AsyncSplineBuilder/architecture.md -->
# Référence des paramètres

Cette référence décrit les paramètres dont la plupart des utilisateurs ont besoin lors de la configuration d'un `ASplineGeneratingActor`.

## Mappage du panneau de flux de travail

Ouvrez **Tools > Track Tools > Async Spline Builder** pour accéder à l'interface axée sur les tâches. Le panneau est divisé en onglets **Build**, **Segments** et **Terrain**. Il couvre la sélection d'actor, la configuration des maillages, la validation, les commandes de génération et régénération, le traitement par lots asynchrone, l'état de boucle fermée, les étiquettes de débogage, les assistants de lignes de segments, les interruptions de saut, les dénivelés, l'assignation de paysage, les paramètres de peinture de couche, la déformation de hauteur, les interrupteurs d'alignement et les murs de tènement au niveau de l'actor.

Utilisez cette référence lorsqu'un paramètre n'est exposé que dans le panneau Details ou lorsque vous avez besoin du comportement exact d'un champ. Les tableaux de maillages supplémentaires par segment, les paramètres détaillés de murs de tènement, les tableaux d'objets de tracé, les drapeaux de collision, les contrôles UV et les champs d'assets de données restent des paramètres avancés du panneau Details.

## Configuration des maillages

### StartMesh

Maillage optionnel utilisé pour la première pièce de route générée sur une piste ouverte. S'il n'est pas défini, le maillage de route du segment sélectionné est utilisé.

### MainMesh

Maillage de route de secours obligatoire. La validation bloque la génération lorsqu'il est absent.

### EndMesh

Maillage optionnel utilisé pour la dernière pièce de route générée sur une piste ouverte. S'il n'est pas défini, le maillage de route du segment sélectionné est utilisé.

## TrackTools

### bEditSpline

Lorsque cette option est activée, les composants générés sont effacés et seule l'édition de spline/débogage reste active pendant la construction. Utilisez ceci pour façonner la spline sans reconstruire les maillages.

### bShowSegmentNumbers / bShowPointNumbers

Crée des composants texte de débogage pour les indices de segments ou de points. Ils sont étiquetés et nettoyés avec les autres composants générés.

### bShowLayoutConnectorDebug

Booléen, valeur par défaut `false`. La case à cocher **Show Connector Debug** dans la section **Layout Connectors** du panneau contrôle ce même paramètre. Lorsqu'elle est activée, l'éditeur affiche un marqueur textuel pour chaque extrémité de connecteur résoluble indépendamment. Chaque étiquette inclut l'index et le type de connecteur, le rôle `From` ou `To`, l'identifiant d'agencement et la distance configurée ; sa taille suit `DebugTextWorldSize`.

Les agencements manquants et les distances hors plage sont ignorés au lieu d'être affichés à une position erronée. Le basculement ou le rafraîchissement des étiquettes de connecteurs est purement visuel : cela ne régénère pas la piste, ne crée pas de géométrie de route de connecteur, ne modifie pas le nombre de routes générées et n'étend pas le comportement du terrain. La désactivation du paramètre supprime uniquement les étiquettes de connecteurs.

### bShowSplineVisualizationWidth / SplineVisualizationWidth

Contrôle la largeur de visualisation de la spline dans l'éditeur.

### bSnapPointsToLandscape

Déplace les points de spline sur les impacts de tracé. Nécessite `ObjectsToHitForLandscapeLineTrace`.

### bTangentPointsUpdate

Met à jour les tangentes après l'alignement des points sur le paysage.

### bMirrorExtraMesh

Applique un effet miroir aux maillages supplémentaires en inversant leur échelle X.

### SplinePointType

Le type de point de spline appliqué lors des mises à jour de spline. `CurveCustomTangent` est un bon choix par défaut pour les routes.

### SplineZOffset

Applique un décalage vertical au composant spline.

### TrackSplineData

Données par segment. Si aucune entrée n'existe pour un segment, l'entrée `0` sert de secours.

### AdditionalLayouts

Enregistrements de parcours optionnels pour voies des stands, itinéraires alternatifs, routes de service et splines décoratives. La spline d'actor héritée reste la façade de l'agencement `Main`.

### LayoutConnectors

Liens sémantiques passifs entre deux distances d'agencement. Chaque connecteur stocke :

- `FromLayoutId` / `FromDistance`
- `ToLayoutId` / `ToDistance`
- `ConnectorKind`

Les natures connues sont `PitEntry`, `PitExit`, `Link` et `ServiceAccess`. `ConnectorKind` reste un `FName` ouvert ; les natures personnalisées non vides sont autorisées et validées sous forme d'avertissements. Une nature vide, des agencements manquants, de mauvaises distances et des extrémités très proches sur un même agencement sont des erreurs de portée connecteur signalées par la validation de connecteur, mais les erreurs de connecteur ne bloquent pas les régénérations de géométrie.

Les lignes de connecteurs ne génèrent pas de maillages de transition, ne se régénèrent pas automatiquement et ne modifient pas le comportement de déformation du terrain.

## TrackSplineData

### RoadMesh

Maillage de route optionnel pour le segment. Se rabat sur `MainMesh`.

### MeshInstances

Nombre exact de pièces de route dans le segment. Lorsqu'il est supérieur à zéro, il remplace le nombre automatique basé sur la longueur.

### SegmentLength

Espacement de secours lorsque `RoadMeshLength` n'est pas défini. Les valeurs supérieures à `1` sont utilisées.

### RoadMeshLength

Longueur souhaitée de couverture du maillages de route. Utilisez ceci lorsque les limites du maillages ne correspondent pas à la longueur visuelle répétée.

### ExtraMeshStart / ExtraMesh / ExtraMeshEnd

Tableaux optionnels de maillages supplémentaires pour la première pièce, les pièces centrales et la dernière pièce.

### ExtraMeshOffset

Décalage latéral par emplacement de maillage supplémentaire.

### GroundWallSettings

Paramètres de génération de mur, tracé, largeur, collision et UV par segment.

## Options

### bClosedLoop

Relie le dernier point de spline au premier.

### bEnableCollision

Active la collision pour la route générée et les composants de mur procéduraux.

### bCastShadow / bCastContactShadow

Contrôle les drapeaux d'ombre des maillages de spline générés.

### bMirrorMesh

Applique un effet miroir à l'échelle du maillages de route.

### bSnapMeshesToLandscape

Aligne les extrémités des maillages de route générés et des maillages supplémentaires sur les impacts de tracé. Nécessite des types d'objets de tracé.

## Landscape

### Landscape

Proxy de paysage utilisé par la déformation réservée à l'éditeur.

### ActorsToIgnoreForGenerationTraces

Actors ignorés par les tracés d'alignement et de mur.

### bSnapTraceLandscapeOnly

Si vrai, les tracés d'alignement n'acceptent que les impacts sur le paysage.

### ObjectsToHitForLandscapeLineTrace

Types d'objets utilisés par l'alignement de maillages et de points. Requis lorsque l'alignement est activé.

### FallOff

Distance à l'extérieur de la largeur de la route sur laquelle la déformation de hauteur se fond progressivement dans le terrain existant.

### NumberOfSubdivisionsForDeform

Résolution d'échantillonnage de la spline pour la déformation du paysage. Des valeurs plus élevées peuvent améliorer l'ajustement mais augmentent le coût.

### bRaiseHeights / bLowerHeights

Contrôle si la déformation peut élever et/ou abaisser les échantillons de paysage.

### PaintHalfWidth

Demi-largeur à plein poids pour la peinture de couche (cm). `0` utilise la demi-largeur de route à chaque échantillon de déformation.

### PaintFallOff

Distance d'atténuation progressive (smoothstep) pour la peinture de couche (cm). Indépendante du `FallOff` de hauteur. `0` donne un bord net sans bande douce à l'extérieur de `PaintHalfWidth`.

### PaintLayer

`ULandscapeLayerInfoObject` peint le long de la route par `PaintLandscapeLayerNow` / panneau **Paint Layer**. Doit être enregistré sur le paysage cible. Si les informations de couche utilisent `bNoWeightBlend`, la couche cible peut toujours recevoir de la peinture, mais il n'est pas garanti que les autres couches de matériau soient réduites sous la route.

### LandscapeEditLayerName

Nom de la couche de modification utilisée pour les altérations de hauteur de paysage lorsque la configuration du paysage la prend en charge.

### LineTraceLength

Profondeur de tracé pour l'alignement sur le paysage.

## Async Build

### bUseAsyncBuild

Active les régénérations par lots.

### SegmentsPerTick

Nombre d'unités de travail asynchrones traitées par tick. Une unité de travail correspond à une pièce de route ou de maillage supplémentaire générée, de sorte qu'un long segment de spline comprenant de nombreuses pièces soit réparti sur plusieurs ticks. Commencez bas pour la réactivité et augmentez après test.

### bAutoRebuildOnConstruction

Planifie les régénérations après les modifications de construction.

## Ground Walls

### bGenerateGroundWalls

Active la génération de murs de tènement procéduraux.

### GroundWallSubdivisions

Nombre d'échantillons de mur le long de la spline. Des valeurs plus élevées produisent des murs plus lisses et plus de géométrie.

### GroundWallOutset

Décalage horizontal supplémentaire au-delà de la demi-largeur de route déduite.

### GroundWallFallbackDepth

Profondeur utilisée lorsqu'un tracé de mur échoue.

### bGroundWallsDoubleSided

Ajoute des triangles inverses pour que les murs soient rendus des deux côtés.

### GroundWallObjectsToHitForLineTrace

Types d'objets de tracé par défaut pour les murs de tènement lorsque les paramètres de tracé par segment sont vides.

## GroundWallSettings

### bGenerateGroundWalls

Activation du mur par segment.

### bGenerateBothSides

Si faux, le côté gauche est neutralisé pour ce segment.

### TrackHalfWidth

Remplacement manuel de la demi-largeur. Laissez `0` pour déduire la largeur à partir des limites du maillages de route sélectionné.

### MinWallHeight / MaxWallHeight

Ignore les murs minuscules et limite les très grands murs.

### bCreateCollision

Contrôle la collision du mur procédural, également contrôlée par l'actor `bEnableCollision`.

### TraceSettings

Types d'objets de tracé, longueur de tracé et complexité de tracé par segment.

### UVSettings

Répétition UV et inversions du mur par segment.

## Drop Walls

### DropWallMaterial

Matériau appliqué aux murs de dénivelé générés.

### DropWallUVWorldUnitsU / DropWallUVWorldUnitsV

Répétition UV en unités du monde pour les murs de dénivelé.

## Configuration de base recommandée

- `bUseAsyncBuild = true`
- `SegmentsPerTick = 24`
- `bAutoRebuildOnConstruction = true`
- `MainMesh` assigné
- `RoadMeshLength = 0` sauf si les limites du maillages sont erronées
- `TrackHalfWidth = 0` sauf si les limites du maillages sont erronées
- Types d'objets de tracé des murs de tènement configurés avant d'activer les murs
- Déformation du paysage exécutée manuellement une fois la forme de la route stabilisée

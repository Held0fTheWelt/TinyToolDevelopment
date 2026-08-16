<!-- doc-provenance: AKDB:plugins/ProceduralGeneratedStructures/architecture.md; docs/architecture/plugins/ProceduralGeneratedStructures/product-facts.yml; reconciled 2026-06-21 -->
# Référence des paramètres

Chaque propriété accessible à l'utilisateur et champ d'asset de données, avec son objectif.

## `AAsyncProceduralGeneratedActor`

| Propriété | Catégorie | Type | Objectif |
| --- | --- | --- | --- |
| `InstancesPerFrame` | Procedural\|Performance | int32 (min 1) | Instances ajoutées par tick sur l'ensemble des tâches de génération lorsque la génération asynchrone est activée. |
| `bAutoBuildOnConstruction` | Procedural\|Build | bool | Déclenche une génération pendant `OnConstruction`. |
| `bUseAsyncBuild` | Procedural\|Build | bool | Répartit la génération sur plusieurs images (non bloquant) ; sinon génère en une seule passe. |
| `bCenterGeneratedTransforms` | Procedural\|Build | bool | Centre les transformations de **rangées générées** autour de l'origine XY locale. Les instances explicites capturées ne sont jamais recentrées. |
| `ProceduralStructure` | Procedural | `UProceduralStructureDataAsset` | Source de données définissant ce qui est construit. |
| `ReadInComponentConfiguration` | Procedural | tableau de `FInstancedComponentConfiguration` | Associe les `UInstancedStaticMeshComponent` de la scène → entrées d'asset de données (lecture). |
| `ComponentConfiguration` | Procedural | tableau de `FInstancedComponentConfiguration` | Associe les entrées d'asset de données → composants sur cet actor (régénération). |
| `bClearProceduralStructureInformation` | Procedural\|Debug | bool | Efface les données `ProceduralStructure` (déclencheur éditeur). |
| `bReadInMeshComponentData` | Procedural\|Debug | bool | Lit les instances de composants de la scène dans l'asset de données (déclencheur éditeur). |
| `EstimatedBuildInstanceCount` | Procedural\|Debug | int64 | Nombre estimé d'instances pour la régénération actuelle ou la plus récente. |
| `AddedBuildInstanceCount` | Procedural\|Debug | int64 | Instances ajoutées par la régénération actuelle ou la plus récente. |

### Fonctions d'aide de l'actor

| Fonction | Objectif |
| --- | --- |
| `GetBuildPlan` | Aperçu non mutatif avec composants cibles, problèmes bloquants, intention de mutation et nombre d'instances exact après élagage. |
| `GetEstimatedBuildInstanceCount` | Renvoie le nombre estimé d'instances pour la génération actuelle ou la plus récente. |
| `GetAddedBuildInstanceCount` | Renvoie le nombre d'instances ajoutées par la génération actuelle ou la plus récente. |
| `GetBuildProgress` | Renvoie la progression de la génération de `0.0` à `1.0` lorsqu'une estimation est disponible. |

## `FInstancedComponentConfiguration`

| Champ | Type | Objectif |
| --- | --- | --- |
| `Name` | FName | Nom du composant de maillages instancié sur l'actor. |
| `StructureType` | `EStructureType` | Classification de structure pour l'association. |

## `EStructureType`

`None`, `Structure`, `Railing`, `Tribune`, `Stairs`.

## `UProceduralStructureDataAsset` → `FInstancedMeshInformation`

| Champ | Type | Objectif |
| --- | --- | --- |
| `Name` | FName | Nom de l'entrée (correspond à une configuration de composant). |
| `Type` | `EStructureType` | Classification de structure. |
| `Mesh` | `UStaticMesh` | Maillage utilisé pour les instances. |
| `Instances` | tableau de `FTransform` | Transformations explicites, rejouées à l'identique. |
| `InstancedMeshRows` | tableau de `FInstancedMeshRowInformation` | Règles de génération de rangées procédurales. |

### Fonctions d'aide de DataAsset

| Fonction | Objectif |
| --- | --- |
| `GetElementStats` | Renvoie `FProceduralStructureElementStats` pour une entrée nommée. |
| `GetAllElementStats` | Renvoie les statistiques pour chaque entrée. |
| `GetTotalExplicitInstanceCount` | Compte les instances explicites capturées dans toutes les entrées. |
| `GetTotalPotentialGeneratedInstanceCount` | Compte la capacité de rangées générées avant élagage. |
| `GetTotalGeneratedInstanceCount` | Compte les instances de rangées générées après élagage. |
| `GetTotalInstanceCount` | Compte les instances explicites plus les instances générées après élagage. |

## `FProceduralStructureBuildPlan`

| Champ | Type | Objectif |
| --- | --- | --- |
| `bHasDataAsset` / `bHasComponentConfiguration` / `bHasInstancedComponents` | bool | Drapeaux de préparation de haut niveau. |
| `ConfiguredComponentCount` / `AvailableInstancedComponentCount` | int32 | Nombre d'associations et nombre de composants ISM appartenant à l'actor découverts. |
| `MutatingComponentCount` | int32 | Composants qui seraient effacés et régénérés. |
| `InstanceAddingComponentCount` | int32 | Composants qui recevraient una ou plusieurs instances. |
| `TotalExplicitInstanceCount` | int64 | Instances explicites capturées dans les entrées générables. |
| `TotalPotentialGeneratedInstanceCount` | int64 | Capacité de rangées générées avant élagage. |
| `TotalGeneratedInstanceCount` | int64 | Instances de rangées générées après élagage. |
| `TotalInstanceCount` | int64 | Instances explicites plus instances générées après élagage. |
| `Entries` | tableau de `FProceduralStructureBuildPlanEntry` | Entrées d'aperçu par composant configuré. |
| `Issues` | tableau de string | Codes de problèmes bloquants. |

## `FProceduralStructureElementStats`

| Champ | Type | Objectif |
| --- | --- | --- |
| `Name` / `Type` / `Mesh` / `bHasMesh` | mixte | Identité et préparation de maillage pour une entrée d'asset de données. |
| `ExplicitInstanceCount` | int32 | Nombre de transformations explicites capturées. |
| `RowRuleCount` | int32 | Nombre de règles de génération de rangées. |
| `PotentialGeneratedInstanceCount` | int64 | Capacité de rangées avant élagage. |
| `GeneratedInstanceCount` | int64 | Nombre exact généré après élagage. |
| `TotalInstanceCount` | int64 | Nombre d'instances explicites plus instances générées après élagage. |

## `FInstancedMeshRowInformation` (génération de rangées)

| Champ | Type | Objectif |
| --- | --- | --- |
| `Transform` | FTransform | Transformation de base pour la rangée. |
| `RowCount_FirstDimension` / `_SecondDimension` / `_ThirdDimension` | int32 (min 0) | Nombre d'instances par dimension. |
| `Movement_First_Dimension` / `_Second_Dimension` / `_Third_Dimension` | FTransform | Transformation pas à pas appliquée le long de chaque dimension. |
| `MovementAdjustmentByRotation_First_Dimension` | FVector | Ajustement de déplacement appliqué par rotation le long de la première dimension. |
| `DefinedSecondDimension` | tableau de FVector | Placements explicites dans la deuxième dimension. |
| `PrunedInstances` / `PrunedFirstDimension` / `PrunedSecondDimension` / `PrunedThirdDimension` / `PrunedSecondDimensionInThirdDimension` | tableaux | Indices/instances à ignorer pendant la génération. |
| `bApplyRowCountAdjust` | bool | Appliquer l'ajustement du nombre de rangées. |
| `bUseDefinedPlacementMethod` | bool | Utiliser le placement `DefinedSecondDimension` au lieu du déplacement pas à pas. |

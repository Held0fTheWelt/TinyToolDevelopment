<!-- doc-provenance: AKDB:plugins/ProceduralGeneratedStructures/architecture.md; docs/architecture/plugins/ProceduralGeneratedStructures/product-facts.yml; reconciled 2026-06-21 -->
# Manuel utilisateur

Ce manuel explique comment utiliser Procedural Generated Structures dans l'éditeur Unreal.

## Objectif

Procedural Generated Structures génère des structures de maillages statiques instanciés réutilisables à partir d'un asset de données.
L'actor en runtime peut lire des instances existantes de `UInstancedStaticMeshComponent` dans un `UProceduralStructureDataAsset`, puis régénérer ces instances explicites ou générer des structures supplémentaires basées sur des rangées.

## Objets principaux

- **`AAsyncProceduralGeneratedActor`** — possède le flux de travail de génération et peut régénérer les composants de manière synchrone ou sur plusieurs ticks d'éditeur/jeu.
- **`UProceduralStructureDataAsset`** — stocke les entrées de maillage nommées (`FInstancedMeshInformation`) avec des transformations explicites et des règles optionnelles de génération de rangées.
- **`FInstancedComponentConfiguration`** — associe un composant de maillage instancié nommé sur l'actor à une entrée stockée dans l'asset de données (`Name` + `StructureType`).
- **`FProceduralStructureBuildPlan`** — indique ce qu'effectuerait une régénération : composants cibles, problèmes bloquants, intention de mutation, comptages asynchrones et totaux d'instances exacts après élagage.
- **`FProceduralStructureElementStats`** — indique le nombre d'instances explicites, générées, potentiellement générées et totales par entrée.
- **`EStructureType`** — `None`, `Structure`, `Railing`, `Tribune`, `Stairs`.

## Flux de travail

1. Ajoutez un `AAsyncProceduralGeneratedActor` à un niveau ou un blueprint.
2. Ajoutez un ou plusieurs composants enfants `UInstancedStaticMeshComponent` avec des **noms de composants stables**.
3. Assignez un `UProceduralStructureDataAsset` à **ProceduralStructure**.
4. Configurez **ReadInComponentConfiguration** pour capturer les instances de composants existantes dans l'asset (déclencher avec **bReadInMeshComponentData**).
5. Configurez **ComponentConfiguration** pour régénérer ces entrées sur les composants.
6. Inspectez **GetBuildPlan** (Blueprint/C++) ou la route d'aperçu si vous utilisez l'automatisation. Corrigez tout problème signalé avant d'appliquer une régénération.
7. Utilisez **bClearProceduralStructureInformation** (effacer), **bReadInMeshComponentData** (lire) et la génération (construction / asynchrone) pour itérer sur la structure.

## Notes de génération

- Les transformations explicites lues depuis les composants de scène sont **rejouées à l'identique** et ne sont pas recentrées lors de la régénération.
- Les transformations de rangées générées peuvent être centrées autour de l'origine XY locale avec **bCenterGeneratedTransforms**.
- **InstancesPerFrame** limite le nombre d'instances ajoutées par tick lorsque la génération asynchrone est activée.
- Le nombre de rangées est limité à des valeurs non négatives avant la génération.
- Les plans de génération et les statistiques d'assets de données indiquent à la fois la capacité de rangées non élaguées et le nombre exact généré après élagage, permettant d'estimer les régénérations importantes avant toute mutation.
- **bAutoBuildOnConstruction** déclenche une génération pendant `OnConstruction` (similaire à l'actor de spline).
- **bUseAsyncBuild** répartit la génération sur plusieurs images ; sinon la génération s'effectue en une seule passe.
- **GetBuildProgress**, **GetEstimatedBuildInstanceCount** et **GetAddedBuildInstanceCount** rapportent la progression de la génération asynchrone pour les outils d'éditeur et les Blueprints.

## Plan de génération et validation

`AAsyncProceduralGeneratedActor::GetBuildPlan` est un aperçu non mutatif. Utilisez-le avant de régénérer des structures volumineuses ou partagées.

Le plan de génération indique :

- Si un asset de données, una configuration de composant et des composants de maillage instancié appartenant à l'actor existent.
- Une entrée par composant configuré, incluant le chemin du composant, le chemin du maillage, les statistiques d'élément DataAsset, l'intention de mutation et les codes de problèmes bloquants.
- Les totaux pour les instances explicites, les instances potentiellement générées avant élagage, les instances générées après élagage et le nombre d'instances combiné.

Les codes de problèmes bloquants courants incluent :

- `missing_procedural_structure_data_asset`
- `missing_component_configuration`
- `actor_has_no_instanced_static_mesh_components`
- `component_not_found:<Name>`
- `data_asset_element_not_found:<Name>`
- `data_asset_element_missing_mesh:<Name>`
- `data_asset_element_type_none:<Name>`

## Entrées d'asset de données

Chaque entrée `FInstancedMeshInformation` contient :

- `Name`, `Type` (`EStructureType`), `Mesh` (`UStaticMesh`).
- `Instances` — transformations explicites (par ex. capturées depuis la scène), rejouées telles quelles.
- `InstancedMeshRows` — règles optionnelles de génération de rangées procédurales (nombre de rangées par dimension, transformations de déplacement par dimension, options d'élagage/placement défini). Voir [SettingsReference.md](SettingsReference.md) pour chaque champ.

## Ce que le plugin ne fait pas

- Il ne crée pas de maillages statiques pour vous — vous fournissez les vôtres.
- Il ne recentre pas les instances capturées explicitement.
- Ce n'est pas un système complet de modélisation procédurale ; il place et régénère des maillages instanciés à partir de données.

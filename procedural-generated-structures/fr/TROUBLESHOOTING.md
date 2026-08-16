<!-- doc-provenance: AKDB:plugins/ProceduralGeneratedStructures/architecture.md; docs/architecture/plugins/ProceduralGeneratedStructures/product-facts.yml; reconciled 2026-06-21 -->
# Dépannage

## J'ai activé le plugin mais rien ne se produit

Le plugin ajoute la classe `AAsyncProceduralGeneratedActor` et l'asset `UProceduralStructureDataAsset`.
Placez l'actor dans un niveau (Place Actors → *Async Procedural Generated Actor*) ; il n'y a pas de menu —
le flux de travail réside dans le panneau Details de l'actor.

## La génération ne produit aucune instance

- Confirmez que l'actor possède au moins un composant enfant `UInstancedStaticMeshComponent` avec un **nom stable**.
- Confirmez que **ComponentConfiguration** contient une entrée dont le **Name** correspond à ce composant.
- Confirmez qu'un **Mesh** valide est assigné à l'entrée de l'asset de données.
- Si vous utilisez la lecture, assurez-vous d'avoir capturé au préalable (**bReadInMeshComponentData**) avec une entrée **ReadInComponentConfiguration** correspondante.
- Inspectez **GetBuildPlan**. Il rapporte des codes de problème précis tels que `component_not_found:<Name>`, `data_asset_element_not_found:<Name>` et `data_asset_element_missing_mesh:<Name>`.

## L'aperçu indique un nombre très élevé d'instances

Le plan de génération indique à la fois les instances potentiellement générées avant élagage et le nombre exact généré après élagage. Si les deux sont trop élevés, réduisez le nombre de rangées, ajoutez de l'élagage, ou activez **bUseAsyncBuild** et réduisez **InstancesPerFrame**.

## Les instances capturées se sont déplacées/recentrées de manière inattendue

Les instances explicites capturées sont rejouées à l'identique et ne sont jamais recentrées. Seules les transformations des **rangées générées** sont affectées par **bCenterGeneratedTransforms**.

## La génération fait saccader l'éditeur / le jeu sur les grandes structures

Activez **bUseAsyncBuild** et réduisez **InstancesPerFrame** afin que les instances soient ajoutées sur plusieurs ticks au lieu d'une passe unique bloquante.

## La lecture a capturé le mauvais composant

`ReadInComponentConfiguration` effectue la correspondance sur le **Name** du composant. S'assurer que les noms de composants sont stables et uniques, et que le `Name` de l'entrée de configuration correspond exactement.

## La grille générée présente des trous

Vérifiez les tableaux `Pruned*` dans les informations de rangée — les indices/instances élagués sont intentionnellement ignorés. Effacez-les pour générer une grille complète.

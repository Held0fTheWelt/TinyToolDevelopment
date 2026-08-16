<!-- doc-provenance: AKDB:plugins/ProceduralGeneratedStructures/architecture.md; docs/architecture/plugins/ProceduralGeneratedStructures/product-facts.yml; reconciled 2026-06-21 -->
# Documentation de ProceduralGeneratedStructures

ProceduralGeneratedStructures génère des structures de maillages statiques instanciés réutilisables à partir d'un asset de données. L'actor en runtime peut lire des instances existantes de `UInstancedStaticMeshComponent` dans un `UProceduralStructureDataAsset`, puis régénérer ces instances explicites ou générer des structures supplémentaires basées sur des rangées. Il expose également des données de plan de génération et de statistiques afin que vous puissiez inspecter les composants cibles, les problèmes bloquants, l'intention de mutation, la progression asynchrone et le nombre exact d'instances après élagage avant d'appliquer une régénération.

## Documentation

- [QUICKSTART.md](QUICKSTART.md) : installer → placer l'actor → capturer et régénérer, avec les résultats attendus.
- [UserManual.md](UserManual.md) : flux de travail complet, objets principaux et notes de génération.
- [SettingsReference.md](SettingsReference.md) : chaque propriété d'actor et champ d'asset de données.
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md) · [FAQ.md](FAQ.md)
- [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md) : déclaration de logiciels tiers (aucun regroupé).

## Assets principaux

- `AAsyncProceduralGeneratedActor` possède le flux de travail de génération et peut régénérer les composants de manière synchrone ou sur plusieurs ticks d'éditeur/jeu.
- `UProceduralStructureDataAsset` stocke les entrées de maillage nommées avec des transformations explicites et des règles optionnelles de génération de rangées.
- `FInstancedComponentConfiguration` associe un composant de maillage instancié nommé sur l'actor à une entrée stockée dans l'asset de données.
- `FProceduralStructureBuildPlan` et `FProceduralStructureElementStats` exposent des données d'aperçu exactes pour les outils, les Blueprints et les routes UCM.

## Notes de génération

- Les transformations explicites lues depuis les composants de scène sont rejouées à l'identique et ne sont pas recentrées lors de la régénération.
- Les transformations de rangées générées peuvent être centrées autour de l'origine XY locale avec `bCenterGeneratedTransforms`.
- `InstancesPerFrame` limite le nombre d'instances ajoutées par tick lorsque la génération asynchrone est activée.
- Le nombre de rangées est limité à des valeurs non négatives avant la génération.
- Les plans de génération indiquent la capacité de rangées générées avant élagage et le nombre exact d'instances générées après élagage.

## Flux de travail recommandé

1. Ajoutez un `AAsyncProceduralGeneratedActor` à un niveau ou un blueprint.
2. Ajoutez un ou plusieurs composants enfants `UInstancedStaticMeshComponent` avec des noms de composants stables.
3. Assignez un `UProceduralStructureDataAsset`.
4. Configurez `ReadInComponentConfiguration` pour capturer les instances de composants existantes.
5. Configurez `ComponentConfiguration` pour régénérer ces entrées.
6. Inspectez `GetBuildPlan` ou la route d'aperçu, puis utilisez les actions de lecture, d'effacement et de génération appelables dans l'éditeur pour itérer sur la structure.

<!-- doc-provenance: AKDB:plugins/ProceduralGeneratedStructures/architecture.md; docs/architecture/plugins/ProceduralGeneratedStructures/product-facts.yml; reconciled 2026-06-21 -->
# Guide de démarrage rapide

Ce guide vous accompagne de l'installation jusqu'à un **résultat visible** : un `AAsyncProceduralGeneratedActor` qui régénère des structures de maillages instanciés à partir d'un asset de données. Le plugin fonctionne de manière autonome — aucun autre plugin n'est requis.

## Ce que vous obtiendrez après ce guide

Un actor dans votre niveau dont les instances de maillage statique instancié sont capturées dans un asset de données et régénérées à partir de celui-ci, rendant la structure réutilisable et régénérable.

## Prérequis

- Éditeur Unreal Engine 5 et un niveau ouvert.
- Un `UStaticMesh` de votre projet à instancier (par ex. un maillage de mur ou de pilier).
- Aucun logiciel tiers, compte ou runtime. Voir [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md).

## 1. Installer et activer

1. Ajoutez **ProceduralGeneratedStructures** depuis votre bibliothèque Fab au projet (ou installez-le dans le moteur).
2. Ouvrez **Edit → Plugins**, activez **ProceduralGeneratedStructures** et redémarrez quand demandé.

## 2. Placer l'actor (Premier résultat)

1. Dans le panneau **Place Actors**, recherchez **Async Procedural Generated Actor** et glissez-le dans le niveau (ou ajoutez `AAsyncProceduralGeneratedActor` depuis la liste des classes).
2. Ajoutez un ou plusieurs composants enfants **Instanced Static Mesh Component** à l'actor et donnez à chacun un **nom de composant stable** (par ex. `Walls`). Assignez votre maillage statique et placez quelques instances.

## 3. Un exemple pratique : capturer et régénérer

1. Créez un **Procedural Structure Data Asset** (`UProceduralStructureDataAsset`) dans le Content Browser et assignez-le à la propriété **ProceduralStructure** de l'actor.
2. Dans **ReadInComponentConfiguration**, ajoutez une entrée dont le **Name** correspond à votre composant (`Walls`) et choisissez un **StructureType** (par ex. `Structure`).
3. Activez **bReadInMeshComponentData** pour capturer les instances actuelles du composant dans l'asset de données.
4. Dans **ComponentConfiguration**, ajoutez une entrée associant le même **Name** (`Walls`) à l'entrée de l'asset de données.
5. Affichez un aperçu avec **GetBuildPlan** depuis Blueprint/C++ ou la route d'aperçu automatisée. Un plan propre ne comporte aucun problème bloquant et indique le total exact d'instances qui seront régénérées.
6. Régénérer — activez **bAutoBuildOnConstruction** (régénère lors de la construction) ou déplacez/modifiez l'actor pour déclencher une génération.

**Résultat attendu :** les maillages instanciés sont régénérés à partir de l'asset de données. Les transformations explicites capturées sont rejouées à l'identique (jamais recentrées). Pour itérer, activez **bClearProceduralStructureInformation** pour effacer les données stockées et capturez à nouveau.

## 4. Performance / Asynchrone

- **bUseAsyncBuild** : répartit la génération sur plusieurs images au lieu d'une passe unique bloquante.
- **InstancesPerFrame** : nombre d'instances ajoutées par tick lorsque la génération asynchrone est activée.
- **GetBuildProgress** / **GetAddedBuildInstanceCount** : suit la progression de la génération asynchrone pour les outils.
- **bCenterGeneratedTransforms** : centre les transformations de *rangées générées* autour de l'origine XY locale (les instances explicites capturées ne sont jamais recentrées).

## 5. Générer des structures basées sur des rangées (Optionnel)

Au-delà de la réexécution des instances capturées, une entrée d'asset de données peut définir des **InstancedMeshRows** pour générer des grilles/rangées de manière procédurale (nombre de rangées par dimension avec transformations de déplacement par dimension). Voir [SettingsReference.md](SettingsReference.md) pour chaque champ.

## 6. Étapes suivantes

- Flux de travail complet et notes de génération : [UserManual.md](UserManual.md).
- Chaque propriété d'actor et champ d'asset de données : [SettingsReference.md](SettingsReference.md).
- Problèmes : [TROUBLESHOOTING.md](TROUBLESHOOTING.md) et [FAQ.md](FAQ.md).

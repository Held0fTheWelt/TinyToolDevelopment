<!-- doc-provenance: AKDB:plugins/ProceduralGeneratedStructures/architecture.md; docs/architecture/plugins/ProceduralGeneratedStructures/product-facts.yml; reconciled 2026-06-21 -->
# FAQ

**Ce plugin nécessite-t-il un autre plugin ?**
Non. Il fonctionne de manière totalement autonome.

**Inclus-t-il des maillages ?**
Non. Vous fournissez vos propres assets `UStaticMesh` ; le plugin les instancie.

**Quelles versions du moteur sont prises en charge ?**
Unreal Engine 5.4+ (Win64, Linux, Mac). Le module est Runtime, donc l'actor fonctionne dans l'éditeur et dans les jeux empaquetés.

**Regroupe-t-il des logiciels tiers, Python ou des modèles d'IA ?**
Non. Voir [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md).

**Quelle est la différence entre instances explicites et génération de rangées ?**
Les instances explicites sont des transformations exactes (souvent capturées depuis des composants existants) et rejouées telles quelles. La génération de rangées crée procéduralement des instances à partir du nombre de rangées et des transformations de déplacement par dimension définies sur l'asset de données.

**Puis-je générer au runtime, pas seulement dans l'éditeur ?**
Oui. L'actor est compatible au runtime et peut générer de manière synchrone ou sur plusieurs ticks (`bUseAsyncBuild`).

**Comment éviter les saccades d'images sur les grandes structures ?**
Activez `bUseAsyncBuild` et ajustez `InstancesPerFrame`.

**Puis-je prévisualiser le résultat d'une régénération avant de modifier les composants ?**
Oui. Utilisez `GetBuildPlan` ou la route d'aperçu de régénération. Le plan indique les composants cibles, les problèmes bloquants, l'intention de mutation et le nombre d'instances exact après élagage.

**Les outils peuvent-ils afficher la progression de la génération asynchrone ?**
Oui. `GetEstimatedBuildInstanceCount`, `GetAddedBuildInstanceCount` et `GetBuildProgress` exposent la progression pour les outils d'éditeur, les Blueprints et les routes d'automatisation.

**Où puis-je signaler des problèmes ou obtenir du support ?**
Utilisez le lien de support sur la page du produit Fab.

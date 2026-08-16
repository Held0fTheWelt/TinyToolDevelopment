<!-- doc-provenance: AKDB:plugins/SmartContentDiet/architecture.md; docs/architecture/plugins/SmartContentDiet/product-facts.yml; reconciled 2026-07-16 -->
# FAQ

**Smart Content Diet nécessite-t-il une IA, un compte ou un autre plugin ?**
Non. La boucle principale (analyser → examiner → appliquer les correctifs sûrs → réanalyser → mesurer) s'exécute entièrement dans l'éditeur sans service d'IA, compte ou plugin pair. Des routes d'écosystème optionnelles via **Unreal Capability Mesh (UCM)** existent mais ne sont jamais requises.

**Est-il sans danger à exécuter ?**
L'analyse et la prévisualisation sont en lecture seule. L'application de corrections/réductions/déplacements/suppressions **modifie les assets du projet** — ne le faites que dans un espace de travail sauvegardé, sous contrôle de source et jetable. Les routes modificatives sont soumises à approbation par défaut. À utiliser à vos propres risques.

**Quelles versions de l'engine sont prises en charge ?**
Unreal Engine 5.4+. C'est un plugin pour l'éditeur.

**Quelle est la différence entre les analyses Quick Safe, Full et Deep ?**
Quick Safe utilise uniquement le registre/métadonnées (aucun chargement d'assets, rapide). Full charge les assets pour des résultats exploitables sur maillages/textures/matériaux. Deep ajoute des métriques approfondies sur matériaux/maillages statiques et est le plus lent.

**Pourquoi ne puis-je pas voir les onglets Préréglage ou Gouvernance ?**
Ce sont des onglets avancés (Ingénieur / Producteur). Changez de rôle dans les Paramètres ou dans l'en-tête.

**Puis-je l'exécuter en CI / sans interface ?**
Oui. Un commandlet prend en charge `-QuickSafe` / `-FullScan` / `-DeepScan`, `-OptimizationQueueReport` et `-ApplySafeQueue` (application uniquement sur projets sauvegardés).

**Intègre-t-il des logiciels tiers ?**
Non. Voir [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md).

**Où puis-je obtenir de l'aide ?**
Utilisez le lien de support sur la page du produit Fab.

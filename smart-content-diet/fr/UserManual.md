<!-- doc-provenance: AKDB:plugins/SmartContentDiet/architecture.md; docs/architecture/plugins/SmartContentDiet/product-facts.yml; reconciled 2026-07-16 -->
# Manuel de l'utilisateur

Ce manuel résume le workflow de l'éditeur Smart Content Diet et renvoie vers les guides détaillés.

## Point d'entrée

Ouvrez **Tools → Content Tools → Smart Content Diet**. La fenêtre est un shell adapté aux rôles.

## Rôles et onglets

Définissez le rôle (Débutant / Ingénieur / Producteur) et le niveau d'explication dans les **Paramètres** ou dans le sélecteur de public de l'en-tête. La visibilité des onglets dépend du rôle :

| Onglet | Débutant | Avancé (Ingénieur / Producteur) |
| --- | --- | --- |
| Aperçu, Optimiser, Résultats, Paramètres | ✓ | ✓ |
| Préréglage | — | ✓ |
| Gouvernance (Tendance, Dette, Budget, Propriété, Analyse approfondie) | — | ✓ |
| Redondance | — | ✓ (uniquement avec un fournisseur de similarité externe) |

## Profondeurs d'analyse

Choisissez dans l'en-tête : **Quick Safe** (registre/métadonnées, aucun chargement d'assets), **Full** (charge les assets), **Deep** (métriques approfondies sur matériaux/maillages ; Gouvernance → Analyse approfondie). Chaque exécution d'analyseur respecte la profondeur sélectionnée ; le commandlet respecte `-QuickSafe` / `-FullScan` / `-DeepScan`.

Les analyses larges utilisent un pipeline privilégiant AssetRegistry. SCD rassemble les candidats une fois, lit les métadonnées légères de textures/matériaux à partir des balises lorsque c'est possible, compare d'abord sur la base des balises, et ne charge en profondeur que l'ensemble des candidats survivants nécessitant des données d'objets. L'étape de comparaison en lecture seule peut s'exécuter en parallèle ; les QuickFixes modificatifs nécessitent toujours une action explicite de l'utilisateur ou du commandlet.

Les chemins de doublons et d'alpha partagent du code utilitaire entre les résultats d'analyse et les réductions. Les vérifications d'alpha de textures/matériaux utilisent la même logique d'opacité d'instance de matériau, et les sorties anticipées de réduction utilisent des clés de doublons alignées sur la réduction, de sorte qu'une consolidation sûre n'est pas ignorée simplement parce que l'index d'analyse plus strict n'a pas regroupé les assets.

## Workflow principal — Boucle d'optimisation sécurisée (sans IA)

1. Ouvrez l'outil.
2. Choisissez la profondeur d'analyse (Quick Safe / Full / Deep).
3. Lancez l'analyse depuis l'en-tête.
4. Examinez **Aperçu**, puis **Optimiser → File d'attente d'optimisation sûre**.
5. **Aperçu sécurisé** → Sauvegarde / contrôle de source → **Appliquer en toute sécurité**.
6. Le shell réanalyse automatiquement après une application réussie ou une correction d'asset unique.
7. Comparez le nombre d'éléments en file d'attente et le delta ; les rapports JSON sont enregistrés sous `Saved/SmartContentDiet/OptimizationQueue/<timestamp>/`.

## Workflow d'analyse général

1. Lancez une analyse (sélection, dossier ou étendue du projet).
2. Examinez les résultats par gravité, impact, dimension et chaîne d'explicabilité.
3. Utilisez **Préréglage** (avancé) pour voir comment les poids d'évaluation affectent les scores.
4. Utilisez **Gouvernance** (avancé) pour la tendance, la dette, le budget, la propriété et l'analyse approfondie optionnelle.
5. N'appliquez les QuickFixes qu'après avoir confirmé la sauvegarde/le contrôle de source.
6. Réanalysez et validez dans le contexte du projet cible.

## Sécurité

Les actions modificatives changent les assets du projet et sont soumises à une approbation par défaut. Exécutez-les uniquement dans un espace de travail sauvegardé, sous contrôle de source et jetable. Voir la note de sécurité dans [QUICKSTART.md](QUICKSTART.md).

## Tâches de l'éditeur et UCM

Les travaux récents de l'éditeur sont enregistrés sous forme d'historique de tâches pour les analyses, les validations et les actions d'optimisation. Lorsque Unreal Capability Mesh est activé, SCD expose des routes de tâches en lecture seule :

```text
scd.editor.jobs.list.v1
scd.editor.jobs.status.v1
```

Unified MCP Server peut agréger ces routes via `jobs_list` / `jobs_status` ; SCD lui-même ne dépend pas d'UMCP.

## Guides détaillés

- Shell de l'éditeur, onglets, résultats, QuickFixes, gouvernance : [../Resources/UI_AND_BEHAVIOR.md](../Resources/UI_AND_BEHAVIOR.md).
- File d'attente d'optimisation sûre (compartiments, règles de sécurité, schéma de rapport) : [../Resources/OPTIMIZATION_QUEUE.md](../Resources/OPTIMIZATION_QUEUE.md).
- Architecture : [../Resources/SMART_ANALYSIS_ARCHITECTURE.md](../Resources/SMART_ANALYSIS_ARCHITECTURE.md).

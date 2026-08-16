<!-- doc-provenance: AKDB:plugins/SmartContentDiet/architecture.md; docs/architecture/plugins/SmartContentDiet/product-facts.yml; reconciled 2026-07-16 -->
# Documentation de SmartContentDiet

SmartContentDiet analyse les assets de projet Unreal Engine, explique les résultats d'optimisation en contexte, expose des vues de gouvernance et propose des workflows validés de QuickFix et de réduction. La boucle produit par défaut est **analyser → examiner → appliquer les correctifs sûrs → réanalyser → mesurer l'amélioration** — sans nécessiter d'IA ni d'outils externes.

## Avis de sécurité

SmartContentDiet peut modifier les assets du projet lors de l'application de QuickFixes, de réductions de maillages, de modifications de textures/matériaux, de déplacements/suppressions lors de la révision d'assets, de mises à jour de référence ou d'écritures de gouvernance. Utilisez-le uniquement dans une branche ou un espace de travail sauvegardé, sous contrôle de source et jetable. Ne l'exécutez jamais sur du code source non protégé. À utiliser à vos propres risques.

La fonctionnalité est mise en œuvre avec soin dans le cadre de son périmètre énoncé, mais elle ne remplace pas les sauvegardes, le contrôle de source, la révision de code/contenu ni la validation spécifique au projet.

## Carte de la documentation

| Document | Public | Contenu |
|----------|--------|---------|
| [UI_AND_BEHAVIOR.md](../Resources/UI_AND_BEHAVIOR.md) | Artistes, artistes techniques, producteurs | Shell de l'éditeur, onglets, workflow d'analyse, résultats, QuickFixes, gouvernance |
| [OPTIMIZATION_QUEUE.md](../Resources/OPTIMIZATION_QUEUE.md) | Tous les utilisateurs de l'éditeur | File d'attente d'optimisation sûre, compartiments, appliquer/prévisualiser, delta avant/après |
| [SMART_ANALYSIS_ARCHITECTURE.md](../Resources/SMART_ANALYSIS_ARCHITECTURE.md) | Ingénieurs, intégrateurs | Analyseurs, préréglages, impact, réduction, tendance, architecture de gouvernance |
| [DIMENSION_INTEGRATION_STATUS.md](../Resources/DIMENSION_INTEGRATION_STATUS.md) | Ingénieurs | FindingType, mappage de dimensions, convertisseur, état d'intégration UI |
| [SmartAnalysisResult_Usage.md](../Resources/SmartAnalysisResult_Usage.md) | Ingénieurs | Utilisation du modèle de résultat, métadonnées de correction automatique |
| [CHANGELOG.md](../CHANGELOG.md) | Opérateurs de version | Historique des versions |

**Nouveau ici ?** Commencez par [QUICKSTART.md](QUICKSTART.md) pour l'installation et la boucle sécurisée analyse→correction.

## Package pour Engine installé

Utilisez un package BuildPlugin Smart Content Diet produit pour la version installée de l'engine. Le package conserve les fichiers binaires générés et les métadonnées de précompilation requises par les builds installés. Ne supprimez pas ces fichiers lors de la copie ou de l'archivage du plugin.

> **Pour les mainteneurs :** le gate de publication SCD et les documents de publication/runbook se trouvent dans le dépôt de développement et ne font **pas** partie du package Fab ; vous n'en avez pas besoin pour installer ou utiliser SCD.

## Point d'entrée de l'éditeur

Ouvrez **Tools → Content Tools → Smart Content Diet**.

### Shell adapté aux rôles

La fenêtre principale utilise les paramètres de public (Débutant / Ingénieur / Producteur) pour contrôler la profondeur des explications et les onglets visibles.

| Onglet | Débutant | Avancé (Ingénieur / Producteur + mode avancé) |
|-----|----------|--------------------------------------------------|
| Aperçu | ✓ | ✓ |
| Optimiser | ✓ | ✓ |
| Résultats | ✓ | ✓ |
| Préréglage | — | ✓ |
| Gouvernance | — | ✓ (Tendance, Dette, Budget, Propriété, Analyse approfondie en sous-onglets) |
| Redondance | — | ✓ uniquement lorsqu'un fournisseur de similarité externe est enregistré |
| Paramètres | ✓ | ✓ |

Modifiez le rôle et le niveau d'explication dans **Paramètres** ou via le sélecteur de public dans l'en-tête.

### Profondeurs d'analyse (en-tête)

| Profondeur | Charge les assets ? | Utilisation typique |
|-------|---------------|-------------|
| **Quick Safe** (par défaut) | Non — chemin registre/métadonnées | Premier passage, rapide « que puis-je améliorer en toute sécurité ? » |
| **Full** | Oui — pipeline d'analyseur complet | Résultats exploitables sur les maillages/textures/matériaux |
| **Deep** | Oui — inclut des métriques approfondies sur les matériaux/maillages statiques | Le plus lent ; statistiques de shaders et travail approfondi |

La boîte combinée de l'en-tête met à jour le libellé du bouton d'analyse principal (`Quick Safe Scan` / `Full Scan` / `Deep Scan`) et affiche un conseil de profondeur sous les commandes.

La profondeur sélectionnée est respectée par **chaque** exécution d'analyseur : les analyses de l'éditeur (Résultats / Gouvernance → Lancer l'analyse) la transmettent à `FSmartAnalysisOrchestrator`, et la ligne d'état de gouvernance nomme la profondeur utilisée. **Commandlet et CI** respectent `-QuickSafe`, `-FullScan` et `-DeepScan` comme auparavant. Les métriques approfondies de matériaux/maillages utilisent en outre le workflow Governance Deep Scan (`Governance → Deep Scan`), identiquement au commandlet.

## Workflows rapides

### Routes de l'écosystème UCM

Lorsque Unreal Capability Mesh (UCM) est activé, SmartContentDiet peut être utilisé via des routes déclarées dans la configuration plutôt que via des ponts de fournisseurs directs. SCD ne lie jamais un plugin pair et n'en liste aucun dans `required_plugin_names` ou `Build.cs` ; la valeur inter-plugins provient des routes JSON, non des dépendances de code. Le profil de projet actif expose **12 capacités SCD** :

| Capacité | Type | Politique |
| --- | --- | --- |
| `scd.migration.advice_from_handoff` | conseil | lecture seule |
| `scd.scan.run` | fournisseur | lecture seule |
| `scd.findings.get` | fournisseur | lecture seule |
| `scd.findings.explain` | fournisseur | lecture seule |
| `scd.health.snapshot` | fournisseur | lecture seule |
| `scd.health.evidence` | fournisseur | lecture seule |
| `scd.governance.snapshot` | fournisseur | lecture seule |
| `scd.similarity.groups` | similarité | lecture seule |
| `scd.similarity.ingest_groups` | similarité | lecture seule |
| `scd.optimize.preview_safe` | optimisation | lecture seule |
| `scd.optimize.apply_safe` | optimisation | **modificatif — requiert une approbation** |
| `scd.optimize.apply_fix` | optimisation | **modificatif — requiert une approbation** |

**Contrat de dégradation.** Chaque capacité renvoie l'enveloppe partagée `smart_content_diet.capability_mesh_endpoint.v1` (`status` valant `ok`/`degraded`/`error`). Les capacités réduisent leur fonctionnement plutôt que d'échouer lorsqu'une précondition est manquante : les routes d'optimisation/résultats renvoient une enveloppe `error` vous demandant d'exécuter d'abord `scd.scan.run` ; `scd.optimize.apply_fix` renvoie une enveloppe `degraded` (sans mutation) lorsqu'une correction destructive est demandée sans `allow_destructive: true`. La connexion de SCD à un pair n'est jamais présumée — une route qui référence un autre plugin (par ex. l'exemple `scd_ingest_from_iis.v1`, `iis.search.hybrid → scd.similarity.ingest_groups`) est signalée par la découverte UCM comme *disponible mais plugin non chargé* lorsque ce pair est absent, tandis que chaque capacité réservée à SCD reste *disponible*.

**Gate d'approbation (et Option 3).** Les deux routes modificatives portent `requires_user_approval: true`, de sorte qu'UCM les bloque avec `ApprovalRequired` jusqu'à ce qu'un humain approuve l'exécution — aucun asset n'est touché avant cela. Les opérateurs qui souhaitent une application sécurisée non surveillée peuvent modifier la politique de route pour supprimer l'exigence d'approbation (Option 3) ; la version livrée est protégée par approbation.

Les workflows de placement PRS restent des routes UCM appartenant à PRS. Les ponts gratuits restent disponibles uniquement pour les équipes sans UCM et comme implémentations de référence pour les adaptateurs directs ; ils ne sont pas requis dans le projet principal.

### Boucle d'optimisation sécurisée autonome (sans IA)

### Exactitude et performances de l'analyse

Le chemin d'analyseur actuel privilégie AssetRegistry. Il construit l'ensemble des candidats une fois, lit les métadonnées de balises avant de charger les assets, parallélise le travail de comparaison en lecture seule et ne charge en profondeur que les candidats finaux. Un cache de métadonnées par asset avec invalidation par horodatage/version évite de répéter le travail inchangé.

L'analyse des doublons et de l'alpha partage des utilitaires avec le moteur de réduction. Les sorties anticipées de réduction utilisent des clés de doublons alignées sur la réduction (`DuplicateTextureReduction`, `DuplicateStaticMeshReduction`) afin que les vérifications de consolidation sécurisées correspondent à la logique d'empreinte utilisée par le réducteur réel. Les heuristiques d'alpha de texture sont centralisées dans `SCDMaterialAlpha` pour maintenir l'alignement entre l'analyseur et la réduction.

L'historique des tâches de l'éditeur est disponible via les routes UCM (`scd.editor.jobs.list.v1`, `scd.editor.jobs.status.v1`) pour l'agrégation UMCP sans ajouter de dépendance UMCP à SCD.

1. Ouvrez Smart Content Diet.
2. Laissez la profondeur d'analyse sur **Quick Safe** ou choisissez **Full** / **Deep**.
3. Lancez l'analyse depuis l'en-tête.
4. Examinez **Aperçu**, puis ouvrez **Optimiser** → File d'attente d'optimisation sûre.
5. **Aperçu sécurisé** → **Appliquer en toute sécurité** (sauvegarde / contrôle de source d'abord).
6. Après une application réussie ou une correction d'asset unique depuis les détails de **Résultats**, le shell effectue automatiquement une nouvelle analyse.
7. Comparez le nombre d'éléments en file d'attente et le résumé delta dans le panneau Optimiser ; les rapports d'application JSON sont enregistrés sous `Saved/SmartContentDiet/OptimizationQueue/<timestamp>/`.

Consultez [OPTIMIZATION_QUEUE.md](../Resources/OPTIMIZATION_QUEUE.md) pour les définitions de compartiments, les règles de sécurité et le schéma de rapport.

### Workflow d'analyse général

1. Lancez une analyse (sélection, dossier ou étendue du projet).
2. Examinez les résultats par gravité, impact, dimension et chaîne d'explicabilité.
3. Utilisez **Préréglage** (avancé) pour comprendre comment les poids d'évaluation affectent les scores.
4. Utilisez **Gouvernance** (avancé) pour la tendance, la dette, le budget, la propriété et l'analyse approfondie optionnelle.
5. N'appliquez les QuickFixes qu'après avoir confirmé la sauvegarde/le contrôle de source.
6. Réanalysez et validez dans le contexte du projet cible.

## Commandlet (CI / sans interface)

```powershell
UnrealEditor-Cmd.exe "<Project>.uproject" -run=SmartContentDiet `
  -QuickSafe -OptimizationQueueReport -Path=/Game -Limit=50 `
  -NoFail -unattended -nop4 -nosplash
```

Appliquer les lignes de file d'attente sécurisées (projet sauvegardé uniquement) :

```powershell
UnrealEditor-Cmd.exe "<Project>.uproject" -run=SmartContentDiet `
  -QuickSafe -ApplySafeQueue -OptimizationQueueReport -Path=/Game `
  -NoFail -unattended -nop4 -nosplash
```

| Option | Effet |
|--------|-------|
| `-QuickSafe` | Analyse du registre/dépendances ; ne charge pas d'assets |
| `-FullScan` | Charge les assets et exécute les analyseurs (par défaut si `-QuickSafe` est absent) |
| `-DeepScan` | Profondeur la plus lente ; métriques approfondies sur matériaux/maillages |
| `-OptimizationQueueReport` | Écrit la file d'attente au format JSON/Markdown (auto-activé avec `-QuickSafe`) |
| `-ApplySafeQueue` | Applique uniquement les lignes **Safe Now** ; les lignes destructives sont rejetées |
| `-Path=/Game/...` | Étendue de l'analyse |
| `-NoFail` | Sortie 0 même en cas d'avertissements de politique (à utiliser avec précaution en CI) |

Le commandlet affiche l'avertissement de sécurité lors de l'utilisation et au démarrage de l'exécution. Les mises à jour de référence et les écritures de rapports sont des opérations qui modifient l'espace de travail.

## Emplacements des artefacts (gitignored)

| Artefact | Chemin |
|----------|--------|
| Rapport d'application de la file d'optimisation | `Saved/SmartContentDiet/OptimizationQueue/<timestamp>/apply_report.json` |
| Rapport de file d'attente du commandlet | `-ReportDir` / par défaut sous `Saved/SmartContentDiet/` |
| Sortie de validation de publication | `Saved/SCDValidation/` lors de l'exécution de la validation par le mainteneur |

## Périmètre des QuickFixes implémentés (résumé)

SmartContentDiet propose des QuickFixes révisés couvrant les textures, les maillages statiques/squelettiques, les matériaux, les animations, l'hygiène audio/VFX ainsi que la révision/consolidation d'assets. Les actions destructives ou inter-assets nécessitent une confirmation explicite et ne sont pas sécurisées par traitement par lots par défaut.

Catalogue complet : [UI_AND_BEHAVIOR.md § Optimization Packs](../Resources/UI_AND_BEHAVIOR.md#71-optimization-packs).

## Validation de version

La validation de version est un workflow réservé aux mainteneurs. L'utilisation par l'acheteur ne nécessite pas de scripts de contrôle locaux, de modules de test de projet hôte ni de chemins spécifiques au dépôt.

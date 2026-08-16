<!-- doc-provenance: AKDB:plugins/SmartContentDiet/architecture.md; docs/architecture/plugins/SmartContentDiet/product-facts.yml; reconciled 2026-07-16 -->
# Référence des paramètres

## Rôle / Public

Défini dans les **Paramètres** ou dans le sélecteur de public de l'en-tête. Contrôle la profondeur d'explication et la visibilité des onglets :

- **Débutant** — Aperçu, Optimiser, Résultats, Paramètres.
- **Ingenieur / Producteur (avancé)** — ajoute Préréglage et Gouvernance (Tendance, Dette, Budget, Propriété, Analyse approfondie) ; Redondance n'apparaît que lorsqu'un fournisseur de similarité externe est enregistré.

## Profondeur d'analyse (en-tête)

| Profondeur | Charge les assets ? | Remarques |
| --- | --- | --- |
| `Quick Safe` (par défaut) | Non | Chemin registre/métadonnées ; premier passage rapide. |
| `Full` | Oui | Pipeline d'analyseur complet ; résultats exploitables sur maillages/textures/matériaux. |
| `Deep` | Oui | Métriques approfondies sur matériaux/maillages statiques ; utilise Gouvernance → Analyse approfondie ; le plus lent. |

La profondeur sélectionnée est respectée par chaque exécution d'analyseur (éditeur et commandlet).

Quick Safe est le chemin privilégiant AssetRegistry : les analyses larges évitent de charger lourdement les assets sauf si un candidat passe les vérifications de métadonnées légères. Full et Deep peuvent charger des assets pour des détails d'analyseur exploitables.

## Emplacements de sortie

```text
Saved/SmartContentDiet/OptimizationQueue/<timestamp>/   ← rapports d'application de la file d'attente sécurisée
```

## Approbation / Sécurité

Les capacités modificatives (`scd.optimize.apply_safe`, `scd.optimize.apply_fix`) sont **soumises à approbation par défaut**. Les corrections destructives nécessitent un `allow_destructive: true` explicite. N'exécutez des mutations que dans un espace de travail sauvegardé, sous contrôle de source et jetable.

## Commandlet (CI / sans interface)

Options : `-QuickSafe`, `-FullScan`, `-DeepScan`, `-OptimizationQueueReport`, `-ApplySafeQueue`, `-Path=`, `-Limit=`, `-NoFail`, ainsi que les options standard `-unattended -nop4 -nosplash`. Les options d'application ne doivent cibler que des projets sauvegardés.

## Routes d'écosystème optionnelles

Lorsque **Unreal Capability Mesh (UCM)** est activé, SCD expose des capacités de fournisseur en lecture seule et deux routes d'optimisation modificatives soumises à approbation via des routes UCM déclarées en JSON. SCD ne lie jamais un plugin pair dans le code ; cette intégration est entièrement optionnelle. Voir l'index de la [documentation](README.md) et [../Resources/SMART_ANALYSIS_ARCHITECTURE.md](../Resources/SMART_ANALYSIS_ARCHITECTURE.md).

SCD expose également des routes de tâches de l'éditeur en lecture seule (`scd.editor.jobs.list.v1`, `scd.editor.jobs.status.v1`) pour l'agrégation UMCP via UCM.

Pour des paramètres plus approfondis sur les analyseurs/préréglages/gouvernance, voir [../Resources/SMART_ANALYSIS_ARCHITECTURE.md](../Resources/SMART_ANALYSIS_ARCHITECTURE.md).

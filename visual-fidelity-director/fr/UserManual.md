<!-- doc-provenance: AKDB:plugins/VisualFidelityDirector/architecture.md; docs/architecture/plugins/VisualFidelityDirector/product-facts.yml; reconciled 2026-07-12 -->
# Manuel de l'utilisateur

Visual Fidelity Director est un outil local pour Unreal Editor. La version `2.0.0` se concentre sur un cockpit centré sur les profils tout en conservant le panneau Expert Tools 1.x intégré pour les workflows de snapshots et de recettes.

## Ouvrir l'outil

Utilisez **Tiny Tools > Visual Fidelity Director**.

L'onglet ancrable propose les pages **Cockpit**, **Evidence** et **Expert Tools**.

Optionnel : **Édition > Editor Configurations > Visual Fidelity Director Editor Settings** ouvre les préférences de l'éditeur de plugins (raccourci de menu désactivable dans les paramètres).

## Page Cockpit

### Bannière d'état

Affiche le titre de disponibilité et le texte détaillé de compilation du profil actif et de l'état de validation.

### Carte d'action

| Action | Résultat attendu |
| --- | --- |
| **Refresh** | Recharge les profils, recompile l'aperçu du profil actif, redémarre l'échantillonnage des métriques multi-images et rafraîchit les bandes d'axes. |
| **Compile Preview** | Recompile les cibles de paramètres souhaitées pour le profil actif sans écrire de configuration. |
| **Open Reports** | Ouvre le dossier local des rapports VFD dans le navigateur de fichiers du système d'exploitation. |

### Barre de profils

Sélectionnez le profil de fidélité actif. La barre affiche l'état de validation et les profils connus chargés depuis `Saved/VisualFidelityDirector/profiles/`.

### Barre de métriques

Affiche les métriques de l'éditeur en direct multi-images (image, thread de jeu, thread de rendu, GPU, goulot d'étranglement et part de coût par axe lorsque disponible). Les valeurs de `-1` ou les chaînes indisponibles explicites signifient que la mesure n'est pas disponible dans le contexte actuel de l'éditeur — VFD ne fabrique jamais de chiffres.

### Bandes d'axes

Chaque bande d'axe de composition comprend :

- le libellé de l'axe et la couleur de disponibilité ;
- la boîte combinée **Variant** (les variantes indisponibles restent visibles mais désactivées avec la preuve de compatibilité) ;
- le curseur **Intent** (`0.00`–`1.00`) ;
- la mise en évidence de sélection pour le tiroir de détails de l'axe actif.

### Tiroir de détails de l'axe

Pour l'axe sélectionné :

- **Chemin d'héritage** — chaîne ordonnée de l'ancêtre racine au profil actif ;
- **Provenance** — lignes au niveau des champs pour les paramètres compilés (destination, valeur, source) ;
- **Résultats** — résultats de compilation et de compatibilité locaux à la commande.

### Carte de comparaison de profils

Choisissez un second profil et inspectez les différences par axe de l'état souhaité compilé. Utilise le même moteur de comparaison que la bibliothèque Blueprint.

### Tiroir d'application gouvernée

| Action | Résultat attendu |
| --- | --- |
| **Build Destinations** | Résumés en lecture seule pour les destinations Scalability, renderer ini et Device Profiles. |
| **Apply Approved** | Écrit uniquement les destinations cochées et approuvées par l'utilisateur via sauvegarde → écriture → vérification → manifeste de restauration. |
| **Rollback** | Restaure les derniers fichiers sauvegardés depuis le manifeste de restauration. |

Les destinations bloquées (assets, matériaux, MRQ, accessibilité, axes de révision uniquement) n'apparaissent jamais comme cibles inscriptibles.

## Page Evidence

Affiche onze blocs de preuves à voies fixes (Lumen et autres voies de révision) avec les mappages d'axes déclarés, la confiance et les limites de révision manuelle. Cette page est en lecture seule.

## Page Expert Tools

Le panneau de commande 1.x intégré pour les workflows hérités :

### Intent Mixer

Chaque curseur accepte `0.00` à `1.00` et n'affecte l'évaluation à blanc de la recette que jusqu'à ce que vous exportiez ou appliquiez.

| Curseur | Signification |
| --- | --- |
| Image Stability | Préfère des détails sous-pixel plus calmes et moins de scintillement. |
| Motion Clarity | Préfère moins d'étalement/image fantôme dans le contenu en mouvement. |
| Fine Detail Preservation | Préfère des détails apparents plus nets. |
| Specular Calmness | Préfère moins de scintillement dans les reflets/zones brillantes. |
| UI Crispness | Préfère la clarté HUD/UMG. |
| Cinematic Accumulation | Préfère l'accumulation d'échantillons de rendu final. |
| Performance Headroom | Préfère des recommandations moins coûteuses. |

### Recettes intégrées

Les mêmes quinze ID de recettes intégrées que la version `1.0.0` (voir [SettingsReference.md](SettingsReference.md)).

### Actions des Expert Tools

| Action | Résultat attendu |
| --- | --- |
| Export Snapshot (Expert Tools) | `quality_snapshot.json/.md` plus les dernières copies. |
| Export Recipe Dry Run (Expert Tools) | `recipe_evaluation.json` et `settings_diff.md` ; aucune mutation. |
| Duplicate Recipe | JSON appartenant au projet sous `Saved/VisualFidelityDirector/recipes/`. |
| Import Recipe | Met à jour la recette active et les curseurs à partir du JSON importé. |
| Export Scanner Report | `visual_quality_report.json/.md`. |
| Lumen Deep Scan (Expert Tools) | Résultats de métadonnées du cache de surface Lumen ; aucune mutation de maillage/matériau. |
| Preview Apply + Rollback (Expert Tools) | Aperçu CVar de session avec restauration ; `visual_fidelity_apply_report.*`. |
| Export A/B Report | `comparison_report.json/.md`. |
| Export Cinematic Report | `cinematic_quality_report.*` et `mrq_recommendation.md`. |
| Validate Schemas | `schema_validation_report.*`. |
| Export Diagnostics | `experimental_diagnostics_report.*`. |
| Productization Report | `productization_readiness_report.*`. |
| Open Output Folder | Ouvre la racine des rapports. |

## Bibliothèque Blueprint

`UVFDCockpitBlueprintLibrary` expose les mêmes services headless que le cockpit :

- charger, résoudre, valider et compiler des profils de fidélité ;
- comparer des profils ;
- détecter les capacités du pipeline ;
- construire l'état des preuves ;
- prévisualiser, appliquer et restaurer des configurations permanentes gouvernées.

Showcase empaqueté : `Content/Blueprints/BPF_VFD_API`.

## Modèle de sécurité

- L'examen du cockpit, les preuves, la comparaison et l'aperçu des destinations sont en lecture seule.
- L'application permanente gouvernée est le seul chemin de mutation du cockpit et nécessite une approbation explicite par destination.
- L'aperçu d'application des Expert Tools reste limité aux CVars de session avec restauration.
- Les assets, matériaux, Post Process Volumes, préréglages MRQ et paramètres d'accessibilité ne sont pas modifiés par VFD.

## Rapports et profils

```text
Saved/VisualFidelityDirector/profiles/
Saved/VisualFidelityDirector/reports/
Saved/VisualFidelityDirector/recipes/
```

Traitez les sorties comme locales/privées car elles peuvent contenir des noms de projets, des valeurs CVar et des directions de qualité.

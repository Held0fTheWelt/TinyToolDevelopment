<!-- doc-provenance: AKDB:plugins/VisualFidelityDirector/architecture.md; docs/architecture/plugins/VisualFidelityDirector/product-facts.yml; reconciled 2026-07-12 -->
# Référence des paramètres

VFD ajoute des paramètres de plugin d'éditeur sous **Édition > Editor Configurations > Visual Fidelity Director Editor Settings**. Les paramètres de rendu du projet ne sont modifiés que par une application permanente gouvernée ou un aperçu de session des Expert Tools.

## Commandes du Cockpit

| Commande | Valeurs | Effet |
| --- | --- | --- |
| Sélecteur de profils | Profils connus de `Saved/VisualFidelityDirector/profiles/` | Définit le profil de fidélité actif pour la compilation, les preuves et la comparaison. |
| Boîte combinée variante d'axe | Variantes de pipeline par axe | Sélectionne la variante active ; les options indisponibles restent visibles avec la preuve de compatibilité. |
| Curseur d'intention d'axe | `0.00`–`1.00` | Ajuste le niveau d'intention pour l'axe dans la variante sélectionnée. |
| Compare against | Second profil | Pilote la différence côte à côte par axe dans la carte de comparaison. |
| Cases à cocher d'approbation de destination | Scalability / renderer ini / Device Profiles | Bloque les écritures permanentes gouvernées ; les destinations non cochées ne sont jamais écrites. |

## Destinations d'application gouvernée (Configuration permanente)

| Destination | Fichier | Écriture permanente ? |
| --- | --- | --- |
| Niveaux de qualité Scalability | `DefaultGameUserSettings.ini` `[ScalabilityGroups]` | Oui, si approuvé. |
| Paramètres de rendu | Section renderer de `DefaultEngine.ini` | Oui, si approuvé. |
| Profils d'appareils | `DefaultDeviceProfiles.ini` | Oui, si approuvé. |
| Variables de console (session) | Session éditeur uniquement | Chemin d'aperçu des Expert Tools ; non permanent. |
| Assets, matériaux, MRQ, accessibilité | Bloqué | Jamais écrit par VFD. |

Flux d'application : construire destinations → approuver → sauvegarder → écrire → vérifier → manifeste de restauration.

## Fonctions de la bibliothèque Blueprint

Catégories de `UVFDCockpitBlueprintLibrary` :

| Fonction | Catégorie | Sortie |
| --- | --- | --- |
| LoadFidelityProfiles | Visual Fidelity\|Profiles | Tableau de profils + avertissements |
| ResolveFidelityProfile | Visual Fidelity\|Profiles | Profil résolu ou erreurs |
| ValidateFidelityProfile | Visual Fidelity\|Profiles | Résultat de validation |
| CompileFidelityProfile | Visual Fidelity\|Profiles | Cibles de paramètres compilées + résultats |
| CompareFidelityProfiles | Visual Fidelity\|Profiles | Résultat de comparaison par axe |
| DetectPipelineCapabilities | Visual Fidelity\|Capability | Rapport de capacités |
| BuildEvidenceState | Visual Fidelity\|Evidence | État des preuves |
| PreviewPersistentDestinations | Visual Fidelity\|Apply | Résumés de destinations en lecture seule |
| ApplyPersistentConfiguration | Visual Fidelity\|Apply | Rapport d'application (requiert approbation) |
| RollbackPersistentConfiguration | Visual Fidelity\|Apply | Rapport de restauration |

Asset de démonstration : `Content/Blueprints/BPF_VFD_API`.

## Valeurs des curseurs d'intention (Expert Tools)

Tous les curseurs d'intention utilisent des valeurs à virgule flottante de `0.00` à `1.00`.

| Commande | Source par défaut | Effet |
| --- | --- | --- |
| Image Stability | Recette sélectionnée | Les valeurs plus élevées favorisent une stabilité temporelle plus calme. |
| Motion Clarity | Recette sélectionnée | Les valeurs plus élevées favorisent moins d'étalement/image fantôme. |
| Fine Detail Preservation | Recette sélectionnée | Les valeurs plus élevées favorisent des détails plus nets avec plus de risques d'aliasing. |
| Specular Calmness | Recette sélectionnée | Les valeurs plus élevées favorisent une réduction du scintillement des reflets. |
| UI Crispness | Recette sélectionnée | Les valeurs plus élevées priorisent la clarté HUD/UMG. |
| Cinematic Accumulation | Recette sélectionnée | Les valeurs plus élevées favorisent l'accumulation du rendu final. |
| Performance Headroom | Recette sélectionnée | Les valeurs plus élevées favorisent des recommandations moins coûteuses. |

## ID de recettes intégrées

Utilisez ces ID dans les fichiers JSON de recettes et les rapports exportés :

```text
stable_gameplay
sharp_gameplay
cinematic_calm
vegetation_heavy_scene
specular_heavy_scene
ui_safe_temporal
vr_clarity
low_end_stable
marketing_screenshot
debug_no_temporal
lumen_static_material_performance
lumen_dynamic_material_safe
lumen_low_end_atlas_budget
lumen_surface_cache_debug
lumen_archviz_many_instances
```

## CVars capturées

La capture de snapshot lit ce registre CVar sélectionné lorsque cela est disponible :

```text
r.AntiAliasingMethod
r.ScreenPercentage
r.TemporalAA.Upsampling
r.PostProcessAAQuality
r.TSR.History.ScreenPercentage
r.TSR.ShadingRejection.Flickering
r.DefaultFeature.MotionBlur
r.MotionBlurQuality
r.LumenScene.SurfaceCache.CardCapturesPerFrame
r.LumenScene.SurfaceCache.CardCaptureRefreshFraction
r.LumenScene.SurfaceCache.CardMaxResolution
r.LumenScene.SurfaceCache.AtlasSize
r.LumenScene.SurfaceCache.AllowCardSharing
r.LumenScene.SurfaceCache.DetectCardSharingCompatibility
r.LumenScene.SurfaceCache.MeshCardsMinSize
r.LumenScene.SurfaceCache.MeshCardsMergeComponents
r.LumenScene.SurfaceCache.MeshCardsMergeInstances
r.LumenScene.DirectLighting.UpdateFactor
r.LumenScene.Radiosity.UpdateFactor
```

Les CVars indisponibles sont enregistrées comme indisponibles au lieu de faire échouer l'ensemble du rapport.

## Examen du cache de surface Lumen

La voie d'examen du cache de surface Lumen est réservée aux rapports sur le contenu des maillages et des matériaux. Elle peut capturer des CVars Lumen sélectionnées, évaluer des recettes Lumen, regrouper les résultats Lumen dans `visual_quality_report.md` et exécuter **Lumen Deep Scan** pour les indices de métadonnées du registre d'assets réservés à l'éditeur. Elle ne modifie pas les paramètres des cartes Static Mesh, les graphes de matériaux, les drapeaux de partage de cartes, la configuration du projet ou les préréglages MRQ.

## Support d'aperçu d'application (Expert Tools)

| Cible prise en charge | Modes pris en charge | Écriture permanente ? |
| --- | --- | --- |
| Variables de console | Preview Only, Editor Session Only | Aucune écriture de configuration de projet. |
| Paramètres du projet | Tiroir d'application gouvernée sur la page Cockpit | Oui, si explicitement approuvé. |
| Post Process Volumes | Recommandation/export uniquement | Non. |
| Préréglages MRQ | Recommandation/export uniquement | Non. |
| Assets | Recommandation/export uniquement | Non. |
| Paramètres de maillage/matériau Lumen | Recommandation/export/examen manuel uniquement | Non. |

## Fichiers de rapports

| Workflow | Fichiers |
| --- | --- |
| Snapshot | `quality_snapshot.json`, `quality_snapshot.md` |
| Recipe dry run | `recipe_evaluation.json`, `settings_diff.md` |
| Scanner | `visual_quality_report.json`, `visual_quality_report.md` |
| Lumen deep scan | `visual_quality_report.json`, `visual_quality_report.md` |
| Apply (session) | `visual_fidelity_apply_report.json`, `visual_fidelity_apply_report.md` |
| Persistent apply | Rapport d'application gouvernée sous les racines de sauvegarde/rapports VFD |
| A/B comparison | `comparison_report.json`, `comparison_report.md` |
| Cinematic | `cinematic_quality_report.json`, `cinematic_quality_report.md`, `mrq_recommendation.md` |
| Schema validation | `schema_validation_report.json`, `schema_validation_report.md` |
| Diagnostics | `experimental_diagnostics_report.json`, `experimental_diagnostics_report.md` |
| Productization | `productization_readiness_report.json`, `productization_readiness_report.md` |

Les dernières copies utilisent les mêmes noms précédés de `latest_` sous `Saved/VisualFidelityDirector/reports/`.

Le fichier JSON du profil utilise des schémas sous le dossier `Schemas/` du plugin et s'enregistre sous `Saved/VisualFidelityDirector/profiles/`.

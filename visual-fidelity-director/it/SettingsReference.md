<!-- doc-provenance: AKDB:plugins/VisualFidelityDirector/architecture.md; docs/architecture/plugins/VisualFidelityDirector/product-facts.yml; reconciled 2026-07-12 -->
# Riferimento impostazioni

VFD aggiunge impostazioni per il plugin dell'editor in **Modifica > Editor Configurations > Visual Fidelity Director Editor Settings**. Le impostazioni di rendering del progetto vengono modificate solo tramite l'applicazione permanente governata o l'anteprima di sessione di Expert Tools.

## Controlli Cockpit

| Controllo | Valori | Effetto |
| --- | --- | --- |
| Selettore profili | Profili noti da `Saved/VisualFidelityDirector/profiles/` | Imposta il profilo di fedeltà attivo per compilazione, prove e confronto. |
| Menu a tendina variante asse | Varianti di pipeline per asse | Seleziona la variante attiva; le opzioni non disponibili rimangono visibili con la prova di compatibilità. |
| Cursore intento asse | `0.00`–`1.00` | Regola il livello di intento per l'asse all'interno della variante selezionata. |
| Compare against | Secondo profilo | Pilota il confronto affiancato per asse nella scheda di confronto. |
| Caselle di controllo approvazione destinazione | Scalability / ini renderer / Device Profiles | Bloccano le scritture permanenti governate; le destinazioni non spuntate non vengono mai scritte. |

## Destinazioni di applicazione governata (Configurazione permanente)

| Destinazione | File | Scrittura permanente? |
| --- | --- | --- |
| Livelli di qualità Scalability | `DefaultGameUserSettings.ini` `[ScalabilityGroups]` | Sì, se approvato. |
| Impostazioni renderer | Sezione renderer di `DefaultEngine.ini` | Sì, se approvato. |
| Profili dispositivi | `DefaultDeviceProfiles.ini` | Sì, se approvato. |
| Variabili di console (sessione) | Solo sessione editor | Percorso di anteprima Expert Tools; non permanente. |
| Asset, materiali, MRQ, accessibilità | Bloccato | Mai scritto da VFD. |

Flusso di applicazione: costruisci destinazioni → approva → backup → scrivi → verifica → manifesto di rollback.

## Funzioni della libreria Blueprint

Categorie di `UVFDCockpitBlueprintLibrary`:

| Funzione | Categoria | Output |
| --- | --- | --- |
| LoadFidelityProfiles | Visual Fidelity\|Profiles | Array di profili + avvisi |
| ResolveFidelityProfile | Visual Fidelity\|Profiles | Profilo risolto o errori |
| ValidateFidelityProfile | Visual Fidelity\|Profiles | Risultato validazione |
| CompileFidelityProfile | Visual Fidelity\|Profiles | Target impostazioni compilati + risultati |
| CompareFidelityProfiles | Visual Fidelity\|Profiles | Risultato confronto per asse |
| DetectPipelineCapabilities | Visual Fidelity\|Capability | Report funzionalità |
| BuildEvidenceState | Visual Fidelity\|Evidence | Stato elementi di prova |
| PreviewPersistentDestinations | Visual Fidelity\|Apply | Riepiloghi destinazioni in sola lettura |
| ApplyPersistentConfiguration | Visual Fidelity\|Apply | Report applicazione (richiede approvazione) |
| RollbackPersistentConfiguration | Visual Fidelity\|Apply | Report rollback |

Asset showcase: `Content/Blueprints/BPF_VFD_API`.

## Valori cursori intento (Expert Tools)

Tutti i cursori dell'intento utilizzano valori con virgola mobile da `0.00` a `1.00`.

| Controllo | Sorgente predefinita | Effetto |
| --- | --- | --- |
| Image Stability | Ricetta selezionata | Valori più alti favoriscono una stabilità temporale più calma. |
| Motion Clarity | Ricetta selezionata | Valori più alti favoriscono meno sbavature/ghosting. |
| Fine Detail Preservation | Ricetta selezionata | Valori più alti favoriscono dettagli più nitidi con maggior rischio di aliasing. |
| Specular Calmness | Ricetta selezionata | Valori più alti favoriscono un ridotto sfarfallio nei punti luce. |
| UI Crispness | Ricetta selezionata | Valori più alti danno priorità alla chiarezza di HUD/UMG. |
| Cinematic Accumulation | Ricetta selezionata | Valori più alti favoriscono l'accumulo del rendering finale. |
| Performance Headroom | Ricetta selezionata | Valori più alti favoriscono raccomandazioni meno onerose. |

## ID ricette integrate

Utilizzare questi ID nei file JSON delle ricette esportate e nei report:

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

## CVar acquisite

La cattura dello snapshot legge questo registro CVar selezionato, quando disponibile:

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

Le CVar non disponibili vengono registrate come non disponibili anziché far fallire l'intero report.

## Revisione cache di superficie Lumen

La corsia di revisione del cache di superficie Lumen è riservata ai report per i contenuti di mesh e materiali. Può acquisire CVar Lumen selezionate, valutare ricette Lumen, raggruppare i risultati Lumen in `visual_quality_report.md` ed eseguire **Lumen Deep Scan** per indicazioni sui metadati dell'Asset Registry riservate all'editor. Non modifica le impostazioni delle schede Static Mesh, i grafi dei materiali, le opzioni di condivisione delle schede, la configurazione del progetto o i preset MRQ.

## Supporto anteprima applicazione (Expert Tools)

| Target supportato | Modalità supportate | Scrittura permanente? |
| --- | --- | --- |
| Variabili di console | Preview Only, Editor Session Only | Nessuna scrittura di configurazione del progetto. |
| Impostazioni di progetto | Cassetto applicazione governata nella pagina Cockpit | Sì, se esplicitamente approvato. |
| Post Process Volumes | Solo raccomandazione/esportazione | No. |
| Preset MRQ | Solo raccomandazione/esportazione | No. |
| Asset | Solo raccomandazione/esportazione | No. |
| Impostazioni mesh/materiali Lumen | Solo raccomandazione/esportazione/revisione manuale | No. |

## File dei report

| Workflow | File |
| --- | --- |
| Snapshot | `quality_snapshot.json`, `quality_snapshot.md` |
| Recipe dry run | `recipe_evaluation.json`, `settings_diff.md` |
| Scanner | `visual_quality_report.json`, `visual_quality_report.md` |
| Lumen deep scan | `visual_quality_report.json`, `visual_quality_report.md` |
| Apply (session) | `visual_fidelity_apply_report.json`, `visual_fidelity_apply_report.md` |
| Persistent apply | Report di applicazione governata sotto le radici dei backup/report di configurazione VFD |
| A/B comparison | `comparison_report.json`, `comparison_report.md` |
| Cinematic | `cinematic_quality_report.json`, `cinematic_quality_report.md`, `mrq_recommendation.md` |
| Schema validation | `schema_validation_report.json`, `schema_validation_report.md` |
| Diagnostics | `experimental_diagnostics_report.json`, `experimental_diagnostics_report.md` |
| Productization | `productization_readiness_report.json`, `productization_readiness_report.md` |

Le ultime copie utilizzano gli stessi nomi prefissati da `latest_` sotto `Saved/VisualFidelityDirector/reports/`.

Il file JSON dei profili utilizza schemi sotto la cartella `Schemas/` del plugin e salva in `Saved/VisualFidelityDirector/profiles/`.

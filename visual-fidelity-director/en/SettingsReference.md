<!-- doc-provenance: AKDB:plugins/VisualFidelityDirector/architecture.md; docs/architecture/plugins/VisualFidelityDirector/product-facts.yml; reconciled 2026-07-12 -->
# Settings Reference

VFD adds editor plugin settings under **Edit > Editor Configurations > Visual Fidelity Director Editor
Settings**. Project rendering settings are changed only through governed persistent apply or Expert Tools
session preview.

## Cockpit Controls

| Control | Values | Effect |
| --- | --- | --- |
| Profile selector | Known profiles from `Saved/VisualFidelityDirector/profiles/` | Sets the active fidelity profile for compilation, evidence, and comparison. |
| Axis variant combo | Pipeline variants per axis | Selects the acting variant; unavailable options stay visible with compatibility evidence. |
| Axis intent slider | `0.00`–`1.00` | Adjusts intent level for the axis within the selected variant. |
| Compare against | Second profile | Drives side-by-side per-axis diff in the comparison card. |
| Destination approval checkboxes | Scalability / renderer ini / Device Profiles | Gates governed persistent writes; unchecked destinations are never written. |

## Governed Apply Destinations (Persistent Configuration)

| Destination | File | Persistent write? |
| --- | --- | --- |
| Scalability quality levels | `DefaultGameUserSettings.ini` `[ScalabilityGroups]` | Yes, when approved. |
| Renderer settings | `DefaultEngine.ini` renderer section | Yes, when approved. |
| Device profiles | `DefaultDeviceProfiles.ini` | Yes, when approved. |
| Console variables (session) | Editor session only | Expert Tools preview path; not persistent. |
| Assets, materials, MRQ, accessibility | Blocked | Never written by VFD. |

Apply flow: build destinations → approve → backup → write → verify → rollback manifest.

## Blueprint Library Functions

`UVFDCockpitBlueprintLibrary` categories:

| Function | Category | Output |
| --- | --- | --- |
| LoadFidelityProfiles | Visual Fidelity\|Profiles | Profile array + warnings |
| ResolveFidelityProfile | Visual Fidelity\|Profiles | Resolved profile or errors |
| ValidateFidelityProfile | Visual Fidelity\|Profiles | Validation result |
| CompileFidelityProfile | Visual Fidelity\|Profiles | Compiled setting targets + findings |
| CompareFidelityProfiles | Visual Fidelity\|Profiles | Per-axis comparison result |
| DetectPipelineCapabilities | Visual Fidelity\|Capability | Capability report |
| BuildEvidenceState | Visual Fidelity\|Evidence | Evidence state |
| PreviewPersistentDestinations | Visual Fidelity\|Apply | Read-only destination summaries |
| ApplyPersistentConfiguration | Visual Fidelity\|Apply | Apply report (requires approval) |
| RollbackPersistentConfiguration | Visual Fidelity\|Apply | Rollback report |

Showcase asset: `Content/Blueprints/BPF_VFD_API`.

## Intent Slider Values (Expert Tools)

All intent sliders use floating-point values from `0.00` to `1.00`.

| Control | Default source | Effect |
| --- | --- | --- |
| Image Stability | Selected recipe | Higher values favor calmer temporal stability. |
| Motion Clarity | Selected recipe | Higher values favor less smear/ghosting. |
| Fine Detail Preservation | Selected recipe | Higher values favor sharper detail with more aliasing risk. |
| Specular Calmness | Selected recipe | Higher values favor reduced highlight flicker. |
| UI Crispness | Selected recipe | Higher values prioritize HUD/UMG clarity. |
| Cinematic Accumulation | Selected recipe | Higher values favor final-render accumulation. |
| Performance Headroom | Selected recipe | Higher values favor cheaper recommendations. |

## Built-In Recipe IDs

Use these IDs in exported recipe JSON and reports:

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

## Captured CVars

Snapshot capture reads this curated CVar registry when available:

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

Unavailable CVars are recorded as unavailable instead of failing the whole report.

## Lumen Surface Cache Review

The Lumen Surface Cache Review lane is report-only for mesh and material content. It can capture
curated Lumen CVars, evaluate Lumen recipes, group Lumen findings in `visual_quality_report.md`, and
run **Lumen Deep Scan** for editor-only Asset Registry metadata clues. It does not change Static Mesh
card settings, material graphs, card-sharing flags, project config, or MRQ presets.

## Preview Apply Support (Expert Tools)

| Supported target | Supported modes | Persistent write? |
| --- | --- | --- |
| Console variables | Preview Only, Editor Session Only | No project config write. |
| Project settings | Governed apply drawer on Cockpit page | Yes, when explicitly approved. |
| Post Process Volumes | Recommendation/export only | No. |
| MRQ presets | Recommendation/export only | No. |
| Assets | Recommendation/export only | No. |
| Lumen mesh/material settings | Recommendation/export/manual review only | No. |

## Report Files

| Workflow | Files |
| --- | --- |
| Snapshot | `quality_snapshot.json`, `quality_snapshot.md` |
| Recipe dry run | `recipe_evaluation.json`, `settings_diff.md` |
| Scanner | `visual_quality_report.json`, `visual_quality_report.md` |
| Lumen deep scan | `visual_quality_report.json`, `visual_quality_report.md` |
| Apply (session) | `visual_fidelity_apply_report.json`, `visual_fidelity_apply_report.md` |
| Persistent apply | Governed apply report under VFD config backup/report roots |
| A/B comparison | `comparison_report.json`, `comparison_report.md` |
| Cinematic | `cinematic_quality_report.json`, `cinematic_quality_report.md`, `mrq_recommendation.md` |
| Schema validation | `schema_validation_report.json`, `schema_validation_report.md` |
| Diagnostics | `experimental_diagnostics_report.json`, `experimental_diagnostics_report.md` |
| Productization | `productization_readiness_report.json`, `productization_readiness_report.md` |

Latest copies use the same names prefixed with `latest_` under
`Saved/VisualFidelityDirector/reports/`.

Profile JSON uses schemas under the plugin `Schemas/` folder and saves to
`Saved/VisualFidelityDirector/profiles/`.

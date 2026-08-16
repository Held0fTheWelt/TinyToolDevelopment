<!-- doc-provenance: AKDB:plugins/VisualFidelityDirector/architecture.md; docs/architecture/plugins/VisualFidelityDirector/product-facts.yml; reconciled 2026-07-12 -->
# Einstellungsreferenz

VFD fügt Editor-Plugin-Einstellungen unter **Bearbeiten > Editor-Konfigurationen > Visual Fidelity Director Editor Settings** hinzu. Projekt-Rendering-Einstellungen werden nur durch verwaltetes permanentes Anwenden oder die Sitzungsvorschau der Expert Tools geändert.

## Cockpit-Steuerelemente

| Steuerelement | Werte | Wirkung |
| --- | --- | --- |
| Profilauswahl | Bekannte Profile aus `Saved/VisualFidelityDirector/profiles/` | Legt das aktive Fidelity-Profil für Kompilierung, Evidenz und Vergleich fest. |
| Achsenvarianten-Kombinationsfeld | Pipeline-Varianten pro Achse | Wählt die wirkende Variante; nicht verfügbare Optionen bleiben mit Kompatibilitätsevidenz sichtbar. |
| Achsen-Intent-Regler | `0.00`–`1.00` | Passt die Intent-Stufe für die Achse innerhalb der ausgewählten Variante an. |
| Compare against | Zweites Profil | Steuert den Gegenüberstellungs-Diff pro Achse in der Vergleichskarte. |
| Ziel-Genehmigungs-Kontrollkästchen | Scalability / Renderer ini / Device Profiles | Steuert verwaltete permanente Schreibvorgänge; nicht aktivierte Ziele werden niemals beschrieben. |

## Verwaltete Anwendungsziele (Permanente Konfiguration)

| Ziel | Datei | Permanenter Schreibvorgang? |
| --- | --- | --- |
| Scalability-Qualitätsstufen | `DefaultGameUserSettings.ini` `[ScalabilityGroups]` | Ja, wenn genehmigt. |
| Renderer-Einstellungen | `DefaultEngine.ini` Renderer-Abschnitt | Ja, wenn genehmigt. |
| Device Profiles | `DefaultDeviceProfiles.ini` | Ja, wenn genehmigt. |
| Konsolenvariablen (Sitzung) | Nur Editor-Sitzung | Expert Tools Vorschaupfad; nicht permanent. |
| Assets, Materialien, MRQ, Barrierefreiheit | Blockiert | Wird niemals von VFD beschrieben. |

Anwendungsablauf: Build Destinations → Genehmigen → Backup → Schreiben → Überprüfen → Rollback-Manifest.

## Blueprint-Bibliotheksfunktionen

`UVFDCockpitBlueprintLibrary` Kategorien:

| Funktion | Kategorie | Ausgabe |
| --- | --- | --- |
| LoadFidelityProfiles | Visual Fidelity\|Profiles | Profil-Array + Warnungen |
| ResolveFidelityProfile | Visual Fidelity\|Profiles | Aufgelöstes Profil oder Fehler |
| ValidateFidelityProfile | Visual Fidelity\|Profiles | Validierungsergebnis |
| CompileFidelityProfile | Visual Fidelity\|Profiles | Kompilierte Einstellungsziele + Befunde |
| CompareFidelityProfiles | Visual Fidelity\|Profiles | Ergebnis des Vergleichs pro Achse |
| DetectPipelineCapabilities | Visual Fidelity\|Capability | Funktionsbericht |
| BuildEvidenceState | Visual Fidelity\|Evidence | Evidenzzustand |
| PreviewPersistentDestinations | Visual Fidelity\|Apply | Schreibgeschützte Ziel-Zusammenfassungen |
| ApplyPersistentConfiguration | Visual Fidelity\|Apply | Anwendungsbericht (erfordert Genehmigung) |
| RollbackPersistentConfiguration | Visual Fidelity\|Apply | Rollback-Bericht |

Showcase-Asset: `Content/Blueprints/BPF_VFD_API`.

## Intent-Reglerwerte (Expert Tools)

Alle Intent-Regler verwenden Gleitkommawerte von `0.00` bis `1.00`.

| Steuerelement | Standardquelle | Wirkung |
| --- | --- | --- |
| Image Stability | Ausgewähltes Rezept | Höhere Werte bevorzugen ruhigere temporale Stabilität. |
| Motion Clarity | Ausgewähltes Rezept | Höhere Werte bevorzugen weniger Verschmieren/Ghosting. |
| Fine Detail Preservation | Ausgewähltes Rezept | Höhere Werte bevorzugen schärfere Details mit höherem Aliasing-Risiko. |
| Specular Calmness | Ausgewähltes Rezept | Höhere Werte bevorzugen reduziertes Flimmern von Glanzlichtern. |
| UI Crispness | Ausgewähltes Rezept | Höhere Werte priorisieren HUD/UMG-Klarheit. |
| Cinematic Accumulation | Ausgewähltes Rezept | Höhere Werte bevorzugen die Final-Render-Akkumulation. |
| Performance Headroom | Ausgewähltes Rezept | Höhere Werte bevorzugen günstigere Empfehlungen. |

## Integrierte Rezept-IDs

Verwenden Sie diese IDs in exportierten Rezept-JSONs und Berichten:

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

## Erfasste CVars

Die Snapshot-Erfassung liest diese kuratierte CVar-Registrierung, wenn verfügbar:

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

Nicht verfügbare CVars werden als nicht verfügbar aufgezeichnet, anstatt den gesamten Bericht fehlschlagen zu lassen.

## Lumen Surface Cache Review

Die Lumen Surface Cache Review Lane ist nur berichtsbezogen für Mesh- und Materialinhalte. Sie kann kuratierte Lumen-CVars erfassen, Lumen-Rezepte auswerten, Lumen-Befunde in `visual_quality_report.md` gruppieren und **Lumen Deep Scan** für reine Editor-Asset-Registry-Metadatenhinweise ausführen. Sie ändert keine Static Mesh Card-Einstellungen, Materialgraphen, Card-Sharing-Flags, Projektkonfigurationen oder MRQ-Presets.

## Vorschau-Anwendungsunterstützung (Expert Tools)

| Unterstütztes Ziel | Unterstützte Modi | Permanenter Schreibvorgang? |
| --- | --- | --- |
| Konsolenvariablen | Preview Only, Editor Session Only | Kein Projektkonfigurations-Schreibvorgang. |
| Projekteinstellungen | Verwalteter Anwendungs-Drawer auf Cockpit-Seite | Ja, wenn explizit genehmigt. |
| Post Process Volumes | Nur Empfehlung/Export | Nein. |
| MRQ-Presets | Nur Empfehlung/Export | Nein. |
| Assets | Nur Empfehlung/Export | Nein. |
| Lumen Mesh-/Materialeinstellungen | Nur Empfehlung/Export/manuelle Überprüfung | Nein. |

## Berichtsdateien

| Workflow | Dateien |
| --- | --- |
| Snapshot | `quality_snapshot.json`, `quality_snapshot.md` |
| Recipe dry run | `recipe_evaluation.json`, `settings_diff.md` |
| Scanner | `visual_quality_report.json`, `visual_quality_report.md` |
| Lumen deep scan | `visual_quality_report.json`, `visual_quality_report.md` |
| Apply (session) | `visual_fidelity_apply_report.json`, `visual_fidelity_apply_report.md` |
| Persistent apply | Verwalteter Anwendungsbericht unter VFD-Konfigurations-Backup-/Berichts-Stammverzeichnissen |
| A/B comparison | `comparison_report.json`, `comparison_report.md` |
| Cinematic | `cinematic_quality_report.json`, `cinematic_quality_report.md`, `mrq_recommendation.md` |
| Schema validation | `schema_validation_report.json`, `schema_validation_report.md` |
| Diagnostics | `experimental_diagnostics_report.json`, `experimental_diagnostics_report.md` |
| Productization | `productization_readiness_report.json`, `productization_readiness_report.md` |

Neueste Kopien verwenden dieselben Namen mit dem Präfix `latest_` unter `Saved/VisualFidelityDirector/reports/`.

Profil-JSON verwendet Schemata unter dem Plugin-Ordner `Schemas/` und speichert in `Saved/VisualFidelityDirector/profiles/`.

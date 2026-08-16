<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/LightweightEditorMode/architecture.md -->
# Einstellungsreferenz

Lightweight Editor Mode speichert Einstellungen in EditorPerProjectUserSettings und macht sie unter Project Settings > Plugins > Lightweight Editor Mode verfügbar.

## Einstellungsmodell

Das Einstellungsobjekt besteht aus drei Schichten:

- High-Level-Optionen wie Startverhalten und ausgewählter Profilindex.
- Aktive Runtime-Werte, die vom Modus verwendet werden, wenn er aktiviert ist.
- Vier bearbeitbare Profil-Structs: Mild, Balanced, Aggressive und Extreme.

Die Slate-UI kopiert das ausgewählte Profil in die aktiven Runtime-Werte, bevor der Modus aktiviert oder aktualisiert wird.

## High-Level-Optionen

### bEnableOnStartup

Aktiviert den Lightweight Editor Mode automatisch beim Start des Editors.

Implementierungshinweise:

- Das Modul aktiviert sich während StartupModule nicht sofort.
- Es startet einen kurzen Ticker.
- Der Ticker wartet, bis GEditor Editor-Viewport-Clients besitzt.
- Der Modus wird erst aktiviert, wenn Viewports verfügbar sind.
- Die Wiederherstellung veralteter Sitzungen läuft vor der automatischen Aktivierung, falls die vorherige Editor-Sitzung beendet wurde, während der Lightweight Mode noch aktiv war.

Dies verhindert den Verlust von Viewport-Änderungen während des frühen Editor-Starts.

### AggressivenessLevel

Speichert den aktuell ausgewählten Profilindex.

| Wert | Profil |
| --- | --- |
| 0 | Mild |
| 1 | Balanced |
| 2 | Aggressive |
| 3 | Extreme |

Der Wert wird auf den gültigen Bereich begrenzt (clamped).

## Aktive Runtime-Werte

Diese Werte werden von FEditorLightweightMode angewendet.

### OverallQuality

Eine einzelne Qualitätsstufe der Unreal-Skalierbarkeit.

| Wert | Bedeutung |
| --- | --- |
| 0 | Low (Niedrig) |
| 1 | Medium (Mittel) |
| 2 | High (Hoch) |
| 3 | Epic (Episch) |
| 4 | Cinematic (Kino) |

Das Plugin begrenzt diesen Wert vor der Anwendung auf 0..4.

### ScreenPercentage

Ziel-Bildschirmprozentsatz für das Rendering des Editor-Viewports sowie PIE/Game-Vorschaupfade.

| Bereich | Bedeutung |
| --- | --- |
| 25..59 | Sehr aggressiv, geringe visuelle Genauigkeit |
| 60..79 | Leistungsorientierte Bearbeitung |
| 80..99 | Ausgewogene Bearbeitung |
| 100 | Volle interne Auflösung |
| 101..200 | Supersampling, für den Lightweight Mode selten nützlich |

Das Plugin begrenzt diesen Wert auf 25..200.

Wichtiges Implementierungsdetail: Editor-Viewports nutzen editor-spezifische Screen-Percentage-CVars. Das Plugin setzt:

- r.Editor.Viewport.ScreenPercentage
- r.Editor.Viewport.ScreenPercentageMode.RealTime
- r.Editor.Viewport.ScreenPercentageMode.NonRealTime

Es setzt außerdem r.ScreenPercentage für PIE und Game-Vorschaupfade, wo diese CVar weiterhin relevant ist.

### bDisableLumen

Deaktiviert indirekte Lumen-Diffuse-Beleuchtung und Lumen-Reflexionen, während der Modus aktiv ist.

CVars:

- r.Lumen.DiffuseIndirect.Allow = 0
- r.Lumen.Reflections.Allow = 0

Wenn im Profil deaktiviert, stellt das Plugin alle vorhandenen Sicherungen für diese CVars wieder her, indem es seine getaggte Überschreibung entfernt. Wenn eine andere Quelle dieselbe CVar geändert hat, während der Lightweight Mode aktiv war, bleibt dieser neuere Wert aktiv.

### bDisableVirtualShadows

Deaktiviert virtuelle Schattenkarten (Virtual Shadow Maps).

CVar:

- r.Shadow.Virtual.Enable = 0

Dies kann leistungskritische Nanite- und Large-World-Szenen reaktionsschneller machen, ändert jedoch das Erscheinungsbild von Schatten erheblich.

### bDisableVolumetricFog

Deaktiviert volumetrischen Nebel und regulären Nebel.

CVars:

- r.VolumetricFog = 0
- r.Fog = 0

Dies ist nützlich in atmosphärischen Szenen, in denen Nebel die Editor-Frame-Zeit dominiert.

### bForceUnlitViewports

Schaltet Editor-Viewports auf Unlit (unbeleuchtet), während der Modus aktiv ist.

Das Plugin speichert den ursprünglichen Ansichtsmodus pro Viewport vor dem Umschalten. Wenn der Modus in derselben Editor-Sitzung deaktiviert wird, werden die ursprünglichen Ansichtsmodi wiederhergestellt.

### bDisableViewportRealtime

Schaltet das Echtzeit-Rendering in Editor-Viewports aus, während der Modus aktiv ist.

Das Plugin nutzt das temporäre Echtzeit-Übersteuerungssystem von Unreal, anstatt die dauerhafte Echtzeit-Einstellung des Viewports zu ändern. Wenn deaktiviert, entfernt es seine eigene Übersteuerung.

## Werte pro Profil

Jedes Profil enthält dieselben Felder:

- OverallQuality
- ScreenPercentage
- bDisableLumen
- bDisableVirtualShadows
- bDisableVolumetricFog
- bForceUnlitViewports
- bDisableViewportRealtime

Profile sind in den Project Settings bearbeitbar. Das Ändern eines Profils wendet es nicht sofort an, es sei denn, die Benutzeroberfläche kopiert dieses Profil in die aktiven Werte.

## LastViewModeBeforeLightweight

Diese versteckt-sichtbare Einstellung speichert den letzten Ansichtsmodus, der vor dem Aktivieren des Modus beobachtet wurde. Sie dient als dauerhafter Fallback nach einem Editor-Neustart.

Wiederherstellungen in derselben Sitzung nutzen zuerst Pro-Viewport-Sicherungen. Eine Wiederherstellung nach einem Neustart kann diese In-Memory-Sicherungen nicht nutzen, weshalb der Fallback-Wert nur verwendet wird, um Unlit-Viewports wieder in einen angemessenen Nicht-Unlit-Modus zu versetzen.

## bWasLightweightModeActiveLastSession

Diese sichtbare Diagnose-Einstellung zeichnet auf, ob der Lightweight Mode vor dem letzten Beenden des Editors aktiv war. Sie wird gesetzt, wenn Enable mit dem Anwenden von Overrides beginnt, und von Disable gelöscht.

Wenn sie nach dem Neustart weiterhin wahr (true) ist, bietet die Benutzeroberfläche Restore Lightweight State an und die automatische Start-Aktivierung stellt den veralteten Viewport-Zustand wieder her, bevor erneut aktiviert wird.

## Beabsichtigter Zweck der Standardprofile

| Profil | Beabsichtigter Zweck |
| --- | --- |
| Mild | Leichte Entlastung bei Erhalt des visuellen Kontextes |
| Balanced | Empfohlener Standard für die allgemeine Bearbeitung |
| Aggressive | Bearbeitung schwerer Szenen, bei der Reaktionsfähigkeit vorgeht |
| Extreme | Notfall-Bearbeitung oder sehr ressourcenarme Umgebungen |

## Empfohlene Anpassung

Für Grafik-fokussierte Teams machen Sie Mild weniger destruktiv und lassen Sie die Lit-Ansicht aktiv. Für Large-World- oder Laptop-Workflows machen Sie Balanced aggressiver. Für technisches Debugging behalten Sie mindestens ein Profil bei, das Unlit nicht erzwingt, damit Rendering-Probleme weiterhin schnell inspiziert werden können.

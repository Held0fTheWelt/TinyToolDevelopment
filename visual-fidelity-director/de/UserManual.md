<!-- doc-provenance: AKDB:plugins/VisualFidelityDirector/architecture.md; docs/architecture/plugins/VisualFidelityDirector/product-facts.yml; reconciled 2026-07-12 -->
# Benutzerhandbuch

Visual Fidelity Director ist ein lokales Unreal Editor-Werkzeug. Version `2.0.0` konzentriert sich auf ein profilzentriertes Cockpit, während das integrierte 1.x Expert Tools-Bedienfeld für Snapshot- und Rezept-Workflows erhalten bleibt.

## Werkzeug öffnen

Verwenden Sie **Tiny Tools > Visual Fidelity Director**.

Die Dock-Registerkarte bietet die Seiten **Cockpit**, **Evidence** und **Expert Tools**.

Optional: **Bearbeiten > Editor-Konfigurationen > Visual Fidelity Director Editor Settings** öffnet die Plugin-Editor-Einstellungen (Menü-Tastenkombination kann in den Einstellungen deaktiviert werden).

## Cockpit-Seite

### Statusbanner

Zeigt die Bereitschaftsüberschrift und den Detailtext aus dem aktiven Profilkompilierungs- und Validierungsstatus.

### Aktionskarte

| Aktion | Erwartetes Ergebnis |
| --- | --- |
| **Refresh** | Lädt Profile neu, kompiliert die aktive Profilvorschau neu, startet die Erfassung von Multi-Frame-Metriken neu und aktualisiert Achsenstreifen. |
| **Compile Preview** | Kompiliert gewünschte Einstellungsziele für das aktive Profil neu, ohne Konfigurationen zu schreiben. |
| **Open Reports** | Öffnet den lokalen VFD-Berichtsordner im Dateibrowser des Betriebssystems. |

### Profilleiste

Wählen Sie das aktive Fidelity-Profil. Die Leiste zeigt den Validierungsstatus und bekannte Profile, die aus `Saved/VisualFidelityDirector/profiles/` geladen wurden.

### Metrikleiste

Zeigt Live-Editor-Metriken über mehrere Frames (Frame, Game Thread, Render Thread, GPU, Engpass und Kostenanteil pro Achse, wenn verfügbar). Werte von `-1` oder explizite Nicht-Verfügbar-Zeichenketten bedeuten, dass die Messung im aktuellen Editor-Kontext nicht verfügbar ist — VFD erfindet niemals Zahlen.

### Achsenstreifen

Jeder Kompositionsachsen-Streifen beinhaltet:

- Achsenbeschriftung und Bereitschaftsfarbe;
- **Variant**-Kombinationsfeld (nicht verfügbare Varianten bleiben sichtbar, sind jedoch mit Kompatibilitätsevidenz deaktiviert);
- **Intent**-Regler (`0.00`–`1.00`);
- Auswahthervorhebung für den aktiven Achsendetail-Drawer.

### Achsendetail-Drawer

Für die ausgewählte Achse:

- **Vererbungspfad** — geordnete Kette vom Stammvorgänger zum aktiven Profil;
- **Provenienz** — feldebene Zeilen für kompilierte Einstellungen (Ziel, Wert, Quelle);
- **Befunde** — kontrolllokale Kompilierungs- und Kompatibilitätsbefunde.

### Profilvergleichs-Karte

Wählen Sie ein zweites Profil und inspizieren Sie Diffs des kompilierten Zielzustands pro Achse. Verwendet dieselbe Vergleichslaufzeit wie die Blueprint-Bibliothek.

### Verwalteter Anwendungs-Drawer

| Aktion | Erwartetes Ergebnis |
| --- | --- |
| **Build Destinations** | Schreibgeschützte Zusammenfassungen für Scalability-, Renderer-ini- und Device Profile-Ziele. |
| **Apply Approved** | Schreibt nur geprüfte, vom Benutzer genehmigte Ziele durch Backup → Schreiben → Überprüfen → Rollback-Manifest. |
| **Rollback** | Stellt die zuletzt gesicherten Dateien aus dem Rollback-Manifest wieder her. |

Blockierte Ziele (Assets, Materialien, MRQ, Barrierefreiheit, reine Überprüfungsachsen) erscheinen niemals als beschreibbare Ziele.

## Evidence-Seite

Zeigt elf feste Lane-Evidenzblöcke (Lumen und andere Überprüfungslanes) mit deklarierten Achsenzuordnungen, Vertrauen und manuellen Überprüfungsgrenzen. Diese Seite ist schreibgeschützt.

## Expert Tools-Seite

Das integrierte 1.x-Bedienfeld für Legacy-Workflows:

### Intent Mixer

Jeder Schieberegler akzeptiert `0.00` bis `1.00` und beeinflusst die Rezept-Trockenlauf-Auswertung nur, bis Sie exportieren oder anwenden.

| Schieberegler | Bedeutung |
| --- | --- |
| Image Stability | Bevorzugt ruhigete Subpixel-Details und weniger Flimmern. |
| Motion Clarity | Bevorzugt weniger Verschmieren/Ghosting bei bewegten Inhalten. |
| Fine Detail Preservation | Bevorzugt schärfere sichtbare Details. |
| Specular Calmness | Bevorzugt weniger Flimmern in Highlights/glänzenden Bereichen. |
| UI Crispness | Bevorzugt HUD/UMG-Klarheit. |
| Cinematic Accumulation | Bevorzugt die Sample-Akkumulation des Final-Renders. |
| Performance Headroom | Bevorzugt günstigere Empfehlungen. |

### Integrierte Rezepte

Dieselben fünfzehn integrierten Rezept-IDs wie in Version `1.0.0` (siehe [SettingsReference.md](SettingsReference.md)).

### Expert Tools-Aktionen

| Aktion | Erwartetes Ergebnis |
| --- | --- |
| Export Snapshot (Expert Tools) | `quality_snapshot.json/.md` plus neueste Kopien. |
| Export Recipe Dry Run (Expert Tools) | `recipe_evaluation.json` und `settings_diff.md`; keine Mutation. |
| Duplicate Recipe | Projekt-eigenes JSON unter `Saved/VisualFidelityDirector/recipes/`. |
| Import Recipe | Aktualisiert aktives Rezept und Schieberegler aus importiertem JSON. |
| Export Scanner Report | `visual_quality_report.json/.md`. |
| Lumen Deep Scan (Expert Tools) | Lumen Surface Cache-Metadatenbefunde; keine Mesh-/Material-Mutation. |
| Preview Apply + Rollback (Expert Tools) | Sitzungs-CVar-Vorschau mit Rollback; `visual_fidelity_apply_report.*`. |
| Export A/B Report | `comparison_report.json/.md`. |
| Export Cinematic Report | `cinematic_quality_report.*` und `mrq_recommendation.md`. |
| Validate Schemas | `schema_validation_report.*`. |
| Export Diagnostics | `experimental_diagnostics_report.*`. |
| Productization Report | `productization_readiness_report.*`. |
| Open Output Folder | Öffnet das Berichts-Stammverzeichnis. |

## Blueprint-Bibliothek

`UVFDCockpitBlueprintLibrary` macht dieselben headless Dienste verfügbar wie das Cockpit:

- Laden, Auflösen, Validieren und Kompilieren von Fidelity-Profilen;
- Vergleichen von Profilen;
- Erkennen von Pipeline-Funktionen;
- Erstellen des Evidenzzustands;
- Vorschau, Anwenden und Rollback verwalteter permanenter Konfigurationen.

Verpacktes Showcase-Asset: `Content/Blueprints/BPF_VFD_API`.

## Sicherheitsmodell

- Cockpit-Überprüfung, Evidenz, Vergleich und Zielvorschau sind schreibgeschützt.
- Verwaltetes permanentes Anwenden ist der einzige Cockpit-Mutationspfad und erfordert eine explizite Genehmigung pro Ziel.
- Expert Tools Vorschau-Anwenden bleibt nur für Sitzungs-CVars mit Rollback.
- Assets, Materialien, Post Process Volumes, MRQ-Presets und Barrierefreiheitseinstellungen werden von VFD nicht geändert.

## Berichte und Profile

```text
Saved/VisualFidelityDirector/profiles/
Saved/VisualFidelityDirector/reports/
Saved/VisualFidelityDirector/recipes/
```

Behandeln Sie Ausgaben als lokal/privat, da sie Projektnamen, CVar-Werte und Qualitätsausrichtungen enthalten können.

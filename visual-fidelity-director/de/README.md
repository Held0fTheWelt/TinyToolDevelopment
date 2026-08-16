<!-- doc-provenance: AKDB:plugins/VisualFidelityDirector/architecture.md; docs/architecture/plugins/VisualFidelityDirector/product-facts.yml; reconciled 2026-07-12 -->
# Visual Fidelity Director Dokumentation

Dieser Ordner enthält die mitgelieferte Käuferdokumentation für Visual Fidelity Director. Der Kern-Workflow ist eigenständig: Aktivieren Sie das Plugin, öffnen Sie das Cockpit, überprüfen Sie Fidelity-Profile und Kompositionsachsen, inspizieren Sie Evidenzen, genehmigen Sie optional verwaltete Konfigurationsschreibvorgänge und nutzen Sie Expert Tools für klassische Snapshot-/Rezept-Workflows ohne weiteres Plugin oder externen Dienst.

Die aktuelle Paketdokumentation ist auf Version `2.0.0` und den Veröffentlichungsstatus `In Publishment` abgestimmt.

## Hier beginnen

- [QUICKSTART.md](QUICKSTART.md): Installation, Aktivierung, erste Cockpit-Aktualisierung und eine Profilvergleichsaufgabe.
- [UserManual.md](UserManual.md): Jede Cockpit-, Evidenz- und Expert Tools-Aktion.
- [SettingsReference.md](SettingsReference.md): Steuerelemente, Profilpfade, Blueprint-Bibliotheksfunktionen, Berichts-Ausgaben und Anwendungsverhalten.
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md): Häufige Probleme und Lösungen.
- [FAQ.md](FAQ.md): Antworten zu Kompatibilität, Sicherheit, MRQ, Screenshots und Support.
- [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md): Erklärung zu externen Abhängigkeiten.

## Cockpit-Einstieg

Öffnen Sie Visual Fidelity Director über **Tiny Tools > Visual Fidelity Director** (Bereich Performance).

Die Dock-Registerkarte bietet drei Seiten:

| Seite | Zweck |
| --- | --- |
| **Cockpit** | Profilleiste, Multi-Frame-Laufzeitmetriken, neun Kompositionsachsen, Variantenselektor, Intent-Regler, Achsendetails mit Vererbungspfad, Provenienz, Befunde, Profilvergleich und verwaltetes permanentes Anwenden. |
| **Evidence** | Elf feste Lane-Evidenzblöcke, die Kompositionsachsen zugeordnet sind. |
| **Expert Tools** | Integriertes 1.x-Bedienfeld für Snapshots, Rezepte, Scanner, Vorschau-Anwenden und Legacy-Berichte. |

## Profile und Berichte

Fidelity-Profile befinden sich unter:

```text
Saved/VisualFidelityDirector/profiles/
```

Berichte aus Expert Tools und Validierungs-Workflows befinden sich unter:

```text
Saved/VisualFidelityDirector/reports/
```

Rezeptkopien verbleiben unter:

```text
Saved/VisualFidelityDirector/recipes/
```

## Blueprint-Oberfläche

Laufzeit-Blueprint-Aufrufer verwenden `UVFDCockpitBlueprintLibrary` (dieselben C++-Dienste wie die Cockpit-UI). Ein verpacktes Showcase-Asset wird unter `Content/Blueprints/BPF_VFD_API` ausgeliefert.

## Sicherheitsmodell

- Cockpit-Überprüfung, Evidenz und Vergleichsaktionen sind schreibgeschützt, außer Sie verwenden die verwaltete Anwendungs-Schublade.
- **Verwaltetes permanentes Anwenden** schreibt nur in `DefaultGameUserSettings.ini` Scalability-Gruppen, `DefaultEngine.ini` Renderer-Einstellungen und `DefaultDeviceProfiles.ini`, und das nur nach expliziter Genehmigung pro Ziel mit Unterstützung für Backup, Überprüfung und Rollback.
- **Expert Tools > Preview Apply + Rollback** bleibt der Sitzungs-CVar-Vorschaupfad.
- Assets, Materialien, Post Process Volumes, MRQ-Presets, LevelSequences, Blueprints und Barrierefreiheitseinstellungen bleiben gesperrt.

## Schemata

Verpackte Laufzeit-Schemadateien befinden sich unter `Schemas/` im Plugin-Stammverzeichnis.

## Verwandte Dateien

- [../README.md](../README.md): Produktübersicht.
- [../CHANGELOG.md](../CHANGELOG.md): Versionshistorie.

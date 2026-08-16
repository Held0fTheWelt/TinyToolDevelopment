<!-- doc-provenance: AKDB:plugins/VisualFidelityDirector/architecture.md; docs/architecture/plugins/VisualFidelityDirector/product-facts.yml; reconciled 2026-07-12 -->
# Schnellstart

Dieser Leitfaden führt Sie von der Installation zu einem konkreten Ergebnis: Das Visual Fidelity Director Cockpit ist geöffnet mit einer aktualisierten Profilansicht und einem Gegenüberstellungs-Profilvergleich.

## Was Sie nach diesem Leitfaden haben werden

Das VFD-Cockpit ist im Unreal Editor geöffnet, die Erfassung von Live-Metriken ist gestartet, eine Kompositionsachse wurde mit Varianten- und Provenienzdetails überprüft und ein Vergleich mit einem zweiten Profil wurde durchgeführt.

## Anforderungen

- Unreal Engine 5.4 Editor auf Win64, Linux oder Mac.
- Ein Projekt, das Editor-Plugins laden kann.
- Keine Drittanbieter-Software, kein Konto, kein KI-Dienst und kein anderes Tiny Tool-Plugin.

## 1. Installieren und Aktivieren

1. Fügen Sie **VisualFidelityDirector** aus Ihrer Fab-Bibliothek dem Projekt hinzu oder installieren Sie es in der Engine.
2. Öffnen Sie **Bearbeiten > Plugins**.
3. Suchen Sie nach **Visual Fidelity Director**.
4. Aktivieren Sie das Plugin und starten Sie Unreal Editor neu, wenn Sie dazu aufgefordert werden.

Wenn Sie ein reines Quellcode-Plugin-Paket in ein C++-Projekt installieren, lassen Sie Unreal die Projektmodule beim nächsten Editor-Start kompilieren.

## 2. Cockpit öffnen

1. Öffnen Sie **Tiny Tools > Visual Fidelity Director**.
2. Bestätigen Sie, dass die Seite **Cockpit** aktiv ist (Standard).
3. Überprüfen Sie das Statusbanner, die Profilauswahl und die Metrikleiste.

Erwartetes Ergebnis:

- Der Titel der Dock-Registerkarte lautet **Visual Fidelity Director**.
- Die Profilleiste listet bekannte Profile aus `Saved/VisualFidelityDirector/profiles/` sowie den integrierten/Projektkontext auf.
- Die Metrikleiste füllt sich über mehrere Editor-Ticks (Multi-Frame-Abtastung) oder zeigt einen expliziten Nicht-Verfügbar-Status an.

## 3. Durchgeführtes Beispiel: Eine Achse überprüfen

1. Klicken Sie auf der Cockpit-Aktionskarte auf **Refresh**.
2. Wählen Sie einen beliebigen Kompositionsachsen-Streifen (z. B. **Anti-Aliasing** oder **Upscaling**).
3. Überprüfen Sie im Achsendetail-Drawer:
   - den **Vererbungspfad** vom Stammprofil zum aktiven Profil;
   - **Provenienz**-Zeilen für kompilierte Einstellungen;
   - **kontrolllokale Befunde** für diese Achse.
4. Ändern Sie das **Variant**-Kombinationsfeld, wenn mehrere Pipeline-Varianten verfügbar sind. Nicht verfügbare Varianten bleiben sichtbar, sind jedoch mit Kompatibilitätsevidenz deaktiviert.

Erwartetes Ergebnis:

- Intent-Regler-Aktualisierungen spiegeln die ausgewählte Variante wider.
- Provenienz und Befunde werden für die ausgewählte Achse aktualisiert.
- Keine Projektdateien ändern sich, bis Sie das verwaltete Anwenden oder die Vorschauanwendung der Expert Tools verwenden.

## 4. Durchgeführtes Beispiel: Zwei Profile vergleichen

1. Scrollen Sie zur Karte **Profile Comparison** auf der Cockpit-Seite.
2. Wählen Sie im Dropdown-Menü ein Profil unter **Compare against**.
3. Lesen Sie die prozentuale Diff-Zusammenfassung pro Achse.

Erwartetes Ergebnis:

- Abweichende Achsen werden mit Details auf Einstellungsebene aufgelistet.
- Übereinstimmende Achsen zeigen keine Diff-Zeilen.
- Der Vergleich verwendet dieselbe Laufzeit-Vergleichslogik wie `UVFDCockpitBlueprintLibrary::CompareFidelityProfiles`.

## 5. Optional: Expert Tools Snapshot

1. Wechseln Sie zur Seite **Expert Tools**.
2. Klicken Sie auf **Export Snapshot**.

Erwartetes Ergebnis:

- `Saved/VisualFidelityDirector/reports/<timestamp>/quality_snapshot.json` existiert.
- Neueste Kopien erscheinen unter `Saved/VisualFidelityDirector/reports/`.

Dieser Pfad bewahrt den Snapshot- und Rezept-Workflow von 1.x für Benutzer, die eine berichtsbasierte Überprüfung bevorzugen.

## 6. Optional: Verwaltetes permanentes Anwenden

Fahren Sie nur fort, wenn Sie beabsichtigen, Projektkonfigurationsdateien zu schreiben.

1. Klicken Sie auf der Cockpit-Seite in der Anwendungs-Schublade auf **Build Destinations**.
2. Überprüfen Sie jede Ziel-Zusammenfassung (Scalability, Renderer-ini, Device Profiles).
3. Aktivieren Sie die Genehmigung nur für Ziele, die Sie akzeptieren.
4. Klicken Sie auf **Apply Approved**.

Erwartetes Ergebnis:

- Zeitgestempelte Backups und ein Rollback-Manifest unter dem VFD-Konfigurations-Backup-Stammverzeichnis.
- Anwendungsbericht mit Überprüfungsergebnissen.
- **Rollback** stellt gesicherte Dateien wieder her, wenn eine Überprüfung fehlschlägt.

## 7. Wo Ausgaben liegen

```text
Saved/VisualFidelityDirector/profiles/
Saved/VisualFidelityDirector/reports/<timestamp>/
Saved/VisualFidelityDirector/recipes/
```

## 8. Nächste Schritte

- Vollständige Operationsliste: [UserManual.md](UserManual.md)
- Steuerelemente und Blueprint-Funktionen: [SettingsReference.md](SettingsReference.md)
- Probleme und Lösungen: [TROUBLESHOOTING.md](TROUBLESHOOTING.md)
- Kompatibilitäts- und Sicherheitsantworten: [FAQ.md](FAQ.md)

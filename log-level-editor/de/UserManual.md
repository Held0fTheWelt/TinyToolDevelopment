<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/LogLevelEditor/architecture.md -->
# Benutzerhandbuch

Dieses Handbuch erklärt den täglichen Editor-Workflow für LogLevelEditor.

## Installation

1. Fügen Sie das Plugin zum Ordner `Plugins` Ihres Projekts hinzu oder installieren Sie es über Fab.
2. Aktivieren Sie **LogLevelEditor** unter **Edit > Plugins**.
3. Starten Sie den Editor neu, falls Unreal dazu auffordert.
4. Bestätigen Sie, dass der Plugin-Inhalt sichtbar ist, wenn Sie das Standard-DataAsset untersuchen möchten.

## Tool öffnen

Öffnen Sie LogLevelEditor über **Tools → Log Tools → Log Level Editor** oder das optionale Symbolleisten-Kürzel. Das Plugin öffnet sich als andockbarer Editor-Tab, damit es im Editor-Workspace bleibt.

## Erster Scan

Beim Öffnen scannt das Tool die konfigurierten Pfade nach Log-Kategorien.

Standardmäßig konzentriert es sich auf:

- Projekt-Quellcodedateien.
- Projekt-Plugin-Quellcodedateien.

Optionale Einstellungen können einschließen:

- Engine-Plugin-Quellcodedateien.
- Engine-Quellcodedateien.

Engine-Scans können zeitaufwendig sein. Aktivieren Sie diese nur, wenn Sie Engine-Kategorien wirklich im Dashboard benötigen.

## Liste lesen

Jede Zeile repräsentiert eine Log-Kategorie.

Wichtige Felder:

- Kategoriename: der Unreal-Log-Kategoriename, zum Beispiel `LogTemp`.
- Erkannter Standardwert: die Standard-Ausführlichkeit, die nach Möglichkeit aus dem Deklarations-/Definitionsmakro abgeleitet wird.
- Aktuelle Stufe: die Ausführlichkeit, die Unreal derzeit für die registrierte Kategorie meldet. Wenn Unreal sie noch nicht melden kann, zeigt die Zeile `Unavailable`. Nach dem ersten Scan wird dieser Wert regelmäßig aus dem Runtime-Zustand von Unreal aktualisiert.
- Quellcode-Pfad: wo der Scanner die Kategorie gefunden hat (falls verfügbar).

## Ausführlichkeit ändern

1. Finden Sie die Kategorie über Suche/Filterung.
2. Wählen Sie einen Verbosity-Wert aus den Schaltflächen der Zeile.
3. Das Plugin führt den Unreal-Konsolenbefehl aus.
4. Die Zeile und das DataAsset werden erst nach erfolgreicher Befehlsausführung aktualisiert.

Häufige Optionen:

- `Warning`: Rauschen reduzieren, wichtige Probleme behalten.
- `Log`: üblicher Standard für normale Ausgaben.
- `Verbose`: nützlich für Diagnosen.
- `VeryVerbose`: sehr detaillierte Ausgabe, meist temporär.
- `NoLogging`: Kategorie so stumm schalten, wie Unreal es erlaubt.

## Standardwerte wiederherstellen

Wenn die ausgewählte Ausführlichkeit dem erkannten Standardwert entspricht, entfernt das Plugin die dauerhafte Überschreibung für diese Kategorie. Dadurch bleibt das DataAsset auf echte Überschreibungen fokussiert.

Wenn kein Standardwert erkannt wurde, behandeln Sie die Zeile als informativ und setzen Sie sie manuell auf den Wert zurück, den Ihr Projekt erwartet.

## Dauerhafte Überschreibungen

Dauerhafte Werte werden im konfigurierten `ULogLevelDataAsset` gespeichert.

Empfohlener Workflow:

1. Halten Sie beabsichtigte projektweite Überschreibungen im Standard-DataAsset.
2. Fügen Sie das Asset nur dann zur Versionsverwaltung hinzu, wenn diese Überschreibungen der Team-Richtlinie entsprechen.
3. Vermeiden Sie es, temporäres Debug-Rauschen in die gemeinsame Quellcodeverwaltung zu speichern.
4. Nutzen Sie temporäre Ausblend-Einstellungen für den persönlichen UI-Fokus.

## Anwendung beim Start

Gespeicherte Überschreibungen werden beim Editor-Start erneut angewendet. Das Modul wartet, bis die Engine Konsolenbefehle akzeptieren kann, und wiederholt den Versuch bei frühem Start mehrmals.

Die erneute Anwendung wird pro Kategorie nachverfolgt.

## Kategorien ausblenden

Permanente Ausblendliste:

- In der Konfiguration gespeichert.
- Nützlich für Kategorien, die selten im Tool erscheinen sollen.

Temporäre Ausblendliste:

- Flüchtige Speicherung.
- Nützlich für lokalen Fokus während einer Editor-Sitzung.
- Nicht in die Konfiguration geschrieben.

## Einstellungen

Öffnen Sie die Plugin-Einstellungen unter den registrierten Editor-/Projekteinstellungen.

Wichtige Einstellungen:

- `LogLevelDataAsset`: DataAsset zur Speicherung dauerhafter Überschreibungen.
- `bAutoSaveLogLevelDataAsset`: speichert das Asset automatisch nach beabsichtigten Änderungen.
- `bShowToolbarButton`: blendet das Symbolleisten-Kürzel ein oder aus.
- `bAlsoListEnginePluginChannels`: schließt Engine-Plugin-Kategorien in Scans ein.
- `bAlsoListEngineSourceChannels`: schließt Engine-Quellcode-Kategorien in Scans ein.
- `LogChannelsToHide`: permanent ausgeblendete Kategorien.
- `LogChannelsToHideTemporary`: nur für die Sitzung ausgeblendete Kategorien.

## Empfohlener Team-Workflow

Für die Nutzung im Team:

1. Halten Sie das Standard-DataAsset in der Quellcodeverwaltung.
2. Speichern Sie nur stabile Projekt-Richtlinienüberschreibungen.
3. Committen Sie keine lokalen temporären Ausblendungen.
4. Dokumentieren Sie Support-/Debug-Presets im Wiki Ihres Projekts.

## Entfernen des Plugins

Vor dem Entfernen des Plugins:

1. Setzen Sie temporäre Log-Verbosity-Änderungen zurück.
2. Entfernen oder ignorieren Sie das Plugin-DataAsset, falls es nicht mehr verwendet wird.
3. Deaktivieren Sie das Plugin und starten Sie den Editor neu.

Das Plugin verändert keine Quellcode-Deklarationen von Log-Kategorien, daher erfordert das Entfernen keine Bereinigung in C++.

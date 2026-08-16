<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/LogLevelEditor/architecture.md -->
# LogLevelEditor Dokumentation

LogLevelEditor ist ein Unreal Engine-Editor-Plugin zur Erkennung von Log-Kategorien und zur Änderung ihrer Ausführlichkeit (Verbosity) über ein fokussiertes Editor-Dashboard. Es hilft Teams, störende Logs während der täglichen Arbeit zu reduzieren, Diagnosekanäle beim Debuggen vorübergehend anzuheben und beabsichtigte Überschreibungen in einem DataAsset zu speichern.

Kernaktionen sind **Scan**, **Set Verbosity** und **Hide Category**.

Dieser Ordner enthält die vollständige Dokumentation, die mit dem Plugin geliefert wird.

## Hier beginnen

- [BUYER_GUIDE.md](BUYER_GUIDE.md): käuferfreundliche Übersicht, Eignung und praktischer Nutzen.
- [UserManual.md](UserManual.md): vollständiger Editor-Workflow von der Einrichtung bis zum Anwenden von Überschreibungen.
- [FAQ.md](FAQ.md): Fab-bereite Fragen und Antworten für Käufer.

## Referenz

- [SettingsReference.md](SettingsReference.md): jede Einstellung, Standardverhalten und empfohlener Grundstandard.
- [TechnicalOverview.md](TechnicalOverview.md): Architektur und Runtime-Verhalten für Maintainer.
- [CodeDocumentation.md](CodeDocumentation.md): Quellcode-Layout, Code-Verträge und Erweiterungspunkte.
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md): häufige Probleme und Lösungen.
- [ReleaseChecklist.md](ReleaseChecklist.md): Validierungsschritte vor dem Versand eines Fab-Updates.

## Enthaltene Assets

- `../Readme.pdf`: klassische verpackte Readme.
- `../LogLevelEditor_Changelog.txt`: Versionshinweise.
- `../Content/DA_LogLevelVerbosity.uasset`: Standard-DataAsset für dauerhafte Verbosity-Überschreibungen.
- `../Content/Map_Tutorial_LogLevelEditor.umap`: Tutorial-/Demo-Inhalt.

## Schneller Workflow

1. Aktivieren Sie das Plugin und starten Sie den Editor neu, wenn Sie dazu aufgefordert werden.
2. Öffnen Sie die Registerkarte Log Level Editor über **Tools → Log Tools → Log Level Editor** oder das optionale Symbolleisten-Kürzel.
3. Lassen Sie den Scanner Projekt- und Plugin-Log-Kategorien erkennen.
4. Nutzen Sie Such- und Ausblend-Einstellungen, um sich auf die wichtigen Kanäle zu konzentrieren.
5. Ändern Sie die Ausführlichkeit einer Kategorie über die Verbosity-Schaltflächen der jeweiligen Zeile.
6. Speichern Sie Überschreibungen im konfigurierten `ULogLevelDataAsset`, wenn die Änderung beabsichtigt ist.
7. Setzen Sie eine Kategorie auf ihren erkannten Standard zurück, indem Sie erneut den erkannten Standardwert auswählen.

## Was das Tool ändert

Das Plugin wendet Unreal-Konsolenbefehle in folgender Form an:

```text
Log <CategoryName> <VerbosityName>
```

Es verändert nicht die Quellcode-Deklaration einer Log-Kategorie. Dauerhafte Änderungen werden im konfigurierten DataAsset gespeichert und vom Editor-Modul erneut angewendet, sobald die Engine zur Aufnahme von Konsolenbefehlen bereit ist.

## Unterstützte Verbosity-Namen

Der gemeinsame Verbosity-Helper unterstützt die Standard-Log-Ebenen von Unreal:

- `NoLogging`
- `Fatal`
- `Error`
- `Warning`
- `Display`
- `Log`
- `Verbose`
- `VeryVerbose`

Der Editor nutzt bewusst dieselben Namen wie die Log-Konfiguration von Unreal, damit Benutzer UI-Änderungen direkt Konsolenbefehlen zuordnen können.

## Sicherheitsmodell

LogLevelEditor vermeidet es, dem Benutzer falsche Zustände anzuzeigen:

- Das Label `Current` wird aus dem Runtime-Zustand von Unreal gelesen, sobald die Kategorie abgefragt werden kann.
- Der UI-Zustand wird erst aktualisiert, nachdem ein Konsolenbefehl erfolgreich war.
- Dauerhafte Überschreibungen werden entfernt, wenn der ausgewählte Wert dem erkannten Standard entspricht.
- Temporäre Ausblend-Einstellungen bleiben flüchtig und werden nicht in die Konfigurationsdatei geschrieben.
- Gespeicherte Überschreibungen werden beim Starten mit einer Kategorie-Wiederholungslogik angewendet, da der Editor beim Modulstart noch nicht immer bereit für Konsolenbefehle ist.

## Typische Anwendungsfälle

- Reduzieren von Spam eines lauten Plugins, während das Plugin aktiviert bleibt.
- Vorübergehendes Anheben eines Gameplay-, Build-, Asset- oder Editor-Subsystems auf `Verbose`.
- Wiederherstellen sauberer Standardwerte nach der Untersuchung eines Problems.
- Teilen eines Team-DataAssets mit beabsichtigten, projektweiten Verbosity-Überschreibungen.
- Getrenntes Verwalten von Engine- und Projektkategorien über Einstellungen, um Scans schnell und relevant zu halten.

## Wichtige Einschränkungen

- Log-Kategorien müssen im Quellcode existieren oder bereits durch Runtime-/Editor-Module registriert sein.
- Der Quellcode-Scan kann Standardwerte nur aus gängigen Unreal-Makros ableiten.
- Runtime-Code kann die Ausführlichkeit nach dem Anwenden gespeicherter Überschreibungen weiterhin ändern.
- Versand-Builds (Shipping Builds) werden von diesem Editor-Plugin nicht beeinflusst.

## Rechtlicher Hinweis

LogLevelEditor ist ein Produktivitätswerkzeug für den Editor. Es ändert weder die Logging-Semantik von Unreal Engine noch den Engine-Quellcode oder die Lizenzbedingungen des Projekts.

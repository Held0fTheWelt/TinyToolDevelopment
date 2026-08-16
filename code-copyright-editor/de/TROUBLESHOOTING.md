<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/CodeCopyrightEditor/architecture.md -->
# Risoluzione dei problemi / Fehlerbehebung

Diese Seite listet häufige Probleme und praktische Lösungen auf.

## Das Werkzeug erscheint nicht im Menü "Tools"

Prüfe:

- Das Plugin ist für das Projekt aktiviert.
- Unreal Editor wurde nach der Aktivierung des Plugins neu gestartet.
- Das Plugin wurde für die aktuelle Unreal Engine-Version kompiliert.

Erwarteter Menüpfad:

```text
Tools > Code Tools > Code Copyright Editor
```

## Die Seite in den Project Settings fehlt

Prüfe:

- Das Plugin-Modul wurde erfolgreich geladen.
- Das Projekt verwendet einen Editor-Build, keinen gepackten Runtime-Build.
- Das Plugin ist im Projekt- oder Engine-Plugin-Ordner installiert.

## Der Scan findet keine Dateien

Prüfe:

- `ScanRootPaths` enthält Ordner, die existieren.
- Dateien verwenden unterstützte Dateiendungen.
- Ausgeschlossene Pfadfragmente sind nicht zu breit gefasst.

## Dateien sind als PROTECTED markiert

Der Scanner hat hinweisähnlichen Text gefunden, der nicht zu den eigenen Markierungen passt oder mit geschützten Markierungen übereinstimmt.

Lösungsoptionen:

- Lass die Datei unangetastet, wenn es sich um Drittanbieter- oder Epic-Code handelt.
- Füge den Anbieterordner zu den Ausschlüssen hinzu.
- Füge eine eigene Markierung nur hinzu, wenn die Datei wirklich zu deinem Projekt gehört.

## Schreibfehler (Write Errors)

Häufige Ursachen:

- Datei ist schreibgeschützt.
- Datei ist durch einen anderen Prozess gesperrt.
- Checkout in der Quellcodeverwaltung ist erforderlich.
- Benutzerkonto fehlen Schreibrechte.

Behebe den Dateistatus und führe Scan/Apply erneut aus.

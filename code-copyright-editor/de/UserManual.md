<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/CodeCopyrightEditor/architecture.md -->
# Benutzerhandbuch

Dieses Handbuch erklärt den vollständigen Editor-Workflow für den Code Copyright Editor.

## Zweck

Code Copyright Editor verwaltet Urheberrechtshinweistexte an zwei Stellen:

- Den Urheberrechtshinweis auf Unreal Engine-Projektebene.
- Quellcode-Datei-Header über konfigurierte Projekt- und Plugin-Ordner hinweg.

Das Plugin ist für kontrollierte Quellcode-Umschreibungen konzipiert. Es scannt zuerst, zeigt eine Vorschau an, lässt den Benutzer Dateien auswählen und schreibt ausgewählte änderbare Dateien erst nach Bestätigung um.

## Das Werkzeug öffnen

Nach Aktivierung des Plugins öffne:

```text
Tools > Code Tools > Code Copyright Editor
```

Das Plugin macht seine Konfiguration auch unter folgendem Pfad zugänglich:

```text
Project Settings > Plugins > Code Copyright Editor
```

## Haupt-Workflow

1. Konfiguriere Identität, Lizenz, Vorlage, Scope und Schutz-Einstellungen.
2. Speichere die Einstellungen.
3. Aktualisiere bei Bedarf den Projekthinweis (Project Settings Notice).
4. Scanne die Codebasis.
5. Überprüfe Status-Badges und Vorschauen.
6. Füge optionale dateibezogene Metadaten hinzu.
7. Wähle nur die Dateien aus, die umgeschrieben werden sollen.
8. Wende die Änderung auf die ausgewählten Dateien an.
9. Führe einen erneuten Scan zur Überprüfung durch.
10. Exportiere Berichte oder führe das Commandlet in der CI aus.

Das Scannen schreibt niemals Quelldateien. Das Anwenden schreibt nur markierte Dateien um, die als änderbar klassifiziert sind.

## Editor-Registerkarten

Das Haupt-Editorfenster ist in fokussierte Registerkarten unterteilt:

| Registerkarte | Zweck |
| --- | --- |
| `Configure` | Vorlagen, Eigentümer-/Lizenzeinstellungen, Scanbereich, Schutzregeln und Projekthinweis-Einstellungen bearbeiten. |
| `Scan & Review` | Scans ausführen, Dateistatus überprüfen, änderbare Dateien auswählen, Dateien ausschließen und vorhandene/vorgeschlagene Hinweise vergleichen. |
| `File Metadata` | Dateibezogene Informationen und Beschreibungen hinzufügen oder löschen, die durch Metadaten-Token gerendert werden. |
| `Apply & Reports` | Ausgewählte Umschreibungen bestätigen und den neuesten Editor-JSON-Scanbericht exportieren. |
| `Help` | Die integrierte Workflow-Anleitung und Statuslegende lesen. |

Die Auswahl der Registerkarte ändert nur die sichtbare Seite. Scan-Ergebnisse, ausgewählte Datei, Metadaten-Entwürfe, Vorschau und Status-Output werden zwischen allen Registerkarten geteilt.

## Statuswerte

| Status | Bedeutung | Anwendungsverhalten |
| --- | --- | --- |
| `OK` | Die Datei entspricht bereits der gerenderten Vorlage. | Nicht erforderlich. |
| `MISSING` | Es wurde kein kompatibler Hinweis gefunden. | Kann eingefügt werden, wenn aktiviert. |
| `REPLACE` | Ein eigener Hinweis oder Unreal-Platzhalter kann ersetzt werden. | Kann umgeschrieben werden. |
| `PROTECTED` | Ein fremder, Epic- oder Drittanbieter-Hinweis wurde gefunden. | Wird nicht automatisch umgeschrieben. |
| `CONFLICT` | Eigene und geschützte Markierungen treten zusammen auf. | Manuelle Überprüfung erforderlich. |
| `EXCLUDED` | Die Datei entspricht einer Ausschlussregel. | Nicht verarbeitet. |
| `READ_ERROR` | Die Datei konnte nicht gelesen werden. | Nicht verarbeitet. |
| `WRITE_ERROR` | Die Datei konnte nicht gespeichert werden. | Nicht verarbeitet. |
| `UPDATED` | Die Datei wurde im letzten Anwendungsdurchlauf geschrieben. | Führe einen erneuten Scan zur Überprüfung aus. |

## Dateibezogene Metadaten

Dateibezogene Metadaten fügen Kontext zu einer einzelnen Datei hinzu, ohne die globale Vorlage zu ändern.

Verfügbare Metadaten:

- `File Information`
- `Description`

Empfohlener Workflow:

1. Scanne Dateien.
2. Wähle eine Datei aus.
3. Gib Dateiinformationen oder eine Beschreibung ein.
4. Klicke auf `Save File Metadata`.
5. Stelle sicher, dass die Vorlage `{FileMetadataBlock}` enthält.
6. Überprüfe die Vorschau.
7. Wende die Änderung auf die Datei an, wenn der gerenderte Hinweis korrekt ist.

`Clear File Metadata` entfernt die gespeicherten Metadaten für die ausgewählte Datei.

## Ausgewählte anwenden (Apply Selected)

Vor dem Anwenden bittet der Editor um Bestätigung. Geschützte und Konflikt-Dateien bleiben unangetastet.

Nach dem Anwenden führt das Tool einen erneuten Scan aus und zeigt Folgendes an:

- Anwendungs-Ergebnis.
- Aktuelles Scan-Ergebnis.
- Aktualisierte Statuszeilen.

Nutze die Quellcodeverwaltung vor Massenumschreibungen. Für ein zusätzliches Sicherheitsnetz beim ersten Durchlauf aktiviere `Create Backup Before Write`.

## Was das Plugin nicht tut

Code Copyright Editor führt folgende Aktionen **nicht** aus:

- Rechtliches Eigentum entscheiden.
- Lizenzrechte gewähren.
- Drittanbieter-Lizenzen validieren.
- Eine Rechtsberatung ersetzen.
- Geschützte Hinweise automatisch umschreiben.
- In gepackten Spielen laufen.

Es bietet einen konsistenten technischen Workflow für Hinweise, Berichte und CI-Prüfungen.

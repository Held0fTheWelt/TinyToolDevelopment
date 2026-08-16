<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/CodeCopyrightEditor/architecture.md -->
# Dokumentation des Code Copyright Editors

Code Copyright Editor hält Quellcode-Header in Unreal Engine-Projekten konsistent. Er kann den Urheberrechtshinweis in den Systemeinstellungen (Project Settings) aktualisieren, den Quellcodebaum scannen, ausgewählte Dateien umschreiben und als Headless-CI-Prüfung ausgeführt werden.

Dieser Ordner enthält die vollständige mit dem Plugin gelieferte Dokumentation.

## Hier starten

- [QUICKSTART.md](QUICKSTART.md): Installation, erster Scan und ein echter Anwendungsdurchlauf mit erwarteten Ergebnissen.
- [UserManual.md](UserManual.md): Vollständiger Editor-Workflow und UI-Bedienung.
- [SettingsReference.md](SettingsReference.md): Jede Einstellung, Standardwerte und empfohlene Ausgangskonfiguration.
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md): Häufige Probleme und Lösungen.
- [FAQ.md](FAQ.md): Fragen und Antworten für Käufer und Fab-Ressourcen.
- [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md): Erklärung zu Drittanbieter-Software (keine enthalten).

## Schneller Editor-Workflow

1. Öffne **Tools > Code Tools > Code Copyright Editor**.
2. Bearbeite die Vorlagen für Quellcode- und Projekthinweise.
3. Verwende **Scan Files**, um die Codebasis zu klassifizieren, ohne Dateien zu schreiben.
4. Überprüfe die Status-Badges und wähle nur die Dateien aus, die umgeschrieben werden sollen.
5. Füge optionale dateibezogene Informationen und Beschreibungen für ausgewählte Dateien hinzu.
6. Verwende **Apply Selected** nach Überprüfung der Vorschau.

## Schnelle Vorlagen-Token

Häufige Token:

- `{CopyrightText}`
- `{OwnerName}`
- `{ContactEmail}`
- `{ProductName}`
- `{ModuleName}`
- `{FileName}`
- `{RelativeFilePath}`
- `{Year}`
- `{LicenseName}`
- `{LicenseUrl}`
- `{LicenseIdentifier}`
- `{FileInformation}`
- `{FileDescription}`
- `{FileMetadataBlock}`

Für REUSE/SPDX-konforme Header halte diese beiden Tags nahe der Oberseite der Vorlage:

```text
/* {CopyrightText}
 * SPDX-FileCopyrightText: {CopyrightText}
 * SPDX-License-Identifier: {LicenseIdentifier}
```

## Commandlet

Führe denselben Scanner über die CI oder ein lokales Terminal aus:

```powershell
UnrealEditor-Cmd.exe "D:\PluginProjectGit\PluginProject.uproject" -run=CodeCopyrightCheck -unattended -nop4 -nosplash -NoShaderCompile -ReportDir="Saved\CodeCopyrightEditor\Reports"
```

Nützliche Schalter:

- `-Fix`: Änderbare Dateien umschreiben, bevor der finale Bericht erstellt wird.
- `-ReportDir=<Path>`: Berichte in ein projektrelatives oder absolutes Verzeichnis schreiben.
- `-FailOnProtected`: Geschützte fremde Hinweise als CI-Fehler behandeln.
- `-NoJson`, `-NoSpdx`, `-NoReuse`: Einzelne Berichtsformate überspringen.
- `-NoFail`: Berichte schreiben, aber immer den Exit-Code `0` zurückgeben.

Standardmäßig schlägt die CI fehl, wenn Dateien geändert würden, Konflikte bestehen oder Dateien nicht gelesen/geschrieben werden konnten. Geschützte Hinweise von Drittanbietern werden gemeldet, führen aber nur dann zum Fehlschlagen des Builds, wenn `-FailOnProtected` gesetzt ist.

## Schnelle Berichte

Das Commandlet schreibt:

- `CodeCopyrightReport.json`: Maschinenlesbare Scan-Zusammenfassung.
- `CodeCopyrightReport.spdx`: Bericht im SPDX 2.3 Tag/Value-Stil.
- `REUSE-Report.md`: Für Menschen lesbarer REUSE/SPDX-Überprüfungsbericht.

## Rechtlicher Hinweis

Code Copyright Editor hilft dabei, Hinweistexte konsistent anzuwenden und zu überprüfen. Er entscheidet nicht über Eigentumsrechte, validiert keine Drittanbieter-Lizenzen, gewährt keine Rechte und ersetzt keine Rechtsberatung.

## Referenzen

- REUSE-Spezifikation 3.3: https://reuse.software/spec-3.3/
- SPDX-Spezifikation 2.3: https://spdx.github.io/spdx-spec/v2.3/
- Unreal Engine UCommandlet-API: https://dev.epicgames.com/documentation/en-us/unreal-engine/API/Runtime/Engine/Commandlets/UCommandlet

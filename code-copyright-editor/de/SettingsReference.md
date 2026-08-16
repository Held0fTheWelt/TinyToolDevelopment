<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/CodeCopyrightEditor/architecture.md -->
# Einstellungsreferenz

Die Einstellungen des Code Copyright Editors befinden sich unter:

```text
Project Settings > Plugins > Code Copyright Editor
```

Das Editor-Fenster bietet außerdem Zugriff auf die wichtigsten Vorlagen- und Workflow-Aktionen.

## Identität

| Einstellung | Standardwert | Verwendet von |
| --- | --- | --- |
| `OwnerName` | `Your Company or Name` | `{OwnerName}`, `{CopyrightText}`, Berichte |
| `ContactEmail` | Leer | `{ContactEmail}` |
| `ProductNameFallback` | `PluginProject` | `{ProductName}`, wenn kein Anzeigename gefunden wird |
| `CopyrightStartYear` | `2025` | `{Year}`, `{CopyrightText}` |

`{Year}` wird als Startjahr gerendert, wenn es dem aktuellen Jahr entspricht. Wenn das aktuelle Jahr abweicht, wird es als Bereich wie `2025-2026` gerendert.

## Lizenz

| Einstellung | Standardwert | Verwendet von |
| --- | --- | --- |
| `LicenseName` | `Fab Standard End User License Agreement` | `{LicenseName}` |
| `LicenseUrl` | `https://www.fab.com/eula` | `{LicenseUrl}` |
| `LicenseIdentifier` | `LicenseRef-Fab-Standard-EULA` | `{LicenseIdentifier}`, Berichte |

Verwende Standard-SPDX-Kennungen für Standardlizenzen, wie z. B. `MIT` oder `Apache-2.0`. Verwende `LicenseRef-*` für benutzerdefinierte oder marktplatzspezifische Lizenzen wie eine Produkt-EULA.

## Vorlagen

| Einstellung | Zweck |
| --- | --- |
| `SourceNoticeTemplate` | Header, der in Quelldateien gerendert wird. |
| `ProjectSettingsNoticeTemplate` | Hinweis, der in das projektspezifische Urheberrechtsfeld von Unreal gerendert wird. |

Das Editorfenster bietet größere mehrzeilige Editoren für beide Vorlagen.

## Scope (Scanbereich)

| Einstellung | Standardwert | Zweck |
| --- | --- | --- |
| `ScanRootPaths` | `Source`, `Plugins` | Von `Scan Files` gescannte Ordner. |
| `SourceFileExtensions` | `.h`, `.hpp`, `.hh`, `.inl`, `.c`, `.cc`, `.cpp`, `.cxx`, `.cs`, `.usf`, `.ush` | Dateiendungen, die als Quelldateien behandelt werden. |
| `ExcludedPathFragments` | `.git`, `.vs`, `Binaries`, `Content`, `DerivedDataCache`, `External`, `Intermediate`, `Resources`, `Saved`, `ThirdParty` | Ordner-/Pfadfragmente, die bei Scans übersprungen werden. |
| `ExcludedFilePaths` | Standardmäßig leer | Exakte projektrelative Dateien, die bei Scans übersprungen werden. |
| `ExcludedFilePatterns` | `*.generated.h` | Platzhalter-Muster, die bei Scans übersprungen werden. |

## Schutz (Protection)

| Einstellung | Standardwert | Zweck |
| --- | --- | --- |
| `ProtectForeignNotices` | Aktiviert | Verhindert, dass unbekannter Hinweistext automatisch umgeschrieben wird. |
| `TreatUnrealDefaultNoticesAsReplaceable` | Aktiviert | Erlaubt das Ersetzen von Unreal-Platzhalter-/Standardhinweisen. |
| `OwnNoticeMarkers` | Eigentümername, Lizenzkennung, Fab-EULA-Text, Unreal-Platzhaltertext | Identifiziert Hinweise, die zu diesem Projekt gehören. |
| `ProtectedNoticeMarkers` | Urheberrechtsmarkierungen von Drittanbietern und Epic | Identifiziert Hinweise, die nicht automatisch umgeschrieben werden sollten. |

## Empfohlene Ausgangskonfiguration

Für die meisten Fab-Plugin-Produkte:

- Halte `ProtectForeignNotices` aktiviert.
- Halte `TreatUnrealDefaultNoticesAsReplaceable` aktiviert.
- Halte `ThirdParty`, `External`, `Binaries`, `Intermediate` und `Saved` ausgeschlossen.
- Verwende `LicenseRef-Fab-Standard-EULA` für Fab-EULA-Produkte.
- Halte SPDX-Zeilen nahe der Oberseite der Quellcode-Vorlage.
- Verwende `{FileMetadataBlock}` für optionalen Kontext auf Dateiebene.

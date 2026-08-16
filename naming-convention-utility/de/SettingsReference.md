<!-- doc-provenance: product-facts.yml reconciled 2026-07-04; source AKDB:plugins/NamingConventionUtility/architecture.md -->
# Einstellungsreferenz

Naming Convention Utility speichert projektweite Einstellungen in `UNamingConventionUtility_Settings`.

## Einstellungsobjekt

Quelldatei:

```text
Source/NamingConventionUtility/Public/NamingConventionUtility_Settings.h
```

Konfigurationsumfang:

```text
Editor
```

Die Einstellungen sind für Editor-Workflows und die Konventionssteuerung auf Projektebene gedacht.

Editor-Ort:

```text
Edit > Project Settings > Plugins > Naming Convention Utility
```

## NamingConventionDataAssetPath

Typ:

```text
FSoftObjectPath
```

Standard:

```text
/NamingConventionUtility/Editor/Data/DA_NamingConvention.DA_NamingConvention
```

Zweck:

- Zeigt auf das DataAsset mit den Umbenennungsregeln.
- Wird vom Ordner-Umbenennungs-Workflow genutzt.
- Wird von der DataTable-Konvertierung als Ziel-Asset genutzt.
- Wird als `project_custom` Workbench-Profil genutzt.

Empfehlung:

- Duplizieren Sie das Standard-DataAsset in Ihr Projekt, wenn Ihr Team explizite Eigentümerschaft wünscht.
- Halten Sie das projektspezifische Asset in der Quellcodeverwaltung.

## bConfirmBeforeApplyingConventions

Standard:

```text
true
```

Zweck:

- Zeigt eine Vorschau an und bittet um Bestätigung vor dem Anwenden von Stapel-Umbenennungen.
- Die Workbench schützt das Anwenden außerdem mit dem überprüften Plan-Hash.

Empfehlung:

- Für den normalen Gebrauch aktiviert lassen.

## bFixRedirectorsAfterRename

Standard:

```text
true
```

Zweck:

- Versucht, Redirectoren in ausgewählten Ordnern nach tatsächlichen Umbenennungen zu korrigieren.

Empfehlung:

- Für kleine und mittlere Umbenennungsstapel aktiviert lassen.

## DataAsset: NamingConventions

Typ:

```text
TArray<FNamingConventions>
```

Jeder Eintrag definiert die Regel für ein `EFileTypeIdentifier`.

Felder:

- `FileTypeIdentifier`: Ziel-Asset-Typ.
- `NamingsToRemove`: alte zu entfernende Fragmente.
- `PreFix`: hinzuzufügendes Präfix.
- `PostFix`: hinzuzufügendes Suffix.

## Workbench-Profile

Die Workbench bietet drei Profiloptionen:

- `epic_recommended`: integrierte schreibgeschützte Epic-konforme Regeln.
- `tiny_legacy`: integrierte schreibgeschützte 1.0.x-kompatible Regeln.
- `project_custom`: das konfigurierte `NamingConventionDataAssetPath`.

Integrierte Profile werden nicht direkt bearbeitet. Nutzen Sie **Copy to Project**, um das konfigurierte Project Custom DataAsset durch ein integriertes Profil zu ersetzen, und bearbeiten Sie dann ausgewählte Regeln.

## Berichte

Workbench-Export/Anwendung schreibt JSON- und Markdown-Berichte unter:

```text
Saved/NamingConventionUtility/Reports/
```

Die Berichte enthalten Profil-Metadaten, Ordnerbereich, Plan-Hash, Konformitätszusammenfassung, ausgewählte Zielpfade, akzeptierte Einträge, übersprungene Einträge und die angewendete Anzahl.

## DataTable-Zeilenfelder

`FNamingConventionTableInformation` unterstützt:

- `FileType`
- `ToolType`
- `Value`

`ToolType` bestimmt, wie `Value` angewendet wird:

- `NCTT_TOREMOVE`: an `NamingsToRemove` anhängen.
- `NCTT_PREFIX`: `PreFix` zuweisen.
- `NCTT_POSTFIX`: `PostFix` zuweisen.

## Empfohlener Grundstandard

Für die meisten Projekte:

```text
bConfirmBeforeApplyingConventions = true
bFixRedirectorsAfterRename = true
NamingConventionDataAssetPath = projekt-eigenes Duplikat des Standard-Assets
```

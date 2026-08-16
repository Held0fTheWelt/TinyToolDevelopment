<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/LogLevelEditor/architecture.md -->
# Einstellungsreferenz

LogLevelEditor speichert seine Konfiguration in `ULogLevelEditor_Settings`.

## Einstellungsobjekt

Quelldatei:

```text
Source/LogLevelEditor/Public/LogLevelEditor_Settings.h
```

Konfigurationsumfang:

```text
EditorPerProjectUserSettings
```

Dies bedeutet, dass viele Einstellungen benutzer-/editor-bezogen sind und keine Gameplay-Laufzeiteinstellungen darstellen.

## LogLevelDataAsset

Typ:

```text
TSoftObjectPtr<ULogLevelDataAsset>
```

Standard:

```text
/LogLevelEditor/DA_LogLevelVerbosity.DA_LogLevelVerbosity
```

Zweck:

- Speichert dauerhafte kategoriebezogene Verbosity-Überschreibungen.
- Wird vom Modul beim Start geladen.
- Wird vom Widget nach erfolgreicher Befehlsausführung aktualisiert.

Empfehlung:

- Nutzen Sie das bereitgestellte Standard-Asset für kleine Projekte.
- Erstellen Sie eine projektspezifische Kopie für strikte Eigentümerschaft in der Quellcodeverwaltung.
- Halten Sie nur beabsichtigte Richtlinien- oder Support-Presets in der gemeinsamen Quellcodeverwaltung.

## bAutoSaveLogLevelDataAsset

Standard:

```text
true
```

Zweck:

- Speichert das DataAsset nach dauerhaften Überschreibungsänderungen automatisch.
- Verringert die Wahrscheinlichkeit, dass ein Benutzer das Speichern nach einer Änderung vergisst.

Empfehlung:

- Für die meisten Teams aktiviert lassen.

## bShowToolbarButton

Standard:

```text
true
```

Zweck:

- Zeigt das Log Level Editor-Kürzel in der Symbolleiste des Level-Editors an.
- Der Menüeintrag **Tools → Log Tools → Log Level Editor** bleibt verfügbar, wenn dieses Kürzel ausgeblendet ist.

## bAlsoListEnginePluginChannels

Standard:

```text
false
```

Zweck:

- Schließt Engine-Plugin-Quellcodeverzeichnisse in den Scanner ein.

Kompromiss:

- Vollständigere Ergebnisse.
- Längere Scanzeit und mehr Kategorien in der Benutzeroberfläche.

## bAlsoListEngineSourceChannels

Standard:

```text
false
```

Zweck:

- Schließt Engine-Quellcodeverzeichnisse in den Scanner ein.

Kompromiss:

- Sehr breite Sichtbarkeit.
- Potenziell sehr viel größere Scans.

## bTemporaryHideLogLevels

Standard:

```text
false
```

Zweck:

- Aktiviert die nur für die Sitzung gültige Ausblendliste.

Speicherung:

- Flüchtige Speicherung (Transient).
- Nicht in der Konfiguration gespeichert.

## LogChannelsToHideTemporary

Zweck:

- Kategorienamen, die nur für die aktuelle Editor-Sitzung ausgeblendet sind.

Beispiel:

```text
LogTemp
LogSlate
LogDerivedDataCache
```

## LogChannelsToHide

Zweck:

- Kategorienamen, die über Sitzungen hinweg ausgeblendet sind.

Empfehlung:

- Sparsam einsetzen. Permanentes Ausblenden kann das spätere Auffinden relevanter Logs erschweren.

## Praktische Basisrefeferenz

Für die meisten Projekte:

```text
bAutoSaveLogLevelDataAsset = true
bAlsoListEnginePluginChannels = false
bAlsoListEngineSourceChannels = false
bTemporaryHideLogLevels = false
```

---
lang: de
title: GameFeaturedClasses Settings Reference
audience: [end_user]
owner_ref: plugin:GameFeaturedClasses
applies_to:
  component: GameFeaturedClasses
contract_ref: plugin:GameFeaturedClasses/module-shell-settings
version:
  since: "1.0"
---
# Einstellungen-Referenz

GameFeaturedClasses 1.0.1 enthält **keine** DeveloperSettings, Konfigurations-`.ini`-Objekte oder bearbeitbare Deskriptoren für hervorgehobene Klassen. Das Laufzeitmodul bietet keine `UPROPERTY`-Einstellungsfläche über die leere Modul-Schnittstelle hinaus.

## Ausgelieferte Oberflächen

| Name | Typ | Standardwert | Wirkung |
| --- | --- | --- | --- |
| Plugin-Aktivierung | Editor-Plugins-Benutzeroberfläche | deaktiviert, bis der Käufer es aktiviert | Lädt das Laufzeitmodul `GameFeaturedClasses`. |
| `FGameFeaturedClassesModule::StartupModule` | Modul-Hook | vom Engine aufgerufen | Modulstart; keine Käufer-Einstellungen. |
| `FGameFeaturedClassesModule::ShutdownModule` | Modul-Hook | vom Engine aufgerufen | Modulshutdown; keine Käufer-Einstellungen. |

## Noch nicht verfügbar

| Erwartete Einstellungsfläche | Status |
| --- | --- |
| Deskriptor-Assets für hervorgehobene Klassen | noch nicht verfügbar |
| Feature-Set-Assets | noch nicht verfügbar |
| Registry-/Auflösungseinstellungen | noch nicht verfügbar |
| Editor-Arbeitsbereichseinstellungen | noch nicht verfügbar |
| `UGameFeaturedClassesSettings` DeveloperSettings | noch nicht verfügbar |
| `Config/DefaultGameFeaturedClasses.ini` | nicht ausgeliefert |

Hier werden keine Einstellungseinträge erfunden. Wenn spätere Paketversionen echte `UPROPERTY`-/DeveloperSettings-Felder hinzufügen, muss diese Referenz im selben Change aus der Quelle aktualisiert werden.

## Verwandte Dokumente

- [UserManual.md](UserManual.md) — aktuelle vs. Ziel-Grenze.
- [QUICKSTART.md](QUICKSTART.md) — Smoke-Check der Aktivierung.
- [FAQ.md](FAQ.md)

## Packaging-Metadaten (keine Laufzeiteinstellungen)

Der `.uplugin`-Deskriptor enthält `Version` / `VersionName` für das Packaging. Diese Felder sind Plugin-Metadaten, keine Laufzeit-DeveloperSettings, und dürfen nicht willkürlich aus Käufer-Dokumentations-Workflows bearbeitet werden.

## Aktualisierungsregel

Jeder zukünftige Einstellungseintrag in dieser Datei muss im selben Dokumentations-Change den Header-Pfad und den Eigenschaftsnamen aus der Quelle zitieren.

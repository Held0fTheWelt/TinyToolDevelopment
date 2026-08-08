# LightweightDummyActorSystem-Dokumentation

LightweightDummyActorSystem (LDAS) ist ein autonomer Runtime-Dienst für Dummy-Aktor-Workflows. MVP 1+2+3 stellt die Module Runtime, Editor und DeveloperTool bereit: Registrierung von Subjekten, Abfrage der Bereitschaft, Policy-gesteuerte Tore für Beförderung/Herabstufung, Darstellung von Dummy-Aktoren, Diagnose, Editor-Inspektor und ein Validate-Befehlslet.

Zielgruppe: Gameplay- und Tools-Ingenieure, die leichte Dummy-Darstellungen mit Policy-gesteuerter Beförderung/Herabstufung benötigen, ohne Peer-Tiny-Tool-Plugins für das Kernpaket zu erfordern.

## Funktionen (ausgeliefert)

- `RegisterSubject` / `RegisterSubjectFromProfile` / `UnregisterSubject`
- `QueryReadiness` → `FLDASReadinessReport`
- `RequestPromotion` / `RequestDemotion`
- `ULDASRepresentationProfile`, `ALDASLightweightDummyActor`, `ULDASDummyActorComponent`
- Editor-Inspektor und `ULDASValidateContractsCommandlet`

## Erste Schritte

1. Aktivieren Sie das Plugin – siehe [QUICKSTART.md](QUICKSTART.md) mit einem Arbeitsbeispiel (Registrierung + Abfrage der Bereitschaft).
2. Konfigurieren Sie ein `ULDASRepresentationProfile`-Datenasset mit echten Distanz-/Cooldown-Werten.
3. Lesen Sie [UserManual.md](UserManual.md) und [SettingsReference.md](SettingsReference.md).

## Verwandte Dateien

- [../README.md](../README.md) — Produktübersicht.
- [../CHANGELOG.md](../CHANGELOG.md) — Versionshistorie.
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md) · [FAQ.md](FAQ.md) · [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md)

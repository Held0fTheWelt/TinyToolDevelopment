# Benutzerhandbuch

LightweightDummyActorSystem (LDAS) ist ein autonomer Runtime-Dienst für Dummy-Aktor-Workflows. MVP 1+2+3 stellt die Module Runtime, Editor und DeveloperTool bereit.

## Implementierte Fähigkeiten

| Fähigkeit | Primäre Typen |
| --- | --- |
| Subjektregistrierung | `ULDASWorldSubsystem::RegisterSubject`, `RegisterSubjectFromProfile`, `UnregisterSubject` |
| Bereitschaftsabfrage | `QueryReadiness` → `FLDASReadinessReport` |
| Beförderung / Degradierung | `RequestPromotion`, `RequestDemotion` mit `ELDASTransitionReason` |
| Dummy-Repräsentation | `ALDASLightweightDummyActor`, `ULDASDummyActorComponent` |
| Profil-Asset | `ULDASRepresentationProfile` |
| Diagnose | `ULDASDiagnosticsSubsystem` |
| Editor-Inspektor | `SLDASRepresentationInspector` |
| Validierung | `FLDASEditorValidationService`, `ULDASValidateContractsCommandlet` |

<!-- image slot: ldas-inspector -->

## Runtime-Flow

1. Rufen Sie `ULDASWorldSubsystem` aus der Welt ab.
2. Registrieren Sie ein Subjekt mit einem Deskriptor oder einem `ULDASRepresentationProfile`.
3. Fragen Sie die Bereitschaft für die gewünschte Repräsentationsart ab.
4. Fordern Sie eine Beförderung oder Degradierung an, wenn Richtlinie und Bereitsigung dies zulassen.
5. Untersuchen Sie Diagnosen / Editor-Inspektor bei der Fehlersuche.

Beförderung und Degradierung sind richtliniengesteuert. Eingebaute Anbieter (`ULDASBuiltInReadinessProvider`, `ULDASBuiltInPromotionPolicy`, `ULDASBuiltInHeavyActorAdapter`) stellen Standardverhalten bereit; Projekte können in unterstützten Builds zusätzliche Anbieter registrieren.

## Editor-Oberflächen

- Repräsentationsinspektor für registrierte Subjekte.
- Editor-Validierungsdienst für Vertragsprüfungen.
- Entwickler-Commandlet für Offline-Validierungsläufe.

## Autarkie und optionale Integrationen

Die Kernmodule Runtime / Editor / DeveloperTool funktionieren ohne peer Tiny Tool-Plugins. Die folgenden Komponenten sind **nur für das Ziel** relevant und müssen bei Fehlen graceful degradieren:

- WarCollection schreibgeschützter Pilot-Adapter
- Multiplayer-Pilot-Beweis
- LightningCore-Entitätsbrücke
- UCM / PIO / BPJ-Automatisierungsbrücken

Behandeln Sie diese Adapter nicht als Einrichtungsvoraussetzungen für das ausgelieferte Kernsystem.

## Verwandte Dokumente

- [QUICKSTART.md](QUICKSTART.md)
- [SettingsReference.md](SettingsReference.md)
- [FAQ.md](FAQ.md)
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md)
- [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md)

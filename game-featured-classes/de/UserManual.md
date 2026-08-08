# Benutzerhandbuch

GameFeaturedClasses stellt derzeit eine leichte Laufzeit-Plugin-Shell für projektspezifische Featured-Gameplay-Klassen bereit.

## Aktuelles Paketverhalten

| Bereich | Status in 1.0.1 |
| --- | --- |
| Laufzeitmodul (`GameFeaturedClasses`) | Ausgeliefert — nur Start/Shutdown. |
| Deskriptor / Verpackung / Symbol / Änderungsprotokoll | Ausgeliefert. |
| Featured-Gameplay-Klassen | noch nicht verfügbar |
| Game-Feature-Aktionen / Feature-Set-Assets | noch nicht verfügbar |
| Laufzeit-Registry / Schnittstellengrenze | noch nicht verfügbar |
| Editor-Arbeitsbereich / Reparatur / Beweisberichte | noch nicht verfügbar |
| Tiny-Tools-Automatisierungsrouten | noch nicht verfügbar |

<!-- image slot: gfc-module-shell -->

## Quellzuordnung

- `Source/GameFeaturedClasses/GameFeaturedClasses.Build.cs` — Modulabhängigkeiten.
- `Source/GameFeaturedClasses/Public/GameFeaturedClasses.h` — `FGameFeaturedClassesModule`-Schnittstelle.
- `Source/GameFeaturedClasses/Private/GameFeaturedClasses.cpp` — Start und Shutdown.

## Verwendung der Shell heute

1. Aktivieren Sie das Plugin (siehe [QUICKSTART.md](QUICKSTART.md)).
2. Bewahren Sie projektspezifische Featured-Klassen in Ihren eigenen Modulen auf, bis dieses Paket sie ausliefert.
3. Dokumentieren oder verlassen Sie sich nicht auf Arbeitsbereich-Menüs, die in diesem Build nicht vorhanden sind.

## Zielarchitektur (informative Angaben, nicht ausgeliefert)

Die interne Produktarchitektur beschreibt eine zukünftige Premium-GameFeature-Arbeitsfläche, auf der Autoren Featured-Klassen und Feature-Sets deklarieren, weltumfassende Aktionen diese registrieren, Verbraucher sie über eine Registry-/Schnittstellengrenze auflösen und Wartungsverantwortliche einen Feature-Graphen scannen, verwaltete Reparaturen vorschauen und Beweisberichte exportieren. Dieses Verhalten ist **nur zielvorgabespezifisch** und darf in 1.0.1 nicht als für Käufer verfügbare Funktionalität betrachtet werden.

## Autarkie

Die Modul-Shell lädt eigenständig. Zukünftige optionale Integrationen mit LightweightDummyActorSystem, Unreal Capability Mesh oder Project Intelligence Orchestrator sind keine Einrichtungsvoraussetzungen für dieses Paket.

## Verwandte Dokumente

- [QUICKSTART.md](QUICKSTART.md)
- [SettingsReference.md](SettingsReference.md)
- [FAQ.md](FAQ.md)
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md)
- [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md)

# FAQ

## Liefert GameFeaturedClasses Gameplay-Klassen?

Nein. Version 1.0.1 ist eine leichte Runtime-Plugin-Shell mit Deskriptor, Modul-Grenze, Packaging-Metadaten, Symbol und Änderungsprotokoll. Das Premium-Verhalten von GameFeature Workbench ist ziel-spezifisch, aber in diesem Paket noch nicht implementiert.

## Ist ein anderes Tiny Tool-Plugin erforderlich?

Nein. Die aktuelle Modul-Shell lädt eigenständig. Zukünftige Integrationen mit LightweightDummyActorSystem, Unreal Capability Mesh oder Project Intelligence Orchestrator sind optionale Zielarchitektur und keine Runtime-Anforderung für dieses Paket.

## Welche Engine-Versionen werden unterstützt?

Die ausgelieferte Release-Matrix zielt auf Unreal Engine 5.4 bis 5.8 ab (Deskriptor `EngineVersion` 5.4.0 in diesem Branch).

## Enthält es Drittanbieter-Software oder externe Dienste?

Nein. Das Paket enthält keine Drittanbieter-Software und erfordert kein Konto, keinen KI-Anbieter oder keine externe Runtime. Siehe [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md).

## Wo erhalte ich Support?

Nutzen Sie `mailto:support@tiny-tool-development.com` (Deskriptor `SupportURL`) oder den Support-Link auf der Fab-Produktseite.

## Warum gibt es kein Einstellungspanel?

Version 1.0.1 stellt keine DeveloperSettings oder Featured-Class-Deskriptoren bereit. Siehe [SettingsReference.md](SettingsReference.md).

## Kann ich die Featured Classes meines Projekts in diesem Plugin-Ordner ablegen?

Nicht für das Shipping als GFC-Inhalt in 1.0.1. Behalten Sie die Gameplay-Klassen Ihres Projekts in Ihren eigenen Modulen, bis ein späteres Paket explizit Featured-Class-Assets ausliefert.

## Wie überprüfe ich, ob die Shell geladen wurde?

Aktivieren Sie das Plugin, starten Sie den Editor neu und bestätigen Sie, dass das `GameFeaturedClasses`-Runtime-Modul vorhanden ist. Siehe das durchgearbeitete Beispiel in [QUICKSTART.md](QUICKSTART.md).

## Wo finde ich die Online-Dokumentation?

https://docs.tiny-tool-development.com/game-featured-classes/

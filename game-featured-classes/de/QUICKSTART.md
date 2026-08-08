---
lang: de
title: GameFeaturedClasses Quick Start
audience: [end_user]
owner_ref: plugin:GameFeaturedClasses
applies_to:
  component: GameFeaturedClasses
preconditions:
  - Unreal Engine project open with the plugin package available
  - Edit > Plugins can enable GameFeaturedClasses
expected_result:
  text: GameFeaturedClasses runtime module is enabled and loads after editor restart.
version:
  since: "1.0"
---
# Schnellstart

Dieser Leitfaden installiert und aktiviert **GameFeaturedClasses** und überprüft, ob das Laufzeitmodul geladen wird. Die Version `1.0.1` ist ein **Modul-Shell**: Sie enthält den Deskriptor, die Paketierungs-Metadaten, das Symbol und die Änderungsprotokolle. Sie liefert jedoch noch keine Gameplay-Klassen, Game-Feature-Aktionen oder eine Editor-Arbeitsfläche.

## Was Sie nach diesem Leitfaden haben werden

Das Plugin ist in Ihrem Projekt aktiviert, und das Laufzeitmodul `GameFeaturedClasses` ist in der Modulliste nach dem Neustart des Editors vorhanden.

## Anforderungen

- Unreal Engine 5.4–5.8 (verpackte Release-Matrix).
- Für die Shell ist kein anderes Tiny-Tool-Plugin erforderlich.
- Keine Drittanbieter-Software, kein Konto und keine externe Laufzeitumgebung. Siehe [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md).

## 1. Installieren und Aktivieren

1. Laden Sie **GameFeaturedClasses** von Fab herunter und fügen Sie es dem Projekt hinzu (oder installieren Sie es im Plugins-Verzeichnis der Engine).
2. Öffnen Sie **Bearbeiten → Plugins**, suchen Sie nach **GameFeaturedClasses**, aktivieren Sie es und starten Sie neu, wenn dazu aufgefordert wird.

## 2. Bestätigen der Modul-Grenze

Überprüfen Sie nach dem Neustart, ob das Laufzeitmodul geladen ist (Ausgabelog / Modul-Manager). Die öffentliche Modulschnittstelle ist `FGameFeaturedClassesModule` in `Source/GameFeaturedClasses/Public/GameFeaturedClasses.h` mit nur `StartupModule` / `ShutdownModule`.

## 3. Durchgeführtes Beispiel: Shell-Rauchtest

1. Erstellen oder öffnen Sie ein Projekt mit Unreal Engine 5.4+.
2. Aktivieren Sie das Plugin wie oben beschrieben und starten Sie neu.
3. Filtern Sie im Ausgabelog nach Modulstartgeräuschen für `GameFeaturedClasses` nach dem Laden.

Es gibt keine UI für die Registrierung von Featured-Klassen und keine Beispiel-Game-Feature-Aktion, die in dieser Paketversion ausgeführt werden kann. Das Aufrufen nicht vorhandener Arbeitsflächenmenüs wird erwartungsgemäß fehlschlagen, da diese Oberflächen **noch nicht verfügbar** sind.

## Erwartetes Ergebnis

- Das Plugin wird unter **Bearbeiten → Plugins** als aktiviert angezeigt.
- Das Laufzeitmodul startet und wird beendet, ohne dass Peer-Tiny-Tool-Plugins erforderlich sind.
- Es werden keine Gameplay-Featured-Class-Assets im Content Browser von diesem Paket angezeigt (keine werden ausgeliefert).

## Nächste Schritte

- Lesen Sie [UserManual.md](UserManual.md) für den aktuellen vs. Ziel-Grenzwert.
- Lesen Sie [FAQ.md](FAQ.md) für Fragen zum Umfang.
- Betrachten Sie das Premium-Verhalten von GameFeature Workbench als Zielarchitektur, bis eine spätere Paketversion diese Klassen und Editor-Oberflächen ausliefert.

## Zu merkende Grenzen

- Fügen Sie keine Projekt-Gameplay-Klassen in diesen Plugin-Ordner ein, in der Erwartung, dass sie als GFC-Inhalt in 1.0.1 ausgeliefert werden.
- Aktivieren Sie keine Peer-Plugins ausschließlich, um eine Arbeitsfläche zu „entsperren“, die noch nicht verpackt ist.
- Wenn eine spätere Version Featured-Klassen ausliefert, aktualisieren Sie diesen Schnellstart mit echten Klassennamen und einem durchgeführten Beispiel aus dieser Veröffentlichung.

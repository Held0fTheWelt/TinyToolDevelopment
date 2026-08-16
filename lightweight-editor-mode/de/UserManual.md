<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/LightweightEditorMode/architecture.md -->
# Benutzerhandbuch

Dieses Handbuch erklärt, wie Sie Lightweight Editor Mode bei der täglichen Arbeit im Unreal Engine Editor einsetzen.

## Zweck

Große Szenen in der Unreal Engine können Editor-Viewports stark belasten, selbst wenn die finale Spiel-Laufzeit akzeptabel ist. Hohe Viewport-Auflösung, Lumen, virtuelle Schatten, volumetrischer Nebel, Echtzeit-Ticking der Viewports und hohe Skalierbarkeitsstufen können während der Bearbeitung wertvolle Frame-Zeiten kosten.

Lightweight Editor Mode bietet einen schnellen Schalter für ein vorübergehendes, umkehrbares Bearbeitungsprofil. Es ist besonders nützlich, wenn Sie Reaktionsschnelligkeit für Layout, Blocking, Blueprint-Arbeiten, Foliage-Pässe, Asset-Platzierung oder Projektbereinigungen benötigen.

## Fenster öffnen

1. Öffnen Sie den Unreal Editor.
2. Stellen Sie sicher, dass das Plugin Lightweight Editor Mode aktiviert ist.
3. Nutzen Sie Tools > Performance > Lightweight Editor Mode.
4. Das Plugin öffnet einen andockbaren Editor-Tab.

Der Tab enthält ein Profil-Dropdown, eine Umschalt-Schaltfläche und ein optionales Start-Kontrollkästchen.

## Profil auswählen

Das Profil steuert, wie aggressiv der Editor die Rendering-Kosten verringert.

### Mild

Mild ist für Projekte gedacht, die nur einen kleinen Anstoß benötigen. Es hält das Viewport-Verhalten näher am Normalzustand und ist eine gute erste Wahl, wenn Sie weiterhin visuellen Kontext benötigen.

Typisches Verhalten:

- Höherer Bildschirmprozentsatz (Screen Percentage).
- Höhere Skalierbarkeit als bei aggressiven Profilen.
- Erzwingt standardmäßig kein Unlit.
- Deaktiviert Viewport-Echtzeit standardmäßig nicht.

### Balanced

Balanced ist die empfohlene Standardeinstellung. Es verringert aufwendige Beleuchtung und Viewport-Kosten, bleibt aber für die allgemeine Bearbeitung praktisch.

Typisches Verhalten:

- Mittlerer Bildschirmprozentsatz.
- Niedrigere Gesamtskalierbarkeit.
- Deaktiviert aufwendige Rendering-Funktionen.
- Erzwingt Unlit und deaktiviert Echtzeit standardmäßig.

### Aggressive

Aggressive ist für schwere Szenen gedacht, in denen die Reaktionsfähigkeit des Viewports wichtiger ist als die visuelle Genauigkeit.

Typisches Verhalten:

- Niedrigerer Bildschirmprozentsatz.
- Niedrige Skalierbarkeit.
- Aufwendige Beleuchtung, Schatten und Nebel deaktiviert.
- Viewports werden in Unlit gezwungen.
- Echtzeit-Ticking der Viewports deaktiviert.

### Extreme

Extreme ist für überlastete Projekte, Laptop-Bearbeitung, große Welten oder Notfall-Reaktionsfähigkeit gedacht. Nutzen Sie es, wenn Sie nur Szenenstruktur und Interaktionsgeschwindigkeit benötigen.

Typisches Verhalten:

- Sehr niedriger Bildschirmprozentsatz.
- Niedrigste Skalierbarkeit.
- Aufwendige Rendering-Funktionen deaktiviert.
- Unlit-Viewports und Bearbeitung ohne Echtzeit.

## Modus aktivieren

1. Wählen Sie ein Profil aus.
2. Klicken Sie auf Enable Lightweight Mode.
3. Das Plugin wendet das aktive Profil an.
4. Viewports werden sofort aktualisiert.

Wenn aktiviert, sichert das Plugin den ursprünglichen Editor-Zustand, den es zur Wiederherstellung benötigt:

- Skalierbarkeits-Qualitätsstufen.
- Geänderte Konsolevariablen-Werte.
- Viewport-Ansichtsmodi, wenn Unlit erzwungen wird.
- Vorübergehende Viewport-Echtzeit-Overrides, wenn Echtzeit deaktiviert wird.

## Profil ändern während der Modus aktiviert ist

Sie können ein anderes Profil wählen, während der Modus bereits aktiv ist. Das Plugin aktualisiert die aktiven Einstellungen und behält die ursprünglichen Sicherungen von vor der Aktivierung des Modus bei. Das bedeutet, dass Disable Lightweight Mode weiterhin den Zustand vor der Aktivierung wiederherstellt, anstatt den Zustand des Zwischenprofils.

## Modus deaktivieren

Klicken Sie auf Disable Lightweight Mode, um den Editor-Zustand wiederherzustellen.

Das Plugin stellt folgendes wieder her:

- Gesicherte Skalierbarkeitsstufen.
- Die Konsolevariablen-Overrides des Plugins. Wenn ein anderes System denselben Wert geändert hat, während der Modus aktiv war, bleibt dieser neuere Wert bestehen.
- Gesicherte Viewport-Ansichtsmodi.
- Vorübergehende Viewport-Echtzeit-Overrides.

Wenn der Editor neu gestartet wurde, bevor der Modus deaktiviert wurde, existieren die Sitzungssicherungen nicht mehr. In diesem Fall nutzt das Plugin den gespeicherten Fallback-Ansichtsmodus aus den Einstellungen und führt nur eine konservative Viewport-Wiederherstellung durch. Wenn dieser veraltete Zustand erkannt wird, zeigt die Umschalt-Schaltfläche Restore Lightweight State.

## Bei Editor-Start aktivieren (Enable on Editor startup)

Das Kontrollkästchen Enable on Editor startup speichert eine Benutzereinstellung. Wenn aktiviert, wartet das Plugin, bis Editor-Viewports existieren, und aktiviert den Lightweight Editor Mode dann automatisch.

Dieses verzögerte Startverhalten ist beabsichtigt. Während des frühen Modulstarts hat Unreal möglicherweise noch keine Editor-Viewport-Clients erstellt, wodurch unmittelbare Viewport-Änderungen übersehen werden könnten. Das Plugin verwendet einen kurzen Ticker und aktiviert den Modus, sobald der Editor bereit ist.

Wenn der automatische Start ausgeführt wird, nachdem eine vorherige Editor-Sitzung beendet wurde, bevor der Modus deaktiviert wurde, führt das Plugin zuerst die konservative Viewport-Wiederherstellung durch und aktiviert anschließend das ausgewählte Profil erneut.

## Empfohlene Workflows

### Level-Blocking

Nutzen Sie Balanced oder Aggressive. Normalerweise benötigen Sie keine finale Beleuchtung, während Sie Räume blocken, Navigation prüfen oder große Gruppen von Actorn bewegen.

### Foliage- oder Weltbearbeitung

Nutzen Sie Aggressive. Große Foliage-Szenen können in der Lit-Ansicht mit Schatten und Echtzeit-Updates sehr aufwendig sein.

### Blueprint- oder Gameplay-Iteration

Nutzen Sie Mild oder Balanced. Behalten Sie genügend visuellen Kontext, während die Editor-Reaktion komfortabler wird.

### Beleuchtungsprüfung

Deaktivieren Sie den Lightweight Editor Mode. Das Plugin blendet Beleuchtungsfunktionen bewusst aus oder reduziert sie, weshalb es nicht für finale visuelle Freigaben geeignet ist.

### Kinematografische Aufnahmen oder Screenshots

Deaktivieren Sie den Lightweight Editor Mode, stellen Sie die Produktions-Skalierbarkeit wieder her und überprüfen Sie die Aufnahme im vorgesehenen Viewport-Modus.

## Project Settings

Öffnen Sie Project Settings > Plugins > Lightweight Editor Mode, um Profile und aktive Werte zu bearbeiten.

Die Profil-Structs sind die Quelle der Wahrheit für Mild, Balanced, Aggressive und Extreme. Die aktiven Werte sind das, was der Runtime-Helper anwendet, wenn der Modus aktiviert ist. Die Benutzeroberfläche kopiert das ausgewählte Profil in die aktiven Werte, bevor der Modus angewendet wird.

## Was Sie visuell erwarten können

Je nach Profil kann der Viewport wie folgt aussehen:

- Niedrigere Auflösung.
- Unlit (unbeleuchtet).
- Weniger detailliert.
- Weniger schattiert.
- Ohne Nebel.
- Keine Echtzeitaktualisierung, bis manuell aktualisiert oder interagiert wird.

Dies wird erwartet. Das Ziel ist Interaktionsgeschwindigkeit, nicht finale Rendering-Qualität.

## Was das Plugin nicht tut

- Es ändert keine Einstellungen für paketierte Spiele zur Laufzeit.
- Es bearbeitet keine Projekt-Renderer-Einstellungen dauerhaft.
- Es überschreibt keine Map-Assets dauerhaft.
- Es ersetzt nicht die Arbeit an Unreal-Skalierbarkeit, LOD, HLOD, Nanite oder Content-Optimierung.
- Es garantiert keine identischen Ergebnisse über alle Engine-Versionen und benutzerdefinierten Renderer-Forks hinweg.

## Praktische Gewohnheit

Nutzen Sie den Lightweight Editor Mode als Bearbeitungsmodus. Deaktivieren Sie ihn vor finalen Prüfungen, vor dem Melden von Rendering-Fehlern und vor dem Erstellen von Marketplace- oder Produktions-Screenshots.

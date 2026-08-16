<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/LightweightEditorMode/architecture.md -->
# Fehlerbehebung

Dieser Leitfaden behandelt häufige Probleme und wahrscheinliche Ursachen.

## Das Plugin-Fenster fehlt

Überprüfen Sie Folgendes:

- Das Plugin ist unter Edit > Plugins aktiviert.
- Das Projekt wurde nach dem Aktivieren des Plugins neu gestartet.
- Das Modul ist im Plugins-Array der .uproject-Datei aufgelistet.
- Sie führen den Editor aus und kein Commandlet.

Das Fenster sollte unter Tools > Performance > Lightweight Editor Mode erscheinen.

## Der Modus aktiviert sich beim Start nicht

Die Start-Aktivierung wartet, bis Editor-Viewport-Clients existieren. In einem langsamen Projekt kann dies nach dem Modulstart einen Moment dauern.

Prüfen Sie:

- Enable on Editor startup ist aktiviert.
- Das Plugin ist im Projekt aktiviert.
- Der Editor hat tatsächlich Level-Editor-Viewports erstellt.
- Die Logs enthalten "Scheduling Lightweight Mode auto-enable".
- Die Logs enthalten später "Auto-enabling Lightweight Mode after editor viewports became available".

Wenn die Einstellung deaktiviert wird, bevor Viewports verfügbar sind, bricht der Ticker selbst ab.

## Bildschirmprozentsatz erscheint unverändert

Editor-Viewports folgen r.ScreenPercentage nicht immer. Lightweight Editor Mode verwendet editor-spezifische Viewport-CVars:

- r.Editor.Viewport.ScreenPercentage
- r.Editor.Viewport.ScreenPercentageMode.RealTime
- r.Editor.Viewport.ScreenPercentageMode.NonRealTime

Wenn der Viewport weiterhin unverändert erscheint, prüfen Sie:

- Den Wert ScreenPercentage des ausgewählten Profils.
- Ob der Viewport einen Engine-Pfad nutzt, der den Bildschirmprozentsatz übersteuert.
- Ob ein anderes Plugin oder ein Konsolenbefehl dieselben Editor-CVars ändert, nachdem Lightweight Editor Mode ausgeführt wurde.

## Viewports bleiben nach dem Deaktivieren auf Unlit

Wiederherstellungen in derselben Sitzung nutzen Pro-Viewport-Sicherungen. Der Fallback nach einem Neustart hat nur den gespeicherten Wert LastViewModeBeforeLightweight.

Versuchen Sie:

1. Öffnen Sie das Plugin-Fenster.
2. Klicken Sie auf Disable Lightweight Mode.
3. Schalten Sie den Viewport bei Bedarf manuell wieder auf Lit zurück.
4. Aktivieren und deaktivieren Sie den Modus erneut in derselben Sitzung, um die normale Wiederherstellung zu bestätigen.

Wenn dies häufig vorkommt, prüfen Sie, ob der Editor geschlossen wird, während der Modus noch aktiv ist.

Nach einem Absturz oder erzwungenen Schließen zeigt die Hauptschaltfläche möglicherweise Restore Lightweight State. Klicken Sie darauf, um die konservative Viewport-Wiederherstellung auszuführen und die veraltete Sitzungsmarkierung zu löschen.

## Echtzeit bleibt deaktiviert

Das Deaktivieren von Echtzeit nutzt das temporäre Echtzeit-Übersteuerungssystem von Unreal. In derselben Editor-Sitzung entfernt Disable die Lightweight-Übersteuerung, anstatt die gespeicherte Echtzeit-Einstellung des Viewports zu ändern.

Wenn Echtzeit weiterhin deaktiviert erscheint, prüfen Sie, ob ein anderes Editor-System eine eigene Echtzeit-Übersteuerung aktiv hat. Aktivieren Sie Echtzeit bei Bedarf manuell über das Viewport-Menü wieder.

## Lumen erscheint weiterhin aktiviert

Prüfen Sie, ob:

- Das ausgewählte Profil bDisableLumen aktiviert hat.
- Das Projekt tatsächlich Lumen verwendet.
- Ein anderes Plugin oder Projektcode Lumen-CVars setzt, nachdem der Modus aktiviert wurde.
- Ein benutzerdefinierter Engine-Branch die relevanten CVars umbenannt oder entfernt hat.

Das Plugin zielt auf:

- r.Lumen.DiffuseIndirect.Allow
- r.Lumen.Reflections.Allow

Fehlende CVars werden übersprungen und im Log auf Verbose-Ebene protokolliert.

## Schatten erscheinen weiterhin aufwendig

bDisableVirtualShadows zielt auf virtuelle Schattenkarten (Virtual Shadow Maps):

- r.Shadow.Virtual.Enable

Dies deaktiviert nicht alle möglichen Schattenkosten in jedem Renderer-Pfad. Wenn Ihre Szene nicht-virtuelle Schatten, benutzerdefinierte Schattensysteme, raygetracte Schatten oder Plugin-Rendering nutzt, sind möglicherweise zusätzliche projektspezifische Anpassungen erforderlich.

## Nebel erscheint weiterhin

bDisableVolumetricFog setzt:

- r.VolumetricFog = 0
- r.Fog = 0

Einige Materialien, Post-Process-Volumes, Himmels-Systeme oder benutzerdefinierte Atmosphäre-Effekte können weiterhin ein nebelförmiges Erscheinungsbild erzeugen.

## Der Editor sieht visuell zu minderwertig aus

Verwenden Sie ein weniger aggressives Profil:

- Wechseln Sie von Extreme zu Aggressive.
- Wechseln Sie von Aggressive zu Balanced.
- Erhöhen Sie ScreenPercentage.
- Erhöhen Sie OverallQuality.
- Deaktivieren Sie Force Unlit für ein benutzerdefiniertes Profil.

Nach dem Ändern des Profils bei aktiviertem Modus aktualisiert der Helper die aktiven Einstellungen automatisch.

## Der Editor ist weiterhin langsam

Lightweight Editor Mode zielt auf die Rendering-Kosten des Viewports ab. Es kann nicht alle Performance-Probleme des Editors beheben.

Andere mögliche Engpässe:

- Asset-Kompilierung.
- Shader-Kompilierung.
- Quellcodeverwaltung-Operationen (Source Control).
- Blueprint-Construction-Scripts.
- Editor Utility Widgets.
- Aufwendige Tick-Logik in Editor-Welten.
- Massive Anzahl an Actorn.
- Festplatten- oder Antiviren-Overhead.

Verwenden Sie Unreal Insights, Stat-Befehle und normales Projekt-Profiling, um Engpässe außerhalb des Renderings zu diagnostizieren.

## Disable stellt eine CVar nicht wieder her

Der Wiederherstellungspfad entfernt die getaggte Übersteuerung des Plugins. Wenn ein anderes System dieselbe CVar geändert hat, während Lightweight Editor Mode aktiv war, bleibt dieser neuere Wert aktiv, anstatt durch die alte Sicherung überschrieben zu werden.

Prüfen Sie das Output Log auf den Namen der CVar. Das Plugin protokolliert Sicherungs- und Wiederherstellungsoperationen.

## Project Settings Seite ist versteckt oder fehlt

Die Einstellungsseite sollte unter Project Settings > Plugins > Lightweight Editor Mode erscheinen.

Wenn sie fehlt:

- Bestätigen Sie, dass das Modul geladen wurde.
- Bestätigen Sie, dass das Settings-Modul verfügbar ist.
- Starten Sie den Editor nach dem Aktivieren des Plugins neu.
- Prüfen Sie, ob kein Plugin-Deskriptor oder Build-Problem das Laden des Moduls verhindert hat.

## Build schlägt nach dem Hinzufügen einer neuen CVar fehl

Häufige Ursachen:

- CVar-Namenskonstante hinzugefügt, aber nicht konsistent verwendet.
- Einstellung zum Profil-Struct hinzugefügt, aber nicht zu den aktiven Feldern.
- UI-Switch-Anweisung für ein neues Profil nicht aktualisiert.
- Fehlendes Include für einen Unreal-Typ.
- Syntaxfehler in einem UPROPERTY-Metadatenblock.

Führen Sie den Editor-Target-Build nach Quellcodeänderungen aus.

## Zu überprüfende Logs

Durchsuchen Sie das Output Log nach:

- [Module]
- [Lightweight]
- Backup CVar
- Restore CVar
- ApplyActiveSettings
- ApplyViewportSettings
- Lightweight mode ENABLED
- Lightweight mode DISABLED

Die Logs sind bewusst explizit gestaltet, damit Supportanfragen die relevante Sequenz enthalten können.

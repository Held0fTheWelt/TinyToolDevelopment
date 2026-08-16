<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/LightweightEditorMode/architecture.md -->
# FAQ (Häufig gestellte Fragen)

Diese FAQ wurde sowohl für Käufer als auch für den Support verfasst. Sie beantwortet Fragen, die ein Benutzer voraussichtlich vor dem Kauf, bei der Ersteinrichtung und bei der Validierung des Wiederherstellungsverhaltens in einem echten Projekt stellen wird.

## Schnelle Antworten

### Was ist Lightweight Editor Mode?

Lightweight Editor Mode ist ein Unreal Editor-Plugin, das die Rendering-Kosten von Editor-Viewports über konfigurierbare Profile vorübergehend reduziert. Es soll das Bearbeiten schwerer Szenen komfortabler machen.

### Handelt es sich um ein Laufzeit-Optimierungs-Plugin?

Nein. Dies ist ein Werkzeug für den Editor-Workflow. Es optimiert nicht Ihr paketiertes Spiel und ersetzt weder Laufzeit-Profiling noch Content-Optimierung.

### Betrifft es paketierte Builds?

Nein. Das Plugin ist reines Editor-Tooling. Es ändert den Zustand der Editor-Sitzung während Sie im Unreal Editor arbeiten, und hat keine beabsichtigte Auswirkung auf paketierte Builds.

### Ändert es mein Projekt dauerhaft?

Nein. Der Modus ist als temporäres Overlay konzipiert. Er sichert die geänderten Werte und stellt sie beim Deaktivieren wieder her. Profileinstellungen werden als Editor-Benutzereinstellungen gespeichert, aber Maps, Assets und Projekt-Renderer-Einstellungen werden durch den normalen Aktivieren/Deaktivieren-Workflow nicht überschrieben.

### Für wen ist es gedacht?

Es ist für Unreal-Benutzer gedacht, die in anspruchsvollen Editor-Szenen arbeiten: große Welten, dichte Umgebungskarten, Lumen-intensive Szenen, nebelreiche Level, große Foliage-Pässe oder Projekte, bei denen der Editor-Viewport bei der täglichen Arbeit träge wird.

## Funktionen und Verhalten

### Was kann das Plugin bei Aktivierung ändern?

Je nach ausgewähltem Profil kann es:

- Den Bildschirmprozentsatz des Editor-Viewports verringern.
- Die allgemeine Skalierbarkeitsqualität verringern.
- Indirekte Lumen-Diffuse-Beleuchtung deaktivieren.
- Lumen-Reflexionen deaktivieren.
- Virtuelle Schattenkarten deaktivieren.
- Volumetrischen Nebel und regulären Nebel deaktivieren.
- Editor-Viewports in den Unlit-Modus zwingen.
- Echtzeit-Rendering in Editor-Viewports deaktivieren.

### Warum sieht der Viewport bei Aktivierung schlechter aus?

Das wird erwartet. Das Plugin tauscht visuelle Treue gegen Editor-Reaktionsfähigkeit ein. Nutzen Sie es während der Bearbeitung von Layout, Struktur, Platzierung oder Blueprint-Logik. Deaktivieren Sie es für finale Beleuchtung, Materialien, Screenshots, Cinematic-Aufnahmen oder visuelle Freigaben.

### Warum wird der Viewport Unlit?

Einige Profile erzwingen Unlit, da Beleuchtung einer der aufwendigsten Teile des Viewport-Renderings sein kann. Sie können jedes Profil bearbeiten und bForceUnlitViewports ausschalten, wenn Sie weiterhin Beleuchtungskontext benötigen.

### Warum schaltet sich Echtzeit aus?

Einige Profile deaktivieren Viewport-Echtzeit, damit Viewports nicht mehr kontinuierlich neu gezeichnet werden. Dies hilft bei schweren Szenen, Laptops und thermisch eingeschränkten Geräten. Sie können dieses Verhalten pro Profil deaktivieren.

### Deaktiviert es Nanite?

Nein. Das Plugin deaktiviert Nanite nicht direkt. Es konzentriert sich auf Screen Percentage, Skalierbarkeit, Lumen, virtuelle Schatten, Nebel, Ansichtsmodus und Echtzeit-Verhalten des Editor-Viewports.

### Ersetzt es Unreal-Skalierbarkeitseinstellungen?

Nein. Es nutzt Skalierbarkeit als einen Teil eines breiteren Editor-Workflows. Unreal-Skalierbarkeit allein deckt nicht jeden Editor-Viewport-Kostenfaktor ab, daher steuert das Plugin auch den Screen Percentage des Editor-Viewports, ausgewählte Renderer-CVars, den Ansichtsmodus und das Echtzeit-Verhalten.

## Profile

### Welche Profile sind enthalten?

Das Plugin enthält vier bearbeitbare Profile:

- Mild
- Balanced
- Aggressive
- Extreme

Balanced ist der empfohlene Ausgangspunkt.

### Kann ich die Profile anpassen?

Ja. Öffnen Sie Project Settings > Plugins > Lightweight Editor Mode. Jedes Profil hat seine eigenen Qualitäts-, Screen-Percentage-, Funktions-Toggles und Viewport-Verhaltensweisen.

### Kann ich das Profil ändern, während der Modus aktiv ist?

Ja. Das Plugin aktualisiert die aktiven Einstellungen sofort und bewahrt die ursprünglichen Sicherungen von vor der Aktivierung des Modus auf. Das Deaktivieren stellt weiterhin den Zustand vor der Aktivierung wieder her, anstatt ein Zwischenprofil.

### Welches Profil sollte ich verwenden?

Nutzen Sie Mild, wenn Sie weiterhin visuellen Kontext benötigen. Nutzen Sie Balanced für die allgemeine Bearbeitung. Nutzen Sie Aggressive für schweres Layout, Foliage oder Weltbearbeitung. Nutzen Sie Extreme, wenn Sie maximale Reaktionsfähigkeit benötigen und visuelle Genauigkeit keine Rolle spielt.

## Wiederherstellung und Sicherheit

### Was wird wiederhergestellt, wenn ich den Modus deaktivierung?

In derselben Editor-Sitzung stellt das Plugin folgendes wieder her:

- Gesicherte Skalierbarkeits-Qualitätsstufen.
- Gesicherte CVar-Werte.
- Viewport-Ansichtsmodi, die vom Plugin geändert wurden.
- Viewport-Echtzeit-Zustände, die vom Plugin geändert wurden.

### Was passiert, wenn der Editor geschlossen wird, während der Modus aktiv ist?

Das normale Herunterfahren des Moduls versucht, den Modus zu deaktivieren. Wenn der Editor abstürzt oder unerwartet beendet wird, gehen In-Memory-Sicherungen verloren. Das Plugin speichert einen Fallback-Ansichtsmodus, um zu verhindern, dass der Viewport nach dem Neustart in Unlit stecken bleibt, kann jedoch nach einem unerwarteten Herunterfahren nicht jeden rein sitzungsbezogenen Wert rekonstruieren.

### Was ist, wenn Viewports nach einem Neustart Unlit bleiben?

Öffnen Sie das Fenster Lightweight Editor Mode und klicken Sie auf Disable Lightweight Mode. Wenn keine Sitzungssicherung verfügbar ist, nutzt das Plugin den gespeicherten Fallback-Ansichtsmodus und versetzt Unlit-Viewports zurück in einen angemessenen Nicht-Unlit-Modus. Bei Bedarf können Sie den Viewport auch manuell über das Viewport-Menü wieder auf Lit zurückschalten.

### Kann ein anderes Plugin dieselben CVars übersteuern?

Ja. Unreal-CVars können durch Projektkonfiguration, Befehlszeile, Geräteprofile, Skalierbarkeit, Plugins und Runtime-Editor-Code geändert werden. Lightweight Editor Mode nutzt eine CVar-Schreiboperation mit Plugin-Prioritätstags und stellt seine eigenen Sicherungen wieder her, aber ein späteres Schreiben durch ein anderes System kann sich dennoch durchsetzen.

### Warum werden fehlende CVars nicht als Fehler behandelt?

Renderer-Funktionen unterscheiden sich je nach Engine-Version, Projekteinstellungen, Plattform und benutzerdefinierten Engine-Branches. Wenn eine CVar nicht existiert, überspringt das Plugin diese und protokolliert die Situation, anstatt den gesamten Modus fehlschlagen zu lassen.

## Kompatibilität

### Welche Unreal Engine-Version wird unterstützt?

Die Implementierung zielt auf Editor-APIs und Renderer-CVars im Stil von Unreal Engine 5.4 ab. Validieren Sie jede Engine-Version, die Sie als unterstützt auflisten möchten, insbesondere neuere Versionen, bei denen sich Renderer-CVars ändern können.

### Funktioniert es mit benutzerdefinierten Engine-Branches?

Es sollte funktionieren, wenn die erforderlichen Editor-APIs und CVars vorhanden sind. Wenn ein benutzerdefinierter Branch Renderer-CVars umbenennt oder entfernt, werden diese spezifischen Toggles möglicherweise übersprungen. Überprüfen Sie das Output Log auf Details.

### Funktioniert es auf Windows, Linux und Mac?

Das Plugin besteht aus reinem Editor-C++-Quellcode und vermeidet plattformspezifischen Runtime-Code. Jede Ziel-Editor-Plattform sollte Dennoch gebaut und getestet werden, bevor der offizielle Support für diese Plattform erklärt wird.

### Läuft es in Commandlets?

Für Commandlets wird kein sinnvoller Workflow bereitgestellt. Das Hauptverhalten hängt von interaktiven Editor-Viewport-Clients, Slate-UI und Editor-Sitzungszustand ab.

## Workflow

### Wie öffne ich es?

Nutzen Sie Tools > Performance > Lightweight Editor Mode im Unreal Editor.

### Wie aktiviere ich es automatisch?

Aktivieren Sie Enable on Editor startup im Plugin-Fenster. Das Plugin wartet, bis Editor-Viewports existieren, und wendet dann das aktuelle Profil an.

### Warum wartet die Start-Aktivierung vor dem Anwenden?

Beim frühen Modulstart hat Unreal möglicherweise noch keine Editor-Viewport-Clients erstellt. Das Plugin nutzt einen kurzen Ticker und aktiviert den Modus, sobald Editor-Viewports verfügbar sind, damit der Viewport-Zustand zuverlässig erfasst und geändert werden kann.

### Sollte ich es den ganzen Tag aktiviert lassen?

Sie können es tun, aber die beste Gewohnheit ist, es für die Reaktionsfähigkeit zu aktivieren und vor visuellen Entscheidungen zu deaktivieren. Beurteilen Sie finale Beleuchtung, Schatten, Nebel, Materialien oder Screenshots nicht bei aktivem Modus.

### Hilft es, wenn mein Engpass bei der Shader-Kompilierung oder Quellcodeverwaltung liegt?

Nein. Das Plugin zielt auf die Rendering-Kosten des Editor-Viewports ab. Es behebt keine Shader-Kompilierung, Asset-Ladevorgänge, Verzögerungen der Quellcodeverwaltung, langsame Festplatten, Virenscans oder aufwendige benutzerdefinierte Editor-Tools.

## Support

### Was sollte ich in eine Supportanfrage aufnehmen?

Fügen Sie hinzu:

- Unreal Engine-Version.
- Betriebssystem.
- Ob die Engine Standard (Stock) oder benutzerdefiniert ist.
- Ausgewähltes Profil.
- Ob das Problem beim Aktivieren, Profilwechsel, Deaktivieren, Starten oder nach einem Neustart aufgetreten ist.
- Zeilen des Output Logs, die "[Lightweight]" enthalten.
- Jedes andere Plugin oder Skript, das Rendering-CVars ändert.

### Wo kann ich prüfen, was das Plugin getan hat?

Öffnen Sie das Unreal Output Log und suchen Sie nach:

- [Lightweight]
- Backup CVar
- Restore CVar
- ApplyActiveSettings
- ApplyViewportSettings
- Lightweight mode ENABLED
- Lightweight mode DISABLED

### Was ist die wichtigste Regel bei der Nutzung?

Nutzen Sie den Lightweight Editor Mode für Bearbeitungsgeschwindigkeit. Deaktivieren Sie ihn für die visuelle Wahrheit.

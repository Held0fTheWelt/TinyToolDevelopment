<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/LightweightEditorMode/architecture.md -->
# Dokumentation zum Lightweight Editor Mode

Lightweight Editor Mode ist ein Unreal Engine-Editor-Plugin, mit dem Artists, Level-Designer, Technical Artists und Programmierer die Rendering-Kosten im Editor vorübergehend reduzieren können, während sie in anspruchsvollen Projekten arbeiten. Es ist als umkehrbares Editor-Workflow-Tool konzipiert: Aktivieren Sie es, wenn ein Viewport zu leistungskritisch wird, arbeiten Sie weiter und deaktivieren Sie es anschließend, um zum vorherigen Editor-Zustand zurückzukehren.

Diese Dokumentation bietet die Tiefe, die von einem marktreifen Editor-Plugin erwartet wird. Sie deckt Käufererwartungen, alltägliche Nutzung, Einstellungen, technisches Verhalten, Validierung, Paketierung und Wartung ab.

## Hier beginnen

- [UserManual.md](UserManual.md) erklärt den normalen Editor-Workflow.
- [BUYER_GUIDE.md](BUYER_GUIDE.md) erklärt, was das Plugin macht und für wen es bestimmt ist.
- [SettingsReference.md](SettingsReference.md) listet jede verfügbare Einstellung auf.
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md) hilft bei der Diagnose häufiger Editor-Fälle.
- [TechnicalOverview.md](TechnicalOverview.md) beschreibt das Runtime-Design.
- [CodeDocumentation.md](CodeDocumentation.md) ordnet Quelldateien dem Verhalten zu.
- [PerformanceTuningReference.md](PerformanceTuningReference.md) hilft beim Anpassen von Profilen.
- [ValidationAndQA.md](ValidationAndQA.md) bietet Schritte zur Test- und Release-Validierung.
- [CompatibilityAndPackaging.md](CompatibilityAndPackaging.md) behandelt Engine- und Paketierungshinweise.
- [FAQ.md](FAQ.md) beantwortet häufig gestellte Fragen.
- [ReleaseChecklist.md](ReleaseChecklist.md) ist die finale Checkliste vor dem Release.

## Was das Plugin ändert

Wenn aktiviert, kann Lightweight Editor Mode folgende editorseitige Optimierungen anwenden:

- Verringern des Editor-Viewport-Bildschirmprozentsatzes (Screen Percentage).
- Verringern der allgemeinen Skalierbarkeitsqualität (Scalability Quality).
- Deaktivieren von indirekter Lumen-Diffuse-Beleuchtung und Lumen-Reflexionen.
- Deaktivieren virtueller Schattenkarten (Virtual Shadow Maps).
- Deaktivieren von volumetrischem Nebel und regulärem Nebel.
- Erzwingen des Unlit-Ansichtsmodus in Editor-Viewports.
- Deaktivieren des Echtzeit-Renderings (Realtime) in Editor-Viewports.

Das genaue Verhalten hängt vom ausgewählten Profil und den bearbeitbaren Profileinstellungen in den Project Settings ab.

## Kern-Designversprechen

Das Plugin ist bewusst umkehrbar gestaltet:

- Es sichert die Skalierbarkeitseinstellungen, bevor sie geändert werden.
- Es sichert geänderte Konsolevariablen (CVars), bevor Plugin-Werte gesetzt werden.
- Es speichert pro-Viewport Ansichtsmodi und Echtzeit-Zustände für die aktive Sitzung.
- Es speichert einen dauerhaften Fallback-Ansichtsmodus für die Wiederherstellung nach einem Neustart.
- Es stellt den Editor-Zustand wieder her, wenn der Modus deaktiviert wird oder das Modul herunterfährt.

Dadurch eignet sich das Plugin ideal für schnelle Leistungsentlastung, während die Hauptprojektkonfiguration unberührt bleibt.

## Schneller Workflow

1. Aktivieren Sie das Plugin unter Edit > Plugins.
2. Öffnen Sie Tools > Performance > Lightweight Editor Mode.
3. Wählen Sie ein Profil: Mild, Balanced, Aggressive oder Extreme.
4. Klicken Sie auf Enable Lightweight Mode.
5. Arbeiten Sie im Editor mit reduzierten Viewport-Kosten.
6. Klicken Sie vor finalen Beleuchtungs-, Material- oder Capture-Arbeiten auf Disable Lightweight Mode.

## Visuelle Leitfäden

Der Ordner Documentation/Screenshots enthält SVG-Workflow-Diagramme:

- [01-workflow-overview.svg](Screenshots/01-workflow-overview.svg)
- [02-profile-and-settings.svg](Screenshots/02-profile-and-settings.svg)
- [03-restore-flow.svg](Screenshots/03-restore-flow.svg)

Diese Diagramme sind Dokumentations-Assets, keine Runtime-UI-Assets.

## Engine-Umfang

Die Implementierung zielt auf Editor-APIs und Rendering-Konsolevariablen im Stil von Unreal Engine 5.4 ab. Das wichtigste Implementierungsdetail ist, dass Editor-Viewports nicht zuverlässig demselben Screen-Percentage-Pfad wie das Game- oder PIE-Rendering folgen. Daher nutzt das Plugin editor-spezifische Screen-Percentage-CVars.

## Sicherheitshinweise

Lightweight Editor Mode ist ein Werkzeug für die Editor-Performance, kein Runtime-Optimierungssystem für finale Builds. Es sollte nicht als einziger Validierungspfad für finale Beleuchtung, Schattierung, Nebel, Materialien oder kinematografische Ausgaben verwendet werden.

Deaktivieren Sie den Modus vor finalen Captures oder visuellen Freigaben und überprüfen Sie die Szene in den vorgesehenen Produktions-Qualitätseinstellungen.

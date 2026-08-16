<!-- doc-provenance: product-facts.yml reconciled 2026-07-01; source AKDB:plugins/AssetLoaderStudio/architecture.md -->
# Schnellstart

## Ziel

Asset Loader Studio öffnen, eine Runtime-Ladeanforderung einreichen, einen Tabellen-Snapshot inspizieren, eine verwaltete Operation vorschauen und erst anwenden, wenn die Vorschau zulässig ist.

## Erster Start

1. Aktivieren Sie **Asset Loader Studio** und starten Sie den Unreal Editor neu, falls Sie dazu aufgefordert werden.
2. Öffnen Sie **Tools > Tiny Tools > Asset Loader Studio**.
3. Wählen Sie für den normalen ersten Start den Modus **Guided**. Verwenden Sie **Simple**, wenn Sie nur eine Inspektion durchführen möchten.
4. Geben Sie einen bekannten vollständigen Objektpfad wie `/Game/Data/DT_Items.DT_Items` oder einen DataAsset-Pfad ein, den Sie kontrollieren, und klicken Sie dann auf **Inspect**.
5. Überprüfen Sie den zurückgegebenen Job-Status, die geladenen Pfade, partielle Fehler, den Abhängigkeitsgraphen und die Diagnosedaten.
6. Erfassen Sie einen Tabellen-Snapshot von einem DataAsset oder einer DataTable, das/die Sie kontrollieren.
7. Öffnen Sie **Validation** und beheben Sie fehlende Assets, doppelte Zeilen, ungültige Verweise oder Berechtigungsablehnungen, bevor Sie eine Mutation versuchen.
8. Verwenden Sie **Preview Operation** für jede Erstellungs-, Duplizierungs-, Umbenennungs-, Retargeting-, Reparatur-, Speicher-, Rollback- oder Löschaktion.
9. Verwenden Sie **Apply Operation** nur, wenn die Vorschau eine zulässige Profilentscheidung, ein akzeptables Risikoniveau und die beabsichtigten Ziel-Assets zur Änderung meldet.
10. Überprüfen Sie den Apply-Bericht und speichern Sie geänderte Pakete über Ihren normalen Unreal-/Quellcode-Verwaltungs-Workflow.

## Blueprint- und Runtime-Einstiegspunkte

- `SubmitLoadRequest` startet eine Runtime-Ladeanforderung und gibt einen Job-Status zurück.
- `CaptureTableSnapshot` liest strukturierte Tabellendaten für Validierung und Graph-Arbeit.
- `PreviewOperation` bewertet eine geplante Mutation vor dem Anwenden gegen ein Berechtigungsprofil.

Halten Sie UCM- und MCP-Integrationen optional; der Workspace und das Runtime-Subsystem bilden den eigenständigen First-Use-Pfad.

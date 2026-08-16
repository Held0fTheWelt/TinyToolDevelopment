<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/PerformancePresetWizard/architecture.md -->
# Benutzerhandbuch

Dieses Handbuch beschreibt den normalen Editor-Workflow für Performance Preset Wizard.

## Den Assistenten öffnen

1. Aktivieren Sie **Performance Preset Wizard** in **Edit > Plugins**.
2. Starten Sie Unreal Editor neu, falls Sie dazu aufgefordert werden.
3. Öffnen Sie **Tools > Performance > Performance Preset Wizard**.

Der Assistent scannt die Asset Registry nach `UPerformancePresetAsset`-Assets und listet die erkannten Voreinstellungen auf.

## Hauptfenster

Der Assistent besteht aus zwei Hauptbereichen:

- Voreinstellungsliste: alle erkannten Performance-Preset-Assets.
- Detailbereich: Name der ausgewählten Voreinstellung, Beschreibung, Skalierbarkeitsstufen, CVar-Überschreibungen, Status-Text und Aktions-Schaltflächen.

Verwenden Sie **Refresh**, wenn neue Voreinstellungs-Assets erstellt, umbenannt, verschoben oder importiert wurden.

## Voreinstellung auswählen

Klicken Sie auf eine Voreinstellung in der Liste, um deren Zusammenfassung zu laden.

## Voreinstellung anwenden

1. Wählen Sie eine Voreinstellung aus.
2. Überprüfen Sie die Zusammenfassung.
3. Klicken Sie auf **Apply Preset**.

Die Reihenfolge der Ausführung:

1. Erfassen eines Wiederherstellungspunkts (Restore Point).
2. Begrenzen der Skalierbarkeitswerte auf den von Unreal unterstützten Qualitätsbereich `0..4`.
3. Anwenden der Skalierbarkeit über `Scalability::SetQualityLevels`.
4. Iterieren über CVar-Überschreibungen.
5. Überspringen ungültiger Einträge.
6. Überspringen von `editor-only`-Einträgen außerhalb des Editor-Kontexts.
7. Rückmeldung in der Statusanzeige und im Benachrichtigungsbereich.

## Vorherige Einstellungen wiederherstellen

Klicken Sie auf **Restore Previous**, um zu den Einstellungen zurückzukehren, die unmittelbar vor dem letzten erfolgreichen Anwenden erfasst wurden.

Das Wiederherstellen umfasst:

- Die vollständige Skalierbarkeitsstruktur vor dem Anwenden.
- Die vorherigen Werte für die spezifischen CVars, die von der Voreinstellung überschrieben wurden.

Das Anwenden einer weiteren Voreinstellung ersetzt den vorherigen Wiederherstellungspunkt.

## Editor-Start-Voreinstellung

Öffnen Sie **Edit > Project Settings > Plugins > Performance Preset Wizard**.

Verfügbare Einstellungen:

- **Apply Preset On Editor Startup**: Aktiviert oder deaktiviert das automatische Anwenden beim Start.
- **Startup Preset**: Soft-Reference auf das Voreinstellungs-Asset, das nach der Initialisierung des Editors angewendet werden soll.

## Laufzeit-Voreinstellungen

Laufzeit-Voreinstellungen verwenden dieselben `UPerformancePresetAsset`-Assets. Spiele wenden diese manuell über `UPerformancePresetRuntimeSubsystem` an.

Typischer Blueprint-Ablauf:

1. Abrufen der aktuellen `GameInstance`.
2. Abrufen des `Performance Preset Runtime Subsystem`.
3. Übergeben eines Voreinstellungs-Assets an `ApplyRuntimePreset`.
4. Aufrufen von `RestoreLatestBackup`, wenn das Anwenden rückgängig gemacht werden soll.

## Laufzeit-Auswahl-Widget

`UPerformancePresetRuntimeSelectorWidget` ist als einfaches UMG-Widget enthalten. Es kann konfigurierte Voreinstellungen auflisten, die ausgewählte Voreinstellung anwenden und die neueste Sicherung wiederherstellen.

Laufzeit-Voreinstellungen, die vom Standard-Widget angezeigt werden, können unter **Project Settings > Plugins > Performance Preset Wizard Runtime** konfiguriert werden.

## Bulk-CVar-Editor

Verwenden Sie den CVar-Texteditor zum Kopieren von Überschreibungen aus Dokumenten oder Konsolensitzungen.

Unterstützte Syntax:

```text
# Kommentarzeilen sind erlaubt
r.ScreenPercentage=85
r.Nanite=1
r.Shadow.Virtual.Enable=1,editor
```

Verwenden Sie **Export**, um das aktuelle Array in den Texteditor zu schreiben, und **Apply**, um den Text zurück in das Asset zu parsen.

## Empfohlene Benennung

Verwenden Sie aussagekräftige Namen:

- `Laptop Dev`
- `Desktop Mid Range 60 FPS`
- `Console Like Review`
- `VR Mobile Stable`
- `Cinematic Capture 4k`

## Entfernen oder Verschieben von Voreinstellungen

Wenn die Start-Voreinstellung nicht mehr angewendet wird, wählen Sie das Asset in den Project Settings erneut aus und speichern Sie die Einstellungen.

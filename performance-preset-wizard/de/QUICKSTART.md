<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/PerformancePresetWizard/architecture.md -->
# Schnellstartanleitung

Diese Anleitung führt Sie von der Installation zu einem konkreten Ergebnis: Eine Leistungsvoreinstellung wird auf Ihren Editor angewendet (Skalierbarkeit + Konsolenvariablen), die Sie mit einem Klick vollständig wiederherstellen können. Performance Preset Wizard arbeitet eigenständig.

## Was Sie nach dieser Anleitung haben

Der geöffneter Assistent mit erkannten Voreinstellungen, eine angewendete Voreinstellung (Skalierbarkeitsstufen + CVar-Überschreibungen) und die Möglichkeit, Ihre vorherigen Einstellungen wiederherzustellen.

## Voraussetzungen

- Unreal Engine 5 Editor. Die Laufzeitanwendung in einem verpackten Spiel ist optional.
- Keine Software von Drittanbietern, Konten oder zusätzlichen Laufzeitumgebungen erforderlich. Siehe [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md).

## 1. Installieren und aktivieren

1. Fügt **Performance Preset Wizard** aus Ihrer Fab-Bibliothek zum Projekt hinzu (oder installieren Sie es in der Engine).
2. Öffnen Sie **Edit → Plugins**, aktivieren Sie **Performance Preset Wizard** und starten Sie den Editor neu, wenn Sie dazu aufgefordert werden.

## 2. Den Assistenten öffnen

1. Öffnen Sie **Tools → Performance → Performance Preset Wizard**.
2. Der Assistent scannt die Asset Registry nach `UPerformancePresetAsset`-Assets und listet sie nach Anzeigenamen, Zielplattform und Asset-Pfad auf.
3. Klicken Sie auf eine Voreinstellung, um deren Detailansicht zu laden.

## 3. Ein praktisches Beispiel: Anwenden und Wiederherstellen

1. Wählen Sie eine mitgelieferte Beispielvoreinstellung aus.
2. Klicken Sie auf **Apply Preset**.

**Erwartetes Ergebnis:** Der Assistent erfasst einen Wiederherstellungspunkt, begrenzt die Skalierbarkeit auf den Bereich `0..4` von Unreal, wendet sie an und wendet anschließend jede CVar-Überschreibung an.

3. Klicken Sie auf **Restore Previous**.

**Erwartetes Ergebnis:** Die Skalierbarkeitsstruktur und die spezifischen CVars, die von der Voreinstellung geändert wurden, werden auf die unmittelbar vor dem Anwenden erfassten Werte zurückgesetzt.

## 4. Eigene Voreinstellungen erstellen

Öffnen Sie ein beliebiges `PerformancePresetAsset` im Content Browser. Das Details-Panel bietet Qualitäts-Dropdowns pro Skalierbarkeitsbereich und einen **Bulk-CVar-Editor**:

```text
# Kommentarzeilen sind erlaubt
r.ScreenPercentage=85
r.Nanite=1
r.Shadow.Virtual.Enable=1,editor
```

`,editor` markiert eine Überschreibung als reinen Editor-Wert. Verwenden Sie **Export**, um das aktuelle Array in den Texteditor zu schreiben, und **Apply**, um es wieder in das Asset zu parsen. Siehe [PresetAuthoringGuide.md](PresetAuthoringGuide.md).

## 5. Optional: Start- und Laufzeitnutzung

- **Editor-Start:** *Project Settings → Plugins → Performance Preset Wizard* → **Apply Preset On Editor Startup** + **Startup Preset**.
- **Verpacktes Spiel:** Wenden Sie Voreinstellungen über `UPerformancePresetRuntimeSubsystem.ApplyRuntimePreset` und `RestoreLatestBackup` an, oder verwenden Sie das enthaltene `UPerformancePresetRuntimeSelectorWidget`. Siehe [RuntimeUsage.md](RuntimeUsage.md).

## 6. Nächste Schritte

- Vollständiger Workflow und Sicherungsverlauf: [UserManual.md](UserManual.md).
- Mitgelieferte Voreinstellungen: [SamplePresetsReference.md](SamplePresetsReference.md).
- Einstellungen: [SettingsReference.md](SettingsReference.md). Probleme: [TROUBLESHOOTING.md](TROUBLESHOOTING.md), [FAQ.md](FAQ.md).

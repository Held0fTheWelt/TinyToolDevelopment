<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/PerformancePresetWizard/architecture.md -->
# Dokumentation für Performance Preset Wizard

Performance Preset Wizard erstellt Laufzeit-Zielleistungsvoreinstellungen (Performance Presets), die im Unreal Editor erstellt und überprüft und anschließend manuell über den Editor-Assistenten, C++, Blueprint oder das mitgelieferte Laufzeit-Auswahl-Widget angewendet werden. Eine Voreinstellung kombiniert Skalierbarkeitsstufen der Engine mit optionalen Konsolenvariablen-Überschreibungen (CVar-Overrides), sodass Teams schnell zwischen Hardware-Stufen, VR-Budgets, Capture-Einstellungen, Laptop-Entwicklungseinstellungen und projektspezifischen Qualitätszielen wechseln können.

Dieser Ordner enthält die vollständige Dokumentation, die mit dem Plugin geliefert wird.

## Beginnen Sie hier

- [BUYER_GUIDE.md](BUYER_GUIDE.md): käuferfreundliche Übersicht, enthaltener Wert und allgemeine Produktionsabläufe.
- [UserManual.md](UserManual.md): vollständiger Editor-Workflow zum Öffnen des Assistenten, Anwenden von Voreinstellungen, Wiederherstellen vorheriger Einstellungen und Konfigurieren von Startvoreinstellungen.
- [RuntimeUsage.md](RuntimeUsage.md): Laufzeit-Subsystem, Blueprint-API, Sicherungsverlauf, Speicheranbieter und Auswahl-Widget.
- [FAQ.md](FAQ.md): praktische Antworten für Fab-Käufer, Designer und Technische Artists.

## Referenz

- [PresetAuthoringGuide.md](PresetAuthoringGuide.md): Erstellung zuverlässiger Voreinstellungen, Auswahl von Skalierbarkeitsstufen und Schreiben von CVar-Überschreibungen.
- [RuntimeUsage.md](RuntimeUsage.md): wie verpackte Spiele Voreinstellungs-Assets manuell anwenden und wiederherstellen können.
- [SettingsReference.md](SettingsReference.md): jede Plugin-Einstellung und jedes Asset-Feld mit Standardwerten und empfohlenen Verwendungen.
- [SamplePresetsReference.md](SamplePresetsReference.md): mitgelieferte `DA_*`-Beispielvoreinstellungen und deren Anpassung.
- [CodeDocumentation.md](CodeDocumentation.md): Quellcode-Layout, öffentliche Verträge, Implementierungshinweise und Erweiterungspunkte.
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md): häufige Einrichtungs-, Asset-, CVar- und Build-Probleme mit Lösungen.

## Enthaltene Assets

- [Screenshots/](Screenshots): Dokumentationsdiagramme, die den Wizard-Workflow, die Voreinstellungserstellung und das Wiederherstellungs-/Startverhalten zeigen.
- `../Content/DA_*.uasset`: Beispiel-Voreinstellungs-Data-Assets für Desktop, VR, Konsolen-ähnliche Szenarien, Prototypen für Mobilgeräte, Laptop-Entwicklung und kinematografische Anwendungsfälle.
- `../PerformancePresetWizard_Changelog.txt`: mit dem Plugin gelieferte Versionshinweise.

## Schneller Editor-Workflow

1. Aktivieren Sie das Plugin und starten Sie den Editor neu, wenn Unreal dazu auffordert.
2. Öffnen Sie **Tools > Performance > Performance Preset Wizard**.
3. Wählen Sie eine Voreinstellung aus der Liste aus. Verwenden Sie **Refresh**, um die Liste zu aktualisieren.
4. Überprüfen Sie Anzeigenamen, Beschreibung, Zielplattform, Skalierbarkeitszusammenfassung und CVar-Überschreibungen.
5. Klicken Sie auf **Apply Preset**. Der Assistent wendet zuerst Skalierbarkeitseinstellungen und dann gültige CVar-Überschreibungen an.
6. Klicken Sie auf **Restore Previous**, um zu den Einstellungen zurückzukehren, die unmittelbar vor dem letzten Anwenden erfasst wurden.
7. Aktivieren Sie **Apply on Editor Startup** in den Project Settings, wenn eine Voreinstellung beim Öffnen des Editors automatisch angewendet werden soll.

## Schneller Laufzeit-Workflow

1. Erstellen und überprüfen Sie `UPerformancePresetAsset`-Voreinstellungen im Editor.
2. Fügt Laufzeit-Voreinstellungen unter **Project Settings > Plugins > Performance Preset Wizard Runtime** hinzu oder übergeben Sie sie direkt an das Laufzeit-Subsystem.
3. Rufen Sie in C++ oder Blueprint `UPerformancePresetRuntimeSubsystem` von der aktuellen `GameInstance` ab.
4. Rufen Sie `ApplyRuntimePreset` für eine explizite Benutzer- oder Projektaktion auf.
5. Verwenden Sie `GetBackupHistory`, `RestoreLatestBackup` oder `RestoreBackupById`, wenn das Projekt eine Rückgängig-Funktion benötigt.
6. Verwenden Sie `UPerformancePresetRuntimeSelectorWidget` als kleines, ersetzbares UMG-Auswahl-Widget für Testmenüs oder Optionenseiten.

## Schnelles CVar-Format

Der Bulk-CVar-Editor akzeptiert eine Überschreibung pro Zeile:

```text
r.ScreenPercentage=85
r.Nanite=1
r.Lumen.Reflections.Allow=0
r.Shadow.Virtual.Enable=1,editor
```

Regeln:

- Leere Zeilen werden ignoriert.
- Zeilen, die mit `#` oder `//` beginnen, werden als Kommentare behandelt.
- `Name=Value` erstellt eine normale Überschreibung.
- `Name=Value,editor` markiert die Überschreibung als reinen Editor-Wert (editor-only).
- Unbekannte CVars werden gemeldet, stoppen das Anwenden der Voreinstellung jedoch nicht.
- Leere Namen oder Werte werden übersprungen.

## Skalierbarkeitsstufen

Performance Preset Wizard folgt der Standard-Qualitätsskala von Unreal Engine:

- `0`: Low
- `1`: Medium
- `2`: High
- `3`: Epic
- `4`: Cinematic

Das Plugin unterstützt aktuelle UE5-Skalierbarkeitsbereiche wie Sichtweite, Antialiasing, Schatten, globale Beleuchtung, Reflexionen, Post-Processing, Texturen, Effekte, Foliage, Shading und Landschaft.

## Wichtige Hinweise zum Umfang

Performance Preset Wizard ist kein Benchmarking-Framework, keine Hardware-Erkennung, kein automatischer Optimizer und kein Ersatz für Device Profiles. Voreinstellungen sollten im Zielprojekt, auf der Karte und in der Zielplattform überprüft werden, bevor sie als Produktionsstandards verwendet werden.

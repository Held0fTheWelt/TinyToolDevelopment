<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/PerformancePresetWizard/architecture.md -->
# FAQ (Häufig gestellte Fragen)

## Ist Performance Preset Wizard ein automatischer Optimizer?

Nein. Es ist ein Werkzeug zum Erstellen und Anwenden von Voreinstellungen. Es führt keine automatischen Hardware-Tests durch.

## Funktionierte es zur Laufzeit?

Ja, verpackte Spiele können Voreinstellungen manuell über `UPerformancePresetRuntimeSubsystem`, Blueprint, C++ oder das mitgelieferte UMG-Widget anwenden.

## Werden beim Anwenden einer Voreinstellung Projekteinstellungen gespeichert?

Nein. Es ändert den aktuellen Engine-/Laufzeitstatus über Skalierbarkeits- und CVar-APIs.

## Kann ich ein Anwenden rückgängig machen?

Im Editor-Assistenten können Sie **Restore Previous** verwenden. Zur Laufzeit stehen `RestoreLatestBackup` oder `RestoreBackupById` zur Verfügung.

## Was passiert, wenn eine CVar nicht existiert?

Das Plugin protokolliert dies als fehlend und wendet die restlichen Einstellungen der Voreinstellung an.

## Warum werden CVar-Werte als Strings gespeichert?

Konsolenvariablen können Integer, Floats, Booleans oder Text sein. Ein String-Feld deckt alle Typen ab.

## Was bedeutet "Editor Only"?

Eine `editor-only` Überschreibung wird nur im Editor-Kontext angewendet und in verpackten Spielen übersprungen.

## Ersetzt das Plugin Device Profiles?

Nein. Device Profiles sind weiterhin der richtige Ort für plattformspezifische Richtlinien. Performance Preset Wizard eignet sich für benutzer- oder projektspezifische Leistungsmodi.

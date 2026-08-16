<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/PerformancePresetWizard/architecture.md -->
# Einstellungsreferenz

Diese Referenz listet die Plugin-Einstellungen und Asset-Felder auf.

## Projekteinstellungen

Öffnen Sie **Edit > Project Settings > Plugins > Performance Preset Wizard**.

| Einstellung | Typ | Standard | Beschreibung |
| --- | --- | --- | --- |
| Apply Preset On Editor Startup | Boolean | `false` | Wenn aktiviert, wird die ausgewählte Startvoreinstellung angewendet, sobald der Editor die Initialisierung abgeschlossen hat. |
| Startup Preset | Soft Object Pointer | Leer | Das beim Editor-Start anzuwendende `UPerformancePresetAsset`. Als Soft-Reference gespeichert. |

## Laufzeit-Projekteinstellungen

Öffnen Sie **Edit > Project Settings > Plugins > Performance Preset Wizard Runtime**.

| Einstellung | Typ | Standard | Beschreibung |
| --- | --- | --- | --- |
| Max Backup History | Integer | `10` | Maximale Anzahl von Laufzeit-Sicherungseinträgen. Begrenzt auf `1..100`. |
| Runtime Preset Library | Array von Soft Object Pointers | Leer | Voreinstellungs-Assets, die vom Standard-Laufzeit-Auswahl-Widget angezeigt und vom Laufzeit-Subsystem geladen werden. |
| Storage Provider Class | Class | `PerformancePresetGameUserSettingsStorage` | Vom Laufzeit-Subsystem verwendeter Speicheranbieter. |

## Asset-Felder einer Voreinstellung

Voreinstellungs-Assets verwenden die Klasse `UPerformancePresetAsset`.

| Feld | Typ | Standard | Beschreibung |
| --- | --- | --- | --- |
| Display Name | `FText` | Leer | Lesbarer Name, der im Assistenten angezeigt wird. Verwender den Asset-Namen als Fallback, wenn leer. |
| Description | `FText` | Leer | Kurze Erklärung des Zielgeräts oder Anwendungsfalls. |
| Target Platform | Enum | Desktop Mid Range | Gruppierungs- und Sortierungshinweis. |
| View Distance Quality | Integer | `2` | Skalierbarkeitsstufe für Sichtweite. |
| Anti-Aliasing Quality | Integer | `2` | Skalierbarkeitsstufe für Antialiasing. |
| Shadow Quality | Integer | `2` | Skalierbarkeitsstufe für Schatten. |
| Global Illumination Quality | Integer | `2` | Skalierbarkeitsstufe für globale Beleuchtung. |
| Reflection Quality | Integer | `2` | Skalierbarkeitsstufe für Reflexionen. |
| Post Process Quality | Integer | `2` | Skalierbarkeitsstufe für Post-Processing. |
| Texture Quality | Integer | `2` | Skalierbarkeitsstufe für Texturen. |
| Effects Quality | Integer | `2` | Skalierbarkeitsstufe für Effekte. |
| Foliage Quality | Integer | `1` | Skalierbarkeitsstufe für Foliage. |
| Shading Quality | Integer | `2` | Skalierbarkeitsstufe für Shading. |
| Landscape Quality | Integer | `2` | Skalierbarkeitsstufe für Landschaft. |
| CVar Overrides | Array | Leer | Zusaetzliche Konsolenvariablen-Überschreibungen. |

Alle Qualitätsfelder sind auf den Bereich `0..4` begrenzt:

- `0`: Low
- `1`: Medium
- `2`: High
- `3`: Epic
- `4`: Cinematic

## CVar-Überschreibungsfelder

Jedes `FPerformanceCVarOverride` enthält:

| Feld | Typ | Beschreibung |
| --- | --- | --- |
| Name | `FString` | Name der Konsolenvariable, z. B. `r.ScreenPercentage`. |
| Value | `FString` | Wert, der an die CVar übergeben wird. |
| Editor Only | Boolean | Wenn `true`, wird die Überschreibung nur im Editor angewendet. |

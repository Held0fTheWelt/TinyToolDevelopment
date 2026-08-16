<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/PerformancePresetWizard/architecture.md -->
# Settings Reference

This reference lists the plugin settings and preset asset fields.

## Project Settings

Open **Edit > Project Settings > Plugins > Performance Preset Wizard**.

| Setting | Type | Default | Description |
| --- | --- | --- | --- |
| Apply Preset On Editor Startup | Boolean | `false` | When enabled, the selected startup preset is applied after the editor engine finishes initialization. |
| Startup Preset | Soft object pointer | Empty | The `UPerformancePresetAsset` to apply on editor startup. Stored as a soft reference so the setting can survive editor restarts and normal asset moves. |

## Startup Application Behavior

Startup application is deliberately deferred until the editor engine is initialized. This avoids touching scalability or CVars too early during module startup.

If startup application is enabled but no startup preset is assigned, the plugin logs a warning and does nothing.

If the soft pointer cannot load the asset, the plugin logs a warning and leaves the current editor settings unchanged.

## Runtime Project Settings

Open **Edit > Project Settings > Plugins > Performance Preset Wizard Runtime**.

| Setting | Type | Default | Description |
| --- | --- | --- | --- |
| Max Backup History | Integer | `10` | Maximum number of runtime backup entries kept newest-first. Clamped to `1..100`. |
| Runtime Preset Library | Array of soft object pointers | Empty | Preset assets exposed by the default runtime selector widget and loaded by the runtime subsystem as its available preset list. |
| Storage Provider Class | Class | `PerformancePresetGameUserSettingsStorage` | Storage provider used by the runtime subsystem unless a project installs a custom provider at runtime. |

Runtime settings do not auto-apply a preset on startup. They only configure the manual runtime API, backup history, default storage, and optional selector widget list.

## Preset Asset Fields

Preset assets use the `UPerformancePresetAsset` class.

| Field | Type | Default | Description |
| --- | --- | --- | --- |
| Display Name | `FText` | Empty | Human-readable name shown in the wizard list and detail pane. Falls back to the asset name when empty. |
| Description | `FText` | Empty | Short explanation of the target device, quality goal, or production use case. Multi-line text is supported. |
| Target Platform | Enum | Desktop Mid Range | Grouping and sorting hint. It does not restrict where the preset can be applied. |
| View Distance Quality | Integer | `2` | Unreal scalability level for view distance. |
| Anti-Aliasing Quality | Integer | `2` | Unreal scalability level for anti-aliasing. |
| Shadow Quality | Integer | `2` | Unreal scalability level for shadows. |
| Global Illumination Quality | Integer | `2` | Unreal scalability level for GI, including Lumen where supported. |
| Reflection Quality | Integer | `2` | Unreal scalability level for reflections. |
| Post Process Quality | Integer | `2` | Unreal scalability level for post-processing. |
| Texture Quality | Integer | `2` | Unreal scalability level for textures and streaming behavior. |
| Effects Quality | Integer | `2` | Unreal scalability level for particles and visual effects. |
| Foliage Quality | Integer | `1` | Unreal scalability level for foliage and grass density/culling. |
| Shading Quality | Integer | `2` | Unreal scalability level for shading and material cost. |
| Landscape Quality | Integer | `2` | Unreal scalability level for landscape rendering. |
| CVar Overrides | Array | Empty | Additional console variable overrides applied after scalability. |

All quality fields are clamped and displayed in the `0..4` range:

- `0`: Low
- `1`: Medium
- `2`: High
- `3`: Epic
- `4`: Cinematic

## Target Platform Values

| Value | Intended Use |
| --- | --- |
| Cinematic Capture 4k | Offline capture or very high-quality rendering workflows. |
| Cinematic Menu / Showcase | In-engine menus, showrooms, and presentation scenes. |
| Desktop Ultra High End | Top-tier desktop hardware. |
| Desktop High End | Strong gaming desktops. |
| VRHeadset PC | PC-driven VR with strict frame pacing. |
| Desktop Mid Range | Common gaming PCs and default review workflows. |
| VRHeadset Mobile | Standalone or mobile VR budgets. |
| Console Like | Fixed-budget console-style review. |
| Desktop Low Range | Older or limited desktop hardware. |
| Laptop Development | Thermally or power-constrained editor work. |
| Mobile Prototype | Early mobile gameplay or feature prototyping. |
| Custom 1..5 | Project-specific tiers. |

## CVar Override Fields

Each `FPerformanceCVarOverride` contains:

| Field | Type | Description |
| --- | --- | --- |
| Name | `FString` | Console variable name, for example `r.ScreenPercentage`. Whitespace is trimmed before use. |
| Value | `FString` | Value passed to the CVar. Strings are used so ints, floats, bools, and text-like values can share one representation. |
| Editor Only | Boolean | When true, the override is applied only in editor contexts and skipped elsewhere. |

## Apply Result Counters

When a preset is applied, `FPerformancePresetApplyResult` reports:

| Counter | Meaning |
| --- | --- |
| Applied Scalability | True when scalability was applied. |
| Applied CVar Count | CVars found and set. |
| Skipped Editor-Only CVar Count | Editor-only entries skipped outside editor contexts. |
| Missing CVar Count | Non-empty names that did not resolve to a registered CVar. |
| Invalid CVar Count | Empty names or values skipped after trimming. |

These counters drive the wizard status text and make partial success visible.

## Runtime Backup Structs

Runtime backup history uses `FPerformancePresetBackupEntry`.

| Field | Description |
| --- | --- |
| Backup Id | Stable id used by `RestoreBackupById`. |
| Created Utc | UTC timestamp written when the backup was captured. |
| Applied Preset Path | Preset path that was applied after the backup was captured. |
| Previous Active Preset Path | Active preset path before the apply. |
| Quality Snapshot | Scalability values captured before the apply. |
| CVar Values | Previous values for existing CVars touched by the preset. |


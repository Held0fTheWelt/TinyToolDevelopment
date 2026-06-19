# Settings Reference

Lightweight Editor Mode stores settings in EditorPerProjectUserSettings and
exposes them under Project Settings > Plugins > Lightweight Editor Mode.

## Settings model

The settings object has three layers:

- High-level options such as startup behavior and selected profile index.
- Active runtime values consumed by the mode when it is enabled.
- Four editable profile structs: Mild, Balanced, Aggressive, and Extreme.

The Slate UI copies the selected profile into the active runtime values before
enabling or refreshing the mode.

## High-level options

### bEnableOnStartup

Enables Lightweight Editor Mode automatically when the editor starts.

Implementation notes:

- The module does not enable immediately during StartupModule.
- It starts a short ticker.
- The ticker waits until GEditor has editor viewport clients.
- The mode is enabled only after viewports are available.
- Stale session recovery runs before auto-enable if the previous editor session
  ended while Lightweight Mode was still active.

This avoids losing viewport changes during early editor startup.

### AggressivenessLevel

Stores the currently selected profile index.

| Value | Profile |
| --- | --- |
| 0 | Mild |
| 1 | Balanced |
| 2 | Aggressive |
| 3 | Extreme |

The value is clamped to the valid range.

## Active runtime values

These values are applied by FEditorLightweightMode.

### OverallQuality

A single Unreal scalability quality level.

| Value | Meaning |
| --- | --- |
| 0 | Low |
| 1 | Medium |
| 2 | High |
| 3 | Epic |
| 4 | Cinematic |

The plugin clamps this value to 0..4 before applying it.

### ScreenPercentage

Target screen percentage for editor viewport rendering and PIE/game preview
paths.

| Range | Meaning |
| --- | --- |
| 25..59 | Very aggressive, low visual fidelity |
| 60..79 | Performance-oriented editing |
| 80..99 | Balanced editing |
| 100 | Full internal resolution |
| 101..200 | Supersampling, rarely useful for lightweight mode |

The plugin clamps this value to 25..200.

Important implementation detail: editor viewports use editor-specific screen
percentage CVars. The plugin sets:

- r.Editor.Viewport.ScreenPercentage
- r.Editor.Viewport.ScreenPercentageMode.RealTime
- r.Editor.Viewport.ScreenPercentageMode.NonRealTime

It also sets r.ScreenPercentage for PIE and game-preview paths where that CVar
is still relevant.

### bDisableLumen

Disables Lumen diffuse indirect lighting and Lumen reflections while the mode is
active.

CVars:

- r.Lumen.DiffuseIndirect.Allow = 0
- r.Lumen.Reflections.Allow = 0

When disabled in the profile, the plugin restores any existing backups for
these CVars by removing its tagged override. If another source changed the same
CVar while Lightweight Mode was active, that newer value remains active.

### bDisableVirtualShadows

Disables virtual shadow maps.

CVar:

- r.Shadow.Virtual.Enable = 0

This can make heavy Nanite and large-world scenes more responsive, but it also
changes shadow appearance significantly.

### bDisableVolumetricFog

Disables volumetric fog and regular fog.

CVars:

- r.VolumetricFog = 0
- r.Fog = 0

This is useful in atmospheric scenes where fog dominates editor frame time.

### bForceUnlitViewports

Switches editor viewports to Unlit while the mode is active.

The plugin stores the original view mode per viewport before switching it. When
the mode is disabled in the same editor session, the original view modes are
restored.

### bDisableViewportRealtime

Turns off realtime rendering in editor viewports while the mode is active.

The plugin uses Unreal's temporary realtime override system instead of changing
the viewport's persistent realtime setting. When disabled, it removes its own
override.

## Per-profile values

Each profile contains the same fields:

- OverallQuality
- ScreenPercentage
- bDisableLumen
- bDisableVirtualShadows
- bDisableVolumetricFog
- bForceUnlitViewports
- bDisableViewportRealtime

Profiles are editable in Project Settings. Changing a profile does not
immediately apply it unless the UI copies that profile into the active values.

## LastViewModeBeforeLightweight

This hidden-visible setting stores the last view mode observed before enabling
the mode. It is used as a persistent fallback after editor restart.

Same-session restore uses per-viewport backups first. Restart recovery cannot
use those in-memory backups, so the fallback value is used only to move Unlit
viewports back to a reasonable non-Unlit mode.

## bWasLightweightModeActiveLastSession

This visible diagnostic setting records whether Lightweight Mode was active
before the editor last exited. It is set when Enable starts applying overrides
and cleared by Disable.

If it is still true after restart, the UI offers Restore Lightweight State and
startup auto-enable restores the stale viewport state before enabling again.

## Default profile intent

| Profile | Intent |
| --- | --- |
| Mild | Slight relief while retaining visual context |
| Balanced | Recommended default for general editing |
| Aggressive | Heavy-scene editing where responsiveness wins |
| Extreme | Emergency or very low-resource editing |

## Recommended customization

For art-heavy teams, make Mild less destructive and leave Lit view active. For
large-world or laptop workflows, make Balanced more aggressive. For technical
debugging, keep at least one profile that does not force Unlit so render issues
can still be inspected quickly.

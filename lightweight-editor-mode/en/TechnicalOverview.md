# Technical Overview

This document describes how Lightweight Editor Mode is structured internally.

## Module layout

The plugin has one editor module:

- Module name: LightweightEditorMode
- Module type: Editor
- Primary module class: FLightweightEditorModeModule
- Runtime helper: FEditorLightweightMode
- UI widget: SLightweightEditorModeWidget
- Settings object: ULightweightEditorModeSettings

The module registers editor UI and settings. The helper owns all runtime
application and restore behavior.

## Data flow

1. User selects a profile in SLightweightEditorModeWidget.
2. The widget writes AggressivenessLevel.
3. The widget copies the selected profile into active settings.
4. The user enables the mode.
5. FEditorLightweightMode reads active settings.
6. FEditorLightweightMode backs up existing state.
7. The helper applies scalability, CVars, and viewport behavior.
8. When disabled, the helper restores backed-up state.

## Why profiles copy into active fields

The settings object has editable profile structs and active runtime fields. This
separation keeps the UI simple and lets advanced users inspect or override the
exact values that will be applied.

The selected profile is not applied directly every frame. It is copied into the
active fields when:

- The user clicks Enable Lightweight Mode.
- The user changes profile while the mode is already enabled.

## CVar backup contract

The helper backs up every CVar before it changes that CVar.

Each backup stores:

- The original string value.
- The original SetBy priority flags for diagnostics.

The plugin sets values with ECVF_SetByPluginHighPriority and the tag
LightweightEditorMode. This makes the plugin's override explicit and allows the
restore path to first unset that tagged override.

Restore sequence:

1. Unset the plugin-priority value.
2. Read the value now exposed by Unreal's console manager.
3. If that value matches the backup, the original value is restored.
4. If it differs, another source changed the CVar while the mode was active, so
   the newer value is left in place and logged.

This is more robust than simply writing the old string value with a generic
priority, because Unreal console variables can be influenced by project config,
device profiles, command line, scalability, plugins, and runtime code.

## Scalability backup contract

Scalability is backed up once when the mode is enabled. The helper stores the
current Scalability::FQualityLevels and restores those levels when the mode is
disabled.

Scalability backup is session-only. It is not persisted across editor restarts.
This is intentional because restoring stale scalability after restart could
overwrite legitimate startup configuration.

## Viewport backup contract

Viewports are handled separately from scalability and CVars because they are
represented by editor viewport clients.

When forcing Unlit:

- The helper stores each viewport's original EViewModeIndex.
- It then switches the viewport to VMI_Unlit.

When disabling realtime:

- The helper records that the viewport received a Lightweight override.
- It adds an Unreal realtime override that requests non-realtime rendering.

When disabling the mode in the same session:

- Stored view modes are restored to their original values.
- Lightweight realtime overrides are removed.
- Backup maps are cleared.

While viewport overrides are active, a lightweight ticker periodically reapplies
viewport settings. This catches editor viewports opened after the mode was
enabled and prunes stale viewport-client pointers from the session maps.

## Restart fallback

Per-viewport backups are in-memory only. If the editor restarts while viewports
were left in Unlit, the helper cannot know every original viewport state.

To reduce the chance of a user being stuck in Unlit, the plugin stores
LastViewModeBeforeLightweight in settings before enabling. If Disable is called
without active session backups, the helper switches Unlit viewports back to that
fallback mode. If the fallback is also Unlit, it uses Lit.

This fallback is conservative: it only changes viewports that are still Unlit.

The settings also persist bWasLightweightModeActiveLastSession. Enable sets this
marker before applying overrides, and Disable clears it. If the editor exits
before Disable runs, the UI shows Restore Lightweight State on the next startup.

## Editor viewport screen percentage

Editor viewports do not reliably use r.ScreenPercentage. The implementation
uses Unreal's editor viewport CVars:

- r.Editor.Viewport.ScreenPercentage
- r.Editor.Viewport.ScreenPercentageMode.RealTime
- r.Editor.Viewport.ScreenPercentageMode.NonRealTime

The mode values are forced to manual screen percentage mode, then the configured
screen percentage is applied. r.ScreenPercentage is still set for PIE and game
preview paths.

## Auto-enable timing

StartupModule can run before editor viewports exist. If the plugin enabled
immediately, viewport changes might not apply.

The module therefore starts a short FTSTicker task when bEnableOnStartup is
true. The ticker keeps running until:

- Settings are no longer available or startup enable was disabled.
- GEditor has at least one viewport client.

Once viewports exist, the ticker enables the mode and removes itself.

If a stale Lightweight session marker is present during startup auto-enable, the
module first runs the conservative viewport restore, then applies the selected
profile and enables the mode again.

## Module shutdown

ShutdownModule removes the auto-enable ticker if it is still active. If
Lightweight Editor Mode is enabled, it disables the mode before unregistering UI
and settings. This prevents plugin unload from leaving session CVars or
viewport state behind.

## Thread and lifetime assumptions

The plugin runs on the editor thread. It assumes GEditor and editor viewport
clients are accessed from normal editor module and Slate callbacks.

The backup maps use FEditorViewportClient pointers. They are only valid for the
current editor session and are cleared on restore.

## Error handling

Missing CVars are logged at Verbose level and skipped. This lets the plugin run
across engine configurations where a feature is unavailable or compiled out.

Restore paths log whether the original value came back or a newer value from
another source was kept.

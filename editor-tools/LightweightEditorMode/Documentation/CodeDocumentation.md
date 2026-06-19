# Code Documentation

This document maps the Lightweight Editor Mode source code to behavior and
highlights the invariants that future maintainers should preserve.

## Source layout

| File | Responsibility |
| --- | --- |
| Source/LightweightEditorMode/Public/LightweightEditorMode.h | Module interface and editor integration declarations |
| Source/LightweightEditorMode/Private/LightweightEditorMode.cpp | Module startup, shutdown, tab registration, menu registration, startup ticker |
| Source/LightweightEditorMode/Public/EditorLightweightMode.h | Public contract for applying and restoring the lightweight mode |
| Source/LightweightEditorMode/Private/EditorLightweightMode.cpp | Runtime implementation for scalability, CVars, viewport state, and restore logic |
| Source/LightweightEditorMode/Public/LightweightEditorModeSettings.h | Settings UObject and editable profile structs |
| Source/LightweightEditorMode/Public/SLightweightEditorModeWidget.h | Slate widget API |
| Source/LightweightEditorMode/Private/SLightweightEditorModeWidget.cpp | Slate UI, profile selection, toggle behavior, startup checkbox |
| Source/LightweightEditorMode/Private/Tests/LightweightEditorModeSettingsTests.cpp | Automation coverage for profile-to-active settings copy behavior |

## FLightweightEditorModeModule

The module class owns editor integration. It should not directly set renderer
CVars or scalability. Its job is to expose the plugin to the editor and invoke
the runtime helper when requested.

StartupModule performs:

- RegisterSettings
- RegisterTabSpawner
- RegisterMenus
- Optional StartAutoEnableWhenReady

ShutdownModule performs:

- Remove pending auto-enable ticker.
- Disable the lightweight mode if active.
- Unregister tab spawner.
- Unregister settings.
- Unregister ToolMenus owner entries.

### Auto-enable invariant

Do not call FEditorLightweightMode::Enable directly from StartupModule for the
startup setting. Use the ticker path so editor viewports exist before viewport
state is captured or changed.

## SLightweightEditorModeWidget

The widget is deliberately thin. It has three responsibilities:

- Present profile options and toggle controls.
- Persist user choices in ULightweightEditorModeSettings.
- Call FEditorLightweightMode for actual apply and restore behavior.

It should not contain renderer-specific CVar names. Keep those in
EditorLightweightMode.cpp so restore logic and feature mapping stay in one
place.

### Profile selection behavior

OnAggressivenessSelectionChanged stores the selected index, copies the profile
into active settings, saves config, and refreshes the active mode if needed.

This live refresh is important. Without it, changing the profile while the mode
is enabled would update the UI and config but not the current editor state.

## ULightweightEditorModeSettings

The settings object is stored in EditorPerProjectUserSettings. That storage
class is appropriate because the plugin controls editor behavior for the local
user rather than a packaged runtime feature.

### Profile structs

FLightweightProfileSettings contains the values that define a profile. Four
instances are exposed:

- MildProfile
- BalancedProfile
- AggressiveProfile
- ExtremeProfile

### Active fields

The active fields are what FEditorLightweightMode reads:

- OverallQuality
- ScreenPercentage
- bDisableLumen
- bDisableVirtualShadows
- bDisableVolumetricFog
- bForceUnlitViewports
- bDisableViewportRealtime

The UI copies profile values into active fields. This means the helper does not
need to know which profile is selected; it only applies the active state.

### LastViewModeBeforeLightweight

This value is used only as a fallback. Same-session restore should prefer
per-viewport backups.

### bWasLightweightModeActiveLastSession

This value is a recovery marker. Enable sets it before applying overrides, and
Disable clears it. If it remains true after an editor restart, the UI can offer
Restore Lightweight State and auto-enable can restore stale viewport state
before enabling again.

## FEditorLightweightMode

FEditorLightweightMode is a static editor helper. It owns all apply/restore
state for the current session.

### Session state

- bIsEnabled tracks whether the mode is active in this editor runtime.
- bHasScalabilityBackup tracks whether scalability was captured.
- ScalabilityBackup stores the pre-mode scalability levels.
- CVarBackup stores pre-mode CVar values and SetBy flags for diagnostics.
- ViewportViewModes stores per-viewport view mode backups.
- ViewportRealtimeStates records viewport clients that received realtime overrides.

### Enable

Enable follows this order:

1. If already enabled, refresh from settings and return.
2. Restore stale viewport state if the previous session ended while active.
3. Back up scalability if no backup exists.
4. Store current view mode in settings for fallback.
5. Mark the persisted session flag active.
6. Apply active settings.
7. Apply viewport behavior.
8. Mark bIsEnabled true.

The ordering matters. Backups must be captured before values are changed.

### RefreshFromSettings

RefreshFromSettings re-applies active settings while preserving original
backups. It also restores viewport state pieces that are no longer requested by
the newly selected profile.

Example: if the user switches from Aggressive to Mild while active and Mild no
longer forces Unlit, the helper restores view modes while keeping the mode
enabled.

### Disable

Disable has two paths:

- Active session: restore viewport state, scalability, and CVars.
- Not active in this session: perform conservative viewport fallback only.

The second path exists for restart recovery. It must not touch scalability or
CVars because session backups are not available.

### CVar handling

SetCVarValue sets plugin values with ECVF_SetByPluginHighPriority and the
LightweightEditorMode tag.

BackupCVar captures:

- Var->GetString()
- Var->GetFlags() & ECVF_SetByMask

RestoreCVar first unsets the plugin override. If Unreal reveals the backed-up
value, restore succeeded. If Unreal reveals a different value, another source
changed the CVar while Lightweight Mode was active and that newer value is left
in place.

### Viewport handling

ApplyViewportSettings only records the state it intends to modify:

- View modes are backed up only when bForceUnlit is true.
- Realtime overrides are added only when bDisableRealtime is true.

This prevents disabling the mode from restoring viewport aspects the selected
profile never changed.

RestoreViewportSettings can restore view modes, remove realtime overrides, or
both. This is used by RefreshFromSettings when a profile changes while active.

While viewport overrides are active, a short ticker reapplies viewport settings
so newly opened viewports receive the same Unlit/realtime treatment. It also
prunes stale viewport-client pointers from the session maps.

## Extension points

### Adding another profile

1. Add a profile struct property to ULightweightEditorModeSettings.
2. Add a label in InitializeAggressivenessOptions.
3. Update ApplyProfileToActiveSettings and GetProfileSettings.
4. Update SettingsReference.md and UserManual.md.

### Adding another CVar feature toggle

1. Add a setting to FLightweightProfileSettings and active settings.
2. Add profile defaults.
3. Add a CVar name constant in EditorLightweightMode.cpp.
4. In ApplyActiveSettings, BackupCVar before SetCVarValue.
5. Restore the CVar when the toggle is false.
6. Update documentation and validation steps.

### Adding UI controls

Keep low-level renderer behavior outside the widget. The widget should write
settings and call RefreshFromSettings, Enable, or Disable.

## Maintenance rules

- Preserve backup-before-set behavior.
- Restore CVars by removing the plugin's tagged override and keep newer values
  from other sources.
- Prefer editor-specific CVars for editor viewport behavior.
- Prefer temporary viewport realtime overrides over persistent SetRealtime
  changes.
- Keep restart fallback conservative.
- Treat missing CVars as non-fatal.
- Update docs whenever profile semantics or CVar mappings change.

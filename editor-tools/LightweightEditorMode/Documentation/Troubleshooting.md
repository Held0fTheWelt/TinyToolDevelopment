# Troubleshooting

This guide covers common problems and likely causes.

## The plugin window is missing

Check the following:

- The plugin is enabled in Edit > Plugins.
- The project was restarted after enabling the plugin.
- The module is listed in the .uproject Plugins array.
- You are running the editor, not a commandlet.

The window should appear under Tools > Performance > Lightweight Editor Mode.

## The mode does not enable on startup

Startup enable waits until editor viewport clients exist. In a slow project this
can take a moment after module startup.

Check:

- Enable on Editor startup is checked.
- The plugin is enabled in the project.
- The editor actually created level editor viewports.
- Logs contain "Scheduling Lightweight Mode auto-enable".
- Logs later contain "Auto-enabling Lightweight Mode after editor viewports
  became available".

If the setting is unchecked before viewports become available, the ticker
cancels itself.

## Screen percentage appears unchanged

Editor viewports do not always follow r.ScreenPercentage. Lightweight Editor
Mode uses editor viewport CVars:

- r.Editor.Viewport.ScreenPercentage
- r.Editor.Viewport.ScreenPercentageMode.RealTime
- r.Editor.Viewport.ScreenPercentageMode.NonRealTime

If the viewport still appears unchanged, check:

- The selected profile's ScreenPercentage value.
- Whether the viewport is using an engine path that overrides screen
  percentage.
- Whether another plugin or console command changes the same editor CVars after
  Lightweight Editor Mode runs.

## Viewports stay Unlit after disabling

Same-session restore uses per-viewport backups. Restart fallback only has the
stored LastViewModeBeforeLightweight value.

Try:

1. Open the plugin window.
2. Click Disable Lightweight Mode.
3. If needed, manually switch the viewport back to Lit.
4. Re-enable and disable the mode in the same session to confirm normal restore.

If this happens often, check whether the editor is being closed while the mode
is still enabled.

After a crash or forced close, the main button may show Restore Lightweight
State. Click it to run the conservative viewport restore and clear the stale
session marker.

## Realtime remains disabled

Realtime disable uses Unreal's temporary realtime override system. In the same
editor session, Disable removes the Lightweight override instead of changing the
viewport's saved realtime preference.

If realtime still appears disabled, check whether another editor system has its
own realtime override active. Manually re-enable realtime from the viewport menu
if needed.

## Lumen still appears enabled

Check whether:

- The selected profile has bDisableLumen enabled.
- The project actually uses Lumen.
- Another plugin or project code sets Lumen CVars after the mode is enabled.
- A custom engine branch renamed or removed the relevant CVars.

The plugin targets:

- r.Lumen.DiffuseIndirect.Allow
- r.Lumen.Reflections.Allow

Missing CVars are skipped and logged at Verbose level.

## Shadows still appear expensive

bDisableVirtualShadows targets virtual shadow maps:

- r.Shadow.Virtual.Enable

This does not disable every possible shadowing cost in every renderer path. If
your scene uses non-virtual shadows, custom shadow systems, ray-traced shadows,
or plugin rendering, additional project-specific tuning may be required.

## Fog still appears

bDisableVolumetricFog sets:

- r.VolumetricFog = 0
- r.Fog = 0

Some materials, post-process volumes, sky systems, or custom atmosphere effects
may still create a fog-like appearance.

## The editor looks too low quality

Use a less aggressive profile:

- Switch Extreme to Aggressive.
- Switch Aggressive to Balanced.
- Raise ScreenPercentage.
- Raise OverallQuality.
- Disable Force Unlit for a custom profile.

After changing the profile while the mode is enabled, the helper refreshes the
active settings automatically.

## The editor is still slow

Lightweight Editor Mode targets viewport rendering cost. It cannot fix all
editor performance issues.

Other possible bottlenecks:

- Asset compilation.
- Shader compilation.
- Source control operations.
- Blueprint construction scripts.
- Editor utility widgets.
- Heavy tick logic in editor worlds.
- Massive actor counts.
- Disk or antivirus overhead.

Use Unreal Insights, Stat commands, and normal project profiling to diagnose
non-rendering bottlenecks.

## Disable does not restore a CVar

The restore path removes the plugin's tagged override. If another system changed
the same CVar while Lightweight Editor Mode was active, that newer value stays
active instead of being overwritten by the old backup.

Check the output log for the CVar name. The plugin logs backup and restore
operations.

## Project Settings page is hidden or missing

The settings page should appear under Project Settings > Plugins > Lightweight
Editor Mode.

If it is missing:

- Confirm the module loaded.
- Confirm the Settings module is available.
- Restart the editor after enabling the plugin.
- Check that no plugin descriptor or build issue prevented module load.

## Build fails after adding a new CVar

Common causes:

- CVar name constant added but not used consistently.
- Setting added to profile struct but not to active fields.
- UI switch statement not updated for a new profile.
- Missing include for an Unreal type.
- Syntax error inside a UPROPERTY metadata block.

Run the editor target build after source changes.

## Logs to inspect

Search the Output Log for:

- [Module]
- [Lightweight]
- Backup CVar
- Restore CVar
- ApplyActiveSettings
- ApplyViewportSettings
- Lightweight mode ENABLED
- Lightweight mode DISABLED

The logs are intentionally explicit so support requests can include the relevant
sequence.

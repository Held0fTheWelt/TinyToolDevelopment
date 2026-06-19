# User Manual

This manual explains how to use Lightweight Editor Mode in day-to-day Unreal
Engine editor work.

## Purpose

Large Unreal Engine scenes can make editor viewports expensive even when the
final game runtime is acceptable. High viewport resolution, Lumen, virtual
shadows, volumetric fog, realtime viewport ticking, and high scalability levels
can all cost frame time while editing.

Lightweight Editor Mode gives you a fast toggle for a temporary, reversible
editing profile. It is most useful when you need responsiveness for layout,
blocking, Blueprint work, foliage passes, asset placement, or project cleanup.

## Opening the window

1. Open the Unreal Editor.
2. Make sure the Lightweight Editor Mode plugin is enabled.
3. Use Tools > Performance > Lightweight Editor Mode.
4. The plugin opens a dockable editor tab.

The tab contains a profile drop-down, a toggle button, and an optional startup
checkbox.

## Choosing a profile

The profile controls how aggressively the editor reduces rendering cost.

### Mild

Mild is intended for projects that only need a small push. It keeps viewport
behavior closer to normal and is a good first choice when you still need visual
context.

Typical behavior:

- Higher screen percentage.
- Higher scalability than aggressive profiles.
- Does not force Unlit by default.
- Does not disable viewport realtime by default.

### Balanced

Balanced is the recommended default. It reduces expensive lighting and viewport
cost while remaining practical for general editing.

Typical behavior:

- Medium screen percentage.
- Lower overall scalability.
- Disables costly rendering features.
- Forces Unlit and disables realtime by default.

### Aggressive

Aggressive is for heavy scenes where viewport responsiveness matters more than
visual fidelity.

Typical behavior:

- Lower screen percentage.
- Low scalability.
- Expensive lighting, shadows, and fog disabled.
- Viewports forced into Unlit.
- Realtime viewport ticking disabled.

### Extreme

Extreme is for overloaded projects, laptop editing, large worlds, or emergency
responsiveness. Use it when you only need scene structure and interaction speed.

Typical behavior:

- Very low screen percentage.
- Lowest scalability.
- Expensive rendering features disabled.
- Unlit viewports and non-realtime editing.

## Enabling the mode

1. Select a profile.
2. Click Enable Lightweight Mode.
3. The plugin applies the active profile.
4. Viewports update immediately.

When enabled, the plugin backs up the original editor state it needs to restore:

- Scalability quality levels.
- Modified console variable values.
- Viewport view modes, when Unlit is forced.
- Temporary viewport realtime overrides, when realtime is disabled.

## Changing profile while enabled

You can choose another profile while the mode is already enabled. The plugin
refreshes the active settings and keeps the original backups from before the
mode was enabled. This means Disable Lightweight Mode still restores the
pre-mode state instead of restoring to the intermediate profile.

## Disabling the mode

Click Disable Lightweight Mode to restore the editor state.

The plugin restores:

- Backed-up scalability levels.
- The plugin's console variable overrides. If another system changed the same
  value while the mode was active, that newer value is left in place.
- Backed-up viewport view modes.
- Temporary viewport realtime overrides.

If the editor restarted before the mode was disabled, per-session backups no
longer exist. In that case the plugin uses the stored fallback view mode from
settings and only performs a conservative viewport restore. When this stale
state is detected, the toggle button shows Restore Lightweight State.

## Enable on Editor startup

The Enable on Editor startup checkbox stores a user setting. When enabled, the
plugin waits until editor viewports exist and then enables Lightweight Editor
Mode automatically.

This delayed startup behavior is intentional. During early module startup,
Unreal may not have created editor viewport clients yet, so immediate viewport
changes could be missed. The plugin uses a short ticker and enables the mode
once the editor is ready.

If startup enable runs after a previous editor session ended before the mode was
disabled, the plugin first performs the conservative viewport restore and then
enables the selected profile again.

## Recommended workflows

### Level blocking

Use Balanced or Aggressive. You usually do not need final lighting while
blocking spaces, checking navigation, or moving large groups of actors.

### Foliage or world editing

Use Aggressive. Large foliage scenes can be expensive in Lit view with shadows
and realtime updates.

### Blueprint or gameplay iteration

Use Mild or Balanced. Keep enough visual context while making editor response
more comfortable.

### Lighting review

Disable Lightweight Editor Mode. The plugin intentionally hides or reduces
lighting features, so it is not appropriate for final visual approval.

### Cinematic or screenshot capture

Disable Lightweight Editor Mode, restore production scalability, and review the
shot in the intended viewport mode.

## Project Settings

Open Project Settings > Plugins > Lightweight Editor Mode to edit profiles and
active values.

The profile structs are the source of truth for Mild, Balanced, Aggressive, and
Extreme. The active values are what the runtime helper applies when the mode is
enabled. The UI copies the selected profile into the active values before
applying the mode.

## What to expect visually

Depending on the profile, the viewport may become:

- Lower resolution.
- Unlit.
- Less detailed.
- Less shadowed.
- Without fog.
- Non-realtime until manually refreshed or interacted with.

This is expected. The goal is interaction speed, not final rendering quality.

## What the plugin does not do

- It does not change packaged game runtime settings.
- It does not edit project renderer settings.
- It does not permanently rewrite map assets.
- It does not replace Unreal scalability, LOD, HLOD, Nanite, or content
  optimization work.
- It does not guarantee identical results across all engine versions and custom
  renderer forks.

## Practical habit

Use Lightweight Editor Mode as an editing mode. Disable it before final review,
before reporting render bugs, and before capturing marketplace or production
screenshots.

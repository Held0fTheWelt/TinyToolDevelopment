<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/LightweightEditorMode/architecture.md -->
# FAQ

This FAQ is written for both buyers and support. It answers the questions a
user is likely to ask before purchase, during first setup, and when validating
restore behavior in a real project.

## Quick Answers

### What is Lightweight Editor Mode?

Lightweight Editor Mode is an Unreal Editor plugin that temporarily reduces
editor viewport rendering cost through configurable profiles. It is meant to
make heavy scenes more comfortable to edit.

### Is this a runtime optimization plugin?

No. This is an editor workflow tool. It does not optimize your packaged game and
does not replace runtime profiling or content optimization.

### Does it affect packaged builds?

No. The plugin is editor-only. It changes editor session state while you work in
the Unreal Editor and has no intended effect on packaged builds.

### Does it permanently change my project?

No. The mode is designed as a temporary overlay. It backs up the values it
changes and restores them when disabled. Profile settings are saved as editor
user settings, but maps, assets, and project renderer settings are not rewritten
by the normal enable/disable workflow.

### Who is it for?

It is for Unreal users who work in expensive editor scenes: large worlds, dense
environment maps, Lumen-heavy scenes, fog-heavy levels, large foliage passes, or
projects where the editor viewport becomes sluggish during everyday work.

## Features And Behavior

### What can the plugin change while enabled?

Depending on the selected profile, it can:

- Lower editor viewport screen percentage.
- Lower overall scalability quality.
- Disable Lumen diffuse indirect lighting.
- Disable Lumen reflections.
- Disable virtual shadow maps.
- Disable volumetric fog and regular fog.
- Force editor viewports into Unlit mode.
- Disable realtime rendering in editor viewports.

### Why does the viewport look worse while enabled?

That is expected. The plugin trades visual fidelity for editor responsiveness.
Use it while editing layout, structure, placement, or Blueprint logic. Disable it
for final lighting, materials, screenshots, cinematics, or visual approval.

### Why does the viewport become Unlit?

Some profiles force Unlit because lighting can be one of the most expensive
parts of editor viewport rendering. You can edit any profile and turn off
bForceUnlitViewports if you still need lighting context.

### Why does realtime turn off?

Some profiles disable viewport realtime so viewports stop redrawing
continuously. This can help heavy scenes, laptops, and thermally constrained
machines. You can disable this behavior per profile.

### Does it disable Nanite?

No. The plugin does not directly disable Nanite. It focuses on editor viewport
screen percentage, scalability, Lumen, virtual shadows, fog, view mode, and
realtime viewport behavior.

### Does it replace Unreal scalability settings?

No. It uses scalability as one part of a broader editor workflow. Unreal
scalability alone does not cover every editor viewport cost, so the plugin also
controls editor viewport screen percentage, selected renderer CVars, view mode,
and realtime behavior.

## Profiles

### What profiles are included?

The plugin includes four editable profiles:

- Mild
- Balanced
- Aggressive
- Extreme

Balanced is the recommended starting point.

### Can I customize the profiles?

Yes. Open Project Settings > Plugins > Lightweight Editor Mode. Each profile has
its own quality, screen percentage, feature toggles, and viewport behavior.

### Can I change profile while the mode is enabled?

Yes. The plugin refreshes the active settings immediately and preserves the
original backups from before the mode was enabled. Disabling still restores the
pre-mode state rather than an intermediate profile.

### Which profile should I use?

Use Mild when you still need visual context. Use Balanced for general editing.
Use Aggressive for heavy layout, foliage, or world editing. Use Extreme when you
need maximum responsiveness and visual fidelity does not matter.

## Restore And Safety

### What is restored when I disable the mode?

During the same editor session, the plugin restores:

- Backed-up scalability quality levels.
- Backed-up CVar values.
- Viewport view modes that were changed by the plugin.
- Viewport realtime states that were changed by the plugin.

### What happens if the editor closes while the mode is enabled?

Normal module shutdown attempts to disable the mode. If the editor crashes or is
terminated unexpectedly, in-memory backups are lost. The plugin stores a fallback
view mode to help avoid getting stuck in Unlit after restart, but it cannot
reconstruct every session-only value after an unexpected shutdown.

### What if viewports stay Unlit after a restart?

Open the Lightweight Editor Mode window and click Disable Lightweight Mode. If a
session backup is not available, the plugin uses the stored fallback view mode
and moves Unlit viewports back to a reasonable non-Unlit mode. If needed, you can
also manually switch the viewport back to Lit from the viewport menu.

### Can another plugin override the same CVars?

Yes. Unreal CVars can be changed by project config, command line, device
profiles, scalability, plugins, and runtime editor code. Lightweight Editor Mode
uses a plugin-priority tagged CVar write and restores its own backups, but a
later write by another system can still win.

### Why are missing CVars not treated as errors?

Renderer features differ by engine version, project settings, platform, and
custom engine branches. If a CVar does not exist, the plugin skips it and logs
the situation instead of failing the whole mode.

## Compatibility

### Which Unreal Engine version is supported?

The implementation targets Unreal Engine 5.4 style editor APIs and renderer
CVars. Validate every engine version you intend to list as supported, especially
newer versions where renderer CVars may change.

### Does it work with custom engine branches?

It should work when the required editor APIs and CVars exist. If a custom branch
renames or removes renderer CVars, those specific toggles may be skipped. Check
the Output Log for details.

### Does it work on Windows, Linux, and Mac?

The plugin is editor-only C++ source and avoids platform-specific runtime code.
Each target editor platform should still be built and tested before claiming
official support for that platform.

### Does it run in commandlets?

No meaningful workflow is provided for commandlets. The main behavior depends on
interactive editor viewport clients, Slate UI, and editor session state.

## Workflow

### How do I open it?

Use Tools > Performance > Lightweight Editor Mode in the Unreal Editor.

### How do I enable it automatically?

Check Enable on Editor startup in the plugin window. The plugin waits until
editor viewports exist, then applies the current profile.

### Why does startup enable wait before applying?

During early module startup, Unreal may not have created editor viewport clients
yet. The plugin uses a short ticker and enables the mode once editor viewports
are available, so viewport state can be captured and changed reliably.

### Should I leave it enabled all day?

You can, but the best habit is to enable it for responsiveness and disable it
before visual decisions. Do not judge final lighting, shadows, fog, materials,
or screenshots while the mode is active.

### Does it help if my bottleneck is shader compilation or source control?

No. The plugin targets editor viewport rendering cost. It will not fix shader
compilation, asset loading, source control delays, slow disks, antivirus scans,
or expensive custom editor tools.

## Support

### What should I include in a support request?

Include:

- Unreal Engine version.
- Operating system.
- Whether the engine is stock or custom.
- Selected profile.
- Whether the issue happened on enable, profile switch, disable, startup, or
  after restart.
- Output Log lines containing "[Lightweight]".
- Any other plugin or script that changes rendering CVars.

### Where can I check what the plugin did?

Open the Unreal Output Log and search for:

- [Lightweight]
- Backup CVar
- Restore CVar
- ApplyActiveSettings
- ApplyViewportSettings
- Lightweight mode ENABLED
- Lightweight mode DISABLED

### What is the most important usage rule?

Use Lightweight Editor Mode for editing speed. Disable it for visual truth.


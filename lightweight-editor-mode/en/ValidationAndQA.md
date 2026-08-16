# Validation And QA

This document provides validation steps for source changes, release testing, and
support reproduction.

## Build validation

Build the editor target after code changes.

Example Windows command:

```bat
D:\Engines\UE_5.4\Engine\Build\BatchFiles\Build.bat PluginProjectEditor Win64 Development -Project=D:\PluginProjectGit\PluginProject.uproject -NoHotReloadFromIDE
```

Adjust engine and project paths for the local machine.

## Static text validation

Run a whitespace check before release:

```bash
git diff --check -- Plugins/LightweightEditorMode PluginProject.uproject
```

Review all changed documentation links and file names.

## Manual smoke test

1. Launch the editor.
2. Open Tools > Performance > Lightweight Editor Mode.
3. Select Balanced.
4. Click Enable Lightweight Mode.
5. Confirm the viewport changes.
6. Click Disable Lightweight Mode.
7. Confirm viewport view mode and realtime state restore.
8. Check the Output Log for backup and restore messages.

## Profile switch test

1. Enable Aggressive.
2. Confirm Unlit and realtime disabled.
3. Switch to Mild while still enabled.
4. Confirm settings refresh without disabling the mode.
5. Confirm view mode or realtime state restores if Mild does not request them.
6. Disable.
7. Confirm the original pre-mode state is restored.

## Startup enable test

1. Check Enable on Editor startup.
2. Restart the editor.
3. Confirm the plugin logs that auto-enable was scheduled.
4. Confirm the plugin enables only after editor viewports are available.
5. Disable the mode.
6. Confirm the startup checkbox is cleared if the user disabled via the main
   button.

## Restart fallback test

1. Enable a profile that forces Unlit.
2. Simulate a restart scenario where per-session backups would be unavailable.
3. Open the plugin window.
4. Confirm the main button shows Restore Lightweight State.
5. Click Restore Lightweight State.
6. Confirm Unlit viewports are moved to the stored fallback view mode or Lit.

Do not expect realtime state or CVars to restore from stale session backups
after a restart. The fallback is intentionally conservative.

## CVar restore test

Use the console or logs to verify:

- CVars are backed up before they are changed.
- Plugin values are applied while enabled.
- Disable removes the plugin override.
- If another source changed the same CVar while enabled, the newer value remains
  active after disable.
- Missing CVars are skipped without crashing.

Important CVars:

- r.Editor.Viewport.ScreenPercentage
- r.Editor.Viewport.ScreenPercentageMode.RealTime
- r.Editor.Viewport.ScreenPercentageMode.NonRealTime
- r.ScreenPercentage
- r.Lumen.DiffuseIndirect.Allow
- r.Lumen.Reflections.Allow
- r.Shadow.Virtual.Enable
- r.VolumetricFog
- r.Fog

## Settings test

1. Open Project Settings > Plugins > Lightweight Editor Mode.
2. Change each profile.
3. Save settings.
4. Reopen the editor.
5. Confirm values persist.
6. Select each profile in the plugin UI.
7. Confirm active values are updated.

## UI test

Check:

- The tab opens from **Tools → Performance → Lightweight Editor Mode**.
- The tab can be docked.
- The combo box displays all four profiles.
- The enable button changes label correctly.
- The startup checkbox reflects saved settings.
- No Slate assertion occurs when changing profile.

## Documentation test

Before release, verify:

- README links work.
- All public settings are documented.
- All CVar mappings are documented.
- Troubleshooting covers startup, restore, screen percentage, and missing CVars.
- Release checklist references current files and commands.
- Diagrams are present and open in a browser.

## Why there is no commandlet

The plugin manipulates editor viewport clients and editor session state. A
commandlet does not provide the same interactive viewport context, so a
commandlet would not validate the main behavior. Build validation, manual editor
tests, and optional automation that launches editor tests are more appropriate.

## Optional CI

The Documentation/CI folder contains a sample GitHub Actions workflow. It is a
template for teams that want to compile the plugin in a controlled environment.
It must be adjusted to match the repository's engine installation strategy.

## Release evidence

For a marketplace or internal release, keep a short record of:

- Engine version tested.
- Build command used.
- Manual smoke test result.
- Startup enable test result.
- Profile switch test result.
- Packaging result.
- Known limitations.

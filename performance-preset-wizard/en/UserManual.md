<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/PerformancePresetWizard/architecture.md -->
# User Manual

This manual describes the normal editor workflow for Performance Preset Wizard. Runtime usage is covered after the editor workflow because presets are still authored and reviewed in the editor before they are applied in a packaged game.

## Opening The Wizard

1. Enable **Performance Preset Wizard** in **Edit > Plugins**.
2. Restart Unreal Editor if prompted.
3. Open **Tools > Performance > Performance Preset Wizard**.

The wizard scans the asset registry for `UPerformancePresetAsset` assets and lists discovered presets by display name, target platform, and asset path.

## Main Panel

The wizard has two main areas:

- Preset list: all discovered performance preset assets.
- Detail pane: selected preset name, description, scalability levels, CVar overrides, status text, and action buttons.

Use **Refresh** whenever new preset assets have been created, renamed, moved, or imported during the current editor session.

## Selecting A Preset

Click a preset in the list to load its summary. The detail pane shows:

- Display name, falling back to the asset name when no display name is set.
- Description written on the preset asset.
- Target platform classification.
- Scalability values converted to Low, Medium, High, Epic, or Cinematic.
- CVar overrides with editor-only markers.

If an asset cannot be loaded, refresh the list and verify that the asset still exists.

## Applying A Preset

1. Select a preset.
2. Review the summary.
3. Click **Apply Preset**.

The applier performs the operation in this order:

1. Capture a restore point.
2. Clamp scalability values to Unreal's supported `0..4` quality range.
3. Apply scalability through `Scalability::SetQualityLevels`.
4. Iterate CVar overrides.
5. Skip empty or malformed entries.
6. Skip editor-only entries when not running in an editor context.
7. Report unknown CVars without stopping the rest of the apply.
8. Show a compact result summary in the wizard status area and the editor notification area.

## Restoring Previous Settings

Click **Restore Previous** to return to the settings captured immediately before the last successful preset apply.

Restore includes:

- The full scalability quality structure captured before the apply.
- Previous values for the specific CVars that the preset overwrote and that still exist.

Restore does not include:

- CVars that were not part of the applied preset.
- CVars that did not exist when the preset was applied.
- More than one historical restore point.

Applying another preset replaces the previous restore point.

## Editor Startup Preset

Open **Edit > Project Settings > Plugins > Performance Preset Wizard**.

Available settings:

- **Apply Preset On Editor Startup**: enables or disables startup application.
- **Startup Preset**: soft reference to the preset asset that should be applied after the editor engine finishes initialization.

The plugin defers startup application until the editor engine is ready. This avoids applying settings too early during module startup and keeps asset loading explicit.

## Runtime Presets

Runtime presets use the same `UPerformancePresetAsset` assets that the editor wizard displays. Package-ready projects apply them manually through `UPerformancePresetRuntimeSubsystem`.

Common Blueprint flow:

1. Get the current `GameInstance`.
2. Get `Performance Preset Runtime Subsystem`.
3. Pass a preset asset to `ApplyRuntimePreset`.
4. Read the returned apply result if you need missing/invalid CVar counts.
5. Call `RestoreLatestBackup` when the user or test flow needs to undo the newest runtime apply.

The subsystem records the active preset path and backup history, but it does not auto-apply a saved preset on game startup in V1.

## Runtime Selector Widget

`UPerformancePresetRuntimeSelectorWidget` is included as a simple UMG starting point. It can list configured presets, apply the selected preset, and restore the latest backup. Use it directly for internal menus, or subclass/replace it for a project-specific options screen.

Runtime presets shown by the default widget can be configured under **Project Settings > Plugins > Performance Preset Wizard Runtime**.

## Runtime Backup History

Before every successful runtime apply, the subsystem stores:

- Scalability values captured before the apply.
- Previous values for existing CVars touched by the preset.
- Previous active preset path.
- Applied preset path, backup id, and UTC timestamp.

Backups are stored newest-first. Restoring an older backup removes that backup and all newer backups, so the history behaves like an undo stack.

## Editing A Preset Asset

Open any `PerformancePresetAsset` in the Content Browser or select it in an asset details panel.

The Details customization presents:

- Preset metadata.
- Target platform.
- Quality dropdowns for all scalability buckets.
- A bulk CVar text editor.

Quality dropdowns map to:

- `0`: Low
- `1`: Medium
- `2`: High
- `3`: Epic
- `4`: Cinematic

## Bulk CVar Editor

Use the CVar text editor when copying overrides from a benchmark note, wiki page, console session, or another preset.

Supported syntax:

```text
# Comment lines are allowed
r.ScreenPercentage=85
r.Nanite=1
r.Shadow.Virtual.Enable=1,editor
```

Use **Export** to write the current array into the text editor. Use **Apply** to parse the text back into the asset.

Parsing behavior:

- Whitespace around names and values is trimmed.
- Blank lines are ignored.
- Lines beginning with `#` or `//` are ignored.
- Lines without `=` are reported as malformed.
- Unknown CVar names are reported as unknown but can still be stored for another engine version or project setup.
- `,editor` marks the override as editor-only.

## Recommended Naming

Use names that communicate both target and intent:

- `Laptop Dev`
- `Desktop Mid Range 60 FPS`
- `Console Like Review`
- `VR Mobile Stable`
- `Cinematic Capture 4k`

Put specific assumptions in the description:

```text
Balanced Nanite/Lumen preset for mid-range desktop GPUs. Intended for 1080p editor review, not final capture.
```

## Working With Source Control

Preset assets are normal Unreal assets. Treat them like other shared configuration:

- Keep production presets in a stable content folder.
- Review changes to CVar names and values carefully.
- Prefer duplicating a preset for experiments instead of editing shared defaults directly.
- Use descriptions to capture why a CVar override exists.

## Removing Or Moving Presets

The startup preset setting uses a soft object pointer. If a preset is moved through the Content Browser, Unreal's redirector system normally preserves the reference. If the startup preset stops applying:

1. Open Project Settings.
2. Re-select the startup preset.
3. Save settings.
4. Restart the editor to test startup application.


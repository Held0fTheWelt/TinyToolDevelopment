# Buyer Guide

Performance Preset Wizard is designed for Unreal Engine teams that need repeatable runtime target performance presets without turning every quality switch into a manual checklist. It is especially useful when designers, artists, technical artists, programmers, and QA need to move between multiple device targets during editor work, standalone testing, packaged QA flows, or project-specific options screens.

## What The Plugin Provides

- A dedicated editor wizard for discovering, reviewing, and applying performance preset assets.
- A runtime `UGameInstanceSubsystem` for applying the same preset assets from C++ or Blueprint.
- Persistent runtime backup history with configurable history length.
- Replaceable runtime storage provider with a GameUserSettings ini-backed default.
- A simple UMG runtime selector widget for development menus or project options screens.
- Data-driven `UPerformancePresetAsset` assets that can be duplicated, renamed, versioned, and reviewed like other project assets.
- Full UE5 scalability coverage for common quality buckets, including global illumination, reflections, shading, and landscape.
- Optional CVar overrides for project-specific rendering and performance switches.
- A bulk CVar editor for copy/paste friendly editing.
- Apply-result feedback that reports applied, skipped, missing, and invalid overrides.
- A restore point for returning to the settings captured immediately before the last preset apply.
- Editor startup preset support through Project Settings.
- Sample preset assets for common tiers such as mobile prototype, laptop development, desktop mid range, high end, ultra high end, VR, console-like, and cinematic capture.
- Source code and documentation intended to be readable by maintainers, not only usable by end users.

## Who Benefits Most

### Technical Artists

Use presets to capture render-budget decisions in assets instead of scattered notes. A technical artist can create a "VR Mobile" preset, document why each scalability level was chosen, and include only the CVar overrides needed by that target.

### Designers

Switch between laptop-friendly editing, console-like review, and high-quality showcase settings without remembering console commands.

### QA

Apply named test conditions consistently before reproducing visual or performance bugs.

### Leads And Producers

Keep common performance targets visible and repeatable. The preset list becomes a shared vocabulary for reviews: "test in Laptop Dev", "record in Cinematic Capture 4k", or "verify in Console Like".

## Typical Workflows

## Workflow: Daily Editor Performance

1. Duplicate the included `DA_LaptopDev` sample preset.
2. Lower costly buckets such as shadows, global illumination, reflections, foliage, and effects.
3. Add project-specific CVars only if the standard scalability buckets are not enough.
4. Set the preset as the editor startup preset.
5. Keep a high-quality preset available for review sessions.

## Workflow: VR Budget Reviews

1. Start from the included VR preset closest to the target headset.
2. Favor stable frame rate over peak visual quality.
3. Keep expensive overrides explicit and documented in the preset description.
4. Test in headset or platform preview, because editor viewport performance is not a substitute for device validation.

## Workflow: Cinematic Capture

1. Start from `DA_CinematicCapture4k`.
2. Use Cinematic (`4`) quality only where the capture pipeline can afford it.
3. Add capture-specific CVars as non-editor-only when they must apply during render jobs.
4. Use Restore Previous after capture setup so the editor returns to the previous working profile.

## Why Presets Are Assets

The plugin uses data assets because they fit normal Unreal production workflows:

- They can live in content folders alongside other project configuration assets.
- They can be duplicated for experimentation.
- They can be reviewed in source control.
- They can be referenced by soft object paths from settings.
- They can be filtered and discovered through the asset registry.

## Safety Model

Performance Preset Wizard applies settings to the current editor or runtime process. It does not silently rewrite unrelated project configuration files when a preset is applied. Before applying a valid preset, the applier captures:

- Current engine scalability levels.
- Current values of the specific CVars that the selected preset is about to overwrite.

The editor **Restore Previous** command is intentionally scoped to that single captured restore point. Runtime application stores a persisted newest-first backup history so packaged projects can restore the latest apply or a specific backup id.

## Limitations

- The plugin does not benchmark hardware or choose the best preset automatically.
- The plugin does not guarantee that a CVar exists in every Unreal Engine version or project configuration.
- The plugin does not validate visual correctness after a preset is applied.
- Editor viewport behavior can differ from packaged runtime behavior.
- Runtime presets are applied manually in V1; saved selections are not auto-applied on game startup.
- Device Profiles remain the correct place for platform-wide runtime policy.

## Recommended First Run

1. Enable the plugin.
2. Open the wizard.
3. Select `DA_MidRange`.
4. Apply it and observe the status text.
5. Apply `DA_LaptopDev`.
6. Use Restore Previous.
7. Open one preset asset and review the Details panel customization.
8. Try the bulk CVar editor with a harmless CVar such as `r.ScreenPercentage=90`.

This path exercises discovery, apply feedback, restore behavior, Details customization, and CVar parsing without requiring a production scene.


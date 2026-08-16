<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/PerformancePresetWizard/architecture.md -->
# Performance Preset Wizard Documentation

Performance Preset Wizard creates runtime target performance presets that are authored and reviewed in Unreal Editor, then applied manually through the editor wizard, C++, Blueprint, or the included runtime selector widget. A preset combines engine scalability levels with optional console variable (CVar) overrides, so teams can switch quickly between hardware tiers, VR budgets, capture settings, laptop-development settings, and project-specific quality targets.

This folder contains the complete documentation delivered with the plugin.

## Start Here

- [BUYER_GUIDE.md](BUYER_GUIDE.md): buyer-friendly overview, included value, and common production workflows.
- [UserManual.md](UserManual.md): complete editor workflow for opening the wizard, applying presets, restoring previous settings, and configuring startup presets.
- [RuntimeUsage.md](RuntimeUsage.md): runtime subsystem, Blueprint API, backup history, storage provider, and selector widget.
- [FAQ.md](FAQ.md): practical answers for Fab buyers, designers, and technical artists.

## Reference

- [PresetAuthoringGuide.md](PresetAuthoringGuide.md): how to design reliable presets, choose scalability levels, and write CVar overrides.
- [RuntimeUsage.md](RuntimeUsage.md): how packaged games can manually apply and restore preset assets.
- [SettingsReference.md](SettingsReference.md): every plugin setting and asset field with defaults and recommended usage.
- [SamplePresetsReference.md](SamplePresetsReference.md): included `DA_*` sample presets and how to adapt them.
- [CodeDocumentation.md](CodeDocumentation.md): source layout, public contracts, implementation notes, and extension points.
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md): common setup, asset, CVar, and build problems with fixes.

Maintainer-only automation, strict-include validation, technical architecture notes, and release checklists can exist in the source repository, but they are excluded from the buyer package.

## Included Assets

- [Screenshots/](Screenshots): lightweight documentation diagrams showing the wizard workflow, preset authoring, and restore/startup behavior.
- `../Content/DA_*.uasset`: sample preset data assets covering desktop, VR, console-like, mobile prototype, laptop-development, and cinematic use cases.
- `../PerformancePresetWizard_Changelog.txt`: release notes shipped with the plugin.

![Workflow overview](Screenshots/01-workflow-overview.svg)

## Quick Editor Workflow

1. Enable the plugin and restart the editor if Unreal asks for it.
2. Open **Tools > Performance > Performance Preset Wizard**.
3. Select a preset from the list. Use **Refresh** to List Presets again if new preset assets were just created or imported.
4. Review the display name, description, target platform, scalability summary, and CVar overrides.
5. Click **Apply Preset**. The wizard applies scalability settings first, then valid CVar overrides.
6. Click **Restore Previous** if you want to return to the settings captured immediately before the last apply.
7. Enable **Apply on Editor Startup** in Project Settings if a preset should be applied automatically when the editor opens.

## Quick Runtime Workflow

1. Author and review `UPerformancePresetAsset` presets in the editor.
2. Add runtime presets to **Project Settings > Plugins > Performance Preset Wizard Runtime**, or pass them directly to the runtime subsystem.
3. In C++ or Blueprint, get `UPerformancePresetRuntimeSubsystem` from the current `GameInstance`.
4. Call `ApplyRuntimePreset` for an explicit user or project action.
5. Use `GetBackupHistory`, `RestoreLatestBackup`, or `RestoreBackupById` when the project needs undo behavior.
6. Use `UPerformancePresetRuntimeSelectorWidget` as a small replaceable UMG selector for test menus or options screens.

![Preset authoring](Screenshots/02-preset-authoring.svg)

## Quick CVar Format

The bulk CVar editor accepts one override per line:

```text
r.ScreenPercentage=85
r.Nanite=1
r.Lumen.Reflections.Allow=0
r.Shadow.Virtual.Enable=1,editor
```

Rules:

- Empty lines are ignored.
- Lines beginning with `#` or `//` are treated as comments.
- `Name=Value` creates a normal override.
- `Name=Value,editor` marks the override as editor-only.
- Unknown CVars are reported but do not stop the preset from applying.
- Empty names or values are skipped and counted as invalid.

## Scalability Levels

Performance Preset Wizard follows Unreal Engine's standard quality scale:

- `0`: Low
- `1`: Medium
- `2`: High
- `3`: Epic
- `4`: Cinematic

The plugin exposes current UE5 scalability buckets including view distance, anti-aliasing, shadows, global illumination, reflections, post process, textures, effects, foliage, shading, and landscape.

## Validation Build

For marketplace and release validation, build the plugin in isolation with strict includes from your installed Unreal Engine. This catches missing includes and packaging mistakes earlier than a normal project build. Keep machine-specific command paths in local maintainer notes rather than in the shipped buyer package.

![Restore and startup](Screenshots/03-restore-and-startup.svg)

## Important Scope Notes

Performance Preset Wizard is not a benchmarking framework, hardware detector, automatic optimizer, or replacement for Device Profiles. Presets should be verified in the target project, map, renderer configuration, and platform profile before being treated as production defaults. Runtime preset application is manual in V1; saved selections are not auto-applied on game startup.

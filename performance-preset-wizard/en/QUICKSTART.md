<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/PerformancePresetWizard/architecture.md -->
# Quick Start

This guide takes you from install to a **real result**: a performance preset applied to your editor
(scalability + console variables), which you can fully restore with one click. Performance Preset
Wizard works on its own — no other plugin is required.

## What You'll Have After This Guide

The wizard open with discovered presets, one preset applied (scalability levels + CVar overrides),
and the ability to restore your previous settings.

## Requirements

- Unreal Engine 5 editor. Runtime application in a packaged game is optional (see step 5).
- No third-party software, account, or runtime. See [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md).

## 1. Install And Enable

1. Add **Performance Preset Wizard** from your Fab library to the project (or install to the engine).
2. Open **Edit → Plugins**, enable **Performance Preset Wizard**, and restart when asked.

## 2. Open The Wizard (First Result)

1. Open **Tools → Performance → Performance Preset Wizard**.
2. The wizard scans the asset registry for `UPerformancePresetAsset` assets and lists them by
   display name, target platform, and asset path (including the bundled sample presets).
3. Click a preset to load its detail pane: description, target platform, scalability levels
   (Low/Medium/High/Epic/Cinematic), and CVar overrides.

## 3. A Real Worked Example: Apply, Then Restore

1. Select a bundled sample preset.
2. Click **Apply Preset**.

**Expected output:** the wizard captures a restore point, clamps scalability to Unreal's `0..4`
range and applies it, then applies each CVar override (skipping malformed/editor-only entries as
appropriate) and shows a compact result summary in the status area and an editor notification.

3. Click **Restore Previous**.

**Expected output:** the scalability structure and the specific CVars the preset changed are
returned to the values captured immediately before the apply.

## 4. Author Your Own Preset

Open any `PerformancePresetAsset` in the Content Browser. The Details panel gives you quality
dropdowns per scalability bucket and a **bulk CVar editor**:

```text
# Comment lines are allowed
r.ScreenPercentage=85
r.Nanite=1
r.Shadow.Virtual.Enable=1,editor
```

`,editor` marks an override as editor-only. Use **Export** to dump the current array into the text
editor and **Apply** to parse it back into the asset. See [PresetAuthoringGuide.md](PresetAuthoringGuide.md).

## 5. Optional: Startup And Runtime Use

- **Editor startup:** *Project Settings → Plugins → Performance Preset Wizard* →
  **Apply Preset On Editor Startup** + **Startup Preset**.
- **Packaged game:** apply presets through `UPerformancePresetRuntimeSubsystem.ApplyRuntimePreset`
  and `RestoreLatestBackup`, or use the included `UPerformancePresetRuntimeSelectorWidget`. See
  [RuntimeUsage.md](RuntimeUsage.md).

## 6. Next Steps

- Full workflow and backup history: [UserManual.md](UserManual.md).
- Bundled presets: [SamplePresetsReference.md](SamplePresetsReference.md).
- Settings: [SettingsReference.md](SettingsReference.md). Problems: [Troubleshooting.md](Troubleshooting.md), [FAQ.md](FAQ.md).

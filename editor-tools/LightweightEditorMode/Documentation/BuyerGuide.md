# Buyer Guide

This guide explains what Lightweight Editor Mode is, what kind of projects it
helps, and what buyers should expect before integrating it into an Unreal Engine
workflow.

## Short description

Lightweight Editor Mode is a reversible Unreal Editor performance mode. It
reduces selected editor rendering costs through profiles that adjust viewport
screen percentage, scalability, lighting features, shadows, fog, view mode, and
viewport realtime state.

It is intended for editing responsiveness, not final visual quality.

## Who benefits most

The plugin is useful for:

- Level designers working in large worlds.
- Environment artists placing assets in dense scenes.
- Blueprint authors who need the editor to stay responsive.
- Technical artists switching between visual work and heavy setup tasks.
- Teams using laptops or mixed hardware.
- Marketplace creators who need quick navigation in asset-heavy demo maps.
- Developers who often keep several editor viewports open.

## Typical pain points

Lightweight Editor Mode is designed for situations like these:

- The editor viewport frame rate drops while navigating a heavy level.
- Lumen and virtual shadows are useful for review but expensive during layout.
- Volumetric scenes are difficult to edit interactively.
- Realtime viewport redraws waste performance while doing non-visual work.
- Designers need a quick temporary mode without editing project renderer
  settings.

## What the plugin does

Depending on profile configuration, it can:

- Reduce editor viewport screen percentage.
- Apply a lower Unreal scalability quality level.
- Disable Lumen diffuse indirect lighting.
- Disable Lumen reflections.
- Disable virtual shadow maps.
- Disable volumetric fog and regular fog.
- Force editor viewports to Unlit.
- Disable realtime viewport rendering.
- Restore backed-up state when disabled.

## What the plugin does not do

It does not:

- Replace content optimization.
- Replace HLOD, LOD, Nanite, or material optimization workflows.
- Change packaged runtime behavior.
- Permanently alter maps.
- Guarantee final render appearance while enabled.
- Solve non-rendering editor bottlenecks such as shader compilation, source
  control operations, Blueprint construction scripts, or slow disks.

## Why profiles matter

Projects and users have different tolerance for visual reduction. A lighting
artist may need a Mild profile. A level designer doing layout may prefer
Aggressive. A laptop user may need Extreme.

The plugin ships with four editable profiles:

- Mild
- Balanced
- Aggressive
- Extreme

Each profile can be adjusted in Project Settings.

## Reversibility model

The plugin is designed around restore safety:

- CVar values are backed up before being changed.
- Original CVar SetBy priority flags are backed up.
- Scalability levels are backed up before being changed.
- Viewport view modes are backed up before forcing Unlit.
- Viewport realtime states are backed up before disabling realtime.
- A persistent fallback view mode is stored for restart recovery.

This model makes the plugin a temporary editing mode rather than a permanent
project configuration change.

## Expected visual changes

Buyers should expect visible quality reduction while the mode is enabled:

- Lower internal render resolution.
- Less lighting detail.
- Reduced or missing reflections.
- Reduced or missing shadows.
- Missing fog.
- Unlit viewport appearance.
- Viewports that do not redraw continuously when realtime is disabled.

These changes are the feature, not a defect. They are how the editor workload is
reduced.

## Best fit examples

### Large environment project

Use Balanced for routine editing and Aggressive for foliage, terrain, or dense
set dressing. Disable the mode when reviewing lighting.

### Marketplace asset pack

Use Mild while checking materials and Balanced while arranging demo scenes. Keep
final captures in normal editor settings.

### Blueprint-heavy project

Use Mild or Balanced while working in Blueprints if the level viewport is open
and expensive. Disable when visually debugging rendering.

### Laptop workflow

Use Aggressive or Extreme to reduce heat and improve interaction speed while
travelling or presenting.

## Compatibility expectations

The implementation targets Unreal Engine 5.4 editor APIs and renderer CVars.
Projects using custom engine branches should test the CVar mapping because
renderer variables can be renamed, removed, or overridden.

Missing CVars are skipped rather than treated as fatal errors.

## Support information to provide

For support requests, include:

- Unreal Engine version.
- Whether the engine is stock or custom.
- Selected profile.
- Relevant Output Log lines containing "[Lightweight]".
- Whether the issue happens during enable, refresh, disable, or startup.
- Whether another plugin changes rendering CVars.

## Evaluation checklist

Before relying on the plugin in a project, test:

- Enable and disable in an empty map.
- Enable and disable in the heaviest production map.
- Profile switching while enabled.
- Startup enable.
- Viewport restore after disabling.
- Visual review after disabling.
- Expected behavior on all team hardware tiers.

## Licensing note

Use of this software is governed by the Fab Standard End User License Agreement
applicable to this product. This guide is informational and does not replace the
license terms.


<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/LightweightEditorMode/architecture.md -->
# Lightweight Editor Mode Documentation

Lightweight Editor Mode is an Unreal Engine editor plugin that lets artists,
level designers, technical artists, and programmers temporarily reduce editor
rendering cost while working inside heavy projects. It is designed as a
reversible editor workflow tool: enable it when a viewport is too expensive,
keep editing, then disable it to return to the previous editor state.

This documentation set mirrors the depth expected from a marketplace-ready
editor plugin. It covers buyer expectations, everyday usage, settings,
technical behavior, validation, packaging, and maintenance.

## Start here

- [UserManual.md](UserManual.md) explains the normal editor workflow.
- [BUYER_GUIDE.md](BUYER_GUIDE.md) explains what the plugin does and who it is for.
- [SettingsReference.md](SettingsReference.md) lists every exposed setting.
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md) helps diagnose common editor cases.
- [TechnicalOverview.md](TechnicalOverview.md) describes the runtime design.
- [CodeDocumentation.md](CodeDocumentation.md) maps source files to behavior.
- [PerformanceTuningReference.md](PerformanceTuningReference.md) helps tune profiles.
- [ValidationAndQA.md](ValidationAndQA.md) provides test and release validation steps.
- [CompatibilityAndPackaging.md](CompatibilityAndPackaging.md) covers engine and packaging notes.
- [FAQ.md](FAQ.md) answers common questions.
- [ReleaseChecklist.md](ReleaseChecklist.md) is the final pre-release checklist.

## What the plugin changes

When enabled, Lightweight Editor Mode can apply these editor-side optimizations:

- Lower editor viewport screen percentage.
- Lower overall scalability quality.
- Disable Lumen diffuse indirect lighting and Lumen reflections.
- Disable virtual shadow maps.
- Disable volumetric fog and regular fog.
- Force editor viewports into Unlit view mode.
- Disable realtime rendering in editor viewports.

The exact behavior depends on the selected profile and the editable profile
settings in Project Settings.

## Core design promise

The plugin is intentionally reversible:

- It backs up scalability settings before changing them.
- It backs up modified console variables before setting plugin values.
- It stores per-viewport view modes and realtime states for the active session.
- It stores a persistent fallback view mode for restart recovery.
- It restores editor state when the mode is disabled or the module shuts down.

This makes the plugin suitable for quick performance relief while keeping the
main project configuration untouched.

## Quick workflow

1. Enable the plugin in Edit > Plugins.
2. Open Tools > Performance > Lightweight Editor Mode.
3. Choose a profile: Mild, Balanced, Aggressive, or Extreme.
4. Click Enable Lightweight Mode.
5. Work in the editor with reduced viewport cost.
6. Click Disable Lightweight Mode before final lighting, material, or capture work.

## Visual guides

The Documentation/Screenshots folder contains SVG workflow diagrams:

- [01-workflow-overview.svg](Screenshots/01-workflow-overview.svg)
- [02-profile-and-settings.svg](Screenshots/02-profile-and-settings.svg)
- [03-restore-flow.svg](Screenshots/03-restore-flow.svg)

These diagrams are documentation assets, not runtime UI assets.

## Engine scope

The implementation targets Unreal Engine 5.4 style editor APIs and rendering
console variables. The most important implementation detail is that editor
viewports do not reliably follow the same screen percentage path as game or PIE
rendering, so the plugin uses editor-specific screen percentage CVars.

## Safety notes

Lightweight Editor Mode is an editor performance tool, not a shipping runtime
optimization system. It should not be used as the only validation path for final
lighting, shadowing, fog, materials, or cinematic output.

Before release captures or visual approvals, disable the mode and review the
scene in the intended production quality settings.


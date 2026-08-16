<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/LightweightEditorMode/architecture.md -->
# Quick Start

This guide takes you from install to a **visible result**: a faster, more responsive editor
viewport that you can fully restore with one click. Lightweight Editor Mode works on its own — no
other plugin is required.

## What You'll Have After This Guide

A reversible "lightweight" editing profile enabled (faster viewport), and the knowledge to switch
profiles and restore your original editor state on demand.

## Requirements

- Unreal Engine 5 editor (the plugin affects the editor viewport only, never packaged game runtime).
- No third-party software, account, or runtime. See [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md).

## 1. Install And Enable

1. Add **Lightweight Editor Mode** from your Fab library to the project (or install to the engine).
2. Open **Edit → Plugins**, enable **Lightweight Editor Mode**, and restart when asked.

## 2. Open The Tool (First Result)

1. Open **Tools → Performance → Lightweight Editor Mode**. A dockable tab opens with a profile
   drop-down, a toggle button, and an *Enable on Editor startup* checkbox.
2. Select the **Balanced** profile (the recommended default).
3. Click **Enable Lightweight Mode**.

**Expected output:** the viewport updates immediately — Balanced lowers screen percentage and
scalability, disables costly lighting, and forces Unlit / non-realtime. The editor feels more
responsive right away.

## 3. A Real Worked Example: Switch Profile, Then Restore

1. With the mode enabled, change the profile drop-down to **Aggressive**. The viewport refreshes to
   the more aggressive settings (lower screen percentage, low scalability, no expensive shadows/fog).
   Your original pre-mode state is still preserved.
2. Click **Disable Lightweight Mode**.

**Expected output:** the editor restores your backed-up scalability levels, console-variable
overrides, viewport view modes, and realtime state — you are back exactly where you started.

> Profiles are tuned for responsiveness, not fidelity, so expect lower-resolution, Unlit, less
> shadowed viewports while enabled. **Disable the mode before lighting review or screenshots.**

## 4. Customize Profiles

Open **Project Settings → Plugins → Lightweight Editor Mode** to edit the Mild / Balanced /
Aggressive / Extreme profile values. The selected profile is copied into the active values before
the mode is applied. See [PerformanceTuningReference.md](PerformanceTuningReference.md).

## 5. Optional: Enable On Startup

Tick **Enable on Editor startup** to have the mode turn on automatically once editor viewports
exist on the next launch.

## 6. Next Steps

- Full per-profile behavior and recommended workflows: [UserManual.md](UserManual.md).
- Every setting: [SettingsReference.md](SettingsReference.md).
- Problems (e.g. stale state after restart → *Restore Lightweight State*):
  [Troubleshooting.md](Troubleshooting.md) and [FAQ.md](FAQ.md).

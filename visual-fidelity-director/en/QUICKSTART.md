<!-- doc-provenance: AKDB:plugins/VisualFidelityDirector/architecture.md; docs/architecture/plugins/VisualFidelityDirector/product-facts.yml; reconciled 2026-07-12 -->
# Quick Start

This guide takes you from install to a real result: the Visual Fidelity Director cockpit open with a
refreshed profile view and a side-by-side profile comparison.

## What You'll Have After This Guide

The VFD cockpit open in Unreal Editor, live metrics sampling started, one composition axis reviewed
with variant and provenance detail, and a comparison against a second profile.

## Requirements

- Unreal Engine 5.4 editor on Win64, Linux, or Mac.
- A project that can load editor plugins.
- No third-party software, account, AI service, or other Tiny Tool plugin.

## 1. Install And Enable

1. Add **VisualFidelityDirector** from your Fab library to the project, or install it to the engine.
2. Open **Edit > Plugins**.
3. Search for **Visual Fidelity Director**.
4. Enable the plugin and restart Unreal Editor when asked.

If you install a source-only plugin package into a C++ project, let Unreal compile the project modules
on the next editor start.

## 2. Open The Cockpit

1. Open **Tiny Tools > Visual Fidelity Director**.
2. Confirm the **Cockpit** page is active (default).
3. Review the status banner, profile selector, and metrics bar.

Expected output:

- The dock tab title is **Visual Fidelity Director**.
- The profile bar lists known profiles from `Saved/VisualFidelityDirector/profiles/` plus built-in/project context.
- The metrics bar fills over several editor ticks (multi-frame sampling) or shows an explicit unavailable state.

## 3. Worked Example: Review One Axis

1. Click **Refresh** on the Cockpit action card.
2. Select any composition axis strip (for example **Anti-Aliasing** or **Upscaling**).
3. In the axis detail drawer, review:
   - the **inheritance path** from root profile to the active profile;
   - **provenance** rows for compiled settings;
   - **control-local findings** for that axis.
4. Change the **variant** combo when multiple pipeline variants are available. Unavailable variants stay
   visible but disabled with compatibility evidence.

Expected output:

- Intent slider updates reflect the selected variant.
- Provenance and findings refresh for the selected axis.
- No project files change until you use governed apply or Expert Tools preview apply.

## 4. Worked Example: Compare Two Profiles

1. Scroll to the **Profile Comparison** card on the Cockpit page.
2. Choose a **Compare against** profile from the dropdown.
3. Read the per-axis diff summary.

Expected output:

- Differing axes are listed with setting-level detail.
- Matching axes show no diff rows.
- Comparison uses the same runtime comparator as `UVFDCockpitBlueprintLibrary::CompareFidelityProfiles`.

## 5. Optional: Expert Tools Snapshot

1. Switch to the **Expert Tools** page.
2. Click **Export Snapshot**.

Expected output:

- `Saved/VisualFidelityDirector/reports/<timestamp>/quality_snapshot.json` exists.
- Latest copies appear under `Saved/VisualFidelityDirector/reports/`.

This path preserves the 1.x snapshot and recipe workflow for users who prefer report-first review.

## 6. Optional: Governed Persistent Apply

Only continue when you intend to write project config files.

1. On the Cockpit page, click **Build Destinations** in the apply drawer.
2. Review each destination summary (Scalability, renderer ini, Device Profiles).
3. Check approval only for destinations you accept.
4. Click **Apply Approved**.

Expected output:

- Timestamped backups and a rollback manifest under the VFD config backup root.
- Apply report with verify results.
- **Rollback** restores backed-up files if something fails verification.

## 7. Where Outputs Live

```text
Saved/VisualFidelityDirector/profiles/
Saved/VisualFidelityDirector/reports/<timestamp>/
Saved/VisualFidelityDirector/recipes/
```

## 8. Next Steps

- Full operation list: [UserManual.md](UserManual.md)
- Controls and Blueprint functions: [SettingsReference.md](SettingsReference.md)
- Problems and fixes: [TROUBLESHOOTING.md](TROUBLESHOOTING.md)
- Compatibility and safety answers: [FAQ.md](FAQ.md)

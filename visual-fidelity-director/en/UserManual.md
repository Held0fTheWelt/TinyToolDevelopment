<!-- doc-provenance: AKDB:plugins/VisualFidelityDirector/architecture.md; docs/architecture/plugins/VisualFidelityDirector/product-facts.yml; reconciled 2026-07-12 -->
# User Manual

Visual Fidelity Director is a local Unreal Editor tool. Version `2.0.0` centers on a profile-centric
cockpit while keeping the integrated 1.x Expert Tools panel for snapshot and recipe workflows.

## Open The Tool

Use **Tiny Tools > Visual Fidelity Director**.

The dock tab exposes **Cockpit**, **Evidence**, and **Expert Tools** pages.

Optional: **Edit > Editor Configurations > Visual Fidelity Director Editor Settings** opens plugin
editor preferences (menu shortcut can be disabled in settings).

## Cockpit Page

### Status Banner

Shows readiness headline and detail text from the active profile compilation and validation state.

### Action Card

| Action | Expected output |
| --- | --- |
| **Refresh** | Reloads profiles, recompiles the active profile preview, restarts multi-frame metrics sampling, and refreshes axis strips. |
| **Compile Preview** | Recompiles desired setting targets for the active profile without writing config. |
| **Open Reports** | Opens the local VFD reports folder in the OS file browser. |

### Profile Bar

Select the active fidelity profile. The bar shows validation status and known profiles loaded from
`Saved/VisualFidelityDirector/profiles/`.

### Metrics Bar

Shows multi-frame live editor metrics (frame, game thread, render thread, GPU, bottleneck, and per-axis
cost share when available). Values of `-1` or explicit unavailable strings mean the measurement is not
available in the current editor context — VFD never fabricates numbers.

### Axis Strips

Each composition axis strip includes:

- axis label and readiness color;
- **variant** combo (unavailable variants remain visible but disabled with evidence);
- **intent** slider (`0.00`–`1.00`);
- selection highlight for the active axis detail drawer.

### Axis Detail Drawer

For the selected axis:

- **Inheritance path** — ordered chain from root ancestor to the active profile;
- **Provenance** — field-level rows for compiled settings (destination, value, source);
- **Findings** — control-local compilation and compatibility findings.

### Profile Comparison Card

Choose a second profile and inspect per-axis diffs of compiled desired state. Uses the same comparison
runtime as the Blueprint library.

### Governed Apply Drawer

| Action | Expected output |
| --- | --- |
| **Build Destinations** | Read-only summaries for Scalability, renderer ini, and Device Profile destinations. |
| **Apply Approved** | Writes only checked, user-approved destinations through backup → write → verify → rollback manifest. |
| **Rollback** | Restores the last backed-up files from the rollback manifest. |

Blocked destinations (assets, materials, MRQ, accessibility, review-only axes) never appear as writable targets.

## Evidence Page

Shows eleven fixed lane evidence blocks (Lumen and other review lanes) with declared axis mappings,
confidence, and manual-review limits. This page is read-only.

## Expert Tools Page

The integrated 1.x control panel for legacy workflows:

### Intent Mixer

Each slider accepts `0.00` to `1.00` and affects recipe dry-run evaluation only until you export or apply.

| Slider | Meaning |
| --- | --- |
| Image Stability | Prefer calmer subpixel detail and less shimmer. |
| Motion Clarity | Prefer less smear/ghosting in moving content. |
| Fine Detail Preservation | Prefer sharper apparent detail. |
| Specular Calmness | Prefer less flicker in highlights/glossy areas. |
| UI Crispness | Prefer HUD/UMG clarity. |
| Cinematic Accumulation | Prefer final-render sample accumulation. |
| Performance Headroom | Prefer cheaper recommendations. |

### Built-In Recipes

Same fifteen built-in recipe IDs as version `1.0.0` (see [SettingsReference.md](SettingsReference.md)).

### Expert Tools Actions

| Action | Expected output |
| --- | --- |
| Export Snapshot (Expert Tools) | `quality_snapshot.json/.md` plus latest copies. |
| Export Recipe Dry Run (Expert Tools) | `recipe_evaluation.json` and `settings_diff.md`; no mutation. |
| Duplicate Recipe | Project-owned JSON under `Saved/VisualFidelityDirector/recipes/`. |
| Import Recipe | Updates active recipe and sliders from imported JSON. |
| Export Scanner Report | `visual_quality_report.json/.md`. |
| Lumen Deep Scan (Expert Tools) | Lumen Surface Cache metadata findings; no mesh/material mutation. |
| Preview Apply + Rollback (Expert Tools) | Session CVar preview with rollback; `visual_fidelity_apply_report.*`. |
| Export A/B Report | `comparison_report.json/.md`. |
| Export Cinematic Report | `cinematic_quality_report.*` and `mrq_recommendation.md`. |
| Validate Schemas | `schema_validation_report.*`. |
| Export Diagnostics | `experimental_diagnostics_report.*`. |
| Productization Report | `productization_readiness_report.*`. |
| Open Output Folder | Opens the reports root. |

## Blueprint Library

`UVFDCockpitBlueprintLibrary` exposes the same headless services as the cockpit:

- load, resolve, validate, and compile fidelity profiles;
- compare profiles;
- detect pipeline capabilities;
- build evidence state;
- preview, apply, and rollback governed persistent configuration.

Packaged showcase: `Content/Blueprints/BPF_VFD_API`.

## Safety Model

- Cockpit review, evidence, comparison, and destination preview are read-only.
- Governed persistent apply is the only cockpit mutation path and requires explicit per-destination approval.
- Expert Tools preview apply remains session CVar only with rollback.
- Assets, materials, Post Process Volumes, MRQ presets, and accessibility settings are not changed by VFD.

## Reports And Profiles

```text
Saved/VisualFidelityDirector/profiles/
Saved/VisualFidelityDirector/reports/
Saved/VisualFidelityDirector/recipes/
```

Treat outputs as local/private because they can contain project names, CVar values, and quality direction.

<!-- doc-provenance: product-facts.yml reconciled 2026-07-04; source AKDB:plugins/NamingConventionUtility/architecture.md -->
# Naming Convention Utility Documentation

Naming Convention Utility is an Unreal Engine editor plugin for applying consistent asset prefixes and suffixes across selected Content Browser folders. It discovers asset types, builds a rename plan, validates target names, previews planned changes in a dockable workbench, and applies selected Unreal asset renames through the editor asset tools.

This folder contains the complete documentation delivered with the plugin.

## Start Here

- [BUYER_GUIDE.md](BUYER_GUIDE.md): buyer-friendly overview, use cases, and fit.
- [QUICKSTART.md](QUICKSTART.md): short install-to-result walkthrough.
- [UserManual.md](UserManual.md): complete workflow for configuring, scanning, editing, reporting, and applying conventions.
- [FAQ.md](FAQ.md): Fab-ready buyer questions and answers.

## Reference

- [SettingsReference.md](SettingsReference.md): settings, DataAsset fields, and recommended baselines.
- [TechnicalOverview.md](TechnicalOverview.md): maintainer-level architecture and safety model.
- [CodeDocumentation.md](CodeDocumentation.md): source layout, contracts, and extension points.
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md): common problems and fixes.
- [ReleaseChecklist.md](ReleaseChecklist.md): validation checklist before shipping.

## Included Assets

- `../Readme.pdf`: legacy packaged readme.
- `../Content/Editor/Data/DA_NamingConvention.uasset`: default convention DataAsset.
- `../Content/Editor/Data/DT_NamingConvention.uasset`: DataTable example/source asset.
- `../Resources/NamingConvention.csv`: CSV import reference.
- `../Resources/NamingConvention.json`: JSON import reference.
- `../Resources/NamingConvention_EpicRecommended.csv`: Epic-aligned profile import reference.
- `../Resources/NamingConvention_TinyLegacy.csv`: legacy 1.0.x profile import reference.
- `../Resources/FileTypeValues.txt`: file type enum reference.
- `../Resources/ToolTypeValues.txt`: DataTable tool type reference.

## Quick Workflow

1. Enable the plugin and restart the editor if required.
2. Open Project Settings and verify the configured Naming Conventions DataAsset.
3. Open Workbench from the plugin menu or a folder context action.
4. Choose **Epic Recommended**, **Tiny Legacy**, or **Project Custom**.
5. Scan the folder, inspect compliance, skip reasons, and target paths.
6. Select the accepted rows you want to apply, then export a report or apply after review.
7. Save affected assets/packages after Unreal completes the rename operation.

## Safety Model

The plugin treats rename operations as high impact. Before calling Unreal's asset rename tools, it builds a plan and skips risky entries.

The plan checks:

- Unsupported asset types.
- Missing convention entries.
- Generated names that are empty or invalid.
- Target object paths that are invalid.
- Existing target assets.
- Existing target packages on disk.
- Duplicate targets within the same batch.
- Duplicate source assets selected through overlapping folders.

The Workbench presents a preview before applying the plan, guards apply with the reviewed plan hash, and writes JSON/Markdown reports under `Saved/NamingConventionUtility/Reports/`.

## What The Tool Changes

The plugin renames Unreal assets through `IAssetTools::RenameAssets`.

It does not:

- Rename raw files outside the asset system.
- Edit imported source files.
- Change class names in C++.
- Change Blueprint class names inside generated code.
- Decide studio naming policy for you.

## Default Naming Families

The default DataAsset includes common Unreal prefixes such as:

- `T_`, `T_N_`, `T_D_` for textures.
- `M_`, `MI_`, `MF_` for materials.
- `SM_`, `SK_`, `SKEL_` for meshes and skeletons.
- `BP_`, `BPI_`, `BPF_`, `WB_` for Blueprints and widgets.
- `NS_`, `NE_`, `PS_` for effects.
- `DT_`, `CT_`, `CF_`, `CV_`, `CLC_` for data and curves.

The Workbench also includes:

- `epic_recommended`: Epic-aligned prefixes with documented collision remaps.
- `tiny_legacy`: the backwards-compatible 1.0.x default style.
- `project_custom`: your configured DataAsset rules.

You can edit or replace the DataAsset to match your studio naming standard. The Workbench can also copy a built-in profile into the configured project DataAsset and edit selected project rules inline.

## Important Limitations

- Texture subtype detection uses a combination of compression settings and name tokens. It is helpful, not clairvoyant.
- Asset types not recognized by the plugin are skipped.
- Unreal may still display rename dialogs or fail a rename based on references, source control, or locked packages.
- Large folder renames should be reviewed carefully.

## Legal Note

Naming Convention Utility is an editor productivity tool. It helps apply naming standards but does not guarantee that a naming standard is correct for every studio, marketplace, or project pipeline.

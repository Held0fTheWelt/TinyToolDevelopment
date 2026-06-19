# Naming Convention Utility Documentation

Naming Convention Utility is an Unreal Engine editor plugin for applying consistent asset prefixes and suffixes across selected Content Browser folders. It discovers asset types, builds a rename plan, validates target names, previews planned changes, and applies Unreal asset renames through the editor asset tools.

Fab product page: https://www.fab.com/listings/60aefcc0-6464-4a69-98d1-7ba02c6e06f2

This folder contains the complete documentation delivered with the plugin.

## Start Here

- [BuyerGuide.md](BuyerGuide.md): buyer-friendly overview, use cases, and fit.
- [UserManual.md](UserManual.md): complete workflow for configuring and applying conventions.
- [FAQ.md](FAQ.md): Fab-ready buyer questions and answers.

## Reference

- [SettingsReference.md](SettingsReference.md): settings, DataAsset fields, and recommended baselines.
- [TechnicalOverview.md](TechnicalOverview.md): maintainer-level architecture and safety model.
- [CodeDocumentation.md](CodeDocumentation.md): source layout, contracts, and extension points.
- [Troubleshooting.md](Troubleshooting.md): common problems and fixes.
- [ReleaseChecklist.md](ReleaseChecklist.md): validation checklist before shipping.

## Included Assets

- `../Readme.pdf`: legacy packaged readme.
- `../Content/Data/DA_NamingConvention.uasset`: default convention DataAsset.
- `../Content/Data/DT_NamingConvention.uasset`: DataTable example/source asset.
- `../Resources/NamingConvention.csv`: CSV import reference.
- `../Resources/NamingConvention.json`: JSON import reference.
- `../Resources/FileTypeValues.txt`: file type enum reference.
- `../Resources/ToolTypeValues.txt`: DataTable tool type reference.

## Quick Workflow

1. Enable the plugin and restart the editor if required.
2. Open Project Settings and verify the configured Naming Conventions DataAsset.
3. Right-click a Content Browser folder.
4. Choose **Apply Naming Conventions**.
5. Review the generated rename preview.
6. Confirm only when the planned names are correct.
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

The UI presents a preview before applying the plan when confirmation is enabled.

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

You can edit or replace the DataAsset to match your studio naming standard.

## Important Limitations

- Texture subtype detection uses a combination of compression settings and name tokens. It is helpful, not clairvoyant.
- Asset types not recognized by the plugin are skipped.
- Unreal may still display rename dialogs or fail a rename based on references, source control, or locked packages.
- Large folder renames should be reviewed carefully.

## Legal Note

Naming Convention Utility is an editor productivity tool. It helps apply naming standards but does not guarantee that a naming standard is correct for every studio, marketplace, or project pipeline.

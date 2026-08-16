<!-- doc-provenance: product-facts.yml reconciled 2026-07-04; source AKDB:plugins/NamingConventionUtility/architecture.md -->
# Quick Start

This guide takes you from install to a real result: assets in a folder renamed to your naming convention after a preview-and-confirm pass. Naming Convention Utility works on its own. No other plugin is required.

## What You'll Have After This Guide

The naming rules reviewed, a folder scanned in the Naming Workbench, and selected assets renamed (for example `OldWall` -> `SM_OldWall`) through Unreal's asset system.

## Requirements

- Unreal Engine 5 editor with a project that has content assets to rename.
- No third-party software, account, or runtime. See [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md).

## 1. Install And Enable

1. Add **Naming Convention Utility** from your Fab library to the project or install it to the engine.
2. Open **Edit > Plugins**, enable **Naming Convention Utility**, and restart when asked.

## 2. Review The Rules

1. Open **Edit > Project Settings > Plugins > Naming Convention Utility**.
2. The key setting is **NamingConventionDataAssetPath**, defaulting to the bundled `/NamingConventionUtility/Editor/Data/DA_NamingConvention`.
3. Open that DataAsset to see the project-custom rules. Each rule has a `FileTypeIdentifier`, `NamingsToRemove`, `PreFix`, and `PostFix`.

Example:

```text
FileTypeIdentifier = FTC_STATICMESH
NamingsToRemove    = ["StaticMesh_", "Mesh_"]
PreFix             = "SM_"
PostFix            = ""
```

Recommended: duplicate the default DataAsset into your project content and point `NamingConventionDataAssetPath` at the copy. You can also copy a built-in Workbench profile into the configured project DataAsset.

## 3. Scan In The Naming Workbench

1. Open the **Naming Workbench** from the plugin menu, or right-click a Content Browser folder and open the workbench for that scope.
2. Choose a profile:
   - **Epic Recommended** for an Epic-aligned baseline.
   - **Tiny Legacy** for the 1.0.x default style.
   - **Project Custom** for your configured DataAsset.
3. Click **Scan**. The workbench shows accepted renames, already compliant assets, skipped assets, compliance percent, and top deviations.

## 4. Apply A Real Rename

1. Find a static mesh named `OldWall` in the accepted rows.
2. Confirm the target path ends in `SM_OldWall.SM_OldWall`.
3. Leave the row selected for apply.
4. Optional: click **Export** to write a preview report.
5. Click **Apply** and confirm.

Expected output: `OldWall` becomes `SM_OldWall`; Unreal completes the rename. Save affected packages afterward. Apply writes a JSON/Markdown audit report under `Saved/NamingConventionUtility/Reports/`.

## 5. Common Skip Reasons

A planned rename is skipped when the asset type is unsupported, no rule matches the detected type, the name already matches, the generated name is invalid, the target already exists, or two assets would collide on the same target name.

## 6. Next Steps

- Full workflow, rule fields, DataTable conversion, texture subtype detection: [UserManual.md](UserManual.md).
- Settings: [SettingsReference.md](SettingsReference.md).
- Problems: [TROUBLESHOOTING.md](TROUBLESHOOTING.md) and [FAQ.md](FAQ.md).

Asset renaming affects packages and references. Test on a small folder first, keep source control clean before large renames, and review generated redirectors.

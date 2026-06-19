# User Manual

This manual explains how to configure and use Naming Convention Utility in the Unreal Editor.

## Installation

1. Add the plugin to your project's `Plugins` folder or install it through Fab.
2. Enable **Naming Convention Utility** in **Edit > Plugins**.
3. Restart the editor if Unreal asks for a restart.
4. Confirm that plugin content is visible if you want to inspect the default DataAsset.

## Configure The DataAsset

Open **Edit > Project Settings > Plugins > Naming Convention Utility**.

The key setting is:

```text
NamingConventionDataAssetPath
```

Default:

```text
/NamingConventionUtility/Data/DA_NamingConvention.DA_NamingConvention
```

You can:

- Use the provided default asset.
- Duplicate it into your project content folder.
- Edit prefixes and suffixes to match your standard.
- Convert a compatible DataTable into the target DataAsset.

## Rule Fields

Each rule contains:

- `FileTypeIdentifier`: the Unreal asset category the rule applies to.
- `NamingsToRemove`: substrings removed before adding the current prefix/suffix.
- `PreFix`: prefix prepended to the cleaned name.
- `PostFix`: suffix appended to the cleaned name.

Example:

```text
FileTypeIdentifier = FTC_STATICMESH
NamingsToRemove = ["StaticMesh_", "Mesh_"]
PreFix = "SM_"
PostFix = ""
```

`OldWall` becomes `SM_OldWall`.

## Apply Naming Conventions

1. Right-click a Content Browser folder.
2. Choose **Apply Naming Conventions**.
3. Review the preview dialog.
4. Confirm when the planned names are correct.
5. Let Unreal complete the rename operation.
6. Save affected assets/packages.

The tool scans recursively through the selected folder.

## Preview And Skip Reasons

The preview summarizes:

- Number of scanned assets.
- Number of planned renames.
- Number of skipped assets.
- Example old-name to new-name pairs.
- Example skip reasons.

Common skip reasons:

- Asset type is unsupported.
- No naming rule exists for the detected type.
- Name already matches the convention.
- Generated name is invalid.
- Target asset already exists.
- Multiple assets would produce the same target.

## DataTable Conversion

The plugin can convert a compatible DataTable into the configured DataAsset.

Expected row struct:

```text
FNamingConventionTableInformation
```

Fields:

- `FileType`
- `ToolType`
- `Value`

Supported tool types:

- `NCTT_TOREMOVE`
- `NCTT_PREFIX`
- `NCTT_POSTFIX`

Workflow:

1. Select the compatible DataTable asset.
2. Open its context menu.
3. Choose **Convert NamingConvention Table to DataAsset**.
4. Review the confirmation summary.
5. Confirm to replace the target DataAsset entries.

The conversion uses an editor transaction, so it can be undone through Unreal's undo stack.

## Texture Subtype Detection

Texture subtype detection uses:

- `TC_Normalmap` compression for normal maps.
- Name tokens such as `atlas`, `normal`, `nrm`, `albedo`, `roughness`, `metallic`, `opacity`, `emissive`, `mask`, `orm`, and similar common suffixes.

If a texture cannot be classified more specifically, it falls back to `FTC_TEXTURE`.

## Recommended Workflow

For production use:

1. Duplicate the default DataAsset into your project.
2. Review every prefix and suffix.
3. Test on a small folder first.
4. Confirm preview output.
5. Commit or shelve changes after Unreal finishes renaming.
6. Run redirector cleanup if enabled.

## Undo And Source Control

Unreal asset renaming can affect packages and references. Use normal Unreal/source-control discipline:

- Test on a small folder first.
- Keep source control clean before large renames.
- Review generated redirectors.
- Save affected packages.
- Commit rename operations separately from unrelated work.

## Removing The Plugin

Before removing the plugin:

1. Finish or revert pending asset rename operations.
2. Save content packages.
3. Disable the plugin.
4. Restart the editor.

Already-renamed assets remain renamed because the changes were applied through Unreal's asset system.

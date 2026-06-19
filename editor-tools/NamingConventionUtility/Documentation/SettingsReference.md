# Settings Reference

Naming Convention Utility stores project-wide settings in `UNamingConventionUtility_Settings`.

## Settings Object

Source file:

```text
Source/NamingConventionUtility/Public/NamingConventionUtility_Settings.h
```

Config scope:

```text
Editor
```

The settings are intended for editor workflows and project-level convention control.

Editor location:

```text
Edit > Project Settings > Plugins > Naming Convention Utility
```

## NamingConventionDataAssetPath

Type:

```text
FSoftObjectPath
```

Default:

```text
/NamingConventionUtility/Data/DA_NamingConvention.DA_NamingConvention
```

Purpose:

- Points to the DataAsset containing rename rules.
- Used by folder rename workflow.
- Used by DataTable conversion as the target asset.

Recommendation:

- Duplicate the default DataAsset into your project if your team wants explicit ownership.
- Keep the project-specific asset in source control.
- Review it like any other pipeline policy asset.

## bConfirmBeforeApplyingConventions

Default:

```text
true
```

Purpose:

- Shows a preview and asks for confirmation before applying batch renames.

Recommendation:

- Keep enabled for normal use.
- Disable only for trusted internal automation after thorough testing.

## bFixRedirectorsAfterRename

Default:

```text
true
```

Purpose:

- Attempts to fix redirectors in selected folders after actual renames.

Recommendation:

- Keep enabled for small and medium rename batches.
- For very large projects with strict source-control workflows, consider manual redirector cleanup.

## DataAsset: NamingConventions

Type:

```text
TArray<FNamingConventions>
```

Each entry defines the rule for one `EFileTypeIdentifier`.

Fields:

- `FileTypeIdentifier`: target asset type.
- `NamingsToRemove`: old fragments to remove.
- `PreFix`: prefix to add.
- `PostFix`: suffix to add.

## DataAsset Utility Buttons

The DataAsset includes editor-callable helpers:

- `PopulateDefaultNamingConventions`
- `ClearNamingConventions`
- `ClearPreFixes`
- `ClearPostFixes`
- `ClearNamingsToRemove`

Use these carefully. They modify the DataAsset and mark it dirty.

## DataTable Row Fields

`FNamingConventionTableInformation` supports:

- `FileType`
- `ToolType`
- `Value`

`ToolType` determines how `Value` is applied:

- `NCTT_TOREMOVE`: append to `NamingsToRemove`.
- `NCTT_PREFIX`: assign to `PreFix`.
- `NCTT_POSTFIX`: assign to `PostFix`.

## Recommended Baseline

For most projects:

```text
bConfirmBeforeApplyingConventions = true
bFixRedirectorsAfterRename = true
NamingConventionDataAssetPath = project-owned duplicate of the default asset
```

Then test conventions on a small folder before applying them to production content.

<!-- doc-provenance: product-facts.yml reconciled 2026-07-04; source AKDB:plugins/NamingConventionUtility/architecture.md -->
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
/NamingConventionUtility/Editor/Data/DA_NamingConvention.DA_NamingConvention
```

Purpose:

- Points to the DataAsset containing rename rules.
- Used by folder rename workflow.
- Used by DataTable conversion as the target asset.
- Used as the `project_custom` Workbench profile.

Recommendation:

- Duplicate the default DataAsset into your project if your team wants explicit ownership.
- Keep the project-specific asset in source control.
- Review it like any other pipeline policy asset.
- Use the Workbench copy action if you want to replace it with a built-in Epic Recommended or Tiny Legacy profile.

## bConfirmBeforeApplyingConventions

Default:

```text
true
```

Purpose:

- Shows a preview and asks for confirmation before applying batch renames.
- The Workbench also guards apply with the reviewed plan hash.

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

## Workbench Profiles

The Workbench exposes three profile choices:

- `epic_recommended`: built-in read-only Epic-aligned rules.
- `tiny_legacy`: built-in read-only 1.0.x-compatible rules.
- `project_custom`: the configured `NamingConventionDataAssetPath`.

Built-in profiles are not edited in place. Use **Copy to Project** to replace the configured Project Custom DataAsset with a built-in profile, then edit selected rules inline.

## Reports

Workbench export/apply writes JSON and Markdown reports under:

```text
Saved/NamingConventionUtility/Reports/
```

Reports include profile metadata, folder scope, plan hash, compliance summary, selected target paths, accepted entries, skipped entries, and applied count.

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

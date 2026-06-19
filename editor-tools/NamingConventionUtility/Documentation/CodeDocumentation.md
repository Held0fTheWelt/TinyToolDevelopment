# Code Documentation

This page documents the source layout and main code contracts of Naming Convention Utility. It complements the inline Doxygen-style comments in the plugin headers.

## Source Layout

```text
Source/NamingConventionUtility/
  NamingConventionUtility.Build.cs
  Public/
    NamingConventionUtility.h
    NamingConventionUtility_Settings.h
    Actions/NamingConventionUtilityObject.h
    Data/NamingConventionsDataAsset.h
    Enums/FileTypeIdentifier.h
    Enums/NamingConventionToolType.h
    Structs/NamingConventions.h
    Structs/NamingConventionTableInformation.h
  Private/
    NamingConventionUtility.cpp
    NamingConventionUtilityNaming.h
    NamingConventionUtilityNaming.cpp
    NamingConventionUtility_Settings.cpp
    Actions/NamingConventionUtilityObject.cpp
    Data/NamingConventionsDataAsset.cpp
    Tests/NamingConventionUtilityTests.cpp
```

## Main Classes And Structs

| Class/Struct | File | Responsibility |
| --- | --- | --- |
| `FNamingConventionUtilityModule` | `Public/NamingConventionUtility.h` | Settings and Content Browser menu integration. |
| `UNamingConventionUtility_Settings` | `Public/NamingConventionUtility_Settings.h` | DataAsset path and safety settings. |
| `UNamingConventionsDataAsset` | `Public/Data/NamingConventionsDataAsset.h` | Editable rule collection. |
| `FNamingConventions` | `Public/Structs/NamingConventions.h` | One file-type naming rule. |
| `FNamingConventionTableInformation` | `Public/Structs/NamingConventionTableInformation.h` | DataTable import row. |
| `UNamingConventionUtilityObject` | `Public/Actions/NamingConventionUtilityObject.h` | Compatibility utility entry point. |
| `FRenamePlan` | `Private/NamingConventionUtilityNaming.h` | Validated batch rename plan. |
| `FRenameEntry` | `Private/NamingConventionUtilityNaming.h` | One planned rename. |
| `FSkippedAsset` | `Private/NamingConventionUtilityNaming.h` | One skipped asset and reason. |

## Naming Core Contract

`NamingConventionUtilityNaming.*` is the shared core. All rename entry points should use it.

Important functions:

- `ResolveFileTypeFromAsset`: map loaded UObject assets to `EFileTypeIdentifier`.
- `BuildNewAssetName`: apply remove/prefix/suffix rules.
- `FindConvention`: locate a rule by file type.
- `IsValidAssetObjectName`: validate generated object names.
- `BuildRenamePlan`: produce validated plan and skip reasons.
- `BuildAssetRenameData`: convert plan entries for `IAssetTools`.
- `CountAppliedRenames`: count real post-rename results.
- `BuildRenamePlanSummary`: generate preview text.
- `FileTypeToString`: stable enum display for logs and skip messages.

## Module Contract

`FNamingConventionUtilityModule` owns editor integration only. It should not duplicate naming logic.

Folder action responsibilities:

1. Gather selected folder assets.
2. Call the naming core.
3. Ask for confirmation.
4. Call Unreal asset tools.
5. Report outcome.
6. Optionally fix redirectors.

DataTable conversion responsibilities:

1. Find valid selected DataTable.
2. Read typed rows.
3. Validate rows.
4. Confirm replacement.
5. Modify target DataAsset inside a transaction.

## DataAsset Contract

`UNamingConventionsDataAsset` stores the convention policy.

Important behavior:

- Class default object receives common defaults.
- Editor utility functions call `Modify` and `MarkPackageDirty`.
- `PopulateDefaultNamingConventions` overwrites existing entries.

## Legacy Object Contract

`UNamingConventionUtilityObject` remains available for compatibility. It should delegate to the shared core and not reimplement:

- Asset type detection.
- Name building.
- Package path calculation.
- Collision checks.

It is exposed as an editor-callable/Blueprint-callable object for legacy utility workflows and mirrors the main menu flow's preview, final summary, and redirector cleanup behavior.

## Build Dependencies

Important module dependencies:

- `AssetRegistry`: folder asset discovery and target checks.
- `AssetTools`: rename and redirector operations.
- `ContentBrowser`: context menu integration and selected folders.
- `ToolMenus`: menu registration.
- `MediaAssets`, `Niagara`, `UMG`, `UnrealEd`: asset type support and editor behavior.

## Important Implementation Comments

The code should document:

- Why rename planning happens before `RenameAssets`.
- Why generated names are validated before execution.
- Why duplicate targets are skipped.
- Why texture subtype detection is heuristic.
- Why redirectors are fixed only after actual renames.
- Why DataTable conversion asks before replacing target entries.

## Testing Notes

Existing automation tests cover:

- Idempotent prefix handling.
- Boundary-safe prefix removal.
- Object-name validation.
- Texture subtype and texture atlas classification.
- Post-process material classification.
- Duplicate target skip behavior.
- Existing target asset handling.
- DataTable conversion grouping.
- Unsupported asset skip behavior.

Useful future tests:

- Existing target package-on-disk handling.
- DataTable conversion UI confirmation/cancel behavior.
- Redirector cleanup behavior after real editor renames.

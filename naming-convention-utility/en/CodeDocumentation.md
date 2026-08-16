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
    NamingConventionUtilityMcpInterface.cpp
    NCUCanonicalJson.*
    NCUPreviewSession.*
    NCUReportWriter.*
    NCURuleDiff.*
    NCURuleProfile.*
    SNCUNamingWorkbench.*
    Actions/NamingConventionUtilityObject.cpp
    Data/NamingConventionsDataAsset.cpp
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
| `SNCUNamingWorkbench` | `Private/SNCUNamingWorkbench.h` | Dockable Slate workbench for scan, profiles, filters, inline rule editing, report export, and guarded apply. |
| `FNCURuleProfile` | `Private/NCURuleProfile.h` | Built-in and project-custom rule profile model. |
| `FNCURuleDiff` | `Private/NCURuleDiff.h` | Per-file-type profile comparison. |
| `FNCUPreviewSession` | `Private/NCUPreviewSession.h` | Folder/profile/plan/session state plus canonical hash helpers and guarded apply plan. |
| `FNCUReportWriter` | `Private/NCUReportWriter.h` | Deterministic JSON/Markdown report writer. |
| `UNamingConventionUtilityMcpInterface` | `Public/NamingConventionUtilityMcpInterface.h` | Optional JSON facade for UCM/MCP route calls. |

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

Session/report helpers:

- `ComputeCanonicalPlanHash`: hash profile id, ordered rules, accepted entries, and skipped entries.
- `SummarizeCompliance`: derive supported/compliant/needs-rename/unsupported counts and top deviations.
- `FilterRenamePlanByTargetObjectPaths`: keep only selected accepted target paths for selective apply.
- `BuildGuardedApplyPlan`: reject stale, empty, or unselected apply attempts before mutation.
- `FNCUReportWriter::WriteReport`: write JSON and Markdown preview/apply evidence.

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

Workbench responsibilities:

1. Resolve active rule profile.
2. Gather scoped folder assets and call the naming core.
3. Display compliance, accepted rows, compliant rows, skipped rows, and row details.
4. Copy built-in profiles into Project Custom on explicit user action.
5. Edit selected Project Custom rules through the configured DataAsset.
6. Export reports and apply selected accepted rows through `BuildGuardedApplyPlan`.

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
- Why guarded apply compares canonical plan hashes before mutation.

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
- Built-in profile defaults and prefix uniqueness.
- Rule diff.
- Canonical plan hash stability.
- Compliance scoring.
- Selective plan filtering.
- Guarded apply rejection paths.
- Report JSON shape.

Useful future tests:

- Existing target package-on-disk handling.
- DataTable conversion UI confirmation/cancel behavior.
- Redirector cleanup behavior after real editor renames.
- Manual or functional editor smoke coverage for Workbench Slate interactions.

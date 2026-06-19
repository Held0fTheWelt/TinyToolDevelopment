# Technical Overview

This page documents the internal architecture and safety model of Naming Convention Utility.

## Module

The plugin module is `FNamingConventionUtilityModule`.

Responsibilities:

- Register project settings under `Project Settings > Plugins > Naming Convention Utility`.
- Extend Content Browser folder context menus.
- Extend DataTable asset context menus.
- Load the configured naming DataAsset.
- Build and apply rename plans.
- Convert compatible DataTables into DataAsset entries.

## Main Components

| Component | Responsibility |
| --- | --- |
| `FNamingConventionUtilityModule` | Editor integration, menus, folder action, DataTable conversion. |
| `NamingConventionUtilityNaming.*` | Shared naming core for type detection, name building, validation, and plan summaries. |
| `UNamingConventionUtility_Settings` | Config-backed DataAsset reference and safety settings. |
| `UNamingConventionsDataAsset` | Editable convention rule asset. |
| `FNamingConventions` | One rule for one file/asset type. |
| `FNamingConventionTableInformation` | DataTable row used for import/conversion. |
| `UNamingConventionUtilityObject` | Legacy/utility entry point that now delegates to the shared core. |

## Folder Rename Flow

The main folder action performs:

1. Read selected folders from the Content Browser context.
2. Gather assets recursively through the Asset Registry.
3. De-duplicate assets selected through overlapping folders.
4. Load the configured DataAsset.
5. Build a rename plan through `NamingConventionUtility::BuildRenamePlan`.
6. Show a preview confirmation.
7. Convert plan entries into `FAssetRenameData`.
8. Call `IAssetTools::RenameAssets`.
9. Count actual applied renames.
10. Fix redirectors only when real renames occurred and the setting is enabled.

## Rename Plan Validation

The shared core validates:

- Asset can be loaded.
- Asset type is supported.
- Convention entry exists.
- Generated name differs from current name.
- Generated object name is valid.
- Generated object path is valid.
- Target asset is not already registered.
- Target package does not already exist on disk.
- No two plan entries share the same target object path.

Skipped assets are stored with a human-readable reason.

## Type Detection

`ResolveFileTypeFromAsset` maps Unreal asset classes to `EFileTypeIdentifier`.

Examples:

- `UStaticMesh` -> `FTC_STATICMESH`
- `UMaterialInstance` -> `FTC_MATERIAL_INSTANCE`
- `UWidgetBlueprint` -> `FTC_WIDGET_BLUEPRINT`
- `UDataTable` -> `FTC_DATA_TABLE`
- `UCurveVector` -> `FTC_CURVE_VECTOR`
- `UCurveLinearColor` -> `FTC_CURVE_LINEAR_COLOR`
- `UMediaTexture` -> `FTC_MEDIA_TEXTURE`
- `UWorld` map assets -> `FTC_LEVEL`
- Post-process `UMaterial` / `UMaterialInstance` assets -> `FTC_POST_PROCESS`
- Optional plugin asset classes such as Control Rig, Paper2D sprite atlases, and Landscape helper assets are detected by class-name hierarchy when those plugins are present.

`FTC_WORLD` is kept as a legacy enum value for older saved settings. New map assets resolve to `FTC_LEVEL`, and the default source/CSV/JSON rules no longer include an active `FTC_WORLD` row.

`FTC_OTHER` remains a custom placeholder rule. The resolver does not assign unknown assets to it automatically; unsupported assets still resolve to `FTC_NONE` so the rename plan can skip them explicitly.

Texture subtypes use a heuristic:

- Compression settings identify normal maps.
- Name tokens identify atlases, diffuse, roughness, metallic, mask, opacity, and emissive textures.
- Unknown texture intent falls back to `FTC_TEXTURE`.

## Name Building

`BuildNewAssetName` performs:

1. Remove configured legacy fragments from `NamingsToRemove`.
2. Remove known texture prefixes when applying texture subtype rules.
3. Remove the configured prefix only at the start of the name.
4. Remove the configured suffix only at the end of the name.
5. Trim whitespace.
6. Add the configured prefix and suffix exactly once.

Prefix and suffix removal is boundary-aware to avoid corrupting names that merely contain the token in the middle.

## DataTable Conversion Flow

The conversion action:

1. Finds the first selected DataTable with row struct `FNamingConventionTableInformation`.
2. Loads the configured target DataAsset.
3. Reads typed rows through `GetAllRows`.
4. Groups rows by file type.
5. Tracks skipped rows and duplicate prefix/postfix rows.
6. Shows a confirmation dialog before replacing entries.
7. Uses `FScopedTransaction` for undo support.
8. Marks the DataAsset dirty.

## Safety Philosophy

The plugin favors skipping over guessing.

If a target is ambiguous or unsafe, it is not renamed. This keeps user trust high and makes large folder operations reviewable.

## Extension Points

Useful future extension points:

- Add project-configurable texture token aliases.
- Add support for more asset classes.
- Add dry-run report export.
- Add named convention profiles.
- Add commandlet automation for CI naming checks.
- Add editor UI for editing rules without opening the raw DataAsset.

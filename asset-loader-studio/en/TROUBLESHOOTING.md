<!-- doc-provenance: product-facts.yml reconciled 2026-07-01; source AKDB:plugins/AssetLoaderStudio/architecture.md -->
# Troubleshooting

## Missing Assets

Use full object paths with the object suffix, for example `/Game/Data/DA_Item.DA_Item`. If validation
reports `ALS.Table.MissingReferencedAsset`, retarget the field to an existing asset or clear it.

## Wrong Paths

`ALS.InvalidSoftObjectPath` and `ALS.Table.InvalidReferencePath` mean the path cannot be parsed as an
Unreal object path. Recopy the reference from the Content Browser.

## Failed Applies

Applies require an allowed preview and an approval token. In the editor workspace, the Apply button
approves the last preview. Through automation, set `approval_token` to the preview id or to
`approved`.

## Permission Denials

Use `asset_loader_studio.state.read.v1` to inspect active profiles. Common denials are read-only mode,
dry-run-only mode, affected row/asset limits, roots outside `allowed_roots`, or missing destructive
permission.

## Failed Saves

Generic apply marks packages dirty and returns recovery guidance. Save through the Unreal editor save
prompt or source-control workflow after reviewing the changed assets.

## Empty Or Duplicate Rows

DataTables with empty or duplicate row ids cannot be safely mapped to stable row operations. Rename
or repair the rows in the owning table, then capture a fresh snapshot.

## Destructive Actions Blocked

Delete and other destructive operations need a profile that allows them and an explicit destructive
approval token. Prefer previewing the plan, saving backups or source-control state, then applying
only the reviewed preview.

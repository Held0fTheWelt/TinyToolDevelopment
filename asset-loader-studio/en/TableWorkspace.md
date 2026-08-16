# Table Workspace

The table service inspects DataAssets and DataTables through Unreal reflection.

DataAssets are represented as one row named `asset`. DataTables are represented as one row per
DataTable row name. Columns include display name, C++ type, editability, visibility, and reference
metadata. Cells include value text, referenced object path where available, validation badges, and
editability.

Queries support:

- row/value filtering
- sort column and direction
- grouping column
- visible column filtering
- diagnostics on/off
- invalid rows only

Structured edits are staged through `FALSOperationRequest` and `FALSOperationPreview`. Apply supports
safe field writes for DataAsset properties and DataTable row fields using Unreal property import
rules. Packages are marked dirty; saving remains an explicit editor/source-control step.

## Inspection Tips

- Use full object paths copied from the Content Browser.
- Turn diagnostics on when you are looking for broken references or unsupported field types.
- Use invalid-only filtering for cleanup passes.
- Use visible-column filtering when a large table needs a focused review.
- Treat value text as review data; final persistence still goes through preview/apply.

## Edit Boundaries

Asset Loader Studio can stage structured field writes for supported DataAsset properties and
DataTable row fields. Unsupported classes, unsupported field import text, disallowed roots, row/asset
limits, or destructive actions are reported as preview diagnostics before apply.

<!-- doc-provenance: product-facts.yml reconciled 2026-07-01; source AKDB:plugins/AssetLoaderStudio/architecture.md -->
# Quickstart

## Goal

Open Asset Loader Studio, submit a runtime load request, inspect a table snapshot, preview a
governed operation, and apply only after the preview is allowed.

## First Run

1. Enable **Asset Loader Studio** and restart Unreal Editor if requested.
2. Open **Tools > Tiny Tools > Asset Loader Studio**.
3. Choose **Guided** mode for the normal first run. Use **Simple** when you only want inspection.
4. Enter a known full object path such as `/Game/Data/DT_Items.DT_Items` or a DataAsset path you
   control, then click **Inspect**.
5. Review the returned job status, loaded paths, partial failures, dependency graph, and diagnostics.
6. Capture a table snapshot from a DataAsset or DataTable you control.
7. Open **Validation** and resolve missing assets, duplicate rows, invalid references, or permission
   denials before attempting mutation.
8. Use **Preview Operation** for any create, duplicate, rename, retarget, repair, save, rollback, or
   delete action.
9. Use **Apply Operation** only when the preview reports an allowed profile decision, an acceptable
   risk level, and the targets are the assets you intended to change.
10. Review the apply report and save dirty packages through your normal Unreal/source-control workflow.

## Blueprint And Runtime Entry Points

- `SubmitLoadRequest` starts a runtime load request and returns a job status.
- `CaptureTableSnapshot` reads structured table data for validation and graph work.
- `PreviewOperation` evaluates a planned mutation against a permission profile before apply.

Keep UCM and MCP integrations optional; the workspace and runtime subsystem are the standalone first-use path.

# Asset Loader Studio

Asset Loader Studio is a standalone Unreal plugin for structured asset-data work.

Current version: `1.0.0`. Publication state: `In Publishment`.

runtime load jobs, Blueprint access, table snapshots, dependency graphs, validation, governed
preview/apply workflows, and audit records.

Not a verbatim copy of shipped docs.

## What It Does

- Submits runtime load requests and reports job status, progress, partial failures, and diagnostics.
- Captures DataAsset/DataTable snapshots for row, field, and dependency inspection.
- Previews create, duplicate, rename, retarget, repair, save, rollback, and delete operations before apply.
- Uses permission profiles, plan hashes, audit records, and apply reports for governed mutation.
- Exposes optional UCM/UMCP routes over the same standalone runtime/editor services.

## Best Entry Points

- Use the shipped `Documentation/QUICKSTART.md` for first-run workspace and runtime load flow.
- Use `Documentation/UserManual.md` for editor workspace usage.
- Use `Documentation/SettingsReference.md`, `Documentation/ValidationAndRepair.md`, and `Documentation/TROUBLESHOOTING.md` for governance, validation, and repair behavior.
- Use the generated ProductImages gallery for current visual overview media.

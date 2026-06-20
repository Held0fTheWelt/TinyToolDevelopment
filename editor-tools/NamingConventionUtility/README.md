# Naming Convention Utility

Naming Convention Utility helps teams apply Unreal asset prefixes, suffixes, and cleanup rules through a preview-first rename workflow. It is built around reviewable plans, skip reasons, and guarded AssetTools execution rather than blind string replacement.

Not a verbatim copy of shipped docs.

## What It Does

- Stores naming rules in a DataAsset or imports them from DataTable rows.
- Builds non-mutating rename previews before any asset changes happen.
- Detects unsupported types, invalid names, existing targets, duplicate targets, and stale assets.
- Applies accepted renames through Unreal AssetTools and optional redirector cleanup.
- Provides optional UCM/UMCP routes for preview, apply, import, defaults, clear, and job status workflows.

## Best Entry Points

- Use the shipped `Documentation/QUICKSTART.md` for a first preview/apply pass.
- Use `Documentation/UserManual.md` for Content Browser actions and DataTable import.
- Use `Documentation/SettingsReference.md` and `Documentation/TROUBLESHOOTING.md` for rule source, confirmation, redirector, and skip-reason behavior.

Fab listing: <https://www.fab.com/listings/60aefcc0-6464-4a69-98d1-7ba02c6e06f2>

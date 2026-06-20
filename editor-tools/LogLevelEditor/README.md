# LogLevelEditor

LogLevelEditor is a focused Unreal Editor surface for discovering log categories, inspecting runtime/default verbosity, hiding noisy channels, and persisting intentional verbosity overrides in a DataAsset.

Not a verbatim copy of shipped docs.

## What It Does

- Scans configured source roots for Unreal log-category macros.
- Shows category verbosity so teams can tune diagnostics without editing config by hand.
- Stores intentional overrides in a versionable DataAsset.
- Lets users hide temporary or persistent noisy categories without deleting scan evidence.
- Exposes optional UCM/UMCP routes for scan, query, set, hide, clear, and job status flows.

## Best Entry Points

- Use the shipped `Documentation/QUICKSTART.md` for a first category scan and verbosity change.
- Use `Documentation/UserManual.md` for dashboard and DataAsset workflows.
- Use `Documentation/SettingsReference.md` and `Documentation/TROUBLESHOOTING.md` for scan roots, hidden channels, and persistence behavior.

Fab listing: <https://www.fab.com/listings/e9d934de-0432-452d-b899-be2461859f76>

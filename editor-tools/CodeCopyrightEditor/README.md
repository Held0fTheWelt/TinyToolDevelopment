# Code Copyright Editor

Code Copyright Editor keeps Unreal project and source-file copyright notices consistent through a scan-first workflow. It supports editor review, selected rewrites, project notice updates, commandlet checks, and JSON/SPDX/REUSE-style reports while avoiding legal-proof claims.

Not a verbatim copy of shipped docs.

## What It Does

- Configures owner, license, templates, scan scope, protection markers, and report behavior.
- Scans source without mutation and classifies files before any rewrite is attempted.
- Applies only selected, changeable source notice updates and project notice changes.
- Writes local release or CI evidence reports from the same result model used by the UI.
- Exposes optional UCM/UMCP routes for scan, apply, notice update, report writing, and job status workflows.

## Best Entry Points

- Use the shipped `Documentation/QUICKSTART.md` for first scan and selected apply flow.
- Use `Documentation/UserManual.md` and `Documentation/SettingsReference.md` for template, metadata, and scan-scope setup.
- Use `Documentation/CommandletAndCI.md`, `Documentation/ReportsAndCompliance.md`, and `Documentation/TROUBLESHOOTING.md` for headless checks and report behavior.

Fab listing: <https://www.fab.com/listings/e30d9b22-9c8b-41ff-8887-d2cce63a119f>

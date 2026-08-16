# Validation and Repair

Validation runs during table snapshot capture and records findings on the snapshot and affected rows.

Current diagnostics include:

- empty source asset path
- missing source asset
- unsupported source type
- missing DataTable row struct
- empty or duplicate row ids
- invalid referenced object paths
- missing referenced asset packages
- permission action, root, row, asset, dry-run, and destructive-action denials
- approval required before apply
- target apply failures
- invalid mutation destinations
- unsupported create classes
- source/template assets missing during create, duplicate, rename, save, or delete
- save, rollback, and destructive approval failures

Guided repair flow:

1. Inspect the source asset.
2. Open **Validation** and identify the affected row and field.
3. Enter the row id, field id, and replacement value.
4. Preview the operation.
5. Apply only after the preview is allowed by the active profile.
6. Review dirty packages and save explicitly.

Mutation workflows:

1. Stage the operation kind: create, duplicate, rename, retarget, repair, save, rollback, or delete.
2. Preview and inspect planned actions, required packages, risk, and recovery plan.
3. Apply only after the preview is allowed. Destructive delete requires an explicit destructive approval token.
4. Review the apply report for created, renamed, deleted, saved, mutated assets, and recovery artifacts.
5. Use Unreal undo immediately for transaction rollback, or restore from source control/package backups when needed.

## Reading A Finding

Each finding is structured data: code, severity, message, affected asset path, affected row id,
affected field id, and next action. Use the affected row/field to jump from a validation issue back
to the table row you need to repair.

## Safe Repair Pattern

- Fix one category of findings at a time.
- Prefer retarget or clear-field repairs before destructive deletes.
- Re-run validation after apply.
- Keep the apply report with your review notes when the change is part of a release cleanup.

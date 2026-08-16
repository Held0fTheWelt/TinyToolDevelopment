<!-- doc-provenance: product-facts.yml reconciled 2026-07-01; source AKDB:plugins/AssetLoaderStudio/architecture.md -->
# Asset Loader Studio User Manual

Open the workspace from **Tiny Tools -> Asset Loader Studio -> Asset Loader Studio**.

Asset Loader Studio is built around one review loop: inspect, validate, preview, apply, audit. You
can stop at inspection, or continue into governed edits when the active permission profile allows it.

The workspace contains seven views:

- **Graph** shows asset, row, field, reference, and diagnostic nodes.
- **Table** shows schema-aware DataAsset/DataTable rows and editable fields.
- **Validation** explains missing references, invalid paths, duplicate ids, and permission blocks.
- **Jobs** shows the latest runtime load request status.
- **Inspector** shows the active mode, permission profile, last preview, and last apply report.
- **History** keeps recent workspace actions.
- **Governance** shows active profile, route overrides, audit status, and profile actions.

Modes control mutation authority:

- **Simple** uses the read-only profile.
- **Guided** allows safe staged edits with approval.
- **Expert** allows broader bulk/persist previews and still requires approval before apply.

Use **Inspect** after entering a full object path such as `/Game/Data/DT_Items.DT_Items`. Use the
Row, Field, and New Value inputs to preview a structured field update. **Apply** only runs the last
approved preview and marks changed packages dirty for explicit saving.

## Review Loop

1. Inspect the source asset.
2. Check the graph/table state and diagnostics.
3. Select a profile that matches the amount of authority you need.
4. Preview the operation and verify targets, plan hash, affected counts, risk, and recovery guidance.
5. Apply only the preview you just reviewed.
6. Inspect the apply report and audit history.
7. Save dirty packages manually after review.

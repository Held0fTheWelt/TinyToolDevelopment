<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/CodeCopyrightEditor/architecture.md -->
# User Manual

This manual explains the complete editor workflow for Code Copyright Editor.

## Purpose

Code Copyright Editor manages copyright notice text in two places:

- The Unreal Engine project-level copyright notice.
- Source-file headers across configured project and plugin folders.

The plugin is built for controlled source rewrites. It scans first, shows a preview, lets the user select files, and only writes selected changeable files after confirmation.

## Opening The Tool

After enabling the plugin, open:

```text
Tools > Code Tools > Code Copyright Editor
```

The plugin also exposes configuration under:

```text
Project Settings > Plugins > Code Copyright Editor
```

## Main Workflow

1. Configure identity, license, template, scope, and protection settings.
2. Save the settings.
3. Update the Project Settings notice if needed.
4. Scan the codebase.
5. Review status badges and previews.
6. Add optional per-file metadata.
7. Select only the files that should be rewritten.
8. Apply selected files.
9. Run another scan to verify.
10. Export reports or run the commandlet in CI.

Scanning never writes source files. Applying only rewrites checked files that are classified as changeable.

## Editor Tabs

The main editor window is organized into focused tabs:

| Tab | Purpose |
| --- | --- |
| `Configure` | Edit templates, owner/license settings, scan scope, protection rules, and project notice settings. |
| `Scan & Review` | Run scans, inspect file statuses, select changeable files, exclude files, and compare existing/proposed notices. |
| `File Metadata` | Add or clear selected-file information and descriptions rendered by metadata tokens. |
| `Apply & Reports` | Confirm selected rewrites and export the latest editor JSON scan report. |
| `Help` | Read the built-in workflow guide and status legend. |

Tab selection changes only the visible page. Scan results, selected file, metadata drafts, preview, and status output are shared across tabs.

## Configure

Use the settings panel and template editors to define:

- Who owns the code.
- Which license text should be referenced.
- Which folders and file extensions should be scanned.
- Which folders or files should be excluded.
- Which notices are considered owned.
- Which notices should be protected.
- Which templates should be rendered into files.

Use `Save` after changing settings or metadata. The values are saved into project editor config.

## Project Settings Notice

The `Update Project Notice` action writes the rendered project notice to Unreal's project copyright field:

```text
Project Settings > Project > Description > Legal > Copyright Notice
```

This action does not rewrite source files. It only updates the global project setting.

## Source File Notice

The source template is rendered for each supported source file. It can include global project values and file-specific values such as file name, path, plugin product name, module name, and metadata.

The default template is intended for Fab/EULA-oriented plugin products and includes REUSE/SPDX-oriented tags:

```text
/* {CopyrightText}
 * SPDX-FileCopyrightText: {CopyrightText}
 * SPDX-License-Identifier: {LicenseIdentifier}
```

See [TemplateReference.md](TemplateReference.md) for all tokens and examples.

## Scan Files

`Scan Files` walks through the configured scan roots, filters files by extension and exclusion rules, then classifies each eligible file.

The scan result includes:

- File path.
- Product name.
- Current notice.
- Proposed notice.
- Status.
- Message.
- Whether the file can be applied.

No source file is changed during scanning.

## Review List

Each row in the review list represents one scanned file. Select a row to view:

- The existing notice.
- The proposed rendered notice.
- The scanner decision.
- The product name used for `{ProductName}`.

Use the checkbox to decide whether that file should be included in `Apply Selected`.

## Status Values

| Status | Meaning | Apply behavior |
| --- | --- | --- |
| `OK` | The file already matches the rendered template. | Not needed. |
| `MISSING` | No compatible notice was found. | Can be inserted when enabled. |
| `REPLACE` | An owned notice or Unreal placeholder can be replaced. | Can be rewritten. |
| `PROTECTED` | A foreign, Epic, or third-party notice was found. | Not rewritten automatically. |
| `CONFLICT` | Owned and protected markers appear together. | Manual review required. |
| `EXCLUDED` | The file matched an exclusion rule. | Not processed. |
| `READ_ERROR` | The file could not be read. | Not processed. |
| `WRITE_ERROR` | The file could not be saved. | Not processed. |
| `UPDATED` | The file was written in the last apply pass. | Run another scan to verify. |

## Per-File Metadata

Per-file metadata adds context to one file without changing the global template.

Available metadata:

- `File Information`
- `Description`

Recommended workflow:

1. Scan files.
2. Select a file.
3. Enter file information or description.
4. Click `Save File Metadata`.
5. Make sure the template contains `{FileMetadataBlock}`.
6. Review the preview.
7. Apply the file if the rendered notice is correct.

`Clear File Metadata` removes the stored metadata for the selected file.

## Selection Actions

| Action | Result |
| --- | --- |
| `Select Changeable` | Checks all rows that can be safely rewritten. |
| `Clear` | Unchecks all review rows. |
| `Exclude File` | Adds the selected file to exact exclusions and refreshes the scan. |
| `Apply Selected` | Rewrites only checked, changeable files after confirmation. |
| `Export JSON` | Writes the latest editor scan to `Saved/CodeCopyrightEditor/LastCopyrightScan.json`. |

## Apply Selected

Before applying, the editor asks for confirmation. Protected and conflict files remain untouched.

After applying, the tool runs another scan and shows:

- Apply result.
- Current scan result.
- Updated status lines.

Use source control before bulk rewrites. For an extra first-pass safety net, enable `Create Backup Before Write`.

## Suggested First Production Pass

1. Commit or stash unrelated work.
2. Configure owner and license settings.
3. Scan the codebase.
4. Exclude third-party or generated paths.
5. Apply a small test selection.
6. Review the diff in source control.
7. Apply the remaining selected files.
8. Run the commandlet without `-NoFail`.
9. Save generated reports with release artifacts if your workflow requires it.

## What The Plugin Does Not Do

Code Copyright Editor does not:

- Decide legal ownership.
- Grant license rights.
- Validate third-party licenses.
- Replace legal review.
- Rewrite protected notices automatically.
- Run in packaged games.

It provides a consistent technical workflow for notices, reports, and CI checks.

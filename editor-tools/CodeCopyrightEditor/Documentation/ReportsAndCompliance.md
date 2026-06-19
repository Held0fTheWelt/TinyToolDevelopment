# Reports And Compliance Notes

Code Copyright Editor can produce reports from the commandlet and a JSON report from the editor UI.

The reports help with review, release preparation, and CI gates. They are not legal certification.

## Report Outputs

| File | Produced by | Purpose |
| --- | --- | --- |
| `CodeCopyrightReport.json` | Commandlet | Machine-readable scan result. |
| `CodeCopyrightReport.spdx` | Commandlet | SPDX 2.3 Tag/Value style source file report. |
| `REUSE-Report.md` | Commandlet | Human-readable REUSE/SPDX-oriented review report. |
| `LastCopyrightScan.json` | Editor UI | Latest editor scan export. |

The commandlet report directory defaults to:

```text
Saved/CodeCopyrightEditor/Reports
```

The editor JSON export writes to:

```text
Saved/CodeCopyrightEditor/LastCopyrightScan.json
```

## JSON Report

Top-level fields:

| Field | Meaning |
| --- | --- |
| `scanned` | Total files found under scan roots before eligibility filtering. |
| `eligible` | Files with supported extensions and no exclusion match. |
| `changeable` | Files that can be inserted, replaced, or were changed in apply mode. |
| `unchanged` | Files already matching the rendered template. |
| `skipped` | Files skipped due to exclusion, protection, conflict, or disabled insertion. |
| `protected` | Files with protected foreign or third-party notices. |
| `conflicts` | Files with both own and protected markers. |
| `failed` | Files with read or write errors. |
| `files` | Per-file result objects. |

Per-file fields:

| Field | Meaning |
| --- | --- |
| `status` | `OK`, `MISSING`, `REPLACE`, `PROTECTED`, `CONFLICT`, `EXCLUDED`, `READ_ERROR`, `WRITE_ERROR`, `UPDATED`, or `UNKNOWN`. |
| `relativePath` | Project-relative file path. |
| `absolutePath` | Absolute file path on the current machine. |
| `productName` | Product name rendered for the file. |
| `message` | Scanner decision text. |
| `canApply` | Whether the file can be rewritten automatically. |
| `wouldChange` | Whether the rendered notice differs from the current file. |
| `changed` | Whether the file was written in an apply pass. |

## SPDX-Style Report

`CodeCopyrightReport.spdx` is written in SPDX 2.3 Tag/Value style. It includes:

- SPDX document metadata.
- Tool creator information.
- Generation timestamp.
- One source file section per scanned result.
- File SHA1 checksums where available.
- License expression from `LicenseIdentifier`, unless the file is protected.
- File comments containing status, product, and scanner message.

For protected notices, license conclusion fields are written as `NOASSERTION`, because the plugin intentionally does not claim the license for foreign notices.

## REUSE-Style Report

`REUSE-Report.md` is a readable review report with:

- Project name.
- Generation timestamp.
- Expected license expression.
- CI pass/fail summary.
- Scan metrics.
- REUSE notes.
- Per-file result table.

It reminds teams to keep the following lines in source templates:

```text
/* {CopyrightText}
 * SPDX-FileCopyrightText: {CopyrightText}
 * SPDX-License-Identifier: {LicenseIdentifier}
```

## Compliance Positioning

The plugin is best described as:

- REUSE/SPDX-oriented.
- CI-friendly.
- Review-focused.
- Helpful for consistent notice application.

Avoid describing the output as legally certified or automatically compliant. The reports document what the scanner saw and what template settings were used.

## Suggested Release Evidence

For marketplace submissions or internal release archives, keep:

- The final `REUSE-Report.md`.
- The final `CodeCopyrightReport.json`.
- The final `CodeCopyrightReport.spdx`, if your workflow uses SPDX artifacts.
- The source control diff that applied notice changes.
- Any manual decisions for protected or conflict files.

## Third-Party Code

Third-party code often has its own license and notice requirements. Code Copyright Editor protects unknown or marked foreign notices by default, but humans should still review:

- Vendor folders.
- External dependencies.
- Epic sample code.
- Generated files with copied headers.
- Mixed-license source files.

Do not rewrite third-party notices unless you have verified that doing so is appropriate.

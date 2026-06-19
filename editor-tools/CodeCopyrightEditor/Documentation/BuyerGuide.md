# Code Copyright Editor Buyer Guide

Code Copyright Editor is an editor-only Unreal Engine plugin for keeping source-file copyright notices consistent across a project or plugin. It helps teams prepare professional Fab/EULA-oriented headers, review existing notices before changing them, add per-file information, and run the same check from CI.

This guide is written for buyers who want to understand what the plugin does, how to use it safely, and how it fits into a production workflow.

## How To Use This Guide

Start with the first-run checklist below if you only want to use the plugin. Open the reference pages only when you need details:

- [UserManual.md](UserManual.md): complete editor workflow.
- [TemplateReference.md](TemplateReference.md): all template tokens and examples.
- [CommandletAndCI.md](CommandletAndCI.md): commandlet, CI, and report automation.
- [FAQ.md](FAQ.md): short buyer-facing answers.
- [README.md](README.md): full documentation index.

The screenshot files are optional reference assets. You do not need them for the workflow, and some Markdown viewers may not render the SVG previews inline. Open them directly if you want a quick visual reference:

- [Workflow overview](Screenshots/01-workflow-overview.svg)
- [Review and metadata](Screenshots/02-review-and-metadata.svg)
- [CI report](Screenshots/03-ci-report.svg)

## What You Get

- A dedicated editor window for editing copyright notice templates.
- Project Settings integration for the Unreal `Copyright Notice` field.
- A scanner for source files under configured project or plugin folders.
- Review results with status badges, previews, and selectable apply targets.
- Per-file information and descriptions rendered into file headers.
- Protection for foreign, Epic, and third-party notices.
- A commandlet for CI checks and automated reporting.
- JSON, SPDX-style, and REUSE-style report output.
- Example scripts and a GitHub Actions starter workflow.

The plugin does not add runtime gameplay code and is intended for editor and pipeline use.

## Recommended First Run

1. Enable the plugin in Unreal Engine and restart the editor if required.
2. Open `Tools > Code Tools > Code Copyright Editor`.
3. Review `Project Settings > Plugins > Code Copyright Editor`.
4. Set your owner name, license name, license URL, and license identifier.
5. Keep source control enabled before applying changes to many files.
6. Click `Scan Files` before writing anything.
7. Select only the files you want to update.
8. Review the preview for one or two representative files.
9. Click `Apply Selected`.
10. Run another scan to confirm the result.

For the safest first pass, enable backups in the settings or apply changes to a small selection first.

## Main Editor Window

Open the tool from:

```text
Tools > Code Tools > Code Copyright Editor
```

The window is organized into focused workflow tabs:

- `Configure`: edit identity, license, scope, protection, and template settings.
- `Scan & Review`: classify files without writing, inspect statuses, select changeable files, and compare notices.
- `File Metadata`: add per-file information and descriptions for the selected file.
- `Apply & Reports`: rewrite checked files after confirmation and export the editor JSON report.
- `Help`: read the built-in workflow guide and status legend.

The preview shows the existing notice and the rendered replacement for the selected file. If no file is selected, it shows a template preview.

## Project Settings Notice

Unreal Engine has a project-level copyright field under:

```text
Project Settings > Project > Description > Legal > Copyright Notice
```

Code Copyright Editor can render the `Project Settings Notice` template and write it into that Unreal field. This keeps the global project notice aligned with the same owner, license, and product information used in your source headers.

Use this for the high-level project notice. Use the source template for individual `.h`, `.cpp`, `.cs`, shader, and related source files.

## Source Notice Template

The source template is the header that gets rendered at the top of supported source files. It supports tokens that are replaced per project and per file.

Common tokens:

```text
{CopyrightText}
{OwnerName}
{ContactEmail}
{ProductName}
{ModuleName}
{FileName}
{RelativeFilePath}
{Year}
{LicenseName}
{LicenseUrl}
{LicenseIdentifier}
{FileInformation}
{FileDescription}
{FileMetadataBlock}
```

Recommended REUSE/SPDX-oriented lines near the top:

```text
/* {CopyrightText}
 * SPDX-FileCopyrightText: {CopyrightText}
 * SPDX-License-Identifier: {LicenseIdentifier}
```

For Fab products that use the Fab Standard EULA, a custom license reference such as this is appropriate in the plugin settings:

```text
LicenseRef-Fab-Standard-EULA
```

`LicenseRef-*` values are useful when a license is product-specific or not represented by a standard SPDX license identifier.

## Example Fab-Oriented Header

You can use the default template as a starting point and adjust wording for each product line:

```text
/* {CopyrightText}
 * SPDX-FileCopyrightText: {CopyrightText}
 * SPDX-License-Identifier: {LicenseIdentifier}
 *
 * This file is part of the "{ProductName}" Unreal Engine plugin.
{FileMetadataBlock}
 *
 * Use of this software is governed by the {LicenseName}
 * (EULA) applicable to this product, available at:
 * {LicenseUrl}
 *
 * Except as expressly permitted by the Fab Standard EULA, any reproduction,
 * distribution, modification, or use of this software, in whole or in part,
 * is strictly prohibited.
 *
 * This software is provided on an "AS IS" basis, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, either express or implied, including but not
 * limited to warranties of merchantability, fitness for a particular purpose,
 * and non-infringement.
 * available at: {LicenseUrl}.
 */
```

The final line can be part of the template. Place it before the closing `*/` if it belongs inside the header comment.

## Per-File Information And Descriptions

Some files need more context than a generic project header. Code Copyright Editor supports metadata per file:

- `File Information`: short technical context, module responsibility, generated/source notes, or ownership details.
- `Description`: a readable explanation of what the file is for.
- `Relative File Path`: the project-relative path that connects the metadata to the file.

The easiest way to add metadata:

1. Run `Scan Files`.
2. Select a file in the review list.
3. Fill `File Information` and/or `Description`.
4. Click `Save File Metadata`.
5. Make sure the source template contains `{FileMetadataBlock}`.

`{FileMetadataBlock}` formats the file path, information, and description as comment-safe header lines. If you prefer full control, use `{FileInformation}` and `{FileDescription}` directly in the template.

## Scan Results

After scanning, every supported file receives a status:

| Status | Meaning | Typical action |
| --- | --- | --- |
| `OK` | The file already matches the rendered template. | No action needed. |
| `MISSING` | No compatible notice was found. | Review preview, then apply if this is your file. |
| `REPLACE` | An owned or Unreal placeholder notice can be replaced. | Usually safe after preview. |
| `PROTECTED` | A foreign, Epic, or third-party notice was detected. | Leave untouched unless you review manually. |
| `CONFLICT` | Owned and protected markers appear together. | Inspect the file manually. |
| `EXCLUDED` | The file or path matches an exclude rule. | Adjust scope only if needed. |
| `READ_ERROR` | The file could not be loaded. | Check file permissions or path. |
| `WRITE_ERROR` | The file could not be saved. | Check locks, permissions, or source control state. |
| `UPDATED` | The file was written in the last apply pass. | Run another scan to confirm. |

Protected and conflict files are not rewritten automatically.

## Scope And Exclusions

The scanner looks under the configured `Scan Root Paths`. Defaults are:

```text
Source
Plugins
```

Supported file extensions include common C++, C#, and shader source extensions such as:

```text
.h, .hpp, .hh, .inl, .c, .cc, .cpp, .cxx, .cs, .usf, .ush
```

Default excluded folders include build, generated, external, third-party, resource, and saved-output paths. You can also exclude exact files from the editor when a file should stay untouched.

Good examples for exclusions:

```text
ThirdParty
External
*.generated.h
Plugins/SomePlugin/Source/Vendor/File.cpp
```

## Notice Protection

The plugin is intentionally conservative around unknown notices.

`Own Notice Markers` identify headers that belong to your project and can be replaced. Good markers are your owner name, your license identifier, your product name, or a known old notice line.

`Protected Notice Markers` identify notices that should not be rewritten automatically. Defaults include common third-party and Epic notice markers.

If a file is marked `PROTECTED`, review it manually. It may belong to a dependency, a sample, generated code, or third-party code with different license requirements.

## Commandlet And CI

The commandlet lets you run the same check outside the editor:

```powershell
UnrealEditor-Cmd.exe "D:\Path\To\Project.uproject" -run=CodeCopyrightCheck -unattended -nop4 -nosplash -NoShaderCompile -ReportDir="Saved\CodeCopyrightEditor\Reports"
```

Useful switches:

| Switch | Purpose |
| --- | --- |
| `-Fix` | Rewrite changeable files before producing reports. |
| `-ReportDir=<Path>` | Write reports to a project-relative or absolute folder. |
| `-FailOnProtected` | Treat protected notices as CI failures. |
| `-NoJson` | Skip the JSON report. |
| `-NoSpdx` | Skip the SPDX-style report. |
| `-NoReuse` | Skip the REUSE-style Markdown report. |
| `-NoFail` | Always return exit code `0` after writing reports. |
| `-Help` | Print commandlet usage. |

CI fails by default when files would change, conflicts exist, or files could not be read or written. Protected notices are reported separately and only fail CI when `-FailOnProtected` is used.

A GitHub Actions starter workflow is included here:

```text
Plugins/CodeCopyrightEditor/Documentation/CI/GitHubActions-CodeCopyrightCheck.yml
```

The workflow expects a runner that already has Unreal Engine installed.

## Reports

When the commandlet runs, it can write:

- `CodeCopyrightReport.json`: machine-readable scan summary.
- `CodeCopyrightReport.spdx`: SPDX 2.3 Tag/Value style report.
- `REUSE-Report.md`: human-readable REUSE/SPDX review report.

These reports are intended for project review, pipeline gates, and release preparation. They help document the state of source notices, but they are not a legal certification.

## Practical Workflows

### New Plugin Or Project

1. Set identity and license fields.
2. Keep the default source template or adapt it to your product name.
3. Scan the codebase.
4. Apply missing notices to your own source files.
5. Export reports before submission or release.

### Existing Plugin With Old Headers

1. Add old notice lines to `Own Notice Markers`.
2. Scan first and inspect `REPLACE` results.
3. Exclude or protect files that are not yours.
4. Apply selected files in batches.
5. Commit the result after a clean rescan.

### Project With Third-Party Source

1. Keep `Protect Foreign Notices` enabled.
2. Add vendor folders to excluded path fragments.
3. Review every `PROTECTED` and `CONFLICT` file manually.
4. Use `-FailOnProtected` only if your team wants protected files to block CI.

### Release Or Fab Submission

1. Run the editor scan.
2. Fix all `MISSING`, `REPLACE`, `CONFLICT`, `READ_ERROR`, and `WRITE_ERROR` items.
3. Run the commandlet without `-NoFail`.
4. Save the generated reports as release evidence if your workflow needs them.

## Troubleshooting

`The commandlet is not found`

Make sure the plugin is enabled for the project and the editor has been restarted or rebuilt after installation.

`Files are marked PROTECTED`

The scanner found notice text that does not match your own markers. Add a clear owned marker only if the file really belongs to your project. Otherwise exclude the file or leave it untouched.

`The header does not use the plugin name I expected`

When `Prefer Plugin FriendlyName` is enabled, files inside a plugin use the plugin descriptor `FriendlyName` for `{ProductName}`. Disable it if you want the fallback product name everywhere.

`CI fails although the editor looked fine`

Run the commandlet with the same project, same config, and same scan roots as the editor. Also check whether CI sees files that your local editor path excludes.

`Write errors appear`

Check source control checkout state, read-only files, editor locks, antivirus locks, or write permissions.

## Good Habits

- Always scan before applying.
- Preview representative files before bulk changes.
- Keep third-party and generated folders excluded.
- Use source control for every rewrite pass.
- Keep templates short enough to stay readable in source files.
- Use `LicenseRef-*` for custom marketplace EULAs.
- Treat REUSE/SPDX output as review evidence, not legal advice.

## Legal Note

Code Copyright Editor helps apply and review notice text consistently. It does not decide legal ownership, grant rights, validate third-party licenses, or replace professional legal advice. If your project contains third-party code, generated code, marketplace samples, or mixed-license files, review those files carefully before rewriting notices.

## Included Documentation

- `Documentation/README.md`: compact technical overview.
- `Documentation/BuyerGuide.md`: this buyer-oriented guide.
- `Documentation/Screenshots/`: visual documentation assets.
- `Documentation/CI/GitHubActions-CodeCopyrightCheck.yml`: CI starter workflow.

## References

- REUSE Specification: https://reuse.software/spec-3.3/
- SPDX Specification 2.3: https://spdx.github.io/spdx-spec/v2.3/
- Fab Standard EULA: https://www.fab.com/eula

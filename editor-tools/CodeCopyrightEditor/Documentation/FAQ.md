# FAQ

## What is Code Copyright Editor used for?

Code Copyright Editor helps Unreal Engine developers manage consistent copyright notices across Project Settings and source files. It can scan, preview, update, and report source-file headers from one editor workflow.

## Does the plugin affect runtime gameplay code?

No. Code Copyright Editor is an editor-only tool. It is intended for development, review, documentation, and CI workflows.

## Can it update an entire codebase automatically?

Yes, but only after scanning and review. The editor shows which files can be changed, which files are protected, and what the proposed replacement will look like before applying changes.

## Does it protect third-party or Epic notices?

Yes. The scanner is designed to protect foreign, Epic, and third-party notices from automatic rewriting. Protected and conflict files should be reviewed manually.

## Can I customize the copyright template?

Yes. You can edit the source-file notice template and the Project Settings notice template. Tokens such as product name, file path, year, license identifier, and per-file description can be rendered automatically.

## Does it support SPDX or REUSE workflows?

The plugin provides REUSE/SPDX-oriented templates and reports, including SPDX-style and REUSE-style output. These reports are intended to support review and CI workflows, but they are not legal certification.

## Can I add individual information per file?

Yes. Selected files can store their own file information and description. These values can be rendered into the header through template tokens.

## Is there a commandlet for CI?

Yes. The included `CodeCopyrightCheck` commandlet can scan the project, optionally fix changeable files, write reports, and fail CI when copyright notices are out of sync.

## Which report formats are included?

The commandlet can generate a machine-readable JSON report, an SPDX-style report, and a human-readable REUSE-style Markdown report. The editor UI can also export the latest scan as JSON.

## Should I use source control before applying changes?

Yes. The plugin is built for controlled workflows, but source-file rewrites should always be done with source control enabled so changes can be reviewed and reverted if needed.

## Can it be used for plugins sold on Fab?

Yes. The default template and settings are designed for Fab/EULA-oriented plugin products. You can adjust owner, product, license, URL, and custom wording for each product line.

## Does it replace legal advice?

No. It helps apply and review notice text consistently. It does not decide ownership, validate third-party licenses, or provide legal advice.

## Why are some files protected instead of changed?

The plugin detected a notice that does not clearly belong to your project or matched a protected marker. This is intentional and helps avoid accidental third-party notice rewrites.

## Can I exclude individual files?

Yes. Select a scan row and use `Exclude File`, or add project-relative paths to `ExcludedFilePaths` in settings.

## Can I run it without failing CI?

Yes. Use `-NoFail` to write reports while always returning exit code `0`.

## Can the commandlet fix files automatically?

Yes. Use `-Fix` to rewrite changeable files before the final report is produced. Use this with source control and review the resulting diff.

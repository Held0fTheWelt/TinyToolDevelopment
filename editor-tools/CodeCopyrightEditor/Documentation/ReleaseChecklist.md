# Release Checklist

Use this checklist before shipping a project or submitting a plugin build.

## Before First Use

- Enable the plugin.
- Restart Unreal Editor.
- Open `Tools > Code Tools > Code Copyright Editor`.
- Open `Project Settings > Plugins > Code Copyright Editor`.
- Confirm the settings match your product.
- Make sure source control is active.

## Product Identity

- Owner name is correct.
- Contact email is correct or intentionally empty.
- Product fallback name is correct.
- Plugin `FriendlyName` values are correct.
- Start year is correct.
- Current year range is expected.

## License

- License name is correct.
- License URL is correct.
- License identifier is correct.
- Custom Fab/EULA license identifiers use `LicenseRef-*`.
- Legal wording has been reviewed for your product.

## Template

- Source template starts with a plain copyright line such as `{CopyrightText}`.
- Source template contains `SPDX-FileCopyrightText`.
- Source template contains `SPDX-License-Identifier`.
- Project Settings template is appropriate for the product.
- The final line is inside the comment block.
- `{FileMetadataBlock}` is present if per-file metadata should appear.
- Preview output looks correct.

## Scope

- Scan roots are correct.
- Third-party folders are excluded.
- Generated folders are excluded.
- Build output folders are excluded.
- Exact file exclusions are intentional.
- File extension list matches the project's source types.

## Review

- `Scan Files` has been run.
- `OK` files are expected.
- `MISSING` files are reviewed.
- `REPLACE` files are reviewed.
- `PROTECTED` files are reviewed or intentionally excluded.
- `CONFLICT` files are resolved manually.
- `READ_ERROR` and `WRITE_ERROR` items are fixed.

## Apply

- A source control diff is available.
- A small test apply has been reviewed.
- Bulk apply is confirmed.
- Another scan is clean after apply.
- Unwanted backups are removed or ignored if `CreateBackupBeforeWrite` was enabled.

## CI

- `CodeCopyrightCheck` commandlet runs locally.
- Reports are written to the expected directory.
- CI runner uses the correct Unreal Engine version.
- CI runner uses the correct project path.
- GitHub Actions or equivalent CI uploads reports.
- The intended failure policy is selected.

## Release Evidence

- `REUSE-Report.md` is archived if needed.
- `CodeCopyrightReport.json` is archived if needed.
- `CodeCopyrightReport.spdx` is archived if needed.
- Manual decisions for protected files are documented.
- Final source control diff has been reviewed.

## Fab Submission Notes

- The plugin is described as editor-only.
- Supported platforms match tested platforms and the module `PlatformAllowList`.
- Untested platforms such as Mac or Linux are not selected in the Fab listing.
- Version notes explain that Unreal-generated plugin binaries are required for this code plugin.
- Empty `Content` folders are removed when `CanContainContent=false`.
- If content is added later, all assets live below one correctly named pack folder.
- `FilterPlugin.ini` includes intended root-level files such as `CHANGELOG.md`.
- Listing text does not promise legal certification.
- FAQ explains third-party notice protection.
- Documentation is included in the packaged plugin.
- Screenshots show the workflow, review view, and CI/report output.

# Troubleshooting

This page lists common issues and practical fixes.

## The Tool Does Not Appear In The Tools Menu

Check:

- The plugin is enabled for the project.
- Unreal Editor was restarted after enabling the plugin.
- The plugin compiled for the current Unreal Engine version.

Expected menu path:

```text
Tools > Code Tools > Code Copyright Editor
```

## The Project Settings Page Is Missing

Check:

- The plugin module loaded successfully.
- The project is using an editor build, not a packaged runtime build.
- The plugin is installed in the project or engine plugin folder.

Expected path:

```text
Project Settings > Plugins > Code Copyright Editor
```

## Scan Finds No Files

Check:

- `ScanRootPaths` contains folders that exist.
- Files use supported extensions.
- Excluded path fragments are not too broad.
- The project path is the one you expect.

Default scan roots are:

```text
Source
Plugins
```

## Too Many Files Are Skipped

Likely causes:

- A path fragment in `ExcludedPathFragments` matches too much.
- An exact path was added to `ExcludedFilePaths`.
- A wildcard in `ExcludedFilePatterns` matches more than intended.

Review exclusions and rescan.

## Files Are Marked PROTECTED

The scanner found notice-like text that does not match owned markers, or it matched protected markers.

Fix options:

- Leave the file untouched if it is third-party or Epic code.
- Add the vendor folder to exclusions.
- Add an owned marker only if the file truly belongs to your project.
- Review the file manually if ownership is unclear.

## Files Are Marked CONFLICT

A conflict means the notice matched both owned and protected logic.

Typical causes:

- An old project header includes a protected marker.
- A third-party file contains your owner name.
- Own markers are too broad.
- Protected markers are too broad.

Inspect the file manually and refine markers.

## Missing Notices Are Not Inserted

Check `InsertNoticeWhenMissing`.

If disabled, missing notices are reported but not inserted. Enable it when you want the plugin to add notices to owned files that have no header.

## The Wrong Product Name Is Rendered

If `PreferPluginFriendlyName` is enabled, files inside a plugin use the nearest `.uplugin` `FriendlyName`.

Fix options:

- Edit the plugin descriptor `FriendlyName`.
- Disable `PreferPluginFriendlyName`.
- Set a better `ProductNameFallback`.

## Per-File Metadata Does Not Appear

Check:

- The selected file metadata was saved.
- The `RelativeFilePath` matches the scan row.
- The source template contains `{FileMetadataBlock}`, `{FileInformation}`, or `{FileDescription}`.
- You rescanned or refreshed the preview after saving.

## The Last Template Line Is Missing

The multiline template editor supports real new lines. Put every line that belongs inside the header before the closing comment marker.

Example:

```text
 * available at: {LicenseUrl}.
 */
```

If text is placed after `*/`, it is outside the comment and may be treated as source code.

## Write Errors

Common causes:

- File is read-only.
- File is locked by another process.
- Source control checkout is required.
- User account lacks write permission.
- Antivirus or indexing tool temporarily locked the file.

Fix the file state, then run scan/apply again.

## Commandlet Is Not Found

Check:

- The plugin is enabled in the project.
- The plugin is compiled for the editor version.
- The command uses the correct project `.uproject`.
- The editor path points to `UnrealEditor-Cmd.exe`.

Command:

```powershell
UnrealEditor-Cmd.exe "D:\Path\To\Project.uproject" -run=CodeCopyrightCheck -Help
```

## CI Fails But Local Editor Looks Clean

Compare:

- Same branch and checkout.
- Same project config files.
- Same Unreal Engine version.
- Same scan roots.
- Same excluded paths.
- Same plugin version.
- Same commandlet switches.

CI may run from a different working directory or include files that are not present locally.

## Reports Are Not Written

Check:

- `-ReportDir` is valid.
- The runner/user can create the directory.
- The commandlet completed after scanning.
- Individual report switches did not disable all formats.

Use `-NoFail` to collect reports while investigating nonzero CI exits.

## BuildPlugin Fails Because A DLL Is Locked

If Unreal Editor is running, existing plugin DLLs can be locked on Windows.

Fix:

- Close Unreal Editor.
- Close tools that load the plugin DLL.
- Re-run the build.

This is an environment issue, not a documentation or report issue.

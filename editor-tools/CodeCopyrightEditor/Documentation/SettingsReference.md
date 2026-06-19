# Settings Reference

Code Copyright Editor settings are available under:

```text
Project Settings > Plugins > Code Copyright Editor
```

The editor window also exposes the most important template and workflow actions.

## Identity

| Setting | Default | Used by |
| --- | --- | --- |
| `OwnerName` | `Yves Tanas` | `{OwnerName}`, `{CopyrightText}`, reports |
| `ContactEmail` | `yves.tanas@gmx.de` | `{ContactEmail}` |
| `ProductNameFallback` | `PluginProject` | `{ProductName}` when no plugin friendly name is found |
| `CopyrightStartYear` | `2025` | `{Year}`, `{CopyrightText}` |

`{Year}` renders as the start year when it equals the current year. If the current year differs, it renders as a range such as `2025-2026`.

## License

| Setting | Default | Used by |
| --- | --- | --- |
| `LicenseName` | `Fab Standard End User License Agreement` | `{LicenseName}` |
| `LicenseUrl` | `https://www.fab.com/eula` | `{LicenseUrl}` |
| `LicenseIdentifier` | `LicenseRef-Fab-Standard-EULA` | `{LicenseIdentifier}`, reports |

Use standard SPDX identifiers for standard licenses, for example `MIT` or `Apache-2.0`. Use `LicenseRef-*` for custom or marketplace-specific licenses such as a product EULA.

## Templates

| Setting | Purpose |
| --- | --- |
| `SourceNoticeTemplate` | Header rendered into source files. |
| `ProjectSettingsNoticeTemplate` | Notice rendered into Unreal's project-level copyright field. |

The editor window provides larger multiline editors for both templates. See [TemplateReference.md](TemplateReference.md) for tokens and examples.

## File Metadata

`FileMetadata` stores optional per-file information:

| Field | Purpose |
| --- | --- |
| `RelativeFilePath` | Project-relative path used to match the metadata to a file. |
| `FileInformation` | Rendered by `{FileInformation}` and `{FileMetadataBlock}`. |
| `FileDescription` | Rendered by `{FileDescription}` and `{FileMetadataBlock}`. |

The editor can create and maintain entries from the selected scan row.

## Scope

| Setting | Default | Purpose |
| --- | --- | --- |
| `ScanRootPaths` | `Source`, `Plugins` | Folders scanned by `Scan Files`. |
| `SourceFileExtensions` | `.h`, `.hpp`, `.hh`, `.inl`, `.c`, `.cc`, `.cpp`, `.cxx`, `.cs`, `.usf`, `.ush` | Extensions treated as source files. |
| `ExcludedPathFragments` | `.git`, `.vs`, `Binaries`, `Content`, `DerivedDataCache`, `External`, `Intermediate`, `Resources`, `Saved`, `ThirdParty` | Folder/path fragments skipped during scans. |
| `ExcludedFilePaths` | Empty by default | Exact project-relative files skipped during scans. |
| `ExcludedFilePatterns` | `*.generated.h` | Wildcard patterns skipped during scans. |

Paths may be project-relative or absolute, depending on the field. For exact file exclusions, project-relative paths are recommended.

## Protection

| Setting | Default | Purpose |
| --- | --- | --- |
| `ProtectForeignNotices` | Enabled | Prevents unknown notice text from being rewritten automatically. |
| `TreatUnrealDefaultNoticesAsReplaceable` | Enabled | Allows Unreal placeholder/default notices to be replaced as project boilerplate. |
| `OwnNoticeMarkers` | Owner name, license identifier, Fab EULA text, Unreal placeholder text | Identifies notices that belong to this project. |
| `ProtectedNoticeMarkers` | Third-party and Epic copyright markers | Identifies notices that should not be rewritten automatically. |

Keep protection enabled for production projects. Only add an owned marker when you are certain that the notice belongs to your project.

## Behavior

| Setting | Default | Purpose |
| --- | --- | --- |
| `PreferPluginFriendlyName` | Enabled | Uses a `.uplugin` `FriendlyName` for `{ProductName}` when a file is inside a plugin. |
| `InsertNoticeWhenMissing` | Enabled | Allows the tool to add a notice to supported files that have none. |
| `CreateBackupBeforeWrite` | Disabled | Writes `.copyright.bak` backups before changing source files. |
| `MaxResultRowsInReport` | `40` | Limits rows printed in status text. |

For the first pass on an existing codebase, enabling backups is a conservative choice. Source control is still recommended.

## Recommended Baseline

For most Fab plugin products:

- Keep `ProtectForeignNotices` enabled.
- Keep `TreatUnrealDefaultNoticesAsReplaceable` enabled.
- Keep `ThirdParty`, `External`, `Binaries`, `Intermediate`, and `Saved` excluded.
- Use `LicenseRef-Fab-Standard-EULA` for Fab EULA products.
- Keep SPDX lines near the top of the source template.
- Use `{FileMetadataBlock}` for optional file-level context.

# Template Reference

Code Copyright Editor renders templates by replacing tokens with project and file values. Tokens can be written as `{TokenName}` or `${TokenName}`.

## Core Tokens

| Token | Source files | Project notice | Meaning |
| --- | --- | --- | --- |
| `{CopyrightText}` | Yes | Yes | Full copyright text, for example `Copyright (c) 2025-2026 Your Company or Name`. |
| `{OwnerName}` | Yes | Yes | Configured owner name. |
| `{ContactEmail}` | Yes | Yes | Optional configured contact email. |
| `{ProductName}` | Yes | Yes | Plugin friendly name, project name, or fallback product name. |
| `{ModuleName}` | Yes | Empty | Module/folder context inferred from the file path. |
| `{FileName}` | Yes | Empty | File name including extension. |
| `{RelativeFilePath}` | Yes | Empty | Project-relative source file path. |
| `{Year}` | Yes | Yes | Start year or year range. |
| `{LicenseName}` | Yes | Yes | Human-readable license name. |
| `{LicenseUrl}` | Yes | Yes | License URL. |
| `{LicenseIdentifier}` | Yes | Yes | SPDX expression or `LicenseRef-*` value. |
| `{FileInformation}` | Yes | Empty | Per-file information. |
| `{FileDescription}` | Yes | Empty | Per-file description. |
| `{FileMetadataBlock}` | Yes | Empty | Formatted file path, information, and description block. |

Project-level notices do not have a selected source file, so file-specific tokens render empty there.

## Recommended SPDX Lines

For Fab review and REUSE/SPDX-oriented headers, keep these lines near the top:

```text
/* {CopyrightText}
 * SPDX-FileCopyrightText: {CopyrightText}
 * SPDX-License-Identifier: {LicenseIdentifier}
```

For product-specific Fab EULA notices, a custom license reference can be used:

```text
LicenseRef-Fab-Standard-EULA
```

## Default Source Template

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

## Default Project Settings Template

```text
/* {CopyrightText}
 * SPDX-FileCopyrightText: {CopyrightText}
 * SPDX-License-Identifier: {LicenseIdentifier}
 *
 * This project is part of the "{ProductName}" Unreal Engine product line.
 * Use of this software is governed by the {LicenseName}, available at:
 * {LicenseUrl}
 */
```

## File Metadata Block

When `{FileMetadataBlock}` is used, the plugin formats available file metadata as comment lines.

Example metadata:

```text
Relative file path: Plugins/MyPlugin/Source/MyPlugin/Private/MyClass.cpp
File information: Runtime spline generation helper
Description: Builds spline points asynchronously before applying them on the game thread.
```

Rendered block:

```text
 * File: Plugins/MyPlugin/Source/MyPlugin/Private/MyClass.cpp
 * Info: Runtime spline generation helper
 * Description: Builds spline points asynchronously before applying them on the game thread.
```

If information or description is empty, that line is omitted. If no metadata exists, only the file path line is rendered.

## Product Name Resolution

For source files, `{ProductName}` is resolved in this order:

1. Plugin `FriendlyName` from the nearest `.uplugin`, when `PreferPluginFriendlyName` is enabled.
2. Project name.
3. `ProductNameFallback`.

For project-level notices, the project name or fallback product name is used.

## Notice Matching

The scanner compares the existing top-of-file notice with the rendered template. It also checks own and protected markers.

A file can be considered replaceable when:

- It has no notice and `InsertNoticeWhenMissing` is enabled.
- It has a notice that matches an owned marker.
- It has an Unreal placeholder/default notice and `TreatUnrealDefaultNoticesAsReplaceable` is enabled.

A file is protected when:

- It has notice-like text.
- The notice does not match owned markers.
- Foreign notice protection is enabled.
- Or the notice matches a protected marker.

## Template Tips

- Keep the source template short enough to remain readable in every file.
- Put SPDX lines near the top.
- Put legal prose after the SPDX lines.
- Use `{FileMetadataBlock}` for optional per-file details.
- Do not add per-file-only tokens to the project notice unless empty output is acceptable.
- Review a sample file preview before applying to many files.
- Keep third-party license text outside your owned template unless you are deliberately documenting your own license notice.

# Code Documentation

This page documents the source structure and main code contracts of Code Copyright Editor. It complements the inline Doxygen-style comments in the plugin headers.

## Source Layout

```text
Source/CodeCopyrightEditor/
  CodeCopyrightEditor.Build.cs
  Public/
    CodeCopyrightEditor.h
    CodeCopyrightEditorSettings.h
    CodeCopyrightCheckCommandlet.h
  Private/
    CodeCopyrightEditor.cpp
    CodeCopyrightEditorSettings.cpp
    CodeCopyrightNoticeService.h
    CodeCopyrightNoticeService.cpp
    SCodeCopyrightEditorWidget.h
    SCodeCopyrightEditorWidget.cpp
    CodeCopyrightCheckCommandlet.cpp
```

## Main Classes

| Class/Struct | File | Responsibility |
| --- | --- | --- |
| `FCodeCopyrightEditorModule` | `Public/CodeCopyrightEditor.h` | Registers project settings, the editor tab, and the Tools menu entry. |
| `UCodeCopyrightEditorSettings` | `Public/CodeCopyrightEditorSettings.h` | Stores shared editor/commandlet config for identity, license, templates, scope, protection, and behavior. |
| `FCodeCopyrightFileMetadata` | `Public/CodeCopyrightEditorSettings.h` | Stores optional per-file metadata rendered by template tokens. |
| `SCodeCopyrightEditorWidget` | `Private/SCodeCopyrightEditorWidget.h` | Slate UI for template editing, scanning, review, metadata editing, applying, and JSON export. |
| `FCodeCopyrightNoticeService` | `Private/CodeCopyrightNoticeService.h` | Stateless service for template rendering, scanning, notice classification, rewriting, and report generation. |
| `FCodeCopyrightRenderContext` | `Private/CodeCopyrightNoticeService.h` | Token values used during template rendering. |
| `FCodeCopyrightFileResult` | `Private/CodeCopyrightNoticeService.h` | Per-file scan/apply result. |
| `FCodeCopyrightApplyResult` | `Private/CodeCopyrightNoticeService.h` | Aggregate result shared by UI, commandlet, and report writers. |
| `UCodeCopyrightCheckCommandlet` | `Public/CodeCopyrightCheckCommandlet.h` | Headless CI/local automation entry point. |

## Implementation Files

| File | Implementation focus |
| --- | --- |
| `CodeCopyrightEditor.cpp` | Minimal editor-module glue: settings registration, tab creation, and Tools menu integration. |
| `CodeCopyrightEditorSettings.cpp` | Default identity, Fab/EULA license values, scan roots, source extensions, exclusions, marker policy, and behavior flags. |
| `CodeCopyrightNoticeService.cpp` | Technical core: path normalization, token rendering, plugin friendly-name lookup, notice parsing, protection classification, rewrite construction, counting, and report generation. |
| `SCodeCopyrightEditorWidget.cpp` | Tabbed Slate workflow: configure, scan/review, metadata, apply/report, help pages, shared review-row state, live template preview, metadata draft handling, scan/apply actions, and editor JSON export. |
| `CodeCopyrightCheckCommandlet.cpp` | Thin CI adapter: command-line parsing, scan/fix/report orchestration, and exit-code policy. |

## Module Lifecycle

`FCodeCopyrightEditorModule::StartupModule` performs editor registration:

1. Register `UCodeCopyrightEditorSettings` under Project Settings.
2. Register the hidden nomad tab spawner.
3. Register the `Tools > Code Tools > Code Copyright Editor` menu entry.

`ShutdownModule` unregisters these integration points in reverse.

The module is editor-only. Packaged runtime games should not depend on it.

## Implementation Comments

The `.cpp` files include inline comments around the non-obvious implementation decisions:

- Why project-relative paths are preferred for settings and reports.
- How plugin `FriendlyName` is resolved for source files inside plugins.
- Why notice parsing only inspects top-of-file comment blocks.
- How line endings and leading BOM-like markers are preserved during rewrites.
- Why protected notices stop automatic rewriting.
- Why scan mode and apply mode share the same rewrite construction.
- Why commandlet report output is opt-out.
- Why `-NoFail` logs warnings instead of errors.
- How UI draft metadata updates live previews before config save.
- Why apply actions re-run service-side safety checks and rescan after writes.

## Settings Contract

`UCodeCopyrightEditorSettings` is the single source of truth for both UI and commandlet behavior.

Important categories:

- `Identity`: owner, contact, product fallback, copyright start year.
- `License`: license name, URL, and SPDX/custom license identifier.
- `Template`: source-file and project notice templates.
- `File Metadata`: optional per-file information and description entries.
- `Scope`: scan roots, file extensions, path exclusions, exact file exclusions, wildcard exclusions.
- `Protection`: own markers, protected markers, foreign notice protection.
- `Behavior`: plugin friendly-name resolution, missing notice insertion, backups, compact report length.

Because settings are config-backed, changes made in the editor are reused by `CodeCopyrightCheck`.

## Rendering Flow

Template rendering is handled by `FCodeCopyrightNoticeService`.

For project notices:

```text
MakeProjectRenderContext
RenderProjectSettingsNotice
RenderTemplate
```

For source files:

```text
MakeFileRenderContext
RenderSourceNoticeForFile
RenderTemplate
```

The renderer supports both token forms:

```text
{TokenName}
${TokenName}
```

File-specific metadata is resolved from `UCodeCopyrightEditorSettings::FileMetadata` by project-relative path.

## Scan Flow

The UI and commandlet both call:

```text
FCodeCopyrightNoticeService::ScanCodebase
```

The scan flow is:

1. Collect files from configured `ScanRootPaths`.
2. Convert paths to project-relative paths where possible.
3. Skip unsupported file extensions.
4. Skip excluded paths, exact files, and wildcard patterns.
5. Load each eligible file.
6. Extract top-of-file notice text.
7. Render the expected notice for that file.
8. Compare existing and proposed notices.
9. Evaluate own and protected markers.
10. Return `FCodeCopyrightApplyResult`.

Scan mode never writes files.

The parser recognizes leading `//` blocks and `/* ... */` blocks. A block must look notice-related before it becomes part of the replace range. Multiple leading notice-like blocks can be consumed together, which supports projects that have separate SPDX and prose comments at the top of a file.

## Classification

Each file receives an `ECodeCopyrightReviewStatus`:

| Status | Meaning |
| --- | --- |
| `Unknown` | Initial or unclassified state. |
| `MatchesTemplate` | Existing notice already matches the rendered template. |
| `MissingNotice` | No compatible notice was found. |
| `ReplaceOwnNotice` | Existing notice is considered owned and replaceable. |
| `ProtectedForeignNotice` | Existing notice is foreign, third-party, Epic, or explicitly protected. |
| `Conflict` | Own and protected markers both matched. |
| `Excluded` | File was skipped by scope or pattern rules. |
| `ReadError` | File could not be loaded. |
| `WriteError` | File could not be saved during apply. |
| `Updated` | File was written during the last apply pass. |

The stable report strings are produced by:

```text
FCodeCopyrightNoticeService::LexToString
```

## Apply Flow

The UI collects checked review rows and calls:

```text
FCodeCopyrightNoticeService::ApplyToFiles
```

The service re-analyzes each supplied file in write mode. Files are written only when:

- The extension is supported.
- The file is not excluded.
- The notice is missing and insertion is enabled, or the notice is owned/replaceable.
- The file is not protected.
- The file is not in conflict.
- The rendered output differs from the original.

When `CreateBackupBeforeWrite` is enabled, the original file is saved next to the source file with a `.copyright.bak` suffix before writing.

Apply mode reuses the same `BuildRewrittenFileText` path as scan mode. This keeps preview, would-change classification, and actual writes aligned.

## UI State

`SCodeCopyrightEditorWidget` stores transient UI state:

- `MainTabSwitcher`: top-level tab page switcher.
- `ActiveTab`: currently visible workflow tab.
- `ReviewItems`: shared pointers used by the Slate list view.
- `SelectedReviewItem`: current selection.
- `LastScanResult`: latest complete scan/apply result for summaries and export.
- `PreviewText`: cached preview text.
- `StatusText`: cached status/output text.
- `EditingFileInformation`: unsaved metadata edit text.
- `EditingFileDescription`: unsaved metadata edit text.

The widget does not implement file parsing or report generation directly. It delegates those operations to `FCodeCopyrightNoticeService`.

Live edits to templates and selected file metadata are written to the mutable settings object for preview rendering. They are only persisted to config when the user clicks `Save` or `Save File Metadata`.

## Commandlet Flow

`UCodeCopyrightCheckCommandlet::Main` performs:

1. Parse switches.
2. Load `UCodeCopyrightEditorSettings`.
3. Run `ScanCodebase`.
4. If `-Fix` is set, apply all changeable files and scan again.
5. Write selected report formats.
6. Count CI failures.
7. Return `0` for pass or `1` for fail, unless `-NoFail` is set.

CI-relevant failures are counted by:

```text
FCodeCopyrightNoticeService::CountCiFailures
```

## Reports

Reports are generated from `FCodeCopyrightApplyResult`:

| Function | Output |
| --- | --- |
| `FCodeCopyrightApplyResult::ToReportText` | Compact human-readable text for UI/log output. |
| `FCodeCopyrightApplyResult::ToJsonReport` | JSON scan summary and per-file results. |
| `FCodeCopyrightNoticeService::BuildSpdxTagValueReport` | SPDX 2.3 Tag/Value style report. |
| `FCodeCopyrightNoticeService::BuildReuseMarkdownReport` | REUSE/SPDX-oriented Markdown report. |
| `FCodeCopyrightNoticeService::WriteComplianceReports` | Writes all requested report files. |

## Extension Points

When adding a new template token:

1. Add a field to `FCodeCopyrightRenderContext`.
2. Populate it in `MakeProjectRenderContext` and/or `MakeFileRenderContext`.
3. Add replacement logic in `RenderTemplate`.
4. Document it in `TemplateReference.md`.

When adding a new setting:

1. Add a config property to `UCodeCopyrightEditorSettings`.
2. Set a default in `CodeCopyrightEditorSettings.cpp`.
3. Use it in the UI, service, or commandlet.
4. Document it in `SettingsReference.md`.

When adding a new report format:

1. Add an option to `FCodeCopyrightComplianceReportOptions`.
2. Add commandlet parsing for an enable/disable switch if needed.
3. Implement report generation in `FCodeCopyrightNoticeService`.
4. Extend `WriteComplianceReports`.
5. Document it in `ReportsAndCompliance.md` and `CommandletAndCI.md`.

When adding a new review status:

1. Add it to `ECodeCopyrightReviewStatus`.
2. Update `LexToString`.
3. Update UI color/explanation mapping in `SCodeCopyrightEditorWidget.cpp`.
4. Update result counting if needed.
5. Update documentation status tables.

## Build Notes

After source changes, validate with:

```text
RunUAT BuildPlugin -Plugin=<PathTo>/CodeCopyrightEditor.uplugin -Package=<OutputDir> -Rocket -TargetPlatforms=Win64
```

If a full project build fails because an existing plugin DLL is locked, close Unreal Editor and retry. The isolated `BuildPlugin` command is the preferred validation for this plugin.

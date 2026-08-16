# Release Checklist

Use this checklist before packaging Naming Convention Utility for Fab or a project release.

## Documentation

- [ ] `Documentation/README.md` is current.
- [ ] `BUYER_GUIDE.md` describes value, buyers, and limits.
- [ ] `UserManual.md` matches the current Workbench and context menu labels.
- [ ] `SettingsReference.md` lists every user-facing setting and DataAsset field.
- [ ] `TechnicalOverview.md` matches current architecture.
- [ ] `CodeDocumentation.md` matches source layout.
- [ ] `FAQ.md` answers likely buyer questions.
- [ ] `TROUBLESHOOTING.md` includes common rename failures.
- [ ] Legacy `Readme.pdf` is still accurate or clearly superseded.
- [ ] CSV/JSON resources match DataAsset defaults and built-in profile references.

## Source Documentation

- [ ] Public headers have Doxygen-style comments.
- [ ] Rename plan structs explain their role.
- [ ] Texture heuristic comments are clear.
- [ ] DataTable conversion comments explain overwrite behavior.
- [ ] Legacy utility object comments state it delegates to the shared core.

## Functional Checks

- [ ] Plugin enables in a clean UE 5.4 project.
- [ ] Project settings load the default DataAsset.
- [ ] Folder context menu appears.
- [ ] Naming Workbench opens from menu and folder scope.
- [ ] Workbench profile selector switches `epic_recommended`, `tiny_legacy`, and `project_custom`.
- [ ] Copy to Project modifies only the configured Project Custom DataAsset after confirmation.
- [ ] Inline Project Custom rule edits mark the preview stale.
- [ ] DataTable conversion menu appears only for compatible DataTables.
- [ ] Small folder rename preview is correct.
- [ ] Workbench export writes JSON and Markdown report files.
- [ ] Workbench apply only renames selected accepted rows.
- [ ] Stale plan hash blocks Workbench/MCP apply until rescan.
- [ ] Existing target assets are skipped.
- [ ] Duplicate target names are skipped.
- [ ] Invalid generated names are skipped.
- [ ] Actual applied rename count is reported.
- [ ] Redirector fixup runs only after actual renames.

## Data And Config

- [ ] Default DataAsset contains expected rules.
- [ ] `NamingConvention_EpicRecommended.csv` and `NamingConvention_TinyLegacy.csv` are packaged.
- [ ] DataTable asset uses `FNamingConventionTableInformation`.
- [ ] CSV and JSON examples are import-ready.
- [ ] FilterPlugin includes documentation and resources.
- [ ] UCM guide/schema/route metadata includes profiles, compliance, plan hash, selected apply, report paths, and `rules_diff`.
- [ ] No local test assets are packaged accidentally.

## Build And Tests

- [ ] `RunUAT BuildPlugin` succeeds for Win64.
- [ ] Automation tests compile.
- [ ] Automation tests run in an editor test environment.
- [ ] `git diff --check -- Plugins/NamingConventionUtility` is clean.

## Fab Packaging

- [ ] `.uplugin` description is buyer-friendly.
- [ ] VersionName is updated.
- [ ] DocsURL is current.
- [ ] SupportURL is current.
- [ ] MarketplaceURL is current when known.
- [ ] Screenshots/video show preview and confirmation behavior.
- [ ] Documentation describes safe source-control workflow.

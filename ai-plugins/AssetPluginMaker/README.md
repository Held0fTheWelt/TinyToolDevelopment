# Asset Plugin Maker

> Not a verbatim copy of shipped docs. This online page is an overview and routing surface; shipped buyer docs stay in the plugin package.

Asset Plugin Maker (APM) is an Unreal Engine code plugin for controlled asset distillation. It scans a larger source plugin, applies an extraction recipe, builds a focused target asset plugin, and writes the technical evidence needed for review: source snapshots, build manifests, origin ledgers, BOM files, validation reports, update diffs, and release candidate reports.

Version 1.0.0 is in publishment.

## Get It / Routing

- Fab: not listed yet
- Status: In Publishment
- Package docs: shipped inside the plugin package as `Documentation/QUICKSTART.md`,
  `Documentation/UserManual.md`, `Documentation/SettingsReference.md`,
  `Documentation/TROUBLESHOOTING.md`, `Documentation/FAQ.md`, and
  `Documentation/THIRD_PARTY_SOFTWARE.md`.
- Category: AI Plugins

## What It Does

- Scans source plugins without mutating them during normal operation.
- Validates recipes before target plugin generation.
- Builds target content plugins under a caller-provided output root.
- Writes provenance, BOM, validation, update, and release-candidate evidence under `Saved/AssetPluginMaker`.
- Keeps full internal evidence out of buyer plugin roots by default.

## Typical Workflow

1. Open `Tiny Tools -> Asset Tools -> Asset Plugin Maker`.
2. Scan a source plugin and create a source snapshot.
3. Validate a recipe that names the target plugin and selected content.
4. Build the target plugin.
5. Generate the origin ledger, BOM, target validation report, and release candidate report.

The same flow is available through `UAPMEditorSubsystem` and the `APM.*` commandlets described in the shipped quickstart.

## Publication Boundary

APM creates technical readiness evidence. It does not grant redistribution rights, does not provide legal approval, and does not submit anything to Fab. Human review remains required before publication.

## Media

Product slides are maintained by the Product Presentation region. The current slide set is marked dirty internally until Slot 01 and Slot 02 are backed by real Unreal Editor screenshots.

![Asset Plugin Maker title slide](Media/01-asset-plugin-maker-title-1920x1080.png)

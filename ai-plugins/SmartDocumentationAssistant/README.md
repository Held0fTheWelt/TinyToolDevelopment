# Smart Documentation Assistant

> Not a verbatim copy of shipped docs. This online page is an overview and routing surface; shipped buyer docs stay in the plugin package.

Smart Documentation Assistant audits Unreal C++ source documentation, drafts review-gated documentation patches, and writes local reports. It is standalone-first: deterministic analysis runs without external AI, while optional capability providers can enrich source context, evidence, and patch drafting.

## What It Does

- Scans selected source scopes for missing, stale, noisy, or incomplete documentation.
- Writes symbol records, issue reports, hashes, provider status, prompt packs, and patch-plan artifacts.
- Builds documentation-only proposals that require explicit review before apply.
- Applies approved proposals only when target path, range, and original hash still match.
- Discloses absent or degraded optional providers instead of hiding fallback behavior.

## Product Boundary

SDA improves source documentation. It does not refactor runtime behavior, own provider secrets, or grant unreviewed source-edit authority. Optional providers can assist, but SDA keeps finding semantics, reports, and patch safety.

## Status

- Category: AI Plugins
- Status: Advanced Preview
- Fab: Not listed yet
- Current focus: standalone scans, provider disclosure, prompt packs, patch plans, and review-gated documentation-only apply

## Package Docs

Buyer docs ship inside the plugin package as `Documentation/QUICKSTART.md`, `Documentation/UserManual.md`, `Documentation/SettingsReference.md`, `Documentation/TROUBLESHOOTING.md`, `Documentation/FAQ.md`, `Documentation/THIRD_PARTY_SOFTWARE.md`, and `Documentation/CodeDocumentation.md`.

## Support

For questions, setup help, and product support:

https://discord.gg/HycgjVkK4J

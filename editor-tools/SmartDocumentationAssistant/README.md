# Smart Documentation Assistant

> Not a verbatim copy of shipped docs. This online page is an overview and routing surface; shipped buyer docs stay in the plugin package.

Smart Documentation Assistant is in publishment as a standalone-first Unreal C++ source documentation assistant. It audits source documentation, writes local reports, exports prompt and patch-plan evidence, and applies only reviewed documentation-only proposals.

## What It Does

- Scans selected source scopes for missing, stale, noisy, or incomplete documentation.
- Writes symbol records, issue reports, hashes, provider status, prompt packs, and patch-plan artifacts.
- Builds documentation-only proposals that require explicit review before apply.
- Applies approved proposals only when target path, range, and original hash still match.
- Discloses absent or degraded optional providers instead of hiding fallback behavior.

## Product Boundary

SDA improves source documentation. It does not refactor runtime behavior, own provider secrets, or grant unreviewed source-edit authority. Optional providers can assist, but SDA keeps finding semantics, reports, and patch safety.

## Status

- Category: Editor Tools
- Product family: Editor Governance Tools
- Status: In Publishment
- Fab: In publishment; not live until Fab shows the listing as Live
- Current focus: standalone scans, provider disclosure, prompt packs, patch plans, and review-gated documentation-only apply

## Package Docs

Buyer docs ship inside the plugin package as `Documentation/QUICKSTART.md`, `Documentation/UserManual.md`, `Documentation/SettingsReference.md`, `Documentation/TROUBLESHOOTING.md`, `Documentation/FAQ.md`, `Documentation/THIRD_PARTY_SOFTWARE.md`, and `Documentation/CodeDocumentation.md`.

## Support

For questions, setup help, and product support:

https://discord.gg/HycgjVkK4J

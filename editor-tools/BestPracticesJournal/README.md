# Best Practices Journal

> Not a verbatim copy of shipped docs. This online page is an overview and routing surface; shipped buyer docs stay in the plugin package.

Best Practices Journal helps teams capture, review, organize, and reuse engineering practices directly inside the Unreal Editor. It is built for project-local notes about proven practices, trade-offs, evidence, review state, and lessons learned, while staying out of source or asset mutation.

The current public release line is 1.1.2. Its behavior is implemented for Unreal Engine 5.4 and
later; the descriptor mirrored by this documentation belongs to the UE 5.8 build line. Imported
evidence and provider output remain candidates until a human explicitly reviews and promotes them.

## What It Does

- Captures practice records and candidates with evidence, provenance, review state, and rights notes.
- Creates intent-only application briefs for downstream implementation workflows.
- Imports implementation outcomes so practice confidence and evolution history can be reviewed later.
- Supports JSON artifact storage by default, with optional local or studio storage profiles.
- Keeps optional Tiny Tool integrations replaceable instead of turning them into core requirements.

## Product Boundary

BPJ is decision support. It does not plan patches, apply project changes, roll back mutations, or validate implementation results for another tool. Downstream execution belongs to human workflows or approved tools such as UCI or PRS.

## Status

- Category: Editor Tools
- Version: 1.1.2
- Engine baseline: Unreal Engine 5.4+
- Current descriptor/build target: Unreal Engine 5.8
- Status: In Publishment
- Fab: In publishment; not live until Fab shows the listing as Live
- Current focus: practice governance, application briefs, outcome import, storage profiles, and optional route/provider handoffs

## Package Docs

Buyer docs ship inside the plugin package as `Documentation/QUICKSTART.md`, `Documentation/UserManual.md`, `Documentation/SettingsReference.md`, `Documentation/TROUBLESHOOTING.md`, `Documentation/FAQ.md`, `Documentation/THIRD_PARTY_SOFTWARE.md`, and `Documentation/StorageBackends.md`.

## Support

For questions, setup help, and product support:

https://discord.gg/HycgjVkK4J

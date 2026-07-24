# Project Design Assistant PDA

> Not a verbatim copy of shipped docs. This online page is an overview and routing surface; shipped buyer docs stay in the plugin package.

Project Design Assistant PDA is an in-publishment Unreal Engine editor plugin for deterministic
design briefs, file-backed Source/Destination UML workspaces, journal-backed Source assembly,
artifact-derived Destination reflection, explicit deviation review, and preparation-only handoff.

## What It Does

- Creates and opens guarded, user-owned PDA workspaces.
- Authors or assembles Source models from reviewed journal features.
- Loads or reflects an artifact-derived Destination model.
- Compares Source and Destination at element level.
- Records reimplement, adopt-into-source, or third-solution review outcomes.
- Writes a reviewable handoff file and can optionally dispatch it through available mesh routes.

## Product Boundary

PDA writes only its own workspace, reconciliation, export, registry, and handoff artifacts. It does
not mutate target-project code, assets, settings, or levels and does not claim that a handoff was
implemented. Core workflows work without another Tiny Tool plugin. Live mesh reflection and dispatch
are optional and degrade visibly when their route owners are absent.

The development workspace can supply the neutral `category_taxonomy.v1` vocabulary to journal
matching. Installed packages remain standalone through the validated embedded vocabulary fallback;
BestPracticesJournal is not a runtime dependency.

## Status

- Category: AI Plugins
- Status: In Publishment
- Version: 1.0.2
- Fab: Not listed yet
- Current focus: deterministic design workspaces, safe reconciliation, and reviewed handoff

## Package Docs

Buyer docs ship inside the plugin package as `Documentation/QUICKSTART.md`,
`Documentation/UserManual.md`, `Documentation/SettingsReference.md`,
`Documentation/TROUBLESHOOTING.md`, `Documentation/FAQ.md`, and
`Documentation/THIRD_PARTY_SOFTWARE.md`.

## Support

For questions, setup help, and product support:

https://discord.gg/HycgjVkK4J

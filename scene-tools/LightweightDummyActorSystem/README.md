# Lightweight Dummy Actor System

> Not a verbatim copy of shipped docs. This online page is an overview and routing surface; shipped buyer docs stay in the plugin package.

Lightweight Dummy Actor System (LDAS) is an autonomous runtime representation service for dummy-actor workflows. MVP 1+2+3 ships Runtime, Editor, and DeveloperTool modules: subject registration, readiness queries, promotion/demotion policy gates, dummy actor representation, diagnostics, editor inspector, and a validate commandlet.

## Get It / Routing

- Fab: Not listed yet
- Online docs URL (descriptor `DocsURL`): https://docs.tiny-tool-development.com/lightweight-dummy-actor-system/
- Package docs: shipped inside the plugin package as `Documentation/QUICKSTART.md`,
  `Documentation/UserManual.md`, `Documentation/SettingsReference.md`,
  `Documentation/TROUBLESHOOTING.md`, `Documentation/FAQ.md`, and
  `Documentation/THIRD_PARTY_SOFTWARE.md`.
- Category: Scene Tools
- Descriptor version: `1.1.1` (`EngineVersion` 5.4.0)

## Synergies & Bridges

Core Runtime / Editor / DeveloperTool modules work without peer Tiny Tool plugins. The following remain **optional / target-only** and belong on this online surface (Fab Autark §11), never as buyer-package prerequisites:

- WarCollection read-only pilot adapter
- Multiplayer pilot proof
- LightningCore entity bridge
- UCM / PIO / BPJ automation bridges

## Media

Inspector / workflow screenshots are tracked by the Product Presentation region. Use the in-package Quick Start for register + `QueryReadiness` with a `ULDASRepresentationProfile`.

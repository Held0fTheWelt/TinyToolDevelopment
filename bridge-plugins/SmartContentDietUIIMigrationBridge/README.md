# SmartContentDiet UII Migration Bridge

SmartContentDiet UII Migration Bridge is an optional companion plugin for teams that use **Smart Content Diet** and **Unreal Integration Intelligence (UII)** in the same Unreal Engine project.

The bridge registers an SCD migration advisor provider named `uii-migration`. It reads UII migration handoff availability through the UII public service, loads the latest handoff JSON, and translates handoff guardrails and migration-relevant evidence into advisory SCD migration findings.

## UCM-First Note

In the current Tiny Tool Development stack, SCD/UII migration-advice workflows should normally be exposed through **Unreal Capability Mesh (UCM)** setup-declared routes. Use this Freebie Bridge only when a project does not own or enable UCM, or when you need a concrete reference for building a narrow direct adapter.

## Product Boundary

| Product | Responsibility |
| --- | --- |
| Smart Content Diet | Asset health review, migration-advice requests, and user-facing optimization context. |
| SmartContentDiet UII Migration Bridge | Adapter from UII migration handoff artifacts into SCD migration-advisor results. |
| Unreal Integration Intelligence | Evidence export, migration handoff generation, and project integration analysis. |

## Why Use It Without UCM

- Surface UII migration handoff evidence inside SCD review workflows.
- Preserve UII guardrails when SCD displays migration-related findings.
- Keep SCD independent from UII implementation details.
- Use UII evidence without turning SCD into a migration executor.
- Keep findings advisory so migration decisions stay human-reviewed.

## Technical Shape

- Unreal Engine 5.4.
- Version: `1.0.1`.
- Module: `SmartContentDietUIIMigrationBridge` (`Editor`).
- Platforms: Win64, Mac, Linux.
- Content: none.
- Public interfaces: `SmartContentDietInterface`, `UnrealIntegrationIntelligenceInterface`.
- Provider id: `uii-migration`.

## Quick Start

Place all required plugins side by side:

```text
Plugins/
  SmartContentDiet/
  UnrealIntegrationIntelligence/
  SmartContentDietUIIMigrationBridge/
```

Enable all three plugins, build the editor target, and run the UII workflow that writes migration handoff artifacts. SCD migration-advice workflows can then request advisory findings through the `uii-migration` provider.

If UII has no handoff available, the bridge reports that state instead of fabricating migration advice.

## What It Does Not Do

The bridge does not generate migration plans, apply patches, move assets, copy files, mutate project settings, replace UII evidence export, or replace PRS execution. It only translates available UII handoff evidence into SCD advisory migration findings.

## Documentation

- [Documentation overview](Documentation/README.md)
- [Changelog](CHANGELOG.md)

## Status

- Category: Freebie Bridge Plugins
- Status: In preparation
- Fab: Not listed separately

## Support

For questions, setup help, and product support:

https://discord.gg/HycgjVkK4J

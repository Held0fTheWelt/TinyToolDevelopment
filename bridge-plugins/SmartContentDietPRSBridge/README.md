# SmartContentDiet PRS Bridge

SmartContentDiet PRS Bridge is an optional companion plugin for teams that use **Smart Content Diet** and **Project Restructure Service (PRS)** in the same Unreal Engine project.

The bridge connects reviewed SCD placement moves to PRS plan, validation, dry-run, apply, and rollback contracts. SCD owns the review decision and user-facing asset-health context. PRS owns guarded execution.

## UCM-First Note

In the current Tiny Tool Development stack, PRS placement workflows should normally be exposed as PRS-owned **Unreal Capability Mesh (UCM)** routes. Use this Freebie Bridge only when a project does not own or enable UCM, or when you need a concrete reference for building a narrow direct adapter.

## Product Boundary

| Product | Responsibility |
| --- | --- |
| Smart Content Diet | Asset health findings, optimization review, severity context, and user-confirmed placement proposals. |
| SmartContentDiet PRS Bridge | Adapter from SCD placement proposals into PRS placement plans and rollback calls. |
| Project Restructure Service | Plan validation, dry-run diff generation, explicit apply gates, and rollback execution. |

## Why Use It Without UCM

- Convert SCD placement moves into PRS placement plans.
- Preview PRS validation results and dry-run diffs before any mutation.
- Apply only after SCD has shown the preview and the user confirms.
- Roll back a PRS run by run id.
- Let PRS consult read-only SCD health severity when evaluating placement context.

## Technical Shape

- Unreal Engine 5.4.
- Version: `1.0.1`.
- Module: `SmartContentDietPRSBridge` (`Runtime`).
- Platforms: Win64, Mac, Linux.
- Content: none.
- Public interfaces: `SmartContentDietInterface`, `ProjectRestructureServiceInterface`.
- Main adapter: `FSCDToPRSPlacementAdapter`.
- Read-only health helper: `FSCDHealthForPRS`.

## Quick Start

Place all required plugins side by side:

```text
Plugins/
  SmartContentDiet/
  ProjectRestructureService/
  SmartContentDietPRSBridge/
```

Enable all three plugins, build the project, and route reviewed SCD placement moves through the bridge:

```text
BuildPlan -> Preview -> Apply
```

Use `Rollback` with a PRS run id when a previously applied run needs to be reverted.

## Guardrails

The bridge never auto-applies a restructure plan. It forwards reviewed SCD proposals to PRS, and PRS must still validate the plan, build the dry-run diff, enforce its apply options, and own rollback.

## What It Does Not Do

The bridge does not decide what should be moved, bypass PRS validation, apply changes without confirmation, index project evidence, or generate AI plans. It only adapts SCD-reviewed placement moves to PRS execution contracts.

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

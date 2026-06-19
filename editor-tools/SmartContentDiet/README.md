# Smart Content Diet

> Not a verbatim copy of shipped docs. This page is an online overview and routing surface; install and day-to-day buyer docs stay in the shipped plugin package.

Smart Content Diet is an Unreal Editor workflow tool for reviewing asset optimization candidates, explaining findings, and supporting guarded QuickFix/reduction workflows.

The product is not listed on Fab yet. This page exists to document the current direction and to make the relationship to the wider TinyToolDevelopment tool stack visible before publication.

## What It Does

- Scans Unreal Engine project assets for optimization and hygiene candidates.
- Explains findings with severity, impact, and review context.
- Supports governance views for debt, trends, budgets, ownership, and review state.
- Provides reviewed QuickFix and reduction workflows for selected asset categories.
- Can produce reports for local review and CI-style validation.

Open the editor panel from **Tools → Content Tools → Smart Content Diet**.

## Safety Boundary

Smart Content Diet can become workspace-mutating when QuickFixes, reductions, review moves/deletes, baseline updates, or governance writes are applied.

Use mutating workflows only in backed-up, source-controlled, disposable branches or workspaces. Never run destructive or cross-asset actions on unprotected source. Review generated changes before keeping them.

## Relationship To AI Tools

Smart Content Diet is an editor tool, not an autonomous agent. In the broader TinyToolDevelopment stack, IIS can provide project memory and retrieval, UII can prepare evidence and migration context, and PRS can execute gated restructure plans. Smart Content Diet focuses on asset health and optimization review.

## UCM Integration And Optional No-UCM Bridges

The main project routes Smart Content Diet ecosystem workflows through **Unreal Capability Mesh (UCM)**. The active UCM setup includes `scd.migration_advice_from_handoff.v1` for handoff-to-advice translation, and PRS placement workflows are exposed as PRS-owned UCM routes.

The Freebie Bridges below are not the default integration path. They remain available for teams without UCM and as reference implementations for direct provider registration:

| Bridge | Connects | Purpose |
| --- | --- | --- |
| [SmartContentDiet IIS Similarity Bridge](../../bridge-plugins/SmartContentDietIISSimilarityBridge/README.md) | Smart Content Diet + Internal Index Service | No-UCM/reference adapter for IIS-backed semantic similarity and prepared health-evidence import. |
| [SmartContentDiet PRS Bridge](../../bridge-plugins/SmartContentDietPRSBridge/README.md) | Smart Content Diet + Project Restructure Service | No-UCM/reference adapter for reviewed SCD placement moves into PRS validation, dry-run, apply, and rollback workflows. |
| [SmartContentDiet UII Migration Bridge](../../bridge-plugins/SmartContentDietUIIMigrationBridge/README.md) | Smart Content Diet + Unreal Integration Intelligence | No-UCM/reference adapter for surfacing UII migration handoff evidence as advisory SCD migration findings. |

## Status

- Category: Editor Tools
- Status: Advanced Preview
- Fab: Not listed yet
- Documentation: Online overview and routing page available; package buyer docs ship with the plugin

## Support

For questions, setup help, and product support:

https://discord.gg/HycgjVkK4J

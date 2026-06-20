# Project Restructure Service

> Not a verbatim copy of shipped docs. This online page is an overview and routing surface; shipped buyer docs stay in the plugin package.

Project Restructure Service (PRS) is a safe, gated project restructuring and placement executor for Unreal Engine workflows.

PRS is designed to consume evidence and plans from surrounding tools while keeping mutation explicit, reviewed, and reversible. IIS can provide retrieval and project evidence, but IIS itself remains read-only; PRS is the separate executor layer for controlled restructuring.

## What It Does

- Loads and validates restructure plans.
- Runs dry-run validation before applying changes.
- Uses confirmation gates and hashes so the applied diff matches the reviewed diff.
- Requires clean preflight conditions for mutation workflows.
- Supports rollback for the last applied run.
- Keeps restructure execution separate from retrieval and decision systems.

## Product Boundary

PRS is not an AI planner by itself. Planning, retrieval, and evidence analysis live in companion tools such as IIS and UII. PRS focuses on the guarded execution side: moving from a reviewed plan to a controlled project change.

## UCM Integration And Optional No-UCM Bridge

Project Restructure Service participates in the Tiny Tool Development stack through UCM-first route declarations. Normal PRS ecosystem workflows should be exposed as PRS-owned UCM routes so Capability Mesh keeps route policy, dry-run requirements, approval rules, and MCP-visible tool metadata in one setup layer.

The Freebie Bridge below is retained for teams that do not use UCM and as a reference for a narrow direct adapter.

| Bridge | Connects | Purpose |
| --- | --- | --- |
| [SmartContentDiet PRS Bridge](../../bridge-plugins/SmartContentDietPRSBridge/README.md) | Smart Content Diet + Project Restructure Service | No-UCM/reference adapter that turns reviewed SCD placement moves into PRS validation, dry-run, apply, and rollback workflows. |

## Status

- Category: AI Plugins
- Status: Advanced Preview
- Fab: Not listed yet
- Current focus: plan loading, dry-run, apply gate, rollback, and executor safety

## Support

For questions, setup help, and product support:

https://discord.gg/HycgjVkK4J

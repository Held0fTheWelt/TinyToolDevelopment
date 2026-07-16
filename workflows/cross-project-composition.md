# Cross-Project Composition Workflow

This workflow combines existing Tiny Tool capabilities without turning the composition into another
plugin product. Each participant keeps its domain authority, and one reviewed manifest records the
intended result.

## Workflow

1. Evidence tools inspect the source and target projects.
2. Asset Plugin Maker inventories plugins and content packs recursively, ranks dependencies, and
   identifies mirrored code plugins.
3. Project Intelligence Orchestrator compiles the two inventories into a deterministic composition
   draft.
4. A human reviews wiring, target content, transfer decisions, budgets, and verification checks.
5. Only an approved manifest can start the dry-run-first execution path.
6. APM exports or adopts plugins in dependency order.
7. Unreal Blueprint Integrator materializes reviewed Blueprint or DataAsset instructions through
   preview and apply.
8. PIO verifies the target and records findings, budget evidence, optional content-diet evidence, and
   optional variant comparisons.

## Ownership

| Layer | Owner |
| --- | --- |
| Transport and access | Unified MCP Server |
| Tool discovery and invocation lifecycle | Tiny Tool Execution |
| Route planning, dry-run, approval, and execution governance | Unreal Capability Mesh |
| Project inventory, export, adoption, and dependency checks | Asset Plugin Maker |
| Manifest compile, execute orchestration, and verification | Project Intelligence Orchestrator |
| Blueprint and DataAsset mutation | Unreal Blueprint Integrator |
| Optional optimization findings | Smart Content Diet |

## Current Proof Boundary

The read and planning path has been demonstrated through project evidence collection, recursive
inventory, mirror detection, and repeatable draft compilation. The draft remains unapproved until a
human supplies construction-ready target choices. Mutation, target materialization, runtime
verification, and optional variant comparison therefore remain pending and are not presented as a
completed composition.

## Engine Compatibility

The shared capabilities are implemented from Unreal Engine 5.4. A later engine version may be used as
the host for a particular target project's acceptance run, but that does not raise the functional
baseline of the composition tools.

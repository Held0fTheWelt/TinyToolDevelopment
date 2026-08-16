<!-- doc-provenance: AKDB:plugins/ProceduralGeneratedStructures/architecture.md; docs/architecture/plugins/ProceduralGeneratedStructures/product-facts.yml; reconciled 2026-06-21 -->
# ProceduralGeneratedStructures

ProceduralGeneratedStructures builds reusable instanced static mesh structures from a data asset. The runtime actor can read existing `UInstancedStaticMeshComponent` instances into a `UProceduralStructureDataAsset`, then rebuild those explicit instances or generate additional row-based structures. It also exposes build-plan and statistics data so you can inspect target components, blocking issues, mutation intent, async progress, and exact post-prune instance counts before applying a rebuild.

## Documentation

- [QUICKSTART.md](QUICKSTART.md): install → place actor → capture and rebuild, with expected results.
- [UserManual.md](UserManual.md): full workflow, core objects, and build notes.
- [SettingsReference.md](SettingsReference.md): every actor property and data-asset field.
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md) · [FAQ.md](FAQ.md)
- [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md): third-party declaration (none bundled).

## Core Assets

- `AAsyncProceduralGeneratedActor` owns the build workflow and can rebuild components synchronously or across editor/game ticks.
- `UProceduralStructureDataAsset` stores named mesh entries with explicit transforms and optional row-generation rules.
- `FInstancedComponentConfiguration` maps a named instanced mesh component on the actor to a stored data asset entry.
- `FProceduralStructureBuildPlan` and `FProceduralStructureElementStats` expose exact preview data for tools, Blueprints, and UCM routes.

## Build Notes

- Explicit transforms read from scene components are replayed exactly and are not recentered during rebuild.
- Generated row transforms can be centered around the local XY origin with `bCenterGeneratedTransforms`.
- `InstancesPerFrame` limits how many instances are added per tick when async build is enabled.
- Row counts are clamped to non-negative values before generation.
- Build plans report generated row capacity before pruning and the exact generated count after pruning.

## Recommended Workflow

1. Add an `AAsyncProceduralGeneratedActor` to a level or blueprint.
2. Add one or more `UInstancedStaticMeshComponent` children with stable component names.
3. Assign a `UProceduralStructureDataAsset`.
4. Configure `ReadInComponentConfiguration` to capture existing component instances.
5. Configure `ComponentConfiguration` to rebuild those entries.
6. Inspect `GetBuildPlan` or the preview route, then use the editor-callable read, clear, and build actions to iterate on the structure.

<!-- doc-provenance: AKDB:plugins/ProceduralGeneratedStructures/architecture.md; docs/architecture/plugins/ProceduralGeneratedStructures/product-facts.yml; reconciled 2026-06-21 -->
# User Manual

This manual explains how to use Procedural Generated Structures in the Unreal Editor.

## Purpose

Procedural Generated Structures builds reusable instanced static mesh structures from a data asset.
The runtime actor can read existing `UInstancedStaticMeshComponent` instances into a
`UProceduralStructureDataAsset`, then rebuild those explicit instances or generate additional
row-based structures.

## Core Objects

- **`AAsyncProceduralGeneratedActor`** — owns the build workflow and can rebuild components
  synchronously or across editor/game ticks.
- **`UProceduralStructureDataAsset`** — stores named mesh entries (`FInstancedMeshInformation`) with
  explicit transforms and optional row-generation rules.
- **`FInstancedComponentConfiguration`** — maps a named instanced mesh component on the actor to a
  stored data asset entry (`Name` + `StructureType`).
- **`FProceduralStructureBuildPlan`** — reports what a rebuild would do: target components,
  blocking issues, mutation intent, async counts, and exact post-prune instance totals.
- **`FProceduralStructureElementStats`** — reports per-entry explicit, generated, potential
  generated, and total instance counts.
- **`EStructureType`** — `None`, `Structure`, `Railing`, `Tribune`, `Stairs`.

## Workflow

1. Add an `AAsyncProceduralGeneratedActor` to a level or blueprint.
2. Add one or more `UInstancedStaticMeshComponent` children with **stable component names**.
3. Assign a `UProceduralStructureDataAsset` to **ProceduralStructure**.
4. Configure **ReadInComponentConfiguration** to capture existing component instances into the asset
   (trigger with **bReadInMeshComponentData**).
5. Configure **ComponentConfiguration** to rebuild those entries back onto the components.
6. Inspect **GetBuildPlan** (Blueprint/C++) or the preview route if you use automation. Fix any
   reported issues before applying a rebuild.
7. Use **bClearProceduralStructureInformation** (clear), **bReadInMeshComponentData** (read), and the
   build (construction / async) to iterate on the structure.

## Build Notes

- Explicit transforms read from scene components are **replayed exactly** and are not recentered
  during rebuild.
- Generated row transforms can be centered around the local XY origin with
  **bCenterGeneratedTransforms**.
- **InstancesPerFrame** limits how many instances are added per tick when async build is enabled.
- Row counts are clamped to non-negative values before generation.
- Build plans and DataAsset stats report both unpruned row capacity and the exact generated count
  after pruning, so large rebuilds can be estimated before mutation.
- **bAutoBuildOnConstruction** triggers a build during `OnConstruction` (similar to the spline actor).
- **bUseAsyncBuild** spreads the build across frames; otherwise the build happens in one pass.
- **GetBuildProgress**, **GetEstimatedBuildInstanceCount**, and **GetAddedBuildInstanceCount** report
  async build progress for editor tools and Blueprints.

## Build Plan And Validation

`AAsyncProceduralGeneratedActor::GetBuildPlan` is a non-mutating preview. Use it before rebuilding
large or shared structures.

The build plan reports:

- Whether a data asset, component configuration, and actor-owned instanced mesh components exist.
- One entry per configured component, including component path, mesh path, DataAsset element stats,
  mutation intent, and blocking issue codes.
- Totals for explicit instances, potential generated instances before pruning, generated instances
  after pruning, and combined instance count.

Common blocking issue codes include:

- `missing_procedural_structure_data_asset`
- `missing_component_configuration`
- `actor_has_no_instanced_static_mesh_components`
- `component_not_found:<Name>`
- `data_asset_element_not_found:<Name>`
- `data_asset_element_missing_mesh:<Name>`
- `data_asset_element_type_none:<Name>`

## Data Asset Entries

Each `FInstancedMeshInformation` entry holds:

- `Name`, `Type` (`EStructureType`), `Mesh` (`UStaticMesh`).
- `Instances` — explicit transforms (e.g. captured from the scene), replayed as-is.
- `InstancedMeshRows` — optional procedural row rules (row counts per dimension, per-dimension
  movement transforms, pruning/defined-placement options). See
  [SettingsReference.md](SettingsReference.md) for every field.

## What The Plugin Does Not Do

- It does not author static meshes for you — you supply your own.
- It does not recenter explicitly captured instances.
- It is not a full procedural-modeling system; it places and regenerates instanced meshes from data.

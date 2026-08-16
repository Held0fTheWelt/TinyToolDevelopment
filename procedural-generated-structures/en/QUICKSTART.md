<!-- doc-provenance: AKDB:plugins/ProceduralGeneratedStructures/architecture.md; docs/architecture/plugins/ProceduralGeneratedStructures/product-facts.yml; reconciled 2026-06-21 -->
# Quick Start

This guide takes you from install to a **visible result**: an `AAsyncProceduralGeneratedActor` that
rebuilds instanced-mesh structures from a data asset. The plugin works on its own — no other plugin
is required.

## What You'll Have After This Guide

An actor in your level whose instanced static mesh instances are captured into a data asset and
rebuilt from it, so the structure is reusable and regenerable.

## Requirements

- Unreal Engine 5 editor and an open level.
- A `UStaticMesh` from your project to instance (e.g. a wall or pillar mesh).
- No third-party software, account, or runtime. See [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md).

## 1. Install And Enable

1. Add **ProceduralGeneratedStructures** from your Fab library to the project (or install to the engine).
2. Open **Edit → Plugins**, enable **ProceduralGeneratedStructures**, and restart when asked.

## 2. Place The Actor (First Result)

1. In the **Place Actors** panel, search for **Async Procedural Generated Actor** and drag it into
   the level (or add `AAsyncProceduralGeneratedActor` from the class list).
2. Add one or more **Instanced Static Mesh Component** children to the actor and give each a **stable
   component name** (e.g. `Walls`). Assign your static mesh and place a few instances.

## 3. A Real Worked Example: Capture And Rebuild

1. Create a **Procedural Structure Data Asset** (`UProceduralStructureDataAsset`) in the Content
   Browser and assign it to the actor's **ProceduralStructure** property.
2. In **ReadInComponentConfiguration**, add an entry whose **Name** matches your component (`Walls`)
   and pick a **StructureType** (e.g. `Structure`).
3. Set **bReadInMeshComponentData** to capture the component's current instances into the data asset.
4. In **ComponentConfiguration**, add an entry mapping the same **Name** (`Walls`) back to the data
   asset entry.
5. Preview with **GetBuildPlan** from Blueprint/C++ or the automation preview route. A clean plan
   has no blocking issues and reports the exact instance total that will be rebuilt.
6. Rebuild — enable **bAutoBuildOnConstruction** (rebuilds on construction) or move/edit the actor to
   trigger a build.

**Expected output:** the instanced meshes are rebuilt from the data asset. Explicit captured
transforms are replayed exactly (never recentered). To iterate, set
**bClearProceduralStructureInformation** to clear the stored data and capture again.

## 4. Performance / Async

- **bUseAsyncBuild**: spread the build across frames instead of one blocking pass.
- **InstancesPerFrame**: how many instances are added per tick when async build is enabled.
- **GetBuildProgress** / **GetAddedBuildInstanceCount**: track async build progress for tools.
- **bCenterGeneratedTransforms**: center *generated row* transforms around the local XY origin
  (explicit captured instances are never recentered).

## 5. Generate Row-Based Structures (Optional)

Beyond replaying captured instances, a data asset entry can define **InstancedMeshRows** to generate
grids/rows procedurally (row counts per dimension with per-dimension movement transforms). See
[SettingsReference.md](SettingsReference.md) for every field.

## 6. Next Steps

- Full workflow and build notes: [UserManual.md](UserManual.md).
- Every actor property and data-asset field: [SettingsReference.md](SettingsReference.md).
- Problems: [TROUBLESHOOTING.md](TROUBLESHOOTING.md) and [FAQ.md](FAQ.md).

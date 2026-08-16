<!-- doc-provenance: product-facts.yml reconciled 2026-07-15; source AKDB:plugins/AsyncSplineBuilder/architecture.md -->
# Quick Start

This guide takes you from install to a **visible result**: a road/track mesh generated along a
spline you control. Async Spline Builder works on its own — no other plugin is required.

## What You'll Have After This Guide

A `Spline Generating Actor` in your level with a road built from spline mesh sections that you can
reshape by moving spline points and rebuild on demand.

## Requirements

- Unreal Engine 5 editor and an open level.
- At least one **road mesh** that tiles along its local X axis (see step 3 / Mesh Authoring in the
  User Manual). You can use any tiling mesh from your project to start.
- No third-party software, account, or runtime. See [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md).

## 1. Install And Enable

1. Add **AsyncSplineBuilder** from your Fab library to the project (or install to the engine).
2. Open **Edit → Plugins**, enable **AsyncSplineBuilder**, and restart when asked.

## 2. Open The Panel (First Result)

1. Open or create a level.
2. Open **Tools → Track Tools → Async Spline Builder**. The panel has **Build**, **Segments**, and
   **Terrain** tabs.

## 3. A Real Worked Example: Build A Track

1. On the **Build** tab, click **Create Actor** (this spawns an `ASplineGeneratingActor`), or select
   an existing one and click **Use Selection**.
2. In **Setup**, assign a tiling mesh to **MainMesh** (required). Optionally assign **StartMesh** and
   **EndMesh**.
3. In the viewport, move the actor's spline points to shape the path.
4. Click **Validate** (this checks that `MainMesh` is set and the spline is buildable).
5. Click **Build Now**.

**Expected output:** the actor generates `USplineMeshComponent` road sections along the spline. Move
a spline point and click **Rebuild** to see the road update.

> For long tracks, enable **Use Async Build** and set **SegmentsPerTick** so generation is batched
> across ticks and the editor stays responsive. Use **Cancel** to stop an in-progress async build.

## 4. Go Further (Optional)

- **Segments** tab: per-segment meshes, jump gaps (`JumpGapsByPoints`), and stunt drops.
- **Terrain** tab: snap to landscape, height deformation, and procedural **ground walls**
  (`bGenerateGroundWalls`). See [LandscapeAndWalls.md](LandscapeAndWalls.md).
- **Data asset:** save/load layouts with `WriteSplineToDataAsset` / `ReadSplineFromDataAsset`.

## 5. Next Steps

- Full workflow, per-segment data, gaps, drops, walls, landscape deformation: [UserManual.md](UserManual.md).
- Settings: [SettingsReference.md](SettingsReference.md).
- Problems: [Troubleshooting.md](Troubleshooting.md) and [FAQ.md](FAQ.md).

<!-- doc-provenance: product-facts.yml reconciled 2026-07-15; source AKDB:plugins/AsyncSplineBuilder/architecture.md -->
# Async Spline Builder Documentation

Async Spline Builder generates road, race-track, pipe, rail, wall, and side-object spline meshes without forcing large editor stalls. It supports synchronous builds, editor async batching, runtime async batching, per-segment mesh plans, optional ground walls, stunt gaps, drop walls, spline point data assets, and editor-only landscape height deformation plus additive layer paint.

This folder contains the documentation delivered with the plugin.

## Start Here

- [BUYER_GUIDE.md](BUYER_GUIDE.md): product-level overview, workflows, strengths, and limitations.
- [UserManual.md](UserManual.md): complete editor workflow from first actor placement to rebuilds.
- [FAQ.md](FAQ.md): Fab-ready questions and answers.

## Reference

- [SettingsReference.md](SettingsReference.md): every important actor setting and recommended baseline.
- [LandscapeAndWalls.md](LandscapeAndWalls.md): snapping, height deformation, ground walls, gaps, and drop walls.
- [TechnicalOverview.md](TechnicalOverview.md): maintainer-level architecture and build flow.
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md): common setup, build, trace, and geometry issues.

Maintainer-only audits, completion notes, automation commands, legacy notes, and release checklists can exist in the source repository, but they are excluded from the buyer package.

## Quick Workflow

1. Enable the plugin and restart the editor if required.
2. Open **Tools > Track Tools > Async Spline Builder**.
3. Place or select an `ASplineGeneratingActor` from the workflow panel.
4. Assign `MainMesh` in the panel setup section.
5. Edit the `TrackSpline` points in the viewport.
6. Use **Build Now** for an immediate build or **Rebuild** for async batching.
7. Use the segment helpers to create per-segment rows before advanced per-segment edits.
8. Optional: enable ground walls and configure trace object types in the Details panel.
9. Optional: assign a landscape, run **Deform Height**, then **Paint Layer** (requires `PaintLayer` on the actor) for additive weight painting.

## Main Features

- Road or track mesh generation along a spline.
- Track Shape Editor for native route/layout point authoring, with designer controls for layouts, anchors, and segments.
- Validate Layout Connectors to review passive `PitEntry`, `PitExit`, `Link`, `ServiceAccess`, or custom connector metadata before trusting route relationships.
- Apply Layout Connector for adding or updating passive layout relationship records without creating hidden mesh branches.
- Async editor rebuilds with `SegmentsPerTick`.
- Runtime async rebuilds using a next-tick timer pump.
- Per-segment mesh selection and mesh length planning.
- Start, middle, and end extra meshes for rails, barriers, fences, pipes, or detail meshes.
- Stunt gaps that suppress road and side meshes.
- Drop regions and procedural drop walls between height steps.
- Procedural ground walls that trace down to terrain or other configured object types.
- Tag-based generated component cleanup that survives stale arrays and construction rebuilds.
- Spline point save/load through `USplinePointListAsset`.
- Editor-only landscape height deformation plus additive global layer paint.
- Automation tests for the highest-risk behaviors.

## Supported Runtime Position

The runtime module contains the actor, spline mesh generation, ground wall generation, drop wall generation, data asset access, and runtime async pump.

The editor module contains the workflow panel, editor-only landscape deformation and layer paint, and editor selection helpers. Packaged games can build the spline meshes and procedural walls, but landscape height/weight edits and the workflow panel are editor-only.

## Editor Workflow Panel

The primary editor surface is **Tools > Track Tools > Async Spline Builder**. It groups the common workflow into **Build**, **Segments**, and **Terrain** tabs so day-to-day tasks stay compact without hiding validation status.

Use the Track Shape Editor when a route needs native point/layout authoring, and use layout connector controls when pit lanes, service access, or alternate routes need explicit relationship metadata.

Use the panel for day-to-day work. Use the Unreal Details panel for advanced raw fields such as per-segment extra mesh arrays, detailed wall UV settings, trace object arrays, custom collision settings, and experimental fields.

## Important Limitations

- Landscape: height deformation plus **additive global** layer weight paint when `PaintLayer` is set (`PaintLandscapeLayerNow` or panel **Paint Layer**). Replace/clear paint mode is not implemented.
- Landscape deformation is a one-shot editor operation, not an automatic part of every track rebuild.
- Complex production landscapes still need manual QA, especially tight curves, very steep terrain, and mixed per-segment wall settings.
- Runtime async automation is covered through a deterministic test hook; a full PIE timer-world integration pass is still recommended for release maps.

## Validation

For a local package validation pass, build the editor target for your project and run the AsyncSplineBuilder automation group from Unreal's Automation tools. Keep maintainer-specific command paths in local release notes rather than in the shipped buyer package.

## Recommended First Production Pass

Use a short open test spline first, then a closed loop, then the real track. Keep `bUseAsyncBuild` enabled, start with `SegmentsPerTick = 2`, and only raise it after confirming editor responsiveness. Configure trace object types before enabling snapping or ground walls, because validation intentionally blocks builds that would otherwise destroy old geometry and produce no valid replacement.

## Legal Note

Async Spline Builder is provided under the license terms included with the product distribution. The plugin does not grant rights to third-party meshes, materials, landscapes, or content used with generated tracks.

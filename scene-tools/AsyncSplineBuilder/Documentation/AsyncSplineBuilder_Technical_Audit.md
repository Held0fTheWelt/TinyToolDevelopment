# Async Spline Builder - Algorithmic Integration Audit

Date: 2026-05-31
Scope: `Plugins/AsyncSplineBuilder`

This report checks whether the current systems actually work together: spline mesh generation, async batching, runtime/editor split, landscape deformation, ground walls, gaps/drops, generated-component cleanup, data assets, and tests.

## Wave 2 Remediation Status (2026-05-31)

| ID | Finding | Status | Notes |
|----|---------|--------|-------|
| P0 | Runtime async timer stall (`0.0f` interval) | **Fixed** | Uses `SetTimerForNextTick()` with re-arm in `RuntimeBuildPump`. |
| P0 | Ground wall forward vertex references | **Fixed** | Quads emitted only between previous/current sample pairs in the same strip. |
| P1 | `FTrackBuildPlan` not consumed by builders | **Fixed** | Road/extra builders and width helpers read segment plan fields. |
| P1 | Extra meshes tagged as road meshes | **Fixed** | Role tags applied at call sites; registry filters by tag. |
| P1 | Per-segment ground wall settings partial | **Fixed** | `TraceLength`, `TrackHalfWidth`, per-sample `bGenerateBothSides` wired. |
| P1 | Landscape nearest-sample + paint layer | **Partial** | Height deform + **additive global** `PaintLayer` weight paint (editor). Deferred: replace/clear, per-segment paint, weightmap automation. |
| P2 | Validation does not gate builds | **Fixed** | `FBuildValidationResult` errors abort before clear/build. |
| P2 | Debug text registry/cleanup gaps | **Fixed** | Tag scan on rebuild/clear; edit path uses full component cleanup. |
| P2 | Automation tests too loose | **Fixed** | 14 tests with exact counts and targeted risky-path coverage. |

### Verification (Wave 2)

- `PluginProjectEditor Win64 Development` — builds successfully.
- `PluginProject Win64 Development` — builds successfully.
- `Automation RunTests AsyncSplineBuilder` — 14 tests (exact counts, async runtime pump, gap walls, validation gating, tag separation, landscape footprint helpers).

## Executive Summary

After Wave 1–2 and Phase 3 landscape layer paint (2026-06-01), the plugin supports editor height deformation and **additive global** weight painting for a configured `PaintLayer`. Remaining landscape gaps: replace/clear paint mode, per-segment layers, and automated weightmap tests. Complex per-segment wall styling on long mixed tracks should still be validated manually on target content.

## What Works Now

- Runtime and editor modules are split cleanly.
- Synchronous `BuildTrack()` and async editor tick / runtime timer pumps.
- `FTrackBuildPlan` drives road mesh piece counts, extra meshes, and deformation width.
- Distinct component tags for road, extra, ground wall, and debug text.
- Ground wall strips split correctly at gaps and invalid samples.
- Validation blocks fatal misconfiguration before destroying generated geometry.
- Landscape height deformation with closest-point spline projection (editor module).
- Additive global landscape layer weight paint via `PaintLandscapeLayerNow` / panel **Paint Layer** (editor module).
- 14 automation tests covering core, high-risk, and landscape footprint helpers.

## What Should Not Be Claimed Yet

- Replace/clear landscape paint mode or per-segment paint layers.
- Automated verification of weightmap writes (manual QA on a real landscape required).
- Production-grade landscape shoulder quality on very tight curves without manual tuning.
- Full PIE timer-pump verification in headless automation (runtime async path is tested via direct pump hook).

## Historical Findings (pre–Wave 2)

The items below were verified in the second-pass audit and addressed in Wave 2 unless noted as partial/deferred.

### P0 - Runtime async rebuild can stall

Evidence (pre-fix):

- Runtime timer was set with a `0.0f` repeating interval.

Resolution: `SetTimerForNextTick()` reschedule loop in `RuntimeBuildPump`.

### P0 - Ground wall strip splitting can emit invalid triangles

Evidence (pre-fix):

- Triangles referenced `BaseIndex + 2/+3` before the next sample existed; gaps flushed strips with dangling indices.

Resolution: Previous/current vertex pair model; quads only when both samples are valid in the same strip.

### P1 - Build plan is not the single source of truth

Evidence (pre-fix):

- Builders recomputed piece count from live `FTrackSplineData`, ignoring `SegmentLength` in the plan.

Resolution: `BuildSplineMeshComponents`, `BuildExtraSplineMeshComponent`, and `GetHalfRoadWidthAtDistance` consume `BuildPlan.Segments[]`.

### P1 - Extra mesh components are also tagged as road meshes

Evidence (pre-fix):

- `CreateSplineMeshComponent()` unconditionally applied `RoadMeshTag`.

Resolution: Tags applied at road vs extra call sites only.

### P1 - Per-segment ground wall settings are only partially honored

Evidence (pre-fix):

- `bGenerateBothSides` from segment 0 only; `TrackHalfWidth` and `TraceLength` unused.

Resolution: Per-sample side flags, segment mesh width, and trace length honored.

### P1 - Landscape deformation: layer painting and fitting quality

Evidence (pre-fix):

- Nearest-sample fitting; `PaintLayer` unused; width from `MainMesh` only.

Resolution: Closest-point polyline projection; per-segment width from build plan. **Implemented (2026-06-01):** additive global `PaintLayer` weight paint. **Completion hardening implemented (2026-06-01):** true zero-falloff hard edge, user-facing `bNoWeightBlend` caveat, and panel paint controls. **Release QA pending:** recorded real-landscape weightmap QA. **Still deferred:** replace/clear mode, per-segment paint layers.

### P2 - Validation reports issues but does not gate bad builds

Resolution: Errors abort `RequestBuild()` before `ClearGeneratedComponents()`.

### P2 - Debug text cleanup weaker than mesh cleanup

Resolution: Registry rebuild and tag-based destroy; edit-mode uses `ClearGeneratedComponents()`.

### P2 - Automation tests pass but miss risky paths

Resolution: Extended suite with exact counts and targeted tests (see Wave 2 verification).

## Recommended Follow-up (post–Wave 2)

1. Finish `CompletionPlan.md`: recorded real-landscape QA.
2. Optional replace/clear paint mode; per-segment paint layers if product needs them.
3. Optional PIE integration test with a fully registered game world for timer pump (no test hook).
4. Manual QA on mixed per-segment wall configs on production splines.

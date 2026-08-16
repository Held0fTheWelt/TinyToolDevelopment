<!-- doc-provenance: product-facts.yml reconciled 2026-07-15; source AKDB:plugins/AsyncSplineBuilder/architecture.md -->

# Manual Landscape QA - Async Spline Builder Layer Painting

**Last audited:** 2026-07-15

**Status:** Code, automation, and build proof are complete; real-landscape QA is pending before a
release-complete claim.

Automation covers the paint math, but it cannot prove Unreal's real weightmap write path, edit-layer
routing, or transaction behavior. Run this gate in a disposable map with at least two material paint
layers. Back up the map or use source control.

## Setup

1. Enable **Async Spline Builder** in the host project.
2. Place a landscape with two weight-blended paint layers, for example grass and dirt.
3. Add a second test area with a layer marked `bNoWeightBlend` if available.
4. Place `ASplineGeneratingActor` with a spline over the landscape.
5. Set `PaintLayer` to the target layer and, for the edit-layer case, set
   `LandscapeEditLayerName` to an existing named layer.

## Test Matrix

| # | Scenario | Steps | Pass criteria |
| --- | --- | --- | --- |
| 1 | Weight-blended paint | Panel -> **Paint Layer** | Weights increase under the road corridor. |
| 2 | Default half-width | Set `PaintHalfWidth = 0` | Coverage follows the road width. |
| 3 | Fixed half-width | Set `PaintHalfWidth > 0` | Coverage follows the fixed override. |
| 4 | Soft falloff | Set `PaintFallOff > 0` | Weight fades smoothly at the edges. |
| 5 | Hard edge | Set `PaintFallOff = 0` | Full weight inside the band and zero immediately outside it. |
| 6 | Layer reduction | Paint a weight-blended layer | Other weight-blended layers reduce under the painted area. |
| 7 | No-weight-blend caveat | Paint a `bNoWeightBlend` layer | Warning is shown and the target paints without claiming cross-layer removal. |
| 8 | Undo from panel | Paint, then undo | Previous weights are restored. |
| 9 | Undo from CallInEditor | Run `PaintLandscapeLayerNow`, then undo | Previous weights are restored. |
| 10 | Named edit layer | Paint with `LandscapeEditLayerName` set | Edits land on the selected named layer. |

## QA Record

Fill every row during the release pass. Add the map path, relevant screenshots/logs, and any observed
engine-specific behavior to Notes.

| Item | Result | Notes |
| --- | --- | --- |
| Engine version | Pending | |
| Test map / landscape | Pending | |
| Weight-blended `PaintLayer` paints under road | Pending | |
| `PaintHalfWidth = 0` follows road width | Pending | |
| Fixed `PaintHalfWidth` override changes coverage | Pending | |
| Positive `PaintFallOff` fades correctly | Pending | |
| `PaintFallOff = 0` produces a hard edge | Pending | |
| Other layers reduce under weight-blended paint | Pending | |
| `bNoWeightBlend` caveat verified | Pending | |
| Undo restores weights from panel action | Pending | |
| Undo restores weights from CallInEditor action | Pending | |
| Named `LandscapeEditLayerName` receives edits | Pending | |

## Release Claim Boundary

Do not describe landscape painting as release-complete until every QA row passes. Documentation must
continue to say that painting is additive and global and that `bNoWeightBlend` does not guarantee
removal of other layers. Replace/clear, auto-shrink clearing, per-segment paint layers, and multi-layer
paint remain out of scope.

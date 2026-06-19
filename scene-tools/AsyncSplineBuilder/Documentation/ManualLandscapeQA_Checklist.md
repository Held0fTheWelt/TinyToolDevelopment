# Manual Landscape QA — AsyncSplineBuilder Layer Painting

**Plan:** `docs/superpowers/plans/2026-06-01-asyncsplinebuilder-completion-hardening.md` (Task 4)

**Status:** Code + automation complete; **manual QA pending** before release-complete claim.

Use a **disposable** landscape map with at least two paint layers. Back up the map or use source control.

---

## Setup

1. Enable **AsyncSplineBuilder** in the host project.
2. Place a landscape with **two weight-blended paint layers** (e.g. grass + dirt).
3. Add a second test area with a layer marked **`bNoWeightBlend`** if available.
4. Place `ASplineGeneratingActor` with a spline over the landscape.
5. Set `PaintLayer` to the target layer name.

---

## Test matrix

| # | Scenario | Steps | Pass criteria |
|---|----------|-------|---------------|
| 1 | Weight-blended paint | Panel → **Paint Layer** | Weights increase under road corridor |
| 2 | Default half-width | `PaintHalfWidth = 0` | Coverage follows road width |
| 3 | Fixed half-width | Set `PaintHalfWidth` > 0 | Coverage matches override |
| 4 | Soft falloff | `PaintFallOff > 0` | Smooth fade at edges |
| 5 | Hard edge | `PaintFallOff = 0` | Full weight inside band, zero just outside (`HalfWidth + 0.5`) |
| 6 | Layer reduction | Weight-blended layer | Other layers reduce under painted area |
| 7 | No weight blend | `bNoWeightBlend` layer | Warning shown; target paints but no cross-layer guarantee |
| 8 | Undo (panel) | Paint → Ctrl+Z | Weights restored |
| 9 | Undo (CallInEditor) | Paint via actor button → undo | Weights restored |
| 10 | Edit layer | Set `LandscapeEditLayerName` | Edits land on named layer |

---

## Record results

Copy outcomes into `Documentation/CompletionPlan.md` → **Manual QA Record** table.

Example:

```markdown
| Engine version | Pass | UE 5.4.x |
| Test map / landscape | Pass | `/Game/Maps/QA_Landscape` |
| Weight-blended `PaintLayer` paints under road | Pass | |
```

When all rows are **Pass**, set plan Task 4 / release gate to complete.

---

## Out of scope (documented, not tested here)

- Replace/clear paint mode
- Per-segment paint layers
- Multi-layer paint in one action

# Completion Plan

This document tracks the remaining work needed before Async Spline Builder can treat the current landscape painting workflow as release-complete.

The code supports editor height deformation and additive global layer painting through `PaintLandscapeLayerNow` / panel **Paint Layer**. The 2026-06-01 completion hardening implemented true zero-falloff semantics, user-visible `bNoWeightBlend` warnings, and panel controls for the core paint settings. The remaining release gate is real landscape QA.

## Completed Hardening

### True zero-falloff hard edge

`PaintFallOff = 0` is a hard edge. The helper returns full weight at or inside the half-width band and zero outside it, including sub-centimeter distances such as `HalfWidth + 0.5`.

Implemented outcome:

- `Lateral <= HalfWidth` returns full weight.
- `Lateral > HalfWidth` returns zero when falloff is zero or negative.
- Positive falloff keeps the smoothstep fade.
- Automation includes a test just outside the band, not only at `HalfWidth + 1`.

### Non-weight-blended landscape layers

Unreal layer infos can be marked `bNoWeightBlend`. When such a layer is used as `PaintLayer`, target-layer paint can still be written, but the operation cannot promise that other material layers are reduced under the road.

Implemented outcome:

- Output log warning remains.
- Validation and panel summary warn before painting.
- FAQ, troubleshooting, QA, and release docs explain the caveat.
- Manual QA tests both normal weight-blended layers and `bNoWeightBlend` layers.

### Layer paint controls in the panel

The panel currently exposes the action button, but the core paint settings still need to be easier to find.

Implemented outcome:

- `PaintLayer`, `PaintHalfWidth`, and `PaintFallOff` are available in the panel near **Deform Height** and **Paint Layer**.
- Panel mutations use undo transactions and mark validation stale.
- `PaintFallOff = 0` is labelled as a hard edge.

### Real landscape QA evidence

Automation covers the pure math. It does not prove Unreal's real weightmap write path, edit-layer routing, or undo behavior.

Required outcome:

- Manual QA is run on a disposable landscape with at least two paint layers.
- Follow `Documentation/ManualLandscapeQA_Checklist.md` and record results below.
- QA includes panel and CallInEditor paths.
- QA includes undo, named edit layer, width override, falloff fade, hard edge, and `bNoWeightBlend`.

## Verification

2026-06-01:

- Editor target build: passed.
- AsyncSplineBuilder automation: 20 tests found, 20 success, exit code 0.
- `AsyncSplineBuilder.FalloffWeightHardEdge`: passed with the `HalfWidth + 0.5` assertion.
- Manual real-landscape QA: pending.

## Implementation Plan

The detailed agent plan lives at:

```text
docs/superpowers/plans/2026-06-01-asyncsplinebuilder-completion-hardening.md
```

The design notes live at:

```text
docs/superpowers/specs/2026-06-01-asyncsplinebuilder-completion-hardening-design.md
```

## Release Gate

Do not describe landscape layer painting as release-complete until all of these are true:

- `AsyncSplineBuilder.FalloffWeightHardEdge` verifies a value just outside the band. Done 2026-06-01.
- `AsyncSplineBuilder` automation passes. Done 2026-06-01.
- Full editor build passes. Done 2026-06-01.
- Manual landscape paint QA is recorded.
- Documentation states that layer painting is additive and global.
- Documentation states that `bNoWeightBlend` layers do not guarantee removal of other layers.
- Documentation states that replace/clear, auto-shrink clearing, per-segment paint layers, and multi-layer paint are not implemented.

## Manual QA Record

Fill this section during the release pass.

| Item | Result | Notes |
|------|--------|-------|
| Engine version | Pending |  |
| Test map / landscape | Pending |  |
| Weight-blended `PaintLayer` paints under road | Pending |  |
| `PaintHalfWidth = 0` follows road width | Pending |  |
| Fixed `PaintHalfWidth` override changes coverage | Pending |  |
| Positive `PaintFallOff` fades correctly | Pending |  |
| `PaintFallOff = 0` hard edge | Pending |  |
| Other layers reduce under weight-blended paint | Pending |  |
| `bNoWeightBlend` caveat verified | Pending |  |
| Undo restores weights from panel action | Pending |  |
| Undo restores weights from CallInEditor action | Pending |  |
| Named `LandscapeEditLayerName` receives edits | Pending |  |

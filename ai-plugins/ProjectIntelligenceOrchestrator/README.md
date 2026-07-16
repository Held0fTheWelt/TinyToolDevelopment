# Project Intelligence Orchestrator

> Internal/preview online overview. This page documents the current public-safe workflow boundary,
> not a Fab availability claim.

Project Intelligence Orchestrator (PIO) coordinates deterministic, UCM-first workflows while the
participating plugins keep ownership of their data and mutations. It validates workflow manifests,
invokes owner-held routes, writes reconstructable journals and reports, and exposes explicit
review-only or approval-gated execution modes.

## Current Composition Surface

- `pio.composition.compile.v1` turns two project inventories into a deterministic draft manifest.
- The draft always remains unapproved until a human records the review decision.
- `pio.composition.execute.v1` is approval-gated and runs transfer dry-runs before delegated
  mutations begin.
- Wiring materialization follows preview-before-apply and can roll back the active chapter.
- `pio.composition.verify.v1` reports boot checks, findings, budgets, optional content-diet evidence,
  and an optional Lightning variant comparison.
- Headless runs report unavailable measurements as degraded or not measured; they never fabricate a
  pass.

## Requirements and Boundaries

- Engine baseline: Unreal Engine 5.4+.
- Unreal Capability Mesh is the required route gateway.
- APM, UBI, SCD, and other route owners remain optional per workflow; unavailable owners are reported
  explicitly instead of hidden.
- Review-only workflows remain review-only. The composition execute workflow is separately
  approval-gated and delegates mutation to its owning plugins.
- PIO is not the owner of asset copying, Blueprint mutation, indexing, model routing, or content
  optimization.

## Current Proof Boundary

The deterministic read and planning path has been demonstrated through evidence collection,
cross-project inventory, and repeatable draft compilation. The draft still requires human review;
target mutation, materialization, and final runtime verification are not presented as complete.

See the [cross-project composition workflow](../../workflows/cross-project-composition.md).

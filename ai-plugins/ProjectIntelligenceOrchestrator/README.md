# Project Intelligence Orchestrator

> Internal/preview online overview. This page documents the current public-safe workflow boundary,
> not a Fab availability claim.

Project Intelligence Orchestrator (PIO) coordinates deterministic, UCM-first workflows while the
participating plugins keep ownership of their data and mutations. It validates workflow manifests,
invokes owner-held routes, writes reconstructable journals and reports, and exposes explicit
review-only or approval-gated execution modes.

The current internal release line is 1.0.5. Its behavior is implemented for Unreal Engine 5.4 and
later; the descriptor mirrored by this documentation belongs to the UE 5.8 build line.

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
- Current descriptor/build target: Unreal Engine 5.8.
- Unreal Capability Mesh is the required route gateway.
- APM, UBI, SCD, and other route owners remain optional per workflow; unavailable owners are reported
  explicitly instead of hidden.
- Review-only workflows remain review-only. The composition execute workflow is separately
  approval-gated and delegates mutation to its owning plugins.
- PIO is not the owner of asset copying, Blueprint mutation, indexing, model routing, or content
  optimization.

## Current Proof Boundary

The deterministic runner, journals, route mapping, Port Blueprint, content-packaging, composition
compile, approval-gated execute, materialization, and findings-bearing verification surfaces have
UE 5.4 automation evidence. This is implementation proof, not project acceptance: a draft still
requires human review, and restart, runtime verification, comparison, and play proof remain owned by
the target project's operator.

The Blueprint-to-C++ Port Blueprint also has a review-only Translation Evidence lane. PIO binds UBI
deep-export and in-memory compiler diagnostics to UII's source/target C++ and Reflection Surface
bundle, then passes the reviewed evidence onward without extracting source truth or promoting BPJ
content itself.

In content packaging, `verify_pins` is bound to `verify_only:true` and `execute_plan` to
`verify_only:false`; workflow input cannot change those bindings. APM remains the owner of package
review, confirmation, and mutation.

## Status

- Version: 1.0.5
- Status: Internal
- Fab: Internal preview; no public listing claim

See the [cross-project composition workflow](../../workflows/cross-project-composition.md).

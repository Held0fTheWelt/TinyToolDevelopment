# SmartContentDiet PRS Bridge Documentation

This bridge connects reviewed Smart Content Diet placement proposals to Project Restructure Service planning, dry-run, apply, and rollback contracts for projects that do not route the workflow through Unreal Capability Mesh.

## Start Here

- [../README.md](../README.md): product boundary, quick start, guardrails, and technical shape.
- [../CHANGELOG.md](../CHANGELOG.md): release history.

## Source Map

- `FSCDToPRSPlacementAdapter`: converts SCD placement proposals into PRS placement plans and forwards preview/apply/rollback calls.
- `FSCDHealthForPRS`: provides read-only SCD health context to PRS placement evaluation.
- `SCDPRSBridgeTests.cpp`: adapter test coverage.

## Boundary

The bridge never auto-applies a restructure plan. PRS still owns validation, dry-run diffs, confirmation gates, mutation, run records, and rollback.

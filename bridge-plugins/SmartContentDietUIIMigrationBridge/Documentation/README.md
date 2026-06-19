# SmartContentDiet UII Migration Bridge Documentation

This bridge lets Smart Content Diet surface advisory migration findings from Unreal Integration Intelligence handoff artifacts for projects that do not route the workflow through Unreal Capability Mesh.

## Start Here

- [../README.md](../README.md): product boundary, quick start, and technical shape.
- [../CHANGELOG.md](../CHANGELOG.md): release history.

## Source Map

- `FUIIMigrationAdvisorProvider`: reads UII handoff availability and translates migration-relevant guardrails into SCD advisory findings.
- `SmartContentDietUIIMigrationBridgeModule`: registers and unregisters the bridge provider.

## Boundary

The bridge does not generate migration plans, apply patches, move assets, copy files, mutate project settings, or replace UII evidence export. It only presents available UII handoff evidence as SCD migration advice.

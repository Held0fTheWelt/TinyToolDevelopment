<!-- doc-provenance: AKDB:plugins/UnrealCapabilityMesh/architecture.md; docs/architecture/plugins/UnrealCapabilityMesh/product-facts.yml; reconciled 2026-07-19 -->
# Troubleshooting

## Setup Load Fails

Check `Saved/UnrealCapabilityMesh/setup_validation_report.json`.

Common causes:

- no `project_profile.json` in the bundled, enabled-plugin, or project setup roots
- invalid `schema_version`
- manifest path typo
- malformed JSON
- missing required arrays such as `capabilities` or `endpoints`

For first use, a project-local profile is optional. UCM merges its bundled default profile with profiles shipped by enabled plugins. Create a project profile only for intentional overrides or project-owned routes, then click `Reload Setup`.

## Capability Is Not Discovered

Check:

- capability manifest is referenced by the profile in its owning setup root
- capability has a non-empty `capability_id`
- endpoint id exists
- required plugin names are loaded
- required schemas exist

If the capability belongs to another plugin, confirm that plugin is enabled and that its package
contains `Config/UnrealCapabilityMesh/project_profile.json`. Do not copy the provider definition
into the project as a workaround; reload setup and inspect which setup roots were discovered.

## Project Reports Duplicate Definition Warnings

The same provider-owned capability, endpoint, schema, or route likely exists both in a plugin-local
profile and the project override.

Remove the duplicate project copy unless the project intentionally overrides that definition.
Project profiles should normally contain project-owned policy changes or composite routes, while
provider contracts remain plugin-local.

## TTER Does Not Show A Valid UCM Route After Startup

Confirm the optional Tiny Tool Execution Integration Bridge is enabled. Its Editor module reloads
UCM setup before TTER discovery. After enabling a new provider or editing setup, click
`Reload Setup` and refresh tool discovery.

## Route Is Blocked

Open the route report under `Saved/UnrealCapabilityMesh/route_reports`. The route planner records explanations and block reasons.

Common causes:

- no rule allows the aggregate side effects
- route uses `project_mutation` and the default rule blocks it
- asset mutation requires approval or dry-run
- input and output schemas are incompatible

If **EXPERIMENTAL** self automatic approval is enabled in the Route Catalog approval column or profile, disable it before troubleshooting governance behavior. The broad override skips matching deny rules, route asset/project-mutation checks, approval requirements, and dry-run requirements, so it can mask every one of those policy outcomes.

## Endpoint Invocation Fails

Check `Saved/UnrealCapabilityMesh/invocation_reports`.

Common causes:

- class path does not resolve
- function name is wrong
- parameter binding does not match the function parameter
- invocation mode is declared but no generic invoker supports it yet
- provider plugin is not loaded

## Reports Are Empty

Click `Reload Setup` again. The panel reloads manifests and regenerates diagnostics. Also confirm the project config path is the active project, not an engine or example folder.

## Source Validation Reports Hardcoding

Source validation can report partner plugin names or product-specific capability ids in UCM code. Move integration-specific strings into setup JSON instead of adding C++ branches.

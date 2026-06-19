# Troubleshooting

## Setup Load Fails

Check `Saved/UnrealCapabilityMesh/setup_validation_report.json`.

Common causes:

- missing `project_profile.json` in both the project config folder and the bundled plugin config folder
- invalid `schema_version`
- manifest path typo
- malformed JSON
- missing required arrays such as `capabilities` or `endpoints`

For first use, a project-local profile is optional. UCM loads the bundled default profile from `Plugins/UnrealCapabilityMesh/Config/UnrealCapabilityMesh/project_profile.json` when `<YourProject>/Config/UnrealCapabilityMesh/project_profile.json` does not exist. To customize the setup, copy the bundled `Config/UnrealCapabilityMesh` folder into the project `Config/UnrealCapabilityMesh` folder, edit `project_profile.json`, then click `Reload Setup`.

## Capability Is Not Discovered

Check:

- capability manifest is referenced by `project_profile.json`
- capability has a non-empty `capability_id`
- endpoint id exists
- required plugin names are loaded
- required schemas exist

## Route Is Blocked

Open the route report under `Saved/UnrealCapabilityMesh/route_reports`. The route planner records explanations and block reasons.

Common causes:

- no rule allows the aggregate side effects
- route uses `project_mutation` and the default rule blocks it
- asset mutation requires approval or dry-run
- input and output schemas are incompatible

If **EXPERIMENTAL** self automatic approval is enabled in the Route Catalog approval column or profile, disable it while troubleshooting approval behavior. The override is for test/own-risk workflows only and can mask whether a route input supplied explicit approval.

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

## Gate Fails On Hardcoding

The gate scans UCM source for partner plugin names and product-specific capability ids. Move integration-specific strings into setup JSON instead of adding C++ branches.

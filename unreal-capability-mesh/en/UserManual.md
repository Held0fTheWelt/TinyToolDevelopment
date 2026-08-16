<!-- doc-provenance: AKDB:plugins/UnrealCapabilityMesh/architecture.md; docs/architecture/plugins/UnrealCapabilityMesh/product-facts.yml; reconciled 2026-07-19 -->
# User Manual

## Control Panel

Open the panel from:

```text
Tools -> Unreal Capability Mesh
```

The panel is a technical operations view for manifest-driven interoperability. It now uses a status banner and focused pages instead of stacking all tools into one long view.

Pages:

- `Overview`: active profile, inventory counts, availability counts, setup flow, and MCP contract.
- `Capabilities`: loaded capability ids, endpoints, side effects, availability, warnings, and source manifests.
- `Routes`: route catalog plus dry-run and execution input/output.
- `Governance`: active side-effect vocabulary and rule decisions.
- `Tiny Tools`: setup package switches for Tiny Tool Development content.
- `Setup Editor`: type-aware JSON editor for project setup manifests, read-only reference samples, and the non-binding playground sandbox.
- `Config Admin`: whitelisted configuration targets and route presets for list/read/write operations.
- `Diagnostics`: setup validation, discovery, and reload messages.
- `Adapter`: starter manifest writer for adding setup-declared capabilities without a bridge dependency.

## Tiny Tools

The `Tiny Tools` page is driven by catalog manifests under:

```text
Config/UnrealCapabilityMesh/tool_catalogs/
```

The first switch answers whether the project should use Tiny Tool Development setup content. When it is off, all catalog-owned setup entries are removed from the active profile. Individual tool switches then add or deactivate the package entries declared by the catalog:

- capability manifests
- endpoint manifests
- schema manifests
- rule manifests
- route manifests
- transform manifests
- adapter manifests
- config target ids

This is a deactivation model, not file deletion. Manifest files remain in the project and can be re-enabled later.

Tiny Tool packages are intentionally split by ownership. IIS, LLM Store, and UII can be enabled independently. Cross-plugin workflows are separate route switches, so a project can use IIS alone, LLM Store alone, UII+IIS, or IIS+LLM Store without owning the full stack.

The profile field `enabled_config_target_ids` limits which config targets are visible to Config Admin. If the field is absent, Config Admin keeps the legacy behavior and scans every target manifest.

## Setup Editor

The `Setup Editor` page edits project-local manifests under `Config/UnrealCapabilityMesh` with type-aware fields:

- booleans for policy and profile switches
- string arrays for `enabled_*_manifests`
- enum fields such as `invocation_mode` and `side_effects`
- nested objects and object arrays from route, capability, and endpoint manifests

The left tree has three roots:

1. `Project Setup` — editable project manifests, including `project_profile.json`.
2. `Playground Sandbox` — editable sandbox manifests under `playground/` with no real plugin binding. Use `Add playground to profile` to test activation failure, or enable the `Setup Editor Playground` catalog item from `Tiny Tools`.
3. `Reference Samples` — read-only bundled Tiny Tool manifests grouped by catalog plugin, plus UCM core samples. Use `Copy to project` to duplicate a reference manifest into the project config.

Toolbar actions:

- `Save` / `Revert` — write or discard the active manifest file.
- `Validate file` — run `FCapabilityMeshSetupLoader::ValidateManifestFile` on the selected file.
- `Reload Setup` — reload the active mesh after profile or manifest changes.
- `Open source folder` — open the mapped C++ plugin path from `editor/plugin_source_hints.json` when a reference plugin node is selected.

Field typing rules live in `editor/manifest_field_schema.json`.

## Reload Setup

`Reload Setup` calls `FCapabilityMeshService::ReloadSetup`.

It performs this sequence:

1. Clears previous registries and reports.
2. Discovers the bundled UCM setup, plugin-local setup roots from enabled plugins, and the optional project override.
3. Merges their `project_profile.json` files in priority order.
4. Loads capabilities, endpoints, schemas, rules, routes, transforms, and adapters.
5. Registers loaded definitions.
6. Writes setup and registry diagnostics.
7. Runs discovery.
8. Writes discovery and compatibility reports.

Provider-owned manifests should remain below the provider plugin's
`Config/UnrealCapabilityMesh/` folder. Project-local manifests have higher priority and are for
intentional overrides or project-owned composite routes. Duplicating provider definitions into
the project can create override warnings and obscure ownership.

When the optional Tiny Tool Execution Integration Bridge is enabled, its Editor module calls
`ReloadSetup` before registering and discovering projected UCM tools. UCM still owns the resulting
route definitions and every policy decision.

## Discovered Capabilities

The discovered view lists capability id, provider id, interop mode, and availability. Availability can be available, unavailable, unsafe, missing schema, approval required, or plugin not loaded.

## Diagnostics

The diagnostics view shows setup validation errors and warnings plus messages returned from reload/discovery. Use it first when a route or endpoint does not appear.

## Routes

Enter a route id and run a dry run. UCM resolves route steps, checks capability availability, aggregates side effects, evaluates rules, and writes a route report.

Enter route JSON input and execute a route when the dry run is clean. UCM plans the route first, blocks policy violations and dry-run-required routes, then invokes each endpoint in step order. Routes that require approval must include `approval_granted: true` or `approval: "granted"` in the route input before they execute unless the explicitly marked **EXPERIMENTAL** self automatic approval override is active for that route. Step outputs and route output are written to `Saved/UnrealCapabilityMesh/route_execution_reports/`.

### Route Catalog

The **Route Catalog** on the Routes page lists every loaded route from setup manifests in a plugin-grouped table:

| Column | Content |
| --- | --- |
| Plugin / Route | Expandable plugin groups and route rows with policy, steps, endpoints, side effects, and source manifest details |
| Approve all at own risk | **EXPERIMENTAL** self automatic approval controls |

Column header:

- **Approve all at own risk** — global switch for every approval-gated route in the active profile. When enabled, per-route checkboxes are disabled because all approval-gated routes inherit the override.

Plugin rows:

- Expand/collapse arrow, plugin display name, route count, and a per-plugin approval checkbox when that plugin owns approval-gated routes.

Route rows:

- Expand/collapse arrow, route id, and route detail text from the dry-run plan.
- Approval-gated routes: per-route checkbox (unless **Approve all** is active).
- Routes that do not require approval: `n/a` with a tooltip explaining that no approval gate applies.

An orange warning above the catalog states that self automatic approval activates a broad policy bypass. Matching deny rules, route asset/project-mutation checks, approval requirements, and dry-run requirements are skipped; enabled routes can therefore change editor state without those safeguards.

The same settings persist in `project_profile.json` (`experimental_self_approval_all_routes`, `experimental_self_approved_route_ids`) and can be read or changed over MCP with `mesh_configure_experimental_self_approval`; enabling through MCP requires `acknowledge_experimental_risk: true`. Keep self automatic approval disabled for normal production use.

The `Config Admin` page can prepare the standard config-admin route ids and JSON envelopes in the route runner. This keeps MCP, editor users, and automation on the same route contract.

## DataAsset And DataTable Administration

`UCapabilityMeshAssetAdminSubsystem` exposes JSON-callable operations for DataAsset/DataTable administration:

- `ExportAdminSurfaceJson`: exports a DataAsset or DataTable into a portable admin envelope and can write it under `Saved/UnrealCapabilityMesh/asset_admin`.
- `ImportAdminSurfaceJson`: imports a previously exported envelope into an existing DataAsset or DataTable.
- `SyncAdminSurfaceJson`: copies editable fields from a DataAsset to one DataTable row or from one DataTable row back into a DataAsset.

Composite DataTables are safe export sources. Direct writes to a Composite DataTable are blocked; target the concrete child DataTable that should own the row.

Example route input for a mutating sync route:

```json
{
  "approval_granted": true,
  "request_json": "{\"source_object_path\":\"/Game/Config/DA_Settings.DA_Settings\",\"target_object_path\":\"/Game/Config/DT_Settings.DT_Settings\",\"mode\":\"data_asset_to_data_table\",\"row_name\":\"Default\"}"
}
```

## Configuration Administration

`UCapabilityMeshConfigAdminSubsystem` exposes manifest-whitelisted configuration targets. This is the standard MCP route for plugin settings and project config files.

Targets are declared under:

```text
Config/UnrealCapabilityMesh/config_targets/
```

Common routes:

- `capability_mesh.config_admin.list_targets.v1`
- `capability_mesh.config_admin.read_target.v1`
- `capability_mesh.config_admin.write_target.v1`

Read example:

```json
{
  "request_json": "{\"target_id\":\"example_plugin.settings\"}"
}
```

Write example:

```json
{
  "approval_granted": true,
  "request_json": "{\"target_id\":\"example_plugin.settings\",\"fields\":{\"bEnabled\":true}}"
}
```

Object-instance targets, such as an asset-backed configuration object, also require `object_path` in the request JSON. JSON-file targets accept `payload` or `payload_json`.

## MCP Access

`UCapabilityMeshMcpGatewaySubsystem` exposes setup reload, capability listing, route dry-run, route execution, and endpoint invocation as JSON-callable functions. Unified MCP Server attaches to that gateway through the generic `mesh` provider when both plugins are loaded.

Common UMCP tool names:

- `mesh_reload_setup`
- `mesh_list_capabilities`
- `mesh_list_routes`
- `mesh_configure_experimental_self_approval`
- `mesh_dry_run_route`
- `mesh_execute_route`
- `mesh_invoke_endpoint`

Unified MCP Server also flattens declared routes into direct MCP tools named
`mesh_route_<sanitized_route_id>_<hash>`. These tools accept `mode: "dry_run"`
for analysis or `mode: "execute"` for execution. If no `input` or `input_json`
field is supplied, the remaining arguments become the route input object. UCM
exports route-derived `input_schema`, `output_schema`, and `tool_annotations`
through `mesh_list_routes`; UMCP publishes those as MCP `inputSchema`,
`outputSchema`, and annotations for each `mesh_route_*` tool. For common routes
that bind to `request_json`, UMCP also mirrors flattened arguments into that
serialized request field so AI can call tools with understandable named
parameters.

Use `mesh_execute_route` for DataAsset/DataTable import, sync, and configuration writes so route policy and approval checks remain active. Use `mesh_configure_experimental_self_approval` only for **EXPERIMENTAL** test or own-risk workflows; it can enable the broad policy bypass globally or for selected route ids. Use `mesh_list_routes` to verify current MCP-visible state; it reports the global experimental flag, selected route overrides, and the effective per-route bypassed plan.

## Primary UCM Integration

The active project profile connects Tiny Tool Development products with setup-declared routes. Use this UCM path as the normal integration model. Freebie Bridges are only for teams without UCM or for developers who want direct-adapter examples.

- `uii_to_iis_context_pack.v1`: UII evidence -> IIS import/search/context-pack flow, with LLM Store embedding route execution where configured.
- `prs.build_asset_move_plan.v1`, `prs.preview_plan.v1`, `prs.apply_plan.v1`, `prs.rollback.v1`: PRS placement workflows through UCM route policy and approval.
- `scd.migration_advice_from_handoff.v1`: UII handoff contract/envelope -> SmartContentDiet advisory migration findings through UCM.
- `capability_mesh.asset_admin.export.v1`, `capability_mesh.asset_admin.import.v1`, `capability_mesh.asset_admin.sync.v1`: DataAsset/DataTable administration through the mesh.
- `capability_mesh.config_admin.list_targets.v1`, `capability_mesh.config_admin.read_target.v1`, `capability_mesh.config_admin.write_target.v1`: whitelisted settings and config-file administration through the mesh.

Project or asset mutation routes still require explicit route approval unless the explicitly marked **EXPERIMENTAL** self automatic approval override is active for that route.

## Rules

Rules decide whether a route is allowed, requires approval, requires dry-run, or is blocked. Rules are ordered by priority and are declared in JSON.

## Adapter Editor

The adapter editor writes a simple adapter manifest under `Config/UnrealCapabilityMesh/adapters`. It is intended as a starting point for mapping another plugin into UCM without adding direct C++ dependencies to the hub.

<!-- doc-provenance: AKDB:plugins/UnrealCapabilityMesh/architecture.md; docs/architecture/plugins/UnrealCapabilityMesh/product-facts.yml; reconciled 2026-07-19 -->
# Manifest And Settings Reference

UCM does not expose a `UDeveloperSettings` page. Configuration is JSON loaded from three setup-root classes:

1. UCM's bundled default setup.
2. `Config/UnrealCapabilityMesh` folders shipped by enabled provider plugins.
3. The optional project `Config/UnrealCapabilityMesh` override.

Profiles are merged in that order, with the project override taking precedence. A project-local profile is not required for first use or for an enabled provider plugin's routes. Create one only when the project intentionally overrides setup or owns composite routes.

## `project_profile.json`

| Field | Purpose |
| --- | --- |
| `schema_version` | Must start with `capability_mesh.project_profile`. |
| `profile_id` | Stable id for the active profile. |
| `display_name` | Human-readable profile name. |
| `enable_knowledge_store` | Writes invocation history when true. |
| `experimental_self_approval_all_routes` | **EXPERIMENTAL, use at your own risk.** When true, configured routes use the broad policy bypass described below. Keep false for normal use. |
| `experimental_self_approved_route_ids` | **EXPERIMENTAL, use at your own risk.** Route ids that use the broad policy bypass when `experimental_self_approval_all_routes` is false. |
| `active_ruleset_id` | Name of the ruleset to treat as active. |
| `enabled_capability_manifests` | Capability manifest paths. |
| `enabled_endpoint_manifests` | Endpoint manifest paths. |
| `enabled_schema_manifests` | Schema manifest paths. |
| `enabled_rule_manifests` | Rule manifest paths. |
| `enabled_route_manifests` | Route manifest paths. |
| `enabled_transform_manifests` | Transform manifest paths. |
| `enabled_adapter_manifests` | Adapter manifest paths. |
| `enabled_config_target_ids` | Optional allow-list for Config Admin targets. If absent, all target manifests are scanned. |
| `tiny_tool_development_plugins_enabled` | UI-managed opt-in switch for the Tiny Tool Development catalog. |
| `reflection_metadata_keys` | Metadata keys used when scanning reflection-exposed capabilities. |
| `optional_scan_paths` | Additional folders or files to scan for JSON manifests. |
| `setup_editor_playground_enabled` | UI-managed opt-in switch for the Setup Editor playground catalog item. |
| `setup_editor_show_cpp_source_hints` | Optional profile flag for showing C++ source hints in the Setup Editor reference tree. |

Relative manifest entries are resolved from the setup root that owns the profile, with project and project-root fallbacks where applicable. For customization, copy only the profile or manifests the project intends to override. Leaving provider-owned definitions plugin-local keeps route ownership clear and avoids duplicate-definition warnings.

## Setup Editor Assets

| Path | Purpose |
| --- | --- |
| `editor/manifest_field_schema.json` | Maps JSON field paths to editor widget types (`bool`, `enum`, `string_array`, and similar). |
| `editor/plugin_source_hints.json` | Maps catalog `item_id` values to C++ plugin source folders for read-only reference browsing. |
| `playground/` | Editable sandbox manifests without real plugin binding. |
| `tool_catalogs/setup_editor_playground.json` | Catalog item that adds playground manifests to `project_profile.json`. |

## Capability Manifest

Capabilities declare what a provider can do. Each capability has an id, title, category, side effects, input ports, output ports, and endpoint id.

## Endpoint Manifest

Endpoints declare how a capability is invoked. Important fields:

- `endpoint_id`
- `invocation_mode`
- `target`
- `parameters`
- `availability`

Supported invocation modes include reflection functions, file contracts, modular feature providers, Python bridge, commandlet, and external process declarations. Reflection, file contract, and UCM endpoint-provider modular features execute directly; Python bridge, commandlet, and external process declarations are discovery-only until their generic invokers are implemented.

## Schema Manifest

Schemas describe the expected shape of input and output ports. UCM uses schema ids to check compatibility.

## Rule Manifest

Rules decide whether a route is allowed. Common side effects:

- `read_only`
- `saved_folder_write`
- `project_config_write`
- `asset_mutation`
- `project_mutation`
- `network`
- `ai_completion`

## Route Manifest

Routes define ordered steps. Each step references a capability id and declares input/output bindings.

Mutating routes should set `allow_asset_mutation` or `allow_project_mutation` only when the operation is intentional. The executor normally requires approval at runtime; provide `approval_granted: true`, `approvalGranted: true`, or `approval: "granted"` in the route input unless the **EXPERIMENTAL** self automatic approval override below is intentionally active.

### Experimental Self Automatic Approval

`experimental_self_approval_all_routes` and `experimental_self_approved_route_ids` are explicitly experimental escape hatches for testing and local own-risk workflows. When enabled, UCM passes `bExperimentalPolicyBypass=true` through route planning and execution. Matching rules with `allow=false` no longer block the route, rule-level approval and dry-run requirements are ignored, the route-level asset/project-mutation checks are skipped, and the final plan clears both approval and dry-run requirements.

Keep both settings off for normal and production workflows. The editor Route Catalog labels these switches as **EXPERIMENTAL** and states the full bypass scope. MCP hosts can read or change the same settings through `mesh_configure_experimental_self_approval`; enabling through MCP requires `acknowledge_experimental_risk: true`.

## Transform Manifest

Transforms map source JSON to target JSON. They are used to adapt outputs from one capability into inputs for another.

## Adapter Manifest

Adapters map third-party plugin functions into UCM without adding a direct C++ dependency to the hub.

## Asset Administration Setup

The bundled setup under UCM's own `Config/UnrealCapabilityMesh` declares DataAsset/DataTable administration capabilities:

- `capability_mesh.asset_admin.export`
- `capability_mesh.asset_admin.import`
- `capability_mesh.asset_admin.sync`

All three call `UCapabilityMeshAssetAdminSubsystem` through `reflection_subsystem_function` endpoints. MCP hosts should route through these declarations instead of calling project-specific bridge code.

## Configuration Target Manifest

Configuration administration targets are whitelisted separately from route manifests under:

```text
Config/UnrealCapabilityMesh/config_targets/*.json
```

Target manifests use:

```json
{
  "schema_version": "capability_mesh.config_target_manifest.v1",
  "targets": [
    {
      "target_id": "example_plugin.settings",
      "display_name": "Example Plugin Settings",
      "description": "Explains what the target controls and when it should be edited.",
      "kind": "uobject_config",
      "class_path": "/Script/ExamplePlugin.ExamplePluginSettings",
      "required_plugin_names": ["ExamplePlugin"]
    }
  ]
}
```

Supported `kind` values:

- `uobject_config`: reads and writes config properties on a class default object, then saves config.
- `uobject_instance`: reads and writes editable fields on a whitelisted object class. Requests must include `object_path`.
- `json_file`: reads and writes one declared JSON file under an allowed base directory.

Every target should include a non-empty `description`; Config Admin surfaces missing descriptions as manifest warnings because users need context before reading or writing a target.

The standard routes are `capability_mesh.config_admin.list_targets.v1`, `capability_mesh.config_admin.read_target.v1`, and `capability_mesh.config_admin.write_target.v1`. Write routes declare `project_config_write` and `asset_mutation` so config files, config objects, DataAssets, and editable object instances all pass through the same approval and dry-run path.

## Tool Catalog Manifest

Tool catalogs live under:

```text
Config/UnrealCapabilityMesh/tool_catalogs/*.json
```

They group setup entries into UI-switchable packages. A package can declare capability, endpoint, schema, rule, route, transform, adapter manifest paths and config target ids. The UI deactivates packages by removing those entries from `project_profile.json`; it does not delete manifest files.

Catalog packages should stay as small as the ownership boundary allows. A plugin package should only add that plugin's own capabilities, endpoints, schemas, and config targets. Cross-plugin workflows should be separate route packages that reference the already enabled building blocks. This keeps IIS-only, LLM Store-only, UII+IIS, and IIS+LLM Store setups valid without requiring every Tiny Tool Development plugin.

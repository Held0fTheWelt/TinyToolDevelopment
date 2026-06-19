# UCM Setup Editor Help

The Setup Editor is the structured manifest editor inside `Tools -> Unreal Capability Mesh`. It is meant for project-local setup work under `Config/UnrealCapabilityMesh` and for reading bundled reference manifests without editing them in place.

Online documentation entry:

<https://github.com/Held0fTheWelt/TinyToolDevelopment/blob/master/foundation-plugins/UnrealCapabilityMesh/Documentation/SetupEditorHelp.md>

## Main Areas

| Area | Purpose |
| --- | --- |
| Reference tree | Shows editable project setup, playground manifests, and read-only reference samples. |
| Header | Shows the selected manifest path and whether the file is saved, dirty, or read-only. |
| Action row | Saves, reverts, validates, reloads setup, opens help/tutorial documentation, copies references, opens source hints, and manages playground activation. |
| Structured JSON editor | Groups fields by intent and renders arrays or nested objects as table-like sections. |
| Validation output | Shows file validation results, reload messages, and setup warnings. |

## Action Row

| Button | Use |
| --- | --- |
| `Save` | Writes the selected editable manifest file. |
| `Revert` | Reloads the selected manifest from disk and discards unsaved changes. |
| `Validate file` | Runs file-level manifest validation and prints issues in the validation output. |
| `Reload Setup` | Reloads profile manifests, route catalogs, registries, discovery state, and diagnostics. |
| `Help` | Opens this Setup Editor help page in the TinyToolDevelopment documentation. |
| `Tutorial` | Opens the guided Setup Editor tutorial. |
| `Copy to project` | Copies a read-only reference manifest into the editable project config tree. |
| `Open source folder` | Opens the C++ source folder hinted by a selected reference plugin node. |
| `Add playground to profile` | Adds sandbox manifests to `project_profile.json` for editor experimentation. |
| `Remove playground from profile` | Removes sandbox manifest references from `project_profile.json`. |

## Field Sections

| Section | Typical fields |
| --- | --- |
| Identity and contract | `schema_version`, `profile_id`, `capability_id`, `endpoint_id`, `route_id`, `category`, `display_name`, `description` |
| Availability and policy | `availability`, `requires_editor`, `required_plugin_names`, `side_effects`, rule decisions, approvals |
| Bindings and data flow | `inputs`, `outputs`, `parameters`, `endpoint_id`, `invocation_mode`, route bindings, transforms |
| Setup references | `enabled_*_manifests`, config target ids, plugin names, class paths, source hints |
| Schema definition | JSON schema fields such as `properties`, `required`, `type`, and nested schema objects |
| Other fields | Valid JSON fields that do not yet map to a known editor section |

## Table Editing

Primitive arrays are shown as rows with `Index`, `Value`, and `Action`.

Object arrays, such as `capabilities`, `endpoints`, `inputs`, `outputs`, and `parameters`, are shown as grouped item blocks. Each item has a compact header with a readable summary and a `Remove` action. The fields inside each item are shown as a two-column table: field metadata on the left, editor control on the right.

For known object arrays, `Add item` creates a useful starting object. For example:

| Array | New item starts with |
| --- | --- |
| `inputs` / `outputs` | `direction`, `port_id`, `schema_id` |
| `parameters` | `param`, `bind` |
| `capabilities` | `capability_id`, `category`, `endpoint_id`, empty `inputs`, `outputs`, `side_effects` |
| `endpoints` | `endpoint_id`, `invocation_mode`, empty `parameters` |
| `routes` | `route_id`, `capability_id`, `endpoint_id`, empty route binding arrays |

## Related Documentation

- [Setup Editor Tutorial](SetupEditorTutorial.md)
- [Manifest and Settings Reference](SettingsReference.md)
- [Integration Guide](INTEGRATION.md)
- [Troubleshooting](TROUBLESHOOTING.md)

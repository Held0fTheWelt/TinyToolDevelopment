# UCM Setup Editor Tutorial

This tutorial walks through a safe manifest editing pass in the Setup Editor. It assumes the Unreal Capability Mesh plugin is enabled and the editor is open.

Online documentation entry:

<https://github.com/Held0fTheWelt/TinyToolDevelopment/blob/master/foundation-plugins/UnrealCapabilityMesh/Documentation/SetupEditorTutorial.md>

## Goal

Create or adjust a project-local manifest, validate it, reload the mesh, and confirm that the edited setup is visible in the control panel.

## 1. Open The Setup Editor

1. Open `Tools -> Unreal Capability Mesh`.
2. Select the `Setup Editor` page.
3. Keep `Show C++ source hints in reference tree` enabled while learning the shipped reference setup.

The left tree has three practical zones:

| Zone | Meaning |
| --- | --- |
| Project Setup | Editable manifests under the project `Config/UnrealCapabilityMesh` folder. |
| Playground Sandbox | Editable test manifests with no real plugin binding. |
| Reference Samples | Read-only bundled examples that can be copied into the project. |

## 2. Start From A Reference

1. Pick a read-only reference manifest that is close to what you need.
2. Click `Copy to project`.
3. Select the copied file in `Project Setup`.

The header should now show an editable project path rather than a read-only reference path.

## 3. Edit Identity Fields

In `Identity and contract`, set the fields that make the manifest recognizable:

| Field | Guidance |
| --- | --- |
| `schema_version` | Keep the existing manifest family and version unless the reference is outdated. |
| `capability_id` / `endpoint_id` / `route_id` | Use stable, dotted ids such as `myplugin.asset_scan`. |
| `category` | Group related capabilities, for example `asset_admin`, `quality`, or `project_restructure`. |
| `description` | Explain what the route or capability does, including relevant side effects. |

## 4. Edit Data Flow

Use the `Bindings and data flow` section to make the manifest operational.

For capability ports:

| Array | Required idea |
| --- | --- |
| `inputs` | What the capability consumes, with `port_id` and `schema_id`. |
| `outputs` | What the capability produces, with `port_id` and `schema_id`. |

For endpoints:

| Field | Required idea |
| --- | --- |
| `endpoint_id` | The callable endpoint id referenced by capabilities or routes. |
| `invocation_mode` | How UCM invokes the endpoint. |
| `parameters` | Bind route input/output values to endpoint parameters. |

Object arrays render as item blocks. Use `Add item` to create a starter row, then fill the fields in the table.

## 5. Check Policy And Availability

In `Availability and policy`, confirm the setup can be discovered and governed correctly:

| Field | Guidance |
| --- | --- |
| `required_plugin_names` | List provider plugin names that must be loaded. |
| `requires_editor` | Enable for editor-only functions. |
| `side_effects` | Declare effects such as `read_only`, `saved_folder_write`, `project_config_write`, or `asset_mutation`. |
| rule fields | Keep approval or block behavior explicit for mutating routes. |

## 6. Save, Validate, Reload

1. Click `Save`.
2. Click `Validate file`.
3. Fix validation output until no critical issue remains.
4. Click `Reload Setup`.
5. Check `Capabilities`, `Routes`, `Governance`, and `Diagnostics` for the updated setup.

## 7. Use Playground Safely

The playground is for UI and validation experiments. It is expected to fail activation because `SetupEditorSandbox` is not a real provider plugin.

| Button | Use |
| --- | --- |
| `Add playground to profile` | Adds sandbox manifests to `project_profile.json`. |
| `Remove playground from profile` | Removes sandbox manifests from the active profile. |

Use the playground to learn field structure, not as a production integration.

## Next Reading

- [Setup Editor Help](SetupEditorHelp.md)
- [Manifest and Settings Reference](SettingsReference.md)
- [Integration Guide](INTEGRATION.md)
- [Troubleshooting](TROUBLESHOOTING.md)

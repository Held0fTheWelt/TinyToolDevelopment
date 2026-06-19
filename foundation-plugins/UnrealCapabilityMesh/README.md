# Unreal Capability Mesh

Unreal Capability Mesh (UCM) is a setup-driven interoperability hub for Unreal Engine plugins. It reads JSON manifests from project-local config, discovers declared capabilities, validates schemas and policies, plans safe routes, and writes local diagnostics.

UCM is published on Fab as **Unreal Capability Mesh - The Plug for your Tools**:

https://www.fab.com/listings/fd186d26-cdcf-4c4f-93d4-50e437b7673e

UCM contains no product-specific bridge logic. Integrations are declared through manifests under `Config/UnrealCapabilityMesh/`; a plugin-installed copy is shipped under `UnrealCapabilityMesh/Config/UnrealCapabilityMesh/` and mirrored into `ProjectConfigDir/UnrealCapabilityMesh` on first editor startup.

It also includes a generic DataAsset/DataTable administration surface for exporting, importing, and synchronizing setup data through declared UCM endpoints, plus a JSON MCP gateway for setup reload, capability listing, dry runs, and route execution.

Approval-gated routes can be switched to **EXPERIMENTAL** self automatic approval from the Route Catalog approval column on the Routes page, `project_profile.json`, or the MCP tool `mesh_configure_experimental_self_approval`. This is for testing/local own-risk use only and should remain disabled for normal production workflows.

## Modules

| Module | Purpose |
| --- | --- |
| `UnrealCapabilityMesh` | Editor-facing data contracts, manifest loading, registries, rule evaluation, route planning, fast route execution, transform handling, invocation routing, diagnostics. |
| `UnrealCapabilityMeshEditor` | Tools menu entry and editor control panel for reload, discovery, diagnostics, dry-run routes, and adapter authoring. |
| `UnrealCapabilityMeshDeveloper` | Developer-only automation fixtures and test invoker used by validation gates. |

## Quick Start

1. Enable the plugin in your `.uproject`.
2. The plugin ships setup manifests and a default profile under `UnrealCapabilityMesh/Config/UnrealCapabilityMesh/`; UCM can load this bundled profile immediately if the project does not have `Config/UnrealCapabilityMesh/project_profile.json` yet.
3. Open `Tools -> Unreal Capability Mesh`.
4. Click `Reload Setup`.
5. To customize the setup, copy the bundled `Config/UnrealCapabilityMesh` folder into the project `Config/UnrealCapabilityMesh` folder, edit `project_profile.json`, then click `Reload Setup` again.
6. Dry-run or execute a route from the panel.
7. Review generated reports under `Saved/UnrealCapabilityMesh/`.

## Setup Layout

```text
Config/UnrealCapabilityMesh/
  project_profile.json
  capabilities/
  endpoints/
  schemas/
  rules/
  routes/
  transforms/
  adapters/
```

Example ecosystem manifests are bundled under the plugin's `Config/UnrealCapabilityMesh/` and are mirrored into your project on first start; reference them from the active project profile.

The bundled Tiny Tool Development profile includes editor job list/status routes for IIS, LLM Store, SmartContentDiet, and Unified MCP Server, plus Async Spline Builder MCP routes for actor creation/list/read/rebuild/validation, live spline application, point-list reads, and track-settings application.

## Documentation

- [Buyer Guide](Documentation/BUYER_GUIDE.md)
- [Quick Start](Documentation/QUICKSTART.md)
- [User Manual](Documentation/UserManual.md)
- [Technical Overview](Documentation/TechnicalOverview.md)
- [Code Documentation](Documentation/CodeDocumentation.md)
- [Manifest and Settings Reference](Documentation/SettingsReference.md)
- [Integration Guide](Documentation/INTEGRATION.md)
- [Troubleshooting](Documentation/TROUBLESHOOTING.md)
- [FAQ](Documentation/FAQ.md)
- [Release Checklist](Documentation/ReleaseChecklist.md)

## For Maintainers (Not Required To Use The Plugin)

Building from source and the validation gate (`Gates/capability_mesh_gate/`) live in the
development repository and are **not** part of the Fab package. You do not need Python or any gate
to install or use UCM — see [Quick Start](Documentation/QUICKSTART.md).

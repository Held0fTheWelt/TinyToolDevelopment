# Code Documentation

This document is a source-reading guide for Unreal Capability Mesh C++ code.

## Main Entry Points

| File | What To Read It For |
| --- | --- |
| `Source/UnrealCapabilityMesh/Public/CapabilityMeshTypes.h` | Shared data contracts for manifests, routes, reports, discovery, side effects, and binding contexts. |
| `Source/UnrealCapabilityMesh/Public/CapabilityMeshService.h` | Main service facade used by editor UI and future integrations. |
| `Source/UnrealCapabilityMesh/Private/CapabilityMeshService.cpp` | End-to-end orchestration for reload, discovery, dry-run, route execution, invocation, and adapter save. |
| `Source/UnrealCapabilityMesh/Private/CapabilityMeshRouteExecutor.cpp` | Fast in-process route executor that keeps one binding context across ordered generic endpoint calls. |
| `Source/UnrealCapabilityMesh/Public/CapabilityMeshAssetAdminSubsystem.h` | JSON-callable DataAsset/DataTable export, import, and sync surface for setup and MCP access. |
| `Source/UnrealCapabilityMesh/Public/CapabilityMeshMcpGatewaySubsystem.h` | JSON-callable MCP gateway for reload, capability/route listing, experimental self-approval administration, dry-run, route execution, and endpoint invocation. |
| `Source/UnrealCapabilityMeshEditor/Private/SCapabilityMeshControlPanel.cpp` | Editor workflow and UI calls into the service. |

## Runtime Module

### `CapabilityMeshTypes`

`CapabilityMeshTypes.h/.cpp` define the vocabulary of the system:

- manifest structures for capabilities, endpoints, schemas, rules, routes, transforms, and adapters
- side-effect tags used by policies
- invocation mode and availability enums
- route plan, invocation report, discovery entry, validation issue, and knowledge record
- helper functions for config/output roots and enum string conversion

`CapabilityMeshGetConfigRoot()` resolves to `Project/Config/UnrealCapabilityMesh`. `CapabilityMeshGetOutputRoot()` resolves to `Project/Saved/UnrealCapabilityMesh`.

### `FCapabilityMeshSetupLoader`

The setup loader reads JSON files and converts them into typed C++ definitions. It always starts with `project_profile.json`, then resolves explicit or scanned manifest paths. It validates the `schema_version` prefix for each manifest type and records issues in `FCapabilityMeshSetupValidationReport`.

### `FCapabilityMeshRegistry`

The registry stores loaded capabilities, endpoints, and adapters. It provides lookup by capability id, endpoint id, and endpoint referenced by a capability.

`FCapabilityMeshSchemaRegistry` stores schemas and checks whether an output port schema can connect to an input port schema.

### `FCapabilityMeshDiscoveryService`

Discovery evaluates whether declared capabilities are available in the current editor context. It checks required plugin names, editor requirements, endpoint definitions, schema availability, and supported invocation modes. It writes discovered entries for diagnostics and UI display.

### `FCapabilityMeshRoutePlanner`

The route planner builds a dry-run plan from a route definition. It resolves each route step, finds the matching capability and endpoint, collects side effects, checks schema compatibility, and asks the rule engine whether the route is allowed.

### `FCapabilityMeshRouteExecutor`

The route executor runs an already declared route without product-specific code. It plans the route, blocks unsafe policy states, keeps one JSON binding context across all steps, invokes generic endpoints in order, and records route/step outputs for diagnostics.

Approval-required routes normally execute only when the route input contains `approval_granted: true`, `approvalGranted: true`, or `approval: "granted"`. This lets setup or MCP callers perform allowed mutating operations without bypassing the side-effect model.

The service layer also contains the **EXPERIMENTAL** self automatic approval override. When `project_profile.json` enables `experimental_self_approval_all_routes` or includes a route id in `experimental_self_approved_route_ids`, `FCapabilityMeshService` passes `bExperimentalPolicyBypass=true` to the planner and executor. The rule engine then ignores matched deny rules, skips route asset/project-mutation checks, and clears approval and dry-run requirements. This broad bypass is intentional and is for testing/local own-risk use only.

### `UCapabilityMeshAssetAdminSubsystem`

The asset admin subsystem is the generic DataAsset/DataTable administration surface. It exposes three Blueprint/reflection-callable JSON functions:

- `ExportAdminSurfaceJson`
- `ImportAdminSurfaceJson`
- `SyncAdminSurfaceJson`

Exports produce a `capability_mesh.asset_admin.v1` envelope. DataAssets export editable/config/Blueprint-visible properties as Unreal text values. DataTables export native rows plus text rows for field-level sync. Composite DataTables can be exported, but direct writes are blocked so callers must target the concrete child table that owns the row.

### `UCapabilityMeshMcpGatewaySubsystem`

The MCP gateway wraps the service facade in JSON-callable functions:

- `ReloadSetupJson`
- `ListCapabilitiesJson`
- `ListRoutesJson`
- `ConfigureExperimentalSelfApprovalJson`
- `DryRunRouteJson`
- `ExecuteRouteJson`
- `InvokeEndpointJson`

UMCP uses this gateway through reflection, and other MCP hosts can do the same. Mutating work should go through `ExecuteRouteJson` so route policy and approval checks are preserved unless the explicit broad experimental bypass is enabled. `ConfigureExperimentalSelfApprovalJson` requires risk acknowledgement before enabling that bypass over MCP.

### `FCapabilityMeshRuleEngine`

The rule engine evaluates ordered rules. Rules can allow, block, require user approval, require dry-run, and explain the reason. This is where side-effect policy becomes a concrete route decision.

### `FCapabilityMeshTransformEngine`

The transform engine applies declarative mappings between JSON objects. Supported mapping concepts include copying values and setting constants into target paths.

### `FCapabilityMeshInvocationRouter`

The invocation router chooses an invoker based on endpoint invocation mode:

- reflection static function
- reflection subsystem function
- reflection CDO function
- file contract
- modular feature provider

The router writes an `FCapabilityMeshInvocationReport` with success, warnings, errors, mode, duration, endpoint id, and capability id.

### `FCapabilityMeshDiagnosticsWriter`

The diagnostics writer persists setup validation, registry, discovery, compatibility, route, and invocation reports under `Saved/UnrealCapabilityMesh`.

### `FCapabilityMeshKnowledgeStore`

The knowledge store records recent invocation success, failure counts, and average duration per capability when the active profile enables it.

## Editor Module

`UnrealCapabilityMeshEditorModule.cpp` registers the Tools menu entry through the nomad tab spawner (`GetToolsCategory()`) and the dockable control panel. A separate manual menu registration is intentionally not used, so the entry appears only once.

`SCapabilityMeshControlPanel.cpp` is the UI surface. It calls:

- `ReloadSetup` when the panel opens or the button is clicked
- `DryRunRoute` when the user tests a route id
- `SaveAdapterManifest` when the adapter editor creates a mapping

The panel reads reports from the service and displays discovered capabilities, diagnostics, routes, rules, a text graph, and adapter fields.

The **Routes** page **Route Catalog** (`BuildRouteCatalogPanel`, `RebuildRouteCatalogRows`) groups routes by owning plugin display name from capability metadata, supports expand/collapse at plugin and route level, and exposes **EXPERIMENTAL** self automatic approval in a dedicated right column. The column header hosts **Approve all at own risk**; plugin rows can toggle all approval-gated routes for that plugin; route rows toggle individual approval-gated routes. State is persisted through `project_profile.json` and reflected in `mesh_list_routes` / `mesh_configure_experimental_self_approval`.

## Developer Module

`CapabilityMeshTestInvoker` is a small reflection target used by sample endpoints and automation. `CapabilityMeshAutomationTests.cpp` verifies loader, registry, planning, and invocation behavior.

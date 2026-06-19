# Technical Overview

## Architecture

UCM has three modules:

- `UnrealCapabilityMesh`: editor-facing logic and public contracts.
- `UnrealCapabilityMeshEditor`: editor panel and menu integration.
- `UnrealCapabilityMeshDeveloper`: developer-only tests and fixtures.

The core module is intentionally generic. It does not branch on partner plugin names or provider-specific capability ids.

## Data Flow

```text
Config/UnrealCapabilityMesh/project_profile.json
        |
        v
FCapabilityMeshSetupLoader
        |
        v
Registries: capabilities, endpoints, schemas, rules, routes, transforms, adapters
        |
        v
FCapabilityMeshDiscoveryService
        |
        v
Reports in Saved/UnrealCapabilityMesh
```

For route dry runs:

```text
Route id
  -> FCapabilityMeshRoutePlanner
  -> FCapabilityMeshRuleEngine
  -> route report and explanations
```

For route execution:

```text
Route id + JSON input
  -> FCapabilityMeshRoutePlanner
  -> FCapabilityMeshRouteExecutor
  -> one shared binding context
  -> generic endpoint invokers in route-step order
  -> route execution report and step outputs
```

For endpoint invocation:

```text
Endpoint id + capability id + JSON input
  -> FCapabilityMeshInvocationRouter
  -> reflection/file/modular-feature invoker
  -> invocation report
  -> optional knowledge-store update
```

For asset administration:

```text
DataAsset/DataTable object path + JSON request
  -> UCapabilityMeshAssetAdminSubsystem
  -> export/import/sync admin envelope
  -> optional Saved/UnrealCapabilityMesh/asset_admin file
  -> optional asset mutation when route policy allows it and approval is supplied
```

For configuration administration:

```text
Config/UnrealCapabilityMesh/config_targets/*.json
  -> UCapabilityMeshConfigAdminSubsystem
  -> whitelisted UObject config, UObject instance, or JSON file target
  -> read/write response through setup-declared routes
```

For MCP hosts:

```text
MCP tool call
  -> UCapabilityMeshMcpGatewaySubsystem
  -> reload/list/list-routes/configure-experimental-approval/dry-run/execute/invoke operation
  -> setup-declared Capability Mesh route or endpoint
```

Unified MCP Server can use `ListRoutesJson` to publish setup-declared routes as direct
`mesh_route_<sanitized_route_id>_<hash>` MCP tools. Those flattened tools still call
back into `DryRunRouteJson` or `ExecuteRouteJson`; they do not bypass route policy.
`ListRoutesJson` also returns route-derived `input_schema`, `output_schema`, and
`tool_annotations` so MCP hosts can expose real per-route parameters,
structured-result expectations, and risk hints.

For UCM-first product integration:

```text
Owning plugin JSON endpoint or file contract
  -> Config/UnrealCapabilityMesh capability + endpoint manifest
  -> UCM route policy and approval check
  -> optional MCP exposure through mesh_* tools
```

## Storage

UCM reads project setup from:

```text
Config/UnrealCapabilityMesh/
```

UCM writes diagnostics to:

```text
Saved/UnrealCapabilityMesh/
```

The plugin does not write into content folders by itself. Any content mutation must be performed by a declared endpoint and allowed by the route policy/rule set.

## Editor Control Panel

Open **Tools → Unreal Capability Mesh** for the dockable control panel (`SCapabilityMeshControlPanel`).

The **Routes** page includes a **Route Catalog** table that lists loaded routes grouped by owning plugin (from capability `display_name` / `provider_id`). Each row can expand to show route policy, steps, endpoints, side effects, and source manifest details. A dedicated right column hosts **EXPERIMENTAL** self automatic approval controls:

- **Approve all at own risk** in the column header for every approval-gated route
- Per-plugin toggles when a plugin owns approval-gated routes
- Per-route toggles for individual approval-gated routes
- `n/a` for routes that do not require approval

An orange warning above the catalog explains that self automatic approval injects `approval_granted=true` and can let asset or project mutation routes change editor state without a confirmation prompt. Policy blockers and dry-run requirements still apply.

## Safety Model

Capability manifests declare side-effect tags such as `read_only`, `saved_folder_write`, `project_config_write`, `asset_mutation`, `project_mutation`, `network`, and `ai_completion`. Route planning aggregates those tags and evaluates the active rule set before a route can be considered allowed.

Routes with asset or project mutation still require explicit approval. The route executor accepts `approval_granted: true`, `approvalGranted: true`, or `approval: "granted"` in the route input. Without approval the execution report stops at `ApprovalRequired`.

An explicit **EXPERIMENTAL** override exists for testing/local own-risk workflows: `experimental_self_approval_all_routes` and `experimental_self_approved_route_ids` in `project_profile.json`. The Route Catalog approval column on the Routes page and MCP tool `mesh_configure_experimental_self_approval` both manage those fields. When active, the service injects `approval_granted: true` only for allowed approval-gated route plans that did not already provide approval, and execution messages record the experimental self-approval. This is not intended for production use, does not allow blocked routes, and does not remove dry-run requirements.

`project_config_write` is intentionally separate from broad `project_mutation`. The default setup allows whitelisted config writes only with approval and dry-run planning, while broad project mutation remains blocked unless a project chooses a different rule set.

## Build Requirements

The plugin is C++ and uses Unreal Build Tool module rules. All UCM modules use `CppStandardVersion.Cpp20` and `BuildSettingsVersion.Latest`.

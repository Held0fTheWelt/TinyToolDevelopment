# Governed Automation

Asset Loader Studio is standalone-first. It does not depend on Unreal Capability Mesh or Unified MCP
Server at compile time. Optional UCM manifests are shipped under `Config/UnrealCapabilityMesh`.

Routes:

- `asset_loader_studio.tools.describe.v1`
- `asset_loader_studio.state.read.v1`
- `asset_loader_studio.load.submit.v1`
- `asset_loader_studio.jobs.status.v1`
- `asset_loader_studio.table.snapshot.v1`
- `asset_loader_studio.table.validate.v1`
- `asset_loader_studio.graph.build.v1`
- `asset_loader_studio.governance.snapshot.v1`
- `asset_loader_studio.governance.profile.save.v1`
- `asset_loader_studio.operation.preview.v1`
- `asset_loader_studio.operation.apply.v1`
- `asset_loader_studio.table.export.v1`
- `asset_loader_studio.audit.read.v1`
- `asset_loader_studio.audit.prune.v1`

Permission profiles:

- `read_only` allows read, inspect, validate, preview, and export.
- `guided_safe` allows staged edits with limits and confirmation.
- `expert` allows bulk and destructive capability flags, with strong approval for destructive work.

Every automation response uses a stable envelope with `success`, `operation`, `summary`,
`diagnostics`, `mutation_flags`, and route-specific payloads.

Automation is optional. If UCM or MCP is not installed, use the editor workspace, Blueprint library,
or runtime subsystem directly. Route callers should preview before apply and store the preview id or
approval token with their review record.

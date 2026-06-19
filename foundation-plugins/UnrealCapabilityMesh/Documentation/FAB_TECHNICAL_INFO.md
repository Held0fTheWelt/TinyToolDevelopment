# Fab Technical Information

Paste the block below into the Fab **Technical Details** field as-is. Maximum length: **1477 characters** (Fab field limit verified by filler test).

```text
Technical Details

Features
Setup-driven connector for Unreal Engine plugins.
JSON in Config/UnrealCapabilityMesh/: capabilities, endpoints, schemas, rules, routes, transforms, adapters.
Shared JSON binding context for cross-plugin input/output routing.
Invocation: reflection, subsystems, CDOs, file contracts, modular features.
Discovery: schema, plugin, and invocation checks.
Route planning: schema compatibility and side-effect tracking.
Rules: allow, approval required, dry-run, or block. Fast in-process execution.
Route Catalog with dry-run before execute; mutating routes require policy approval.
DataAsset/DataTable export/import/sync via JSON; whitelisted UObject/JSON config admin.
Optional MCP gateway. Editor: Tools -> Unreal Capability Mesh. Diagnostics: Saved/UnrealCapabilityMesh/.
No product-specific bridge logic in core. No bundled AI model, runtime, or executable.

Modules
UnrealCapabilityMesh, UnrealCapabilityMeshEditor, UnrealCapabilityMeshDeveloper

Blueprints
0

C++
Loader, registries, discovery, rule engine, planner/executor, transforms, invocation router, diagnostics, knowledge store, asset/config admin, optional MCP gateway, Slate panel.

Replication
Not replicated.

Platforms
Windows, Mac, Linux. Builds: Win64, Mac, Linux.

Documentation
https://github.com/Held0fTheWelt/TinyToolDevelopment/tree/master/foundation-plugins/UnrealCapabilityMesh

Included
README, CHANGELOG, docs, examples, fixtures.
```

Character count: 1434 / 1477.

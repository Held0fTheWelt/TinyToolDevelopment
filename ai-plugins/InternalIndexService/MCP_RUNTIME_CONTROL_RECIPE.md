# IIS Runtime Control — MCP Exposure Recipe (Non-Shipped)

This document describes how to expose the **shipped autark** IIS runtime control surface over MCP
using existing UCM + UMCP infrastructure. IIS itself has **zero UCM/UMCP dependency**; this is an
operator-side upsell layer.

## Prerequisites

- Internal Index Service (runtime module with `UIISControlEndpoints`)
- Unreal Capability Mesh (UCM)
- Unified MCP Server (UMCP) with `CapabilityMeshUmcpToolProvider`

## Manifest

Copy or merge the endpoint definitions from:

```text
Documentation/ai-plugins/InternalIndexService/ucm/iis_control_endpoints.json
```

into your project's UCM endpoint manifest (for example `Config/UnrealCapabilityMesh/endpoints/`).

Each endpoint reflects to `UIISControlEndpoints` on `/Script/InternalIndexService.IISControlEndpoints`
with `RequestJson` / `ResponseJson` parameters — the same shape as `UUmcpCapabilityMeshEndpoints`.

## Route ids

Declare matching UCM routes (one per tool), for example:

| Route id | Endpoint function | Gated |
| --- | --- | --- |
| `iis.control.state` | `State` | no |
| `iis.diagnostics.recent` | `DiagnosticsRecent` | no |
| `iis.perf.last` | `PerfLast` | no |
| `iis.control.tune` | `Tune` | yes |
| `iis.perf.run` | `PerfRun` | yes |
| `iis.index.sync` | `IndexSync` | yes |
| `iis.index.rebuild` | `IndexRebuild` | yes |
| `iis.index.import` | `IndexImport` | yes |
| `iis.control.persist` | `Persist` | yes |
| `iis.control.reset` | `Reset` | yes |

Mutating routes honor `UIISSettings::bEnableRuntimeControlMutations` (default on).

## UMCP

With routes registered in the project Capability Mesh profile, UMCP's existing
`CapabilityMeshUmcpToolProvider` surfaces them as MCP tools (`mesh_route_*` or `mesh_execute_route`).

## Standalone (no UCM/UMCP)

The same verbs are available without this recipe via:

- Editor console: `iis.control.state`, `iis.control.tune {"efSearch":128}`, …
- Blueprint: `UIISSubsystem::GetControlState`, `SetTuning`, …

See the shipped `UserManual.md` and `QUICKSTART.md` in the IIS plugin package.

## Reference

The standalone console and Blueprint surfaces are documented in the shipped IIS package docs:
`Documentation/UserManual.md` and `Documentation/QUICKSTART.md`.

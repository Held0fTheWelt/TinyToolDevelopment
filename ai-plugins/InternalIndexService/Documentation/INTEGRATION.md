# Integration Guide

## With Unreal Integration Intelligence

Unreal Integration Intelligence owns evidence extraction. IIS owns indexing and retrieval. The integration handoff is prepared chunk JSONL:

```text
UII extraction -> prepared chunks JSONL -> IIS import
```

IIS validates and imports the prepared records, then builds local retrieval artifacts.

## With LLM Store

IIS discovers embedding route executors at runtime through `FIISEmbeddingDiscovery` and `IModularFeatures` (`IIISEmbeddingRouteExecutor`). IIS consumers re-resolve the executor on each use; they do not cache executor pointers across module lifetimes.

In the current Tiny Tool Development stack, prefer UCM/LLM Store setup for cross-product routing when no direct executor is registered. When embedding capability is absent, IIS continues in degraded mode (`embedding_capability_unavailable` warnings) rather than crashing.

`FIISEmbeddingRouteExecutorRegistry` remains as a deprecated adapter for legacy `RegisterExecutor` callers. New bridge code should register `IIISEmbeddingRouteExecutor` in `StartupModule` and unregister in `ShutdownModule`:

```cpp
void FMyBridgeModule::StartupModule()
{
    IModularFeatures::Get().RegisterModularFeature(
        IIISEmbeddingRouteExecutor::GetModularFeatureName(),
        &EmbeddingExecutor);
}

void FMyBridgeModule::ShutdownModule()
{
    IModularFeatures::Get().UnregisterModularFeature(
        IIISEmbeddingRouteExecutor::GetModularFeatureName(),
        &EmbeddingExecutor);
}
```

This mirrors the Unified MCP Server `IUmcpToolProvider` registration pattern.

No-UCM direct-adapter flow:

```text
IIS embedding job / search query
        |
        v
FIISEmbeddingDiscovery::GetExecutor()
        |
        v
IModularFeatures (IIISEmbeddingRouteExecutor)
        |
        v
Optional direct executor (Freebie Bridge or custom adapter)
        |
        v
Provider/model/secret handling outside IIS
```

This keeps API keys and provider policy outside IIS.

## With Unified MCP Server

IIS does not host MCP directly and does not depend on Unified MCP Server at compile time. For
external agents, use:

- `UnifiedMcpServer` for loopback MCP transport
- `UnrealCapabilityMesh` plus project setup manifests for autonomous IIS agent routes

Each IIS agent operation is one read-only UCM route backed by `IISPythonBridge` agent helpers.
Unified MCP Server aggregates those routes as generic `mesh_route_*` tools. IIS itself stays
autonomous: enable or disable MCP access by changing project setup, not IIS code.

## Public Service API

Consumers should call `IInternalIndexService` through `FInternalIndexServiceModule`.

Common calls:

| Call | Purpose |
| --- | --- |
| `ImportPreparedChunksJsonl` | Import prepared evidence. |
| `Search` | Search indexed chunks. |
| `BuildContextPack` | Build a compact context pack. |
| `BuildEmbeddingJobs` | Queue embedding work. |
| `ExecuteEmbeddingJobs` | Execute queued embedding work through registered executor. |
| `ExecuteAgentTool` | Route one read-only agent request. |

## Agent Contract Files

`FIISAgentAccessService::WriteAgentToolContracts` writes JSON files under the IIS agent contracts directory. UCM routes and optional no-UCM provider bridges should read these contracts instead of duplicating tool descriptions.

## Safety Contract

IIS is retrieval-only. Integrations must not reinterpret IIS tool responses as permission to mutate project files. Agent responses include guardrail fields for this reason.

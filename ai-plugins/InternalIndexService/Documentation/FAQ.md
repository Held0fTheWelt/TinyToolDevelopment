# FAQ

## Does IIS modify my project?

No. IIS is retrieval-only. It writes generated index/report files, but it does not apply source, Blueprint, asset, or config mutations as an agent action.

## Does IIS include an MCP server?

No, not in current releases. MCP transport is provided by Unified MCP Server. IIS agent operations are exposed through project Capability Mesh routes, not an IIS-owned MCP server or bridge plugin.

## Where does data go?

By default:

```text
Saved/InternalIndexService
```

You can override the root in Project Settings.

## Does IIS send project data to the cloud?

Only if an embedding executor route in LLM Store uses a cloud provider. Search, catalog, import, and report files are local.

## Why are there no vector results?

Vector search requires embeddings. Build and execute embedding jobs after configuring an embedding route through LLM Store.

## What is hnswlib used for?

hnswlib powers the optional `hnsw` approximate nearest-neighbor vector backend. It is bundled as source under `Source/ThirdParty/hnswlib`.

## Why is my MCP tool list missing IIS tools?

Check that these plugins are enabled:

- Internal Index Service
- Unified MCP Server
- Unreal Capability Mesh

Ensure the project Capability Mesh profile lists IIS agent routes (`iis.agent.*.v1`), then write/refresh IIS agent contracts and call `mesh_reload_setup` or refresh the MCP client.

## Can I call IIS from C++?

Yes. Use `FInternalIndexServiceModule::Get().GetService()` and the `IInternalIndexService` interface.

## Can I call IIS from Blueprint?

IIS primarily exposes editor UI and C++ services. Agent-facing and integration paths are C++/JSON based.

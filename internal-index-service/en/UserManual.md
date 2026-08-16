<!-- doc-provenance: SAD architecture.md sections 1,5,6,8; facts product-facts.yml; reconciled 2026-07-16 -->
# User Manual

## Main Workflow

IIS follows a read-only retrieval workflow:

1. Import prepared evidence.
2. Build or refresh the local catalog.
3. Build embeddings when vector search is needed.
4. Search or build context packs.
5. Expose the same read-only tools to agents through UMCP.

IIS does not apply project mutations.

## Product Function Map

| Fact-sheet function | Buyer-facing surface |
| --- | --- |
| `ImportPreparedChunks` | Imports prepared chunk JSONL from the Control Panel Imports tab or service API. |
| `Search` | Runs lexical, vector, or hybrid retrieval from the Search tab and service API. |
| `BuildContextPack` | Builds evidence-focused context packs from a query or selected results. |
| `RunPerfSelfCheck` | Runs the shipped synthetic performance self-check from Blueprint/API and console surfaces. |
| `RuntimeControlDispatch` | Dispatches observe, tune, act, persist, and reset control verbs through the runtime control surface. |
| `AgentRetrievalTools` | Provides read-only agent retrieval operations through local contracts and optional UCM/UMCP routes. |

## Control Panel

Open:

```text
Tiny Tools -> AI -> Internal Index Service -> Open Internal Index Service
```

Tabs:

| Tab | Use |
| --- | --- |
| Dashboard | Index health, integration health, rebuild shortcut, search shortcut. |
| Index | Imports, catalog build, embedding job creation/execution. |
| Use | Search against local evidence. |
| Agents | Agent contracts and UMCP bridge status. |
| Governance | Retrieval-only posture, local paths, bridge and tool visibility. |
| Diagnostics | Reports, overview, and generated artifact locations. |
| Settings | In-panel view of `UIISSettings`. |

## Import Behavior

Import consumes prepared chunk JSONL. Each chunk carries IDs, content, source references, asset/symbol metadata, and lifecycle state. IIS validates input, appends accepted chunks, and writes import reports.

Important files:

```text
Saved/InternalIndexService/chunks.jsonl
Saved/InternalIndexService/imports/
Saved/InternalIndexService/reports/
```

## Catalog Build

Catalog build reads stored chunks and produces searchable local structures. It filters inactive chunk lifecycle states and writes a report so users can review warnings.

## Search

Search query fields include query text, search mode, max results, filters, and context-pack options. Results contain chunk IDs, score information, snippets, and source references.

Search modes:

| Mode | Meaning |
| --- | --- |
| Lexical | Uses local text matching over the chunk catalog. |
| Vector | Uses persisted embeddings and the configured vector backend. |
| Hybrid | Combines lexical and vector candidates. |

## Runtime Control Surface

IIS ships an **autark** runtime control surface for observe → tune → act without reloading the
editor. It mutates the live `UIISSettings` object in memory (transient by default) and re-applies
cached levers such as HNSW `efSearch` and the active int8 kernel immediately.

**No UCM or UMCP dependency** — the surface works from Blueprint, C++, and the editor console on
its own.

### Typed Blueprint API (`UIISSubsystem`)

| Method | Purpose |
| --- | --- |
| `GetControlState` | Snapshot of effective levers and mutation gate state. |
| `SetTuning` | Apply optional per-field tuning deltas (`FIISTuningRequest`). |
| `PersistTuning` | Write current overrides to config (`SaveConfig`). |
| `ResetTuning` | Reload config and revert transient overrides. |
| `RunPerfSelfCheck` | Run SYN-2 perf workloads against configured budgets. |

### Console commands

| Command | Purpose |
| --- | --- |
| `iis.control.state` | Print effective control state JSON. |
| `iis.control.tune {json}` | Transient tune (e.g. `{"efSearch":128}`). |
| `iis.control.persist` | Persist overrides to config. |
| `iis.control.reset` | Reload config / revert overrides. |
| `iis.control.diagnostics.recent` | Recent per-query diagnostics (when retention is on). |
| `iis.perf.run` / `iis.perf.last` | Run or read the last perf self-check. |
| `iis.index.sync` / `iis.index.rebuild` / `iis.index.import` | Index maintenance act-verbs. |

Mutating verbs honor **Enable Runtime Control Mutations** in project settings (default on).

## Embeddings

IIS does not own provider credentials. Embedding route resolution and execution are delegated through `FIISEmbeddingDiscovery` (`IIISEmbeddingRouteExecutor` via `IModularFeatures`), normally supplied by an LLM Store bridge that registers in `StartupModule` and unregisters in `ShutdownModule`.

The embedding flow:

1. Build jobs for chunks that need vectors.
2. Resolve an embedding route.
3. Execute jobs through the registered executor.
4. Persist vector records.
5. Update reports.

## Agent Tools

Agent tools are read-only and return structured JSON. IIS defines six autonomous retrieval
operations. Local contract names remain available for in-engine and JSON-file invocation:

| Local contract | UCM route id | Purpose |
| --- | --- | --- |
| `iis_search` | `iis.agent.search.v1` | Search indexed chunks (inline JSON payload plus artifact path). |
| `iis_get_context_pack` | `iis.agent.get_context_pack.v1` | Build a compact context pack from search results (inline JSON payload plus artifact path). |
| `iis_get_chunk` | `iis.agent.get_chunk.v1` | Fetch one chunk by ID. |
| `iis_get_source_references` | `iis.agent.get_source_references.v1` | Return source references for a chunk. |
| `iis_find_usages` | `iis.agent.find_usages.v1` | Look up usage records. |
| `iis_explain_blueprint` | `iis.agent.explain_blueprint.v1` | Summarize indexed Blueprint evidence (inline JSON payload plus artifact path). |

`iis.index.status.v1` additionally reports `catalog_exists`, `chunk_store_records`, and `vector_records` so agents can verify whether the index was populated without reading files.

MCP transport is owned by Unified MCP Server. IIS does not register MCP tools itself; the project
Capability Mesh setup declares one route per agent operation and UMCP publishes them as generic
`mesh_route_*` tools. No bridge plugin is required.

## Data And Privacy

IIS stores generated indexes in the project `Saved` folder by default. If a custom index root is set, use a local/private path unless your team intentionally shares generated evidence.

Cloud exposure only happens if an embedding executor route in LLM Store uses a cloud provider.

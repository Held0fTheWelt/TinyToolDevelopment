# User Manual

## Main Workflow

IIS follows a read-only retrieval workflow:

1. Import prepared evidence.
2. Build or refresh the local catalog.
3. Build embeddings when vector search is needed.
4. Search or build context packs.
5. Expose the same read-only tools to agents through UMCP.

IIS does not apply project mutations.

## Control Panel

Open:

```text
Tools -> AI -> Internal Index Service -> Open Internal Index Service
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

## Embeddings

IIS does not own provider credentials. Embedding route resolution and execution are delegated through `FIISEmbeddingRouteExecutorRegistry`, normally supplied by an LLM Store bridge.

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
| `iis_search` | `iis.agent.search.v1` | Search indexed chunks. |
| `iis_get_context_pack` | `iis.agent.get_context_pack.v1` | Build a compact context pack from search results. |
| `iis_get_chunk` | `iis.agent.get_chunk.v1` | Fetch one chunk by ID. |
| `iis_get_source_references` | `iis.agent.get_source_references.v1` | Return source references for a chunk. |
| `iis_find_usages` | `iis.agent.find_usages.v1` | Look up usage records. |
| `iis_explain_blueprint` | `iis.agent.explain_blueprint.v1` | Summarize indexed Blueprint evidence. |

MCP transport is owned by Unified MCP Server. IIS does not register MCP tools itself; the project
Capability Mesh setup declares one route per agent operation and UMCP publishes them as generic
`mesh_route_*` tools. No bridge plugin is required.

## Data And Privacy

IIS stores generated indexes in the project `Saved` folder by default. If a custom index root is set, use a local/private path unless your team intentionally shares generated evidence.

Cloud exposure only happens if an embedding executor route in LLM Store uses a cloud provider.

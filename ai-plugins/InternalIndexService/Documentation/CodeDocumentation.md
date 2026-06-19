# Code Documentation

This document is a source-reading guide for the IIS C++ code.

## Entry Points

| File | What To Read It For |
| --- | --- |
| `Source/InternalIndexService/Public/InternalIndexServiceModule.h` | Module singleton and access to the local service. |
| `Source/InternalIndexService/Private/InternalIndexServiceModule.cpp` | Startup/shutdown and service ownership. |
| `Source/InternalIndexServiceInterface/Public/IISServiceInterface.h` | Main service API consumed by editor, UCM endpoints, and optional bridge code. |
| `Source/InternalIndexService/Public/IISLocalIndexService.h` | Concrete service implementation surface. |

## Interface Module

The interface module is intentionally data-heavy. It keeps shared contracts free from editor dependencies.

| Header | Contents |
| --- | --- |
| `IISIndexTypes.h` | Chunks, lifecycle states, source metadata, catalog records. |
| `IISSearchTypes.h` | Search query, mode, result, response, filters. |
| `IISContextPackTypes.h` | Context pack sections and output format. |
| `IISImportTypes.h` | Prepared import files, records, reports. |
| `IISEmbeddingTypes.h` | Embedding routes, requests, jobs, reports, `FIISEmbeddingDiscovery`, deprecated registry adapter. |
| `IISAgentAccessTypes.h` | Agent tool request/response and tool kinds. |
| `IISUsageGraphTypes.h` | Usage graph records and query results. |
| `IISBlueprintExplanationTypes.h` | Blueprint explanation request/result structs. |

## Runtime Module

### `FIISLocalIndexService`

This is the main implementation of `IInternalIndexService`. It coordinates import, search, context packs, embeddings, and agent tools.

Typical call flow:

```text
Editor/UCM/optional bridge calls IInternalIndexService
        |
        v
FIISLocalIndexService validates request
        |
        v
Importer/catalog/vector/backend/helper service
        |
        v
Structured response + report path + warnings
```

### Import

`FIISPreparedChunkImporter` reads prepared JSONL, converts it to IIS chunk records, writes import manifests/reports, and appends valid chunks to the store.

### Catalog

`FIISChunkCatalog` owns chunk loading, lifecycle filtering, lexical search support, and report generation.

### Embeddings

`FIISEmbeddingJobQueue` builds and executes embedding jobs. It resolves executors through `FIISEmbeddingDiscovery::GetExecutor()` on each execution path, so IIS remains decoupled from concrete LLM providers. `FIISChunkCatalog` uses the same discovery seam for query embeddings during search.

`FIISEmbeddingJobStore` is the SQLite-backed persistence layer for embedding job rows and run records. JSONL remains an export/fallback artifact, not the only source of status truth.

### Vector Search

`IIISVectorIndexBackend` defines the backend interface. Implementations:

- `IISJsonlBruteForceBackend`
- `IISHnswVectorIndexBackend`

`IISVectorBackendFactory.cpp` selects the backend from settings.

`FIISVectorIndexService` coordinates persistent records and backend sync. Important implementation points:

- `IISVectorRecordUtil` fingerprints vector records so unchanged records are skipped during sync.
- Backend partitions include provider, model, dimensions, and route metadata.
- `IISHnswVectorIndexBackend` stores records in the configured HNSW vector storage policy, reuses deleted HNSW slots for updates, and compacts tombstones after sustained churn.
- Supported HNSW storage policies are `Int8PerVectorScale` (compact default), `Float32` (high-fidelity/debug), and gated `ExperimentalGlobalScale` (measurement-only because global int8 scaling can waste most levels on normalized high-dimensional embeddings).
- HNSW manifests include a storage format version and quantization id. Incompatible persisted layouts are rejected and, by default, deleted for rebuild from source vectors rather than read through the wrong distance space.
- HNSW binary persistence uses Unreal archive IO rather than narrow hnswlib file paths, keeping non-ASCII project paths safe on Windows.
- `IISJsonlBruteForceBackend` and HNSW both lock search/upsert/remove paths for concurrent editor operations.

### Agent Tools

`FIISAgentAccessService` maps `EIISAgentToolKind` to concrete operations:

- search
- get context pack
- get chunk
- get source references
- find usages
- explain Blueprint

It also writes tool contracts and serializes responses for external agents.

## Editor Module

| File | Role |
| --- | --- |
| `InternalIndexServiceEditorModule.cpp` | Editor module startup, menu registration, panel commands. |
| `IISToolMenuRegistration.cpp` | **Tools → AI → Internal Index Service** menu entries. |
| `SIISControlPanel.cpp` | Main Slate panel and tab grouping. |
| `SIISDashboard.cpp` | Dashboard work row and status cards. |
| `SIISGovernancePanel.cpp` | Retrieval-only, integration, and governance visibility. |
| `SIISSettingsPanel.cpp` | In-panel settings display and Project Settings shortcut. |
| `IISPanelStatus.cpp` | Status snapshot used by Dashboard/Governance. |
| `IISPythonBridge.cpp` | Editor-callable helper functions for automation. |

## Tests

Automation tests live beside implementation files and use `InternalIndexService.*` filters. They cover settings defaults, panel status, vector backends, agent access, usage graph, Blueprint explanation, embeddings, and editor UI invariants.

## Headers And Publication Comments

All IIS code files include a top comment with publisher `Tiny Tool Development` and intended publication year `2026`. Bundled hnswlib headers retain upstream licensing and include a separate bundle notice.

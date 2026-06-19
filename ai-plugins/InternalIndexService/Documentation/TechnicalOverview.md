# Technical Overview

## Module Layout

| Module | Type | Responsibility |
| --- | --- | --- |
| `InternalIndexServiceInterface` | Runtime | Public structs and service contracts for import, search, context, embeddings, usage graphs, Blueprint explanation, and agent access. |
| `InternalIndexService` | Runtime | Local service implementation, storage paths, catalog, import, search, vector backends, embedding queue, and agent tool execution. |
| `InternalIndexServiceEditor` | Editor | Control Panel, settings views, menu registration, status capture, and editor-facing Python bridge. |

## High-Level Data Flow

```text
Prepared evidence JSONL
        |
        v
ImportPreparedChunksJsonl
        |
        v
Chunk store + import reports
        |
        v
Build catalog / lifecycle filtering
        |
        +--> Lexical search
        |
        +--> Embedding job queue -> LLM Store route executor -> vector store
                                      |
                                      v
                              Vector / hybrid search
        |
        v
Context packs and read-only agent tool responses
```

## Storage

`FIISStoragePaths` centralizes generated paths. The default root is:

```text
Saved/InternalIndexService
```

`UIISSettings::IndexRoot` can override this. IIS stores generated data, reports, contracts, and vector artifacts under that root.

## Import

`FIISPreparedChunkImporter` validates prepared input files, converts prepared chunk JSON to `FIISIndexChunk`, appends accepted chunks to the store, and writes JSON/Markdown reports.

The importer is intentionally append/report oriented. It records warnings instead of silently discarding questionable input.

## Catalog And Search

`FIISChunkCatalog` manages chunk records and search helpers. `FIISLocalIndexService` uses it to answer `Search` and `BuildContextPack` calls.

Search responses are built from `FIISSearchQuery` and `FIISSearchResponse` structs in the interface module, so editor, runtime, UCM endpoints, and optional bridge code share the same contract.

## Vector Backends

The vector backend abstraction is `IIISVectorIndexBackend`.

Current backends:

| Backend | Notes |
| --- | --- |
| `jsonl_bruteforce` | Exact local backend for small indexes and debugging. It automatically hands larger indexes to HNSW once the configured brute-force record limit is exceeded. |
| `hnsw` | Uses bundled hnswlib for approximate nearest-neighbor search, configurable vector storage policy, incremental inserts, tombstone reuse, and partition compaction. |

`IISResolveConfiguredVectorBackendId()` reads `UIISSettings`. HNSW tuning is controlled by `HnswM`, `HnswEfConstruction`, and `HnswEfSearch`; higher values can improve recall at the cost of memory, build time, or query latency. HNSW storage is controlled by `VectorStorageFormat`: `Int8PerVectorScale` is the supported compact default, `Float32` is available for high-fidelity/debug runs, and `ExperimentalGlobalScale` is gated for measurement-only experiments. Incompatible vector-storage manifests are detected and rebuilt automatically by default.

`FIISVectorIndexService` owns the persistent vector lifecycle. It partitions vector records by provider, model, dimensions, and route, so queries only search compatible embeddings. Upserts and removals use `ChunkId` lookup maps and vector-record fingerprints to skip unchanged records; the sync key includes partition metadata so a route/model change cannot reuse stale vector data.

Both backends are guarded for concurrent editor use. HNSW uses a read/write lock and a read-only search path that never rebuilds or writes during query; the JSONL brute-force backend is locked for parity. HNSW index/manifest persistence uses temp-file plus move writes, and the binary index is saved/loaded through Unreal file IO so non-ASCII project paths remain safe. Normalization and cosine helpers use ISPC when available with a scalar fallback.

## Embedding Jobs

`FIISEmbeddingJobQueue` builds work items from chunks that need vector records. IIS does not own model credentials or provider setup. In the current stack, embedding execution should be routed through UCM/LLM Store setup where available. When a direct executor is present, `FIISEmbeddingDiscovery` resolves `IIISEmbeddingRouteExecutor` implementations from `IModularFeatures`; `FIISEmbeddingRouteExecutorRegistry` is a deprecated adapter for legacy registration helpers.

Embedding job status is persisted through a SQLite-backed job store when available, with JSONL export/fallback compatibility for older tooling. Small status updates no longer rewrite the whole JSONL file. Running jobs found after editor restart are recovered out of stale `running` state, and failed SQLite snapshot replacement invalidates the store so stale rows are not preferred over fresh JSONL data.

## Agent Access

`FIISAgentAccessService` converts agent requests into service operations. It also writes contracts consumed by UCM routes and, where needed, optional no-UCM bridge/provider tooling.

Agent responses include guardrails that state IIS is retrieval-only and does not permit project mutation.

## UMCP Integration

IIS no longer embeds its own MCP endpoint. The integration path is:

```text
IIS agent contracts -> project Capability Mesh routes -> Unified MCP Server
```

Each agent operation is one autonomous UCM route backed by `IISPythonBridge`. UMCP publishes them as generic `mesh_route_*` tools.

## Editor UI

`SIISControlPanel` hosts grouped workflow tabs. `IISCapturePanelStatus` gathers status snapshots. UI actions call the same service APIs used by tests, UCM endpoints, and optional bridge code.

## Third-Party Source

The `hnsw` backend includes hnswlib under:

```text
Source/ThirdParty/hnswlib
```

See `THIRD_PARTY_SOFTWARE.md`.

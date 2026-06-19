# Settings Reference

IIS settings are stored in `UIISSettings`.

Open:

```text
Edit -> Project Settings -> Plugins -> Internal Index Service
```

## Fields

| Setting | Default | Meaning |
| --- | --- | --- |
| Vector Backend | `jsonl_bruteforce` | Selects the local vector search backend. Supported values include `jsonl_bruteforce` and `hnsw`. With `jsonl_bruteforce`, IIS automatically switches to HNSW above the brute-force record limit below. |
| Index Root | empty | Optional override for generated IIS data. Empty uses `Saved/InternalIndexService`. |
| Brute Force Max Records | `10000` | At or below this record count, exact brute-force search is used; above it, HNSW. |
| Vector Storage Format | `Int8 Per-Vector Scale` | HNSW vector storage policy. `Int8 Per-Vector Scale` is the supported compact default; `Float32` is useful for high-fidelity/debug runs; `Experimental Global Scale` is gated and measurement-only. |
| Allow Experimental Vector Formats | `false` | Enables experimental HNSW storage formats. When disabled, experimental selections fall back to `Int8 Per-Vector Scale`. |
| Rebuild On Vector Format Mismatch | `true` | Deletes incompatible persisted HNSW partitions so they can be rebuilt from source vectors instead of being read with the wrong byte layout. |
| Quantization Recall Gate | `0.7` | Minimum recall target used by quantized vector-storage automation gates. Raise only after validating on representative project embeddings. |
| HNSW M | `16` | HNSW graph connectivity. Higher improves recall at the cost of memory and build time. Applies to newly built indices. |
| HNSW efConstruction | `200` | Build-time candidate list size. Higher improves graph quality and recall at the cost of build time. Applies to newly built indices. |
| HNSW efSearch | `64` | Query-time candidate list size. Higher improves recall at the cost of query latency. Applied on load and rebuild. |

> HNSW indices are stored using int8 scalar quantization by default (per-vector scaling), which keeps recall high while reducing index memory and on-disk size. Float32 is available as a high-fidelity/debug policy. Experimental global-scale int8 is intentionally gated because it can waste most int8 levels on normalized high-dimensional embeddings. Indices built with another storage policy are detected and rebuilt automatically by default.

## Generated Paths

Default root:

```text
Saved/InternalIndexService
```

Important generated areas:

| Path | Purpose |
| --- | --- |
| `chunks.jsonl` | Imported chunk store. |
| `imports/` | Import manifests and reports. |
| `reports/` | Catalog, embedding, and diagnostic reports. |
| `agent_contracts/` | Agent tool contracts and MCP manifest consumed by bridges. |
| `vectors/` or backend-specific files | Persisted embedding/vector data. |

Exact file names may vary by workflow and backend.

## MCP Settings

MCP server settings are not in IIS. Configure them under:

```text
Edit -> Project Settings -> Plugins -> Unified MCP Server
```

IIS agent access is published through project Capability Mesh routes such as `iis.agent.search.v1`.

## Secret Handling

IIS does not store provider secrets. Embedding provider credentials belong to LLM Store or the provider environment.

## Recommended Defaults

| Scenario | Vector Backend | Vector Storage Format | Experimental Formats | Index Root |
| --- | --- | --- | --- | --- |
| First setup | `jsonl_bruteforce` | `Int8 Per-Vector Scale` | disabled | empty |
| Larger local index | `hnsw` | `Int8 Per-Vector Scale` | disabled | empty or project-local custom path |
| High-fidelity debugging | `hnsw` | `Float32` | disabled | temporary workspace path |
| Recall experiment | `hnsw` | `Experimental Global Scale` | enabled | temporary workspace path |
| Shared CI validation | `jsonl_bruteforce` | `Int8 Per-Vector Scale` | disabled | temporary workspace path |

# Project Settings (`UIISSettings`)

IIS configuration lives in a standard Unreal **Developer Settings** class so teams can edit values in Project Settings instead of hand-editing `DefaultEngine.ini`.

**Path:** `Edit -> Project Settings -> Plugins -> Internal Index Service`

**Class:** `UIISSettings` (config = Engine, category Plugins)

## Fields

| Property | Config key | Default | Description |
| --- | --- | --- | --- |
| Vector Backend | `VectorBackend` | `jsonl_bruteforce` | Selects the vector index backend. Supported values include `jsonl_bruteforce` and `hnsw` (lowercased at resolve time). With the default router, IIS uses exact brute-force at or below the record threshold and HNSW above it. |
| Index Root (optional) | `IndexRoot` | *(empty)* | When set, overrides the on-disk index root. Empty uses `Saved/InternalIndexService`. |
| Brute Force Max Records | `BruteForceMaxRecords` | `10000` | Maximum record count for exact brute-force before the router uses HNSW. |
| Vector Storage Format | `VectorStorageFormat` | `Int8PerVectorScale` | Storage layout for HNSW vectors. `Int8PerVectorScale` is the supported compact default, `Float32` is for high-fidelity/debug runs, and `ExperimentalGlobalScale` is measurement-only. |
| Allow Experimental Vector Formats | `bAllowExperimentalVectorFormats` | `false` | Allows experimental HNSW storage layouts. When false, experimental selections fall back to `Int8PerVectorScale`. |
| Rebuild On Vector Format Mismatch | `bRebuildOnVectorFormatMismatch` | `true` | Deletes incompatible persisted HNSW partitions so they can be rebuilt from source vectors instead of read with the wrong byte layout. |
| Quantization Recall Gate | `QuantizationRecallGate` | `0.7` | Minimum recall target used by quantized-vector automation gates. Treat it as a CI guardrail, not as a guarantee for every project corpus. |
| HNSW M | `HnswM` | `16` | HNSW graph connectivity for newly built partitions. Higher can improve recall at the cost of memory/build time. |
| HNSW efConstruction | `HnswEfConstruction` | `200` | Build-time candidate list size for newly built HNSW partitions. |
| HNSW efSearch | `HnswEfSearch` | `64` | Query-time candidate list size applied when partitions load or rebuild. |
| Max Job History Count | `MaxJobHistoryCount` | `50` | Maximum recent editor jobs retained for panel history and UCM job endpoints. |

## Consumers

These read sites use `GetDefault<UIISSettings>()`:

- `IISResolveConfiguredVectorBackendId()` / `IISVectorBackendFactory`
- `FIISStoragePaths::GetDefaultIndexRoot()` (when `IndexRoot` is set)
- `FIISVectorIndexService` and HNSW partitions for brute-force/HNSW routing, HNSW tuning, vector storage policy, and format-mismatch rebuild behavior
- `UIISEditorJobsEndpoints` for editor job list/status limits

## MCP configuration

MCP server enable, port, and token are configured in the **Unified MCP Server** plugin settings (`UUmcpSettings`), not in IIS. External agent access uses **Capability Mesh** routes declared in project setup (`iis.agent.*.v1`). IIS has no compile-time dependency on UMCP or UCM.

## Secrets and index paths

API keys for cloud embedding providers remain in **LLM Store** secret storage, not in IIS settings.

Index root and artifact paths are managed by `FIISStoragePaths`, which reads `UIISSettings::IndexRoot` when non-empty.

Generated vector and job artifacts include backend-specific vector folders, HNSW partition manifests/binaries, embedding job reports, and the SQLite embedding job store with JSONL export/fallback data. HNSW manifests include a storage format version and quantization id so IIS can reject and rebuild incompatible persisted layouts.

## Migration note

Older builds stored MCP enable/port in `UIISSettings` or used a dedicated IIS UMCP bridge plugin. After upgrading, configure MCP in Project Settings → Plugins → Unified MCP Server and declare IIS agent routes in your Capability Mesh project profile.

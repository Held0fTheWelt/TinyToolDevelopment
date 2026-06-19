# Internal Index Service

Internal Index Service (IIS) is an Unreal Engine plugin for **local** indexing, retrieval, context packs, and agent-facing search. It is retrieval-only: it does not mutate project content or generate patches.

## Runtime Control (Autark)

The shipped runtime control surface (console + Blueprint API) is documented in `UserManual.md` and
`QUICKSTART.md`. For optional MCP exposure via UCM + UMCP (not shipped in the base plugin), see
[MCP_RUNTIME_CONTROL_RECIPE.md](MCP_RUNTIME_CONTROL_RECIPE.md).

## Modules

| Module | Purpose |
| --- | --- |
| `InternalIndexServiceInterface` | Public contracts for chunks, search, imports, embeddings, and agent access. |
| `InternalIndexService` | Runtime engine subsystem, chunk catalog, vector backends, embedding jobs, incremental indexing. |
| `InternalIndexServiceEditor` | Editor control panel, Python bridge, and Tools menu entries. |

## Open the Control Panel

```text
Tools -> AI -> Internal Index Service -> Open Internal Index Service
```

Or use the nomad tab **Internal Index Service** if your layout already shows it.

The panel is organized as:

| Tab | Purpose |
| --- | --- |
| **Dashboard** | Health cards for Index and Integrations; quick actions (Rebuild catalog). |
| **Overview** | Service version, index root, catalog/vector presence. |
| **Imports** | UII handoff and import report summaries. |
| **Catalog** | Build catalog and `catalog_build_report.json` summary. |
| **Embeddings** | Build and execute persisted embedding jobs through a discovered `IIISEmbeddingRouteExecutor`. |
| **Search** | Inline lexical / vector / hybrid search against the local index. |
| **Agent/MCP** | Agent contracts, UCM route ids, and MCP access guidance through Unified MCP Server. |
| **Reports** | Reports and logs folder shortcuts. |

The header shows the project name, a retrieval-only marker, a **Settings** button, and a **Refresh** button. Refresh updates all tab summaries, forces a Dashboard card update, and refreshes the Governance panel.

Dashboard cards are refreshed on open, by explicit **Refresh**, and after dashboard actions such as **Rebuild**. The panel does not rebuild cards on a periodic timer, which keeps the UI stable while editing or inspecting the panel.

## Project Settings

Configure IIS under:

```text
Edit -> Project Settings -> Plugins -> Internal Index Service
```

| Setting | Default | Meaning |
| --- | --- | --- |
| **Vector Backend** | `jsonl_bruteforce` | Local vector index implementation (`jsonl_bruteforce` or `hnsw`), with automatic brute-force/HNSW routing by record count. |
| **Index Root (optional)** | *(empty)* | Override for on-disk index root; empty uses `Saved/InternalIndexService`. |
| **Brute Force Max Records** | `10000` | Exact search threshold before HNSW is used. |
| **Vector Storage Format** | `Int8 Per-Vector Scale` | HNSW storage policy. Keep the compact per-vector int8 default for normal use; use `Float32` for high-fidelity/debug runs; use `Experimental Global Scale` only behind the experimental gate. |
| **Allow Experimental Vector Formats** | `false` | Enables measurement-only vector layouts that can reduce recall. |
| **Rebuild On Vector Format Mismatch** | `true` | Rebuilds incompatible persisted HNSW partitions instead of loading them with the wrong byte layout. |
| **Quantization Recall Gate** | `0.7` | Recall floor used by quantization automation tests; raise after representative project validation. |
| **HNSW M / efConstruction / efSearch** | `16` / `200` / `64` | HNSW recall, build-time, memory, and query-latency tuning. |

MCP access is provided by Unified MCP Server through project Capability Mesh routes. IIS no longer ships or requires a dedicated IIS UMCP bridge.

## Integrations

Embedding execution is delegated through `FIISEmbeddingDiscovery` (`IModularFeatures` / `IIISEmbeddingRouteExecutor`). Bridge plugins register in `StartupModule` and unregister in `ShutdownModule`. `FIISEmbeddingRouteExecutorRegistry` is a deprecated adapter for legacy callers.

The Dashboard **Integrations** card lists executor IDs from `FIISEmbeddingDiscovery::GetExecutorIds()` and whether each integration is active.

Editor job history is exposed through UCM routes (`iis.editor.jobs.list.v1`, `iis.editor.jobs.status.v1`) instead of a UMCP compile-time provider. The list route merges panel history with recent SQLite embedding job rows.

## For Maintainers (Not Required To Use The Plugin)

The IIS release validation gate (`Gates/iis_gate/`) lives in the development repository and is
**not** part of the Fab package. Buyers do not need it to install or use IIS. To use the plugin,
see [QUICKSTART.md](QUICKSTART.md).

## Related Documentation

| Document | Audience |
| --- | --- |
| [BUYER_GUIDE.md](BUYER_GUIDE.md) | Buyer-facing value, scope, and limits. |
| [QUICKSTART.md](QUICKSTART.md) | First setup, import, index build, and search. |
| [UserManual.md](UserManual.md) | Full editor workflow and operational behavior. |
| [CONTROL_PANEL.md](CONTROL_PANEL.md) | Editor panel workflows (dashboard, tabs, MCP). |
| [SETTINGS.md](SETTINGS.md) | `UIISSettings` fields and migration from manual config. |
| [SettingsReference.md](SettingsReference.md) | Settings, generated files, and storage paths. |
| [TechnicalOverview.md](TechnicalOverview.md) | Maintainer-level architecture and data flow. |
| [CodeDocumentation.md](CodeDocumentation.md) | C++ source map, core classes, and execution paths. |
| [INTEGRATION.md](INTEGRATION.md) | How UII, LLM Store, and UMCP bridge into IIS. |
| [FAQ.md](FAQ.md) | Common buyer and reviewer questions. |
| [TROUBLESHOOTING.md](TROUBLESHOOTING.md) | Common failures and fixes. |
| [ReleaseChecklist.md](ReleaseChecklist.md) | Build, packaging, documentation, and Fab checks. |
| [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md) | Third-party source declaration details for Fab submission. |
| [IIS_Readme.txt](IIS_Readme.txt) | Short packaged readme for quick inspection. |
| [../CHANGELOG.md](../CHANGELOG.md) | Release notes. |

## Packaging

Ensure `Config/FilterPlugin.ini` includes `/Documentation/...` so buyers receive this folder in Fab builds. Release validation gates live in the repo-level `Gates/` folder and are not shipped with the plugin.

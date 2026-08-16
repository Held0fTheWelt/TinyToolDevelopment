<!-- doc-provenance: SAD architecture.md sections 1,3,6,7,8; facts product-facts.yml; reconciled 2026-07-16 -->
# Quick Start

## 1. Enable The Plugin

Enable `Internal Index Service` in the Plugins browser. Restart the editor if Unreal requests it.

## 2. Open The Control Panel

Use:

```text
Tiny Tools -> AI -> Internal Index Service -> Open Internal Index Service
```

The Control Panel opens on the Dashboard.

## 3. Configure Settings

Open:

```text
Edit -> Project Settings -> Plugins -> Internal Index Service
```

Recommended first setup:

| Setting | Value |
| --- | --- |
| Vector Backend | `jsonl_bruteforce` |
| Vector Storage Format | `Int8 Per-Vector Scale` |
| Allow Experimental Vector Formats | `false` |
| Index Root | empty |

Empty `Index Root` means IIS uses:

```text
Saved/InternalIndexService
```

The default storage policy uses per-vector int8 scaling for HNSW partitions. It is the normal
compact mode. `Float32` is available for high-fidelity/debug runs; `Experimental Global Scale`
should stay disabled unless you are deliberately measuring recall trade-offs.

## 4. Import Prepared Chunks

Use the Control Panel Imports tab or call the service API with a prepared chunks JSONL file. Prepared chunks normally come from a companion extraction pipeline such as Unreal Integration Intelligence.

The import writes reports under the IIS saved folder and updates the chunk store.

## 5. Build The Catalog

Use the Dashboard **Rebuild** action or the Catalog tab. IIS reads imported chunks, normalizes lifecycle state, and writes a catalog build report.

## 6. Search

Use the Search tab:

- lexical search works from the local catalog
- vector search requires embeddings
- hybrid search combines both when vectors exist

## 7. Build Embeddings (Optional — adds vector search, requires LLM Store)

Lexical search (steps 1–6) works on its own with no other plugin. Vector and hybrid search are an
optional enhancement: configure the **LLM Store** plugin first, then IIS asks the embedding
executor registry for a route, creates jobs, and writes embedding reports. Execute jobs from the
Embeddings tab. Without LLM Store, IIS still imports, builds, and searches lexically.

## 8. Expose Agent Tools (Optional — requires Unified MCP Server + Capability Mesh)

This step is optional and only needed if you want AI agents to call IIS. Install and enable:

- Unified MCP Server
- Unreal Capability Mesh

Ensure the project Capability Mesh profile includes the IIS agent routes (for example
`iis.agent.search.v1`). Then start Unified MCP Server. Each IIS agent capability is exposed as
its own autonomous UCM route, flattened to a `mesh_route_*` MCP tool, such as:

```text
mesh_route_iis_agent_search_v1_<hash>
mesh_route_iis_agent_get_context_pack_v1_<hash>
mesh_route_iis_agent_get_chunk_v1_<hash>
mesh_route_iis_agent_get_source_references_v1_<hash>
mesh_route_iis_agent_find_usages_v1_<hash>
mesh_route_iis_agent_explain_blueprint_v1_<hash>
```

Alternatively call `mesh_execute_route` with `route_id` set to the route id (for example
`iis.agent.search.v1`).

## 9. Runtime Tune (Optional - no extra plugins)

The shipped runtime control surface is **autark**: no UCM or UMCP required.

Open the editor output log console and run:

```text
iis.control.state
```

Example response excerpt (default `efSearch` is 64):

```json
{"ok":true,"errorCode":"","errorMessage":"","efSearch":64,...}
```

Raise query-time `efSearch` live:

```text
iis.control.tune {"efSearch":128}
```

Confirm the change:

```text
iis.control.state
```

Example after tune:

```json
{"ok":true,"errorCode":"","errorMessage":"","efSearch":128,...}
```

Overrides are **transient** until you run `iis.control.persist`. Use `iis.control.reset` to reload
from config. See `UserManual.md` for the full console command list and Blueprint API.

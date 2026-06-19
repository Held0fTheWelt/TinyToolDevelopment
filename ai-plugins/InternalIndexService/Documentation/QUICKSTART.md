# Quick Start

## 1. Enable The Plugin

Enable `Internal Index Service` in the Plugins browser. Restart the editor if Unreal requests it.

## 2. Open The Control Panel

Use:

```text
Tools -> AI -> Internal Index Service -> Open Internal Index Service
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

## 9. Validate (Optional)

The plugin ships an optional validation helper that checks agent contract files and can optionally
check a live MCP endpoint:

```text
Tools/mvp_e_validation/validate_iis_mvp_e.py
```

This step is optional and requires Python 3 installed on your machine. It is not needed to import,
build, or search — those work entirely inside the editor (steps 1–6).

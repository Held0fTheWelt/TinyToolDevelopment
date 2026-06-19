# Control Panel

The IIS Control Panel is the primary operator surface for indexing, search, embeddings, agent tools, governance, and diagnostics.

Open it from **Tools → AI → Internal Index Service → Open Internal Index Service**.

## Header

- **Title**, **project name**, and **retrieval-only marker** — reminds operators that IIS does not apply project mutations.
- **Settings** — jumps to the in-panel Settings tab.
- **Refresh** — reloads tab bodies, forces a Dashboard card update, and refreshes the Governance panel from a fresh `IISCapturePanelStatus()` snapshot.

Dashboard cards are refreshed on open, by explicit **Refresh**, and after dashboard actions such as **Rebuild**. The panel does not rebuild cards on a periodic timer, so volatile counters do not cause visible card flicker.

## Tabs

| Tab | Content |
| --- | --- |
| Dashboard | Health cards (Index, Integrations) plus work shortcuts (Import, quick Search, Data & Privacy). |
| Index | Imports, Catalog, Embeddings (scrollable). |
| Use | Search (lexical / vector / hybrid). |
| Agents | Agent contracts, MCP tool manifest, UCM route ids for external agents. |
| Governance | Retrieval-only guarantee, MCP security (via Unified MCP Server), data locality, bridge health, agent tool transparency. |
| Diagnostics | Overview and Reports (scrollable). |
| Settings | In-panel `UIISSettings` details view and link to Project Settings. |

Tab buttons use **active-state** styling (highlighted tab vs dimmed siblings).

## Dashboard

### Health row

- **Index** — catalog/vector presence, chunk count; **Rebuild** runs `BuildChunkCatalogWithWarnings`.
- **Integrations** — embedding executors from `FIISEmbeddingDiscovery::GetExecutorIds()`.

### Work row

- **Import** — **Go to Imports** switches to the Index tab.
- **Search** — inline query + **Go** runs search on the Use tab.
- **Data & Privacy** — **Open folder** opens the index root.

## Governance

Read-only display of mutation flags (default `FIISAgentToolResponse`), Unified MCP Server posture, index paths, bridge/executor registration (including LLM Store bridge load hints), and exposed MCP tool names. Actions: write/refresh agent contracts, open agent folder.

## MCP access

MCP server lifecycle (start/stop, token rotation) is handled by the **Unified MCP Server** plugin (**Tools → AI → Universal MCP**). IIS agent access for external clients is provided by autonomous **Capability Mesh** routes (`iis.agent.*.v1`) published as `mesh_route_*` MCP tools. IIS itself has no compile-time dependency on UMCP or UCM.

Editor job visibility follows the same autark pattern. IIS exposes read-only UCM endpoints for `iis.editor.jobs.list.v1` and `iis.editor.jobs.status.v1`; the list endpoint merges panel job history with recent SQLite embedding-job rows. UMCP can aggregate these through its `jobs_list` / `jobs_status` tools when UCM is enabled, but IIS does not register a direct UMCP job provider.

## Tools menu

**Tools → AI → Internal Index Service** submenu:

- Open Internal Index Service
- Quick Actions: Build Index, Open Index Folder

Legacy flat menu entries were removed; full workflows live in the panel tabs.

## Automation

Filter: `InternalIndexService.Editor` (panel, dashboard, governance, settings, retrieval-only invariant, panel status).

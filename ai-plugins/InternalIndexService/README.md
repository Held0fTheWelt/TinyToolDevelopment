# Internal Index Service

> Not a verbatim copy of shipped docs. This online page is an overview and routing surface; shipped buyer docs stay in the plugin package.

Internal Index Service (IIS) is a local, editor-based indexing, retrieval, and context-pack service
for Unreal Engine projects. It imports prepared evidence chunks, builds a searchable catalog, and
answers lexical, vector, and hybrid searches entirely on your machine, with no cloud service required.

It also exposes agent retrieval through **Capability Mesh routes** on the **Unified MCP Server** plugin
(for example `iis.agent.search.v1`), and can delegate embedding generation to the **LLM Store** plugin
when you want vector search.

## Get It / Routing

- Fab: https://www.fab.com/listings/9dfa7b61-cf4e-476b-8edc-253c7c5585e9
- Package docs: shipped inside the plugin package as `Documentation/QUICKSTART.md`,
  `Documentation/UserManual.md`, `Documentation/SettingsReference.md`,
  `Documentation/TROUBLESHOOTING.md`, `Documentation/FAQ.md`, and
  `Documentation/THIRD_PARTY_SOFTWARE.md`.
- Category: AI Plugins

## Synergies & Bridges

- **LLM Store** can provide embedding route executors for vector and hybrid search.
- **Unreal Capability Mesh** plus **Unified MCP Server** can expose IIS agent retrieval routes to local MCP clients.
- [IIS Runtime Control MCP Exposure Recipe](MCP_RUNTIME_CONTROL_RECIPE.md) describes the optional UCM/UMCP route layer for the shipped runtime control surface.

## Third-Party Software

IIS bundles the header-only **hnswlib** (Apache-2.0) for local vector search. No cloud account, Python
runtime, or external executable is required to install and use IIS.

## Media

Product slides, screenshots, and video assets are maintained by the Product Presentation region.

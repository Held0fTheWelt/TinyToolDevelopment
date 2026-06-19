# Internal Index Service

Internal Index Service (IIS) is a local, editor-based indexing, retrieval, and context-pack
service for Unreal Engine projects. It imports prepared evidence chunks, builds a searchable
catalog, and answers lexical, vector, and hybrid searches — entirely on your machine, with no
cloud service required.

It also exposes agent retrieval through **Capability Mesh routes** on the **Unified MCP
Server** plugin (for example `iis.agent.search.v1`), and can delegate embedding generation to the **LLM Store** plugin when you want
vector search.

## Quick Start

1. Enable **Internal Index Service** in *Edit → Plugins* and restart the editor.
2. Open **Tools → AI → Internal Index Service → Open Internal Index Service**.
3. In *Edit → Project Settings → Plugins → Internal Index Service*, set **Vector Backend** to
   `jsonl_bruteforce`, leave **Vector Storage Format** at `Int8 Per-Vector Scale`, and leave **Index Root** empty (defaults to `Saved/InternalIndexService`).
4. Import prepared chunks, rebuild the catalog, and search from the Control Panel.

Full walkthrough with expected results: [Documentation/QUICKSTART.md](Documentation/QUICKSTART.md).

## Documentation

All buyer and technical docs are in [Documentation/](Documentation/README.md):
Buyer Guide, Quick Start, User Manual, Control Panel, Settings Reference, Integration,
Troubleshooting, FAQ, and the third-party software declaration.

## Third-Party Software

IIS bundles the header-only **hnswlib** (Apache-2.0) for local vector search. See
[Documentation/THIRD_PARTY_SOFTWARE.md](Documentation/THIRD_PARTY_SOFTWARE.md). No cloud account,
Python runtime, or external executable is required to install and use IIS.

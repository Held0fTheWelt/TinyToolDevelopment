# Unreal Integration Intelligence

> Not a verbatim copy of shipped docs. This online page is an overview and routing surface; shipped buyer docs stay in the plugin package.

Unreal Integration Intelligence (UII) is in publishment for version 1.0.0. It prepares Unreal project evidence, System Dossiers, review packs, RAG-ready chunks, and bridge-ready handoff contracts for migration, integration review, project understanding, and downstream tooling.

UII is evidence infrastructure. It validates project profiles, exports structured project evidence, and helps other tools consume reviewed handoff artifacts. In the current stack, UCM is the preferred way to route UII evidence into IIS, PRS, Smart Content Diet, UCI, BPJ, PIO, or agent-facing workflows. Freebie Bridges remain available only for no-UCM projects and as direct-adapter examples.

## What It Does

- Exports project evidence for review and downstream tooling.
- Builds asset, module, C++ symbol, reflection, network, source, and Blueprint-oriented analysis artifacts.
- Builds System Dossiers with subsystem clustering, C++ context, data/animation evidence, port-readiness bands, and confidence factors.
- Produces review packs, RAG-oriented packages, and handoff contracts for retrieval, planning, reporting, and bridge workflows.
- Keeps retrieval, embeddings, model routes, provider secrets, planning authority, and project mutation outside UII.

## Product Boundary

UII does not replace IIS as the local retrieval/index layer, PRS as the gated restructure executor, LLM Store as the provider-policy owner, or UCI/PIO as reviewed planning/orchestration owners. UII describes and prepares the project; downstream tools decide how to index, plan, report, or execute.

## UCM Integration And Optional No-UCM Bridges

Normal UII ecosystem workflows should be declared through UCM capabilities, endpoints, and routes. UCM keeps handoff routing, policy, route visibility, and optional MCP exposure in one setup layer while UII remains the evidence producer.

The Freebie Bridges below are retained for teams that do not use UCM and as reference implementations for direct adapters.

| Bridge | Connects | Purpose |
| --- | --- | --- |
| [UII Internal Index Service Bridge](../../bridge-plugins/UIIInternalIndexServiceBridge/README.md) | Unreal Integration Intelligence + Internal Index Service | No-UCM/reference adapter that docks UII handoff contracts into IIS import, catalog, retrieval, context-pack, embedding, and agent workflows. |
| [SmartContentDiet UII Migration Bridge](../../bridge-plugins/SmartContentDietUIIMigrationBridge/README.md) | Smart Content Diet + Unreal Integration Intelligence | No-UCM/reference adapter that translates UII migration handoff artifacts into advisory SCD migration findings. |

## Product Media

Product images are available under [Media](Media/). The current generated set is fact-bound and marked internally as needing real Slot 01/02 Unreal Editor captures before any live Fab gallery claim.

## Status

- Category: AI Plugins
- Version: 1.0.0
- Status: In Publishment
- Fab: In publishment; not live until Fab shows the listing as Live
- Current focus: package-real evidence export, System Dossier review packs, RAG packages, and bridge-ready handoff contracts

## Support

For questions, setup help, and product support:

https://discord.gg/HycgjVkK4J

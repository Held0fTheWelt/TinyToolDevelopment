# Unreal Integration Intelligence

> Not a verbatim copy of shipped docs. This online page is an overview and routing surface; shipped buyer docs stay in the plugin package.

Unreal Integration Intelligence (UII) is an Unreal Engine project analysis and integration-intelligence plugin for evidence export, migration planning, architecture review, and tool handoff workflows.

UII prepares structured project evidence that other tools can consume. In the current stack, UCM is the preferred way to route UII evidence into IIS, PRS, Smart Content Diet, or agent-facing workflows. Freebie Bridges remain available only for no-UCM projects and as direct-adapter examples.

## What It Does

- Exports project evidence for review and downstream tooling.
- Builds asset, module, C++ symbol, reflection, network, and Blueprint-oriented analysis artifacts.
- Supports migration planning and integration review workflows.
- Produces handoff contracts and RAG-oriented packages for retrieval systems.
- Helps prepare structured evidence for IIS and future AI-assisted development workflows.

## Product Boundary

UII is evidence and planning infrastructure. It does not replace IIS as the local retrieval/index layer, and it does not replace PRS as the gated restructure executor. In the TinyToolDevelopment stack, UII helps describe and prepare the project; IIS retrieves and contextualizes; PRS applies reviewed restructure actions.

## UCM Integration And Optional No-UCM Bridges

Normal UII ecosystem workflows should be declared through UCM capabilities, endpoints, and routes. UCM keeps handoff routing, policy, route visibility, and optional MCP exposure in one setup layer while UII remains the evidence producer.

The Freebie Bridges below are retained for teams that do not use UCM and as reference implementations for direct adapters.

| Bridge | Connects | Purpose |
| --- | --- | --- |
| [UII Internal Index Service Bridge](../../bridge-plugins/UIIInternalIndexServiceBridge/README.md) | Unreal Integration Intelligence + Internal Index Service | No-UCM/reference adapter that docks UII handoff contracts into IIS import, catalog, retrieval, context-pack, embedding, and agent workflows. |
| [SmartContentDiet UII Migration Bridge](../../bridge-plugins/SmartContentDietUIIMigrationBridge/README.md) | Smart Content Diet + Unreal Integration Intelligence | No-UCM/reference adapter that translates UII migration handoff artifacts into advisory SCD migration findings. |

## Status

- Category: AI Plugins
- Status: Advanced Preview
- Fab: Not listed yet
- Current focus: evidence export, analysis artifacts, planning packages, and bridge-ready contracts

## Support

For questions, setup help, and product support:

https://discord.gg/HycgjVkK4J

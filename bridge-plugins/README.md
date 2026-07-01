# Example Projects

This category contains optional free companion example projects for teams that do not own or do not enable **Unreal Capability Mesh (UCM)**, plus reference implementations that show how direct adapters should be shaped.

UCM is the primary integration layer for the current Tiny Tool Development stack. Normal cross-product workflows should be declared as UCM capabilities, endpoints, routes, rules, transforms, and adapters, then exposed through Unified MCP Server when agent access is needed.

Example Projects do not replace UCM and do not replace the products they connect. They keep responsibilities clear: each core plugin continues to own its own data, settings, governance, and runtime behavior.

These entries are listed here even when their full buyer-facing documentation is still being expanded. That makes no-UCM fallback integrations discoverable, provides examples for custom direct adapters, and keeps product boundaries visible from the repository start page. They are parked outside the active Fab publication framework until the Example Projects track is fully integrated.

## Companion Bridges

| Bridge Plugin | Connects | Description | Start Here |
| --- | --- | --- | --- |
| IIS LLM Store Bridge | Internal Index Service + LLM Store | No-UCM/reference adapter for IIS embedding jobs through LLM Store embedding routes. | [Overview](InternalIndexServiceLLMStoreBridge/README.md) |
| SmartContentDiet IIS Similarity Bridge | Smart Content Diet + Internal Index Service | No-UCM/reference adapter for SCD semantic similarity backed by IIS and SCD health-evidence JSONL import. | [Overview](SmartContentDietIISSimilarityBridge/README.md) |
| SmartContentDiet PRS Bridge | Smart Content Diet + Project Restructure Service | No-UCM/reference adapter for reviewed SCD placement moves into PRS validation, dry-run, apply, and rollback APIs. | [Overview](SmartContentDietPRSBridge/README.md) |
| SmartContentDiet UII Migration Bridge | Smart Content Diet + Unreal Integration Intelligence | No-UCM/reference adapter for translating UII handoff artifacts into advisory SCD migration findings. | [Overview](SmartContentDietUIIMigrationBridge/README.md) |
| UII Internal Index Service Bridge | Unreal Integration Intelligence + Internal Index Service | No-UCM/reference adapter for docking UII handoff contracts into IIS evidence, catalog, retrieval, context-pack, embedding-job, and agent workflows. | [Overview](UIIInternalIndexServiceBridge/README.md) |

## Support

For setup help and product support:

https://discord.gg/HycgjVkK4J

# AI Plugins

This category contains plugins focused on AI infrastructure, model routing, provider governance, secrets, costs, and agent-facing workflows.

## Products

| Product | Description | Start Here | Fab |
| --- | --- | --- | --- |
| Asset Plugin Maker | In-publishment asset distillation, target-plugin builds, provenance, BOMs, validation reports, and release candidate evidence for Unreal Engine content plugins. | [Overview](AssetPluginMaker/README.md) | Not listed yet |
| Internal Index Service | Local indexing, retrieval, context packs, embedding jobs, and agent-facing search for Unreal Engine projects. | [Overview](InternalIndexService/README.md) | [Fab product](https://www.fab.com/listings/9dfa7b61-cf4e-476b-8edc-253c7c5585e9) |
| LLM Store | Central management for AI providers, models, routes, policies, costs, secrets, and optional agents inside Unreal Engine. | [Overview](LLMStore/README.md) | [Fab product](https://www.fab.com/listings/4e9c6062-e3e7-4113-93d1-f08d6e276020) |
| Project Restructure Service | Safe, gated project restructuring and placement executor. PRS can consume IIS evidence, but IIS remains read-only. | [Overview](ProjectRestructureService/README.md) | Not listed yet |
| Unified MCP Server | Marketplace-available editor-only loopback MCP host with provider registry, bearer-token handshake, UCM route exposure, and optional provider-tool aggregation. | [Overview](UnifiedMcpServer/README.md) | [Fab product](https://www.fab.com/listings/f5ded18c-38b5-4e12-88cb-120f484e282f) |
| Unreal Integration Intelligence | Project analysis, evidence export, migration planning, integration intelligence, and IIS handoff preparation. | [Overview](UnrealIntegrationIntelligence/README.md) | Not listed yet |

## Notes

Unreal Capability Mesh (UCM) is the preferred cross-product integration layer for the Tiny Tool Development AI stack. Optional Freebie Bridges are fallback/reference plugins for no-UCM projects, not the normal connection model.

AI infrastructure plugins share the **Tools -> AI** section in the editor where applicable. Asset Plugin Maker uses `Tiny Tools -> Asset Tools -> Asset Plugin Maker`; Unified MCP Server exposes lifecycle actions under **Universal MCP**; Internal Index Service, Unreal Integration Intelligence, and Project Restructure Service register alongside it. See [Editor menu layout](../EDITOR_MENUS.md).

The product folders in this category are online overview and routing entries. Package-specific buyer
docs stay with the shipped plugins unless a product page links to a curated public copy.

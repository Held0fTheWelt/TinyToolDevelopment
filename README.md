# Tiny Tool Development - Documentation Showcase

This repository is the public documentation showcase for Tiny Tool Development. It collects product-facing documentation, Unreal Capability Mesh (UCM) setup patterns, release notes, media assets, optional free bridge examples, and shared documentation conventions for the Tiny Tool Unreal Engine tool family.

It is not an Unreal Engine project and it is not the source-of-truth implementation repository for the products themselves. The folders are organized for browsing, product discovery, buyer-facing documentation, integration examples, and public reference material. Detailed documentation lives inside each product folder, usually under `Documentation/`.

## Repository Scope

This repository should contain:

- product landing pages and documentation indexes;
- buyer guides, quickstarts, user manuals, settings references, troubleshooting notes, changelogs, and release checklists;
- UCM setup and bridge documentation;
- optional free bridge plugin reference code where it is useful for no-UCM projects;
- product media and public documentation assets.

This repository should not contain private credentials, local machine state, generated Unreal build folders, local runtime databases, dependency trees, unpublished internal planning data, or temporary inspection output.

## Product Categories

| Category | Folder | Purpose |
| --- | --- | --- |
| AI Plugins | [ai-plugins](ai-plugins/README.md) | AI infrastructure, provider routing, model governance, and agent-facing systems. |
| Foundation Plugins | [foundation-plugins](foundation-plugins/README.md) | Cross-product interoperability, capability routing, setup manifests, and shared integration surfaces. |
| Engine Plugins | [engine-plugins](engine-plugins/README.md) | Engine-level infrastructure plugins, protocol hosts, shared runtime/editor contracts, UCM, and extensibility surfaces. |
| Scene Tools | [scene-tools](scene-tools/README.md) | World, spline, track, environment, and scene-authoring tools. |
| Editor Tools | [editor-tools](editor-tools/README.md) | Governance, documentation health, diagnostics, asset quality, rendering review, validation, naming, logging, performance, and workflow tools for Unreal Editor. |
| Freebie Bridge Plugins | [bridge-plugins](bridge-plugins/README.md) | Optional no-UCM fallback and reference plugins that show how direct adapters should be built. |

## Main Products

| Product | Category | Description | Start Here | Fab |
| --- | --- | --- | --- | --- |
| Internal Index Service | AI Plugins | Local indexing, retrieval, context packs, embedding jobs, and agent-facing search for Unreal Engine projects. | [Overview](ai-plugins/InternalIndexService/README.md) | [Fab product](https://www.fab.com/listings/9dfa7b61-cf4e-476b-8edc-253c7c5585e9) |
| LLM Store | AI Plugins | Central management for AI providers, models, routes, policies, costs, secrets, and optional agents inside Unreal Engine. | [Overview](ai-plugins/LLMStore/README.md) | [Fab product](https://www.fab.com/listings/4e9c6062-e3e7-4113-93d1-f08d6e276020) |
| Asset Plugin Maker | AI Plugins | In-publishment asset distillation, target-plugin builds, provenance, BOMs, validation reports, and release candidate evidence for Unreal Engine content plugins. | [Overview](ai-plugins/AssetPluginMaker/README.md) | Not listed yet |
| Project Restructure Service | AI Plugins | Safe, gated project restructuring and placement executor that can consume IIS evidence while keeping IIS itself read-only. | [Overview](ai-plugins/ProjectRestructureService/README.md) | Not listed yet |
| Unified MCP Server | AI Plugins | Marketplace-available editor-only loopback MCP host with provider registry, bearer-token handshake, UCM route exposure, and optional provider-tool aggregation. | [Overview](ai-plugins/UnifiedMcpServer/README.md) | [Fab product](https://www.fab.com/listings/f5ded18c-38b5-4e12-88cb-120f484e282f) |
| Unreal Integration Intelligence | AI Plugins | Project evidence export, migration planning, integration analysis, and handoff tooling for Unreal Engine projects. | [Overview](ai-plugins/UnrealIntegrationIntelligence/README.md) | Not listed yet |
| Unreal Capability Mesh | Foundation Plugins | Published setup-driven interoperability hub for Unreal Engine plugins, with capability manifests, route planning, policy checks, editor job routes, and optional MCP gateway support. | [Overview](foundation-plugins/UnrealCapabilityMesh/README.md) | [Fab product](https://www.fab.com/listings/fd186d26-cdcf-4c4f-93d4-50e437b7673e) |
| Async Spline Builder | Scene Tools | Builds roads, tracks, pipes, rails, walls, and side objects along splines, including async builds, segment planning, and landscape support. | [Overview](scene-tools/AsyncSplineBuilder/README.md) | [Fab product](https://www.fab.com/listings/41f15640-e169-490c-9edf-bd3255699043) |
| Code Copyright Editor | Editor Tools | Keeps Unreal Engine source copyright headers, project notices, metadata, and CI checks consistent. | [Overview](editor-tools/CodeCopyrightEditor/README.md) | [Fab product](https://www.fab.com/listings/e30d9b22-9c8b-41ff-8887-d2cce63a119f) |
| Lightweight Editor Mode | Editor Tools | Temporarily reduces Unreal Editor viewport and rendering cost through reversible performance profiles. | [Overview](editor-tools/LightweightEditorMode/README.md) | [Fab product](https://www.fab.com/listings/94911975-ec7d-4d7c-8408-04bc647eb373) |
| LogLevelEditor | Editor Tools | Discovers Unreal log categories and changes verbosity levels from a focused editor dashboard. | [Overview](editor-tools/LogLevelEditor/README.md) | [Fab product](https://www.fab.com/listings/e9d934de-0432-452d-b899-be2461859f76) |
| Naming Convention Utility | Editor Tools | Applies consistent asset prefixes and suffixes through validated Unreal asset rename workflows. | [Overview](editor-tools/NamingConventionUtility/README.md) | [Fab product](https://www.fab.com/listings/60aefcc0-6464-4a69-98d1-7ba02c6e06f2) |
| Performance Preset Wizard | Editor Tools | Creates, reviews, applies, and restores reusable performance presets with scalability values and CVar overrides. | [Overview](editor-tools/PerformancePresetWizard/README.md) | [Fab product](https://www.fab.com/listings/39d1e5ea-4135-4197-91de-4c2193eb0d9c) |
| Smart Content Diet | Editor Tools | Scans Unreal assets for optimization candidates, explains findings, and supports reviewed QuickFix/reduction workflows with explicit safety boundaries. | [Overview](editor-tools/SmartContentDiet/README.md) | Not listed yet |

## UCM-First Integration Model

Cross-product workflows in the current Tiny Tool Development stack are primarily connected through **Unreal Capability Mesh (UCM)**. UCM owns the setup-declared capability, endpoint, route, rule, transform, and adapter layer. Core products keep their own data, settings, governance, and runtime behavior; UCM describes how those products connect without adding product-specific integration code to the hub.

Unified MCP Server exposes UCM routes as `mesh_*` and `mesh_route_*` tools for local agents. For normal multi-product setups, prefer UCM over direct provider bridges.

## Freebie Bridge Plugins

Freebie Bridge Plugins are not the default integration path for the current stack. They are provided for two specific cases:

- teams that do not own or do not enable UCM but still need a narrow direct adapter;
- developers who want reference implementations for how a responsible direct bridge should look.

They do not replace UCM, and they do not replace the products they connect. Each bridge keeps ownership clear: every core plugin continues to own its own data, settings, governance, and runtime behavior.

| Bridge Plugin | Connects | What It Does | Start Here |
| --- | --- | --- | --- |
| IIS LLM Store Bridge | Internal Index Service + LLM Store | No-UCM/reference adapter for routing IIS embedding jobs through LLM Store embedding routes while LLM Store keeps provider governance. | [Overview](bridge-plugins/InternalIndexServiceLLMStoreBridge/README.md) |
| SmartContentDiet IIS Similarity Bridge | Smart Content Diet + Internal Index Service | No-UCM/reference adapter for IIS-backed semantic similarity and prepared health-evidence import. | [Overview](bridge-plugins/SmartContentDietIISSimilarityBridge/README.md) |
| SmartContentDiet PRS Bridge | Smart Content Diet + Project Restructure Service | No-UCM/reference adapter for reviewed SCD placement moves into PRS validation, dry-run, apply, and rollback workflows. | [Overview](bridge-plugins/SmartContentDietPRSBridge/README.md) |
| SmartContentDiet UII Migration Bridge | Smart Content Diet + Unreal Integration Intelligence | No-UCM/reference adapter for surfacing UII migration handoff evidence as advisory SCD migration findings. | [Overview](bridge-plugins/SmartContentDietUIIMigrationBridge/README.md) |
| UII Internal Index Service Bridge | Unreal Integration Intelligence + Internal Index Service | No-UCM/reference adapter for importing UII handoff contracts into IIS evidence, catalog, retrieval, context-pack, embedding-job, and agent workflows. | [Overview](bridge-plugins/UIIInternalIndexServiceBridge/README.md) |

## Optional Freebie Scripts

Some products include optional free helper scripts that can extend a buyer's local project copy, internal source fork, or automation setup after purchase. These scripts are not hidden required setup steps and they do not replace the core product documentation.

Each script set is documented in the matching product folder so users can see what the script changes before they run it.

| Product | Script Documentation | Purpose |
| --- | --- | --- |
| LLM Store | [FREEBIE_SCRIPTS.md](ai-plugins/LLMStore/Documentation/FREEBIE_SCRIPTS.md) | Optional agent/authentication automation helpers such as `enable_agent_automation.sh`. |

## Documentation Reference

Depending on the product, documentation may include:

- `README.md` in the product folder for a short product-level landing page.
- `Documentation/README.md` for the complete documentation index.
- `CONTROL_PANEL.md` for products with a dedicated editor/operator panel.
- `BuyerGuide.md` or `BUYER_GUIDE.md` for product fit and buyer-facing overview.
- `QUICKSTART.md` for short setup and first verification steps.
- `UserManual.md` for practical editor workflows.
- `SettingsReference.md` or `SETTINGS.md` for settings, defaults, and recommended baselines.
- `INTEGRATION.md` for interfaces, runtime flow, and integration boundaries.
- `TechnicalOverview.md` and `CodeDocumentation.md` for architecture, source layout, contracts, and extension points.
- `Troubleshooting.md` or `TROUBLESHOOTING.md` for common problems and fixes.
- `FAQ.md` for quick answers.
- `ReleaseChecklist.md` or `RELEASE_CHECKLIST.md` for release, QA, and Fab preparation.
- `CHANGELOG.md` for release notes. Each listed product mirrors the plugin-root changelog from the shipped package when release notes change.
- `FREEBIE_SCRIPTS.md` for optional helper scripts that extend a buyer's local project copy or internal source fork after purchase.
- [EDITOR_MENUS.md](EDITOR_MENUS.md) for the shared Unreal Editor **Tools** menu layout across Tiny Tool Development products.
- [LOGGING_GUIDELINES.md](LOGGING_GUIDELINES.md) for Unreal log category, verbosity, and LogLevelEditor conventions.
- `Documentation/Screenshots/` and `Documentation/CI/` when visual guides or CI examples are included.

## Folder Naming

The top-level folders use lowercase kebab-case because this is a showcase repository:

```text
ai-plugins/
bridge-plugins/
editor-tools/
engine-plugins/
scene-tools/
```

Product folders keep their product/plugin names, for example `LLMStore`, `AsyncSplineBuilder`, and `PerformancePresetWizard`.

## Repository Structure

```text
ai-plugins/
  AssetPluginMaker/
  InternalIndexService/
  LLMStore/
  ProjectRestructureService/
  UnifiedMcpServer/
  UnrealIntegrationIntelligence/

foundation-plugins/
  UnrealCapabilityMesh/

engine-plugins/

bridge-plugins/
  InternalIndexServiceLLMStoreBridge/
  SmartContentDietIISSimilarityBridge/
  SmartContentDietPRSBridge/
  SmartContentDietUIIMigrationBridge/
  UIIInternalIndexServiceBridge/

editor-tools/
  CodeCopyrightEditor/
  LightweightEditorMode/
  LogLevelEditor/
  NamingConventionUtility/
  PerformancePresetWizard/
  SmartContentDiet/

scene-tools/
  AsyncSplineBuilder/
```

## Repository Hygiene

The repository is intentionally documentation-first. Generated folders such as `Binaries/`, `Intermediate/`, `Saved/`, `DerivedDataCache/`, local logs, runtime databases, dependency folders, and private environment files are ignored by Git.

Product screenshots, public media, PDFs, Markdown documents, bridge source samples, schemas, and curated examples may be committed when they are part of the public documentation package.

## Repository Restart

This repository was restarted from a fresh root commit so the active online branch no longer exposes the previous commit history. The restart preserves the current public documentation snapshot, keeps the product/category structure, adds stronger ignore rules for generated and local-only files, and records this README as the top-level orientation point for the documentation showcase.

## Support

For questions, setup help, and product support, join the Discord server:

https://discord.gg/HycgjVkK4J

## Note

This repository primarily provides product documentation, UCM integration information, and optional free bridge references for no-UCM projects. Product behavior may vary by version, Unreal Engine project, and product package. For authoritative details, always check the documentation in the matching product folder and the license or product materials included with the distribution.

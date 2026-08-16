<!-- doc-provenance: AKDB:plugins/UnrealCapabilityMesh/architecture.md; docs/architecture/plugins/UnrealCapabilityMesh/product-facts.yml; reconciled 2026-07-19 -->
# Unreal Capability Mesh Documentation

This folder documents the Unreal Capability Mesh plugin for Unreal Engine 5.4+, project setup, integration, and source-code reading.

Fab product page: https://www.fab.com/listings/fd186d26-cdcf-4c4f-93d4-50e437b7673e

## Start Here

| Document | Purpose |
| --- | --- |
| [BUYER_GUIDE.md](BUYER_GUIDE.md) | Product scope, included modules, what UCM does and does not do. |
| [QUICKSTART.md](QUICKSTART.md) | Minimal setup flow from manifests to generated reports. |
| [UserManual.md](UserManual.md) | Control panel workflow and normal operating procedure. |
| [TechnicalOverview.md](TechnicalOverview.md) | Architecture, data flow, storage locations, and diagnostics. |
| [CodeDocumentation.md](CodeDocumentation.md) | C++ source-reading guide by module and class. |
| [SettingsReference.md](SettingsReference.md) | Manifest folder layout, project profile fields, policy fields, output paths. |
| [INTEGRATION.md](INTEGRATION.md) | How to connect another plugin through manifests or adapters. |
| [TROUBLESHOOTING.md](TROUBLESHOOTING.md) | Common validation, discovery, route, and invocation problems. |
| [FAQ.md](FAQ.md) | Short answers for buyers and reviewers. |
| [ReleaseChecklist.md](ReleaseChecklist.md) | Fab compliance and packaging checklist. |
| [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md) | Third-party software declaration notes. |

## Core Idea

UCM is a neutral hub. It does not know about specific partner plugins in C++ code. UCM itself, enabled provider plugins, and the project can each describe capabilities, endpoints, schemas, rules, routes, transforms, and adapters in JSON. The loader merges those setup roots in priority order, builds registries, evaluates safety rules, and writes reports.

Current project setup uses UCM as the primary integration layer between Tiny Tool Development products. Product-specific behavior stays in the owning plugin as JSON-callable endpoints or file contracts; UCM only loads the setup that connects them. Freebie Bridges are optional fallback/reference plugins for teams without UCM, not the default connection model.

## Important Paths

```text
<EnabledPlugin>/Config/UnrealCapabilityMesh/  ← provider-owned read-only manifests
Config/UnrealCapabilityMesh/                   ← optional project-owned overrides and composite routes
Saved/UnrealCapabilityMesh/                    ← generated reports and route outputs
```

Do not copy a provider's manifests into the project merely to expose its routes. Enable the provider plugin and reload setup. Create a project override only when the project intentionally changes profile fields or owns a composite route.

<!-- doc-provenance: AKDB:plugins/UnrealCapabilityMesh/architecture.md; docs/architecture/plugins/UnrealCapabilityMesh/product-facts.yml; reconciled 2026-07-19 -->
# FAQ

## Is UCM an AI model or agent?

No. UCM is an interoperability hub. It can describe AI-related capabilities, but it does not include models, prompts, providers, or agent runtimes.

## Does UCM mutate assets?

Not by itself. It only loads manifests, plans routes, invokes declared endpoints, and writes diagnostics. Asset mutation must be performed by a provider endpoint and allowed by policy.

## Can approval be bypassed?

Only through the explicitly labeled **EXPERIMENTAL** self automatic approval controls in the Route Catalog approval column on the Routes page, the matching `project_profile.json` fields, or the MCP tool `mesh_configure_experimental_self_approval`. This is a broad policy bypass: deny rules, route asset/project-mutation checks, approval, and dry-run requirements are skipped. It is for testing or local own-risk workflows only; keep **Approve all at own risk** and all per-route switches disabled for normal use.

## Why use manifests instead of direct C++ dependencies?

Manifests let projects connect tools without creating compile-time dependency chains between plugins. That keeps the hub neutral and easier to package.

## Where are reports written?

Reports are written under `Saved/UnrealCapabilityMesh`.

## Where are project manifests stored?

Project manifests are stored under `Config/UnrealCapabilityMesh`.

## Can UCM integrate third-party marketplace plugins?

Yes, when those plugins expose callable functions, file contracts, or modular features that can be described by manifests or adapters.

## Does UCM bundle third-party code?

No bundled third-party source or runtime dependency is included in the plugin.

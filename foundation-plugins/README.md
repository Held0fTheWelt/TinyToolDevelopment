# Foundation Plugins

This category contains cross-product infrastructure that helps Unreal Engine tools discover capabilities, route work, enforce setup policy, and stay decoupled.

| Product | Description | Start Here | Fab |
| --- | --- | --- | --- |
| Unreal Capability Mesh | Published setup-driven interoperability hub for capabilities, endpoints, schemas, rules, routes, transforms, adapters, editor job routes, and optional MCP gateway access. | [Overview](UnrealCapabilityMesh/README.md) | [Fab product](https://www.fab.com/listings/fd186d26-cdcf-4c4f-93d4-50e437b7673e) |

Unreal Capability Mesh (UCM) is the preferred integration layer for current Tiny Tool Development cross-product workflows. Optional Freebie Bridges remain no-UCM fallback/reference implementations.

Provider plugins can ship their own mesh manifests for installed-project portability. Project-level
profiles then select or override those provider routes for a particular composition. See the
[cross-project composition workflow](../workflows/cross-project-composition.md) for a concrete
multi-owner example.

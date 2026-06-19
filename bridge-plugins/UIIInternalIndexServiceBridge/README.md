# UII Internal Index Service Bridge

UII Internal Index Service Bridge is an optional companion plugin for teams that use **Unreal Integration Intelligence (UII)** and **Internal Index Service (IIS)** in the same Unreal Engine project.

The plugin reads UII handoff contracts from disk and docks those evidence artifacts into IIS through IIS public APIs. It gives teams a controlled one-shot path from UII evidence exports into IIS import, catalog, retrieval, context-pack, embedding-job, and agent-contract workflows.

## UCM-First Note

In the current Tiny Tool Development stack, UII-to-IIS handoff workflows should normally be exposed through **Unreal Capability Mesh (UCM)** setup-declared routes. Use this Freebie Bridge only when a project does not own or enable UCM, or when you need a concrete reference for building a narrow direct adapter.

## Product Boundary

This plugin is intentionally a bridge. It does not replace or bundle either core product, and it does not replace UCM in projects that use the full Tiny Tool Development stack.

| Product | Responsibility |
| --- | --- |
| Unreal Integration Intelligence (UII) | Unreal evidence extraction and handoff artifact generation. |
| UII Internal Index Service Bridge | File-level docking from UII handoff contracts to IIS public APIs. |
| Internal Index Service (IIS) | Evidence import, indexing, cataloging, retrieval, context packs, reports, embedding jobs, and agent access. |

The bridge is useful when UII already generated a handoff contract and you want IIS to import, catalog, and validate that prepared evidence without adding UII-specific logic to IIS.

## Why Use It

- Import UII prepared chunks into IIS from a single contract path.
- Chain import, catalog build, bounded embedding jobs, smoke search, context packs, and agent contract export.
- Keep UII focused on evidence extraction while IIS owns indexing and retrieval.
- Use Blueprint, Python, C++, or editor menu entry points that all call the same pipeline implementation.
- Preserve evidence-only guardrails in every docking report.

## Handoff Flow

The bridge reads the standard UII handoff contract:

```text
Saved/UnrealIntegrationIntelligence/iis_handoff/iis_import_contract.json
```

Pipeline flow:

```text
UII handoff contract
  -> validate prepared chunks, labels, groups, manifests
  -> import prepared chunks into IIS
  -> optional IIS catalog build
  -> optional IIS embedding job build/execution
  -> hybrid smoke search
  -> context pack report
  -> agent tool contract export
  -> docking readiness report
```

Reports are written under:

```text
Saved/InternalIndexService/reports/
```

## Requirements

- Unreal Engine 5.4.
- Internal Index Service installed and enabled.
- Unreal Integration Intelligence installed, or an equivalent producer that writes compatible UII handoff contracts.
- A project or engine plugin setup that contains IIS and this bridge.

The bridge depends on IIS because it calls IIS public import, catalog, retrieval, embedding-job, report, and agent APIs. It does not require a compile dependency on UII modules because it reads UII handoff files from disk.

## Quick Start

Place the bridge next to IIS:

```text
Plugins/
  InternalIndexService/
  UIIInternalIndexServiceBridge/
```

Enable both in the `.uproject`:

```json
{
  "Plugins": [
    { "Name": "InternalIndexService", "Enabled": true },
    { "Name": "UIIInternalIndexServiceBridge", "Enabled": true }
  ]
}
```

Run the UII workflow that writes the handoff contract, then trigger the bridge through one of these entry points:

- Tools menu: `Tools > UII -> Internal Index Service`
- Blueprint: `UUIIInternalIndexServiceBridgeBlueprintLibrary`
- Python/editor wrapper: `UUIIInternalIndexServiceBridgePythonBridge`
- C++ facade: `FUIIInternalIndexServiceHandoffImporter`

Common pipeline levels:

- Import the UII handoff into IIS.
- Import the handoff and build the IIS catalog.
- Run the bounded full pipeline with IIS embedding jobs and smoke checks.

## Blueprint and Editor Access

Blueprint nodes are available under:

```text
UII | Internal Index Service Bridge
```

They are intended for Editor Utility Widgets, Editor Utility Blueprints, and diagnostic workflows. Blueprint can resolve the latest UII handoff path, import a contract, build the IIS catalog, run a bounded full handoff pipeline, and return report paths plus warnings.

See [Blueprint usage](Documentation/BLUEPRINT_USAGE.md) for node-by-node examples.

## What It Does Not Do

The bridge does not:

- extract Unreal evidence;
- mutate Blueprints, assets, source files, or project settings;
- authorize migration, placement, patching, copying, or project mutation;
- generate migration decisions;
- generate patches;
- choose LLM providers or models;
- call model providers directly;
- run AI chat or completion;
- reimplement IIS indexing.

UII produces evidence. IIS indexes and retrieves evidence. The bridge only docks the two.

## Documentation

- [Documentation overview](Documentation/README.md)
- [Buyer guide](Documentation/BUYER_GUIDE.md)
- [Quickstart](Documentation/QUICKSTART.md)
- [Blueprint usage](Documentation/BLUEPRINT_USAGE.md)
- [Integration details](Documentation/INTEGRATION.md)
- [Source overview](Documentation/SOURCE_OVERVIEW.md)
- [Troubleshooting](Documentation/TROUBLESHOOTING.md)
- [Release checklist](Documentation/RELEASE_CHECKLIST.md)
- [Changelog](CHANGELOG.md)

## Support

For questions, setup help, and product support, join the Discord server:

https://discord.gg/HycgjVkK4J

## Guardrail Boundary

Every pipeline report preserves the evidence-only rule:

```text
This workflow imports evidence only.
It does not authorize migration, placement, patching, copying, or project mutation.
IIS may index and retrieve evidence, but it does not change Unreal project assets or source files.
```

The bridge writes docking reports under IIS' report directory and keeps all mutation flags false:

```text
allows_migration_decision = false
allows_patch_generation = false
allows_project_mutation = false
```

## Version

Current bridge version: `1.0.0`.

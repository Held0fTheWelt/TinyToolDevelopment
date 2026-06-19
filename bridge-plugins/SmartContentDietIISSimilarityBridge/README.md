# SmartContentDiet IIS Similarity Bridge

SmartContentDiet IIS Similarity Bridge is an optional companion plugin for teams that use **Smart Content Diet** and **Internal Index Service (IIS)** in the same Unreal Engine project.

The bridge registers an SCD semantic similarity provider named `iis-similarity` and provides an importer that translates SCD health-evidence JSONL into IIS prepared chunks. Smart Content Diet keeps ownership of asset-health findings and review workflows. IIS keeps ownership of indexing, retrieval, vector storage, and context data.

## UCM-First Note

In the current Tiny Tool Development stack, **Unreal Capability Mesh (UCM)** is the preferred integration layer for SCD/IIS workflows. Use this Freebie Bridge only when a project does not own or enable UCM, or when you need a concrete reference for building a narrow direct adapter.

## Product Boundary

| Product | Responsibility |
| --- | --- |
| Smart Content Diet | Asset health scans, optimization findings, similarity requests, and reviewed QuickFix/reduction workflows. |
| SmartContentDiet IIS Similarity Bridge | Interface adapter from SCD health evidence and similarity requests into IIS public retrieval contracts. |
| Internal Index Service | Local evidence import, cataloging, retrieval, vector payloads, and context-pack workflows. |

## Why Use It Without UCM

- Use IIS semantic retrieval as a first-party SCD similarity provider.
- Import SCD health-evidence JSONL into IIS prepared chunks for later retrieval.
- Map SCD health metadata to IIS `chunk_kind` and `sensitivity` tokens so imported chunks remain labelled.
- Keep SCD independent from IIS implementation details.
- Keep IIS read-only with respect to Unreal assets and source files.

## Technical Shape

- Unreal Engine 5.4.
- Version: `1.0.1`.
- Module: `SmartContentDietIISSimilarityBridge` (`Editor`).
- Platforms: Win64, Mac, Linux.
- Content: none.
- Public interfaces: `SmartContentDietInterface`, `InternalIndexServiceInterface`.
- Provider id: `iis-similarity`.

## Quick Start

Place all required plugins side by side:

```text
Plugins/
  SmartContentDiet/
  InternalIndexService/
  SmartContentDietIISSimilarityBridge/
```

Enable all three plugins in the project, build the editor target, and start Unreal Editor. SCD similarity workflows can then request semantic grouping through the `iis-similarity` provider when IIS has matching indexed evidence.

For evidence import workflows, call the bridge importer from integration code or the SCD workflow that wraps it:

```text
FSCDHealthEvidenceToIISImporter::ImportHealthEvidenceJsonl
```

## What It Does Not Do

The bridge does not scan assets, mutate assets, generate fixes, choose embedding providers, replace IIS indexing, or make Smart Content Diet an autonomous agent. It only adapts SCD health evidence and semantic similarity requests to IIS-compatible public contracts.

## Documentation

- [Documentation overview](Documentation/README.md)
- [Changelog](CHANGELOG.md)

## Status

- Category: Freebie Bridge Plugins
- Status: In preparation
- Fab: Not listed separately

## Support

For questions, setup help, and product support:

https://discord.gg/HycgjVkK4J

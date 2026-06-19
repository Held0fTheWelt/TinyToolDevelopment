# SmartContentDiet IIS Similarity Bridge Documentation

This bridge connects Smart Content Diet similarity workflows to Internal Index Service retrieval contracts for projects that do not use Unreal Capability Mesh for the same route.

## Start Here

- [../README.md](../README.md): product boundary, quick start, and technical shape.
- [../CHANGELOG.md](../CHANGELOG.md): release history.

## Source Map

- `SCDHealthEvidenceToIISImporter`: imports SCD health-evidence JSONL into IIS prepared chunks.
- `SCDIISSimilarityGrouping`: adapts SCD similarity requests into IIS-style grouping behavior.
- `SCDHealthEvidenceJsonlTranslator`: translates health evidence into importer payloads.
- `SCDHealthEvidenceIISBridgeCommon`: shared bridge DTO helpers.

## Boundary

The bridge does not scan assets, mutate assets, choose embedding providers, or replace IIS indexing. It only adapts reviewed SCD evidence and similarity requests to IIS-compatible public contracts.

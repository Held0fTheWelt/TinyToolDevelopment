# Source Overview

This bridge turns a UII handoff contract into IIS public API calls. It does not run UII extraction and does not perform migration, patching, copying, or project mutation.

```text
UII handoff files on disk
  -> UII Internal Index Service Bridge
  -> IIS public import/catalog/embedding/agent APIs
```

## Runtime Module

Source:

```text
Source/UIIInternalIndexServiceBridge/
  Public/UIIInternalIndexServiceBridgeBlueprintLibrary.h
  Public/UIIInternalIndexServiceBridgeModule.h
  Public/UIIInternalIndexServiceHandoffImporter.h
  Private/UIIInternalIndexServiceBridgeBlueprintLibrary.cpp
  Private/UIIInternalIndexServiceBridgeModule.cpp
  Private/UIIInternalIndexServiceHandoffImporter.cpp
```

The runtime module only logs bridge availability. Pipeline work is explicit through `FUIIInternalIndexServiceHandoffImporter`.

## Blueprint Library

`UUIIInternalIndexServiceBridgeBlueprintLibrary` exposes the same evidence-only pipeline levels to Blueprint:

- latest handoff contract path lookup;
- import-only handoff docking;
- import plus catalog build;
- bounded full pipeline with IIS embedding jobs;
- report paths and warnings for operator diagnostics.

The Blueprint nodes delegate to `FUIIInternalIndexServiceHandoffImporter`, so Blueprint, C++, Python, and menu actions share the same implementation.

## Pipeline Facade

`FUIIInternalIndexServiceHandoffImporter` exposes three levels:

- `ImportUIIHandoffContract(...)`: import prepared evidence only.
- `ImportUIIHandoffAndBuildCatalog(...)`: import evidence and rebuild the IIS catalog.
- `ImportUIIHandoffBuildCatalogAndEmbeddings(...)`: import, catalog, build/execute bounded IIS embedding jobs, run smoke retrieval, and write agent contracts.

## Contract Resolution

The importer supports both:

- flat fields such as `prepared_chunks_jsonl_path`;
- newer `input_files` entries with logical names.

Required files are validated before import starts. Optional files produce warnings, not hard failures.

## Pipeline Phases

The implementation runs these phases in order:

1. Resolve and validate the UII handoff contract.
2. Import prepared chunks into IIS.
3. Optionally build the IIS catalog and usage graph.
4. Optionally build and execute IIS embedding jobs.
5. Run a local hybrid smoke search and context pack build.
6. Write IIS agent tool contracts.
7. Write the docking readiness report.

Every report keeps the evidence-only guardrails and all mutation flags false.

## Editor Module

Source:

```text
Source/UIIInternalIndexServiceBridgeEditor/
  Public/UIIInternalIndexServiceBridgeEditorModule.h
  Public/UIIInternalIndexServiceBridgePythonBridge.h
  Private/UIIInternalIndexServiceBridgeEditorModule.cpp
  Private/UIIInternalIndexServiceBridgePythonBridge.cpp
```

The editor module provides Tools menu diagnostics and Python/Blueprint-callable wrappers. It intentionally uses the same wrappers for menu actions and automation so behavior stays consistent.

## Non-Goals in Source

The source code must not add:

- UII extraction logic;
- provider/model selection;
- AI chat/completion execution;
- LLM reranking;
- migration planning;
- patch generation;
- asset, Blueprint, source, or project mutation;
- direct dependencies on UII runtime internals.

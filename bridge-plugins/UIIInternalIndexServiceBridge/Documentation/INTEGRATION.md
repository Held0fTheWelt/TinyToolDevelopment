# Integration Details

## Runtime Architecture

The bridge has two modules:

```text
UIIInternalIndexServiceBridge
  runtime pipeline and contract reader

UIIInternalIndexServiceBridgeEditor
  Python bridge and Tools menu actions
```

The runtime module reads UII handoff JSON from disk. The editor module exposes convenient entry points.

## Dependency Direction

```text
UII
  -> no dependency on IIS required for evidence export

InternalIndexService
  -> no dependency on UII

UIIInternalIndexServiceBridge
  -> InternalIndexService
  -> InternalIndexServiceInterface
```

The bridge may know UII file paths. IIS should not.

## Handoff Contract Inputs

The bridge reads these flat contract fields when present:

```text
source_id
source_run_id
destination_run_id
prepared_chunks_jsonl_path
prepared_chunks_manifest_path
retrieval_labels_path
retrieval_groups_path
rag_export_package_path
rag_consumer_contract_path
langgraph_handoff_envelope_path
guardrails
forbidden_actions
```

It also supports `input_files[]` entries with `logical_name` and `relative_path`.

## Pipeline Modes

The public runtime class exposes three pipeline levels:

```cpp
ImportUIIHandoffContract(...)
ImportUIIHandoffAndBuildCatalog(...)
ImportUIIHandoffBuildCatalogAndEmbeddings(...)
```

### Import Only

Validates the contract and imports prepared chunks into IIS.

### Import + Catalog

Runs import, then builds or updates the IIS chunk catalog.

### Full Pipeline

Runs import, catalog build, embedding job build/execution, hybrid smoke search, context pack report, and agent contract export.

Embedding execution still belongs to IIS and its registered embedding executor. If IIS is connected to LLM Store through the IIS LLM Store Bridge, LLM Store governs provider/model routing.

## Guardrails

All reports set:

```text
allows_migration_decision = false
allows_patch_generation = false
allows_project_mutation = false
```

The bridge does not authorize copying, placement, migration, patching, or mutation.

## Reports

The bridge writes:

```text
Saved/InternalIndexService/reports/uii_iis_docking_report.json
Saved/InternalIndexService/reports/uii_iis_docking_report.md
```

Report fields are intentionally redundant so an operator or agent can inspect readiness without opening every downstream IIS report.


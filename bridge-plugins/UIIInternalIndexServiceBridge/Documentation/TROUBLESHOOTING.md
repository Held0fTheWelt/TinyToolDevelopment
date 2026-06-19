# Troubleshooting

## Contract Missing

Expected default path:

```text
Saved/UnrealIntegrationIntelligence/iis_handoff/iis_import_contract.json
```

If missing:

- run the UII handoff export workflow;
- pass an explicit contract path to the Python bridge;
- verify the project Saved directory is the one you expect.

## Required File Missing

The bridge requires:

```text
prepared_chunks_jsonl_path
prepared_chunks_manifest_path
retrieval_labels_path
retrieval_groups_path
```

If any path is missing or unreadable, the pipeline fails before import.

## Import Succeeds but Catalog Does Not Build

Check the IIS catalog report:

```text
Saved/InternalIndexService/indexes/catalog_build_report.json
```

Common causes:

- malformed imported chunk JSON;
- unsafe chunk guardrail flags;
- stale catalog file locked by another process;
- SQLite initialization failure.

## Embedding Step Does Not Complete

Embedding is optional in the bridge pipeline.

If enabled, IIS needs a registered embedding executor. With LLM Store, install and enable:

```text
InternalIndexServiceLLMStoreBridge
```

If no executor is registered, IIS should return a controlled embedding failure while import and catalog remain valid.

## Hybrid Smoke Search Returns No Results

The default smoke query is:

```text
guardrail
```

No result can be valid if the imported evidence has no matching chunk. Check:

- imported chunk count;
- catalog chunk count;
- labels/groups in the catalog;
- search report under IIS logs.

## BuildPlugin Fails Because Dependencies Are Missing

Build the bridge in a host project that includes IIS:

```text
Plugins/InternalIndexService/
Plugins/UIIInternalIndexServiceBridge/
```

If you also execute embedding validation, include LLM Store and the IIS LLM Store Bridge.

## Do Not Commit Build Artifacts

Public repositories should not include:

```text
Binaries/
Intermediate/
Saved/
DerivedDataCache/
```


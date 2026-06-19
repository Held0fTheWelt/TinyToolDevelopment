# Quickstart

## 1. Install Required Plugins

Install IIS and this bridge:

```text
Plugins/
  InternalIndexService/
  UIIInternalIndexServiceBridge/
```

UII should also be installed or otherwise available to produce handoff contracts.

## 2. Enable Plugins

Enable the bridge in your `.uproject`:

```json
{
  "Name": "UIIInternalIndexServiceBridge",
  "Enabled": true
}
```

IIS must also be enabled.

## 3. Generate a UII Handoff Contract

Run the UII workflow that writes:

```text
Saved/UnrealIntegrationIntelligence/iis_handoff/iis_import_contract.json
```

The contract should point to:

- prepared chunks JSONL;
- prepared chunks manifest;
- retrieval labels;
- retrieval groups;
- optional RAG package;
- optional consumer contract;
- optional LangGraph handoff envelope.

## 4. Import Through the Bridge

Use the Blueprint library, Python bridge, or menu action:

```cpp
UUIIInternalIndexServiceBridgeBlueprintLibrary::ImportUIIHandoffContract(...)
UUIIInternalIndexServiceBridgeBlueprintLibrary::ImportUIIHandoffAndBuildCatalog(...)
UUIIInternalIndexServiceBridgeBlueprintLibrary::ImportUIIHandoffBuildCatalogAndEmbeddings(...)
UUIIInternalIndexServiceBridgePythonBridge::ImportUIIHandoffContract(...)
UUIIInternalIndexServiceBridgePythonBridge::ImportUIIHandoffAndBuildCatalog(...)
UUIIInternalIndexServiceBridgePythonBridge::ImportUIIHandoffBuildCatalogAndEmbeddings(...)
```

The editor menu is registered under:

```text
Tools > UII -> Internal Index Service
```

For Editor Utility Widgets, use:

```text
Import Latest UII Handoff into IIS
Import Latest UII Handoff and Build IIS Catalog
Run Latest Full UII IIS Handoff Pipeline
```

See [Blueprint usage](BLUEPRINT_USAGE.md) for node-by-node examples.

## 5. Read the Docking Report

The bridge writes IIS docking reports:

```text
Saved/InternalIndexService/reports/uii_iis_docking_report.json
Saved/InternalIndexService/reports/uii_iis_docking_report.md
```

The report includes:

- contract readability;
- prepared chunk readability;
- import status;
- catalog status;
- embedding status;
- vector status;
- hybrid search smoke status;
- agent contract status;
- guardrails;
- warnings and errors.

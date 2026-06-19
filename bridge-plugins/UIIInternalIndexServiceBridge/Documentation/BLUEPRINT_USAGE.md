# Blueprint Usage

The UII Internal Index Service Bridge is usable from Blueprint through:

```text
UUIIInternalIndexServiceBridgeBlueprintLibrary
```

Node category:

```text
UII | Internal Index Service Bridge
```

These nodes are designed for Editor Utility Widgets, Editor Utility Blueprints, and diagnostic Blueprints that should trigger evidence-only UII -> IIS docking workflows.

## What Blueprint Can Do

Blueprint can:

- get the conventional latest UII IIS handoff contract path;
- import a specific UII handoff contract into IIS;
- import the latest UII handoff contract into IIS;
- import and rebuild the IIS catalog;
- run the bounded full handoff pipeline with IIS embedding jobs;
- receive report paths and warnings for operator diagnostics.

Blueprint does not run UII extraction. It only reads UII handoff files already written to disk.

## Nodes

### Get Latest UII IIS Handoff Contract Path

Returns:

```text
Saved/UnrealIntegrationIntelligence/iis_handoff/iis_import_contract.json
```

Use this when UII writes the standard latest handoff contract.

### Import UII Handoff Contract into IIS

Inputs:

```text
ContractPath
```

Outputs:

```text
OutReportPath
OutWarnings
ReturnValue
```

This imports prepared chunks into IIS and writes:

```text
Saved/InternalIndexService/reports/uii_iis_docking_report.json
Saved/InternalIndexService/reports/uii_iis_docking_report.md
```

### Import Latest UII Handoff into IIS

Convenience node that uses the latest conventional UII handoff path.

### Import UII Handoff and Build IIS Catalog

Runs:

```text
Import prepared chunks
Build IIS chunk catalog
Write docking report
```

Use this when the next step is lexical or hybrid evidence search.

### Import Latest UII Handoff and Build IIS Catalog

Convenience node for the standard latest handoff path.

### Run Full UII IIS Handoff Pipeline

Runs:

```text
Import
Catalog build
Embedding job build
Embedding job execution up to MaxEmbeddingJobs
Hybrid smoke search
Context pack report
Agent tool contract export
Docking report
```

Recommended value for diagnostic buttons:

```text
MaxEmbeddingJobs = 10
```

### Run Latest Full UII IIS Handoff Pipeline

Convenience node for the standard latest handoff path.

## Recommended Blueprint Graphs

### Import-Only Button

```text
Editor Utility Button
  -> Get Latest UII IIS Handoff Contract Path
  -> Import UII Handoff Contract into IIS
  -> Print OutReportPath
  -> Print OutWarnings
```

### Catalog-Ready Button

```text
Editor Utility Button
  -> Import Latest UII Handoff and Build IIS Catalog
  -> Branch on ReturnValue
  -> Open or print OutReportPath
```

### Full Local Readiness Button

```text
Editor Utility Button
  -> Run Latest Full UII IIS Handoff Pipeline
       MaxEmbeddingJobs = 10
  -> Branch on ReturnValue
  -> Print OutReportPath
  -> Print OutWarnings
```

## Reports

Blueprint nodes write docking reports under:

```text
Saved/InternalIndexService/reports/
```

The report includes:

- contract readability;
- prepared chunks readability;
- import status;
- catalog status;
- embedding status;
- vector status;
- hybrid smoke search status;
- context pack status;
- agent contract status;
- guardrails;
- warnings and errors.

## Guardrails

Every pipeline report keeps these rules visible:

```text
This workflow imports evidence only.
It does not authorize migration, placement, patching, copying, or project mutation.
IIS may index and retrieve evidence, but it does not change Unreal project assets or source files.
```

Blueprint nodes in this bridge:

- do not extract UII evidence;
- do not mutate assets or Blueprints;
- do not copy source files;
- do not generate migration decisions;
- do not generate patches;
- do not execute AI chat/completion routes;
- do not select LLM providers or models.


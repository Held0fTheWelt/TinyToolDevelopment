<!-- doc-provenance: SAD architecture.md sections 6,8,10,11; facts product-facts.yml; reconciled 2026-07-16 -->
# Troubleshooting

## Build Fails On UE 5.6 With Engine Header Errors

Ensure IIS modules compile with C++20. UE 5.6 engine headers use C++20 syntax. The IIS `.Build.cs` files should use:

```csharp
CppStandard = CppStandardVersion.Cpp20;
```

## Search Returns No Results

Check:

- prepared chunks were imported
- catalog was rebuilt
- query text is not empty
- lifecycle state is active
- index root points to the expected project folder

## Vector Search Returns No Results

Check:

- embedding jobs were built
- embedding jobs executed successfully
- LLM Store route/executor is registered
- vector backend setting matches persisted artifacts

## Import Fails

Check that the prepared chunks JSONL exists and is readable. Review import reports under the IIS saved root for validation warnings and rejected records.

## HNSW Index Cannot Load Or Produces Backend Warnings

If the HNSW backend cannot load, or backend warnings appear after changing vector storage settings,
switch temporarily to `jsonl_bruteforce` to separate vector data issues from backend-specific indexing
issues. Keep **Rebuild On Vector Format Mismatch** enabled so incompatible persisted HNSW partitions
are rebuilt from source vectors instead of being loaded with the wrong byte layout.

Confirm `Source/ThirdParty/hnswlib` is present in the package and rebuild vector artifacts after
changing **Vector Storage Format**.

## Runtime Tune Or Index Act-Verb Returns Disabled

Check **Enable Runtime Control Mutations** in Project Settings. When it is off, read verbs such as
`iis.control.state` still work, but tune, act, persist, and reset verbs return a disabled response by
design.

Re-enable the setting for mutating control verbs, or continue with read-only state and diagnostics
commands.

## Agent Tools Are Missing From The MCP Client

Check:

- Unified MCP Server is enabled and running
- Unreal Capability Mesh is enabled
- project setup includes IIS agent route manifests (`iis.agent.*.v1`)
- call `mesh_list_routes` or `mesh_reload_setup` and refresh the MCP client
- IIS can write agent tool contracts
- the MCP client is connected to the UMCP endpoint, not a legacy per-plugin MCP server

Refresh the Capability Mesh setup and reconnect or refresh the MCP client after route changes.

## Agent Tool Returns Retrieval-Only Guardrails

That is expected. IIS responses intentionally state that project mutation is not allowed.

## Perf Self-Check Reports A Deviation

Review the latest perf result from `iis.perf.last` or rerun `iis.perf.run`. Deviations usually mean the
current vector workload, backend, or tuning exceeds the configured budgets.

Lower query breadth or vector workload first. Update budgets only after representative validation on
the target machine/project profile.

## Where To Look For Reports

Default:

```text
Saved/InternalIndexService/reports
Saved/InternalIndexService/imports
Saved/InternalIndexService/agent_contracts
```

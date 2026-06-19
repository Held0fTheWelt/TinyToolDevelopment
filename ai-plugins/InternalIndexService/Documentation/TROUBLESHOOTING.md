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

## UMCP Does Not Show IIS Agent Routes

Check:

- Unified MCP Server is enabled and running
- Unreal Capability Mesh is enabled
- project setup includes IIS agent route manifests (`iis.agent.*.v1`)
- call `mesh_list_routes` or `mesh_reload_setup` and refresh the MCP client
- IIS can write agent tool contracts
- the MCP client is connected to the UMCP endpoint, not a legacy per-plugin MCP server

## Agent Tool Returns Retrieval-Only Guardrails

That is expected. IIS responses intentionally state that project mutation is not allowed.

## hnsw Backend Problems

Switch temporarily to `jsonl_bruteforce` to separate vector data issues from backend-specific indexing issues. Confirm `Source/ThirdParty/hnswlib` is present in the package.

## Where To Look For Reports

Default:

```text
Saved/InternalIndexService/reports
Saved/InternalIndexService/imports
Saved/InternalIndexService/agent_contracts
```

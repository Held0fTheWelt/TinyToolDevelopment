# Integration Guide

Use this guide when another plugin should expose tools through Unified MCP Server.

## Add A Dependency

In the provider plugin `.Build.cs`, depend on:

```csharp
PrivateDependencyModuleNames.AddRange(new string[]
{
    "UnifiedMcpServerInterface"
});
```

Use public dependency only if your public headers expose UMCP types.

## Implement `IUmcpToolProvider`

```cpp
class FMyToolProvider : public IUmcpToolProvider
{
public:
    virtual FString GetProviderId() const override { return TEXT("myplugin"); }
    virtual FString GetProviderDisplayName() const override { return TEXT("My Plugin"); }
    virtual void GetToolDescriptors(TArray<FUmcpToolDescriptor>& OutTools) const override;
    virtual void InvokeTool(const FUmcpToolInvocation& Invocation, FUmcpToolResult& OutResult) override;
};
```

Provider IDs should not contain underscores. Tools are exposed as:

```text
myplugin_<descriptor.Name>
```

## Register The Provider

Register during module startup:

```cpp
IModularFeatures::Get().RegisterModularFeature(
    IUmcpToolProvider::GetModularFeatureName(),
    Provider.Get());
```

Unregister during shutdown:

```cpp
IModularFeatures::Get().UnregisterModularFeature(
    IUmcpToolProvider::GetModularFeatureName(),
    Provider.Get());
```

Store the provider in a stable object such as `TUniquePtr<FMyToolProvider>` owned by the module.

## Tool Descriptors

Each descriptor contains:

| Field | Meaning |
| --- | --- |
| `Name` | Provider-local tool name. |
| `Description` | User-facing tool description for MCP clients. |
| `InputSchemaJson` | JSON Schema object serialized as a string. |
| `OutputSchemaJson` | Optional JSON Schema object for `structuredContent`, serialized as a string. |
| `AnnotationsJson` | Optional MCP tool annotations object, serialized as a string. |

If `InputSchemaJson` is empty, the server falls back to an object schema. If `Validate Tool Arguments` is enabled in UMCP settings, the registry performs lightweight top-level validation before invoking the provider: required fields, unknown fields when `additionalProperties:false`, primitive JSON types, and enum values.

UMCP access control is applied after descriptors are collected and before MCP exposure or invocation. Disabled provider IDs, access profiles, allowed/blocked tool patterns, and allowed/blocked annotation-derived groups can hide tools from `tools/list` and return `tool_access_denied` for direct `tools/call` requests without invoking the provider.

## JSON Boundary Adapter

`FUmcpJsonAdapter` (`UnifiedMcpServerInterface/Public/UmcpJsonAdapter.h`) is the shared helper for typed JSON at the provider boundary. Keep `IUmcpToolProvider` string fields unchanged; parse once at the top of `InvokeTool` and serialize results back to text.

| Helper | Purpose |
| --- | --- |
| `ParseArgs(ArgumentsJson, Out, OutError)` | Parse `FUmcpToolInvocation::ArgumentsJson` once. Empty input becomes `{}`. Malformed JSON sets `OutError` with `ErrorCode = invalid_arguments_json`. |
| `ParseObject(Json, OutObject)` | Lower-level parse used by `ParseArgs`; empty input becomes an empty object. |
| `Ok(ResultJson)` | Build a successful `FUmcpToolResult` with `Status = Ok`. |

Example pattern:

```cpp
void FMyToolProvider::InvokeTool(const FUmcpToolInvocation& Invocation, FUmcpToolResult& OutResult)
{
    TSharedPtr<FJsonObject> Args;
    if (!FUmcpJsonAdapter::ParseArgs(Invocation.ArgumentsJson, Args, OutResult))
    {
        return;
    }

    // Read typed fields from Args, execute tool logic, then:
    OutResult = FUmcpJsonAdapter::Ok(ResultObjectJson);
}
```

Do not re-parse `ArgumentsJson` deeper in the call stack. Do not change the shape of `FUmcpToolInvocation` or `FUmcpToolResult`.

## Invocation

`InvokeTool` receives:

| Field | Meaning |
| --- | --- |
| `ToolName` | Provider-local tool name, without provider prefix. |
| `ArgumentsJson` | JSON object of arguments serialized as text. |

Return `FUmcpToolResult`:

| Field | Meaning |
| --- | --- |
| `Status` | `Ok` or `Error`. |
| `ResultJson` | JSON value serialized as text. |
| `ErrorCode` | Stable provider error code. |
| `ErrorMessage` | Human-readable failure message. |

When `ResultJson` is a JSON object, `tools/call` returns it both as text content and as MCP `structuredContent`. Providers should keep successful results object-shaped when possible so clients can reason over fields instead of parsing prose.

## Capability Mesh Provider

`UnifiedMcpServerEditor` includes a soft provider for Unreal Capability Mesh. It resolves the mesh gateway by reflection and exposes `mesh_*` tools when the gateway is available. Prefer this path for setup-declared cross-plugin workflows. Flattened `mesh_route_*` tools receive route-derived `inputSchema`, `outputSchema`, and annotations from the UCM gateway. The provider also exposes `mesh_configure_experimental_self_approval`; that tool is explicitly **EXPERIMENTAL**, requires risk acknowledgement when enabling, and is only for own-risk testing workflows.

In the UMCP control panel, generic mesh host tools appear under **Unreal Capability Mesh**. Flattened route tools are grouped under the owning plugin from UCM capability metadata (`provider_id`, `display_name`), which matches how routes are declared in project setup rather than listing every route under the mesh host.

## Editor Job History (UCM Routes)

Fab tool plugins (IIS, LLMStore, SCD, and similar) must **not** depend on `UnifiedMcpServerInterface` to expose job history. Each plugin publishes read-only editor job list/status through static `UFUNCTION` JSON endpoints bound in UCM manifests, for example:

| Route ID | Purpose |
| --- | --- |
| `iis.editor.jobs.list.v1` | Recent IIS jobs (panel cache + optional SQLite store merge) |
| `iis.editor.jobs.status.v1` | Single IIS job lookup |
| `scd.editor.jobs.list.v1` | Recent SCD jobs |
| `llmstore.editor.jobs.list.v1` | Recent LLMStore jobs |
| `umcp.editor.jobs.list.v1` | Recent UMCP panel jobs |

Agents can call these directly as flattened `mesh_route_*` tools when UCM is enabled.

UMCP also exposes aggregated **`jobs_list`** and **`jobs_status`** MCP tools. The host `FUmcpJobsToolProvider` calls the UCM gateway (`ExecuteRouteJson`) for the fixed route table above, merges JSON results, and emits the same wire shape (`source_provider_id`, job fields). This keeps Fab plugins autark while preserving one-call cross-plugin observability when Unreal Capability Mesh is present.

Do **not** implement `IUmcpJobStatusProvider` in tool plugins — that interface is deprecated and retained only for backward compatibility.

## Direct Provider Example

Direct provider plugins can still implement `IUmcpToolProvider` for product-specific tools. Keep those providers narrow and avoid duplicating behavior that already exists as a UCM route.

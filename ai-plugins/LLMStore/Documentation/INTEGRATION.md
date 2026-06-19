# Integration Guide

This guide describes how other plugins, C++ systems, and Blueprints use or extend LLM Store.

## Dependency Choice

Consumer plugins should prefer depending on:

```text
LLMStoreInterface
```

Use the implementation module only when you need direct access to `ULLMStoreSubsystem` functions such as saving config, setting keys, exporting cost reports, or registering Blueprint add-ons.

## Get the Store in C++

```cpp
#include "LLMStoreSubsystem.h"

ULLMStoreSubsystem* Store = GEngine->GetEngineSubsystem<ULLMStoreSubsystem>();
if (!Store)
{
    return;
}
```

If your code only needs the facade contract, keep the dependency conceptual:

```cpp
#include "Interfaces/LLMStoreInterface.h"

ILLMStore* StoreInterface = GEngine->GetEngineSubsystem<ULLMStoreSubsystem>();
```

## Execute a Route

```cpp
FLLMRequest Request;
Request.TaskKind = TEXT("docs.summarize");
Request.SystemPrompt = TEXT("You are concise and precise.");
Request.Prompt = TEXT("Summarize this content...");

FLLMResponseDelegate OnComplete;
OnComplete.BindUFunction(this, FName("HandleLLMResponse"));

Store->ExecuteRoute(Request, OnComplete);
```

Handler:

```cpp
UFUNCTION()
void HandleLLMResponse(const FLLMResponse& Response)
{
    if (Response.Result.bSuccess)
    {
        UE_LOG(LogTemp, Log, TEXT("LLM response: %s"), *Response.Content);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("LLM failed: %s"), *Response.Result.Message);
    }
}
```

## Resolve Without Executing

Use this when your code needs to inspect the selected provider/model or build its own provider call:

```cpp
FLLMResolvedRoute Resolved;
FLLMResult Result = Store->ResolveRouteChecked(TEXT("docs.summarize"), Resolved);
```

`ResolveRouteChecked` applies policy add-ons. `ResolveRoute` performs the base route resolution only.

## Streaming

```cpp
Request.bStream = true;

Store->ExecuteRouteStreaming(Request, OnChunk, OnComplete);
```

Providers with native streaming emit multiple chunks. Providers without native streaming may emit one final chunk.

Streaming requests use the same concurrency-controlled execution queue as `ExecuteRoute` and `EnqueueRoute`. An interactive streaming call still gets front-of-queue treatment, but it no longer bypasses the subsystem's active-request limit.

## Queue Long Local Jobs

Use `EnqueueRoute` when a local server or model should not receive parallel requests:

```cpp
Store->EnqueueRoute(Request, OnComplete);
```

This is useful for slow local inference jobs or GPU-constrained workstations.

The same queue also guards streaming route execution, so local GPU-backed providers and cloud streams follow one concurrency model.

## Blueprint Route Execution

Blueprint users can call the subsystem functions:

- `Resolve Route`
- `Resolve Route Checked`
- `Execute Route`
- `Execute Route Streaming`
- `Enqueue Route`
- `Get Readiness`
- `Estimate Tokens`
- `Get Cost Report`
- `Export Cost Report CSV`

Use stable `TaskKind` strings instead of hard-coded model names.

## Provider Add-ons

C++ provider add-ons implement:

```text
ILLMProvider
```

Required methods:

```cpp
FString GetProviderType() const;
void BuildHttpRequest(
    const FLLMResolvedRoute& Route,
    const FLLMRequest& In,
    FString& OutVerb,
    FString& OutUrl,
    TMap<FString, FString>& OutHeaders,
    FString& OutBody) const;
FLLMResponse ParseHttpResponse(int32 HttpCode, const FString& Body) const;
```

Blueprint provider add-ons derive from:

```text
ULLMBlueprintProviderAddOn
```

They implement the same conceptual flow:

- return provider type
- build HTTP request
- parse HTTP response

## Embedding Provider Add-ons

C++:

```text
ILLMStoreEmbeddingProvider
```

Blueprint:

```text
ULLMBlueprintEmbeddingProviderAddOn
```

Main methods:

- `GetProviderId`
- `SupportsEmbeddingModel`
- `ExecuteEmbedding`

Embedding routes are separate from chat routes because vector dimensions, normalization, and local-only behavior matter.

## Contract Add-ons

Contracts validate whether a model is suitable for a route or capability.

C++:

```text
ILLMContractAddOn
```

Blueprint:

```text
ULLMBlueprintContractAddOn
```

Example checks:

- model supports structured output
- model has required role
- model offers enough context

## Policy Add-ons

Policies can reject a resolved route before execution.

C++:

```text
ILLMPolicyAddOn
```

Blueprint:

```text
ULLMBlueprintPolicyAddOn
```

Typical rules:

- block cloud for confidential assets
- allow only local providers for shipping workflows
- reject routes above a cost limit
- require a specific provider class for a user role

## Test Add-ons

Test add-ons provide project-specific setup checks.

C++:

```text
ILLMTestAddOn
```

Blueprint:

```text
ULLMBlueprintTestAddOn
```

They can validate provider metadata, model names, expected deployments, or studio conventions.

## Context Provider Add-ons

Context providers supply neutral context packs:

```text
FLLMContextQuery -> FLLMContextPack
```

Use them for:

- project source snippets
- asset metadata
- Blueprint summaries
- local documentation
- RAG search results

LLM Store does not own the domain logic; it only consumes the standardized context.

## Agent Add-ons

Agent add-ons expose external tools such as Codex, Claude, Cursor, or a studio assistant.

C++:

```text
ILLMAgentAddOn
```

Blueprint:

```text
ULLMBlueprintAgentAddOn
```

Main methods:

- `GetStatus`
- `GetAuthenticationDescriptor`
- `SupportsAgentTask`
- `ExecuteAgentTask`

Security flags in `FLLMAgentRequest`:

- `bAllowFileWrites`
- `bAllowShellExecution`
- `bRequireDiffPreview`

Adapters must honor these flags.

## Observer Integration

Implement `ILLMStoreObserver` to react to changes:

- `OnRouteChanged`
- `OnReadinessChanged`
- `OnRuntimeModeChanged`
- `OnProviderAvailabilityChanged`

Register with:

```cpp
Store->RegisterObserver(ObserverObject);
```

Unregister when the object is torn down.

## Blueprint Parity Rule

For buyer-facing integrations, add a Blueprint equivalent when adding a C++ extension point. This keeps the plugin usable by technical artists, designers, and Blueprint-only tools.

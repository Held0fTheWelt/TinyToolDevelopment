Current buyer documentation
===========================

This legacy text file is kept for compatibility. The current buyer-facing
documentation is split into focused Markdown files in this folder:

- README.md            - overview and feature map
- FREEBIE_SCRIPTS.md   - optional Bash helpers for local/internal source customization
- BUYER_GUIDE.md       - explanation for buyers and technical decision makers
- UserManual.md        - full editor workflow manual
- TechnicalOverview.md - architecture, modules, and data flow
- CodeDocumentation.md - source layout and public contracts
- SettingsReference.md - configuration field reference
- ProviderReference.md - provider defaults and setup notes
- RoutePolicyReference.md - route, fallback, and policy reference
- CommandletAndCI.md   - commandlet and CI usage
- FAQ.md               - common buyer and team questions
- ReleaseChecklist.md  - release, packaging, and Fab readiness checklist
- QUICKSTART.md        - first working provider/model/route
- INTEGRATION.md       - C++ and Blueprint integration
- AGENT_AUTHENTICATION.md - agent login dialog and adapter auth descriptors
- SECRET_BACKENDS.md   - encrypted file, Credential Manager, Keychain, 1Password, Azure Key Vault
- COST_TRACKING.md     - cost ledger, reports, and CSV export
- TROUBLESHOOTING.md   - common setup and runtime issues


LLM Store - Documentation
=========================

1. Overview
-----------

The LLM Store is a governance-and-routing layer for Large Language Model (LLM)
access in an Unreal Engine 5.4 project. It separates three concerns:

- Governance config (which providers, models, and task routes exist) lives in a
  committed JSON file.
- Secrets (API keys) live in an encrypted, gitignored on-disk vault, never in
  the JSON.
- Consumer code asks the store to resolve a "task kind" to a concrete
  provider+model+key, or to execute a request end to end, without ever knowing
  the secret directly.

The store is an Engine Subsystem, so it is available in both the editor and at
runtime. Consumer plugins depend only on the ILLMStore facade interface.


2. Modules
----------

- LLMStoreInterface - Public interfaces and POD types. This is the only module a
  consumer needs to depend on for the facade (ILLMStore, FLLMRequest, etc.).
- LLMStore          - The ULLMStoreSubsystem implementation, config, and the
  encrypted secret store.
- LLMStoreEditor    - The editor governance panel and the UI extension slot.


3. Getting the Subsystem
------------------------

The store is a UEngineSubsystem. Obtain it through GEngine:

    #include "LLMStoreSubsystem.h"

    ULLMStoreSubsystem* Store = GEngine->GetEngineSubsystem<ULLMStoreSubsystem>();
    if (!Store)
    {
        return; // engine not yet initialized
    }

If you want to keep consumer code decoupled from the implementation module, you
can hold it as the facade interface instead:

    #include "Interfaces/LLMStoreInterface.h"

    ILLMStore* Store = GEngine->GetEngineSubsystem<ULLMStoreSubsystem>();


4. Resolving a Route
--------------------

ResolveRoute maps a task kind (the route key, e.g. "summarize") to a concrete
FLLMResolvedRoute holding the chosen provider, model, endpoint, and the
decrypted API key. The key is in-memory only and is never serialized.

    // virtual FLLMResult ResolveRoute(const FString& TaskKind,
    //                                 FLLMResolvedRoute& OutResolved) const;

    FLLMResolvedRoute Resolved;
    FLLMResult Result = Store->ResolveRoute(TEXT("summarize"), Resolved);
    if (Result.bSuccess)
    {
        // Resolved.Provider, Resolved.Model, Resolved.Endpoint,
        // Resolved.ApiKey, Resolved.bIsMock
    }
    else
    {
        // Result.ErrorCode is an ELLMResultCode (MissingRoute, MissingModel,
        // MissingProvider, MissingKey, ProviderDisabled, ...), and
        // Result.Message has a human-readable reason.
    }

4.1. Policy-checked resolution
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

ResolveRouteChecked does the same resolution and then runs every registered
policy AddOn against the result. If any policy rejects the route, it returns a
result with ErrorCode == ELLMResultCode::PolicyRejected.

    // FLLMResult ResolveRouteChecked(const FString& TaskKind,
    //                                FLLMResolvedRoute& Out) const;

    FLLMResolvedRoute Resolved;
    FLLMResult Result = Store->ResolveRouteChecked(TEXT("summarize"), Resolved);

Use ResolveRouteChecked when you want governance policies enforced; use
ResolveRoute when you only need the raw mapping.


5. Executing a Route
--------------------

ExecuteRoute performs the resolution and the HTTP call asynchronously. It
invokes the supplied dynamic delegate on the game thread when the request
completes.

    // virtual void ExecuteRoute(const FLLMRequest& Request,
    //                           FLLMResponseDelegate OnComplete);
    //
    // DECLARE_DYNAMIC_DELEGATE_OneParam(FLLMResponseDelegate,
    //                                   const FLLMResponse&, Response);

Because FLLMResponseDelegate is a dynamic delegate, the handler must be a
UFUNCTION on a UObject. Example:

    // In a UObject-derived class header:
    UFUNCTION()
    void HandleLLMResponse(const FLLMResponse& Response);

    // Somewhere in that class:
    void UMyThing::SendPrompt()
    {
        ULLMStoreSubsystem* Store = GEngine->GetEngineSubsystem<ULLMStoreSubsystem>();
        if (!Store) { return; }

        FLLMRequest Request;
        Request.TaskKind     = TEXT("summarize");
        Request.Prompt       = TEXT("Summarize the following text...");
        Request.SystemPrompt = TEXT("You are a concise assistant.");
        // Request.Params is a TMap<FString,FString> for provider-specific options.

        FLLMResponseDelegate OnComplete;
        OnComplete.BindUFunction(this, FName("HandleLLMResponse"));

        Store->ExecuteRoute(Request, OnComplete);
    }

    void UMyThing::HandleLLMResponse(const FLLMResponse& Response)
    {
        if (Response.Result.bSuccess)
        {
            // Response.Content  - parsed text content
            // Response.RawBody  - raw HTTP body
            // Response.ModelId  - the model that produced the response
        }
        else
        {
            // Response.Result.ErrorCode / Response.Result.Message
        }
    }


6. Observers
------------

Implement ILLMStoreObserver on a UObject to be notified of governance changes,
then register and unregister it with the store.

    // virtual void RegisterObserver(UObject* Observer);
    // virtual void UnregisterObserver(UObject* Observer);

The observer interface (BlueprintNativeEvent functions) is:

    void OnRouteChanged(const FString& TaskKind);
    void OnReadinessChanged(const FLLMReadiness& Readiness);
    void OnRuntimeModeChanged(const FLLMRuntimeModes& Modes);
    void OnProviderAvailabilityChanged(const FString& ProviderId, bool bAvailable);

Native example:

    // Header:
    UCLASS()
    class UMyObserver : public UObject, public ILLMStoreObserver
    {
        GENERATED_BODY()
    public:
        virtual void OnReadinessChanged_Implementation(
            const FLLMReadiness& Readiness) override;
    };

    // Registration:
    Store->RegisterObserver(MyObserver);
    // ... later:
    Store->UnregisterObserver(MyObserver);

The store holds observers as weak pointers and purges stale entries on notify,
but you should still unregister explicitly when your object is torn down.

6.1. Built-in Providers
~~~~~~~~~~~~~~~~~~~~~~~

The store ships with these provider Type strings:

    openai       - OpenAI chat completions, BaseUrl normally https://api.openai.com/v1
    ollama       - Local Ollama API, default http://127.0.0.1:11434, no key by default
    lmstudio     - LM Studio local server, OpenAI-compatible, default http://127.0.0.1:1234/v1, no key by default
    vllm         - vLLM OpenAI-compatible server, default http://127.0.0.1:8000/v1, no key by default
    tgi          - Hugging Face Text Generation Inference OpenAI-compatible server, default http://127.0.0.1:8080/v1, no key by default
    llamacpp     - llama.cpp llama-server OpenAI-compatible API, no key by default
    anthropic    - Anthropic Messages API, key required by default
    gemini       - Google Gemini generateContent API, key required by default
    azure-openai - Azure OpenAI deployment chat completions, key required by default
    mistral      - Mistral chat completions, key required by default
    openrouter   - OpenRouter chat completions, key required by default
    mock         - Built-in mock response provider, no key

Set Provider.Meta["RequiresApiKey"] = "false" if a gateway or internal proxy
should be treated as keyless. Cloud providers require keys by default; local
providers do not.

The local OpenAI-compatible providers normalize BaseUrl values with or without
/v1 and post to /v1/chat/completions. Ollama posts to /api/chat. Anthropic,
Gemini, and Azure OpenAI use their native request formats and headers.

6.2. Built-in llama.cpp Provider
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The built-in provider type "llamacpp" targets the llama.cpp llama-server
OpenAI-compatible HTTP API. Start a local server, for example:

    llama-server -m C:\Models\model.gguf --host 127.0.0.1 --port 8080

Then create a Provider with:

    Id      = local-llama
    Type    = llamacpp
    BaseUrl = http://127.0.0.1:8080

BaseUrl may also include /v1, e.g. http://127.0.0.1:8080/v1. The provider
normalizes both forms to POST /v1/chat/completions.

No API key is required for "llamacpp" by default. If your local server is
behind a gateway that expects bearer auth, you may still set a provider key;
the Authorization header is sent only when a key exists.

Model.Name is sent as the OpenAI-compatible "model" value. If it is empty,
Model.Id is used instead. Request.Params entries are forwarded into the JSON
request body as strings, numbers, or booleans. ExecuteRouteStreaming sets
Request.bStream and emits a stream chunk callback; providers that only return
a full response emit one final chunk.

6.3. Store Capabilities
~~~~~~~~~~~~~~~~~~~~~~~

FLLMRequest now carries an Operation:

    Chat       - normal prompt/chat completion
    Embedding  - embedding route; Inputs or Prompt become provider input
    Rerank     - reranking route; Prompt is the query, Inputs are documents

OpenAI-compatible providers build /v1/chat/completions, /v1/embeddings and
/v1/rerank requests. Ollama supports /api/chat and /api/embed. Responses can
carry text, embeddings, rerank results, usage/cost metadata and tool-call JSON.

Structured output is represented by FLLMStructuredOutputSpec on the request.
The store validates that returned content is JSON and checks RequiredFields;
if JsonSchema contains a top-level "required" array, those fields are checked
as well. OpenAI-compatible requests serialize response_format hints.

Tool calling is represented by FLLMToolSpec. OpenAI-compatible providers
serialize tools as function definitions and parse returned tool_calls into
FLLMResponse.ToolCallJson.

Execution features:

    ExecuteRouteStreaming - streaming-friendly callback path
    EnqueueRoute          - serialized request queue for long local jobs
    RetryCount            - per-provider retry count
    TimeoutSeconds        - per-provider timeout override
    CircuitBreaker...     - per-provider failure threshold and cooldown
    FallbackModelIds      - ordered multi-model fallback chain
    bUseCache             - response cache keyed by route/model/prompt/params
    CostRules             - estimated cost per provider/model
    EstimateTokens        - lightweight budgeting heuristic
    PromptTemplates       - {{variable}} and {variable} rendering

6.4. Governance and Editor
~~~~~~~~~~~~~~~~~~~~~~~~~~

The editor panel includes:

    Provider Health - latency, last error, availability and circuit state
    Audit Log       - recent task/model/provider/cost/cache events
    Test Route      - route-level probe in addition to provider/model tests
    Route Policy    - local-only, allow-cloud, max context, max cost
    Presets         - export/import JSON presets under Saved/LLMStore/Presets
    Cache           - clear response cache button

Build rules live in FLLMBuildConfigRule. For example, a Shipping rule can set
bRequireLocalOrMock=true or bAllowCloud=false so readiness and CI reject cloud
routes. Secret backend selection is stored in FLLMSecretBackendConfig; the
encrypted file backend remains the built-in implementation, while env vars
continue to override any stored key.

6.5. CI Policy
~~~~~~~~~~~~~~

CI can run the commandlet:

    UnrealEditor-Cmd.exe Project.uproject -run=LLMStoreCIPolicy -Config=Shipping

It loads Config/LLMStore.json and returns a non-zero exit code when configured
BuildRules reject any enabled route/provider combination.

Domain-specific route factories are intentionally not part of this plugin.
Project/indexing plugins can expose content through ILLMContextProviderAddOn and
then use MakeContextRequest to produce FLLMRequest objects against the store's
neutral routing API.


7. Writing and Registering AddOns
---------------------------------

AddOns are plain C++ classes that implement one of the AddOn interfaces. You
register an instance as a TSharedRef on the subsystem. Register early (e.g. in
your module's StartupModule) so the store sees them.

7.1. Provider AddOn (ILLMProvider)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

A provider implementation handles a provider Type string (e.g. "openai") and
knows how to build and parse the HTTP request for that wire format.

    class FMyProvider : public ILLMProvider
    {
    public:
        virtual FString GetProviderType() const override { return TEXT("myapi"); }

        virtual void BuildHttpRequest(const FLLMResolvedRoute& Route,
            const FLLMRequest& In, FString& OutVerb, FString& OutUrl,
            TMap<FString,FString>& OutHeaders, FString& OutBody) const override
        {
            OutVerb = TEXT("POST");
            OutUrl  = Route.Endpoint;
            OutHeaders.Add(TEXT("Authorization"),
                FString::Printf(TEXT("Bearer %s"), *Route.ApiKey));
            OutHeaders.Add(TEXT("Content-Type"), TEXT("application/json"));
            OutBody = /* serialize In.Prompt etc. */ FString();
        }

        virtual FLLMResponse ParseHttpResponse(int32 HttpCode,
            const FString& Body) const override
        {
            FLLMResponse Out;
            // fill Out.Result, Out.Content, Out.RawBody, Out.ModelId
            return Out;
        }
    };

    // Register:
    Store->RegisterProviderAddOn(MakeShared<FMyProvider>());
    // Unregister with the same TSharedRef:
    Store->UnregisterProviderAddOn(ProviderRef);

7.2. Contract AddOn (ILLMContractAddOn)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

A contract validates a model configuration. It contributes to readiness.

    class FMyContract : public ILLMContractAddOn
    {
    public:
        virtual FString GetContractName() const override { return TEXT("requires-structured"); }

        virtual bool ValidateModel(const FLLMModelConfig& Model,
            FString& OutReason) const override
        {
            if (!Model.bStructured)
            {
                OutReason = TEXT("model must support structured output");
                return false;
            }
            return true;
        }
    };

    Store->RegisterContractAddOn(MakeShared<FMyContract>());
    Store->UnregisterContractAddOn(ContractRef);

7.3. Policy AddOn (ILLMPolicyAddOn)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

A policy gates a resolved route. ResolveRouteChecked runs all registered
policies; a rejection produces ELLMResultCode::PolicyRejected.

    class FMyPolicy : public ILLMPolicyAddOn
    {
    public:
        virtual FString GetPolicyName() const override { return TEXT("no-external-cloud"); }

        virtual bool AllowRoute(const FLLMResolvedRoute& Route,
            FString& OutReason) const override
        {
            if (Route.Provider.Type != TEXT("ollama"))
            {
                OutReason = TEXT("only local providers are allowed");
                return false;
            }
            return true;
        }
    };

    Store->RegisterPolicyAddOn(MakeShared<FMyPolicy>());
    Store->UnregisterPolicyAddOn(PolicyRef);

7.4. Context Provider AddOn (ILLMContextProviderAddOn)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

A context provider supplies domain-specific context without the store depending
on that domain plugin. BuildContextPack asks registered providers for a neutral
FLLMContextPack; MakeContextRequest turns that pack into a normal FLLMRequest.

    class FMyContextProvider : public ILLMContextProviderAddOn
    {
    public:
        virtual FString GetContextProviderName() const override
        {
            return TEXT("my-project-index");
        }

        virtual bool BuildContextPack(const FLLMContextQuery& Query,
            FLLMContextPack& OutContextPack, FString& OutReason) const override
        {
            // Fill OutContextPack.Chunks from your project's index/search layer.
            return true;
        }
    };

    Store->RegisterContextProviderAddOn(MakeShared<FMyContextProvider>());
    Store->UnregisterContextProviderAddOn(ContextProviderRef);

7.5. Test AddOn (ILLMTestAddOn)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

A test AddOn runs a synchronous structural check on a provider/model pair.
(Network reachability/auth tests use the async TestConnection/TestModel path on
the subsystem instead.)

    class FMyTest : public ILLMTestAddOn
    {
    public:
        virtual FString GetTestName() const override { return TEXT("has-base-url"); }

        virtual bool RunTest(const FLLMProviderConfig& Provider,
            const FLLMModelConfig& Model, FString& OutReason) const override
        {
            if (Provider.BaseUrl.IsEmpty())
            {
                OutReason = TEXT("provider has no BaseUrl");
                return false;
            }
            return true;
        }
    };

    Store->RegisterTestAddOn(MakeShared<FMyTest>());
    Store->UnregisterTestAddOn(TestRef);


8. Editor UI Extension
----------------------

AddOns can append their own section to the bottom of the governance panel by
implementing ILLMStoreUIExtension and registering it with the editor module
(FLLMStoreEditorModule). The panel reads the live registry when it is
constructed, so register before the tab is opened (e.g. at module startup).

    #include "ILLMStoreUIExtension.h"
    #include "LLMStoreEditorModule.h"
    #include "Modules/ModuleManager.h"

    class FMyUIExtension : public ILLMStoreUIExtension
    {
    public:
        virtual FString GetSectionTitle() const override { return TEXT("My AddOn"); }
        virtual TSharedRef<SWidget> BuildSection() override
        {
            return SNew(STextBlock).Text(FText::FromString(TEXT("My section content")));
        }
    };

    // Register (the editor module name is "LLMStoreEditor"):
    if (FLLMStoreEditorModule* Editor =
            FModuleManager::GetModulePtr<FLLMStoreEditorModule>("LLMStoreEditor"))
    {
        Editor->RegisterUIExtension(MakeShared<FMyUIExtension>());
        // Editor->UnregisterUIExtension(ExtensionRef);
    }


9. Configuration vs. Secrets
----------------------------

The store keeps a hard split between committed governance config and secrets.

9.1. Committed governance config
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The provider/model/route/runtime-mode config is serialized as JSON to:

    <Project>/Config/LLMStore.json

This file is meant to be committed to source control. It contains NO API keys.
The path is returned by FLLMStoreConfig::GetConfigFilePath().

9.2. Secrets
~~~~~~~~~~~~~

API keys are stored, encrypted, in a separate on-disk vault under the project's
Saved directory:

    <Project>/Saved/LLMStore/secrets.bin

This file is gitignored and must NEVER be committed. API keys are never written
into LLMStore.json. Read and write keys through the subsystem:

    FString Key = Store->GetProviderKey(TEXT("openai"));
    Store->SetProviderKey(TEXT("openai"), TEXT("sk-..."));   // sets + flushes to disk

9.3. Environment variable override
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

For each provider, an environment variable can override the stored key. The
variable name is the provider Id uppercased, wrapped as:

    LLMSTORE_<PROVIDERID>_KEY

For example, a provider with Id "openai" is overridden by the env var
LLMSTORE_OPENAI_KEY. When the env var is set, it takes precedence over whatever
is in secrets.bin. This is useful for CI and for keeping keys out of any file on
developer machines.


10. The Editor Governance Panel
-------------------------------

Open the panel from the editor's Window / Tools menu, under the "LLM Store"
entry (it is registered in the Tools category of the workspace menu).

The panel is organized top to bottom into these sections:

- Readiness banner    - A severity-coloured headline plus the current list of
  blockers, computed from config + secrets + contract AddOns. Severity is 0 (ok),
  1 (warn), or 2 (blocked).
- Provider section    - List of providers with an edit form and
  Save / Create / Test / Delete actions. "Test" runs an async connection test
  against the provider.
- Model section       - List of models with an edit form and
  Save / Create / Test / Delete actions. "Test" runs an async model test.
- Route section       - Task routes mapping a TaskKind to preferred / fallback /
  mock models.
- Runtime modes       - Edit form for the runtime modes (generation, retrieval,
  validation, runtime profile) with a Save action.
- AddOn sections      - Any registered ILLMStoreUIExtension sections appended at
  the bottom.

Editing in the panel updates the in-memory config, saves LLMStore.json, and
notifies registered observers. Setting a provider key writes it to the encrypted
secret store, not to the JSON.


11. Type Reference (quick)
--------------------------

- FLLMRequest       - TaskKind, Prompt, SystemPrompt, Params (TMap).
- FLLMResponse      - Result, Content, RawBody, ModelId.
- FLLMResult        - bSuccess, ErrorCode (ELLMResultCode), Message.
- FLLMResolvedRoute - Provider, Model, Endpoint, ApiKey (in-memory only), bIsMock.
- FLLMReadiness     - Severity, Headline, Blockers, Inventory.
- FLLMProviderConfig- Id, DisplayName, Type, BaseUrl, bEnabled, Meta.
- FLLMModelConfig   - Id, Name, DisplayName, ProviderId, Role, bStructured,
  TimeoutSeconds, bEnabled.
- FLLMTaskRoute     - TaskKind, PreferredModelId, FallbackModelId, MockModelId,
  bUseMock, WorkflowScope, bEnabled.
- FLLMRuntimeModes  - GenerationMode, RetrievalMode, ValidationMode, RuntimeProfile.

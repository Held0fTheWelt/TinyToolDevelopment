# Settings Reference

This reference describes the main configuration data used by LLM Store.

Project configuration path:

```text
Config/LLMStore.json
```

Secrets are not stored in this file.

## Setup JSON Files

The Governance UI can export, validate, and import setup JSON files from any selected folder.

The exported wrapper format contains:

| Field | Meaning |
| --- | --- |
| `Format` | `LLMStoreSetup`. |
| `FormatVersion` | Setup JSON format version. |
| `SetupName` | Human-readable setup name. |
| `ExportedUtc` | UTC export timestamp. |
| `Config` | Nested `FLLMStoreConfig` object. |

Import also accepts a raw `FLLMStoreConfig` JSON object for compatibility.

## FLLMStoreConfig

| Field | Type | Meaning |
| --- | --- | --- |
| `Providers` | `TArray<FLLMProviderConfig>` | Known providers. |
| `Models` | `TArray<FLLMModelConfig>` | Models served by providers. |
| `Routes` | `TArray<FLLMTaskRoute>` | Chat/tool/rerank task routes. |
| `EmbeddingRoutes` | `TArray<FLLMStoreEmbeddingRoute>` | Embedding-specific routes. |
| `RoutePolicies` | `TArray<FLLMRoutePolicy>` | Global or task-specific policies. |
| `PromptTemplates` | `TArray<FLLMPromptTemplate>` | Reusable prompt templates. |
| `CostRules` | `TArray<FLLMCostRule>` | Pricing rules for cost tracking. |
| `BuildRules` | `TArray<FLLMBuildConfigRule>` | Governance per build configuration. |
| `SecretBackend` | `FLLMSecretBackendConfig` | Active secret backend. |
| `Modes` | `FLLMRuntimeModes` | Runtime profile labels. |

## FLLMProviderConfig

| Field | Meaning |
| --- | --- |
| `Id` | Stable project-local provider key. |
| `DisplayName` | Human-readable UI/report name. |
| `Type` | Provider type such as `openai`, `ollama`, or `llamacpp`. |
| `BaseUrl` | Server or API endpoint. |
| `bEnabled` | Disables provider without deleting it. |
| `Meta` | Provider-specific metadata, for example Azure deployment names. |
| `RetryCount` | Retries for transient errors. |
| `TimeoutSeconds` | Provider-specific timeout; `0` uses defaults. |
| `CircuitBreakerFailureThreshold` | Failure count before circuit opens. |
| `CircuitBreakerCooldownSeconds` | Cooldown before retry after circuit open. |

## FLLMModelConfig

| Field | Meaning |
| --- | --- |
| `Id` | Stable project-local model key. |
| `Name` | Provider-side model name. |
| `DisplayName` | Human-readable UI name. |
| `ProviderId` | Reference to `FLLMProviderConfig.Id`. |
| `Role` | Optional role such as `fast`, `reasoning`, `local`, or `embedding`. |
| `bStructured` | Model is expected to handle structured JSON output well. |
| `TimeoutSeconds` | Model-specific timeout. |
| `bEnabled` | Disables model without deleting it. |

## FLLMTaskRoute

| Field | Meaning |
| --- | --- |
| `TaskKind` | Stable task name, for example `docs.summarize`. |
| `PreferredModelId` | First model tried by this route. |
| `FallbackModelId` | Legacy single fallback. |
| `FallbackModelIds` | Ordered fallback chain. |
| `MockModelId` | Model used for mock mode. |
| `bUseMock` | Forces mock usage. |
| `WorkflowScope` | Optional scope such as `Editor`, `CI`, or `Runtime`. |
| `PromptTemplateId` | Default template for this route. |
| `Policy` | Route-specific policy. |
| `bEnabled` | Disables route. |

## FLLMRoutePolicy

| Field | Meaning |
| --- | --- |
| `TaskKind` | Empty can be used by tooling as global; otherwise task-specific. |
| `bAllowCloud` | Cloud provider types may be used. |
| `bLocalOnly` | Only local or mock providers are allowed. |
| `MaxContextTokens` | Maximum context budget; `0` disables the limit. |
| `MaxEstimatedCost` | Maximum estimated request cost; `0` disables the limit. |
| `AllowedProviderTypes` | Provider type allow list. |
| `DeniedProviderTypes` | Provider type deny list. |

## FLLMStoreEmbeddingRoute

| Field | Meaning |
| --- | --- |
| `RouteId` | Stable embedding route id. |
| `TaskKind` | Task, for example `docs.embed`. |
| `ProviderId` | Embedding provider. |
| `ModelId` | Embedding model. |
| `Dimensions` | Expected vector dimension; `0` means provider default. |
| `bEnabled` | Route is active. |
| `bLocalOnly` | Prefer or require local execution. |
| `bAllowFallback` | Fallback routes may be used. |
| `FallbackRouteIds` | Embedding fallback routes. |
| `AllowedRuntimeModes` | Optional runtime profile allow list. |

## FLLMCostRule

| Field | Meaning |
| --- | --- |
| `ProviderType` | Provider type covered by the rule. |
| `ModelId` | Optional model id; empty applies broadly. |
| `InputCostPer1KTokens` | Price per 1000 prompt tokens. |
| `OutputCostPer1KTokens` | Price per 1000 completion tokens. |
| `Currency` | Currency label, default `USD`. |

## FLLMSecretBackendConfig

| Field | Meaning |
| --- | --- |
| `Backend` | `EncryptedFile`, `WindowsCredentialManager`, `MacOSKeychain`, `OnePassword`, or `AzureKeyVault`. |
| `Vault` | Backend-specific vault, keychain, or namespace name. |
| `KeyPrefix` | Prefix for generated secret names. |
| `Meta` | Backend-specific provider overrides. |

## FLLMBuildConfigRule

| Field | Meaning |
| --- | --- |
| `BuildConfiguration` | Unreal configuration such as `Development`, `Test`, or `Shipping`. |
| `bAllowCloud` | Cloud providers are allowed in this configuration. |
| `bRequireLocalOrMock` | Each route must have a local or mock path. |
| `AllowedProviderTypes` | Provider types allowed in this configuration. |

## FLLMRuntimeModes

| Field | Meaning |
| --- | --- |
| `GenerationMode` | Free label such as `Local`, `Hybrid`, or `Cloud`. |
| `RetrievalMode` | Free label for retrieval/RAG behavior. |
| `ValidationMode` | Free label for validation/review behavior. |
| `RuntimeProfile` | Overall profile such as `LocalOnly`, `OpenAICloud`, or `Hybrid`. |

## FLLMPromptTemplate

| Field | Meaning |
| --- | --- |
| `Id` | Template key. |
| `Description` | Description for UI and team members. |
| `Template` | Prompt text with variables. |
| `Variables` | Expected variable names. |

## Team Recommendations

- Commit `Config/LLMStore.json`.
- Do not commit API keys.
- Use `SecretBackend` to make team expectations visible.
- Use `BuildRules` to catch shipping mistakes early.
- Add `CostRules` before productive cloud use.
- Document each production route with owner, purpose, and data class.

## Editor Developer Settings

Editor-only preferences live under **Project Settings -> Plugins -> LLM Store** and are stored separately from `Config/LLMStore.json`.

| Field | Default | Meaning |
| --- | --- | --- |
| `MaxJobHistoryCount` | `50` | Maximum recent panel/job records retained for editor history and UCM job endpoints. |
| `DefaultPanelPage` | `Setup` | Panel page shown when LLM Store opens. |
| `bAutoOpenPanelOnStartup` | `false` | Opens the panel automatically when the editor module starts. |
| `bRunValidationOnReload` | `false` | Runs the validation readiness check after config reload. |


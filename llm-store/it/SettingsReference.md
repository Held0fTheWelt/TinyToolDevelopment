<!-- doc-provenance: AKDB:plugins/LLMStore/architecture.md; docs/architecture/plugins/LLMStore/product-facts.yml; reconciled 2026-06-20 -->
# Riferimento delle impostazioni

Questo riferimento descrive i principali dati di configurazione utilizzati da LLM Store.

Percorso di configurazione del progetto:

```text
Config/LLMStore.json
```

I segreti non sono salvati in questo file.

## File JSON di configurazione

L'interfaccia utente della Governance può esportare, validare e importare file JSON di configurazione da qualsiasi cartella selezionata.

Il formato racchiuso esportato contiene:

| Campo | Significato |
| --- | --- |
| `Format` | `LLMStoreSetup`. |
| `FormatVersion` | Versione del formato JSON di configurazione. |
| `SetupName` | Nome della configurazione leggibile dall'utente. |
| `ExportedUtc` | Timestamp UTC dell'esportazione. |
| `Config` | Oggetto `FLLMStoreConfig` annidato. |

L'importatore accetta anche un oggetto JSON `FLLMStoreConfig` grezzo per compatibilità.

## FLLMStoreConfig

| Campo | Tipo | Significato |
| --- | --- | --- |
| `Providers` | `TArray<FLLMProviderConfig>` | Provider noti. |
| `Models` | `TArray<FLLMModelConfig>` | Modelli forniti dai provider. |
| `Routes` | `TArray<FLLMTaskRoute>` | Route per attività di chat/tool/rerank. |
| `EmbeddingRoutes` | `TArray<FLLMStoreEmbeddingRoute>` | Route specifiche per gli embedding. |
| `RoutePolicies` | `TArray<FLLMRoutePolicy>` | Criteri globali o specifici per attività. |
| `PromptTemplates` | `TArray<FLLMPromptTemplate>` | Modelli di prompt riutilizzabili. |
| `CostRules` | `TArray<FLLMCostRule>` | Regole di prezzo per il tracciamento dei costi. |
| `BuildRules` | `TArray<FLLMBuildConfigRule>` | Governance per configurazione di build. |
| `SecretBackend` | `FLLMSecretBackendConfig` | Backend dei segreti attivo. |
| `Modes` | `FLLMRuntimeModes` | Etichette del profilo runtime. |

## FLLMProviderConfig

| Campo | Significato |
| --- | --- |
| `Id` | Chiave del provider stabile e locale al progetto. |
| `DisplayName` | Nome leggibile in UI/report. |
| `Type` | Tipo di provider come `openai`, `ollama` o `llamacpp`. |
| `BaseUrl` | Endpoint del server o dell'API. |
| `bEnabled` | Disabilita il provider senza eliminarlo. |
| `Meta` | Metadati specifici del provider, ad es. nomi dei deployment Azure. |
| `RetryCount` | Tentativi di rientro per errori temporanei. |
| `TimeoutSeconds` | Timeout specifico del provider; `0` usa i valori predefiniti. |
| `CircuitBreakerFailureThreshold` | Numero di errori prima dell'apertura del salvavita. |
| `CircuitBreakerCooldownSeconds` | Tempo di raffreddamento prima di riprovare dopo l'apertura. |

## FLLMModelConfig

| Campo | Significato |
| --- | --- |
| `Id` | Chiave del modello stabile e locale al progetto. |
| `Name` | Nome del modello lato provider. |
| `DisplayName` | Nome leggibile nell'interfaccia utente. |
| `ProviderId` | Riferimento a `FLLMProviderConfig.Id`. |
| `Role` | Ruolo opzionale come `fast`, `reasoning`, `local` o `embedding`. |
| `bStructured` | Il modello è previsto per gestire bene output JSON strutturati. |
| `TimeoutSeconds` | Timeout specifico del modello. |
| `bEnabled` | Disabilita il modello senza eliminarlo. |

## FLLMTaskRoute

| Campo | Significato |
| --- | --- |
| `TaskKind` | Nome di attività stabile, ad es. `docs.summarize`. |
| `PreferredModelId` | Primo modello tentato da questa route. |
| `FallbackModelId` | Singolo fallback legacy. |
| `FallbackModelIds` | Catena di fallback ordinata. |
| `MockModelId` | Modello utilizzato per la modalità mock. |
| `bUseMock` | Forza l'uso del mock. |
| `WorkflowScope` | Ambito opzionale come `Editor`, `CI` o `Runtime`. |
| `PromptTemplateId` | Modello predefinito per questa route. |
| `Policy` | Criterio specifico della route. |
| `bEnabled` | Disabilita la route. |

## FLLMRoutePolicy

| Campo | Significato |
| --- | --- |
| `TaskKind` | Vuoto può essere usato dagli strumenti come globale; altrimenti specifico dell'attività. |
| `bAllowCloud` | I tipi di provider cloud possono essere utilizzati. |
| `bLocalOnly` | Sono consentiti solo provider locali o mock. |
| `MaxContextTokens` | Budget di contesto massimo; `0` disabilita il limite. |
| `MaxEstimatedCost` | Costo stimato massimo per richiesta; `0` disabilita il limite. |
| `AllowedProviderTypes` | Elenco di consenti dei tipi di provider. |
| `DeniedProviderTypes` | Elenco di nega dei tipi di provider. |

## FLLMStoreEmbeddingRoute

| Campo | Significato |
| --- | --- |
| `RouteId` | ID della route di embedding stabile. |
| `TaskKind` | Attività, ad es. `docs.embed`. |
| `ProviderId` | Provider di embedding. |
| `ModelId` | Modello di embedding. |
| `Dimensions` | Dimensione vettoriale prevista; `0` significa il valore predefinito del provider. |
| `bEnabled` | La route è attiva. |
| `bLocalOnly` | Prediligi o richiedi l'esecuzione locale. |
| `bAllowFallback` | Le route di fallback possono essere utilizzate. |
| `FallbackRouteIds` | Route di fallback per l'embedding. |
| `AllowedRuntimeModes` | Elenco di consenti opzionale dei profili runtime. |

## FLLMCostRule

| Campo | Significato |
| --- | --- |
| `ProviderType` | Tipo di provider coperto dalla regola. |
| `ModelId` | ID del modello opzionale; vuoto si applica ampiamente. |
| `InputCostPer1KTokens` | Prezzo per 1000 token di prompt. |
| `OutputCostPer1KTokens` | Prezzo per 1000 token di completamento. |
| `Currency` | Etichetta valuta, predefinito `USD`. |

## FLLMSecretBackendConfig

| Campo | Significato |
| --- | --- |
| `Backend` | `EncryptedFile`, `WindowsCredentialManager`, `MacOSKeychain`, `OnePassword` o `AzureKeyVault`. |
| `Vault` | Vault, portachiavi o nome namespace specifico del backend. |
| `KeyPrefix` | Prefisso per i nomi dei segreti generati. |
| `Meta` | Sostituzioni di provider specifiche del backend. |

## FLLMBuildConfigRule

| Campo | Significato |
| --- | --- |
| `BuildConfiguration` | Configurazione Unreal come `Development`, `Test` o `Shipping`. |
| `bAllowCloud` | I provider cloud sono consentiti in questa configurazione. |
| `bRequireLocalOrMock` | Ogni route deve avere un percorso locale o mock. |
| `AllowedProviderTypes` | Tipi di provider consentiti in questa configurazione. |

## FLLMRuntimeModes

| Campo | Significato |
| --- | --- |
| `GenerationMode` | Etichetta libera come `Local`, `Hybrid` o `Cloud`. |
| `RetrievalMode` | Etichetta libera per il comportamento di retrieval/RAG. |
| `ValidationMode` | Etichetta libera per il comportamento di validazione/revisione. |
| `RuntimeProfile` | Profilo complessivo come `LocalOnly`, `OpenAICloud` o `Hybrid`. |

## FLLMPromptTemplate

| Campo | Significato |
| --- | --- |
| `Id` | Chiave del modello. |
| `Description` | Descrizione per l'interfaccia utente e i membri del team. |
| `Template` | Testo del prompt con variabili. |
| `Variables` | Nomi delle variabili previste. |

## Raccomandazioni per il team

- Invia al repository `Config/LLMStore.json`.
- Non inviare le chiavi API.
- Usa `SecretBackend` per rendere visibili le aspettative del team.
- Usa `BuildRules` per individuare tempestivamente gli errori per la distribuzione.
- Aggiungi `CostRules` prima dell'uso effettivo del cloud.
- Documenta ogni route di produzione con responsabile, scopo e classe di dati.

## Impostazioni sviluppatore dell'editor

Le preferenze dell'editor risiedono in **Editor Settings -> Plugins -> LLM Store** e sono salvate separatamente da `Config/LLMStore.json`.

| Campo | Predefinito | Significato |
| --- | --- | --- |
| `MaxJobHistoryCount` | `50` | Numero massimo di record di pannello/job conservati per la cronologia dell'editor e gli endpoint dei job UCM. |
| `DefaultPanelPage` | `Setup` | Pagina del pannello mostrata all'apertura di LLM Store. |
| `bAutoOpenPanelOnStartup` | `false` | Apre automaticamente il pannello all'avvio del modulo dell'editor. |
| `bRunValidationOnReload` | `false` | Esegue il controllo di idoneità della validazione dopo il ricaricamento della configurazione. |

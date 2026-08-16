<!-- doc-provenance: AKDB:plugins/LLMStore/architecture.md; docs/architecture/plugins/LLMStore/product-facts.yml; reconciled 2026-06-20 -->
# Manuale utente

Questo manuale descrive LLM Store dalla prospettiva di un acquirente, artist tecnico, sviluppatore Blueprint o programmatore di strumenti. Spiega i flussi di lavoro dell'editor e fornisce riferimenti tecnici più approfonditi ove utile.

## Obiettivo del plugin

LLM Store è un livello di controllo IA centralizzato per i progetti Unreal Engine. Gli altri plugin e strumenti non devono sapere se un prompt viene inviato a Ollama, llama.cpp, OpenAI, Claude, Gemini, Azure OpenAI, Mistral, OpenRouter o a un mock. Essi chiamano una route di attività stabile come:

```text
docs.summarize
asset.explain
naming.review
rag.embed
agent.patch
```

La route stabilisce il provider, il modello, il fallback, il criterio, la regola di costo e il backend dei segreti.

## Aprire l'editor

Apri:

```text
Tiny Tools -> LLM Store
```

La scheda è progettata per l'uso quotidiano. Non mostra soltanto le impostazioni grezze; guida la configurazione, le route, lo stato, la guida, gli agenti, i costi e la governance.

## Prima configurazione

### Scheda Quick-Start (percorso più rapido)

1. Apri `Tiny Tools -> LLM Store`.
2. Vai su `Setup`. La sezione **Quick Start — get running in one click** si trova in alto.
3. Scegli una delle opzioni:
   - **Just try it (Mock)** — completamente offline; nessuna chiave API; ideale per CI e primo contatto.
   - **Local (Ollama)** — crea `quickstart_ollama` su `localhost:11434`; avvia Ollama prima di testare.
   - **Create OpenAI** o **Create Anthropic** — incolla una chiave API nel campo password, quindi fai clic sul pulsante del fornitore. La chiave viene salvata solo nel backend dei segreti.
4. Leggi la riga di stato sotto i pulsanti e il banner di idoneità sopra le schede.
5. Se l'idoneità è verde, espandi di nuovo la sezione Quick-Start solo se necessiti di un altro stack iniziale (le voci `quickstart_*` esistenti non vengono duplicate; la tua route `default` non viene mai sovrascritta).

Gli stack iniziali usano ID stabili (`quickstart_mock`, `quickstart_ollama`, `quickstart_openai`, `quickstart_anthropic`) e collegano sempre una route di attività `default` a meno che tu non l'abbia già definita.

### Configurazione manuale (controllo completo)

1. Apri `Tiny Tools -> LLM Store`.
2. Vai su `Setup` (sotto la scheda Quick-Start).
3. Crea un provider, ad esempio `ollama`, `llamacpp`, `openai` o `anthropic`.
4. Conferma che l'URL di base predefinita sia adeguata.
5. Crea un modello per il provider.
6. Vai su `Routes`.
7. Crea una route, ad esempio `docs.summarize`.
8. Scegli il modello preferito.
9. Fai clic su `Test Route`.
10. Controlla `Status` per avvisi o blocchi.

## Configurazione del provider

Un provider descrive il servizio tecnico, non il modello stesso.

| Campo | Significato |
| --- | --- |
| `Id` | ID stabile locale al progetto, ad es. `local-ollama`. |
| `DisplayName` | Nome leggibile nell'interfaccia e nei report. |
| `Type` | Tipo di provider come `ollama`, `llamacpp` o `openai`. |
| `BaseUrl` | Endpoint HTTP. I provider noti ricevono valori predefiniti utili. |
| `Enabled` | Disabilita il provider senza eliminarne le impostazioni. |
| `RetryCount` | Tentativi di rientro per errori temporanei. |
| `TimeoutSeconds` | Timeout specifico del provider. |
| `CircuitBreaker...` | Protezione contro errori ripetuti o server bloccati. |

I provider locali normalmente non richiedono chiavi. I provider cloud richiedono solitamente una chiave nello store dei segreti.

## Provider noti

| Tipo di provider | URL di base predefinita | Uso tipico |
| --- | --- | --- |
| `ollama` | `http://localhost:11434` | Modelli locali tramite Ollama. |
| `llamacpp` | `http://localhost:8080` | Inferenza server llama.cpp locale. |
| `lmstudio` | `http://localhost:1234/v1` | Modelli LM Studio locali. |
| `vllm` | `http://localhost:8000/v1` | Inferenza ad alte prestazioni locale o su server. |
| `tgi` | `http://localhost:8080` | Hugging Face Text Generation Inference. |
| `openai` | `https://api.openai.com/v1` | API OpenAI. |
| `anthropic` | `https://api.anthropic.com` | API Claude. |
| `gemini` | `https://generativelanguage.googleapis.com/v1beta` | API Google Gemini. |
| `azure-openai` | specifico per il progetto | Endpoint Azure e logica di deployment. |
| `mistral` | `https://api.mistral.ai/v1` | API Mistral. |
| `openrouter` | `https://openrouter.ai/api/v1` | Router per molti modelli cloud. |
| `mock` | vuoto | Test, sviluppo UI, CI e lavoro offline. |

## Modelli

Un modello appartiene a un solo provider.

| Campo | Significato |
| --- | --- |
| `Id` | ID modello stabile locale al progetto. |
| `Name` | Nome di rete del provider, ad es. `llama3.1:8b` o `gpt-4o-mini`. |
| `ProviderId` | Provider che fornisce il modello. |
| `Role` | Ruolo opzionale come `fast`, `reasoning`, `embedding` o `local`. |
| `Structured` | Contrassegna i modelli previsti per gestire bene l'output JSON/schema. |
| `TimeoutSeconds` | Timeout specifico del modello. |
| `Enabled` | Disabilita il modello senza eliminare le route. |

## Route

Le route sono il concetto più importante dello store. Una funzionalità richiede un'attività, non un modello.

Esempio:

```text
TaskKind: docs.summarize
PreferredModelId: local-fast
FallbackModelIds:
  - cloud-reasoning
  - mock-docs
Policy: local-only for shipping
```

Vantaggi:

- le funzionalità rimangono stabili al variare dei modelli
- i criteri possono essere applicati per attività
- le catene di fallback possono miscelare modelli locali, cloud e mock
- i costi possono essere analizzati per attività
- la CI può validare i criteri delle route senza conoscere ogni strumento

## Testare una route

Usa `Test Route` nella scheda `Routes`. Il test verifica:

- la route esiste?
- la route è abilitata?
- il modello esiste?
- il provider esiste?
- il provider è abilitato?
- la chiave richiesta esiste?
- il provider risponde a una breve richiesta?

Gli errori compaiono nell'area di stato e nella dashboard di salute del provider.

## Criteri (Policies)

I criteri stabiliscono se una route può essere utilizzata.

Regole tipiche:

- vietare il cloud per i dati sensibili
- consentire solo modelli locali per la distribuzione (shipping)
- impostare un budget di contesto massimo
- impostare un costo massimo per richiesta
- consentire o negare specifici tipi di provider

I criteri appartengono a LLM Store. Un altro plugin può fornire contesto o chiamare una route, ma la decisione di governance centrale rimane nello store.

## Agenti

La scheda `Agents` mostra adattatori opzionali come Codex, Claude, Cursor o strumenti di studio personalizzati.

| Stato | Significato |
| --- | --- |
| `NotInstalled` | Lo strumento non è stato trovato. |
| `Installed` | Lo strumento esiste, l'autenticazione è incerta o mancante. |
| `AuthRequired` | L'autenticazione deve essere completata. |
| `Available` | Lo strumento è utilizzabile. |
| `Disabled` | L'adattatore è disabilitato. |
| `Error` | L'adattatore segnala un errore. |

Il pulsante `Authenticate...` apre una finestra di dialogo con il comando, le istruzioni, il link di guida e un'azione di copia per l'uso manuale nel terminale. LLM Store non memorizza le credenziali di strumenti esterni.

## Analisi dei costi

La scheda `Costs` raccoglie e analizza il registro dei costi (cost ledger).

Mostra:

- eventi totali
- eventi riusciti
- hit di cache
- token di prompt
- token di completamento
- costo stimato
- suddivisione per provider, modello e route
- esportazione CSV

I costi sono accurati solo quanto i dati di utilizzo del provider e le regole di costo configurate. I modelli locali possono essere gratuiti o associati a costi hardware interni.

## Store dei segreti (Secret Store)

Le chiavi API non devono essere inserite in `Config/LLMStore.json`.

Backend supportati:

- file locale crittografato
- Windows Credential Manager
- macOS Keychain
- 1Password CLI
- Azure Key Vault tramite Azure CLI

Le variabili d'ambiente hanno la precedenza:

```text
LLMSTORE_<PROVIDER_ID>_KEY
```

Esempio:

```text
LLMSTORE_OPENAI_MAIN_KEY
```

## Scheda Status

La scheda `Status` risponde a: "Il mio store è utilizzabile adesso?"

Mostra:

- idoneità globale
- blocchi
- avvisi
- inventario provider
- chiavi mancanti
- provider o modelli disabilitati
- problemi nelle route

Usa questa scheda prima di condividere le impostazioni con un team, eseguire la CI o confezionare una versione.

## Esportazione, validazione e importazione JSON della configurazione

La scheda `Governance` include azioni JSON per condividere o spostare configurazioni LLM Store complete.

Azioni disponibili:

| Azione | Scopo |
| --- | --- |
| `Export Setup JSON` | Scegli una cartella e un nome file a piacere, quindi scrivi la configurazione corrente come JSON. I segreti non sono inclusi. |
| `Validate JSON` | Scegli un file JSON e valida schema, ID provider, riferimenti ai modelli, route e avvisi senza applicarlo. |
| `Import JSON` | Scegli un file JSON, validalo e applicalo solo se la validazione ha successo. |

L'importatore accetta sia il formato racchiuso di configurazione LLM Store che un oggetto JSON `FLLMStoreConfig` grezzo. Ciò lo rende adatto per preimpostazioni, backup, file di consegna del team e snapshot di configurazione verificati manualmente.

## Scheda Help

La scheda `Help` spiega direttamente nell'editor:

- cos'è un provider
- cos'è un modello
- perché si usano le route anziché i nomi diretti dei modelli
- come interagiscono i provider locali e cloud
- come si applicano i criteri e le regole di build
- cosa misura il tracciamento dei costi
- come vengono connessi gli agenti

La sezione di guida è inclusa nel plugin affinché gli acquirenti non debbano passare continuamente da un sito web, README e interfaccia utente dell'editor per i concetti fondamentali.

## Utilizzo in Blueprint

I punti di integrazione fondamentali per gli utenti sono disponibili in Blueprint.

| Classe | Scopo |
| --- | --- |
| `ULLMBlueprintProviderAddOn` | Connette un provider da Blueprint. |
| `ULLMBlueprintEmbeddingProviderAddOn` | Connette un provider di embedding da Blueprint. |
| `ULLMBlueprintContractAddOn` | Valida i contratti dei modelli. |
| `ULLMBlueprintPolicyAddOn` | Consente o rifiuta le route a runtime. |
| `ULLMBlueprintTestAddOn` | Aggiunge test di configurazione o di stato. |
| `ULLMBlueprintContextProviderAddOn` | Fornisce contesto di progetto sotto forma di pack di contesto. |
| `ULLMBlueprintAgentAddOn` | Connette CLI esterne o assistenti dell'editor. |

## Utilizzo in C++

Gli utenti C++ ottengono lo store dal sottosistema dell'engine:

```cpp
ULLMStoreSubsystem* Store = GEngine->GetEngineSubsystem<ULLMStoreSubsystem>();
```

Successivamente è possibile risolvere route, eseguire richieste, creare pack di contesto, chiamare agenti e leggere report sui costi.

Vedi [INTEGRATION.md](INTEGRATION.md) e [CodeDocumentation.md](CodeDocumentation.md).

## Flussi di lavoro consigliati

### Sviluppo locale

1. Crea un provider `ollama` o `llamacpp`.
2. Aggiungi un modello locale.
3. Indirizza le route al modello locale.
4. Disabilita il cloud tramite criteri.
5. Mantieni un percorso `mock` per i test.

### Sviluppo ibrido

1. Usa modelli locali per attività veloci.
2. Aggiungi il fallback cloud per attività più impegnative.
3. Imposta limiti di costo.
4. Esamina regolarmente il tracciamento dei costi.
5. Mantieni le regole di build per la distribuzione esclusivamente locali/mock.

### Configurazione del team

1. Invia al repository `Config/LLMStore.json`.
2. Non inviare le chiavi.
3. Documenta il backend dei segreti.
4. Esporta una preimpostazione.
5. Controlla la scheda `Status`.
6. Abilita i controlli dei criteri in CI.

## Confini

LLM Store non è uno strumento finito per la spiegazione di asset, la revisione di Blueprint o un prodotto RAG. Fornisce route, provider, criteri, tracciamento dei costi, segreti e interfacce. Strumenti per funzionalità concrete possono connettersi ad esso senza che LLM Store dipenda da essi.

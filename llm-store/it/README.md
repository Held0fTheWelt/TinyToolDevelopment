<!-- doc-provenance: AKDB:plugins/LLMStore/architecture.md; docs/architecture/plugins/LLMStore/product-facts.yml; reconciled 2026-06-20 -->
# LLM Store

LLM Store è un plugin per Unreal Engine destinato alla gestione centralizzata di provider IA, modelli, route di attività (task route), criteri (policy), costi, segreti (secret) e agenti esterni opzionali. È progettato come plugin di infrastruttura: gli strumenti dell'editor e i sistemi runtime non devono sapere se una richiesta viene servita da Ollama, llama.cpp, OpenAI, Claude, Gemini, Azure OpenAI, Mistral, OpenRouter o da un provider mock. Essi chiamano una route stabile come `asset.explain`, `docs.summarize` o `naming.review`.

## A chi è rivolto?

LLM Store è utile quando un progetto contiene più di una funzionalità basata su IA e tali funzionalità non devono includere nel codice le credenziali dei provider, i nomi dei modelli, le regole per il cloud o la logica dei costi.

Casi d'uso tipici:

- utilizzare modelli locali per lo sviluppo, i test, la CI o flussi di lavoro adiacenti alla distribuzione
- consentire modelli cloud durante lo sviluppo ma bloccarli per i build di distribuzione (shipping)
- instradare le attività IA tramite nomi di attività stabili anziché tramite nomi di modelli diretti
- valutare i costi per provider, modello e route
- mantenere le chiavi API al di fuori della configurazione del progetto inviata al repository
- offrire la stessa superficie di integrazione ai team C++ e Blueprint
- connettere agenti opzionali come Codex, Claude, Cursor o strumenti specifici dello studio
- consentire a plugin specifici di progetto di fornire contesto senza che LLM Store dipenda da essi
- esporre la cronologia dei job dell'editor tramite route UCM senza dipendere da Unified MCP Server

## Moduli

| Modulo | Scopo |
| --- | --- |
| `LLMStoreInterface` | Struct pubbliche, interfaccia facciata, contratti provider, contratti add-on e classi base Blueprint. |
| `LLMStore` | Sottosistema dell'engine, instradamento, esecuzione, governance, segreti, registro costi (cost ledger) e bridge per agenti. |
| `LLMStoreEditor` | Scheda dell'editor per configurazione, route, stato, guida, agenti, costi e governance. |

## Concetti chiave

| Concetto | Significato |
| --- | --- |
| Provider | Servizio tecnico o server locale, ad esempio `ollama`, `llamacpp` o `openai`. |
| Modello | Un modello concreto fornito da un provider. |
| Route | Nome di attività stabile che si risolve in un modello, una catena di fallback e un criterio. |
| Criterio (Policy) | Regola per l'accesso cloud, comportamento solo locale, budget di contesto, elenchi consenti/nega provider e limiti di costo. |
| Regola di costo (Cost Rule) | Regola di prezzo usata per stimare il costo della richiesta dai token di prompt e di completamento. |
| Agente | Adattatore opzionale per uno strumento esterno come Codex, Claude, Cursor o un assistente dello studio. |
| Provider di contesto | Add-on che fornisce pack di contesto neutrali dalle fonti del progetto, asset, documentazione o altri sistemi. |

## Interfaccia utente dell'editor

Apri il plugin tramite:

```text
Tiny Tools -> LLM Store
```

Schede principali:

- `Setup`: **Quick-Start** con un solo clic al primo avvio (Mock / Ollama / cloud), quindi creazione di provider e modelli, modifica delle URL di base, impostazione delle chiavi e test di connettività.
- `Routes`: configurazione delle route di attività, catene di fallback, modelli mock, modelli di prompt e criteri.
- `Agents`: ispezione degli adattatori per agenti Codex, Claude, Cursor e personalizzati; apertura delle finestre di autenticazione.
- `Costs`: analisi di richieste, token, costo stimato, hit di cache ed esportazione di report CSV.
- `Governance`: ispezione dello stato, eventi di audit, preimpostazioni (preset), stato della cache e regole di build.
- `Status`: lettura dello stato corrente delle impostazioni, avvisi, blocchi e inventario.
- `Help`: spiegazione nell'editor dei concetti e dei flussi di lavoro previsti.
- `Advanced`: sezioni UI opzionali fornite dagli add-on.

## Guida rapida

1. Apri `Tiny Tools -> LLM Store`.
2. Nella scheda **Setup**, usa la scheda **Quick-Start** (Mock, Ollama locale o cloud OpenAI/Anthropic) per ottenere con un solo clic una route `default` funzionante.
3. Oppure crea manualmente un provider e un modello, quindi aggiungi le route nella scheda `Routes`.
4. Testa provider, modello e route; conferma che il banner di idoneità diventi verde.
5. Aggiungi regole di costo se l'analisi del cloud o del budget è importante.
6. Esegui una richiesta e ispeziona le schede `Costs` e `Status`.

Vedi [QUICKSTART.md](QUICKSTART.md) per i dettagli passo-passo (scheda Quick-Start e configurazione manuale).

## Provider locali

Tipi di provider locali o auto-ospitati supportati:

- `ollama`
- `llamacpp`
- `lmstudio`
- `vllm`
- `tgi`
- `mock`

Questi provider non richiedono chiavi API per impostazione predefinita.

## Provider cloud

Tipi di provider cloud supportati:

- `openai`
- `anthropic`
- `gemini`
- `azure-openai`
- `mistral`
- `openrouter`

I provider cloud richiedono solitamente una chiave API. Le chiavi vengono archiviate nel backend dei segreti configurato, mai in `Config/LLMStore.json`.

## Blueprint e C++

Le funzionalità rivolte all'utente sono disponibili sia da C++ che da Blueprint.

Classi base Blueprint:

- `ULLMBlueprintProviderAddOn`
- `ULLMBlueprintEmbeddingProviderAddOn`
- `ULLMBlueprintContractAddOn`
- `ULLMBlueprintPolicyAddOn`
- `ULLMBlueprintTestAddOn`
- `ULLMBlueprintContextProviderAddOn`
- `ULLMBlueprintAgentAddOn`

Vedi [INTEGRATION.md](INTEGRATION.md) e [CodeDocumentation.md](CodeDocumentation.md).

L'esecuzione delle route in streaming e non in streaming condivide una singola coda controllata dalla concorrenza. Usa `EnqueueRoute` per job locali lunghi; `ExecuteRouteStreaming` segue lo stesso controllo di richiesta attiva e restituisce blocchi di flusso tramite la sua API di callback.

## Autenticazione degli agenti

La scheda `Agents` può mostrare un pulsante `Authenticate...` per ciascun agente. La finestra di dialogo mostra il comando di accesso, le istruzioni, il link di supporto e le azioni per eseguire o copiare il comando. Le credenziali rimangono con lo strumento esterno; LLM Store memorizza solo lo stato e le istruzioni.

Vedi [AGENT_AUTHENTICATION.md](AGENT_AUTHENTICATION.md).

## Tracciamento dei costi

LLM Store stima il costo in base a:

- token di prompt segnalati dal provider o stimati dallo store
- token di completamento segnalati dal provider o stimati dallo store
- voci `FLLMCostRule` corrispondenti

Il registro dei costi (cost ledger) è archiviato in:

```text
Saved/LLMStore/CostLedger.json
```

Le esportazioni CSV utilizzano per impostazione predefinita:

```text
Saved/LLMStore/CostReports/LLMStoreCostReport.csv
```

Vedi [COST_TRACKING.md](COST_TRACKING.md).

## Privacy e sicurezza

- Le chiavi API non devono essere inserite in `Config/LLMStore.json`.
- I provider locali sono la scelta preferita per i dati di progetto sensibili.
- I criteri possono limitare l'uso del cloud per route.
- Le regole di build possono bloccare i provider cloud per i build di distribuzione (shipping).
- L'esecuzione dell'agente è esplicita e controllata dai flag della richiesta.

Vedi [SECRET_BACKENDS.md](SECRET_BACKENDS.md) per file locali crittografati, Windows Credential Manager, macOS Keychain, 1Password e Azure Key Vault.

## Inizia da qui

- [BUYER_GUIDE.md](BUYER_GUIDE.md): panoramica per gli acquirenti, proposta di valore e flussi di lavoro pratici.
- [QUICKSTART.md](QUICKSTART.md): prima configurazione funzionante di provider/modello/route.
- [UserManual.md](UserManual.md): flusso di lavoro completo dell'editor e utilizzo dell'interfaccia utente.
- [FAQ.md](FAQ.md): domande e risposte per gli acquirenti su Fab.

## Riferimento

- [SettingsReference.md](SettingsReference.md): campi di configurazione, valori predefiniti, file JSON di configurazione e linee guida consigliate.
- [ProviderReference.md](ProviderReference.md): tipi di provider locali/cloud supportati, URL di base e note.
- [RoutePolicyReference.md](RoutePolicyReference.md): criteri delle route, restrizioni cloud/locali, regole di budget e regole di build.
- [COST_TRACKING.md](COST_TRACKING.md): registro dei costi, regole di costo, esportazione CSV e flusso di lavoro di analisi.
- [SECRET_BACKENDS.md](SECRET_BACKENDS.md): archiviazione locale crittografata e comportamento dei backend dei segreti esterni.
- [AGENT_AUTHENTICATION.md](AGENT_AUTHENTICATION.md): adattatori per agenti stile Codex/Claude/Cursor e comportamento delle finestre di autenticazione.
- [INTEGRATION.md](INTEGRATION.md): modelli di integrazione C++ e Blueprint per altri plugin.
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md): problemi comuni e soluzioni.
- [TechnicalOverview.md](TechnicalOverview.md): panoramica dell'architettura a livello di manutentore.

## Asset inclusi

- [Screenshots/](Screenshots): screenshot della documentazione e diagrammi visivi dei flussi di lavoro.

## Panoramiche visive

- [Screenshots/01-workflow-overview.svg](Screenshots/01-workflow-overview.svg)
- [Screenshots/02-editor-tabs.svg](Screenshots/02-editor-tabs.svg)
- [Screenshots/03-agent-cost-governance.svg](Screenshots/03-agent-cost-governance.svg)

## Flusso di lavoro rapido JSON di configurazione

1. Apri `Tiny Tools -> LLM Store`.
2. Configura provider, modelli, route, criteri e regole di costo.
3. Apri `Governance`.
4. Usa `Export Setup JSON` per scrivere la configurazione corrente in un file a tua scelta.
5. Usa `Validate JSON` per ispezionare un file di configurazione senza applicarlo.
6. Usa `Import JSON` solo dopo il superamento della validazione.

I segreti non vengono mai scritti nel JSON di configurazione. Riconnetti le chiavi dei provider tramite il backend dei segreti o le variabili d'ambiente dopo aver importato una configurazione condivisa.

## Visibilità dei job UCM

LLM Store pubblica la cronologia dei job dell'editor in sola lettura tramite `llmstore.editor.jobs.list.v1` e `llmstore.editor.jobs.status.v1` quando Unreal Capability Mesh è abilitato. Unified MCP Server può aggregare tali route tramite `jobs_list` / `jobs_status`; LLM Store rimane autarchico e non richiede una dipendenza in fase di compilazione da UMCP.

## Commandlet

Esegui i controlli dei criteri CI da un terminale locale o da un esecutore di automazione:

```powershell
<UnrealEditorCommand> "D:\PluginProjectGit\PluginProject.uproject" -run=LLMStoreCIPolicy -unattended -nop4 -nosplash -NoShaderCompile
```

`<UnrealEditorCommand>` è la destinazione da riga di comando di Unreal Editor per l'installazione locale dell'engine.

Il commandlet verifica i provider, modelli, route, criteri e regole di build configurati. È destinato alla governance del rilascio, non alla valutazione delle prestazioni in tempo reale dei provider.

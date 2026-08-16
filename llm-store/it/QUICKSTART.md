<!-- doc-provenance: AKDB:plugins/LLMStore/architecture.md; docs/architecture/plugins/LLMStore/product-facts.yml; reconciled 2026-06-20 -->
# Guida rapida

Questa guida illustra come configurare la prima route funzionante in LLM Store.

## 1. Aprire la scheda dell'editor

Apri:

```text
Tiny Tools -> LLM Store
```

La sezione superiore riassume provider, modelli, route, route di embedding caricati, stato di idoneità e informazioni sui costi stimati.

## 2. Utilizzare la scheda Quick-Start (consigliato per il primo avvio)

Nella scheda **Setup**, la scheda **Quick Start** appare sopra le sezioni provider e modelli. Scegli un percorso:

| Pulsante | Cosa crea | Chiave API |
| --- | --- | --- |
| **Just try it (Mock)** | Provider mock offline, modello e route `default` | Nessuna |
| **Local (Ollama)** | Ollama su `http://localhost:11434`, modello predefinito `llama3`, route `default` | Nessuna (Ollama deve essere in esecuzione) |
| **Create OpenAI** | Provider OpenAI, modello `gpt-4o-mini`, route `default` | Incolla la chiave nel campo (salvata solo nello store dei segreti) |
| **Create Anthropic** | Provider Anthropic, modello `claude-3-5-haiku-latest`, route `default` | Incolla la chiave nel campo (salvata solo nello store dei segreti) |

Dopo aver fatto clic su un pulsante, LLM Store:

1. Applica lo stack iniziale in modo idempotente (ID `quickstart_*` stabili; non sovrascrive mai i provider esistenti né una route `default` già configurata da te).
2. Memorizza una chiave API cloud tramite `SetProviderKey` quando fornita (mai scritta in `Config/LLMStore.json`).
3. Esegue **Test Connection** e aggiorna il banner di idoneità.

Quando l'idoneità è già verde, la scheda viene compressa e mostra il titolo «ready — expand to run Quick-Start again».

Per URL personalizzate, modelli aggiuntivi o route per attività specifiche, prosegui con i passaggi manuali di seguito.

## 3. Creare un provider locale (manuale)

Un provider locale è il test iniziale più semplice poiché non richiede alcuna chiave API.

### Opzione A: Ollama

1. Avvia Ollama localmente.
2. Scarica un modello:

```text
ollama pull llama3.1
```

3. In `Setup`, crea un provider:

```text
Id: ollama-local
DisplayName: Ollama Local
Type: ollama
BaseUrl: http://127.0.0.1:11434
Enabled: true
```

4. Crea un modello:

```text
Id: local-chat
Name: llama3.1
DisplayName: Local Chat
ProviderId: ollama-local
Role: fast
Enabled: true
```

### Opzione B: llama.cpp

Avvia un server llama.cpp locale:

```text
llama-server -m C:\Models\model.gguf --host 127.0.0.1 --port 8080
```

Quindi crea:

```text
Provider:
  Id: llamacpp-local
  Type: llamacpp
  BaseUrl: http://127.0.0.1:8080

Model:
  Id: local-llamacpp
  Name: local-model
  ProviderId: llamacpp-local
```

## 4. Creare un provider cloud (manuale)

I provider cloud richiedono solitamente una chiave API. La chiave viene archiviata nel backend dei segreti, non in `Config/LLMStore.json`.

Esempio:

```text
Provider:
  Id: openai-main
  Type: openai
  BaseUrl: https://api.openai.com/v1

Model:
  Id: openai-fast
  Name: gpt-4o-mini
  ProviderId: openai-main
```

Imposta quindi la chiave nella sezione del provider o tramite una variabile d'ambiente:

```text
LLMSTORE_OPENAI_MAIN_KEY
```

## 5. Creare una route

Crea una route nella scheda `Routes`:

```text
TaskKind: docs.summarize
PreferredModelId: local-chat
FallbackModelIds:
  - openai-fast
MockModelId: mock-docs
bUseMock: false
```

Se hai iniziato con llama.cpp, usa `local-llamacpp` come modello preferito.

## 6. Aggiungere un criterio (Policy)

Per una route sicura che predilige il locale:

```text
bAllowCloud: false
bLocalOnly: true
MaxContextTokens: 0
MaxEstimatedCost: 0
AllowedProviderTypes:
  - ollama
  - llamacpp
  - mock
```

Per una route di sviluppo ibrida, consenti il cloud e aggiungi un limite di costo:

```text
bAllowCloud: true
bLocalOnly: false
MaxEstimatedCost: 0.05
```

## 7. Testare provider, modello e route

Utilizza i pulsanti di test nell'editor.

Se la route non si risolve, verifica:

- il provider è abilitato?
- il modello è abilitato?
- il modello fa riferimento al provider corretto?
- la route utilizza l'ID modello corretto?
- la chiave API è impostata per il provider cloud?
- il server locale è in esecuzione?
- il criterio consente il tipo di provider selezionato?

## 8. Aggiungere regole di costo

La scheda `Costs` diventa utile una volta definite le regole di prezzo.

Esempio:

```text
ProviderType: openai
ModelId: openai-fast
InputCostPer1KTokens: 0.00015
OutputCostPer1KTokens: 0.00060
Currency: USD
```

I provider locali possono rimanere a `0` o utilizzare un modello di costo interno.

## 9. Eseguire una richiesta

Dopo una richiesta, la scheda `Costs` mostra:

- conteggio eventi
- conteggio successi
- hit di cache
- token di prompt
- token di completamento
- costo stimato
- suddivisione per provider/modello/attività
- eventi recenti

Usa `Export CSV` per scrivere report in:

```text
Saved/LLMStore/CostReports
```

## 10. Controllare lo stato

Apri la scheda `Status`. La sezione più importante è `Attention`, poiché mostra chiavi mancanti, route interrotte, provider disabilitati e problemi di criteri.

## 11. Configurazione opzionale degli agenti

Per connettere Codex, Claude, Cursor o un agente personalizzato:

1. Apri la scheda `Agents`.
2. Seleziona un agente.
3. Fai clic su `Authenticate...`.
4. Usa `Copy Command` ed esegui il comando manualmente nel tuo terminale.
5. Aggiorna lo stato.

Esempi:

```text
codex login
claude auth login
```

LLM Store non memorizza le credenziali degli agenti.

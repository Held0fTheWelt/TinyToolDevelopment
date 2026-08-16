<!-- doc-provenance: SAD architecture.md sections 2,8,10; facts product-facts.yml; reconciled 2026-07-16 -->
# Riferimento delle impostazioni

Le impostazioni IIS sono memorizzate in `UIISSettings`.

Apri:

```text
Edit -> Project Settings -> Plugins -> Internal Index Service
```

## Campi

| Impostazione | Predefinito | Significato |
| --- | --- | --- |
| Vector Backend | `jsonl_bruteforce` | Seleziona il backend di ricerca vettoriale locale. I valori supportati includono `jsonl_bruteforce` e `hnsw`. Con `jsonl_bruteforce`, IIS passa automaticamente a HNSW oltre il limite dei record di forza bruta indicato di seguito. |
| Index Root | vuoto | Sostituzione opzionale per i dati generati da IIS. Vuoto utilizza `Saved/InternalIndexService`. |
| Brute Force Max Records | `10000` | Entro questo numero di record viene utilizzata la ricerca esatta a forza bruta; al di sopra viene usato HNSW. |
| Embedding Executor Id | vuoto | ID dell'esecutore di embedding IIS preferito. Vuoto usa il rilevamento normale; il bridge opzionale IIS LLM Store imposta questo valore su `llmstore` quando caricato. |
| Vector Storage Format | `Int8 Per-Vector Scale` | Criterio di archiviazione vettoriale HNSW. `Int8 Per-Vector Scale` è la modalità compatta predefinita e supportata; `Float32` è utile per esecuzioni ad alta fedeltà/debug; `Experimental Global Scale` è controllato da un gate e riservato alle misurazioni. |
| Allow Experimental Vector Formats | `false` | Abilita i formati di archiviazione HNSW sperimentali. Se disabilitato, le selezioni sperimentali ripiegano su `Int8 Per-Vector Scale`. |
| Rebuild On Vector Format Mismatch | `true` | Elimina le partizioni HNSW persistenti incompatibili in modo che possano essere ricostruite dai vettori sorgente anziché essere lette con un layout di byte errato. |
| Quantization Recall Gate | `0.7` | Obiettivo minimo di recall utilizzato dai gate di automazione dell'archiviazione vettoriale quantizzata. Aumentare solo dopo la validazione su embedding rappresentativi del progetto. |
| HNSW M | `16` | Connettività del grafo HNSW. Valori più alti migliorano il recall a scapito della memoria e del tempo di creazione. Si applica agli indici creati ex novo. |
| HNSW efConstruction | `200` | Dimensione della lista di candidati in fase di creazione. Valori più alti migliorano la qualità del grafo e il recall a scapito del tempo di creazione. Si applica agli indici creati ex novo. |
| HNSW efSearch | `64` | Dimensione della lista di candidati in fase di query. Valori più alti migliorano il recall a scapito della latenza di query. Applicato durante il caricamento e la ricostruzione. |
| Enable Runtime Control Mutations | `true` | Gate principale per la superficie di controllo runtime. Quando disattivato, i comandi di console e API per tune/act/persist vengono rifiutati; le letture continuano a funzionare. |
| Retain Recent Diagnostics | `false` | Quando attivo, IIS mantiene un buffer circolare in memoria delle diagnostiche recenti per query per l'ispezione tramite `diagnostics.recent` / console. |
| Recent Diagnostics Max Count | `64` | Numero massimo di diagnostiche conservate quando Retain Recent Diagnostics è attivo. |
| Estimate Recall By Default | `false` | Quando attivo, le ricerche stimano recall@K a meno che la query non lo escluda esplicitamente. Aggiunge una scansione di riferimento esatta (SYN-1). |

> Gli indici HNSW sono archiviati per impostazione predefinita utilizzando la quantizzazione scalare int8 (ridimensionamento per vettore), che mantiene alto il recall riducendo al contempo la memoria dell'indice e la dimensione su disco. Float32 è disponibile come criterio ad alta fedeltà/debug. L'int8 su scala globale sperimentale è intenzionalmente controllato da un gate poiché può sprecare la maggior parte dei livelli int8 su embedding multidimensionali normalizzati. Gli indici creati con un altro criterio di archiviazione vengono rilevati e ricostruiti automaticamente per impostazione predefinita.

## Percorsi generati

Radice predefinita:

```text
Saved/InternalIndexService
```

Aree generate importanti:

| Percorso | Scopo |
| --- | --- |
| `chunks.jsonl` | Archivio dei chunk importati. |
| `imports/` | Manifest di importazione e report. |
| `reports/` | Report di catalogo, embedding e diagnostica. |
| `agent_contracts/` | Contratti degli strumenti agente e manifest MCP usati dai bridge. |
| `vectors/` o file specifici del backend | Dati di embedding/vettori persistenti. |

I nomi esatti dei file possono variare in base al flusso di lavoro e al backend.

## Impostazioni MCP

Le impostazioni del server MCP non sono in IIS. Configurale sotto:

```text
Edit -> Editor Settings -> Plugins -> Unified MCP Server
```

L'accesso agente IIS viene pubblicato tramite le route Capability Mesh del progetto come `iis.agent.search.v1`.

## Gestione dei segreti

IIS non memorizza i segreti dei provider. Le credenziali dei provider di embedding appartengono a LLM Store o all'ambiente del provider.

## Valori predefiniti consigliati

| Scenario | Vector Backend | Vector Storage Format | Formati sperimentali | Index Root |
| --- | --- | --- | --- | --- |
| Prima configurazione | `jsonl_bruteforce` | `Int8 Per-Vector Scale` | disabilitato | vuoto |
| Indice locale di grandi dimensioni | `hnsw` | `Int8 Per-Vector Scale` | disabilitato | vuoto o percorso personalizzato locale al progetto |
| Debug ad alta fedeltà | `hnsw` | `Float32` | disabilitato | percorso temporaneo dell'area di lavoro |
| Esperimento di recall | `hnsw` | `Experimental Global Scale` | abilitato | percorso temporaneo dell'area di lavoro |
| Validazione CI condivisa | `jsonl_bruteforce` | `Int8 Per-Vector Scale` | disabilitato | percorso temporaneo dell'area di lavoro |

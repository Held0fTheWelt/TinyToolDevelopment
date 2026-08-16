<!-- doc-provenance: SAD architecture.md sections 1,2,7,8; facts product-facts.yml; reconciled 2026-07-16 -->
# Internal Index Service

Internal Index Service (IIS) è un plugin per Unreal Engine destinato all'indicizzazione **locale**, retrieval, pack di contesto e ricerca per agenti. È una funzionalità di sola lettura (retrieval-only): non modifica i contenuti del progetto e non genera patch.

## Moduli

| Modulo | Scopo |
| --- | --- |
| `InternalIndexServiceInterface` | Contratti pubblici per chunk, ricerca, importazioni, embedding e accesso agente. |
| `InternalIndexService` | Sottosistema runtime dell'engine, catalogo chunk, backend vettoriali, job di embedding, indicizzazione incrementale. |
| `InternalIndexServiceEditor` | Pannello di controllo editor, bridge Python e voci di menu Tiny Tools. |

## Aprire il pannello di controllo

```text
Tiny Tools -> AI -> Internal Index Service -> Open Internal Index Service
```

Oppure utilizza la scheda nomad **Internal Index Service** se il tuo layout la mostra già.

Il pannello è organizzato come segue:

| Scheda | Scopo |
| --- | --- |
| **Dashboard** | Schede di stato per Index e Integrations; azioni rapide (Ricostruisci catalogo). |
| **Overview** | Versione del servizio, radice dell'indice, presenza catalogo/vettori. |
| **Imports** | Passaggio UII e riepiloghi dei report di importazione. |
| **Catalog** | Genera catalogo e mostra il riepilogo di generazione catalogo sotto `Saved/InternalIndexService/reports`. |
| **Embeddings** | Crea ed esegui job di embedding persistenti tramite un `IIISEmbeddingRouteExecutor` rilevato. |
| **Search** | Ricerca lessicale / vettoriale / ibrida integrata nell'indice locale. |
| **Agent/MCP** | Contratti agente, ID route UCM e guida all'accesso MCP tramite Unified MCP Server. |
| **Reports** | Scorciatoie per le cartelle di report e log. |

L'intestazione mostra il nome del progetto, un marcatore di sola lettura, un pulsante **Settings** e un pulsante **Refresh**. L'aggiornamento aggiorna tutti i riepiloghi delle schede, forza l'aggiornamento delle schede della dashboard e aggiorna il pannello Governance.

Le schede della dashboard vengono aggiornate all'apertura, tramite **Refresh** esplicito e dopo azioni della dashboard come **Rebuild**. Il pannello non ricostruisce le schede tramite un timer periodico, mantenendo stabile l'interfaccia utente durante la modifica o l'ispezione.

## Impostazioni di progetto

Configura IIS sotto:

```text
Edit -> Project Settings -> Plugins -> Internal Index Service
```

| Impostazione | Predefinito | Significato |
| --- | --- | --- |
| **Vector Backend** | `jsonl_bruteforce` | Implementazione dell'indice vettoriale locale (`jsonl_bruteforce` o `hnsw`), con instradamento automatico forza bruta/HNSW in base al numero di record. |
| **Index Root (optional)** | *(vuoto)* | Sostituzione per la radice dell'indice su disco; vuoto utilizza `Saved/InternalIndexService`. |
| **Brute Force Max Records** | `10000` | Soglia di ricerca esatta prima dell'uso di HNSW. |
| **Embedding Executor Id** | *(vuoto)* | Esecutore di embedding preferito. Vuoto usa il rilevamento IIS normale; il bridge opzionale IIS LLM Store imposta questo valore su `llmstore` quando caricato. |
| **Vector Storage Format** | `Int8 Per-Vector Scale` | Criterio di archiviazione HNSW. Mantieni il valore predefinito int8 compatto per vettore per l'uso normale; usa `Float32` per esecuzioni ad alta fedeltà/debug; usa `Experimental Global Scale` solo dietro il gate sperimentale. |
| **Allow Experimental Vector Formats** | `false` | Abilita layout vettoriali solo per misurazione che possono ridurre il recall. |
| **Rebuild On Vector Format Mismatch** | `true` | Ricostruisce le partizioni HNSW persistenti incompatibili invece di caricarle con un layout di byte errato. |
| **Quantization Recall Gate** | `0.7` | Soglia minima di recall usata dai test di automazione della quantizzazione; aumentare dopo una validazione rappresentativa del progetto. |
| **HNSW M / efConstruction / efSearch** | `16` / `200` / `64` | Ottimizzazione di recall, tempo di creazione, memoria e latenza di query per HNSW. |

L'accesso MCP è fornito da Unified MCP Server tramite le route Capability Mesh del progetto. IIS non distribuisce né richiede più un bridge UMCP IIS dedicato.

## Integrazioni

L'esecuzione degli embedding è delegata tramite `FIISEmbeddingDiscovery` (`IModularFeatures` / `IIISEmbeddingRouteExecutor`). I plugin bridge si registrano in `StartupModule` e si annullano in `ShutdownModule`. `FIISEmbeddingRouteExecutorRegistry` è un adattatore deprecato per chiamanti legacy.

La scheda **Integrations** della Dashboard elenca gli ID esecutore da `FIISEmbeddingDiscovery::GetExecutorIds()` e indica se ciascuna integrazione è attiva.

L'cronologia dei job dell'editor viene esposta tramite route UCM (`iis.editor.jobs.list.v1`, `iis.editor.jobs.status.v1`) invece di un provider UMCP in fase di compilazione. La route di elenco unisce la cronologia del pannello con le righe recenti dei job di embedding SQLite.

## Documentazione correlata

| Documento | Pubblico |
| --- | --- |
| [QUICKSTART.md](QUICKSTART.md) | Prima configurazione, importazione, creazione indice e ricerca. |
| [UserManual.md](UserManual.md) | Flusso di lavoro completo dell'editor e comportamento operativo. |
| [SettingsReference.md](SettingsReference.md) | Impostazioni, file generati e percorsi di archiviazione. |
| [TechnicalOverview.md](TechnicalOverview.md) | Architettura e flusso dati per manutentori. |
| [CodeDocumentation.md](CodeDocumentation.md) | Mappa del codice sorgente C++, classi principali e percorsi di esecuzione. |
| [INTEGRATION.md](INTEGRATION.md) | Come UII, LLM Store e UMCP si collegano a IIS. |
| [FAQ.md](FAQ.md) | Domande frequenti di acquirenti e revisori. |
| [TROUBLESHOOTING.md](TROUBLESHOOTING.md) | Problemi comuni e soluzioni. |
| [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md) | Dettagli sulla dichiarazione del codice sorgente di terze parti per l'invio a Fab. |
| [../CHANGELOG.md](../CHANGELOG.md) | Note di rilascio. |

## Confezionamento

`Config/FilterPlugin.ini` include `/Documentation/...` in modo che gli acquirenti ricevano questa cartella nei build Fab.
Mantiene inoltre i metadati di precompilazione generati da BuildPlugin nell'output confezionato. Quando IIS viene installato in un'installazione di Unreal Engine, usa un pacchetto compilato per quella versione dell'engine e mantieni intatti i file binari generati e i metadati.

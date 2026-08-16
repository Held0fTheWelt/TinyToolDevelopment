<!-- doc-provenance: SAD architecture.md sections 1,5,6,8; facts product-facts.yml; reconciled 2026-07-16 -->
# Manuale utente

## Flusso di lavoro principale

IIS segue un flusso di lavoro di retrieval in sola lettura:

1. Importa le evidenze preparate.
2. Crea o aggiorna il catalogo locale.
3. Crea gli embedding quando è necessaria la ricerca vettoriale.
4. Esegui ricerche o crea pack di contesto.
5. Esponi gli stessi strumenti in sola lettura agli agenti tramite UMCP.

IIS non applica modifiche (mutation) al progetto.

## Mappa delle funzionalità del prodotto

| Funzionalità scheda tecnica | Superficie visibile all'acquirente |
| --- | --- |
| `ImportPreparedChunks` | Importa i file JSONL di chunk preparati dalla scheda Imports del pannello di controllo o dall'API del servizio. |
| `Search` | Esegue il retrieval lessicale, vettoriale o ibrido dalla scheda Search e dall'API del servizio. |
| `BuildContextPack` | Crea pack di contesto incentrati sulle evidenze a partire da una query o da risultati selezionati. |
| `RunPerfSelfCheck` | Esegue l'autocontrollo delle prestazioni sintetiche fornito tramite Blueprint/API e console. |
| `RuntimeControlDispatch` | Invia i comandi observe, tune, act, persist e reset tramite la superficie di controllo runtime. |
| `AgentRetrievalTools` | Fornisce operazioni di retrieval agente in sola lettura tramite contratti locali e route opzionali UCM/UMCP. |

## Pannello di controllo

Apri:

```text
Tiny Tools -> AI -> Internal Index Service -> Open Internal Index Service
```

Schede:

| Scheda | Uso |
| --- | --- |
| Dashboard | Stato dell'indice, stato dell'integrazione, scorciatoia per la ricostruzione, scorciatoia per la ricerca. |
| Index | Importazioni, creazione del catalogo, creazione/esecuzione dei job di embedding. |
| Use | Ricerca tra le evidenze locali. |
| Agents | Contratti agente e stato del bridge UMCP. |
| Governance | Postura di sola lettura, percorsi locali, visibilità di bridge e strumenti. |
| Diagnostics | Report, panoramica e percorsi degli artefatti generati. |
| Settings | Visualizzazione integrata di `UIISSettings`. |

## Comportamento di importazione

L'importazione elabora file JSONL con chunk preparati. Ciascun chunk contiene ID, contenuto, riferimenti alla fonte, metadati su asset/simboli e stato del ciclo di vita. IIS valida l'input, aggiunge i chunk accettati e scrive report di importazione.

File importanti:

```text
Saved/InternalIndexService/chunks.jsonl
Saved/InternalIndexService/imports/
Saved/InternalIndexService/reports/
```

## Creazione del catalogo

La creazione del catalogo legge i chunk archiviati e produce strutture locali interrogabili. Filtra gli stati non attivi del ciclo di vita dei chunk e scrive un report per consentire agli utenti di rivedere eventuali avvisi.

## Ricerca

I campi della query di ricerca includono il testo della query, la modalità di ricerca, i risultati massimi, i filtri e le opzioni per il pack di contesto. I risultati contengono ID dei chunk, informazioni sul punteggio, snippet e riferimenti alla fonte.

Modalità di ricerca:

| Modalità | Significato |
| --- | --- |
| Lexical | Utilizza il corrispettivo di testo locale sul catalogo dei chunk. |
| Vector | Utilizza gli embedding persistenti e il backend vettoriale configurato. |
| Hybrid | Combina i candidati lessicali e vettoriali. |

## Superficie di controllo runtime

IIS fornisce una superficie di controllo runtime **autarchica** (autark) per observe → tune → act senza ricaricare l'editor. Modifica l'oggetto `UIISSettings` attivo in memoria (transitorio per impostazione predefinita) e riapplica immediatamente i parametri memorizzati nella cache, come l'HNSW `efSearch` e il kernel int8 attivo.

**Nessuna dipendenza da UCM o UMCP** — la superficie funziona autonomamente da Blueprint, C++ e console dell'editor.

### API Blueprint tipizzata (`UIISSubsystem`)

| Metodo | Scopo |
| --- | --- |
| `GetControlState` | Istantanea dei parametri effettivi e dello stato del gate di modifica. |
| `SetTuning` | Applica variazioni opzionali di ottimizzazione per campo (`FIISTuningRequest`). |
| `PersistTuning` | Scrive le modifiche correnti nella configurazione (`SaveConfig`). |
| `ResetTuning` | Ricarica la configurazione e ripristina le modifiche temporanee. |
| `RunPerfSelfCheck` | Esegue i carichi di lavoro di prestazioni SYN-2 in base ai budget configurati. |

### Comandi da console

| Comando | Scopo |
| --- | --- |
| `iis.control.state` | Stampa il JSON dello stato di controllo effettivo. |
| `iis.control.tune {json}` | Ottimizzazione temporanea (ad es. `{"efSearch":128}`). |
| `iis.control.persist` | Salva le modifiche nella configurazione. |
| `iis.control.reset` | Ricarica la configurazione / annulla le modifiche. |
| `iis.control.diagnostics.recent` | Diagnostica recente per query (quando la conservazione è attiva). |
| `iis.perf.run` / `iis.perf.last` | Esegue o legge l'ultimo autocontrollo delle prestazioni. |
| `iis.index.sync` / `iis.index.rebuild` / `iis.index.import` | Verbi di azione per la manutenzione dell'indice. |

I comandi di modifica rispettano l'impostazione **Enable Runtime Control Mutations** nelle impostazioni di progetto (attiva per impostazione predefinita).

## Embedding

IIS non gestisce le credenziali dei provider. La risoluzione e l'esecuzione delle route di embedding sono delegate tramite `FIISEmbeddingDiscovery` (`IIISEmbeddingRouteExecutor` tramite `IModularFeatures`), normalmente fornite da un bridge LLM Store che si registra in `StartupModule` e si annulla in `ShutdownModule`.

Flusso per gli embedding:

1. Crea job per i chunk che necessitano di vettori.
2. Risolvi una route di embedding.
3. Esegui i job tramite l'esecutore registrato.
4. Salva i record dei vettori.
5. Aggiorna i report.

## Strumenti agente

Gli strumenti agente sono in sola lettura e restituiscono JSON strutturato. IIS definisce sei operazioni di retrieval autonome. I nomi dei contratti locali rimangono disponibili per le chiamate in-engine e tramite file JSON:

| Contratto locale | ID route UCM | Scopo |
| --- | --- | --- |
| `iis_search` | `iis.agent.search.v1` | Cerca tra i chunk indicizzati (payload JSON inline e percorso dell'artefatto). |
| `iis_get_context_pack` | `iis.agent.get_context_pack.v1` | Crea un pack di contesto compatto dai risultati della ricerca (payload JSON inline e percorso dell'artefatto). |
| `iis_get_chunk` | `iis.agent.get_chunk.v1` | Recupera un singolo chunk tramite ID. |
| `iis_get_source_references` | `iis.agent.get_source_references.v1` | Restituisce i riferimenti alla fonte per un chunk. |
| `iis_find_usages` | `iis.agent.find_usages.v1` | Cerca i record di utilizzo. |
| `iis_explain_blueprint` | `iis.agent.explain_blueprint.v1` | Riassume le evidenze Blueprint indicizzate (payload JSON inline e percorso dell'artefatto). |

`iis.index.status.v1` segnala inoltre `catalog_exists`, `chunk_store_records` e `vector_records` in modo che gli agenti possano verificare se l'indice è stato popolato senza dover leggere i file.

Il trasporto MCP è gestito da Unified MCP Server. IIS non registra direttamente strumenti MCP; la configurazione Capability Mesh del progetto dichiara una route per ciascuna operazione agente e UMCP le pubblica come strumenti generici `mesh_route_*`. Non è richiesto alcun plugin bridge.

## Dati e privacy

IIS archivia gli indici generati nella cartella `Saved` del progetto per impostazione predefinita. Se viene impostata una radice dell'indice personalizzata, usa un percorso locale/privato a meno che il team non condivida intenzionalmente le evidenze generate.

L'esposizione verso il cloud avviene solo se una route dell'esecutore di embedding in LLM Store utilizza un provider cloud.

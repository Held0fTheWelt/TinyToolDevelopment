<!-- doc-provenance: SAD architecture.md sections 6,8,10,11; facts product-facts.yml; reconciled 2026-07-16 -->
# Risoluzione dei problemi

## La compilazione fallisce su UE 5.6 con errori negli header dell'engine

Assicurati che i moduli IIS vengano compilati con C++20. Gli header dell'engine di UE 5.6 utilizzano la sintassi C++20. I file `.Build.cs` di IIS dovrebbero utilizzare:

```csharp
CppStandard = CppStandardVersion.Cpp20;
```

## La ricerca non restituisce risultati

Verifica:

- che i chunk preparati siano stati importati
- che il catalogo sia stato ricostruito
- che il testo della query non sia vuoto
- che lo stato del ciclo di vita sia attivo
- che la radice dell'indice punti alla cartella di progetto prevista

## La ricerca vettoriale non restituisce risultati

Verifica:

- che i job di embedding siano stati creati
- che i job di embedding siano stati eseguiti con successo
- che la route/esecutore di LLM Store sia registrato
- che l'impostazione del backend vettoriale corrisponda agli artefatti salvati

## L'importazione fallisce

Verifica che il file JSONL dei chunk preparati esista e sia leggibile. Esamina i report di importazione nella cartella salvata di IIS per verificare eventuali avvisi di validazione o record rifiutati.

## L'indice HNSW non si carica o produce avvisi del backend

Se il backend HNSW non riesce a caricarsi o se compaiono avvisi dopo aver modificato le impostazioni di archiviazione vettoriale, passa temporaneamente a `jsonl_bruteforce` per separare i problemi dei dati vettoriali dai problemi di indicizzazione specifici del backend. Mantieni **Rebuild On Vector Format Mismatch** abilitato in modo che le partizioni HNSW persistenti incompatibili vengano ricostruite dai vettori sorgente anziché essere caricate con un layout di byte errato.

Conferma che `Source/ThirdParty/hnswlib` sia presente nel pacchetto e ricostruisci gli artefatti vettoriali dopo aver modificato **Vector Storage Format**.

## L'ottimizzazione runtime o il comando dell'indice restituisce "Disabled"

Verifica **Enable Runtime Control Mutations** nelle impostazioni di progetto. Quando è disattivato, i comandi di lettura come `iis.control.state` continuano a funzionare, ma i comandi di tune, act, persist e reset restituiscono una risposta di disabilitazione per impostazione predefinita.

Riabilita l'impostazione per i comandi di modifica o prosegui con le istruzioni di stato e diagnostica in sola lettura.

## Gli strumenti agente non compaiono nel client MCP

Verifica:

- che Unified MCP Server sia abilitato e in esecuzione
- che Unreal Capability Mesh sia abilitato
- che la configurazione del progetto includa i manifest delle route agente IIS (`iis.agent.*.v1`)
- chiama `mesh_list_routes` o `mesh_reload_setup` e aggiorna il client MCP
- che IIS sia in grado di scrivere i contratti degli strumenti agente
- che il client MCP sia connesso all'endpoint UMCP e non a un server MCP legacy per singolo plugin

Aggiorna la configurazione di Capability Mesh e riconnetti o aggiorna il client MCP dopo le modifiche alle route.

## Lo strumento agente restituisce avvisi sulle restrizioni di sola lettura

È il comportamento previsto. Le risposte di IIS indicano intenzionalmente che le modifiche al progetto non sono consentite.

## L'autocontrollo delle prestazioni segnala uno scostamento

Esamina l'ultimo risultato delle prestazioni da `iis.perf.last` oppure esegui nuovamente `iis.perf.run`. Gli scostamenti indicano solitamente che il carico di lavoro vettoriale attuale, il backend o l'ottimizzazione superano i budget configurati.

Riduci prima l'ampiezza della query o il carico di lavoro vettoriale. Aggiorna i budget solo dopo una validazione rappresentativa sul profilo della macchina/progetto di destinazione.

## Dove cercare i report

Percorsi predefiniti:

```text
Saved/InternalIndexService/reports
Saved/InternalIndexService/imports
Saved/InternalIndexService/agent_contracts
```

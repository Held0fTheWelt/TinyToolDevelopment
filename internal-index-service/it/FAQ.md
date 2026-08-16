<!-- doc-provenance: SAD architecture.md sections 1,2,7,8; facts product-facts.yml; reconciled 2026-07-16 -->
# FAQ (Domande frequenti)

## IIS modifica il mio progetto?

No. IIS è una funzionalità di sola lettura (retrieval-only). Scrive file di indice e report generati, ma non applica modifiche a sorgenti, Blueprint, asset o configurazioni tramite azioni dell'agente.

## IIS include un server MCP?

No, non nelle versioni attuali. Il trasporto MCP è fornito da Unified MCP Server. Le operazioni agente di IIS vengono esposte tramite le route Capability Mesh del progetto, non tramite un server MCP o plugin bridge proprietario di IIS.

## Dove vengono salvati i dati?

Per impostazione predefinita:

```text
Saved/InternalIndexService
```

Puoi sovrascrivere la cartella radice nelle impostazioni di progetto.

## IIS invia i dati del progetto al cloud?

Solo se una route dell'esecutore di embedding in LLM Store utilizza un provider cloud. La ricerca, il catalogo, l'importazione e i file dei report sono locali.

## Perché non ci sono risultati vettoriali?

La ricerca vettoriale richiede gli embedding. Crea ed esegui i job di embedding dopo aver configurato una route di embedding tramite LLM Store.

## A cosa serve hnswlib?

hnswlib gestisce il backend vettoriale opzionale per i vicini più prossimi approssimati `hnsw`. È incluso come codice sorgente nella cartella `Source/ThirdParty/hnswlib`.

## Perché nell'elenco degli strumenti MCP mancano gli strumenti IIS?

Assicurati che i seguenti plugin siano abilitati:

- Internal Index Service
- Unified MCP Server
- Unreal Capability Mesh

Assicurati che il profilo Capability Mesh del progetto elenchi le route agente di IIS (`iis.agent.*.v1`), quindi scrivi/aggiorna i contratti agente di IIS e chiama `mesh_reload_setup` o aggiorna il client MCP.

## Posso chiamare IIS da C++?

Sì. Usa `FInternalIndexServiceModule::Get().GetService()` e l'interfaccia `IInternalIndexService`.

## Posso chiamare IIS da Blueprint?

IIS espone principalmente l'interfaccia utente dell'editor e servizi C++. I percorsi per gli agenti e l'integrazione sono basati su C++/JSON.

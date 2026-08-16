<!-- doc-provenance: AKDB:plugins/UnifiedMcpServer/architecture.md; docs/architecture/plugins/UnifiedMcpServer/product-facts.yml; reconciled 2026-07-04 -->
# Unified MCP Server

Unified MCP Server è un plugin per l'editor di Unreal Engine che fornisce un unico endpoint locale del Model Context Protocol (MCP) per l'intero progetto. Gli altri plugin collegano i propri strumenti tramite una piccola interfaccia modulare, consentendo al server di esporre nuove funzionalità senza dipendere direttamente da essi.

Il plugin è intenzionalmente progettato solo come infrastruttura. Non include alcun eseguibile esterno, pacchetto Node o runtime Python. Ospita un endpoint MCP JSON-RPC 2.0 in loopback all'interno dell'editor e consente ai provider di registrare strumenti a runtime.

## Moduli

| Modulo | Scopo |
| --- | --- |
| `UnifiedMcpServerInterface` | Contratto pubblico `IUmcpToolProvider` e tipi di descrittore/risultato degli strumenti. |
| `UnifiedMcpServerEditor` | Host dell'editor per il server, impostazioni, gestione dei token, registro dei provider, pannello di controllo dello stato e voci del menu Tiny Tools. |

## Flusso di lavoro principale

1. Abilita il plugin nel progetto.
2. Apri `Edit -> Editor Settings -> Plugins -> Unified MCP Server`.
3. Abilita il server locale e scegli una porta, oppure mantieni quella predefinita `8732`.
4. Utilizza `Tiny Tools -> AI -> Universal MCP -> Open Control Panel` per lo stato, i pulsanti del ciclo di vita e l'albero delle funzioni connesse raggruppate per plugin.
5. Avvia il server dal pannello oppure tramite `Tiny Tools -> AI -> Universal MCP -> Start Unified MCP Server`.
6. Leggi i dati di connessione da `Saved/UnifiedMcpServer/agent/mcp_endpoint.json`.
7. Configura un client MCP per chiamare `http://127.0.0.1:8732/mcp` con `Authorization: Bearer <token>`.

## Provider di strumenti (Tool Providers)

I plugin provider implementano `IUmcpToolProvider` e lo registrano come funzionalita modulare di Unreal. I nomi degli strumenti esposti utilizzano la struttura:

```text
<providerId>_<toolName>
```

Quando Unreal Capability Mesh è caricato, il provider mesh integrato espone strumenti generici come `mesh_list_capabilities`, `mesh_list_routes`, `mesh_configure_experimental_self_approval`, `mesh_dry_run_route` e `mesh_execute_route`. Inoltre, appiattisce le route UCM dichiarate nella configurazione in strumenti MCP diretti `mesh_route_*`. Tali strumenti di route pubblicano gli schemi `inputSchema`, `outputSchema` ed eventuali annotazioni derivati dalle route, consentendo ai client di ispezionare parametri e avvisi sui rischi prima di effettuare le chiamate. `mesh_configure_experimental_self_approval` è **SPERIMENTALE** e da utilizzare **a proprio rischio**; l'abilitazione richiede una conferma esplicita del rischio. I bridge di provider diretti legacy possono ancora registrare nomi di strumenti specifici del prodotto, ma le route UCM costituiscono il percorso di configurazione preferito all'interno del progetto.

`tools/call` restituisce il JSON del provider come contenuto di testo e, quando il risultato è un oggetto JSON, come `structuredContent` MCP. `initialize` dichiara `tools.listChanged` e `tools/list` include un valore `_meta.toolsRevision` in modo che i client possano aggiornare i descrittori degli strumenti in cache dopo eventuali modifiche alla configurazione UCM.

UMCP 1.0.3 aggiunge il controllo degli accessi al singolo endpoint. Gli ID dei provider possono essere disabilitati e i nomi degli strumenti esposti possono essere consentiti o bloccati tramite nomi esatti o pattern con caratteri jolly. UMCP 1.0.4 introduce i profili (`Default`, `Read Only`, `Automation`, `Experimental`) e gruppi di strumenti derivati dalle annotazioni. UMCP 1.0.5 aggiunge token di sessione con ambito (scope) in modo che client diversi possano utilizzare gli accessi `default`, `read_only`, `automation` o `experimental_admin` attraverso lo stesso endpoint `/mcp`. UMCP 1.0.6 aggiunge blocchi di Access Guard a runtime e un Access Journal sicuro per i segreti per la diagnostica delle ultime chiamate `tools/call`. La medesima politica viene applicata sia a `tools/list` sia a `tools/call`. Il pannello di controllo mostra se le funzioni connesse sono esposte, bloccate, nascoste o non disponibili.

## Sicurezza

- Il server si collega esclusivamente a `127.0.0.1`.
- Il server è disabilitato per impostazione predefinita.
- Le richieste richiedono un token Bearer presente nel file di handshake.
- Il controllo degli accessi per provider/strumento può nascondere gli strumenti da `tools/list` e bloccare l'esecuzione diretta di `tools/call`.
- I blocchi dell'Access Guard a runtime risiedono solo in memoria e vengono cancellati all'arresto del server.
- I token possono essere ruotati da **Tiny Tools -> AI -> Universal MCP**.
- Il file di handshake viene rimosso quando il server si arresta.
- I metadati delle richieste vengono registrati in `Saved/UnifiedMcpServer/logs/mcp_requests.jsonl`.
- La diagnostica degli accessi viene registrata in `Saved/UnifiedMcpServer/logs/access_audit.jsonl` omettendo le chiavi degli argomenti che assomigliano a segreti.

## Documentazione

| Documento | Scopo |
| --- | --- |
| [BUYER_GUIDE.md](BUYER_GUIDE.md) | Panoramica del prodotto, casi d'uso e limiti. |
| [QUICKSTART.md](QUICKSTART.md) | Prima configurazione e connessione del client. |
| [UserManual.md](UserManual.md) | Flusso di lavoro quotidiano nell'editor. |
| [TechnicalOverview.md](TechnicalOverview.md) | Architettura e comportamento del protocollo. |
| [INTEGRATION.md](INTEGRATION.md) | Come i plugin provider collegano gli strumenti. |
| [SettingsReference.md](SettingsReference.md) | Impostazioni e file salvati. |
| [CodeDocumentation.md](CodeDocumentation.md) | Struttura del codice sorgente e contratti. |
| [FAQ.md](FAQ.md) | Domande frequenti degli acquirenti. |
| [TROUBLESHOOTING.md](TROUBLESHOOTING.md) | Problemi comuni e soluzioni. |
| [ReleaseChecklist.md](ReleaseChecklist.md) | Check-list per il rilascio e il packaging per Fab. |

## Packaging

`Config/FilterPlugin.ini` include `/Documentation/...` e `/CHANGELOG.md` affinché i pacchetti Fab contengano questo set di documentazione.

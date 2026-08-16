<!-- doc-provenance: AKDB:plugins/UnifiedMcpServer/architecture.md; docs/architecture/plugins/UnifiedMcpServer/product-facts.yml; reconciled 2026-07-04 -->
# Manuale dell'utente

## Apertura delle impostazioni

Unified MCP Server si configura in:

```text
Edit -> Editor Settings -> Plugins -> Unified MCP Server
```

Impostazioni:

| Impostazione | Predefinito | Significato |
| --- | --- | --- |
| Enable MCP Server | disattivato | Consente al modulo dell'editor di eseguire il server MCP locale. |
| Server Port | 8732 | Porta TCP utilizzata su `127.0.0.1`. |
| Validate Tool Arguments | disattivato | Convalida opzionalmente gli argomenti di `tools/call` rispetto all'`inputSchema` di ciascun strumento prima di invocare il provider. |
| Access Profile | Default | Modalità di esposizione di alto livello: Default, Read Only, Automation o Experimental. |
| Disabled Provider IDs | vuoto | Nasconde e blocca tutti gli strumenti degli ID provider corrispondenti. |
| Allowed Tool Names | vuoto | Elenco consentito opzionale di nomi di strumenti o pattern con caratteri jolly esposti. Vuoto significa che tutti gli strumenti sono consentiti tranne se bloccati. |
| Blocked Tool Names | vuoto | Nasconde e blocca i nomi di strumenti esposti o i pattern con caratteri jolly. |
| Allowed Tool Groups | vuoto | Elenco consentito opzionale di gruppi derivati da annotazioni come `read_only`, `non_destructive` o `idempotent`. |
| Blocked Tool Groups | vuoto | Nasconde e blocca i gruppi derivati da annotazioni come `risky`, `destructive` o `open_world`. |
| Enable Access Journal | attivato | Scrive diagnostiche di accesso sicure per i segreti per `tools/call`. |
| Access Journal Ring Capacity | 500 | Numero di voci recenti mantenute in memoria per il pannello di controllo e le diagnostiche Blueprint. |
| Access Journal Max File Bytes | 5242880 | Dimensione massima di `access_audit.jsonl` prima della rotazione di un file. |

## Menu Tiny Tools

L'editor aggiunge azioni per il ciclo di vita e lo stato in **Tiny Tools -> AI -> Universal MCP**:

| Azione | Risultato |
| --- | --- |
| Open Control Panel | Apre il pannello di controllo UMCP con i pulsanti del ciclo di vita e l'albero delle funzioni connesse raggruppate per plugin. |
| Start Unified MCP Server | Avvia l'endpoint HTTP in loopback. |
| Stop Unified MCP Server | Arresta l'endpoint e rimuove il file di handshake. |
| Rotate MCP Token | Genera nuovi token Bearer dotati di ambito e riscrive il file di handshake. |

La sezione **AI** raggruppa Unified MCP Server insieme ad altri plugin di IA di Tiny Tool Development come l'Internal Index Service.

## Pannello di controllo (Control Panel)

Il pannello di controllo mostra:

| Area | Dettagli |
| --- | --- |
| Status | Stato di esecuzione/arresto, impostazione di avvio, URL dell'endpoint, presenza/conteggio dei token, conteggio delle richieste, conteggio dei provider, conteggio degli strumenti e percorso del file di handshake. |
| Actions | Avvia, arresta, ruota i token, apri la cartella agent e aggiorna. |
| Tabs | Connected Functions per provider/strumenti/schemi, e Access Activity per le chiamate recenti agli strumenti e i controlli di blocco a runtime. |
| Connected Functions | Gruppi di plugin espandibili con interruttori dei provider, righe degli strumenti, stato di accesso/idoneità, nomi degli strumenti MCP, descrizioni e tabelle degli schemi di input/output caricate in modo differito. |
| Access Activity | Chiamate recenti agli strumenti con dettagli su token/client/esito, conteggio dei blocchi a runtime, aggiorna, blocca/sblocca token/strumento e azioni per rimuovere i blocchi a runtime. |

### Layout di Connected Functions

Connected Functions utilizza un albero gerarchico simile al catalogo delle route di Capability Mesh:

1. **Gruppo plugin** — una riga per plugin con il conteggio delle interfacce e, quando il gruppo corrisponde a un singolo provider, un pulsante per abilitare/disabilitare l'accesso. Fai clic sulla freccia per mostrare o nascondere gli strumenti di quel plugin.
2. **Riga strumento** — una riga per strumento MCP collegato o funzionalità UCM dichiarata nella configurazione. Fai clic sulla freccia per mostrare o nascondere le tabelle degli schemi di input/output di quello strumento.

La disposizione delle colonne dipende dallo stato di espansione **all'interno di ciascun gruppo di plugin**:

| Stato | Colonne |
| --- | --- |
| Tutti gli strumenti compressi | `Provider`, `Ready`, `Tool`, `Description` (ampia) |
| Qualsiasi strumento espanso | `Provider`, `Ready`, `Tool`, `Input`, `Output`, `Description` |

**Raggruppamento provider:** gli strumenti diretti del provider appaiono sotto il relativo `GetProviderDisplayName()`. Gli strumenti delle route UCM appiattiti (`mesh_route_*`) appaiono sotto il **plugin proprietario** estratto dai metadati delle funzionalità di Capability Mesh (ad esempio Internal Index Service o SmartContentDiet), non sotto la voce dell'host mesh. Gli strumenti generici dell'host mesh come `mesh_list_routes` e `mesh_reload_setup` rimangono sotto **Unreal Capability Mesh**.

**Prestazioni:** il pannello carica i metadati degli strumenti in modo asincrono. I dati non modificati vengono serviti dalla cache nelle visite successive, negli avvii/arresti e nell'espansione/compressione. Utiliza **Refresh** per forzare un ricaricamento completo dopo le modifiche alla configurazione UCM.

Le righe contrassegnate con `Needs approval` sono funzionalità UCM che richiedono approvazione. Il loro suggerimento punta al percorso autonomo di auto-approvazione automatica **SPERIMENTALE** nelle route UCM o in `mesh_configure_experimental_self_approval`; utilizzalo solo per test a tuo rischio.

Le righe contrassegnate con `Blocked` o `Hidden` non sono esposte ai client MCP. UMCP le rimuove da `tools/list` e restituisce `tool_access_denied` se un client chiama comunque direttamente il nome dello strumento.

I blocchi a runtime dalla scheda **Access Activity** sono blocchi temporanei della sessione dell'editor. Non scrivono nelle impostazioni dell'editor, nascondono lo strumento da `tools/list` per il token interessato, rifiutano le chiamate dirette con `runtime_access_denied` e vengono cancellati all'arresto del server.

Le descrizioni degli strumenti includono annotazioni MCP quando i provider le pubblicano, come comportamenti di sola lettura, distruttivi, idempotenti o open-world. Il pannello mostra anche i gruppi derivati usati dalle politiche di accesso per profilo e per gruppo.

## File di connessione

File di handshake:

```text
Saved/UnifiedMcpServer/agent/mcp_endpoint.json
```

Registro delle richieste:

```text
Saved/UnifiedMcpServer/logs/mcp_requests.jsonl
```

Journal degli accessi:

```text
Saved/UnifiedMcpServer/logs/access_audit.jsonl
```

Il file di handshake contiene l'host locale, la porta, il `token` di compatibilità e i `tokens` dotati di ambito. Trattalo come una credenziale locale.

Il journal degli accessi omette le chiavi degli argomenti che assomigliano a segreti come token, secret, password, API key, authorization e bearer.

## Chiamate MCP supportate

Il server gestisce questi metodi JSON-RPC:

| Metodo | Comportamento |
| --- | --- |
| `initialize` | Restituisce la versione del protocollo, le funzionalità degli strumenti e le informazioni sul server. |
| `notifications/initialized` | Conferma l'inizializzazione del client. |
| `ping` | Restituisce un risultato vuoto. |
| `tools/list` | Restituisce tutti gli strumenti dei provider registrati, inclusi `inputSchema`, `outputSchema` opzionale, `annotations` opzionali e `_meta.toolsRevision`. |
| `tools/call` | Instrada un nome di strumento con prefisso al rispettivo provider e restituisce i risultati JSON sotto forma di testo e di `structuredContent` quando possibile. |

I metodi sconosciuti restituiscono un errore JSON-RPC di metodo non trovato.

## Strumenti per le attività dell'editor (Editor Job Tools)

UMCP espone strumenti di aggregazione delle attività dell'editor in sola lettura quando Unreal Capability Mesh è disponibile:

| Strumento | Scopo |
| --- | --- |
| `jobs_list` | Unisce le attività recenti delle route UCM fisse per IIS, SmartContentDiet, LLM Store e UMCP. Gli argomenti opzionali `provider_id` e `max_count` restringono il risultato. |
| `jobs_status` | Cerca un ID attività nella medesima tabella di route e restituisce l'ID del provider sorgente corrispondente. |

I plugin sorgente pubblicano la propria lista/stato delle attività dell'editor tramite route UCM e non dipendono da UMCP. Se UCM o una route non è disponibile, l'aggregazione salta quella route e restituisce comunque le attività dai provider disponibili.

## Lavorare con i provider

Unified MCP Server non contiene strumenti di progetto di per sé. Sono i provider ad aggiungerli. Un provider fornisce descrittori, schemi di input e logica di invocazione tramite `IUmcpToolProvider`.

Quando un provider è installato, gli strumenti appaiono nel formato:

```text
provider_tool
```

Ad esempio:

```text
mesh_route_iis_agent_search_v1_<hash>
```

Quando Unreal Capability Mesh è caricato, UMCP espone strumenti mesh generici:

```text
mesh_reload_setup
mesh_list_capabilities
mesh_list_routes
mesh_configure_experimental_self_approval
mesh_dry_run_route
mesh_execute_route
mesh_invoke_endpoint
```

UMCP pubblica inoltre ciascuna route Capability Mesh dichiarata come strumento MCP appiattito:

```text
mesh_route_<sanitized_route_id>_<hash>
```

Gli strumenti delle route appiattite accettano `mode: "execute"` o `mode: "dry_run"`. Se `input` o `input_json` viene omesso, gli argomenti rimanenti vengono trattati come l'oggetto di input della route. Per le route che legano internamente un `request_json` serializzato, UMCP riporta automaticamente gli argomenti appiattiti in `request_json`. Ogni strumento di route appiattito pubblica un `inputSchema`, un `outputSchema` e annotazioni MCP derivati dalla route, come `readOnlyHint`, `destructiveHint` e `openWorldHint`. Le route con effetti collaterali passano comunque attraverso i controlli di politica e di approvazione di Capability Mesh.

Utilizza `mesh_execute_route` per le operazioni con effetti collaterali in modo che la politica delle route e i controlli di approvazione di Capability Mesh rimangano attivi.

`mesh_configure_experimental_self_approval` è esplicitamente **SPERIMENTALE** e da utilizzare **a proprio rischio**. Può leggere o modificare l'auto-approvazione automatica di Capability Mesh a livello globale o per ID di route selezionati. L'abilitazione richiede `acknowledge_experimental_risk: true`.

## Note operative

- Utilizza una porta univoca per ciascuna istanza dell'editor.
- Ruota i token dopo aver condiviso log o screenshot che potrebbero mostrare il file di handshake.
- Arresta il server quando un agente esterno non necessita più di accesso.
- Se nessun plugin provider è abilitato, `tools/list` può legittimamente restituire un elenco vuoto.

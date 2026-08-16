<!-- doc-provenance: AKDB:plugins/UnifiedMcpServer/architecture.md; docs/architecture/plugins/UnifiedMcpServer/product-facts.yml; reconciled 2026-07-04 -->
# Riferimento delle impostazioni

Le impostazioni risiedono in `UUmcpSettings` e sono memorizzate nella configurazione dell'editor.

Apri:

```text
Edit -> Editor Settings -> Plugins -> Unified MCP Server
```

## Server

| Impostazione | Campo di configurazione | Predefinito | Note |
| --- | --- | --- | --- |
| Enable MCP Server | `bEnableServer` | `false` | Disattivato per impostazione predefinita. Se vero, il modulo dell'editor tenta di avviare il server all'avvio. |
| Server Port | `ServerPort` | `8732` | Porta TCP locale per l'endpoint di loopback. Intervallo valido: 1-65535. |

## Strumenti (Tools)

| Impostazione | Campo di configurazione | Predefinito | Note |
| --- | --- | --- | --- |
| Validate Tool Arguments | `bValidateToolArguments` | `false` | Se abilitato, UMCP convalida gli argomenti in arrivo di `tools/call` rispetto all'`inputSchema` di ciascun strumento prima di invocare il provider. La convalida è leggera: campi obbligatori, campi sconosciuti per `additionalProperties:false`, tipi primitivi ed enumerazioni. |

## Controllo degli accessi (Access Control)

| Impostazione | Campo di configurazione | Predefinito | Note |
| --- | --- | --- | --- |
| Access Profile | `AccessProfile` | `Default` | Modalità di esposizione di alto livello. `Default` conserva il comportamento precedente, `Read Only` espone solo gli strumenti annotati come sola lettura, `Automation` nasconde strumenti rischiosi/distruttivi/open-world/non classificati, ed `Experimental` consente intenzionalmente strumenti rischiosi tranne se bloccati manualmente. |
| Disabled Provider IDs | `DisabledProviderIds` | vuoto | ID provider nascosti da `tools/list` e bloccati al momento di `tools/call`. Il pannello di controllo può spostare i gruppi di singoli provider in questo elenco. |
| Allowed Tool Names | `AllowedToolNames` | vuoto | Elenco consentito opzionale di nomi di strumenti MCP esposti o pattern con caratteri jolly come `iis_search` o `mesh_route_*`. Vuoto significa che tutti gli strumenti sono consentiti tranne se disabilitati o bloccati. |
| Blocked Tool Names | `BlockedToolNames` | vuoto | Nomi di strumenti MCP esposti o pattern con caratteri jolly nascosti da `tools/list` e bloccati al momento di `tools/call`. |
| Allowed Tool Groups | `AllowedToolGroups` | vuoto | Elenco consentito opzionale di gruppi derivati da annotazioni come `read_only`, `non_destructive`, `idempotent`, `risky`, `destructive`, `open_world` o `unclassified`. |
| Blocked Tool Groups | `BlockedToolGroups` | vuoto | Gruppi derivati da annotazioni nascosti da `tools/list` e bloccati al momento di `tools/call`. |

L'ordine delle politiche è: provider disabilitato, blocco esplicito dello strumento, profilo di accesso, gruppo bloccato, elenchi consentiti opzionali di strumenti/gruppi, quindi esposto. Se un elenco consentito contiene voci, uno strumento viene esposto quando il suo nome o almeno un gruppo corrisponde. La medesima politica viene applicata sia a `tools/list` sia a `tools/call`.

I blocchi di Access Guard a runtime creati dal pannello di controllo o dagli aiuti Blueprint sono locali alla sessione e si collocano dopo la politica permanente. Nascondono gli strumenti corrispondenti da `tools/list`, rifiutano le chiamate dirette a `tools/call` e vengono cancellati all'arresto del server.

Gli strumenti di aggregazione delle attività dell'editor sono in sola lettura, ma passano comunque attraverso la stessa politica di provider/strumento/profilo di tutti gli altri strumenti MCP. Bloccare `jobs_*` o il provider `jobs` nasconde sia `jobs_list` sia `jobs_status`.

## Journal degli accessi (Access Journal)

| Impostazione | Campo di configurazione | Predefinito | Note |
| --- | --- | --- | --- |
| Enable Access Journal | `bEnableAccessJournal` | `true` | Scrive diagnostiche di accesso semantiche per `tools/call`. |
| Access Journal Ring Capacity | `AccessJournalRingCapacity` | `500` | Voci recenti mantenute in RAM per il pannello di controllo e le diagnostiche Blueprint. |
| Access Journal Max File Bytes | `AccessJournalMaxFileBytes` | `5242880` | Dimensione massima di `access_audit.jsonl` prima della rotazione di un file. |
| Access Journal Redacted String Limit | `AccessJournalRedactedStringLimit` | `128` | Lunghezza massima delle stringhe negli argomenti JSONL oscurati. |
| Access Journal Max RAM Entry Bytes | `AccessJournalMaxRamEntryBytes` | `8192` | Dimensione massima del JSON di argomenti sanificato mantenuto in memoria per voce. Le chiavi che assomigliano a segreti vengono omesse. |

## File generati

| File | Scopo |
| --- | --- |
| `Saved/UnifiedMcpServer/agent/mcp_endpoint.json` | Handshake di connessione contenente host, porta, token di compatibilità e token di sessione con ambito. |
| `Saved/UnifiedMcpServer/logs/mcp_requests.jsonl` | Registro dei metadati delle richieste. |
| `Saved/UnifiedMcpServer/logs/access_audit.jsonl` | Journal degli accessi semantico sicuro per i segreti per `tools/call`. |

## Impostazioni di sicurezza predefinite

- Server disabilitato per impostazione predefinita.
- Solo host di loopback.
- Token Bearer obbligatorio.
- I token possono essere ruotati da **Tiny Tools -> AI -> Universal MCP**.
- Il file di handshake viene eliminato quando il server si arresta.
- UMCP 1.0.5 scrive i token di sessione `default`, `read_only`, `automation` ed `experimental_admin`. Il campo legacy `token` rimane come token predefinito per compatibilità.
- UMCP 1.0.6 omette dalla diagnostica degli accessi le chiavi degli argomenti che assomigliano a segreti, tra cui token, secret, password, API key, authorization e bearer.

## Selezione della porta

Utilizza una porta diversa se:

- un'altra istanza dell'editor sta già utilizzando `8732`
- un servizio locale è collegato alla stessa porta
- progetti separati necessitano di endpoint MCP separati

L'URL del client è:

```text
http://127.0.0.1:<ServerPort>/mcp
```

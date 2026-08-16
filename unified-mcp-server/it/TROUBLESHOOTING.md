<!-- doc-provenance: AKDB:plugins/UnifiedMcpServer/architecture.md; docs/architecture/plugins/UnifiedMcpServer/product-facts.yml; reconciled 2026-07-04 -->
# Risoluzione dei problemi

## Il client riceve 401 Unauthorized

Verifica che il client invii:

```text
Authorization: Bearer <token>
```

Leggi il token di compatibilità corrente o il token con ambito da:

```text
Saved/UnifiedMcpServer/agent/mcp_endpoint.json
```

Se i token sono stati ruotati, aggiorna la configurazione del client.

## La risposta di stato esporrebbe i token

Le risposte del ciclo di vita e di stato riportano solo presenza dell'handshake, percorso, porta e conteggio dei token. Non devono mai restituire il JSON grezzo dell'handshake o i valori dei token Bearer. Utilizza il file di handshake locale per una configurazione autorizzata del client invece di copiare segreti tramite la diagnostica.

## Il file di handshake è mancante

Possibili cause:

- il server non è in esecuzione
- il server non è riuscito a collegarsi alla porta configurata
- il plugin è disabilitato
- l'editor non ha ancora avviato il modulo

Avvia il server da:

```text
Tiny Tools -> AI -> Universal MCP -> Start Unified MCP Server
```

## La porta è già in uso

Modifica la porta in:

```text
Edit -> Editor Settings -> Plugins -> Unified MCP Server
```

Quindi riavvia il server.

## `tools/list` non restituisce alcuno strumento

Unified MCP Server è solo l'host. Abilita Unreal Capability Mesh per ottenere gli strumenti generici `mesh_*`, oppure abilita un altro plugin provider. Verifica inoltre che il provider segnali lo stato di idoneità e abbia registrato la propria funzionalità modulare.

Verifica il controllo degli accessi in Editor Settings e nel pannello di controllo. ID provider disabilitati, profili di accesso restrittivi, elenchi consentiti non vuoti, pattern di strumenti bloccati o gruppi di strumenti bloccati nascondono intenzionalmente gli strumenti corrispondenti da `tools/list`.

Se gli strumenti generici `mesh_*` appaiono ma non compare alcuno strumento `mesh_route_*`, esegui `mesh_reload_setup` o fai clic su **Reload Setup** nel pannello di Capability Mesh, quindi aggiorna il client MCP. Gli strumenti delle route vengono generati dai manifesti delle route attivi in `Config/UnrealCapabilityMesh`.

Se appare `mesh_configure_experimental_self_approval`, trattalo come uno strumento di test **SPERIMENTALE** a tuo rischio. L'abilitazione richiede `acknowledge_experimental_risk: true` e modifica il comportamento di approvazione di Capability Mesh per route selezionate o per tutte le route che richiedono approvazione.

Se l'auto-approvazione automatica è stata modificata nell'interfaccia utente delle route UCM ma il client MCP mostra ancora le vecchie descrizioni delle route, chiama nuovamente `tools/list` o riconnetti/aggiorna il client. UMCP ricarica la configurazione UCM prima di elencare gli strumenti delle route e `mesh_list_routes` restituisce direttamente lo stato corrente di `experimental_self_approval_*`.

## Connected Functions appare obsoleto nel pannello di controllo

Il pannello di controllo mantiene in cache i metadati degli strumenti per velocizzare le visite successive. Dopo aver modificato la configurazione UCM, aggiunto provider o ricaricato le route, fai clic su **Refresh** nel pannello di controllo per forzare un ricaricamento completo delle funzioni connesse. L'avvio/arresto e l'espansione/compressione riutilizzano la cache quando lo snapshot sottostante non è cambiato.

## Il client Stdio non può connettersi direttamente

Il plugin fornisce un trasporto HTTP. I client che supportano solo Stdio necessitano di un bridge installato dall'utente come `mcp-remote`.

## La chiamata allo strumento restituisce uno strumento sconosciuto

Verifica il nome esposto da `tools/list`. Utilizza il nome con prefisso:

```text
<providerId>_<toolName>
```

Non chiamare direttamente i nomi locali del provider.

## La chiamata allo strumento restituisce `tool_access_denied`

Il nome dello strumento esiste, ma il controllo degli accessi di UMCP lo ha bloccato. Verifica `AccessProfile`, rimuovi l'ID del provider da `DisabledProviderIds`, regola `AllowedToolNames` o `AllowedToolGroups`, oppure rimuovi la voce corrispondente da `BlockedToolNames` o `BlockedToolGroups`.

## La build fallisce su UE 5.6 con errori relativi allo standard C++

Assicurati che i moduli UMCP e i moduli bridge dipendenti vengano compilati con C++20. Gli header del motore di UE 5.6 utilizzano la sintassi C++20 negli header principali.

## Posizione del registro delle richieste

I metadati delle richieste vengono scritti in:

```text
Saved/UnifiedMcpServer/logs/mcp_requests.jsonl
```

Utilizzalo per ispezionare nomi di metodi, codici di stato, latenza e codici di errore.

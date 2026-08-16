<!-- doc-provenance: AKDB:plugins/UnifiedMcpServer/architecture.md; docs/architecture/plugins/UnifiedMcpServer/product-facts.yml; reconciled 2026-07-04 -->
# Guida rapida

## 1. Abilitare il plugin

Abilita `Unified MCP Server` nel browser dei plugin e riavvia l'editor se Unreal lo richiede.

## 2. Abilitare il server

Apri:

```text
Edit -> Editor Settings -> Plugins -> Unified MCP Server
```

Attiva **Enable MCP Server**. Mantieni la porta predefinita `8732`, a meno che un altro servizio locale non la stia già utilizzando.

## 3. Avviare il server

Utilizza:

```text
Tiny Tools -> AI -> Universal MCP -> Start Unified MCP Server
```

Per lo stato, i pulsanti del ciclo di vita e l'albero delle funzioni connesse raggruppate per plugin, utilizza:

```text
Tiny Tools -> AI -> Universal MCP -> Open Control Panel
```

L'area delle funzioni connesse raggruppa gli strumenti per plugin, supporta l'espansione differita degli schemi e mantiene in cache i metadati non modificati tra una visita e l'altra. Utilizza **Refresh** dopo le modifiche alla configurazione UCM per forzare un ricaricamento completo.

In UMCP 1.0.3 e versioni successive, il pannello di controllo mostra anche lo stato di accesso. Disabilita un gruppo relativo a un singolo provider per nascondere i suoi strumenti da `tools/list` e bloccare l'esecuzione diretta di `tools/call`.

Se l'impostazione è abilitata prima dell'avvio dell'editor, il server tenta di avviarsi automaticamente al caricamento del modulo dell'editor.

## 4. Leggere il file di handshake

Dopo l'avvio, l'editor scrive:

```text
Saved/UnifiedMcpServer/agent/mcp_endpoint.json
```

Esempio di struttura:

```json
{
  "host": "127.0.0.1",
  "port": 8732,
  "token": "<default-token>",
  "tokens": {
    "default": {"token": "<default-token>", "scope": "default", "profile": "Project Settings"},
    "read_only": {"token": "<read-only-token>", "scope": "read_only", "profile": "Read Only"},
    "automation": {"token": "<automation-token>", "scope": "automation", "profile": "Automation"},
    "experimental_admin": {"token": "<experimental-token>", "scope": "experimental_admin", "profile": "Experimental"}
  }
}
```

Utilizza il campo di compatibilità `token` oppure scegline uno all'interno di `tokens`:

```text
Authorization: Bearer <token-selezionato>
```

## 5. Connettere un client

I client MCP in grado di gestire HTTP possono chiamare:

```text
http://127.0.0.1:8732/mcp
```

Con il server in esecuzione, apri il pannello di controllo e fai clic su **Copy MCP Client Config**.
Questo copierà un frammento `mcp.json` pronto da incollare contenente l'URL dell'endpoint e il token Bearer predefinito corrente. Incollalo nel file di configurazione del tuo client MCP.
Dopo aver eseguito **Rotate Tokens**, copia nuovamente il frammento poiché il token Bearer è cambiato.

In fase di `initialize`, UMCP negozia la `protocolVersion`: quando il client richiede una versione supportata (`2025-06-18`, `2025-03-26` o `2024-11-05`), il server risponde con quella versione; altrimenti risponde con `2024-11-05`. Un controllo del client tramite `GET /mcp` restituisce HTTP 405 poiché UMCP utilizza il sottoinsieme di risposte JSON Streamable-HTTP e non ospita uno stream SSE da server a client.

I client che supportano solo Stdio necessitano di un bridge installato dall'utente come `mcp-remote`. Tale bridge non è incluso in questo plugin.

## 6. Aggiungere strumenti (opzionale)

Il server funziona in modo autonomo; questo passaggio aggiunge gli strumenti che i client possono chiamare. Hai due opzioni indipendenti e devi selezionare solo ciò che si adatta al tuo progetto:

- **Un tuo plugin (o qualsiasi plugin):** registra una funzionalità modulare `IUmcpToolProvider` e i suoi strumenti appariranno automaticamente nel formato `<providerId>_<toolName>`. Non è richiesto alcun plugin catalogo. Vedi [INTEGRATION.md](INTEGRATION.md).
- **Opzionale — Unreal Capability Mesh (UCM):** se possiedi anche Unreal Capability Mesh, la sua abilitazione aggiunge gli strumenti `mesh_*` dichiarati nella configurazione. I chiamanti possono così eseguire le route UCM configurate (ad esempio il pacchetto di contesto IIS, il posizionamento PRS, i consigli di migrazione SCD e l'amministrazione DataAsset/DataTable) tramite `mesh_execute_route` o gli strumenti diretti generati `mesh_route_*`. Espone inoltre `mesh_configure_experimental_self_approval`; questo strumento è **SPERIMENTALE**, richiede una conferma esplicita del rischio al momento dell'abilitazione ed è riservato a flussi di test a proprio rischio.

Entrambe le opzioni sono facoltative: il server, l'handshake e la connessione del client (passaggi 1–5) funzionano anche senza alcun provider installato.

## 7. Arrestare o ruotare

Utilizza il menu Tiny Tools:

```text
Tiny Tools -> AI -> Universal MCP -> Stop Unified MCP Server
Tiny Tools -> AI -> Universal MCP -> Rotate MCP Token
```

L'arresto rimuove il file di handshake. La rotazione lo riscrive con nuovi token dotati di ambito. Entrambe le azioni sono disponibili anche dal pannello di controllo.

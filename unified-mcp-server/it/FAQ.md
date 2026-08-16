<!-- doc-provenance: AKDB:plugins/UnifiedMcpServer/architecture.md; docs/architecture/plugins/UnifiedMcpServer/product-facts.yml; reconciled 2026-07-04 -->
# FAQ (Domande frequenti)

## Questo plugin include un modello di IA?

No. Unified MCP Server è un'infrastruttura di connessione. Espone gli strumenti dei plugin provider ai client MCP locali.

## Include un eseguibile autonomo?

No. Il server viene eseguito all'interno dell'Unreal Editor e non include alcun eseguibile esterno.

## Include Node.js, Python o mcp-remote?

No. I client che supportano solo Stdio potrebbero necessitare di un bridge installato dall'utente come `mcp-remote`, ma questo non è fornito in bundle.

## Il server è abilitato per impostazione predefinita?

No. È disabilitato per impostazione predefinita e deve essere abilitato in Editor Settings o avviato manualmente da **Tiny Tools -> AI -> Universal MCP**.

## Rimane in ascolto sulla rete?

No. Si collega esclusivamente a `127.0.0.1`.

## Come vengono autenticate le richieste?

Il server genera token Bearer dotati di ambito all'avvio. I client li leggono da `Saved/UnifiedMcpServer/agent/mcp_endpoint.json` e inviano un token nell'intestazione `Authorization`.

## Supporta più token dotati di ambito?

Sì. UMCP 1.0.5 scrive i token di sessione `default`, `read_only`, `automation` ed `experimental_admin` nel file di handshake. Tutti i token utilizzano lo stesso endpoint locale `/mcp`; l'ambito modifica quale profilo di accesso viene forzato per `tools/list` e `tools/call`.

## Perché il mio elenco degli strumenti è vuoto?

Il server di base è un'infrastruttura. Abilita Unreal Capability Mesh per ottenere il provider generico `mesh_*`, oppure abilita un altro plugin che registri un `IUmcpToolProvider`. Verifica inoltre il controllo degli accessi di UMCP: provider disabilitati, profili restrittivi, elenchi consentiti attivi, pattern di strumenti bloccati o gruppi di strumenti bloccati possono nascondere intenzionalmente gli strumenti da `tools/list`.

## Posso nascondere o bloccare provider e strumenti specifici?

Sì. UMCP mantiene un unico endpoint locale e applica il controllo degli accessi prima che gli strumenti raggiungano i client MCP. Disabilita gli ID dei provider, scegli un profilo di accesso, aggiungi nomi esatti o con caratteri jolly di strumenti o gruppi agli elenchi consentiti/bloccati, oppure utilizza l'interruttore dei provider nel pannello di controllo per gruppi relativi a un singolo provider. La medesima politica viene applicata sia a `tools/list` sia a `tools/call`.

## Posso bloccare temporaneamente uno strumento durante una sessione?

Sì. UMCP 1.0.6 aggiunge blocchi di Access Guard a runtime dal pannello di controllo e dalle diagnostiche Blueprint. I blocchi a runtime possono nascondere uno strumento per un token con ambito o a livello globale, rifiutare le chiamate dirette con `runtime_access_denied` e vengono cancellati all'arresto del server.

## Il journal degli accessi memorizza segreti?

È progettato per diagnostiche sicure rispetto ai segreti. Le chiavi degli argomenti che assomigliano a segreti come token, secret, password, API key, authorization e bearer vengono omesse dalla memoria e dal journal degli accessi JSONL. Le stringhe oscurate e le voci RAM sanificate sono limitate dalle impostazioni.

## Che cos'è `mesh_configure_experimental_self_approval`?

È uno strumento provider di Capability Mesh per l'auto-approvazione automatica **SPERIMENTALE**. Può modificare la possibilità che le route UCM che richiedono approvazione si auto-approvino a livello globale o per ID di route. L'abilitazione richiede `acknowledge_experimental_risk: true` ed è riservata a flussi di test a proprio rischio.

## Più plugin possono aggiungere strumenti?

Sì. Qualsiasi plugin può registrare un `IUmcpToolProvider`. I nomi degli strumenti hanno come prefisso l'ID del provider.

## I client possono vedere i parametri degli strumenti e i rischi?

Sì. `tools/list` include l'`inputSchema` di ciascun strumento, l'`outputSchema` opzionale e le annotazioni dello strumento opzionali. Gli strumenti delle route UCM li derivano dai collegamenti delle route, dai manifesti degli schemi, dalle politiche e dagli effetti collaterali.

## Come posso ispezionare gli strumenti collegati nell'editor?

Apri **Tiny Tools -> AI -> Universal MCP -> Open Control Panel**. L'area delle funzioni connesse raggruppa gli strumenti per plugin, supporta l'espansione differita degli schemi di input/output e mantiene in cache i metadati non modificati tra una visita e l'altra. Fai clic su **Refresh** dopo le modifiche alla configurazione UCM per forzare un ricaricamento completo.

## Perché UMCP ha rifiutato gli argomenti del mio strumento prima dell'esecuzione del provider?

L'impostazione `Validate Tool Arguments` è abilitata. UMCP verifica quindi gli argomenti in arrivo rispetto all'`inputSchema` dello strumento selezionato e restituisce `invalid_tool_arguments` in caso di campi obbligatori mancanti, campi sconosciuti non consentiti, discrepanze di tipo o discrepanze di enumerazione.

## Quali versioni di Unreal Engine sono supportate?

Il plugin è progettato per plugin di codice Unreal Engine 5.x e utilizza C++20 per l'attuale compatibilità con UE 5.6.

## È destinato ai giochi impacchettati (Packaged Games)?

No. L'attuale server è un'infrastruttura dell'editor per strumenti e agenti locali.

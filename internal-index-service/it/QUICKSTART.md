<!-- doc-provenance: SAD architecture.md sections 1,3,6,7,8; facts product-facts.yml; reconciled 2026-07-16 -->
# Guida rapida

## 1. Abilitare il plugin

Abilita `Internal Index Service` nel browser dei plugin. Riavvia l'editor se Unreal lo richiede.

## 2. Aprire il pannello di controllo

Usa:

```text
Tiny Tools -> AI -> Internal Index Service -> Open Internal Index Service
```

Il pannello di controllo si apre sulla Dashboard.

## 3. Configurare le impostazioni

Apri:

```text
Edit -> Project Settings -> Plugins -> Internal Index Service
```

Prima configurazione consigliata:

| Impostazione | Valore |
| --- | --- |
| Vector Backend | `jsonl_bruteforce` |
| Vector Storage Format | `Int8 Per-Vector Scale` |
| Allow Experimental Vector Formats | `false` |
| Index Root | vuoto |

Un campo `Index Root` vuoto indica che IIS utilizza:

```text
Saved/InternalIndexService
```

I criteri di archiviazione predefiniti utilizzano il ridimensionamento int8 per vettore per le partizioni HNSW. È la modalità compatta normale. `Float32` è disponibile per esecuzioni ad alta fedeltà/debug; `Experimental Global Scale` deve rimanere disattivato a meno che non si stiano valutando intenzionalmente i compromessi di recall.

## 4. Importare chunk preparati

Usa la scheda Imports nel pannello di controllo oppure chiama l'API del servizio fornendo un file JSONL con i chunk preparati. I chunk preparati provengono normalmente da una pipeline di estrazione complementare come Unreal Integration Intelligence.

L'importazione scrive report nella cartella salvata di IIS e aggiorna l'archivio dei chunk.

## 5. Ricostruire il catalogo

Usa l'azione **Rebuild** della Dashboard o la scheda Catalog. IIS legge i chunk importati, normalizza lo stato del ciclo di vita e scrive un report sulla creazione del catalogo.

## 6. Ricerca

Usa la scheda Search:

- la ricerca lessicale funziona a partire dal catalogo locale
- la ricerca vettoriale richiede gli embedding
- la ricerca ibrida combina entrambe quando sono presenti vettori

## 7. Generare embedding (Opzionale – aggiunge la ricerca vettoriale, richiede LLM Store)

La ricerca lessicale (passaggi 1–6) funziona autonomamente senza altri plugin. Le ricerche vettoriale e ibrida sono un miglioramento opzionale: configura prima il plugin **LLM Store**, quindi IIS chiederà una route al registro degli esecutori di embedding, creerà job e scriverà report di embedding. Esegui i job dalla scheda Embeddings. Senza LLM Store, IIS continuerà comunque ad importare, creare e cercare in modalità lessicale.

## 8. Esporre gli strumenti agente (Opzionale – richiede Unified MCP Server + Capability Mesh)

Questo passaggio è opzionale ed è necessario solo se desideri che gli agenti IA chiamino IIS. Installa e abilita:

- Unified MCP Server
- Unreal Capability Mesh

Assicurati che il profilo Capability Mesh del progetto includa le route dell'agente IIS (ad esempio `iis.agent.search.v1`). Quindi avvia Unified MCP Server. Ciascuna funzionalità agente di IIS viene esposta come route UCM autonoma, appiattita in uno strumento MCP `mesh_route_*`, come ad esempio:

```text
mesh_route_iis_agent_search_v1_<hash>
mesh_route_iis_agent_get_context_pack_v1_<hash>
mesh_route_iis_agent_get_chunk_v1_<hash>
mesh_route_iis_agent_get_source_references_v1_<hash>
mesh_route_iis_agent_find_usages_v1_<hash>
mesh_route_iis_agent_explain_blueprint_v1_<hash>
```

In alternativa, chiama `mesh_execute_route` con `route_id` impostato sull'ID della route (ad esempio `iis.agent.search.v1`).

## 9. Ottimizzazione runtime (Opzionale – nessun plugin aggiuntivo)

La superficie di controllo runtime fornita è **autarchica** (autark): non richiede UCM o UMCP.

Apri la console del log di output dell'editor ed esegui:

```text
iis.control.state
```

Estratto di risposta di esempio (il valore predefinito di `efSearch` è 64):

```json
{"ok":true,"errorCode":"","errorMessage":"","efSearch":64,...}
```

Aumenta il valore di `efSearch` per le query in tempo reale:

```text
iis.control.tune {"efSearch":128}
```

Conferma la modifica:

```text
iis.control.state
```

Esempio dopo l'ottimizzazione:

```json
{"ok":true,"errorCode":"","errorMessage":"","efSearch":128,...}
```

Le modifiche sono **transitorie** (transient) fino a quando non esegui `iis.control.persist`. Usa `iis.control.reset` per ricaricare la configurazione. Consulta `UserManual.md` per l'elenco completo dei comandi da console e dell'API Blueprint.

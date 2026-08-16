<!-- doc-provenance: AKDB:plugins/UnrealCapabilityMesh/architecture.md; docs/architecture/plugins/UnrealCapabilityMesh/product-facts.yml; reconciled 2026-07-19 -->
# Manuale utente

## Pannello di controllo

Apri il pannello da:

```text
Tools -> Unreal Capability Mesh
```

Il pannello è una vista operativa tecnica per l'interoperabilità guidata da manifesti. Utilizza un banner di stato e pagine focalizzate anziché raggruppare tutti gli strumenti in un'unica vista estesa.

Pagine:

- `Overview`: profilo attivo, conteggio inventario, conteggio disponibilità, flusso di configurazione e contratto MCP.
- `Capabilities`: ID delle funzionalità caricate, endpoint, effetti collaterali, disponibilità, avvisi e manifesti sorgente.
- `Routes`: catalogo dei percorsi oltre a esecuzione di prova (dry-run) e input/output di esecuzione.
- `Governance`: vocabolario degli effetti collaterali attivo e decisioni sulle regole.
- `Tiny Tools`: interruttori dei pacchetti di configurazione per i contenuti Tiny Tool Development.
- `Setup Editor`: editor JSON sensibile ai tipi per i manifesti di configurazione del progetto, campioni di riferimento in sola lettura e il playground non vincolante.
- `Config Admin`: destinazioni di configurazione approvate e preimpostazioni dei percorsi per operazioni di elenco/lettura/scrittura.
- `Diagnostics`: messaggi di validazione della configurazione, individuazione e ricaricamento.
- `Adapter`: generatore di manifesti di avvio per aggiungere funzionalità dichiarate nella configurazione senza dipendenze da bridge.

## Tiny Tools

La pagina `Tiny Tools` è guidata dai manifesti del catalogo presenti in:

```text
Config/UnrealCapabilityMesh/tool_catalogs/
```

Il primo interruttore stabilisce se il progetto debba utilizzare i contenuti di configurazione Tiny Tool Development. Quando è disattivato, tutte le voci del catalogo vengono rimosse dal profilo attivo. I singoli interruttori degli strumenti aggiungono o disattivano le voci dei pacchetti dichiarate dal catalogo:

- manifesti delle funzionalità
- manifesti degli endpoint
- manifesti degli schemi
- manifesti delle regole
- manifesti dei percorsi
- manifesti delle trasformazioni
- manifesti degli adattatori
- ID delle destinazioni di configurazione

Si tratta di un modello di disattivazione, non di eliminazione di file. I file manifesto rimangono nel progetto e possono essere riabilitati in seguito.

I pacchetti Tiny Tool sono intenzionalmente suddivisi per proprietà. IIS, LLM Store e UII possono essere abilitati indipendentemente. I flussi di lavoro tra plugin sono interruttori di percorso separati, in modo che un progetto possa utilizzare solo IIS, solo LLM Store, UII+IIS o IIS+LLM Store senza possedere l'intero stack.

Il campo del profilo `enabled_config_target_ids` limita le destinazioni di configurazione visibili in Config Admin. Se il campo è assente, Config Admin mantiene il comportamento precedente e scansiona ogni manifesto di destinazione.

## Setup Editor

La pagina `Setup Editor` modifica i manifesti locali del progetto in `Config/UnrealCapabilityMesh` con campi sensibili ai tipi:

- booleani per gli interruttori di criteri e profilo
- array di stringhe per `enabled_*_manifests`
- campi enumerati come `invocation_mode` e `side_effects`
- oggetti annidati e array di oggetti dai manifesti di percorsi, funzionalità ed endpoint

L'albero a sinistra presenta tre radici:

1. `Project Setup` — manifesti di progetto modificabili, incluso `project_profile.json`.
2. `Playground Sandbox` — manifesti sandbox modificabili in `playground/` senza un reale vincolo di plugin. Usa `Add playground to profile` per testare i fallimenti di attivazione, oppure abilita l'elemento di catalogo `Setup Editor Playground` da `Tiny Tools`.
3. `Reference Samples` — manifesti Tiny Tool inclusi in sola lettura raggruppati per plugin di catalogo, oltre ai campioni principali UCM. Usa `Copy to project` per duplicare un manifesto di riferimento nella configurazione del progetto.

Azioni della barra degli strumenti:

- `Save` / `Revert` — scrive o scarta il file manifesto attivo.
- `Validate file` — esegue `FCapabilityMeshSetupLoader::ValidateManifestFile` sul file selezionato.
- `Reload Setup` — ricarica il mesh attivo dopo modifiche al profilo o ai manifesti.
- `Open source folder` — apre il percorso del plugin C++ associato da `editor/plugin_source_hints.json` quando viene selezionato un nodo di riferimento del plugin.

Le regole di tipizzazione dei campi risiedono in `editor/manifest_field_schema.json`.

## Reload Setup

`Reload Setup` richiama `FCapabilityMeshService::ReloadSetup`.

Esegue la seguente sequenza:

1. Cancella registri e report precedenti.
2. Individua la configurazione UCM inclusa, le radici di configurazione locali dei plugin abilitati e l'override opzionale del progetto.
3. Unisce i rispettivi file `project_profile.json` in ordine di priorità.
4. Carica funzionalità, endpoint, schemi, regole, percorsi, trasformazioni e adattatori.
5. Registra le definizioni caricate.
6. Scrive la diagnostica della configurazione e del registro.
7. Esegue l'individuazione.
8. Scrive i report di individuazione e compatibilità.

I manifesti di proprietà del provider devono rimanere nella cartella `Config/UnrealCapabilityMesh/` del relativo plugin. I manifesti locali al progetto hanno una priorità più elevata e servono per override intenzionali o percorsi composti di proprietà del progetto. La duplicazione delle definizioni del provider nel progetto può generare avvisi di override e mascherare la proprietà.

Quando il plugin opzionale Tiny Tool Execution Integration Bridge è abilitato, il suo modulo Editor chiama `ReloadSetup` prima di registrare e individuare gli strumenti UCM proiettati. UCM mantiene la proprietà delle definizioni dei percorsi risultanti e di ogni decisione relativa ai criteri.

## Discovered Capabilities

La vista delle funzionalità individuate elenca ID funzionalità, ID provider, modalità di interoperabilità e disponibilità. La disponibilità può essere disponibile, non disponibile, non sicura, schema mancante, approvazione richiesta o plugin non caricato.

## Diagnostics

La vista diagnostica mostra gli errori e gli avvisi di validazione della configurazione oltre ai messaggi restituiti dal ricaricamento/dall'individuazione. Consultala per prima cosa se un percorso o un endpoint non appare.

## Routes

Inserisci un ID di percorso ed esegui una prova (dry run). UCM risolve i passaggi del percorso, verifica la disponibilità delle funzionalità, aggrega gli effetti collaterali, valuta le regole e scrive un report del percorso.

Inserisci l'input JSON del percorso ed esegui il percorso quando l'esecuzione di prova è pulita. UCM pianifica prima il percorso, blocca le violazioni dei criteri e i percorsi che richiedono l'esecuzione di prova, quindi invoca ciascun endpoint nell'ordine dei passaggi. I percorsi che richiedono approvazione devono includere `approval_granted: true` o `approval: "granted"` nell'input del percorso prima di essere eseguiti, a meno che l'override dell'auto-approvazione automatica **SPERIMENTALE** non sia attivo per quel percorso. Gli output dei passaggi e l'output del percorso vengono scritti in `Saved/UnrealCapabilityMesh/route_execution_reports/`.

### Route Catalog

Il **Route Catalog** nella pagina Routes elenca tutti i percorsi caricati dai manifesti di configurazione in una tabella raggruppata per plugin:

| Colonna | Contenuto |
| --- | --- |
| Plugin / Route | Gruppi di plugin espandibili e righe di percorsi con dettagli su criteri, passaggi, endpoint, effetti collaterali e manifesti sorgente |
| Approve all at own risk | Controlli per l'auto-approvazione automatica **SPERIMENTALE** |

Intestazione di colonna:

- **Approve all at own risk** — interruttore globale per ogni percorso soggetto ad approvazione nel profilo attivo. Quando è abilitato, le caselle di controllo per singolo percorso sono disabilitate perché tutti i percorsi soggetti ad approvazione ereditano l'override.

Righe del plugin:

- Freccia di espansione/compressione, nome visualizzato del plugin, numero di percorsi e una casella di controllo dell'approvazione per singolo plugin quando quel plugin possiede percorsi soggetti ad approvazione.

Righe dei percorsi:

- Freccia di espansione/compressione, ID del percorso e testo di dettaglio del percorso dal piano di esecuzione di prova (dry-run).
- Percorsi soggetti ad approvazione: casella di controllo per singolo percorso (a meno che **Approve all** non sia attivo).
- Percorsi che non richiedono approvazione: `n/a` con un tooltip che spiega che non si applica alcuna porta di approvazione.

Un avviso arancione sopra il catalogo indica che l'auto-approvazione automatica attiva un'ampia deviazione dai criteri. Le regole di diniego corrispondenti, i controlli sulla modifica di asset/progetto del percorso, i requisiti di approvazione e i requisiti di esecuzione di prova vengono ignorati; i percorsi abilitati possono quindi modificare lo stato dell'editor senza tali salvaguardie.

Le stesse impostazioni persistono in `project_profile.json` (`experimental_self_approval_all_routes`, `experimental_self_approved_route_ids`) e possono essere lette o modificate tramite MCP con `mesh_configure_experimental_self_approval`; l'abilitazione tramite MCP richiede `acknowledge_experimental_risk: true`. Mantieni disattivata l'auto-approvazione automatica per il normale utilizzo in produzione.

La pagina `Config Admin` può preparare gli ID dei percorsi di amministrazione della configurazione standard e gli involucri JSON nel runner dei percorsi. Ciò consente a MCP, agli utenti dell'editor e all'automazione di condividere lo stesso contratto di percorso.

## Amministrazione di DataAsset e DataTable

`UCapabilityMeshAssetAdminSubsystem` espone operazioni richiamabili tramite JSON per l'amministrazione di DataAsset/DataTable:

- `ExportAdminSurfaceJson`: esporta un DataAsset o una DataTable in un involucro di amministrazione portatile e può scriverlo in `Saved/UnrealCapabilityMesh/asset_admin`.
- `ImportAdminSurfaceJson`: importa un involucro precedentemente esportato in un DataAsset o in una DataTable esistente.
- `SyncAdminSurfaceJson`: copia i campi modificabili da un DataAsset a una riga di DataTable o da una riga di DataTable a un DataAsset.

Le DataTables composte (Composite DataTables) sono fonti di esportazione sicure. Le scritture dirette in una DataTable composta sono bloccate; indirizza l'operazione alla DataTable figlia concreta che deve possedere la riga.

Esempio di input di percorso per un percorso di sincronizzazione con modifica:

```json
{
  "approval_granted": true,
  "request_json": "{\"source_object_path\":\"/Game/Config/DA_Settings.DA_Settings\",\"target_object_path\":\"/Game/Config/DT_Settings.DT_Settings\",\"mode\":\"data_asset_to_data_table\",\"row_name\":\"Default\"}"
}
```

## Amministrazione della configurazione

`UCapabilityMeshConfigAdminSubsystem` espone le destinazioni di configurazione approvate. Questo è il percorso MCP standard per le impostazioni dei plugin e i file di configurazione del progetto.

Le destinazioni sono dichiarate in:

```text
Config/UnrealCapabilityMesh/config_targets/
```

Percorsi comuni:

- `capability_mesh.config_admin.list_targets.v1`
- `capability_mesh.config_admin.read_target.v1`
- `capability_mesh.config_admin.write_target.v1`

Esempio di lettura:

```json
{
  "request_json": "{\"target_id\":\"example_plugin.settings\"}"
}
```

Esempio di scrittura:

```json
{
  "approval_granted": true,
  "request_json": "{\"target_id\":\"example_plugin.settings\",\"fields\":{\"bEnabled\":true}}"
}
```

Le destinazioni di istanze di oggetti, come un oggetto di configurazione basato su un asset, richiedono anche `object_path` nel JSON della richiesta. Le destinazioni di file JSON accettano `payload` o `payload_json`.

## Accesso MCP

`UCapabilityMeshMcpGatewaySubsystem` espone il ricaricamento della configurazione, l'elenco delle funzionalità, l'esecuzione di prova del percorso, l'esecuzione del percorso e l'invocazione degli endpoint come funzioni richiamabili in JSON. Il server Unified MCP si collega a questo gateway tramite il provider generico `mesh` quando entrambi i plugin sono caricati.

Nomi comuni degli strumenti UMCP:

- `mesh_reload_setup`
- `mesh_list_capabilities`
- `mesh_list_routes`
- `mesh_configure_experimental_self_approval`
- `mesh_dry_run_route`
- `mesh_execute_route`
- `mesh_invoke_endpoint`

Unified MCP Server appiattisce inoltre i percorsi dichiarati in strumenti MCP diretti denominati `mesh_route_<sanitized_route_id>_<hash>`. Questi strumenti accettano `mode: "dry_run"` per l'analisi o `mode: "execute"` per l'esecuzione. Se non viene fornito alcun campo `input` o `input_json`, gli argomenti rimanenti diventano l'oggetto di input del percorso. UCM esporta `input_schema`, `output_schema` e `tool_annotations` derivati dai percorsi tramite `mesh_list_routes`; UMCP li pubblica come `inputSchema`, `outputSchema` e annotazioni MCP per ciascun strumento `mesh_route_*`. Per i percorsi comuni che si collegano a `request_json`, UMCP rispecchia anche gli argomenti appiattiti in quel campo di richiesta serializzato affinché l'AI possa chiamare gli strumenti con parametri denominati comprensibili.

Utilizza `mesh_execute_route` per l'importazione, la sincronizzazione e la scrittura di configurazioni di DataAsset/DataTable affinché i criteri del percorso e i controlli di approvazione rimangano attivi. Utilizza `mesh_configure_experimental_self_approval` solo per flussi di lavoro di test o a proprio rischio **SPERIMENTALI**; può abilitare la deviazione ampia dai criteri a livello globale o per ID di percorsi selezionati. Utilizza `mesh_list_routes` per verificare lo stato corrente visibile a MCP; segnala il flag sperimentale globale, gli override dei percorsi selezionati e il piano effettivo deviato per ciascun percorso.

## Integrazione UCM primaria

Il profilo del progetto attivo connette i prodotti Tiny Tool Development con i percorsi dichiarati nella configurazione. Utilizza questo percorso UCM come modello di integrazione normale. I Freebie Bridges sono destinati solo a team privi di UCM o a sviluppatori che desiderano esempi di adattatori diretti.

- `uii_to_iis_context_pack.v1`: evidenze UII -> flusso di importazione/ricerca/pacchetto di contesto IIS, con esecuzione del percorso di incorporamento LLM Store ove configurato.
- `prs.build_asset_move_plan.v1`, `prs.preview_plan.v1`, `prs.apply_plan.v1`, `prs.rollback.v1`: flussi di lavoro di posizionamento PRS tramite criteri di percorso UCM e approvazione.
- `scd.migration_advice_from_handoff.v1`: contratto/involucro di consegna UII -> indicazioni di migrazione consultiva SmartContentDiet tramite UCM.
- `capability_mesh.asset_admin.export.v1`, `capability_mesh.asset_admin.import.v1`, `capability_mesh.asset_admin.sync.v1`: amministrazione di DataAsset/DataTable tramite il mesh.
- `capability_mesh.config_admin.list_targets.v1`, `capability_mesh.config_admin.read_target.v1`, `capability_mesh.config_admin.write_target.v1`: amministrazione delle impostazioni approvate e dei file di configurazione tramite il mesh.

I percorsi di modifica di progetti o asset richiedono comunque un'approvazione esplicita del percorso a meno che l'override dell'auto-approvazione automatica **SPERIMENTALE** non sia attivo per quel percorso.

## Regole

Le regole stabiliscono se un percorso è consentito, richiede approvazione, richiede un'esecuzione di prova (dry-run) o è bloccato. Le regole sono ordinate per priorità e sono dichiarate in JSON.

## Adapter Editor

L'editor degli adattatori scrive un semplice manifesto di adattatore in `Config/UnrealCapabilityMesh/adapters`. È inteso come punto di partenza per integrare un altro plugin in UCM senza aggiungere dipendenze C++ dirette all'hub.

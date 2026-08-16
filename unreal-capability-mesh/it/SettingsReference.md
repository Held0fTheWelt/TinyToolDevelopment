<!-- doc-provenance: AKDB:plugins/UnrealCapabilityMesh/architecture.md; docs/architecture/plugins/UnrealCapabilityMesh/product-facts.yml; reconciled 2026-07-19 -->
# Riferimento dei manifesti e delle impostazioni

UCM non espone una pagina in `UDeveloperSettings`. La configurazione avviene tramite JSON caricato da tre classi di radici di configurazione:

1. La configurazione predefinita inclusa di UCM.
2. Le cartelle `Config/UnrealCapabilityMesh` fornite dai plugin provider abilitati.
3. L'override opzionale del progetto `Config/UnrealCapabilityMesh`.

I profili vengono uniti in tale ordine, con l'override del progetto che ha la precedenza. Un profilo locale al progetto non è richiesto per il primo utilizzo né per i percorsi di un plugin provider abilitato. Creane uno solo quando il progetto sovrascrive intenzionalmente la configurazione o possiede percorsi composti.

## `project_profile.json`

| Campo | Scopo |
| --- | --- |
| `schema_version` | Deve iniziare con `capability_mesh.project_profile`. |
| `profile_id` | ID stabile per il profilo attivo. |
| `display_name` | Nome del profilo leggibile dall'utente. |
| `enable_knowledge_store` | Scrive la cronologia delle invocazioni se vero. |
| `experimental_self_approval_all_routes` | **SPERIMENTALE, da usare a proprio rischio.** Se vero, i percorsi configurati utilizzano l'ampia deviazione dai criteri descritta di seguito. Mantenere falso per l'uso normale. |
| `experimental_self_approved_route_ids` | **SPERIMENTALE, da usare a proprio rischio.** ID di percorsi che utilizzano la deviazione dai criteri quando `experimental_self_approval_all_routes` è falso. |
| `active_ruleset_id` | Nome del set di regole da considerare attivo. |
| `enabled_capability_manifests` | Percorsi dei manifesti delle funzionalità. |
| `enabled_endpoint_manifests` | Percorsi dei manifesti degli endpoint. |
| `enabled_schema_manifests` | Percorsi dei manifesti degli schemi. |
| `enabled_rule_manifests` | Percorsi dei manifesti delle regole. |
| `enabled_route_manifests` | Percorsi dei manifesti dei percorsi. |
| `enabled_transform_manifests` | Percorsi dei manifesti delle trasformazioni. |
| `enabled_adapter_manifests` | Percorsi dei manifesti degli adattatori. |
| `enabled_config_target_ids` | Elenco di consenso opzionale per le destinazioni Config Admin. Se assente, vengono scansionati tutti i manifesti di destinazione. |
| `tiny_tool_development_plugins_enabled` | Interruttore di consenso gestito da interfaccia utente per il catalogo Tiny Tool Development. |
| `reflection_metadata_keys` | Chiavi di metadati utilizzate durante la scansione delle funzionalità esposte tramite riflessione. |
| `optional_scan_paths` | Cartelle o file aggiuntivi da scansionare per cercare manifesti JSON. |
| `setup_editor_playground_enabled` | Interruttore di consenso gestito da interfaccia utente per il playground in Setup Editor. |
| `setup_editor_show_cpp_source_hints` | Flag di profilo opzionale per mostrare suggerimenti del codice sorgente C++ nell'albero di riferimento di Setup Editor. |

Le voci relative dei manifesti vengono risolte rispetto alla radice di configurazione proprietaria del profilo, con opzioni di ripiego sul progetto e sulla radice del progetto. Per la personalizzazione, copia solo il profilo o i manifesti che il progetto intende sovrascrivere. Mantenere le definizioni del provider a livello di plugin preserva la chiarezza sulla proprietà dei percorsi ed evita avvisi di definizioni duplicate.

## Risorse dell'editor di configurazione (Setup Editor)

| Percorso | Scopo |
| --- | --- |
| `editor/manifest_field_schema.json` | Mappa i percorsi dei campi JSON sui tipi di widget dell'editor (`bool`, `enum`, `string_array`, ecc.). |
| `editor/plugin_source_hints.json` | Mappa i valori `item_id` del catalogo sulle cartelle dei sorgenti dei plugin C++ per la consultazione dei riferimenti in sola lettura. |
| `playground/` | Manifesti sandbox modificabili senza un reale vincolo di plugin. |
| `tool_catalogs/setup_editor_playground.json` | Elemento di catalogo che aggiunge manifesti playground a `project_profile.json`. |

## Manifesto di funzionalità (Capability)

Le funzionalità dichiarano ciò che un provider può fare. Ciascuna funzionalità possiede ID, titolo, categoria, effetti collaterali, porte di input, porte di output e ID dell'endpoint.

## Manifesto di endpoint

Gli endpoint dichiarano le modalità di invocazione di una funzionalità. Campi importanti:

- `endpoint_id`
- `invocation_mode`
- `target`
- `parameters`
- `availability`

Le modalità di invocazione supportate includono funzioni di riflessione, contratti di file, provider di funzionalità modulari, bridge Python, commandlet e dichiarazioni di processi esterni. Riflessione, contratti di file e funzionalità modulari di provider UCM vengono eseguiti direttamente; bridge Python, commandlet e processi esterni rimangono in sola individuazione finché non vengono implementati i rispettivi invocatori generici.

## Manifesto di schema

Gli schemi descrivono la struttura attesa delle porte di input e output. UCM utilizza gli ID degli schemi per verificare la compatibilità.

## Manifesto di regola

Le regole stabiliscono se un percorso è consentito. Effetti collaterali comuni:

- `read_only`
- `saved_folder_write`
- `project_config_write`
- `asset_mutation`
- `project_mutation`
- `network`
- `ai_completion`

## Manifesto di percorso (Route)

I percorsi definiscono passaggi ordinati. Ogni passaggio fa riferimento a un ID di funzionalità e dichiara collegamenti di input/output.

I percorsi di modifica devono impostare `allow_asset_mutation` o `allow_project_mutation` solo quando l'operazione è intenzionale. L'esecutore richiede normalmente un'approvazione durante l'esecuzione; fornisci `approval_granted: true`, `approvalGranted: true` o `approval: "granted"` nell'input del percorso, a meno che l'override dell'auto-approvazione automatica **SPERIMENTALE** sottostante non sia intenzionalmente attivo.

### Auto-approvazione automatica sperimentale

`experimental_self_approval_all_routes` e `experimental_self_approved_route_ids` sono opzioni di emergenza esplicitamente sperimentali per test e flussi di lavoro locali a proprio rischio. Quando abilitate, UCM trasmette `bExperimentalPolicyBypass=true` durante la pianificazione e l'esecuzione del percorso. Le regole di diniego corrispondenti con `allow=false` non bloccano più il percorso, i requisiti di approvazione e di esecuzione di prova a livello di regola vengono ignorati, i controlli sulla modifica di asset/progetto a livello di percorso vengono saltati e il piano finale annulla sia i requisiti di approvazione che quelli di esecuzione di prova.

Mantieni disattivate entrambe le impostazioni per i flussi di lavoro normali e di produzione. Il catalogo dei percorsi dell'editor contrassegna questi interruttori come **SPERIMENTALI** e ne dichiara l'intera portata. Gli host MCP possono leggere o modificare le stesse impostazioni tramite `mesh_configure_experimental_self_approval`; l'abilitazione tramite MCP richiede `acknowledge_experimental_risk: true`.

## Manifesto di trasformazione (Transform)

Le trasformazioni mappano il JSON sorgente sul JSON di destinazione. Vengono utilizzate per adattare gli output di una funzionalità negli input per un'altra.

## Manifesto di adattatore (Adapter)

Gli adattatori mappano le funzioni di plugin di terze parti in UCM senza aggiungere una dipendenza C++ diretta all'hub.

## Configurazione dell'amministrazione degli asset

La configurazione inclusa nella cartella `Config/UnrealCapabilityMesh` di UCM dichiara le funzionalità di amministrazione per DataAsset/DataTable:

- `capability_mesh.asset_admin.export`
- `capability_mesh.asset_admin.import`
- `capability_mesh.asset_admin.sync`

Tutte e tre richiamano `UCapabilityMeshAssetAdminSubsystem` tramite endpoint `reflection_subsystem_function`. Gli host MCP devono instradare le richieste tramite queste dichiarazioni anziché chiamare codice bridge specifico del progetto.

## Manifesto della destinazione di configurazione

Le destinazioni dell'amministrazione della configurazione sono approvate separatamente dai manifesti dei percorsi in:

```text
Config/UnrealCapabilityMesh/config_targets/*.json
```

I manifesti di destinazione utilizzano:

```json
{
  "schema_version": "capability_mesh.config_target_manifest.v1",
  "targets": [
    {
      "target_id": "example_plugin.settings",
      "display_name": "Example Plugin Settings",
      "description": "Explains what the target controls and when it should be edited.",
      "kind": "uobject_config",
      "class_path": "/Script/ExamplePlugin.ExamplePluginSettings",
      "required_plugin_names": ["ExamplePlugin"]
    }
  ]
}
```

Valori di `kind` supportati:

- `uobject_config`: legge e scrive le proprietà di configurazione su un oggetto predefinito di classe (CDO), quindi salva la configurazione.
- `uobject_instance`: legge e scrive i campi modificabili su una classe di oggetti approvata. Le richieste devono includere `object_path`.
- `json_file`: legge e scrive un file JSON dichiarato in una directory di base consentita.

Ogni destinazione deve includere una `description` non vuota; Config Admin evidenzia le descrizioni mancanti come avvisi del manifesto poiché gli utenti necessitano del contesto prima di leggere o scrivere in una destinazione.

I percorsi standard sono `capability_mesh.config_admin.list_targets.v1`, `capability_mesh.config_admin.read_target.v1` e `capability_mesh.config_admin.write_target.v1`. I percorsi di scrittura dichiarano `project_config_write` e `asset_mutation` in modo che file di configurazione, oggetti di configurazione, DataAsset e istanze di oggetti modificabili passino tutti attraverso lo stesso percorso di approvazione ed esecuzione di prova.

## Manifesto del catalogo degli strumenti

I cataloghi degli strumenti risiedono in:

```text
Config/UnrealCapabilityMesh/tool_catalogs/*.json
```

Raggruppano le voci di configurazione in pacchetti attivabili tramite interfaccia utente. Un pacchetto può dichiarare percorsi di manifesti di funzionalità, endpoint, schemi, regole, percorsi, trasformazioni, adattatori e ID di destinazioni di configurazione. L'interfaccia utente disattiva i pacchetti rimuovendo tali voci da `project_profile.json`; non elimina i file manifesto.

I pacchetti del catalogo devono rimanere di dimensioni ridotte in base ai confini di proprietà. Il pacchetto di un plugin deve aggiungere unicamente le funzionalità, gli endpoint, gli schemi e le destinazioni di configurazione propri di quel plugin. I flussi di lavoro tra plugin devono essere pacchetti di percorsi distinti che fanno riferimento ai componenti già abilitati. Ciò mantiene valide le configurazioni per solo IIS, solo LLM Store, UII+IIS e IIS+LLM Store senza richiedere tutti i plugin Tiny Tool Development.

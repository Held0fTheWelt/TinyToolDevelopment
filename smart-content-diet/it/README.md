<!-- doc-provenance: AKDB:plugins/SmartContentDiet/architecture.md; docs/architecture/plugins/SmartContentDiet/product-facts.yml; reconciled 2026-07-16 -->
# Documentazione di SmartContentDiet

SmartContentDiet analizza gli asset del progetto Unreal Engine, spiega i risultati dell'ottimizzazione nel contesto, espone viste di governance e offre workflow di QuickFix/riduzione verificati. Il ciclo di prodotto predefinito è **scansione → revisione → applica correzioni sicure → nuova scansione → misura miglioramento** — senza richiedere IA o strumenti esterni.

## Avviso di sicurezza

SmartContentDiet può modificare gli asset di progetto quando si applicano QuickFix, riduzioni mesh, modifiche a texture/materiali, spostamenti/eliminazioni di revisione asset, aggiornamenti della baseline o scritture di governance. Utilizzarlo solo in un branch o workspace con backup, sotto controllo versione e monouso. Non eseguirlo mai su sorgenti non protette. Utilizzo a proprio rischio.

La funzionalità è implementata con cura nell'ambito dichiarato, ma non sostituisce backup, controllo versione, revisione del codice/contenuto o validazioni specifiche del progetto.

## Mappa della documentazione

| Documento | Pubblico | Contenuto |
|----------|----------|-----------|
| [UI_AND_BEHAVIOR.md](../Resources/UI_AND_BEHAVIOR.md) | Artisti, tech artist, producer | Shell dell'editor, schede, workflow di scansione, risultati, QuickFix, governance |
| [OPTIMIZATION_QUEUE.md](../Resources/OPTIMIZATION_QUEUE.md) | Tutti gli utenti dell'editor | Coda di ottimizzazione sicura, bucket, applica/anteprima, delta prima/dopo |
| [SMART_ANALYSIS_ARCHITECTURE.md](../Resources/SMART_ANALYSIS_ARCHITECTURE.md) | Ingegneri, integratori | Analizzatori, preset, impatto, riduzione, trend, architettura di governance |
| [DIMENSION_INTEGRATION_STATUS.md](../Resources/DIMENSION_INTEGRATION_STATUS.md) | Ingegneri | FindingType, mappatura dimensioni, convertitore, stato integrazione UI |
| [SmartAnalysisResult_Usage.md](../Resources/SmartAnalysisResult_Usage.md) | Ingegneri | Uso modello risultato, metadati auto-fix |
| [CHANGELOG.md](../CHANGELOG.md) | Operatori di release | Cronologia versioni |

**Nuovo qui?** Inizia con [QUICKSTART.md](QUICKSTART.md) per l'installazione e il ciclo sicuro scansione→correzione.

## Pacchetto per Engine installato

Utilizzare un pacchetto BuildPlugin Smart Content Diet prodotto per la versione dell'engine installata. Il pacchetto conserva i binari generati e i metadati di precompilazione richiesti dalle build installate. Non rimuovere questi file durante la copia o l'archiviazione del plugin.

> **Per i manutentori:** il gate di release SCD e i documenti di release/runbook risiedono nel repository di sviluppo e **non** fanno parte del pacchetto Fab; non sono necessari per installare o utilizzare SCD.

## Punto di ingresso nell'editor

Aprire **Tools → Content Tools → Smart Content Diet**.

### Shell con rilevamento ruolo

La finestra principale utilizza le impostazioni del pubblico (Principiante / Ingegnere / Producer) per controllare la profondità delle spiegazioni e le schede visibili.

| Scheda | Principiante | Avanzato (Ingegnere / Producer + modalità avanzata) |
|-----|----------|--------------------------------------------------|
| Panoramica | ✓ | ✓ |
| Ottimizza | ✓ | ✓ |
| Risultati | ✓ | ✓ |
| Preset | — | ✓ |
| Governance | — | ✓ (Trend, Debito, Budget, Proprietà, Scansione approfondita come sotto-schede) |
| Ridondanza | — | ✓ solo quando è registrato un provider di similarità esterno |
| Impostazioni | ✓ | ✓ |

Modificare ruolo e livello di spiegazione in **Impostazioni** o tramite il selettore di pubblico nell'intestazione.

### Profondità di scansione (intestazione)

| Profondità | Carica asset? | Uso tipico |
|-------|---------------|------------|
| **Quick Safe** (predefinito) | No — percorso registro/metadati | Primo passaggio, rapido "cosa posso migliorare in sicurezza?" |
| **Full** | Sì — pipeline analizzatore completa | Risultati azionabili su mesh/texture/materiali |
| **Deep** | Sì — include metriche approfondite materiali/mesh statiche | Più lenta; metriche shader e lavoro approfondito mesh |

Il menu a tendina dell'intestazione aggiorna l'etichetta del pulsante principale di scansione (`Quick Safe Scan` / `Full Scan` / `Deep Scan`) e mostra un suggerimento sulla profondità sotto i controlli.

La profondità selezionata è rispettata da **ogni** esecuzione dell'analizzatore: le analisi dell'editor (Risultati / Governance → Esegui analisi) la passano a `FSmartAnalysisOrchestrator`, e la linea di stato governance indica la profondità usata. **Commandlet e CI** rispettano `-QuickSafe`, `-FullScan` e `-DeepScan` come prima. Le metriche approfondite materiali/mesh usano inoltre il workflow Governance Deep Scan (`Governance → Deep Scan`), identico al commandlet.

## Workflow rapidi

### Rotte dell'ecosistema UCM

Quando Unreal Capability Mesh (UCM) è abilitato, SmartContentDiet può essere utilizzato tramite rotte dichiarate nella configurazione invece di bridge provider diretti. SCD non collega mai un plugin peer e non ne elenca nessuno in `required_plugin_names` o `Build.cs`; il valore cross-plugin deriva da rotte JSON, non da dipendenze di codice. Il profilo di progetto attivo espone **12 funzionalità SCD**:

| Funzionalità | Tipo | Criterio |
| --- | --- | --- |
| `scd.migration.advice_from_handoff` | consultivo | sola lettura |
| `scd.scan.run` | provider | sola lettura |
| `scd.findings.get` | provider | sola lettura |
| `scd.findings.explain` | provider | sola lettura |
| `scd.health.snapshot` | provider | sola lettura |
| `scd.health.evidence` | provider | sola lettura |
| `scd.governance.snapshot` | provider | sola lettura |
| `scd.similarity.groups` | similarità | sola lettura |
| `scd.similarity.ingest_groups` | similarità | sola lettura |
| `scd.optimize.preview_safe` | ottimizzazione | sola lettura |
| `scd.optimize.apply_safe` | ottimizzazione | **modifica — richiede approvazione** |
| `scd.optimize.apply_fix` | ottimizzazione | **modifica — richiede approvazione** |

**Contratto di degradazione.** Ogni funzionalità restituisce l'involucro condiviso `smart_content_diet.capability_mesh_endpoint.v1` (`status` pari a `ok`/`degraded`/`error`). Le funzionalità riducono le prestazioni anziché fallire quando manca una precondizione: le rotte ottimizzazione/risultati restituiscono un involucro `error` chiedendo di eseguire prima `scd.scan.run`; `scd.optimize.apply_fix` restituisce un involucro `degraded` (nessuna mutazione) quando viene richiesta una correzione distruttiva senza `allow_destructive: true`. Il collegamento di SCD a un peer non è mai presunto — una rotta che fa riferimento a un altro plugin (ad es. l'esempio `scd_ingest_from_iis.v1`, `iis.search.hybrid → scd.similarity.ingest_groups`) viene segnalata dalla ricerca UCM come *disponibile ma plugin non caricato* quando quel peer è assente, mentre ogni funzionalità solo SCD rimane *disponibile*.

**Gate di approvazione (e Opzione 3).** Le due rotte di modifica portano `requires_user_approval: true`, quindi UCM le blocca con `ApprovalRequired` fino all'approvazione umana — nessun asset viene toccato prima. Gli operatori che desiderano un'applicazione sicura non presidiata possono modificare il criterio della rotta per rimuovere il requisito di approvazione (Opzione 3); la versione distribuita include il blocco di approvazione.

I workflow di posizionamento PRS rimangono rotte UCM di proprietà PRS. I bridge gratuiti rimangono disponibili solo per i team senza UCM e come implementazioni di riferimento per adattatori diretti; non sono richiesti nel progetto principale.

### Ciclo di ottimizzazione sicura autonomo (senza IA)

### Correttezza e prestazioni di scansione

Il percorso analizzatore attuale privilegia AssetRegistry. Costruisce l'insieme dei candidati una volta, legge i metadati dei tag prima di caricare gli asset, parallelizza il lavoro di confronto in sola lettura e carica in profondità solo i candidati finali. Una cache di metadati per asset con invalidazione per timestamp/versione evita di ripetere il lavoro invariato.

L'analisi dei duplicati e dell'alpha condivide helper con il motore di riduzione. Le uscite anticipate di riduzione usano chiavi duplicato allineate alla riduzione (`DuplicateTextureReduction`, `DuplicateStaticMeshReduction`) in modo che i controlli di consolidamento sicuro corrispondano alla logica delle impronte usata dal riduttore reale. Le euristiche per l'alpha delle texture sono centralizzate in `SCDMaterialAlpha` per mantenere allineati analizzatore e riduzione.

La cronologia dei processi dell'editor è disponibile tramite rotte UCM (`scd.editor.jobs.list.v1`, `scd.editor.jobs.status.v1`) per l'aggregazione UMCP senza aggiungere una dipendenza UMCP a SCD.

1. Aprire Smart Content Diet.
2. Lasciare la profondità di scansione su **Quick Safe** o scegliere **Full** / **Deep**.
3. Eseguire la scansione dall'intestazione.
4. Esaminare **Panoramica**, quindi aprire **Ottimizza** → Coda di ottimizzazione sicura.
5. **Anteprima sicura** → **Applica in sicurezza** (prima backup / controllo versione).
6. Dopo un'applicazione riuscite o una correzione di un singolo asset nei dettagli dei **Risultati**, la shell esegue automaticamente una nuova scansione.
7. Confrontare il numero di elementi in coda e il riepilogo delta nel pannello Ottimizza; i report JSON di applicazione vengono salvati in `Saved/SmartContentDiet/OptimizationQueue/<timestamp>/`.

Vedere [OPTIMIZATION_QUEUE.md](../Resources/OPTIMIZATION_QUEUE.md) per definizioni dei bucket, regole di sicurezza e schema dei report.

### Workflow di analisi generale

1. Eseguire una scansione (ambito selezione, cartella o progetto).
2. Esaminare i risultati per gravità, impatto, dimensione e catena di spiegabilità.
3. Usare **Preset** (avanzato) per capire come i pesi di valutazione influenzano i punteggi.
4. Usare **Governance** (avanzato) per trend, debito, budget, proprietà e Scansione approfondita opzionale.
5. Applicare i QuickFix solo dopo aver confermato backup/controllo versione.
6. Eseguire una nuova scansione e validare nel contesto del progetto di destinazione.

## Commandlet (CI / headless)

```powershell
UnrealEditor-Cmd.exe "<Project>.uproject" -run=SmartContentDiet `
  -QuickSafe -OptimizationQueueReport -Path=/Game -Limit=50 `
  -NoFail -unattended -nop4 -nosplash
```

Applicare le righe della coda sicura (solo progetto con backup):

```powershell
UnrealEditor-Cmd.exe "<Project>.uproject" -run=SmartContentDiet `
  -QuickSafe -ApplySafeQueue -OptimizationQueueReport -Path=/Game `
  -NoFail -unattended -nop4 -nosplash
```

| Flag | Effetto |
|------|---------|
| `-QuickSafe` | Scansione registro/dipendenze; non carica asset |
| `-FullScan` | Carica asset ed esegue analizzatori (predefinito se manca `-QuickSafe`) |
| `-DeepScan` | Profondità più lenta; metriche approfondite materiali/mesh |
| `-OptimizationQueueReport` | Scrive la coda JSON/Markdown (auto-abilitato con `-QuickSafe`) |
| `-ApplySafeQueue` | Applica solo le righe **Safe Now**; le righe distruttive vengono rifiutate |
| `-Path=/Game/...` | Ambito di scansione |
| `-NoFail` | Esci con 0 anche in presenza di avvisi di criteri (usare con cautela in CI) |

Il commandlet stampa l'avviso di sicurezza all'uso e all'avvio dell'esecuzione. Gli aggiornamenti della baseline e la scrittura dei report sono operazioni che modificano il workspace.

## Posizione degli artefatti (gitignored)

| Artefatto | Percorso |
|----------|----------|
| Report applicazione coda ottimizzazione | `Saved/SmartContentDiet/OptimizationQueue/<timestamp>/apply_report.json` |
| Report coda commandlet | `-ReportDir` / predefinito sotto `Saved/SmartContentDiet/` |
| Output validazione release | `Saved/SCDValidation/` quando si esegue la validazione manutentore |

## Ambito QuickFix implementato (riepilogo)

SmartContentDiet offre QuickFix verificati per texture, mesh statiche/scheletriche, materiali, animazioni, igiene audio/VFX e revisione/consolidamento asset. Le azioni distruttive o cross-asset richiedono una conferma esplicita e non sono sicure per l'esecuzione in batch per impostazione predefinita.

Catalogo completo: [UI_AND_BEHAVIOR.md § Optimization Packs](../Resources/UI_AND_BEHAVIOR.md#71-optimization-packs).

## Validazione Release

La validazione della release è un workflow riservato ai manutentori. L'uso da parte dell'acquirente non richiede script di gate locali, moduli di test del progetto host o percorsi specifici del repository.

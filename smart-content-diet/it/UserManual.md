<!-- doc-provenance: AKDB:plugins/SmartContentDiet/architecture.md; docs/architecture/plugins/SmartContentDiet/product-facts.yml; reconciled 2026-07-16 -->
# Manuale utente

Questo manuale riassume il workflow dell'editor di Smart Content Diet e indica le guide dettagliate.

## Punto di ingresso

Aprire **Tools → Content Tools → Smart Content Diet**. La finestra è una shell adattabile al ruolo.

## Ruoli e schede

Impostare il ruolo (Principiante / Ingegnere / Producer) e il livello di spiegazione in **Impostazioni** o nel selettore di pubblico nell'intestazione. La visibilità delle schede segue il ruolo:

| Scheda | Principiante | Avanzato (Ingegnere / Producer) |
| --- | --- | --- |
| Panoramica, Ottimizza, Risultati, Impostazioni | ✓ | ✓ |
| Preset | — | ✓ |
| Governance (Trend, Debito, Budget, Proprietà, Scansione approfondita) | — | ✓ |
| Ridondanza | — | ✓ (solo con un provider di similarità esterno) |

## Profondità di scansione

Scegliere nell'intestazione: **Quick Safe** (registro/metadati, nessun caricamento asset), **Full** (carica asset), **Deep** (metriche approfondite materiali/mesh; Governance → Scansione approfondita). Ogni esecuzione dell'analizzatore rispetta la profondità selezionata; il commandlet rispetta `-QuickSafe` / `-FullScan` / `-DeepScan`.

Le scansioni ampie usano una pipeline basata prima su AssetRegistry. SCD raccoglie i candidati una volta, legge i metadati economici delle texture/materiali dai tag quando possibile, esegue prima il confronto basato sui tag e carica in profondità solo l'insieme dei candidati superstiti che richiedono dati di oggetti. La fase di confronto in sola lettura può essere eseguita in parallelo; i QuickFix di modifica richiedono ancora un'azione esplicita dell'utente o del commandlet.

I percorsi dei duplicati e dell'alpha condividono codice helper tra risultati di scansione e riduzioni. I controlli dell'alpha delle texture/materiali usano la stessa logica di opacità delle istanze di materiale, e le uscite anticipate di riduzione usano chiavi duplicato allineate alla riduzione, in modo che un consolidamento sicuro non venga saltato solo perché l'indice di scansione più rigoroso non ha raggruppato gli asset.

## Workflow principale — Ciclo di ottimizzazione sicura (senza IA)

1. Aprire lo strumento.
2. Scegliere la profondità di scansione (Quick Safe / Full / Deep).
3. Eseguire la scansione dall'intestazione.
4. Esaminare **Panoramica**, quindi **Ottimizza → Coda di ottimizzazione sicura**.
5. **Anteprima sicura** → backup / controllo versione → **Applica in sicurezza**.
6. La shell esegue automaticamente una nuova scansione dopo un'applicazione riuscita o la correzione di un singolo asset.
7. Confrontare il numero di elementi in coda e il delta; i report JSON vengono salvati in `Saved/SmartContentDiet/OptimizationQueue/<timestamp>/`.

## Workflow di analisi generale

1. Eseguire una scansione (ambito selezione, cartella o progetto).
2. Esaminare i risultati per gravità, impatto, dimensione e catena di spiegabilità.
3. Usare **Preset** (avanzato) per vedere come i pesi di valutazione influenzano i punteggi.
4. Usare **Governance** (avanzato) per trend, debito, budget, proprietà e Scansione approfondita opzionale.
5. Applicare i QuickFix solo dopo aver confermato backup/controllo versione.
6. Eseguire una nuova scansione e validare nel contesto del progetto di destinazione.

## Sicurezza

Le azioni di modifica alterano gli asset di progetto e richiedono un'approvazione per impostazione predefinita. Eseguire solo in un workspace con backup, sotto controllo versione e monouso. Vedere l'avviso di sicurezza in [QUICKSTART.md](QUICKSTART.md).

## Processi dell'editor e UCM

I lavori recenti dell'editor vengono registrati come cronologia processi per scansioni, validazioni e azioni di ottimizzazione. Quando Unreal Capability Mesh è abilitato, SCD espone rotte di processi in sola lettura:

```text
scd.editor.jobs.list.v1
scd.editor.jobs.status.v1
```

Unified MCP Server può aggregare tali rotte tramite `jobs_list` / `jobs_status`; SCD stesso non dipende da UMCP.

## Guide dettagliate

- Shell dell'editor, schede, risultati, QuickFix, governance: [../Resources/UI_AND_BEHAVIOR.md](../Resources/UI_AND_BEHAVIOR.md).
- Coda di ottimizzazione sicura (bucket, regole di sicurezza, schema report): [../Resources/OPTIMIZATION_QUEUE.md](../Resources/OPTIMIZATION_QUEUE.md).
- Architettura: [../Resources/SMART_ANALYSIS_ARCHITECTURE.md](../Resources/SMART_ANALYSIS_ARCHITECTURE.md).

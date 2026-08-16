<!-- doc-provenance: AKDB:plugins/SmartContentDiet/architecture.md; docs/architecture/plugins/SmartContentDiet/product-facts.yml; reconciled 2026-07-16 -->
# Riferimento impostazioni

## Ruolo / Pubblico

Impostato in **Impostazioni** o nel selettore di pubblico nell'intestazione. Controlla la profondità delle spiegazioni e la visibilità delle schede:

- **Principiante** — Panoramica, Ottimizza, Risultati, Impostazioni.
- **Ingegnere / Producer (avanzato)** — aggiunge Preset e Governance (Trend, Debito, Budget, Proprietà, Scansione approfondita); Ridondanza appare solo quando è registrato un provider di similarità esterno.

## Profondità di scansione (intestazione)

| Profondità | Carica asset? | Note |
| --- | --- | --- |
| `Quick Safe` (predefinito) | No | Percorso registro/metadati; primo passaggio veloce. |
| `Full` | Sì | Pipeline analizzatore completa; risultati azionabili su mesh/texture/materiali. |
| `Deep` | Sì | Metriche approfondite materiali/mesh statiche; usa Governance → Scansione approfondita; più lenta. |

La profondità selezionata è rispettata da ogni esecuzione dell'analizzatore (editor e commandlet).

Quick Safe è il percorso basato prima su AssetRegistry: le scansioni ampie evitano il caricamento pesante degli asset a meno che un candidato non superi i controlli metadati economici. Full e Deep possono caricare asset per dettagli azionabili dell'analizzatore.

## Posizione di output

```text
Saved/SmartContentDiet/OptimizationQueue/<timestamp>/   ← report di applicazione della coda sicura
```

## Approvazione / Sicurezza

Le funzionalità di modifica (`scd.optimize.apply_safe`, `scd.optimize.apply_fix`) richiedono **un'approvazione per impostazione predefinita**. Le correzioni distruttive richiedono un'esplicita opzione `allow_destructive: true`. Eseguire mutazioni solo in un workspace con backup, sotto controllo versione e monouso.

## Commandlet (CI / headless)

Opzioni: `-QuickSafe`, `-FullScan`, `-DeepScan`, `-OptimizationQueueReport`, `-ApplySafeQueue`, `-Path=`, `-Limit=`, `-NoFail`, oltre alle opzioni standard `-unattended -nop4 -nosplash`. Le opzioni di applicazione devono essere usate solo su progetti con backup.

## Rotte dell'ecosistema opzionali

Quando **Unreal Capability Mesh (UCM)** è abilitato, SCD espone funzionalità provider in sola lettura e due rotte di ottimizzazione con modifica soggette ad approvazione tramite rotte UCM dichiarate in JSON. SCD non collega mai un plugin peer nel codice; questa integrazione è completamente opzionale. Vedere l'indice della [documentazione](README.md) e [../Resources/SMART_ANALYSIS_ARCHITECTURE.md](../Resources/SMART_ANALYSIS_ARCHITECTURE.md).

SCD espone anche rotte dei processi dell'editor in sola lettura (`scd.editor.jobs.list.v1`, `scd.editor.jobs.status.v1`) per l'aggregazione UMCP tramite UCM.

Per impostazioni più approfondite dell'analizzatore/preset/governance, vedere [../Resources/SMART_ANALYSIS_ARCHITECTURE.md](../Resources/SMART_ANALYSIS_ARCHITECTURE.md).

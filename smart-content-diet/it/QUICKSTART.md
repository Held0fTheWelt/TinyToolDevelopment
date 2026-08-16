<!-- doc-provenance: AKDB:plugins/SmartContentDiet/architecture.md; docs/architecture/plugins/SmartContentDiet/product-facts.yml; reconciled 2026-07-16 -->
# Guida rapida

Questa guida accompagna dall'installazione a un **risultato reale**: una scansione degli asset del progetto con risultati di ottimizzazione e (opzionalmente) l'applicazione di una correzione sicura verificata con report prima/dopo. Il ciclo principale di Smart Content Diet funziona in modo autonomo — **nessuna IA, plugin peer o strumento esterno richiesto**.

> **⚠ Sicurezza prima di tutto.** L'applicazione di correzioni, riduzioni, spostamenti/eliminazioni di asset, aggiornamenti della baseline o scritture di governance **modifica gli asset del progetto**. Eseguire queste operazioni solo in un workspace **con backup, sotto controllo versione e monouso** — mai su sorgenti non protette. Scansione e anteprima sono in sola lettura e sicure.

## Cosa si otterrà dopo questa guida

L'strumento aperto nel ruolo scelto, una scansione Quick Safe completata con risultati e la comprensione di come visualizzare l'anteprima, applicare ottimizzazioni sicure e leggere il delta prima/dopo.

## Requisiti

- Editor Unreal Engine 5.4+ con un progetto contenente asset.
- Nessun software di terze parti, account, modello IA o runtime esterno. Vedere [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md).

## 1. Installare e abilitare

1. Aggiungere **SmartContentDiet** dalla libreria Fab al progetto (o installarlo nell'engine).
2. Aprire **Modifica → Plugin**, abilitare **SmartContentDiet** e riavviare quando richiesto.

## 2. Aprire lo strumento e scegliere un ruolo (Primo risultato)

1. Aprire **Tools → Content Tools → Smart Content Diet**.
2. Nel selettore di pubblico nell'intestazione (o in **Impostazioni**), scegliere il ruolo:
   - **Principiante** — Panoramica, Ottimizza, Risultati, Impostazioni; maggiori spiegazioni.
   - **Ingegnere / Producer (avanzato)** — aggiunge Preset e Governance (Trend, Debito, Budget, Proprietà, Scansione approfondita) e Ridondanza quando è registrato un provider di similarità esterno.
3. Lasciare la **profondità di scansione** su **Quick Safe** (predefinito — solo registro/metadati, nessun caricamento asset; veloce).
4. Fare clic su **Quick Safe Scan** nell'intestazione.

**Risultato atteso:** la scansione si completa e la scheda **Panoramica** riassume i risultati (cosa può essere migliorato in sicurezza). Operazione in sola lettura.

## 3. Un esempio pratico: Anteprima e applicazione di una correzione sicura

> Eseguire prima il backup / commit del progetto (vedere nota di sicurezza sopra).

1. Aprire la scheda **Ottimizza** → **Coda di ottimizzazione sicura**.
2. Fare clic su **Anteprima sicura** per vedere le ottimizzazioni sicure in coda e il delta prima/dopo previsto (ancora in sola lettura).
3. Fare clic su **Applica in sicurezza** per applicare la coda sicura. Dopo un'applicazione riuscita (o una correzione di un singolo asset dai dettagli dei **Risultati**), la shell **esegue automaticamente una nuova scansione**.
4. Confrontare il numero di elementi in coda e il riepilogo delta nel pannello Ottimizza.

**Risultato atteso:** le ottimizzazioni sicure vengono applicate e un report di applicazione JSON viene scritto in:

```text
Saved/SmartContentDiet/OptimizationQueue/<timestamp>/
```

## 4. Profondità di scansione

| Profondità | Carica asset? | Uso |
| --- | --- | --- |
| **Quick Safe** (predefinito) | No | Rapido "cosa posso migliorare in sicurezza?" |
| **Full** | Sì | Risultati azionabili su mesh/texture/materiali |
| **Deep** | Sì | Più lenta; metriche approfondite materiali/mesh statiche (Governance → Scansione approfondita) |

L'etichetta del pulsante nell'intestazione e il suggerimento si aggiornano con la profondità selezionata, rispettata da ogni esecuzione dell'analizzatore.

## 5. Passaggi successivi

- Shell dell'editor, schede, risultati, governance: [../Resources/UI_AND_BEHAVIOR.md](../Resources/UI_AND_BEHAVIOR.md).
- Coda di ottimizzazione sicura (bucket, regole di sicurezza, schema report): [../Resources/OPTIMIZATION_QUEUE.md](../Resources/OPTIMIZATION_QUEUE.md).
- Impostazioni e ruoli: [SettingsReference.md](SettingsReference.md).
- Problemi: [TROUBLESHOOTING.md](TROUBLESHOOTING.md) e [FAQ.md](FAQ.md).

> **Opzionale / avanzato:** SCD offre anche un commandlet headless per CI (`-QuickSafe`, `-FullScan`, `-DeepScan`, `-OptimizationQueueReport`, `-ApplySafeQueue`) e — solo se si possiede anche **Unreal Capability Mesh (UCM)** — rotte dell'ecosistema opzionali dichiarate nella configurazione. Nessuno dei due è necessario per il workflow dell'editor sopra; vedere l'indice della [documentazione](README.md).

<!-- doc-provenance: AKDB:plugins/VisualFidelityDirector/architecture.md; docs/architecture/plugins/VisualFidelityDirector/product-facts.yml; reconciled 2026-07-12 -->
# Manuale utente

Visual Fidelity Director è uno strumento locale per Unreal Editor. La versione `2.0.0` si concentra su un cockpit incentrato sui profili, mantenendo il pannello Expert Tools 1.x integrato per i workflow di snapshot e ricette.

## Aprire lo strumento

Utilizzare **Tiny Tools > Visual Fidelity Director**.

La scheda ancorabile offre le pagine **Cockpit**, **Evidence** e **Expert Tools**.

Opzionale: **Modifica > Editor Configurations > Visual Fidelity Director Editor Settings** apre le preferenze dell'editor del plugin (la scorciatoia da menu può essere disabilitata nelle impostazioni).

## Pagina Cockpit

### Banner di stato

Mostra il titolo di disponibilità e il testo dettagliato sullo stato di compilazione e validazione del profilo attivo.

### Scheda azione

| Azione | Risultato atteso |
| --- | --- |
| **Refresh** | Ricarica i profili, ricompila l'anteprima del profilo attivo, riavvia il campionamento delle metriche multi-frame e aggiorna le strisce degli assi. |
| **Compile Preview** | Ricompila i target delle impostazioni desiderate per il profilo attivo senza scrivere la configurazione. |
| **Open Reports** | Apre la cartella locale dei report VFD nel gestore file del sistema operativo. |

### Barra dei profili

Selezionare il profilo di fedeltà attivo. La barra mostra lo stato di validazione e i profili noti caricati da `Saved/VisualFidelityDirector/profiles/`.

### Barra delle metriche

Mostra le metriche dell'editor live multi-frame (frame, game thread, render thread, GPU, collo di bottiglia e quota costo per asse, se disponibile). I valori di `-1` o le stringhe non disponibili esplicite indicano che la misurazione non è disponibile nel contesto dell'editor attuale — VFD non inventa mai numeri.

### Strisce degli assi

Ogni striscia degli assi di composizione include:

- etichetta dell'asse e colore di disponibilità;
- menu a tendina **Variant** (le varianti non disponibili rimangono visibili ma disabilitate con le prove di compatibilità);
- cursore **Intent** (`0.00`–`1.00`);
- evidenziazione della selezione per il cassetto dettagli dell'asse attivo.

### Cassetto dettagli dell'asse

Per l'asse selezionato:

- **Percorso di ereditarietà** — catena ordinata dall'antenato radice al profilo attivo;
- **Provenienza** — righe a livello di campo per le impostazioni compilate (destinazione, valore, sorgente);
- **Risultati** — risultati di compilazione e compatibilità locali al controllo.

### Scheda confronto profili

Scegliere un secondo profilo e ispezionare le differenze dello stato desiderato compilato per ciascun asse. Utilizza lo stesso runtime di confronto della libreria Blueprint.

### Cassetto applicazione governata

| Azione | Risultato atteso |
| --- | --- |
| **Build Destinations** | Riepiloghi in sola lettura per le destinazioni Scalability, ini renderer e Device Profiles. |
| **Apply Approved** | Scrive solo le destinazioni spuntate e approvate dall'utente tramite backup → scrittura → verifica → manifesto di rollback. |
| **Rollback** | Ripristina gli ultimi file salvati dal manifesto di rollback. |

Le destinazioni bloccate (asset, materiali, MRQ, accessibilità, assi solo di revisione) non appaiono mai come destinazioni Scrivibili.

## Pagina Evidence

Mostra undici blocchi di prove a corsia fissa (Lumen e altre corsie di revisione) con mappature degli assi dichiarate, affidabilità e limiti di revisione manuale. Questa pagina è in sola lettura.

## Pagina Expert Tools

Il pannello di controllo 1.x integrato per i workflow legacy:

### Intent Mixer

Ogni cursore accetta da `0.00` a `1.00` e influisce solo sulla valutazione a secco della ricetta fino all'esportazione o all'applicazione.

| Cursore | Significato |
| --- | --- |
| Image Stability | Preferisce dettagli subpixel più calmi e meno sfarfallio. |
| Motion Clarity | Preferisce meno sbavature/ghosting nei contenuti in movimento. |
| Fine Detail Preservation | Preferisce dettagli apparenti più nitidi. |
| Specular Calmness | Preferisce meno sfarfallio nei punti luce/aree lucide. |
| UI Crispness | Preferisce la chiarezza di HUD/UMG. |
| Cinematic Accumulation | Preferisce l'accumulo di campioni nel rendering finale. |
| Performance Headroom | Preferisce raccomandazioni meno onerose. |

### Ricette integrate

Stessi quindici ID di ricette integrate della versione `1.0.0` (vedere [SettingsReference.md](SettingsReference.md)).

### Azioni Expert Tools

| Azione | Risultato atteso |
| --- | --- |
| Export Snapshot (Expert Tools) | `quality_snapshot.json/.md` più le copie più recenti. |
| Export Recipe Dry Run (Expert Tools) | `recipe_evaluation.json` e `settings_diff.md`; nessuna mutazione. |
| Duplicate Recipe | JSON di proprietà del progetto in `Saved/VisualFidelityDirector/recipes/`. |
| Import Recipe | Aggiorna la ricetta attiva e i cursori dal JSON importato. |
| Export Scanner Report | `visual_quality_report.json/.md`. |
| Lumen Deep Scan (Expert Tools) | Risultati metadati del cache di superficie Lumen; nessuna mutazione di mesh/materiali. |
| Preview Apply + Rollback (Expert Tools) | Anteprima CVar della sessione con rollback; `visual_fidelity_apply_report.*`. |
| Export A/B Report | `comparison_report.json/.md`. |
| Export Cinematic Report | `cinematic_quality_report.*` e `mrq_recommendation.md`. |
| Validate Schemas | `schema_validation_report.*`. |
| Export Diagnostics | `experimental_diagnostics_report.*`. |
| Productization Report | `productization_readiness_report.*`. |
| Open Output Folder | Apre la cartella radice dei report. |

## Libreria Blueprint

`UVFDCockpitBlueprintLibrary` espone gli stessi servizi headless del cockpit:

- caricare, risolvere, validare e compilare profili di fedeltà;
- confrontare profili;
- rilevare le funzionalità della pipeline;
- costruire lo stato degli elementi di prova;
- anteprima, applicazione e rollback della configurazione permanente governata.

Showcase confezionato: `Content/Blueprints/BPF_VFD_API`.

## Modello di sicurezza

- La revisione del cockpit, le prove, i confronti e l'anteprima delle destinazioni sono in sola lettura.
- L'applicazione permanente governata è l'unico percorso di mutazione del cockpit e richiede un'approvazione esplicita per destinazione.
- L'anteprima di applicazione di Expert Tools rimane limitata alle CVar della sessione con rollback.
- Asset, materiali, Post Process Volumes, preset MRQ e impostazioni di accessibilità non vengono modificati da VFD.

## Report e profili

```text
Saved/VisualFidelityDirector/profiles/
Saved/VisualFidelityDirector/reports/
Saved/VisualFidelityDirector/recipes/
```

Trattare gli output come locali/privati in quanto possono contenere nomi di progetti, valori CVar e indicazioni di qualità.

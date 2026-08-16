<!-- doc-provenance: AKDB:plugins/VisualFidelityDirector/architecture.md; docs/architecture/plugins/VisualFidelityDirector/product-facts.yml; reconciled 2026-07-12 -->
# Risoluzione dei problemi

## Ho abilitato il plugin e non è successo nulla

Causa: VFD si apre da una voce di menu; non mostra una finestra all'avvio.

Soluzione:

1. Riavviare Unreal Editor dopo aver abilitato il plugin.
2. Aprire **Tiny Tools > Visual Fidelity Director**.
3. Se la voce di menu manca ancora, verificare che il plugin sia abilitato in **Modifica > Plugin**.

## Metriche live non disponibili

Causa: le metriche live richiedono un contesto di misurazione della finestra dell'editor disponibile. Alcune piattaforme, sessioni headless o primi tick dell'editor potrebbero non esporre i dati dei passaggi GPU.

Soluzione:

1. Fare clic su **Refresh** dopo che la finestra è visibile.
2. Attendere il completamento della finestra di campionamento multi-frame (diversi tick dell'editor).
3. Trattare `-1` o le stringhe non disponibili esplicite come degrado onesto — VFD non inventa numeri.

## Nessun profilo appare nella barra dei profili

Causa: non esistono ancora profili di fedeltà in `Saved/VisualFidelityDirector/profiles/`.

Soluzione:

1. Importare o duplicare un profilo tramite il workflow del progetto, oppure migrare da una ricetta integrata utilizzando Expert Tools e gli strumenti del progetto.
2. Fare clic su **Refresh** nella pagina Cockpit.

## L'applicazione governata ha ignorato tutto

Causa: nessuna destinazione è stata spuntata, la differenza compilata corrisponde già, o la destinazione è bloccata.

Soluzione:

1. Fare clic prima su **Build Destinations**.
2. Esaminare ogni riepilogo e spuntare l'approvazione solo per le destinazioni previste.
3. Confermare che il profilo attivo compili con modifiche (`Compile Preview`).

## Il confronto dei profili non mostra differenze

Causa: i due profili compilano nello stesso stato desiderato per tutti gli assi, oppure un profilo non ha superato la validazione.

Soluzione:

1. Verificare che entrambi i profili compilino senza errori.
2. Modificare una variante o un livello di intento su un profilo e aggiornare.

## Il pannello di controllo / Expert Tools si apre ma non viene scritto alcun report

Causa: la cartella `Saved` del progetto potrebbe essere in sola lettura o non disponibile.

Soluzione:

1. Passare a **Expert Tools** e fare clic su **Open Output Folder**.
2. Confermare che il progetto possa scrivere in `Saved/VisualFidelityDirector/`.
3. Riprovare **Export Snapshot** e leggere la riga **Status**.

## L'anteprima di applicazione ha ignorato tutto

Causa: la ricetta selezionata potrebbe contenere solo raccomandazioni di esportazione, il valore raccomandato potrebbe già corrispondere al valore attuale, o la CVar potrebbe non essere disponibile in questo contesto dell'engine.

Soluzione:

1. Esportare prima una valutazione a secco della ricetta.
2. Aprire `settings_diff.md`.
3. Controllare le colonne **Mode**, **Supported** e **Risk**.

## Una CVar risulta Non disponibile

Causa: alcune CVar dipendono dalla versione dell'engine, dal renderer, dalla piattaforma o dal contesto.

Soluzione: trattare la raccomandazione come revisione manuale. VFD registra i valori non disponibili anziché far fallire l'intero workflow.

## Le raccomandazioni MRQ non hanno modificato il mio preset

Causa: la mutazione dei preset MRQ è intenzionalmente non supportata.

Soluzione: aprire `mrq_recommendation.md` e applicare manualmente le impostazioni cinematografiche dopo la revisione.

## La raccomandazione Lumen non ha modificato mesh o materiali

Causa: le impostazioni delle schede mesh Lumen, i grafi dei materiali e le opzioni di condivisione delle schede dei materiali sono intenzionalmente riservati alla sola revisione manuale.

Soluzione: esportare **Lumen Deep Scan** o una valutazione a secco della ricetta Lumen, quindi ispezionare i report e applicare manualmente le modifiche alle mesh o ai materiali solo dopo la validazione visiva.

## La diagnostica sperimentale sembra troppo approssimativa

Causa: il report diagnostico è una mappa di calore di instradamento della revisione basata sui metadati. Non è una mappa di calore delle differenze di frame basata sui pixel e non cattura i vettori di movimento.

Soluzione: utilizzare i report di snapshot e scanner per una revisione strutturata; catturare manualmente le prove visive quando necessario.

## L'applicazione della libreria Blueprint non ha scritto nulla

Causa: `ApplyPersistentConfiguration` richiede `Request.bUserApproved` e riepiloghi delle destinazioni approvati.

Soluzione: chiamare prima `PreviewPersistentDestinations`, contrassegnare come approvate solo le destinazioni previste nella richiesta, quindi chiamare l'applicazione con `bUserApproved=true`.

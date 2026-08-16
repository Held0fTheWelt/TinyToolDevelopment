<!-- doc-provenance: product-facts.yml reconciled 2026-07-01; source AKDB:plugins/AssetLoaderStudio/architecture.md -->
# Guida rapida

## Obiettivo

Aprire Asset Loader Studio, inviare una richiesta di caricamento runtime, ispezionare uno snapshot di tabella, visualizzare l'anteprima di un'operazione gestita e applicarla solo dopo che l'anteprima è stata autorizzata.

## Primo avvio

1. Abilita **Asset Loader Studio** e riavvia l'Unreal Editor se richiesto.
2. Apri **Tools > Tiny Tools > Asset Loader Studio**.
3. Scegli la modalità **Guided** per il primo avvio normale. Usa **Simple** quando desideri solo un'ispezione.
4. Inserisci un percorso oggetto completo noto come `/Game/Data/DT_Items.DT_Items` o un percorso DataAsset sotto il tuo controllo, quindi fai clic su **Inspect**.
5. Esamina lo stato del job restituito, i percorsi caricati, i fallimenti parziali, il grafo delle dipendenze e la diagnostica.
6. Acquisisci uno snapshot di tabella da un DataAsset o una DataTable sotto il tuo controllo.
7. Apri **Validation** e risolvi asset mancanti, righe duplicate, riferimenti non validi o dinieghi di autorizzazione prima di tentare una modifica.
8. Usa **Preview Operation** per qualsiasi azione di creazione, duplicazione, rinominazione, riorientamento (retarget), riparazione, salvataggio, ripristino (rollback) o eliminazione.
9. Usa **Apply Operation** solo quando l'anteprima segnala una decisione di profilo consentita, un livello di rischio accettabile e i target corrispondono agli asset che intendi modificare.
10. Esamina il report di applicazione e salva i pacchetti modificati tramite il normale flusso di lavoro Unreal/controllo codice sorgente.

## Punti di ingresso Blueprint e Runtime

- `SubmitLoadRequest` avvia una richiesta di caricamento runtime e restituisce uno stato del job.
- `CaptureTableSnapshot` legge dati di tabella strutturati per la validazione e il lavoro sul grafo.
- `PreviewOperation` valuta una modifica pianificata rispetto a un profilo di autorizzazione prima dell'applicazione.

Mantieni le integrazioni UCM e MCP opzionali; l'area di lavoro e il sottosistema runtime costituiscono il percorso autonomo di primo utilizzo.

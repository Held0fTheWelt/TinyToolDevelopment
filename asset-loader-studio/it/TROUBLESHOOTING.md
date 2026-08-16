<!-- doc-provenance: product-facts.yml reconciled 2026-07-01; source AKDB:plugins/AssetLoaderStudio/architecture.md -->
# Risoluzione dei problemi

## Asset mancanti

Utilizza percorsi oggetto completi con il suffisso dell'oggetto, ad esempio `/Game/Data/DA_Item.DA_Item`. Se la validazione segnala `ALS.Table.MissingReferencedAsset`, reindirizza il campo a un asset esistente o svuotalo.

## Percorsi errati

`ALS.InvalidSoftObjectPath` e `ALS.Table.InvalidReferencePath` indicano che il percorso non può essere analizzato come percorso oggetto Unreal. Ricopia il riferimento dal Content Browser.

## Applicazioni fallite

Le applicazioni richiedono un'anteprima consentita e un token di approvazione. Nell'area di lavoro dell'editor, il pulsante Apply approva l'ultima anteprima. Nell'automazione, imposta `approval_token` sull'ID dell'anteprima o su `approved`.

## Dinieghi di autorizzazione

Utilizza `asset_loader_studio.state.read.v1` per ispezionare i profili attivi. I dinieghi comuni riguardano la modalità sola lettura, la modalità solo dry-run, i limiti di righe/asset interessati, i percorsi al di fuori di `allowed_roots` o la mancanza dell'autorizzazione distruttiva.

## Salvataggi falliti

L'applicazione generica contrassegna i pacchetti come modificati ("dirty") e fornisce indicazioni per il ripristino. Salva tramite la finestra di salvataggio dell'editor Unreal o il flusso del controllo codice sorgente dopo aver esaminato gli asset modificati.

## Righe vuote o duplicate

Le DataTables con ID di riga vuoti o duplicati non possono essere mappate in modo sicuro su operazioni di riga stabili. Rinomina o ripara le righe nella tabella proprietaria, quindi acquisisci un nuovo snapshot.

## Azioni distruttive bloccate

L'eliminazione e altre operazioni distruttive richiedono un profilo che le consenta e un token di approvazione distruttiva esplicito. È preferibile visualizzare l'anteprima del piano, salvare copie di backup o lo stato del controllo codice sorgente, quindi applicare solo l'anteprima verificata.

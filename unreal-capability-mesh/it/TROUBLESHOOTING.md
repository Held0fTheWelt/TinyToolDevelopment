<!-- doc-provenance: AKDB:plugins/UnrealCapabilityMesh/architecture.md; docs/architecture/plugins/UnrealCapabilityMesh/product-facts.yml; reconciled 2026-07-19 -->
# Risoluzione dei problemi

## Caricamento della configurazione fallito

Verifica `Saved/UnrealCapabilityMesh/setup_validation_report.json`.

Cause comuni:

- nessun file `project_profile.json` nelle radici di configurazione incluse, dei plugin abilitati o del progetto
- `schema_version` non valida
- errore di battitura nel percorso del manifesto
- JSON non valido
- array obbligatori mancanti come `capabilities` o `endpoints`

Per il primo utilizzo, un profilo locale al progetto è opzionale. UCM unisce il proprio profilo predefinito incluso con i profili forniti dai plugin abilitati. Crea un profilo di progetto solo per override intenzionali o percorsi di proprietà del progetto, quindi fai clic su `Reload Setup`.

## Funcionalità non individuata

Verifica:

- il manifesto della funzionalità è referenziato dal profilo nella radice di configurazione proprietaria
- la funzionalità possiede un `capability_id` non vuoto
- l'ID dell'endpoint esiste
- i nomi dei plugin richiesti sono caricati
- gli schemi richiesti esistono

Se la funzionalità appartiene a un altro plugin, conferma che tale plugin sia abilitato e che il suo pacchetto contenga `Config/UnrealCapabilityMesh/project_profile.json`. Non copiare la definizione del provider nel progetto come soluzione temporanea; ricarica la configurazione ed esamina le radici di configurazione individuate.

## Avvisi di definizioni duplicate nel progetto

La stessa funzionalità, lo stesso endpoint, lo stesso schema o lo stesso percorso di proprietà del provider esistono probabilmente sia in un profilo locale al plugin sia nell'override del progetto.

Rimuovi la copia duplicata nel progetto, a meno che il progetto non sovrascriva intenzionalmente tale definizione. I profili di progetto dovrebbero normalmente contenere modifiche ai criteri o percorsi composti di proprietà del progetto, mentre i contratti del provider rimangono locali al plugin.

## TTER non mostra un percorso UCM valido dopo l'avvio

Conferma che il plugin opzionale Tiny Tool Execution Integration Bridge sia abilitato. Il suo modulo Editor ricarica la configurazione di UCM prima dell'individuazione di TTER. Dopo aver abilitato un nuovo provider o modificato la configurazione, fai clic su `Reload Setup` e aggiorna l'individuazione degli strumenti.

## Percorso bloccato

Apri il report del percorso in `Saved/UnrealCapabilityMesh/route_reports`. Il pianificatore dei percorsi registra spiegazioni e motivi di blocco.

Cause comuni:

- nessuna regola consente gli effetti collaterali aggregati
- il percorso utilizza `project_mutation` e la regola predefinita lo blocca
- la modifica degli asset richiede approvazione o esecuzione di prova (dry-run)
- gli schemi di input e output sono incompatibili

Se l'auto-approvazione automatica **SPERIMENTALE** è abilitata nella colonna di approvazione del catalogo percorsi o nel profilo, disabilitala prima di esaminare il comportamento della governance. L'override ampio salta le regole di diniego corrispondenti, i controlli sulla modifica di asset/progetto del percorso, i requisiti di approvazione e di esecuzione di prova, e può quindi mascherare ciascuno di questi esiti dei criteri.

## Invocazione dell'endpoint fallita

Verifica `Saved/UnrealCapabilityMesh/invocation_reports`.

Cause comuni:

- il percorso della classe non si risolve
- il nome della funzione è errato
- il collegamento dei parametri non corrisponde al parametro della funzione
- la modalità di invocazione è dichiarata ma nessun invocatore generico la supporta ancora
- il plugin provider non è caricato

## I report sono vuoti

Fai di nuovo clic su `Reload Setup`. Il pannello ricarica i manifesti e rigenera la diagnostica. Conferma inoltre che il percorso di configurazione del progetto corrisponda al progetto attivo e non a una cartella del motore o di esempio.

## La validazione dei sorgenti segnala valori hardcoded

La validazione dei sorgenti può segnalare nomi di plugin partner o ID di funzionalità specifici del prodotto nel codice UCM. Sposta le stringhe specifiche dell'integrazione nel JSON di configurazione anziché aggiungere rami C++.

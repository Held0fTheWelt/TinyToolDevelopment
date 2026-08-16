<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/CodeCopyrightEditor/architecture.md -->
# Risoluzione dei problemi

Questa pagina elenca i problemi comuni e le soluzioni pratiche.

## Lo strumento non appare nel menu Tools

Verifica:

- Il plugin è abilitato per il progetto.
- Unreal Editor è stato riavviato dopo l'abilitazione del plugin.
- Il plugin è stato compilato per la versione corrente di Unreal Engine.

Percorso del menu atteso:

```text
Tools > Code Tools > Code Copyright Editor
```

## La pagina in Project Settings è mancante

Verifica:

- Il modulo del plugin è stato caricato con successo.
- Il progetto utilizza una build editor, non una build runtime pacchettizzata.
- Il plugin è installato nella cartella dei plugin del progetto o dell'engine.

## La scansione non trova file

Verifica:

- `ScanRootPaths` contiene cartelle esistenti.
- I file utilizzano estensioni supportate.
- I frammenti di percorso esclusi non sono troppo ampi.

## I file sono contrassegnati come PROTECTED

Lo scanner ha trovato un testo simile a una nota che non corrisponde ai marcatori propri o ha corrisposto a marcatori protetti.

Opzioni di risoluzione:

- Lascia il file intatto se si tratta di codice di terze parti o Epic.
- Aggiungi la cartella del fornitore alle esclusioni.
- Aggiungi un marcatore proprio solo se il file appartiene davvero al tuo progetto.

## Errori di scrittura (Write Errors)

Cause comuni:

- Il file è in sola lettura.
- Il file è bloccato da un altro processo.
- È richiesto il checkout nel controllo versione.
- L'account utente non dispone dei permessi di scrittura.

Correggi lo stato del file, quindi esegui di nuovo scansione/applicazione.

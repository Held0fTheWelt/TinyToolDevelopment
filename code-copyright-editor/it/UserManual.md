<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/CodeCopyrightEditor/architecture.md -->
# Manuale utente

Questo manuale spiega l'intero flusso di lavoro nell'editor per Code Copyright Editor.

## Scopo

Code Copyright Editor gestisce il testo delle note sul copyright in due punti:

- La nota sul copyright a livello di progetto Unreal Engine.
- Le intestazioni dei file sorgente nelle cartelle di progetto e plugin configurate.

Il plugin è progettato per riscritture controllate dei sorgenti. Scansiona prima, mostra un'anteprima, consente all'utente di selezionare i file e riscrive i file modificabili selezionati solo dopo conferma.

## Apertura dello strumento

Dopo aver abilitato il plugin, apri:

```text
Tools > Code Tools > Code Copyright Editor
```

Il plugin espone la sua configurazione anche sotto:

```text
Project Settings > Plugins > Code Copyright Editor
```

## Flusso di lavoro principale

1. Configura identità, licenza, modello, ambito e impostazioni di protezione.
2. Salva le impostazioni.
3. Aggiorna la nota nelle impostazioni di progetto, se necessario.
4. Scansiona il codice sorgente.
5. Esamina i badge di stato e le anteprime.
6. Aggiungi metadati opzionali per singolo file.
7. Seleziona solo i file che devono essere riscritti.
8. Applica ai file selezionati.
9. Esegui un'altra scansione per verificare.
10. Esporta report o esegui il commandlet in CI.

La scansione non scrive mai i file sorgente. L'applicazione riscrive solo i file selezionati classificati come modificabili.

## Schede dell'editor

La finestra principale dell'editor è organizzata in schede dedicate:

| Scheda | Scopo |
| --- | --- |
| `Configure` | Modifica modelli, impostazioni proprietario/licenza, ambito di scansione, regole di protezione e impostazioni note del progetto. |
| `Scan & Review` | Esegui scansioni, ispeziona lo stato dei file, seleziona i file modificabili, escludi file e confronta le note esistenti/proposte. |
| `File Metadata` | Aggiungi o cancella informazioni e descrizioni dei file selezionati mostrate dai token di metadati. |
| `Apply & Reports` | Conferma le riscritture selezionate ed esporta l'ultimo report di scansione JSON dell'editor. |
| `Help` | Leggi la guida al flusso di lavoro integrata e la legenda degli stati. |

## Valori di stato

| Stato | Significato | Comportamento applicazione |
| --- | --- | --- |
| `OK` | Il file corrisponde già al modello generato. | Non necessario. |
| `MISSING` | Nessuna nota compatibile trovata. | Può essere inserita se abilitata. |
| `REPLACE` | Una nota propria o un segnaposto Unreal può essere sostituito. | Può essere riscritta. |
| `PROTECTED` | Trovata una nota esterna, Epic o di terze parti. | Non riscritta automaticamente. |
| `CONFLICT` | Marcatori propri e protetti compaiono insieme. | Revisione manuale richiesta. |
| `EXCLUDED` | Il file corrisponde a una regola di esclusione. | Non elaborato. |
| `READ_ERROR` | Il file non può essere letto. | Non elaborato. |
| `WRITE_ERROR` | Il file non può essere salvato. | Non elaborato. |
| `UPDATED` | Il file è stato scritto nell'ultimo passaggio di applicazione. | Esegui un'altra scansione per verificare. |

## Metadati per singolo file

I metadati per singolo file aggiungono contesto a un solo file senza modificare il modello globale.

Metadati disponibili:

- `File Information`
- `Description`

Flusso di lavoro raccomandato:

1. Scansiona i file.
2. Seleziona un file.
3. Inserisci informazioni o descrizione del file.
4. Clicca su `Save File Metadata`.
5. Assicurati che il modello contenga `{FileMetadataBlock}`.
6. Esamina l'anteprima.
7. Applica al file se la nota generata è corretta.

`Clear File Metadata` rimuove i metadati memorizzati per il file selezionato.

## Applica selezionati (Apply Selected)

Prima di applicare, l'editor chiede conferma. I file protetti e in conflitto rimangono intatti.

Dopo l'applicazione, lo strumento esegue un'altra scansione e mostra:

- Risultato dell'applicazione.
- Risultato della scansione attuale.
- Righe di stato aggiornate.

Usa il controllo versione prima di riscritture di massa. Per una rete di sicurezza aggiuntiva al primo passaggio, abilita `Create Backup Before Write`.

## Cosa non fa il plugin

Code Copyright Editor non esegue le seguenti azioni:

- Decidere la proprietà legale.
- Concedere diritti di licenza.
- Validare licenze di terze parti.
- Sostituire una consulenza legale.
- Riscrivere automaticamente le note protette.
- Eseguirsi nei giochi pacchettizzati.

Fornisce un flusso di lavoro tecnico coerente per note, report e controlli CI.

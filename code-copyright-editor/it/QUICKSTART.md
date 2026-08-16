<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/CodeCopyrightEditor/architecture.md -->
# Guida rapida

Questa guida ti accompagna dall'installazione a un **risultato reale**: Una nota sul copyright coerente applicata ai file sorgente selezionati, insieme a un report di scansione che puoi aprire. Code Copyright Editor funziona in modo completamente autonomo — non è richiesto alcun altro plugin.

## Cosa otterrai dopo questa guida

Identità e licenza configurate, il codice sorgente scansionato con lo stato per ogni file e una riscrittura controllata applicata ai file selezionati — oltre a un report di scansione JSON in `Saved/CodeCopyrightEditor/`.

## Requisiti

- Unreal Engine 5 editor (il plugin viene eseguito nell'editor, non nei giochi pacchettizzati).
- Un progetto C++ o Blueprint con cartelle sorgente/plugin da scansionare.
- Nessun software di terze parti, account o runtime esterno richiesto. Vedi [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md).

## 1. Installazione e abilitazione

1. Aggiungi **Code Copyright Editor** dalla tua libreria Fab al progetto (o installalo nell'engine).
2. Nell'editor, apri **Edit → Plugins**, abilita **Code Copyright Editor** e riavvia quando richiesto.

## 2. Apertura dello strumento (Primo risultato)

1. Apri **Tools → Code Tools → Code Copyright Editor**.
2. Sulla scheda **Configure**, imposta la tua identità e licenza (proprietario, identificatore di licenza, modello, ambito di scansione). Clicca su **Save**.
3. Passa a **Scan & Review** e clicca su **Scan Files**.

Ora vedi ogni file idoneo con un badge di stato (`OK`, `MISSING`, `REPLACE`, `PROTECTED`, …). La scansione non scrive mai sui file — è un'anteprima sicura.

## 3. Un esempio pratico reale: Applicare le note ai file selezionati

1. Su **Scan & Review**, clicca su **Select Changeable** — questo seleziona solo le righe che possono essere riscritte in sicurezza (`MISSING`, `REPLACE`). I file `PROTECTED` e `CONFLICT` rimangono intatti.
2. Seleziona prima una singola riga e confronta la nota **esistente** con quella **proposta** nell'anteprima.
3. (Consigliato) Sulla scheda **Configure**, abilita **Create Backup Before Write** ed effettua prima il commit del tuo lavoro nel controllo versione.
4. Clicca su **Apply Selected** e conferma. Lo strumento riscrive solo i file selezionati e modificabili, quindi esegue una nuova scansione.

**Risultato atteso:** I file applicati passano allo stato `UPDATED`; vengono mostrati il risultato dell'applicazione e una nuova scansione. Su **Apply & Reports**, clicca su **Export JSON**.

## 4. Dove si trovano i risultati

```text
Saved/CodeCopyrightEditor/LastCopyrightScan.json
```

Puoi anche aggiornare la nota a livello di progetto (senza riscrittura dei sorgenti) con **Update Project Notice**, che scrive in *Project Settings → Project → Description → Legal → Copyright Notice*.

## 5. Passaggi successivi

- Flusso di lavoro completo e ogni scheda/azione: [UserManual.md](UserManual.md).
- Tutti i token dei modelli (`{CopyrightText}`, `{LicenseIdentifier}`, `{FileMetadataBlock}`, …): [SettingsReference.md](SettingsReference.md).
- Impostazioni: [SettingsReference.md](SettingsReference.md).
- Problemi: [TROUBLESHOOTING.md](TROUBLESHOOTING.md) e [FAQ.md](FAQ.md).

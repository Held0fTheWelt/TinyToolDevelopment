<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/CodeCopyrightEditor/architecture.md -->
# FAQ (Domande frequenti)

## A cosa serve Code Copyright Editor?

Code Copyright Editor aiuta gli sviluppatori di Unreal Engine a gestire note sul copyright coerenti nelle impostazioni di progetto e nei file sorgente. Può scansionare, mostrare in anteprima, aggiornare e segnalare le intestazioni dei file sorgente da un unico flusso di lavoro nell'editor.

## Il plugin influisce sul codice di gioco a runtime?

No. Code Copyright Editor è uno strumento ad uso esclusivo dell'editor. È destinato a flussi di lavoro di sviluppo, revisione, documentazione e CI.

## Può aggiornare automaticamente un intero codice sorgente?

Sì, ma solo dopo la scansione e la revisione. L'editor mostra quali file possono essere modificati, quali file sono protetti e come apparirà la sostituzione proposta prima di applicare le modifiche.

## Protegge le note di terze parti o di Epic?

Sì. Lo scanner è progettato per proteggere le note esterne, di Epic e di terze parti dalla riscrittura automatica. I file protetti e in conflitto devono essere rivisti manualmente.

## Posso personalizzare il modello di copyright?

Sì. Puoi modificare il modello di nota per i file sorgente e il modello di nota per le impostazioni di progetto. Token come nome del prodotto, percorso del file, anno, identificatore di licenza e descrizione per singolo file possono essere inseriti automaticamente.

## Supporta i flussi di lavoro SPDX o REUSE?

Il plugin fornisce modelli e report orientati a REUSE/SPDX. Questi report sono destinati a supportare i flussi di lavoro di revisione e CI, ma non costituiscono una certificazione legale.

## È presente un commandlet per la CI?

Sì. Il commandlet `CodeCopyrightCheck` incluso può scansionare il progetto, correggere facoltativamente i file modificabili, scrivere report e far fallire la CI quando le note sul copyright non sono sincronizzate.

## Sostituisce la consulenza legale?

No. Aiuta ad applicare e rivedere il testo delle note in modo coerente. Non decide la proprietà legale, non valida licenze di terze parti né fornisce consulenza legale.

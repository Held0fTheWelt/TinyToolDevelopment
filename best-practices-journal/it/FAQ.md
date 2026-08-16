<!-- doc-provenance: product-facts.yml reconciled 2026-07-19; source AKDB:plugins/BestPracticesJournal/architecture.md; release 1.1.2 -->
# FAQ

## BPJ è uno strumento di annotazione generico?

No. BPJ è destinato a pratiche ingegneristiche basate su evidenze con applicabilità, compromessi, modalità di errore, provenienza, stato di revisione e cronologia degli esiti.

## Quando un elemento dovrebbe rimanere un candidato?

Mantienilo come candidato quando evidenze, applicabilità, compromessi, modalità di errore, provenienza o stato di revisione sono incompleti. I candidati possono essere utili, ma non devono essere trattati come linee guida accettate.

## BPJ modifica i file del progetto?

No. BPJ può creare documenti di applicazione e importare esiti, ma la modifica del progetto spetta a strumenti a valle approvati o a flussi di lavoro umani.

## Cosa deve contenere un documento di applicazione?

Utilizza un documento per contesto target, adattamento raccomandato, vincoli, riferimenti delle evidenze, validazione richiesta e stato di approvazione. Non utilizzarlo come piano di patch o comando di modifica.

## BPJ richiede IIS, SDA, UCI, PRS, UCM o LLM Store?

No. BPJ è autonomo. Plugin opzionali Tiny Tool possono fornire evidenze, indicizzazione, documentazione, implementazione o flussi di percorsi, ma non sono richiesti per l'uso principale.

## BPJ può chiamare l'AI o decidere i passaggi di implementazione?

No. BPJ può memorizzare evidenze o intenzioni create da un altro flusso di lavoro rivisto, ma non gestisce l'esecuzione dell'AI, il recupero, la pianificazione delle patch, l'applicazione, il ripristino o la validazione finale.

## Dove vengono memorizzati i dati?

Il profilo predefinito utilizza artefatti JSON locali al progetto sotto la radice di archiviazione di BPJ. Profil SQLite opzionali o profili studio esterni possono essere configurati per flussi di lavoro più ampi.

## Quali dati possono essere sensibili?

Registri di pratiche, evidenze, documenti, esiti e report possono contenere percorsi locali, nomi di progetti, note di revisione, output di validazione, note sui diritti o diagnostica dei provider. Esamina ed oscura le esportazioni prima della condivisione.

## Dove trovo log e report?

I report vengono salvati sotto `Saved/BestPracticesJournal/reports/`. La diagnostica di runtime, editor e commandlet utilizza `LogBestPracticesJournal` nel log di Unreal. Gli artefatti salvati rimangono la prova duratura.

## Posso condividere le pratiche con un team?

Sì, dopo la revisione. Tratta le esportazioni come locali al progetto finché non sono state bonificate da percorsi privati, note riservate ed evidenze sensibili sotto il profilo dei diritti.

## La mancanza di provider opzionali può danneggiare il journal?

No. I provider mancanti dovrebbero apparire solo come stato o diagnostica. Registri manuali, evidenze locali, validazione, esportazione e importazione degli esiti devono rimanere disponibili.

## Gli esiti falliti dovrebbero essere importati?

Sì. Gli esiti falliti, respinti, parziali e senza effetto (no-op) sono importanti perché possono indebolire, contraddire, specializzare o sostituire la pratica. Nasconderli rende il journal meno affidabile.

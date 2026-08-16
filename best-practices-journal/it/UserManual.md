<!-- doc-provenance: product-facts.yml reconciled 2026-07-19; source AKDB:plugins/BestPracticesJournal/architecture.md; release 1.1.2 -->
# Manuale utente

Best Practices Journal è un workbench dell'editor per la governance delle pratiche ingegneristiche basata su evidenze. È un supporto alle decisioni e una memoria di revisione, non un pianificatore di patch, un editor di sorgenti, un esecutore AI o uno strumento di modifica degli asset.

## Flusso di lavoro principale

1. Aquisisci una pratica o un candidato da una nota manuale, un riferimento di evidenza o un provider opzionale.
2. Aggiungi applicabilità, compromessi, modalità di errore, provenienza, note sui diritti e metadati di revisione.
3. Valida il registro prima di accettarlo o esportarlo.
4. Cerca le pratiche durante la selezione delle linee guida per un’attività o una revisione.
5. Crea un documento di applicazione per una pratica rivista o un candidato esplicito.
6. Consegna il documento a un flusso di lavoro umano, UCI, PRS o a un altro esecutore approvato.
7. Importa i report degli esiti di implementazione per registrare se la pratica è stata convalidata, indebolita, contraddetta, specializzata o sostituita.

## Qualità dei registri di pratica

Utilizza BPJ per pratiche in grado di superare la revisione. Un registro utile include:

- Un problema concreto e un contesto target.
- Una soluzione espressa come linea guida riutilizzabile, non come codice di implementazione copiato.
- Perché la linea guida funziona, dove si applica e dove fallisce.
- Compromessi, precondizioni, regole di adattamento e modalità di errore.
- Riferimenti delle evidenze, provenienza, note sui diritti, affidabilità e stato di revisione.

Se tali campi sono sconosciuti, mantieni l'elemento come candidato o bozza. Non promuoverlo a linea guida accettata solo perché il riepilogo sembra plausibile.

## Operazioni pubbliche

- **Create practice record** memorizza una pratica rivista o in bozza con evidenze, contesto, compromessi e stato di revisione.
- **Create practice candidate** memorizza una bozza o una proposta derivata da un provider fino alla sua revisione esplicita.
- **Attach evidence** collega prove locali/manuali/provider senza copiare codice di implementazione protetto.
- **Search practices** restituisce i registri delle pratiche corrispondenti dall'archivio di artefatti di proprietà di BPJ.
- **Create application brief** esporta una consegna esclusivamente intenzionale per uno specifico contesto target.
- **Import implementation outcome** chiude il ciclo dopo l'implementazione o il rifiuto.

## Documenti di applicazione (Application Briefs)

Un documento dovrebbe aiutare un altro flusso di lavoro a pianificare in modo sicuro. Può includere progetto/modulo/ambito target, adattamento raccomandato, motivazione, vincoli, categorie di azioni consentite e vietate, requisiti di validazione, output attesi, riferimenti delle evidenze, stato di approvazione e note di compatibilità.

Un documento non deve agire come autorizzazione per BPJ di modificare file. Se lo strumento a valle applica modifiche, deve gestire la risoluzione dell'ambito, la pianificazione dell'esecuzione di prova, l'approvazione, i varchi di modifica, la validazione, il ripristino e il proprio report sull'esito.

## Importazioni degli esiti (Outcome Imports)

Importa ogni esito significativo, inclusi quelli falliti, respinti, parziali e senza effetto (no-op). Gli esiti aggiornano la cronologia della pratica, l'affidabilità, le note di revisione e i collegamenti di evoluzione. Non riscrivono la pratica originale come universalmente corretta.

Utilizza i campi dell'esito per riferimenti ai file modificati, percorsi dei report di validazione, lezioni apprese, aggiornamenti raccomandati del journal, avvisi, errori e collegamenti a piani o report esterni.

## Provider opzionali

Provider opzionali di evidenze, candidati, esiti, consegne, indicizzazione, percorsi o implementazioni possono arricchire BPJ. Devono rimanere sostituibili. Se un provider è assente, prosegui con registri manuali, evidenze locali, artefatti JSON/Markdown e la validazione BPJ.

## Capability Mesh (MCP)

Gli agenti privi di accesso ai file possono completare il ciclo di vita del journal basato sulla revisione tramite UMCP:

- `bpj.gather_candidates.v1` — scansiona le cartelle della posta in arrivo dei provider (incluso `project_intelligence_orchestrator` dalla consegna PIO).
- `bpj.repository.list.v1` — elenca gli ID di pratiche, candidati, evidenze, documenti ed esiti.
- `bpj.practice.read.v1` — legge direttamente un registro serializzato.
- `bpj.candidate.promote.v1` — promuove un candidato rivisto (richiede l'approvazione dell'utente sul percorso).
- `bpj.import_artifacts.v1` — importa gli involucri di candidati PIO (`schema` / `schema_version` che iniziano con `bpj.implementation_intent_candidates.`).

Percorso della posta in arrivo dei provider: `Saved/BestPracticesJournal/provider_inbox/candidates/<provider_id>/`.

## Commandlet

I commandlet sono utili per la validazione, l'importazione di artefatti e l'esportazione di campioni, ma non sono passaggi obbligatori per il primo utilizzo. Utilizza i report salvati in `Saved/BestPracticesJournal/reports/` come prove durature per l'automazione. I log riassumono l'accaduto; gli artefatti salvati rimangono il registro ufficiale.

## Confini

BPJ registra conoscenze e intenzioni. Non modifica file sorgente, asset, file Build.cs, descrittori di progetto o codice di plugin esterni. I responsabili dell'esecuzione a valle devono gestire i propri varchi di anteprima, approvazione, validazione e ripristino.

## Evidenze locali e log

BPJ archivia le prove durature di revisione sotto `Saved/BestPracticesJournal/`. Utilizza i file JSON/Markdown in `reports`, `application_briefs`, `implementation_outcomes` e `schemas` durante la condivisione o l'audit di un flusso di lavoro. La categoria di log Unreal `LogBestPracticesJournal` è destinata alla diagnostica dell'operatore e ai riepiloghi dei commandlet; non rappresenta il registro ufficiale per le pratiche accettate.

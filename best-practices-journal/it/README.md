<!-- doc-provenance: product-facts.yml reconciled 2026-07-19; source AKDB:plugins/BestPracticesJournal/architecture.md; release 1.1.2 -->
# Documentazione di Best Practices Journal

Best Practices Journal aiuta i team a governare le pratiche ingegneristiche riutilizzabili direttamente all'interno dell'Unreal Editor. Memorizza conoscenze sulle pratiche, provenienza, stato di revisione, intenzione di implementazione e cronologia degli esiti sotto una radice di artefatti locale di proprietà di BPJ.

La versione 1.1.2 supporta Unreal Engine 5.4 e successive. Le evidenze importate e gli output dei provider rimangono candidati da rivedere fino all'esplicita promozione umana; nessun produttore esterno può accettare autonomamente una pratica.

BPJ è autonomo. Provider opzionali dell'ecosistema possono fornire evidenze, candidati, esiti o destinazioni di consegna, ma il journal, la validazione, la ricerca, l'esportazione e il ciclo degli esiti devono rimanere utilizzabili anche in assenza di qualsiasi provider opzionale.

## Concetti principali

- I registri delle pratiche (Practice records) descrivono linee guida ingegneristiche riutilizzabili, contesto, compromessi, applicabilità, modalità di errore e stato di revisione.
- I candidati di pratica (Practice candidates) sono bozze o proposte derivate da provider che richiedono ancora una revisione.
- I registri delle evidenze (Evidence records) collegano le pratiche a prove locali del progetto, provenienza, note sui diritti e livello di affidabilità.
- I documenti di applicazione (Application briefs) descrivono l'intenzione di adattare una pratica rivista a un target specifico.
- Le importazioni degli esiti (Outcome imports) registrano se il lavoro a valle ha convalidato, indebolito, contraddetto, specializzato o sostituito una pratica.
- Le politiche di oscuramento e protezione mantengono intenzionali i registri condivisi.
- I backend di archiviazione consentono a BPJ di funzionare come artefatti JSON, SQLite locale o un profilo studio basato su Postgres.

## Confini del prodotto

BPJ possiede registri di pratiche, candidati, riferimenti di evidenze, stato di revisione, documenti di applicazione, importazioni di esiti di implementazione, esportazioni deterministiche, validazione di schemi, oscuramento, protezioni e report locali. Non possiede la pianificazione delle patch, l'esecuzione di prova/applicazione (dry-run/apply), il ripristino (rollback), la validazione finale dell'implementazione, l'esecuzione dell'AI o la modifica di sorgenti/asset.

I documenti di applicazione sono artefatti di consegna esclusivamente intenzionali. Gli strumenti a valle o i flussi di lavoro umani devono comunque eseguire i propri passaggi di pianificazione, approvazione, modifica, validazione e ripristino.

## Contratto di accettazione

Una pratica accettata non dovrebbe essere un semplice slogan. Prima dell'accettazione o di un riutilizzo ad ampio raggio, registra:

- Problema, contesto e soluzione.
- Perché funziona e dove si applica.
- Precondizioni, regole di adattamento, compromessi e modalità di errore.
- Riferimenti delle evidenze, provenienza, note sui diritti e affidabilità.
- Stato di revisione, note dei revisori e cronologia degli esiti, se disponibili.

I campi deboli o mancanti dovrebbero essere trattati come rilievi di validazione e non come innocui problemi di formattazione.

## Contratto per documenti ed esiti

I documenti di applicazione possono includere l'identità della pratica, il contesto target, l'adattamento raccomandato, i vincoli, le categorie di azioni consentite e vietate, i requisiti di validazione, gli output attesi, i riferimenti delle evidenze, lo stato di approvazione e le note di compatibilità. Non devono includere codice di implementazione copiato né concedere autorità di modifica.

Le importazioni degli esiti aggiornano la cronologia e l'affidabilità della pratica. Un esito fallito o respinto è un dato utile: dovrebbe essere importato anziché nascosto, poiché può indebolire, contraddire, specializzare o sostituire la pratica originale.

## Artefatti locali e registrazione

BPJ scrive gli artefatti locali del progetto sotto `Saved/BestPracticesJournal/`, inclusi `practices`, `candidates`, `evidence`, `application_briefs`, `implementation_outcomes`, `reports`, `schemas`, `logs` e `provider_inbox`. La diagnostica Unreal utilizza `LogBestPracticesJournal`; le prove durature dell'operatore dovrebbero essere tratte dagli artefatti JSON/Markdown salvati anziché da righe di log temporanee.

## Documentazione per l'acquirente

- [Guida rapida](QUICKSTART.md)
- [Manuale utente](UserManual.md)
- [Riferimento impostazioni](SettingsReference.md)
- [Risoluzione dei problemi](TROUBLESHOOTING.md)
- [FAQ](FAQ.md)
- [Software di terze parti](THIRD_PARTY_SOFTWARE.md)
- [Storage Backends](StorageBackends.md)

## Superfici operative

- Workbench dell'editor: crea, rivedi, cerca, prepara documenti, importa esiti e ispeziona lo stato dell'integrazione.
- Artefatti salvati: registri JSON/Markdown sotto `Saved/BestPracticesJournal/`.
- Commandlet: validazione, importazione di artefatti ed esportazione di campioni per automazione e controlli di rilascio.
- Percorsi/provider opzionali: superfici di integrazione sostituibili che non devono diventare requisiti per il primo utilizzo.

## Flussi di lavoro

1. Apri `Tools > Best Practices Journal`.
2. Crea o importa registri di pratiche.
3. Allega le evidenze e lo stato di revisione.
4. Valida e rivedi il registro prima dell'accettazione.
5. Produci un documento di applicazione esclusivamente intenzionale quando il contesto di implementazione è noto.
6. Importa gli esiti al termine del lavoro a valle.

## File correlati

- [../README.md](../README.md): guida rapida.
- [../CHANGELOG.md](../CHANGELOG.md): cronologia dei rilasci.
- [StorageBackends.md](StorageBackends.md): modalità di archiviazione JSON, SQLite e Postgres.

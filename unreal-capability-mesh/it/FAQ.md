<!-- doc-provenance: AKDB:plugins/UnrealCapabilityMesh/architecture.md; docs/architecture/plugins/UnrealCapabilityMesh/product-facts.yml; reconciled 2026-07-19 -->
# FAQ

## UCM è un modello o un agente AI?

No. UCM è un hub di interoperabilità. Può descrivere funzionalità correlate all'AI, ma non include modelli, prompt, provider o runtime di agenti.

## UCM modifica gli asset?

Non da solo. Si limita a caricare manifesti, pianificare percorsi, invocare endpoint dichiarati e scrivere diagnostiche. La modifica degli asset deve essere eseguita da un endpoint di un provider e consentita dai criteri.

## L'approvazione può essere aggirata?

Solo tramite i controlli di auto-approvazione automatica esplicitamente etichettati come **SPERIMENTALI** nella colonna di approvazione del catalogo percorsi nella pagina Routes, i campi corrispondenti in `project_profile.json` o lo strumento MCP `mesh_configure_experimental_self_approval`. Si tratta di una deviazione ampia dai criteri: regole di diniego, controlli sulle modifiche di asset/progetto, approvazione e requisiti di esecuzione di prova vengono saltati. È intesa unicamente per test o flussi di lavoro locali a proprio rischio; mantieni **Approve all at own risk** e tutti gli interruttori per singolo percorso disattivati per l'uso normale.

## Perché usare i manifesti anziché dipendenze C++ dirette?

I manifesti consentono ai progetti di connettere gli strumenti senza creare catene di dipendenze al momento della compilazione tra i plugin. Ciò mantiene l'hub neutrale e più semplice da pacchettizzare.

## Dove vengono scritti i report?

I report vengono scritti in `Saved/UnrealCapabilityMesh`.

## Dove vengono archiviati i manifesti del progetto?

I manifesti del progetto vengono archiviati in `Config/UnrealCapabilityMesh`.

## UCM può integrare plugin di terze parti del Marketplace?

Sì, quando tali plugin espongono funzioni richiamabili, contratti di file o funzionalità modulari che possono essere descritte da manifesti o adattatori.

## UCM include codice di terze parti?

Il plugin non include codice sorgente o dipendenze di runtime di terze parti.

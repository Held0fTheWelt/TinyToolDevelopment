<!-- doc-provenance: product-facts.yml reconciled 2026-07-19; source AKDB:plugins/BestPracticesJournal/architecture.md; release 1.1.2 -->
# Software di terze parti

Best Practices Journal non include runtime di terze parti, provider di modelli, server di database o eseguibili esterni.

I flussi di lavoro opzionali con SQLite o Postgres rappresentano profili di archiviazione e scelte di ambiente esterno. Non vengono forniti come software di terze parti inclusi nel pacchetto del plugin.

Se un progetto utilizza SQLite, Postgres, IIS, UCM, UCI, PRS o qualsiasi altro componente opzionale dell'ecosistema, tale componente rimane una scelta esterna del progetto o dello studio. Il pacchetto fornito di BPJ deve comunque poter aprire, validare, importare, esportare e rivedere gli artefatti JSON senza tali componenti.

Provider e consumatori opzionali sono superfici di integrazione, non software inclusi. La loro assenza dovrebbe manifestarsi solo come stato o diagnostica, non come un fallimento di avvio o di primo utilizzo di BPJ.

<!-- doc-provenance: product-facts.yml reconciled 2026-07-19; source AKDB:plugins/BestPracticesJournal/architecture.md; release 1.1.2 -->
# Risoluzione dei problemi

## Validazione della pratica fallita

**Causa:** Il registro non contiene il contesto richiesto, l'applicabilità, le evidenze, i compromessi, le modalità di errore, la provenienza, lo stato di revisione o le note sui diritti.

**Risoluzione:** Apri la pratica, completa i campi mancanti e valida nuovamente prima di accettarla o esportarla.

## La pratica appare troppo generica

**Causa:** Il registro è scritto come uno slogan o una preferenza di stile anziché come una pratica riutilizzabile con contesto ed evidenze.

**Risoluzione:** Aggiungi il problema, il contesto target, perché funziona, dove non si applica, i compromessi, le precondizioni, le modalità di errore, i riferimenti delle evidenze e i requisiti di validazione. Mantienila come candidata finché tali campi non saranno chiari.

## Protezione del documento respinta

**Causa:** Il documento di applicazione assomiglia a un piano di esecuzione, manca di una pratica sorgente rivista, contiene codice di implementazione copiato o tenta di concedere autorità di modifica.

**Risoluzione:** Riscrivi il documento come sola intenzione. Includi il contesto target, l'adattamento raccomandato, i vincoli, la validazione richiesta e lo stato di approvazione, quindi lascia che l'esecutore a valle crei il proprio piano.

## L'importazione dell'esito ha ridotto l'affidabilità

**Causa:** L'esito importato ha segnalato un fallimento, una regressione, un rifiuto, un successo parziale o lezioni che contraddicono la pratica originale.

**Risoluzione:** Conserva l'esito. Aggiorna le note di revisione, aggiungi una specializzazione o una pratica sostitutiva se necessario ed evita di eliminare le prove negative al solo scopo di mantenere pulita la raccomandazione originale.

## Provider mancante

**Causa:** Provider opzionali di candidati, evidenze, esiti di implementazione o consegne sono assenti o disabilitati.

**Risoluzione:** Prosegui con registri manuali/locali o abilita il provider opzionale. L'assenza di un provider non è fatale per il flusso di lavoro autonomo del journal.

## Il report del provider appare oscurato

**Causa:** BPJ oscura la diagnostica del provider prima di scrivere i report di integrazione affinché prompt, token, percorsi e campi riservati non trapelino attraverso gli artefatti condivisi.

**Risoluzione:** Utilizza il report oscurato per la condivisione. Esamina gli strumenti locali del provider solo se sei autorizzato a gestire la diagnostica grezza.

## Backend di archiviazione non disponibile

**Causa:** Il backend di archiviazione selezionato non riesce ad aprire il percorso configurato o il profilo esterno.

**Risoluzione:** Torna a `JsonArtifacts`, verifica i percorsi locali o correggi il profilo del database esterno all'esterno del pacchetto del plugin fornito.

## L'output del commandlet è difficile da trovare

**Causa:** Il log del commandlet riassume solo l'operazione; il report salvato costituisce il risultato duraturo.

**Risoluzione:** Esamina `Saved/BestPracticesJournal/reports/` per i report di validazione e importazione. Filtra i log di Unreal per `LogBestPracticesJournal` quando necessiti della diagnostica di contesto.

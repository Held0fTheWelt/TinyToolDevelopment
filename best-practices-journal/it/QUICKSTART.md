<!-- doc-provenance: product-facts.yml reconciled 2026-07-19; source AKDB:plugins/BestPracticesJournal/architecture.md; release 1.1.2 -->
# Guida rapida

## Obiettivo

Creare un journal delle pratiche autonomo e locale al progetto, acquisire evidenze, rivedere una pratica, esportare un documento di intenzione di implementazione e importare un esito senza modificare il codice sorgente o gli asset del progetto.

## Primo avvio

1. Abilita **Best Practices Journal** nel browser dei plugin dell'Unreal Editor.
2. Riavvia l'editor quando richiesto.
3. Apri **Tools > Best Practices Journal**.
4. Crea prima un candidato di pratica se la linea guida non è ancora stata rivista.
5. Compila problema, contesto, soluzione, applicabilità, compromessi, precondizioni e modalità di errore.
6. Allega evidenze locali o una nota di evidenza manuale con provenienza e note sui diritti.
7. Valida il registro e aggiungi le note del revisore prima di considerarlo una linea guida accettata.
8. Usa **Search practices** per ritrovare il registro per argomento, tag o nota di evidenza.
9. Crea un documento di applicazione per un target specifico ed esamina l'esportazione JSON/Markdown.
10. Importa un esito di implementazione al termine del lavoro a valle.

BPJ è autonomo: provider di evidenze opzionali, percorsi UCM, IIS, SDA, UCI o PRS possono arricchire il flusso di lavoro, ma il journal principale, la revisione, l'esportazione e il ciclo degli esiti funzionano senza alcun altro plugin Tiny Tool.

## Verifica del risultato

Dopo il primo avvio, esamina gli artefatti salvati sotto `Saved/BestPracticesJournal/`:

- `practices/` contiene i registri delle pratiche.
- `application_briefs/` contiene i file di consegna esclusivamente intenzionali.
- `implementation_outcomes/` contiene i registri degli esiti importati.
- `reports/` contiene i report di validazione, importazione e operatore.

Questi file costituiscono le prove durature per la revisione e la consegna. L'output del log di Unreal è utile per la diagnostica, ma non rappresenta il registro ufficiale.

## Verifica dei confini

Un documento di applicazione dovrebbe descrivere l'intenzione, il contesto target, i vincoli, la validazione richiesta e lo stato di approvazione. Non dovrebbe contenere codice di implementazione copiato, istruzioni di patch, passaggi di ripristino o l'autorizzazione per BPJ di modificare i file del progetto.

## Prima buona pratica

Inizia con una piccola pratica supportata da evidenze reali, come una convenzione di registrazione specifica del progetto o una checklist di revisione. Evita di scrivere regole generali come "scrivi codice migliore", a meno che tu non possa aggiungere contesto, modalità di errore, esempi concreti di evidenze e requisiti di validazione.

## Primo buon esito

Dopo che un flusso di lavoro a valle ha provato il documento, importa un esito anche se nulla è cambiato. Gli esiti `rejected`, `failed`, `partial` e `no_op` sono utili perché impediscono a BPJ di presentare una pratica sovrageneralizzata come dimostrata.

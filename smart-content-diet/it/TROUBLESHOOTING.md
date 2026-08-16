<!-- doc-provenance: AKDB:plugins/SmartContentDiet/architecture.md; docs/architecture/plugins/SmartContentDiet/product-facts.yml; reconciled 2026-07-16 -->
# Risoluzione dei problemi

## Ho abilitato il plugin ma non lo vedo

Aprire **Tools → Content Tools → Smart Content Diet**. Se la voce di menu manca, verificare in *Modifica → Plugin* che il plugin sia abilitato e che l'editor sia stato riavviato.

## Una scheda prevista (Preset / Governance / Ridondanza) non è visibile

La visibilità delle schede dipende dal ruolo. **Preset** e **Governance** appaiono per **Ingegnere / Producer** (modalità avanzata); **Ridondanza** appare solo quando è registrato un provider di similarità esterno. Modificare il ruolo/livello di spiegazione in **Impostazioni** o nel selettore di pubblico nell'intestazione.

## La scansione restituisce poco o nulla

**Quick Safe** usa solo il percorso registro/metadati (nessun caricamento asset), quindi alcuni risultati richiedono un passaggio più pesante. Portare la profondità nell'intestazione su **Full** (carica asset) o **Deep** (metriche approfondite materiali/mesh) ed eseguire di nuovo.

## "Esegui prima la scansione" / risultati o ottimizzazioni vuoti

I risultati e le azioni di ottimizzazione richiedono una scansione completata. Eseguire prima una scansione dall'intestazione, quindi aprire **Risultati** o **Ottimizza**.

## L'applicazione è bloccata o richiede approvazione

Le azioni di modifica richiedono un'approvazione per impostazione predefinita e devono essere eseguite in un workspace con backup, sotto controllo versione e monouso. Confermare il backup/controllo versione, quindi approvare l'azione. Le correzioni distruttive richiedono inoltre un consenso esplicito (`allow_destructive: true` sulla rotta pertinente).

## Dove si trovano i report di applicazione?

```text
Saved/SmartContentDiet/OptimizationQueue/<timestamp>/
```

## Una rotta cross-plugin mostra "disponibile ma plugin non caricato"

È un comportamento previsto e sicuro: SCD non richiede mai obbligatoriamente un plugin peer. Le rotte che fanno riferimento a un altro plugin (ad es. un'acquisizione di similarità IIS) vengono segnalate come *disponibili ma plugin non caricato* quando quel peer è assente, mentre ogni funzionalità solo SCD rimane disponibile.

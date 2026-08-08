---
lang: it
title: LightweightDummyActorSystem Troubleshooting
audience: [end_user]
owner_ref: plugin:LightweightDummyActorSystem
applies_to:
  component: LightweightDummyActorSystem
symptom: RegisterSubject fails or QueryReadiness returns a non-Ready status with issues.
recovery:
  steps:
    - Confirm the plugin is enabled under Edit > Plugins and restart the editor
    - Re-read the matching troubleshooting entry and apply the documented fix
    - Re-run the quick start smoke check
version:
  since: "1.0"
---
# Risoluzione dei problemi

Formato: Sintomo → Causa → Soluzione.

## 0. L'ho abilitato ma non è successo nulla

**Sintomo:** Dopo aver abilitato `LightweightDummyActorSystem` e riavviato, non appaiono attori dummy e nessun flusso di lavoro del prodotto Tiny Tools viene eseguito automaticamente.  
**Causa:** LDAS è un pacchetto API/servizio. I soggetti si registrano tramite `ULDASWorldSubsystem`; nulla viene generato automaticamente senza un profilo e una chiamata di registrazione.  
**Soluzione:** Creare un'attività dati `ULDASRepresentationProfile` ed eseguire l'esempio di lavoro di registrazione + `QueryReadiness` in [QUICKSTART.md](QUICKSTART.md).

## 1. `RegisterSubject` restituisce false

**Sintomo:** La registrazione fallisce per un nuovo ID soggetto.  
**Causa:** ID soggetto non valido o duplicato, o descrittore/profilo rifiutati dal registro del sottosistema.  
**Soluzione:** Verificare che i campi di `FLDASSubjectId` siano completi e univoci; confermare che l'attività del profilo sia caricata; riprovare dopo `UnregisterSubject` se si sta sostituendo.

## 2. Lo stato di prontezza non è Ready

**Sintomo:** `QueryReadiness` restituisce `Warning` o uno stato di blocco con problemi.  
**Causa:** I fornitori di prontezza richiesti non hanno funzionato, oppure gli input delle policy (distanza/cool-down) non sono soddisfatti.  
**Soluzione:** Esaminare gli avvisi/problemi in `FLDASReadinessReport`; regolare le distanze, il cool-down o i `RequiredReadinessProviders` in `ULDASRepresentationProfile`; risolvere i guasti dei fornitori prima di promuovere.

## 3. La promozione fallisce in modalità chiusa (fail-closed)

**Sintomo:** `RequestPromotion` non avanza la rappresentazione quando `bFailClosedOnPromotionFailure` è true.  
**Causa:** Il profilo richiede il comportamento fail-closed in caso di fallimento della promozione.  
**Soluzione:** Risolvere prima il sottostante guasto della prontezza/policy. Impostare su false `bFailClosedOnPromotionFailure` solo quando è accettabile un fallimento morbido intenzionale.

## 4. Promozione in runtime rifiutata

**Sintomo:** Le richieste di promozione non hanno effetto mentre la demozione funziona ancora.  
**Causa:** `bAllowRuntimePromotion` è false sul profilo.  
**Soluzione:** Abilitare `bAllowRuntimePromotion` su `ULDASRepresentationProfile` quando si desidera la promozione in runtime.

## 5. L'ispettore dell'editor non mostra soggetti

**Sintomo:** L'interfaccia utente dell'ispettore è vuota dopo la modalità PIE o il lavoro nel mondo dell'editor.  
**Causa:** I soggetti non sono mai stati registrati sul sottosistema di quel mondo, oppure viene ispezionato il contesto del mondo errato.  
**Soluzione:** Confermare la registrazione rispetto allo stesso `UWorld` che l'ispettore osserva; registrare nuovamente dopo il ricaricamento della mappa.

## 6. Il commandlet di validazione segnala errori di contratto

**Sintomo:** `ULDASValidateContractsCommandlet` termina con dei riscontri.  
**Causa:** Disallineamenti tra profilo/descrittore/contratto nei contenuti del progetto.  
**Soluzione:** Leggere l'output del commandlet, correggere le attività nominate ed eseguire nuovamente la validazione.

## 7. Ci si aspetta i bridge WarCollection / Lightning / UCM

**Sintomo:** Le API adapter opzionali sembrano mancanti.  
**Causa:** Questi bridge sono specifici per la destinazione e non fanno parte di MVP 1+2+3.  
**Soluzione:** Utilizzare solo le API core fornite. Considerare gli adapter come integrazioni opzionali future.

## Documenti correlati

- [QUICKSTART.md](QUICKSTART.md)
- [UserManual.md](UserManual.md)
- [SettingsReference.md](SettingsReference.md)
- [FAQ.md](FAQ.md)

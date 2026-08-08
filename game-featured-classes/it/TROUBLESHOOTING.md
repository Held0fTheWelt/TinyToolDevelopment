---
lang: it
title: GameFeaturedClasses Troubleshooting
audience: [end_user]
owner_ref: plugin:GameFeaturedClasses
applies_to:
  component: GameFeaturedClasses
symptom: Buyer expects a GameFeature workbench or featured classes that are not shipped in 1.0.1.
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

**Sintomo:** Dopo aver abilitato `GameFeaturedClasses` e riavviato, non appare il menu Tiny Tools, né nuovi asset nel Content Browser, né l'interfaccia utente della workbench.  
**Causa:** La versione `1.0.1` distribuisce solo lo scheletro del modulo runtime. Le classi featured e le superfici dell'editor non sono ancora disponibili.  
**Soluzione:** Conferma che il plugin sia abilitato in **Modifica → Plugin**, quindi verifica che il modulo `GameFeaturedClasses` venga caricato (vedi [QUICKSTART.md](QUICKSTART.md)). Non aspettarti un menu di prodotto finché un pacchetto successivo non lo distribuirà.

## 1. Ricerca di un menu GameFeature Workbench mancante

**Sintomo:** Non appare alcuna voce Tiny Tools / workbench dopo aver abilitato il plugin.  
**Causa:** La versione 1.0.1 distribuisce solo lo scheletro del modulo runtime; le superfici della workbench dell'editor non sono ancora disponibili.  
**Soluzione:** Utilizza il plugin esclusivamente come confine di modulo. Non aspettarti l'interfaccia utente della workbench finché un pacchetto successivo non la distribuirà esplicitamente.

## 2. Nessuna classe featured nel Content Browser

**Sintomo:** L'abilitazione del plugin non aggiunge asset di classi di gioco.  
**Causa:** Il pacchetto non include contenuti di classi featured o set di funzionalità.  
**Soluzione:** Mantieni le classi del progetto nei tuoi moduli; considera la distribuzione delle classi featured come lavoro futuro del pacchetto.

## 3. Il plugin non appare sotto Modifica → Plugin

**Sintomo:** La ricerca di `GameFeaturedClasses` non restituisce risultati.  
**Causa:** Il plugin non è stato copiato nella cartella Plugins del progetto o del motore, oppure il descrittore è stato filtrato.  
**Soluzione:** Conferma che `GameFeaturedClasses.uplugin` esista sotto l'albero `Plugins` del progetto (o nella cartella Plugins del motore), quindi riavvia l'editor.

## 4. Il modulo non riesce a caricarsi su un motore non supportato

**Sintomo:** L'abilitazione ha successo nell'interfaccia utente, ma il modulo runtime fallisce durante la compilazione/il caricamento.  
**Causa:** Versione del motore al di fuori della matrice 5.4–5.8 confezionata o discrepanza dei binari.  
**Soluzione:** Utilizza un branch del motore supportato corrispondente alla build Fab, oppure ricompila dal sorgente su tale motore.

## 5. Aspettativa di LightweightDummyActorSystem o PIO come dipendenza obbligatoria

**Sintomo:** Le guide di configurazione di altri prodotti implicano che GFC richieda LDAS/UCM/PIO.  
**Causa:** Quelle integrazioni sono un'architettura target opzionale, non requisiti runtime per lo scheletro.  
**Soluzione:** Abilita solo `GameFeaturedClasses` per il controllo fumetto dello scheletro. Aggiungi i peer successivamente solo quando esiste un'integrazione distribuita.

## 6. Dov'è la documentazione online?

**Sintomo:** Il DocsURL di Fab / descrittore dovrebbe risolvere a una pagina del browser.  
**Causa:** Le landing page online si trovano al di fuori del pacchetto Fab.  
**Soluzione:** Apri `https://docs.tiny-tool-development.com/game-featured-classes/` (DocsURL del descrittore) o utilizza l'insieme `Documentation/` incluso nel pacchetto distribuito con questo plugin.

## Documenti correlati

- [QUICKSTART.md](QUICKSTART.md)
- [UserManual.md](UserManual.md)
- [FAQ.md](FAQ.md)
- [SettingsReference.md](SettingsReference.md)

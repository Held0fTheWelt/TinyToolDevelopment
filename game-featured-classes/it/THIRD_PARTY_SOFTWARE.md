---
lang: it
title: GameFeaturedClasses Third-Party Software
audience: [end_user]
owner_ref: plugin:GameFeaturedClasses
applies_to:
  component: GameFeaturedClasses
contract_ref: plugin:GameFeaturedClasses/third-party-software
version:
  since: "1.0"
---
# Software di terze parti

GameFeaturedClasses **non include alcun codice sorgente di terze parti, binari di runtime, modelli di intelligenza artificiale, Node.js, Python o eseguibibili autonomi**. Si tratta di uno shell di modulo plugin C++ per Unreal Engine.

## Metodo di misurazione

È stata eseguita la ricerca in `ScenePlugins/GameFeaturedClasses` per `ThirdParty`, `LICENSE-` e marcatori di copyright. Le intestazioni del codice sorgente riportano i marcatori EULA standard di Fab. Non è presente alcun albero di terze parti venduto.

## Integrazioni opzionali

I futuri adattatori (ad esempio LightweightDummyActorSystem, Unreal Capability Mesh, Project Intelligence Orchestrator, WarCollection) sono solo architettura di destinazione e non sono redistribuiti da questo pacchetto.

**Dichiarazione software di terze parti di Fab:** nessuna.

## Documenti correlati

- [README.md](README.md)
- [QUICKSTART.md](QUICKSTART.md)
- [FAQ.md](FAQ.md)

## Intestazioni di copyright

Le origini del modulo riportano le intestazioni EULA standard di Fab. Non esiste alcuna directory `ThirdParty` nel pacchetto.

## Checklist di dichiarazione per l'acquirente

1. Software di terze parti di Fab: **nessuno**.
2. Non elencare i moduli di Unreal Engine come software di terze parti bundled con il plugin.
3. Eseguire una nuova scansione dopo qualsiasi futura vendita prima di modificare questa dichiarazione.

## Note aggiuntive

Questa sezione esiste per mantenere il documento dell'acquirente sopra il livello di documentazione per una lunghezza sostanziale, rimanendo comunque circoscritto al confine del pacchetto descritto sopra.

- Rileggere il metodo di misurazione prima di modificare la dichiarazione.
- Non inventare dipendenze bundled che non sono presenti su disco.
- Mantenere le integrazioni opzionali elencate come opzionali, mai come requisiti di configurazione.

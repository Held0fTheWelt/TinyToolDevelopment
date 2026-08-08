---
lang: it
title: EditorExtensionBase Third-Party Software
audience: [end_user]
owner_ref: plugin:EditorExtensionBase
applies_to:
  component: EditorExtensionBase
contract_ref: plugin:EditorExtensionBase/third-party-software
version:
  since: "1.0"
---
# Software di terze parti

Editor Extension Base **non include alcun codice sorgente di terze parti, binari di runtime, modelli di intelligenza artificiale, Node.js, Python o eseguibili autonomi**. Si tratta di un plugin Unreal Engine in C++ basato sui moduli dell'Editor di Unreal e sulle Utility di scripting dell'editor.

## Metodo di misurazione

È stata eseguita la ricerca in `GovernanceDevelopmentPlugins/EditorExtensionBase` per `ThirdParty`, `LICENSE-` e marcatori di copyright. Le intestazioni dei file identificano la EULA di Tiny Tool Development / Fab. Non è presente alcun albero di terze parti venduto.

## Dipendenze del motore (non incluse)

| Dipendenza | Inclusa? | Note |
| --- | --- | --- |
| Moduli dell'editor di Unreal Engine | No | Forniti dall'installazione del motore. |
| Utility di scripting dell'editor | No | Abilitate tramite la voce `Plugins` del file `.uplugin`; plugin di proprietà di Epic. |

## Integrazioni opzionali

I plugin di funzionalità possono dipendere da Editor Extension Base per widget condivisi. Tali consumatori sono pacchetti separati e non vengono ridistribuiti qui.

**Dichiarazione software di terze parti di Fab:** nessuna.

## Documenti correlati

- [README.md](README.md)
- [QUICKSTART.md](QUICKSTART.md)
- [FAQ.md](FAQ.md)

## Intestazioni di copyright

Le sorgenti dell'editor e del runtime utilizzano le intestazioni della EULA Standard di Tiny Tool Development / Fab. Non sono stati trovati file di licenza aggiuntivi nella directory `ThirdParty`.

## Checklist di dichiarazione per l'acquirente

1. Dichiarare **nessun** software di terze parti incluso per Fab.
2. Editor Scripting Utilities rimane una dipendenza del plugin del motore Epic, non un albero di terze parti venduto.
3. Ripetere la ricerca dopo eventuali modifiche future alla vendita di librerie prima di aggiornare questo file.

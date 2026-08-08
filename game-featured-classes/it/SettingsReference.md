---
lang: it
title: GameFeaturedClasses Settings Reference
audience: [end_user]
owner_ref: plugin:GameFeaturedClasses
applies_to:
  component: GameFeaturedClasses
contract_ref: plugin:GameFeaturedClasses/module-shell-settings
version:
  since: "1.0"
---
# Riferimento alle impostazioni

GameFeaturedClasses 1.0.1 **non** include DeveloperSettings, oggetti di configurazione `.ini` o descrittori di classi in evidenza modificabili. Il modulo runtime non espone alcuna superficie di impostazioni `UPROPERTY` oltre all'interfaccia del modulo vuoto.

## Superfici fornite

| Nome | Tipo | Valore predefinito | Effetto |
| --- | --- | --- | --- |
| Abilitazione del plugin | Interfaccia utente Editor Plugins | disabilitato fino all'attivazione da parte dell'acquirente | Carica il modulo runtime `GameFeaturedClasses`. |
| `FGameFeaturedClassesModule::StartupModule` | hook del modulo | invocato dal motore | Avvio del modulo; nessuna impostazione da parte dell'acquirente. |
| `FGameFeaturedClassesModule::ShutdownModule` | hook del modulo | invocato dal motore | Arresto del modulo; nessuna impostazione da parte dell'acquirente. |

## Non ancora disponibili

| Superficie di impostazione attesa | Stato |
| --- | --- |
| Asset descrittori di classi in evidenza | non ancora disponibile |
| Asset set di funzionalità | non ancora disponibile |
| Impostazioni di registro / risoluzione | non ancora disponibile |
| Preferenze dell'area di lavoro dell'editor | non ancora disponibile |
| `UGameFeaturedClassesSettings` DeveloperSettings | non ancora disponibile |
| `Config/DefaultGameFeaturedClasses.ini` | non fornito |

Non vengono inventate righe di impostazioni. Quando le versioni successive del pacchetto aggiungeranno campi reali `UPROPERTY` / DeveloperSettings, questo riferimento dovrà essere aggiornato dalla sorgente nella stessa modifica.

## Documenti correlati

- [UserManual.md](UserManual.md) — confine attuale vs target.
- [QUICKSTART.md](QUICKSTART.md) — verifica rapida di abilitazione.
- [FAQ.md](FAQ.md)

## Metadati di impacchettamento (non impostazioni runtime)

Il descrittore `.uplugin` contiene `Version` / `VersionName` per l'impacchettamento. Questi campi sono metadati del plugin, non DeveloperSettings runtime, e non devono essere modificati casualmente dalle flussi di lavoro dei documenti dell'acquirente.

## Regola di aggiornamento

Qualsiasi futura riga di impostazioni in questo file deve citare il percorso dell'intestazione e il nome della proprietà dalla sorgente nella stessa modifica della documentazione.

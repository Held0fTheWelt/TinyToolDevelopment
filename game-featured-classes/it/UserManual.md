# Manuale Utente

GameFeaturedClasses fornisce attualmente un guscio di plugin runtime leggero per classi di gameplay in evidenza specifiche del progetto.

## Comportamento del Pacchetto Attuale

| Area | Stato nella 1.0.1 |
| --- | --- |
| Modulo runtime (`GameFeaturedClasses`) | Rilasciato — solo avvio/arresto. |
| Descrittore / impacchettamento / icona / changelog | Rilasciato. |
| Classi di gameplay in evidenza | non ancora disponibili |
| Azioni Game Feature / asset set di funzionalità | non ancora disponibili |
| Registro runtime / confine interfaccia | non ancora disponibile |
| Banco di lavoro editor / riparazione / report di verifica | non ancora disponibile |
| Percorsi di automazione Tiny Tools | non ancora disponibile |

<!-- image slot: gfc-module-shell -->

## Mappa Sorgente

- `Source/GameFeaturedClasses/GameFeaturedClasses.Build.cs` — dipendenze del modulo.
- `Source/GameFeaturedClasses/Public/GameFeaturedClasses.h` — interfaccia `FGameFeaturedClassesModule`.
- `Source/GameFeaturedClasses/Private/GameFeaturedClasses.cpp` — avvio e arresto.

## Come Utilizzare il Guscio Oggi

1. Abilita il plugin (vedi [QUICKSTART.md](QUICKSTART.md)).
2. Mantieni le classi in evidenza specifiche del progetto nei tuoi moduli fino a quando questo pacchetto non le rilascerà.
3. Non documentare o dipendere dai menu del banco di lavoro che non sono presenti in questa build.

## Architettura Target (informativa, non rilasciata)

L'architettura interna del prodotto descrive un futuro GameFeature Workbench premium dove gli autori dichiarano classi in evidenza e set di funzionalità, le azioni a livello di mondo le registrano, i consumatori le risolvono attraverso un confine registro/interfaccia, e i manutentori scansionano un grafo delle funzionalità, visualizzano riparazioni governate ed esportano report di verifica. Tale comportamento è **solo specificato per il target** e non deve essere considerato come funzionalità disponibile per l'acquirente nella 1.0.1.

## Autarchia

Il guscio del modulo si carica autonomamente. Le future integrazioni opzionali con LightweightDummyActorSystem, Unreal Capability Mesh o Project Intelligence Orchestrator non sono requisiti di configurazione per questo pacchetto.

## Documenti Correlati

- [QUICKSTART.md](QUICKSTART.md)
- [SettingsReference.md](SettingsReference.md)
- [FAQ.md](FAQ.md)
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md)
- [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md)

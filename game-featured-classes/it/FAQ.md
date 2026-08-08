# FAQ

## GameFeaturedClasses include classi di gameplay?

No. La versione 1.0.1 è un guscio di plugin runtime leggero con descrittore, confine del modulo, metadati di impacchettamento, icona e changelog. Il comportamento premium di GameFeature Workbench è specificato per il target, ma non è ancora implementato in questo pacchetto.

## È richiesto un altro plugin Tiny Tool?

No. Il guscio del modulo corrente si carica autonomamente. Le integrazioni future con LightweightDummyActorSystem, Unreal Capability Mesh o Project Intelligence Orchestrator sono architetture target opzionali, non un requisito runtime per questo pacchetto.

## Quali versioni del motore sono supportate?

La matrice di rilascio impaccettato mira a Unreal Engine 5.4 fino a 5.8 (descrittore `EngineVersion` 5.4.0 su questo branch).

## Include software di terze parti o servizi esterni?

No. Il pacchetto non include software di terze parti e non richiede un account, un provider di AI o un runtime esterno. Vedi [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md).

## Dove posso ottenere supporto?

Utilizza `mailto:support@tiny-tool-development.com` (descrittore `SupportURL`) o il link di supporto nella pagina del prodotto Fab.

## Perché non c'è un pannello delle impostazioni?

La versione 1.0.1 non espone DeveloperSettings né descrittori di classi in evidenza. Vedi [SettingsReference.md](SettingsReference.md).

## Posso inserire le classi in evidenza del mio progetto all'interno di questa cartella del plugin?

Non per la distribuzione come contenuto GFC nella versione 1.0.1. Mantieni le classi di gameplay del progetto nei tuoi moduli fino a quando un pacchetto successivo non distribuirà esplicitamente le asset delle classi in evidenza.

## Come verifico che il guscio sia stato caricato?

Abilita il plugin, riavvia l'editor e conferma che il modulo runtime `GameFeaturedClasses` sia presente. Vedi l'esempio pratico in [QUICKSTART.md](QUICKSTART.md).

## Dove si trova la documentazione online?

https://docs.tiny-tool-development.com/game-featured-classes/

# Documentazione di GameFeaturedClasses

GameFeaturedClasses è un guscio di plugin runtime leggero per classi di gameplay in evidenza specifiche del progetto. La versione `1.0.1` include il descrittore, i metadati di impacchettamento, l'icona, il changelog e un confine del modulo runtime (`StartupModule` / `ShutdownModule`).

Destinatari: team che necessitano del confine del pacchetto GFC in un progetto attuale, mentre le classi in evidenza e il premium GameFeature Workbench rimangono l'architettura target (non ancora disponibili in questo pacchetto).

## Pacchetto corrente

- Il modulo runtime `GameFeaturedClasses` viene caricato dopo l'abilitazione e il riavvio.
- Non sono ancora incluse asset di classi di gameplay in evidenza, azioni Game Feature, registro o workbench dell'editor.
- Non è richiesto alcun altro plugin Tiny Tool per il guscio.

## Iniziare

1. Abilita il plugin — vedi l'esempio pratico in [QUICKSTART.md](QUICKSTART.md) (verifica di base del modulo).
2. Leggi [UserManual.md](UserManual.md) per il confine corrente rispetto a quello target.
3. Utilizza [TROUBLESHOOTING.md](TROUBLESHOOTING.md) quando un menu del workbench è atteso ma mancante.

## File correlati

- [../README.md](../README.md) — panoramica del prodotto.
- [../CHANGELOG.md](../CHANGELOG.md) — cronologia delle release.
- [SettingsReference.md](SettingsReference.md) · [FAQ.md](FAQ.md) · [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md)

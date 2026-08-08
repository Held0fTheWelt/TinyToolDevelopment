---
lang: it
title: GameFeaturedClasses Quick Start
audience: [end_user]
owner_ref: plugin:GameFeaturedClasses
applies_to:
  component: GameFeaturedClasses
preconditions:
  - Unreal Engine project open with the plugin package available
  - Edit > Plugins can enable GameFeaturedClasses
expected_result:
  text: GameFeaturedClasses runtime module is enabled and loads after editor restart.
version:
  since: "1.0"
---
# Avvio rapido

Questa guida installa e abilita **GameFeaturedClasses** e verifica che il modulo runtime venga caricato. La versione `1.0.1` è un **guscio di modulo**: include il descrittore, i metadati di pacchettizzazione, l'icona e il changelog. Non include ancora classi di gioco, azioni Game Feature o una postazione di lavoro per l'editor.

## Cosa avrai dopo questa guida

Il plugin abilitato nel tuo progetto, con il modulo runtime `GameFeaturedClasses` presente nell'elenco dei moduli dopo il riavvio dell'editor.

## Requisiti

- Unreal Engine 5.4–5.8 (matrice delle versioni pacchettizzate).
- Non è richiesto alcun altro plugin Tiny Tool per il guscio.
- Nessun software di terze parti, account o runtime esterno. Vedi [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md).

## 1. Installa e abilita

1. Ottieni **GameFeaturedClasses** da Fab e aggiungilo al progetto (o installalo nella directory Plugins dell'engine).
2. Apri **Modifica → Plugin**, cerca **GameFeaturedClasses**, abilitalo e riavvia quando richiesto.

## 2. Conferma il confine del modulo

Dopo il riavvio, verifica che il modulo runtime sia caricato (Registro output / gestore moduli). L'interfaccia del modulo pubblico è `FGameFeaturedClassesModule` in `Source/GameFeaturedClasses/Public/GameFeaturedClasses.h` con solo `StartupModule` / `ShutdownModule`.

## 3. Esempio pratico: verifica di base del guscio

1. Crea o apri un progetto su Unreal Engine 5.4+.
2. Abilita il plugin come descritto sopra e riavvia.
3. Nel Registro output, filtra per i messaggi di avvio del modulo di `GameFeaturedClasses` dopo il caricamento.

In questa versione del pacchetto non è presente un'interfaccia utente per il registro delle classi in evidenza né un'azione Game Feature di esempio da eseguire. È previsto che il richiamo di menu della postazione di lavoro inesistenti fallisca, poiché queste superfici non sono **ancora disponibili**.

## Risultato atteso

- Il plugin viene visualizzato come abilitato sotto **Modifica → Plugin**.
- Il modulo runtime si avvia e si arresta senza richiedere plugin peer Tiny Tool.
- Non compaiono asset di classi in evidenza di gioco nel Content Browser da questo pacchetto (nessuno viene fornito).

## Prossimi passi

- Leggi [UserManual.md](UserManual.md) per il confine attuale rispetto a quello target.
- Leggi [FAQ.md](FAQ.md) per domande sull'ambito.
- Considera il comportamento della postazione di lavoro GameFeature premium come architettura target fino a quando un pacchetto successivo non fornirà quelle classi e superfici dell'editor.

## Confini da ricordare

- Non aggiungere classi di gioco del progetto in questa cartella del plugin aspettandoti che vengano distribuite come contenuto GFC in 1.0.1.
- Non abilitare plugin peer esclusivamente per "sbloccare" una postazione di lavoro che non è ancora pacchettizzata.
- Quando una versione successiva fornirà classi in evidenza, aggiorna questa guida di avvio rapido con i nomi reali delle classi e un esempio pratico tratto da quella release.

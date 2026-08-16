<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/LogLevelEditor/architecture.md -->
# Guida rapida

Questa guida ti accompagna dall'installazione a un **risultato concreto**: il livello di dettaglio (verbosity) di una categoria di log modificato e salvato come sovrascrittura permanente che sopravvive ai riavvii dell'editor. Log Level Editor funziona in modo autonomo — non è richiesto alcun altro plugin.

## Cosa otterrai dopo questa guida

Lo strumento aperto con l'elenco delle categorie di log del tuo progetto, la verbosità di una categoria modificata e quella sovrascrittura salvata in modo permanente nel DataAsset del plugin.

## Requisiti

- Editor di Unreal Engine 5.
- Nessun software di terze parti, account o runtime aggiuntivo richiesto. Vedi [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md).

## 1. Installazione e abilitazione

1. Aggiungi **LogLevelEditor** dalla tua libreria Fab al progetto (o installalo nel motore).
2. Apri **Edit → Plugins**, abilita **LogLevelEditor** e riavvia l'editor quando richiesto.

## 2. Aprire lo strumento (Primo risultato)

1. Apri **Tools → Log Tools → Log Level Editor**. Si aprirà una scheda ancorabile che esegue la scansione del codice sorgente del progetto (e dei plugin del progetto) alla ricerca delle categorie di log.
2. Ogni riga mostra il **nome della categoria** (es. `LogTemp`), il **valore predefinito rilevato**, il **livello attuale** e il **percorso sorgente** se disponibile.

Ora puoi vedere ogni categoria di log individuata e la sua verbosità attuale.

## 3. Un esempio pratico: Modificare la verbosità di una categoria

1. Utilizza la casella di ricerca per trovare `LogTemp`.
2. Fai clic sul pulsante della verbosità **Warning** in quella riga.

**Risultato atteso:** il plugin esegue il comando di console di Unreal corrispondente, la riga si aggiorna a `Warning` e la modifica viene scritta come sovrascrittura permanente nel DataAsset del plugin (in modo da essere riapplicata al successivo avvio dell'editor).

3. Per annullare: seleziona il **valore predefinito rilevato** per la riga. Quando il valore selezionato corrisponde al valore predefinito rilevato, il plugin rimuove automaticamente la sovrascrittura permanente per mantenere il DataAsset concentrato sulle reali sovrascritture.

## 4. Dove si trovano le sovrascritture

Le sovrascritture permanenti sono memorizzate nel `ULogLevelDataAsset` configurato (impostato tramite **LogLevelDataAsset** nelle impostazioni). Le sovrascritture salvate vengono riapplicate durante l'avvio dell'editor non appena il motore può accettare comandi di console.

## 5. Impostazioni

Apri le impostazioni del plugin (Project/Editor settings → Log Level Editor) per controllare:

- `LogLevelDataAsset`, `bAutoSaveLogLevelDataAsset`
- `bShowToolbarButton`
- `bAlsoListEnginePluginChannels`, `bAlsoListEngineSourceChannels` (le scansioni del motore sono dispendiose)
- `LogChannelsToHide`, `LogChannelsToHideTemporary`

Vedi [SettingsReference.md](SettingsReference.md).

## 6. Passaggi successivi

- Flusso di lavoro completo (nascondimento temporaneo vs permanente, flusso di lavoro di team, applicazione all'avvio):
  [UserManual.md](UserManual.md).
- Problemi: [TROUBLESHOOTING.md](TROUBLESHOOTING.md) e [FAQ.md](FAQ.md).

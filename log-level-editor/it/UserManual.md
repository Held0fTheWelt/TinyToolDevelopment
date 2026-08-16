<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/LogLevelEditor/architecture.md -->
# Manuale utente

Questo manuale spiega il flusso di lavoro quotidiano nell'editor per LogLevelEditor.

## Installazione

1. Aggiungi il plugin alla cartella `Plugins` del tuo progetto o installalo tramite Fab.
2. Abilita **LogLevelEditor** in **Edit > Plugins**.
3. Riavvia l'editor se Unreal lo richiede.
4. Conferma che il contenuto del plugin sia visibile se desideri ispezionare il DataAsset predefinito.

## Aprire lo strumento

Apri LogLevelEditor da **Tools → Log Tools → Log Level Editor** o tramite la scorciatoia opzionale sulla barra degli strumenti. Il plugin si apre come una scheda ancorabile nell'editor in modo da rimanere integrato nell'ambiente di lavoro.

## Prima scansione

All'apertura dello strumento, viene eseguita una scansione nei percorsi configurati per individuare le categorie di log.

Per impostazione predefinita si concentra su:

- File sorgente del progetto.
- File sorgente dei plugin del progetto.

Impostazioni opzionali possono includere:

- File sorgente dei plugin del motore.
- File sorgente del motore.

Le scansioni del motore possono richiedere tempo. Abilitale solo quando hai realmente bisogno delle categorie del motore nella dashboard.

## Lettura dell'elenco

Ogni riga rappresenta una categoria di log.

Campi importanti:

- Nome categoria: il nome della categoria di log in Unreal, ad esempio `LogTemp`.
- Valore predefinito rilevato: la verbosità predefinita dedotta dalla macro di dichiarazione/definizione quando possibile.
- Livello attuale: la verbosità attualmente segnalata da Unreal per la categoria registrata. Se Unreal non può ancora segnalarla, la riga mostra `Unavailable`. Dopo la scansione iniziale, questo valore viene aggiornato regolarmente dallo stato a runtime di Unreal.
- Percorso sorgente: la posizione in cui lo scanner ha trovato la categoria, quando disponibile.

## Modificare la verbosità

1. Trova la categoria utilizzando la ricerca o i filtri.
2. Scegli un valore di verbosità dai pulsanti dedicati nella riga.
3. Il plugin esegue il comando di console di Unreal.
4. La riga e il DataAsset vengono aggiornati solo dopo che l'esecuzione del comando è andata a buon fine.

Scelte comuni:

- `Warning`: riduce il rumore mantenendo comunque i problemi importanti.
- `Log`: standard comune per le uscite normali.
- `Verbose`: utile per la diagnosi.
- `VeryVerbose`: output molto dettagliato e di solito temporaneo.
- `NoLogging`: silenzia una categoria per quanto consentito da Unreal.

## Ripristinare i valori predefiniti

Quando la verbosità selezionata corrisponde al valore predefinito rilevato, il plugin rimuove la sovrascrittura permanente per quella categoria. In questo modo il DataAsset rimane concentrato sulle reali sovrascritture.

Se non è stato rilevato alcun valore predefinito, considera la riga come informativa e ripristinala manualmente al valore atteso dal progetto.

## Sovrascritture permanenti

I valori permanenti vengono memorizzati nel `ULogLevelDataAsset` configurato.

Flusso di lavoro consigliato:

1. Mantieni le sovrascritture intenzionali valide per l'intero progetto nel DataAsset predefinito.
2. Sottoponi l'asset al controllo versione solo se tali sovrascritture rappresentano la direttiva del team.
3. Evita di salvare il rumore temporaneo di debug nel controllo codice sorgente condiviso.
4. Utilizza le impostazioni di nascondimento temporaneo per la concentrazione locale sull'interfaccia utente.

## Applicazione all'avvio

Le sovrascritture salvate vengono riapplicate durante l'avvio dell'editor. Il modulo attende fino a quando il motore non è pronto ad accettare comandi di console e riprova un piccolo numero di volte se l'avvio è troppo precoce.

## Nascondere le categorie

Elenco di nascondimento permanente:

- Memorizzato nella configurazione.
- Utile per le categorie che dovrebbero apparire raramente nello strumento.

Elenco di nascondimento temporaneo:

- Memorizzato in modo effimero.
- Utile per la concentrazione locale durante una singola sessione dell'editor.
- Non viene scritto nella configurazione.

## Impostazioni

Apri le impostazioni del plugin nella sezione delle impostazioni dell'editor/progetto.

Impostazioni chiave:

- `LogLevelDataAsset`: DataAsset utilizzato per memorizzare le sovrascritture permanenti.
- `bAutoSaveLogLevelDataAsset`: salva automaticamente l'asset dopo modifiche intenzionali.
- `bShowToolbarButton`: mostra o nasconde la scorciatoia sulla barra degli strumenti.
- `bAlsoListEnginePluginChannels`: include le categorie dei plugin del motore nelle scansioni.
- `bAlsoListEngineSourceChannels`: include le categorie del codice sorgente del motore nelle scansioni.
- `LogChannelsToHide`: categorie nascoste in modo permanente.
- `LogChannelsToHideTemporary`: categorie nascoste solo per la sessione corrente.

## Flusso di lavoro di team consigliato

Per l'utilizzo in team:

1. Mantieni il DataAsset predefinito nel controllo codice sorgente.
2. Salva solo sovrascritture stabili stabilite come regola di progetto.
3. Non inviare modifiche locali di nascondimento temporaneo.
4. Documenta i profili di debug nella wiki del tuo progetto.

## Rimuovere il plugin

Prima di rimuovere il plugin:

1. Ripristina qualsiasi modifica temporanea di verbosità.
2. Rimuovi o ignora il DataAsset del plugin se non viene più utilizzato.
3. Disabilita il plugin e riavvia l'editor.

Il plugin non modifica le dichiarazioni nel codice sorgente delle categorie di log, quindi la rimozione non richiede interventi di pulizia in C++.

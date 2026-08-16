<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/LogLevelEditor/architecture.md -->
# FAQ (Domande frequenti)

## LogLevelEditor modifica le mie dichiarazioni di categoria di log in C++?

No. Non riscrive il codice sorgente. Individua le categorie e utilizza il sistema di comandi di console di Unreal per modificare la verbosità attiva.

## Le modifiche sono permanenti?

Solo le sovrascritture intenzionali memorizzate nel `ULogLevelDataAsset` configurato sono permanenti. Le modifiche alla console a runtime senza un aggiornamento del DataAsset sono temporanee.

## Perché una categoria è scomparsa dall'elenco?

Potrebbe essere nascosta dall'elenco di nascondimento permanente, dall'elenco temporaneo, filtrata dal testo di ricerca o esclusa dall'ambito della scansione corrente.

## Perché manca un livello predefinito?

Lo scanner riconosce le macro comuni di Unreal. Se un progetto utilizza macro personalizzate o formattazioni insolite, la categoria può comunque essere trovata ma il livello predefinito potrebbe non essere dedotto.

## Posso includere le categorie di log del motore?

Sì. Abilita la scansione dei plugin e/o del codice sorgente del motore nelle impostazioni.

## Funziona nei giochi pacchettizzati?

No. LogLevelEditor è un plugin per l'editor destinato ai flussi di lavoro di sviluppo.

## Posso condividere una configurazione di log con il mio team?

Sì. Salva le sovrascritture intenzionali nel DataAsset e sottoponilo al controllo versione con il tuo progetto.

## Perché il plugin riprova ad applicare i livelli salvati all'avvio?

I moduli dell'editor di Unreal possono avviarsi prima che il motore sia pronto a elaborare i comandi di console. La logica di rientro evita di perdere le sovrascritture salvate all'avvio.

## Cosa succede se un comando di console fallisce?

L'interfaccia utente e il DataAsset non vengono aggiornati come se il comando fosse andato a buon fine. Il fallimento viene registrato nei log.

## Posso silenziare completamente una categoria?

Utilizza `NoLogging`, ma ricorda che si applicano comunque le regole sulla verbosità in fase di compilazione e a runtime di Unreal.

## Supporta nomi di verbosità personalizzati?

No. Supporta i nomi di verbosità standard di Unreal.

## Il DataAsset è obbligatorio?

L'interfaccia utente può ispezionare e applicare modifiche a runtime, ma la riapplicazione automatica all'avvio richiede un DataAsset configurato.

## Il plugin può rilevare categorie dai plugin?

Sì. I plugin del progetto fanno parte del normale percorso di scansione. I plugin del motore sono opzionali.

## È sicuro per il controllo codice sorgente?

Sì, se usato con intenzione. L'elemento principale condiviso è il DataAsset contenente le sovrascritture permanenti.

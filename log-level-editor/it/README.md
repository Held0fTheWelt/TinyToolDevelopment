<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/LogLevelEditor/architecture.md -->
# Documentazione di LogLevelEditor

LogLevelEditor è un plugin per l'editor di Unreal Engine progettato per rilevare le categorie di log e modificarne il livello di dettaglio (verbosity) da una dashboard dedicata nell'editor. Aiuta i team a ridurre i log rumorosi durante il lavoro quotidiano, ad alzare temporaneamente i canali di diagnostica durante il debugging e a salvare le sovrascritture intenzionali in un DataAsset.

Le azioni principali sono **Scan**, **Set Verbosity** e **Hide Category**.

Questa cartella contiene la documentazione completa fornita con il plugin.

## Inizia qui

- [BUYER_GUIDE.md](BUYER_GUIDE.md): panoramica per gli acquirenti, idoneità e valore pratico.
- [UserManual.md](UserManual.md): flusso di lavoro completo nell'editor dalla configurazione all'applicazione delle sovrascritture.
- [FAQ.md](FAQ.md): domande e risposte pronte per Fab.

## Riferimento

- [SettingsReference.md](SettingsReference.md): tutte le impostazioni, il comportamento predefinito e la configurazione consigliata.
- [TechnicalOverview.md](TechnicalOverview.md): architettura e comportamento a runtime per i manutentori.
- [CodeDocumentation.md](CodeDocumentation.md): struttura del codice, contratti e punti di estensione.
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md): problemi comuni e soluzioni.
- [ReleaseChecklist.md](ReleaseChecklist.md): passaggi di validazione prima di pubblicare un aggiornamento su Fab.

## Asset inclusi

- `../Readme.pdf`: file di testo informativo classico.
- `../LogLevelEditor_Changelog.txt`: note di rilascio.
- `../Content/DA_LogLevelVerbosity.uasset`: DataAsset predefinito utilizzato per le sovrascritture permanenti di verbosity.
- `../Content/Map_Tutorial_LogLevelEditor.umap`: contenuto di tutorial e dimostrazione.

## Flusso di lavoro rapido

1. Abilita il plugin e riavvia l'editor quando richiesto.
2. Apri la scheda Log Level Editor da **Tools → Log Tools → Log Level Editor** o tramite la scorciatoia opzionale sulla barra degli strumenti.
3. Lascia che lo scanner rilevi le categorie di log del progetto e dei plugin.
4. Utilizza le impostazioni di ricerca e nascondimento per concentrarti sui canali importanti.
5. Modifica la verbosity di una categoria dai pulsanti dedicati nella riga corrispondente.
6. Salva le sovrascritture nel `ULogLevelDataAsset` configurato quando la modifica è intenzionale.
7. Ripristina una categoria al suo valore predefinito rilevato selezionando di nuovo quel valore predefinito.

## Cosa modifica lo strumento

Il plugin applica comandi di console di Unreal nella forma:

```text
Log <CategoryName> <VerbosityName>
```

Non modifica la dichiarazione nel codice sorgente di una categoria di log. Le modifiche permanenti vengono memorizzate nel DataAsset configurato e riapplicate dal modulo dell'editor non appena il motore è pronto ad accettare comandi di console.

## Nomi di verbosità supportati

L'helper di verbosità condiviso supporta i livelli di log standard di Unreal:

- `NoLogging`
- `Fatal`
- `Error`
- `Warning`
- `Display`
- `Log`
- `Verbose`
- `VeryVerbose`

L'editor utilizza intenzionalmente gli stessi nomi mostrati dalla configurazione dei log di Unreal in modo che gli utenti possano associare le modifiche dell'interfaccia ai comandi di console.

## Modello di sicurezza

LogLevelEditor evita di mostrare stati non corretti all'utente:

- L'etichetta `Current` viene letta dallo stato a runtime di Unreal quando la categoria può essere interrogata.
- Lo stato dell'interfaccia utente viene aggiornato solo dopo che un comando di console è andato a buon fine.
- Le sovrascritture permanenti vengono rimosse quando il valore selezionato corrisponde al livello predefinito rilevato.
- Le impostazioni di nascondimento temporaneo rimangono effimere e non vengono scritte nella configurazione.
- Le sovrascritture salvate vengono applicate con una logica di rientro per categoria all'avvio, poiché l'editor non è sempre pronto per i comandi di console al momento dell'avvio del modulo.

## Usi tipici

- Ridurre il rumore di un plugin molto prolisso mantenendo comunque il plugin abilitato.
- Alzare temporaneamente un sottosistema di gameplay, build, asset o editor al livello `Verbose`.
- Ripristinare impostazioni predefinite pulite dopo aver indagato su un problema.
- Condividere un DataAsset di team con sovrascritture di verbosity intenzionali per l'intero progetto.
- Mantenere le categorie del motore e del progetto separate tramite le impostazioni per garantire scansioni veloci e rilevanti.

## Limitazioni importanti

- Le categorie di log devono esistere nel codice sorgente o essere già registrate dai moduli a runtime/editor.
- La scansione del codice sorgente può dedurre i valori predefiniti solo dalle macro standard di Unreal.
- Il codice a runtime può comunque modificare la verbosità dopo che l'editor ha applicato le sovrascritture salvate.
- Le build finali (Shipping builds) non sono influite da questo plugin per l'editor.

## Nota legale

LogLevelEditor è uno strumento di produttività per l'editor. Non modifica la semantica di registrazione dei log di Unreal Engine, il codice sorgente del motore o i termini di licenza del progetto.

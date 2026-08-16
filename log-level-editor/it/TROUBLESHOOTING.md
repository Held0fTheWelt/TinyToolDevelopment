<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/LogLevelEditor/architecture.md -->
# Risoluzione dei problemi

## Lo strumento non mostra la mia categoria

Verifica:

- La categoria è dichiarata o definita in un percorso sorgente sottoposto a scansione.
- L'estensione del file è `.h`, `.hpp`, `.cpp` o `.inl`.
- La categoria non è nascosta dalle impostazioni di nascondimento permanente o temporaneo.
- La scansione è completata o è ancora in corso.
- La macro è una delle forme di macro per i log di Unreal supportate.

## Il livello predefinito manca o è errato

Lo scanner può dedurre i valori predefiniti solo da argomenti di macro riconoscibili. Alcune categorie potrebbero comunque essere elencate con un valore predefinito vuoto o di fallback.

Soluzioni:

- Utilizza la formattazione macro standard di Unreal quando possibile.
- Aggiungi una sovrascrittura permanente se hai bisogno di un valore noto.

## La modifica della verbosità non ha alcun effetto

Possibili cause:

- La categoria non è ancora stata registrata da un modulo caricato.
- Unreal ha rifiutato il comando di console.
- Il codice a runtime ha modificato nuovamente la categoria dopo il comando dell'editor.

Controlla il log di output per i messaggi `LogLogLevelEditor`.

## La verbosità salvata non viene applicata all'avvio

Verifica:

- `LogLevelDataAsset` punti a un asset valido.
- Il DataAsset contenga voci di sovrascrittura.
- La categoria esista nel momento in cui viene eseguita la riapplicazione all'avvio.

## Il mio DataAsset contiene troppe voci

Il DataAsset dovrebbe contenere solo sovrascritture intenzionali. Ripristina le righe ai valori predefiniti rilevati per rimuovere le voci non necessarie.

## I valori nascosti temporaneamente sono riapparsi

I valori nascosti temporaneamente sono effimeri e non persistono tra le sessioni. Utilizza `LogChannelsToHide` per il nascondimento permanente.

## La scansione richiede troppo tempo

Disabilita la scansione dei plugin e del codice sorgente del motore a meno che non sia strettamente necessaria.

Configurazione normale consigliata:

```text
bAlsoListEnginePluginChannels = false
bAlsoListEngineSourceChannels = false
```

## Il log di output è ancora troppo rumoroso

Alcuni sistemi possono registrare log attraverso più categorie. Cerca i prefissi delle categorie correlate e regola ciascun canale rilevante.

## Il plugin si apre ma non mostra le sovrascritture del DataAsset

Lo scanner e il DataAsset sono separati:

- Scanner: individua le categorie disponibili.
- DataAsset: memorizza le sovrascritture permanenti.

Un DataAsset vuoto è del tutto normale se non sono state configurate sovrascritture permanenti.

## Il controllo codice sorgente mostra continuamente che il DataAsset è modificato

Hai probabilmente modificato le sovrascritture permanenti. Mantieni le modifiche come regola di team oppure ripristina le righe ai valori predefiniti prima di inviare i file.

## Informazioni di supporto da raccogliere

Quando segnali un problema, includi:

- Versione di Unreal Engine.
- Versione del plugin.
- Se la scansione dei plugin/sorgenti del motore è abilitata.
- Esempio di dichiarazione della categoria di log.
- Output rilevante relativo a `LogLogLevelEditor`.

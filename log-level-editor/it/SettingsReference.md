<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/LogLevelEditor/architecture.md -->
# Riferimento delle impostazioni

LogLevelEditor memorizza la sua configurazione in `ULogLevelEditor_Settings`.

## Oggetto impostazioni

File sorgente:

```text
Source/LogLevelEditor/Public/LogLevelEditor_Settings.h
```

Ambito di configurazione:

```text
EditorPerProjectUserSettings
```

Ciò significa che molte impostazioni sono legate all'utente o all'editor anziché essere impostazioni per l'esecuzione del gioco.

## LogLevelDataAsset

Tipo:

```text
TSoftObjectPtr<ULogLevelDataAsset>
```

Predefinito:

```text
/LogLevelEditor/DA_LogLevelVerbosity.DA_LogLevelVerbosity
```

Scopo:

- Memorizza le sovrascritture permanenti di verbosity per ciascuna categoria.
- Viene caricato dal modulo all'avvio.
- Viene aggiornato dal widget dopo il successo di un comando.

Raccomandazione:

- Utilizza l'asset predefinito fornito per piccoli progetti.
- Crea una copia specifica per il progetto se desideri una gestione rigorosa nel controllo codice sorgente.

## bAutoSaveLogLevelDataAsset

Predefinito:

```text
true
```

Scopo:

- Salva il DataAsset dopo le modifiche alle sovrascritture permanenti.
- Riduce il rischio che un utente dimentichi di salvare l'asset dopo aver modificato la politica dei log.

## bShowToolbarButton

Predefinito:

```text
true
```

Scopo:

- Mostra la scorciatoia per Log Level Editor nella barra degli strumenti del Level Editor.
- La voce di menu **Tools → Log Tools → Log Level Editor** rimane disponibile anche quando questa scorciatoia è nascosta.

## bAlsoListEnginePluginChannels

Predefinito:

```text
false
```

Scopo:

- Include le directory del codice sorgente dei plugin del motore nello scanner.

Compromesso:

- Risultati più completi.
- Tempo di scansione più lungo e più categorie nell'interfaccia utente.

## bAlsoListEngineSourceChannels

Predefinito:

```text
false
```

Scopo:

- Include le directory del codice sorgente del motore nello scanner.

Compromesso:

- Visibilità molto ampia.
- Scansioni potenzialmente molto più grandi.

## bTemporaryHideLogLevels

Predefinito:

```text
false
```

Scopo:

- Abilita l'elenco di nascondimento valido solo per la sessione corrente.

Memorizzazione:

- Effimera (Transient).
- Non salvata nella configurazione.

## LogChannelsToHideTemporary

Scopo:

- Nomi delle categorie nascoste solo per la sessione corrente dell'editor.

Esempio:

```text
LogTemp
LogSlate
LogDerivedDataCache
```

## LogChannelsToHide

Scopo:

- Nomi delle categorie nascoste in modo permanente tra le sessioni.

Raccomandazione:

- Utilizzare con moderazione. Il nascondimento permanente può rendere più difficile individuare log rilevanti in seguito.

## Configurazione di base consigliata

Per la maggior parte dei progetti:

```text
bAutoSaveLogLevelDataAsset = true
bAlsoListEnginePluginChannels = false
bAlsoListEngineSourceChannels = false
bTemporaryHideLogLevels = false
```

<!-- doc-provenance: AKDB:plugins/LLMStore/architecture.md; docs/architecture/plugins/LLMStore/product-facts.yml; reconciled 2026-06-20 -->
# Risoluzione dei problemi

Questa guida elenca i problemi comuni relativi a configurazione, runtime, interfaccia utente, criteri e build di LLM Store.

## La voce di menu LLM Store è mancante

Verifica:

- Il plugin è abilitato.
- L'editor è stato riavviato dopo l'abilitazione del plugin.
- Il modulo `LLMStoreEditor` è stato compilato.
- Stai eseguendo Unreal Editor e non un build runtime cucinato (cooked).

Posizione prevista:

```text
Tiny Tools -> LLM Store
```

## Il provider non è raggiungibile

Verifica:

- il provider è abilitato
- l'URL di base è corretto
- il server locale è in esecuzione
- il firewall o il proxy non bloccano la richiesta
- il timeout è sufficientemente lungo
- il tipo di provider corrisponde al server

Valori predefiniti locali comuni:

| Provider | Predefinito |
| --- | --- |
| `ollama` | `http://127.0.0.1:11434` |
| `llamacpp` | `http://127.0.0.1:8080` |
| `lmstudio` | `http://127.0.0.1:1234/v1` |
| `vllm` | `http://127.0.0.1:8000/v1` |
| `tgi` | `http://127.0.0.1:8080/v1` |

Usa prima `Test Provider`, quindi `Test Model`, infine `Test Route`.

## La route non si risolve

Verifica:

- il `TaskKind` della route è scritto esattamente come richiesto
- la route è abilitata
- il modello preferito esiste
- il modello è abilitato
- il modello fa riferimento a un provider esistente
- il provider è abilitato
- la chiave cloud esiste se richiesta
- il criterio della route consente il tipo di provider
- la modalità di build/runtime non rifiuta la route

Se `bUseMock` è abilitato, verifica che `MockModelId` esista.

## Chiave API mancante

Le chiavi non vengono salvate in `Config/LLMStore.json`.

Usa una delle seguenti soluzioni:

- campo della chiave del provider nell'editor
- sovrascrittura tramite variabile d'ambiente
- backend dei segreti configurato

Formato della variabile d'ambiente:

```text
LLMSTORE_<PROVIDER_ID>_KEY
```

Esempio:

```text
ProviderId: openai-main
Variable: LLMSTORE_OPENAI_MAIN_KEY
```

## La variabile d'ambiente viene ignorata

Verifica:

- il nome della variabile usa l'ID del provider normalizzato
- il processo dell'editor è stato riavviato dopo l'impostazione
- la variabile è visibile al processo che avvia Unreal
- non vi sono spazi nascosti nel valore

Su Windows, le modifiche alle variabili d'ambiente tramite le impostazioni di sistema richiedono spesso il riavvio del launcher o del terminale.

## Windows Credential Manager non funziona

Verifica:

- esecuzione su Windows
- `Advapi32` è collegato dalla build del plugin
- il nome della destinazione delle credenziali corrisponde al nome del segreto del provider generato
- l'account utente dispone dei permessi
- l'ID del provider non è cambiato

In caso di dubbi, imposta una variabile d'ambiente temporanea per confermare il resto della configurazione del provider.

## macOS Keychain non funziona

Verifica:

- il comando `security` è disponibile
- il portachiavi è sbloccato
- il processo dispone dei permessi per leggere l'elemento
- il nome del segreto generato corrisponde al valore previsto

## Il backend 1Password non funziona

Verifica:

- la CLI `op` è installata
- `op whoami` ha successo nello stesso contesto di terminale
- `Vault` è impostato o `SecretBackend.Meta` contiene un riferimento `op://...` completo
- la sovrascrittura specifica per il provider punta all'elemento e al campo corretti

## Il backend Azure Key Vault non funziona

Verifica:

- la CLI `az` è installata
- `az account show` ha successo
- `Vault` è il nome corretto del Key Vault
- l'identità corrente dispone dei permessi per get/set/delete sui segreti
- la sovrascrittura specifica per il provider corrisponde al nome del segreto

## Il provider cloud fallisce ma il provider locale funziona

Verifica:

- la chiave API è presente
- l'URL di base corrisponde alla documentazione del provider
- il nome del modello del provider è corretto
- l'account ha accesso al modello
- la richiesta non è bloccata da criteri dell'organizzazione
- il criterio di costo della route non rifiuta la richiesta

Ispeziona la salute del provider e l'ultimo evento di audit.

## llama.cpp non risponde

Verifica:

- `llama-server` è in esecuzione
- host e porta corrispondono a `BaseUrl`
- il server espone un endpoint compatibile con OpenAI
- il modello è caricato
- il timeout della richiesta è sufficientemente lungo

Avvio tipico:

```text
llama-server -m C:\Models\model.gguf --host 127.0.0.1 --port 8080
```

Provider:

```text
Type: llamacpp
BaseUrl: http://127.0.0.1:8080
```

## Ollama non risponde

Verifica:

```text
ollama list
ollama serve
```

Assicurati che il modello in `FLLMModelConfig.Name` esista in Ollama.

## Il JSON strutturato non è valido

Verifica:

- la route utilizza un modello adatto agli output strutturati
- `bStructured` è impostato nel modello se il flusso di lavoro lo richiede
- `FLLMStructuredOutputSpec.bRequireJson` è vero solo quando necessario
- lo schema è un JSON valido
- il prompt non richiede testo normale attorno al JSON

Alcuni modelli locali richiedono prompt più rigidi per produrre JSON valido.

## Le chiamate agli strumenti (Tool Calls) sono mancanti

Verifica:

- il provider supporta la chiamata agli strumenti
- `FLLMToolSpec.ParametersJsonSchema` è valido
- il modello supporta gli strumenti
- l'adattatore del provider mappa le specifiche degli strumenti nel formato di rete del provider

## Lo streaming emette un solo blocco

Alcuni provider non supportano lo streaming nativo o l'adattatore corrente potrebbe analizzare solo risposte complete. Questo è consentito. L'API di streaming emette comunque un blocco finale consentendo agli utenti di utilizzare un unico percorso di codice.

## I costi risultano pari a zero

Verifica:

- le regole di costo esistono
- il tipo di provider corrisponde alla regola
- l'ID del modello corrisponde alla regola oppure l'ID del modello nella regola è vuoto
- il provider segnala l'utilizzo o la stima dei token è abilitata
- la richiesta non è stata servita interamente da un modello locale a costo zero

## Il report dei costi sembra troppo elevato

Verifica:

- le unità di costo sono per 1000 token
- i valori di input e output non sono stati invertiti
- la valuta è coerente
- la regola specifica del modello non è duplicata da una regola più generale
- i dati di utilizzo del provider non sono già espressi in un'altra unità

## L'agente non è installato

Verifica:

- la CLI o l'IDE è installato
- il comando dello strumento è presente nel `PATH`
- Unreal è stato avviato da un ambiente che possa vedere il comando dello strumento
- la verifica dello stato dell'adattatore conosce il nome corretto del comando

Usa la finestra di dialogo `Authenticate...` per le istruzioni di configurazione.

## L'autenticazione dell'agente non funziona

Prova a:

1. Fare clic su `Copy Command`.
2. Eseguire il comando in un normale terminale.
3. Completare l'accesso.
4. Riavviare Unreal o aggiornare lo stato dell'agente.

LLM Store non memorizza le credenziali. Si limita a mostrare e copiare il comando di accesso esterno.

## L'agente rifiuta la scrittura dei file

Verifica `FLLMAgentRequest`:

```text
bAllowFileWrites
bAllowShellExecution
bRequireDiffPreview
```

Gli adattatori devono rifiutare le scritture o i comandi di shell quando la richiesta non li consente.

## Il criterio per la distribuzione (Shipping) fallisce

Verifica:

- `BuildRules` per `Shipping`
- i criteri delle route
- l'utilizzo dei provider cloud
- la disponibilità di fallback locali o mock
- gli elenchi consenti dei provider

Esegui il commandlet localmente:

```text
<UnrealEditorCommand> Project.uproject -run=LLMStoreCIPolicy -Config=Shipping -Unattended -NoSplash -NoSound
```

## Lo stato delle impostazioni non è chiaro

Apri la scheda `Status`. Riassume provider, modelli, route, blocchi, avvisi, chiavi mancanti e inventario.

Se lo stato appare obsoleto:

- fai clic su ricarica se disponibile
- chiudi e riapri la scheda
- riavvia l'editor
- verifica se `Config/LLMStore.json` è stato modificato manualmente

## La build fallisce perché Live Coding è attivo

In Unreal, Live Coding può bloccare una build esterna completa mentre l'editor è in esecuzione. Chiudi l'editor o disabilita Live Coding prima di eseguire una build completa da riga di comando.

Questo non influisce sull'uso normale dell'interfaccia utente, ma può bloccare build di tipo CI o la validazione UHT.

## Riferimenti utili

- Prima configurazione: [QUICKSTART.md](QUICKSTART.md)
- Dettagli provider: [ProviderReference.md](ProviderReference.md)
- Criteri delle route: [RoutePolicyReference.md](RoutePolicyReference.md)
- Segreti: [SECRET_BACKENDS.md](SECRET_BACKENDS.md)
- Costi: [COST_TRACKING.md](COST_TRACKING.md)
- Integrazione: [INTEGRATION.md](INTEGRATION.md)
- CI: [CommandletAndCI.md](CommandletAndCI.md)

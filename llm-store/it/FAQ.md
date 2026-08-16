<!-- doc-provenance: AKDB:plugins/LLMStore/architecture.md; docs/architecture/plugins/LLMStore/product-facts.yml; reconciled 2026-06-20 -->
# FAQ (Domande frequenti)

## Esiste una configurazione guidata per la prima volta?

Sì. La scheda **Setup** include una scheda **Quick-Start**. Può creare con un solo clic uno stack completo mock, Ollama o cloud OpenAI/Anthropic (provider, modello e route `default`), eseguire un test di connessione e aggiornare l'idoneità. Non sovrascrive i provider già creati né una route `default` configurata da te.

## LLM Store è un chatbot?

No. LLM Store è un'infrastruttura per provider, modelli, route, criteri, segreti, tracciamento dei costi e agenti. Un chatbot o un assistente agli asset può utilizzare LLM Store, ma rappresenta uno strumento separato.

## Perché dovrei usare le route anziché i nomi dei modelli?

Le route mantengono stabile il codice delle funzionalità. Se uno strumento chiama `docs.summarize`, il team potrà in seguito passare da Ollama a llama.cpp o a OpenAI senza dover modificare il codice dello strumento.

## Posso eseguire tutto in locale?

Sì. Usa provider come `ollama`, `llamacpp`, `lmstudio`, `vllm`, `tgi` o `mock`, imposta i criteri su solo locale e blocca il cloud tramite le regole di build.

## llama.cpp è supportato?

Sì. Il tipo di provider `llamacpp` è destinato ai server llama.cpp locali. L'URL di base tipica è:

```text
http://localhost:8080
```

## Le chiavi API vengono memorizzate nel file di progetto?

No. `Config/LLMStore.json` memorizza provider, modelli, route e criteri, ma non le chiavi. Le chiavi si trovano nello store dei segreti o nelle variabili d'ambiente.

## Quale backend dei segreti dovrei usare?

Per la configurazione di un singolo sviluppatore, `EncryptedFile` è semplice. Per i team, Windows Credential Manager, macOS Keychain, 1Password o Azure Key Vault sono solitamente la scelta migliore.

## Blueprint può fare tutto ciò che fa il C++?

I punti di integrazione principali rivolti all'utente dispongono di versioni Blueprint. Ciò include provider, embedding, criteri, test, provider di contesto, agenti e funzioni della facciata del sottosistema.

## Posso connettere Codex, Claude o Cursor?

Sì, tramite gli add-on per agenti. Lo store può unificare stato, guida all'autenticazione ed esecuzione dell'attività. L'integrazione concreta dello strumento rimane un adattatore e deve rispettare le regole di sicurezza.

## LLM Store esegue automaticamente comandi di shell?

Solo quando un adattatore dell'agente implementa esplicitamente l'esecuzione e i flag della richiesta lo consentono. `bAllowShellExecution`, `bAllowFileWrites` e `bRequireDiffPreview` comunicano i requisiti di sicurezza del chiamante.

## Quanto è accurato il tracciamento dei costi?

L'accuratezza dipende dai dati di utilizzo del provider e dalle `CostRules`. Se un provider non restituisce il conteggio dei token, lo store stima i token. La fatturazione del provider rimane la fonte primaria di verità per le fatture.

## Posso assegnare costi ai modelli locali?

Sì. I modelli locali possono avere costo `0` oppure utilizzare valori contabili interni come il costo approssimativo della GPU per 1000 token.

## Cosa non appartiene direttamente a LLM Store?

Strumenti per funzionalità concrete come la spiegazione degli asset, la documentazione dei Blueprint, la revisione della denominazione o la RAG di progetto dovrebbero utilizzare LLM Store, ma risiedono solitamente in plugin o add-on separati. LLM Store rimane autonomo.

## Cosa succede se un provider è offline?

Lo store aggiorna lo stato di salute del provider, può tentare fallback e registra gli errori nel log di audit. Le impostazioni del salvavita (circuit breaker) prevengono tentativi ripetuti costosi o bloccati.

## Posso usare LLM Store in CI?

Sì. Usa il commandlet `LLMStoreCIPolicy` e i test di automazione. Un esempio per GitHub Actions è incluso in `Documentation/CI`.

## Devo testare i provider cloud dal vivo?

Non sempre. Per la sicurezza del rilascio, test mock, validazione della configurazione e test di funzionamento (smoke test) manuali opzionali sui provider sono spesso sufficienti. I test su cloud devono essere eseguiti solo con segreti intenzionalmente configurati.

## Quali file dovrei inviare al repository (commit)?

Invia:

- `Config/LLMStore.json`
- preimpostazioni opzionali
- documentazione del team per le route di produzione

Non inviare:

- chiavi API
- file locali dei segreti
- file del registro dei costi se contengono dati operativi sensibili

## Posso esportare e importare configurazioni complete?

Sì. La scheda Governance può esportare la configurazione corrente in qualsiasi file JSON, validare un file JSON senza applicarlo e importare una configurazione JSON solo dopo che la validazione ha avuto successo. I file di configurazione esportati non includono chiavi API.

<!-- doc-provenance: AKDB:plugins/UnrealCapabilityMesh/architecture.md; docs/architecture/plugins/UnrealCapabilityMesh/product-facts.yml; reconciled 2026-07-19 -->
# Guida rapida

Questa guida ti accompagna da un'installazione pulita a un **risultato visibile e funzionante**: un inventario di funzionalità individuate e un percorso eseguito personalmente che restituisce una risposta JSON. Non sono richiesti codice né redazione di manifesti — il plugin include un profilo predefinito pronto all'uso.

## Cosa otterrai dopo questa guida

Il pannello di controllo aperto, il profilo incluso **Default Capability Mesh Profile** caricato, le funzionalità individuate e un percorso (`sample.echo.route.v1`) eseguito con una risposta JSON e un report salvato che puoi aprire.

## Requisiti

- Unreal Engine 5.4 o successivo.
- Piattaforma: Windows (Win64), Linux o Mac.
- Un **progetto** Unreal in cui abilitare il plugin. UCM è un plugin di editor C++: in un progetto C++ viene compilato al primo avvio dell'editor; in un progetto solo Blueprint, installalo per una versione del motore corrispondente (tramite la tua libreria Fab) affinché l'editor possa caricarne i moduli precompilati.
- Nessun software di terze parti, account, modello AI o runtime esterno richiesto. Consulta [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md).

## 1. Installa e abilita

1. Acquisisci **Unreal Capability Mesh** dalla tua libreria Fab e aggiungilo al tuo progetto (apparirà nella cartella `Plugins/` del progetto) oppure installalo nel motore.
2. Apri il tuo progetto. Nell'editor, vai su **Edit → Plugins**, cerca `Unreal Capability Mesh` e spunta **Enabled**.
3. Riavvia l'editor quando richiesto. (Per un progetto C++, lascialo compilare a questo primo avvio.)

UCM può funzionare senza una cartella di configurazione locale al progetto. Carica il profilo predefinito incluso e i profili locali dei plugin provider abilitati. Usa `Config/UnrealCapabilityMesh/` solo quando il progetto necessita intenzionalmente di override o percorsi composti di proprietà del progetto.

## 2. Ottieni il primo risultato

1. Apri il pannello di controllo: **Tools → Unreal Capability Mesh**.
2. Nella pagina **Overview** dovresti vedere il profilo attivo **"Default Capability Mesh Profile"**.
3. Fai clic su **Reload Setup**. UCM carica il profilo, valida la configurazione JSON, registra le definizioni ed esegue l'individuazione.
4. Apri la pagina **Capabilities** — ora vedi le funzionalità individuate (ad esempio `mesh.sample.echo`) con la relativa disponibilità ed effetti collaterali.
5. Apri la pagina **Diagnostics** — mostra i messaggi di validazione della configurazione e di individuazione derivanti dal ricaricamento. Un ricaricamento pulito indica che il plugin funziona.

Hai appena fatto funzionare il prodotto utilizzando esclusivamente ciò che è stato fornito nel pacchetto.

## 3. Un esempio pratico reale: Esegui un percorso

UCM include un percorso di esempio sicuro e in sola lettura, `sample.echo.route.v1`, che richiama un endpoint echo. Utilizzalo per eseguire il tuo primo percorso end-to-end.

1. Apri la pagina **Routes**.
2. Nel campo ID del percorso, inserisci:

   ```text
   sample.echo.route.v1
   ```

3. Fai clic su **Dry Run**. UCM pianifica il percorso e conferma che la funzionalità `mesh.sample.echo` è disponibile con effetti collaterali `read_only` e **nessuna approvazione richiesta**. Il report di esecuzione di prova (dry-run) è pulito.
4. Nel campo di input del percorso, inserisci questo JSON (questi sono i parametri attesi — un involucro di input del percorso il cui campo `request_json` contiene il tuo payload):

   ```json
   {
     "request_json": "{\"message\":\"hello\"}"
   }
   ```

5. Fai clic su **Execute**.

**Output atteso:** il percorso restituisce una risposta JSON echo nella forma `{"echo": { ... }}` e scrive un report di esecuzione del percorso. L'endpoint è la funzione inclusa `UCapabilityMeshTestInvoker::EchoJson`, che racchiude il payload della richiesta come `{"echo":<request>}`.

La pagina Routes contiene anche la colonna di approvazione **Route Catalog** per l'auto-approvazione automatica **SPERIMENTALE**. Lascia **Approve all at own risk** e tutti gli interruttori per singolo percorso disattivati per questa guida rapida. Servono solo per testare i percorsi soggetti ad approvazione sotto la propria responsabilità.

## 4. Dove risiedono i risultati

Tutti i file generati vengono scritti nella cartella `Saved/` del tuo progetto:

```text
Saved/UnrealCapabilityMesh/
  setup_validation_report.json     ← validazione del ricaricamento
  capability_registry.json         ← funzionalità registrate
  discovery_report.md              ← riepilogo di individuazione leggibile dall'utente
  compatibility_matrix.json        ← compatibilità funzionalità/endpoint
  route_reports/                   ← piani di esecuzione di prova (dry-run)
  route_execution_reports/         ← input e output dei percorsi eseguiti (il tuo risultato echo)
```

Apri `route_execution_reports/` per vedere la risposta del percorso appena eseguito.

## 5. Passaggi successivi

- Gestire il pannello e ogni funzione con i relativi parametri: [UserManual.md](UserManual.md).
- Ogni campo del profilo, criteri e percorsi di output: [SettingsReference.md](SettingsReference.md).
- Personalizzare la configurazione solo quando necessario: crea `<TuoProgetto>/Config/UnrealCapabilityMesh/project_profile.json` o copia i manifesti specifici che il progetto intende sovrascrivere, quindi fai di nuovo clic su **Reload Setup**. Lascia i manifesti del provider nei rispettivi plugin.
- Connettere un altro plugin: [INTEGRATION.md](INTEGRATION.md).
- Qualcosa non funziona? Consulta [TROUBLESHOOTING.md](TROUBLESHOOTING.md) e [FAQ.md](FAQ.md).

Quando Tiny Tool Execution Integration Bridge è abilitato, ricarica UCM prima che TTER individui i percorsi proiettati durante l'avvio dell'editor. Il **Reload Setup** manuale rimane l'azione normale dopo la modifica di un profilo o l'abilitazione di un provider.

---

> **Per i manutentori / compilazione da codice sorgente (non richiesta per utilizzare il plugin):** gli strumenti di validazione del repository sorgente sono riservati ai manutentori e **non** fanno parte del pacchetto Fab. Non sono necessari Python o controlli sui sorgenti per installare o utilizzare UCM.

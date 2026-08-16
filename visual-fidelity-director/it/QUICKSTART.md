<!-- doc-provenance: AKDB:plugins/VisualFidelityDirector/architecture.md; docs/architecture/plugins/VisualFidelityDirector/product-facts.yml; reconciled 2026-07-12 -->
# Guida rapida

Questa guida accompagna dall'installazione a un risultato concreto: il cockpit di Visual Fidelity Director aperto con una vista del profilo aggiornata e un confronto dei profili affiancato.

## Cosa si otterrà dopo questa guida

Il cockpit VFD aperto in Unreal Editor, il campionamento delle metriche live avviato, un asse di composizione esaminato con dettagli di variante e provenienza, e un confronto eseguito rispetto a un secondo profilo.

## Requisiti

- Unreal Engine 5.4 editor su Win64, Linux o Mac.
- Un progetto in grado di caricare i plugin dell'editor.
- Nessun software di terze parti, account, servizio IA o altro plugin Tiny Tool.

## 1. Installare e abilitare

1. Aggiungere **VisualFidelityDirector** dalla libreria Fab al progetto, oppure installarlo nell'engine.
2. Aprire **Modifica > Plugin**.
3. Cercare **Visual Fidelity Director**.
4. Abilitare il plugin e riavviare Unreal Editor quando richiesto.

Se si installa un pacchetto plugin solo codice sorgente in un progetto C++, lasciare che Unreal compili i moduli del progetto al successivo avvio dell'editor.

## 2. Aprire il Cockpit

1. Aprire **Tiny Tools > Visual Fidelity Director**.
2. Confermare che la pagina **Cockpit** sia attiva (predefinita).
3. Esaminare il banner di stato, il selettore di profili e la barra delle metriche.

Risultato atteso:

- Il titolo della scheda ancorabile è **Visual Fidelity Director**.
- La barra dei profili elenca i profili noti da `Saved/VisualFidelityDirector/profiles/` oltre al contesto integrato/di progetto.
- La barra delle metriche si riempie in diversi tick dell'editor (campionamento multi-frame) o mostra uno stato non disponibile esplicito.

## 3. Esempio pratico: Esaminare un asse

1. Fare clic su **Refresh** nella scheda azione del Cockpit.
2. Selezionare una qualsiasi striscia di asse di composizione (ad esempio **Anti-Aliasing** o **Upscaling**).
3. Nel cassetto dei dettagli dell'asse, esaminare:
   - il **percorso di ereditarietà** dal profilo radice al profilo attivo;
   - le righe di **provenienza** per le impostazioni compilate;
   - i **risultati locali al controllo** per quell'asse.
4. Modificare il menu a tendina **Variant** quando sono disponibili più varianti di pipeline. Le varianti non disponibili rimangono visibili ma disabilitate con le prove di compatibilità.

Risultato atteso:

- Gli aggiornamenti dei cursori dell'intento riflettono la variante selezionata.
- Provenienza e risultati si aggiornano per l'asse selezionato.
- Nessun file di progetto viene modificato finché non si utilizza l'applicazione governata o l'anteprima di applicazione di Expert Tools.

## 4. Esempio pratico: Confrontare due profili

1. Scorrere fino alla scheda **Profile Comparison** nella pagina Cockpit.
2. Scegliere un profilo da **Compare against** dal menu a tendina.
3. Leggere il riepilogo delle differenze per asse.

Risultato atteso:

- Gli assi divergenti sono elencati con dettagli a livello di impostazione.
- Gli assi corrispondenti non mostrano righe di differenza.
- Il confronto utilizza lo stesso comparatore runtime di `UVFDCockpitBlueprintLibrary::CompareFidelityProfiles`.

## 5. Opzionale: Snapshot di Expert Tools

1. Passare alla pagina **Expert Tools**.
2. Fare clic su **Export Snapshot**.

Risultato atteso:

- Esiste il file `Saved/VisualFidelityDirector/reports/<timestamp>/quality_snapshot.json`.
- Le copie più recenti appaiono in `Saved/VisualFidelityDirector/reports/`.

Questo percorso preserva il workflow di snapshot e ricette 1.x per gli utenti che preferiscono una revisione basata su report.

## 6. Opzionale: Applicazione permanente governata

Continuare solo se si intende scrivere file di configurazione del progetto.

1. Nella pagina Cockpit, fare clic su **Build Destinations** nel cassetto di applicazione.
2. Esaminare ogni riepilogo delle destinazioni (Scalability, ini renderer, Device Profiles).
3. Spuntare l'approvazione solo per le destinazioni che si accettano.
4. Fare clic su **Apply Approved**.

Risultato atteso:

- Backup con marca temporale e un manifesto di rollback nella cartella radice dei backup di configurazione VFD.
- Report di applicazione con i risultati della verifica.
- **Rollback** ripristina i file di backup se la verifica fallisce.

## 7. Dove si trovano gli output

```text
Saved/VisualFidelityDirector/profiles/
Saved/VisualFidelityDirector/reports/<timestamp>/
Saved/VisualFidelityDirector/recipes/
```

## 8. Passaggi successivi

- Elenco completo delle operazioni: [UserManual.md](UserManual.md)
- Controlli e funzioni Blueprint: [SettingsReference.md](SettingsReference.md)
- Problemi e soluzioni: [TROUBLESHOOTING.md](TROUBLESHOOTING.md)
- Risposte su compatibilità e sicurezza: [FAQ.md](FAQ.md)

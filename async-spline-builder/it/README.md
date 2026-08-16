<!-- doc-provenance: product-facts.yml reconciled 2026-07-15; source AKDB:plugins/AsyncSplineBuilder/architecture.md -->
# Documentazione di Async Spline Builder

Async Spline Builder genera mesh spline per strade, piste da corsa, tubi, rotaie, muri e oggetti collaterali senza causare blocchi prolungati dell'editor. Supporta build sincrone, batching asincrono nell'editor, batching asincrono in fase di runtime, piani di mesh per segmento, muri di contenimento opzionali, interruzioni di salto, muri di dislivello, asset di dati per punti spline e deformazione dell'altezza del paesaggio riservata all'editor con pittura additiva dei livelli.

Questa cartella contiene la documentazione fornita con il plugin.

## Inizia qui

- [BUYER_GUIDE.md](BUYER_GUIDE.md): panoramica a livello di prodotto, flussi di lavoro, punti di forza e limitazioni.
- [UserManual.md](UserManual.md): flusso di lavoro completo nell'editor dal primo posizionamento dell'actor fino alle rigenerazioni.
- [FAQ.md](FAQ.md): domande e risposte pronte per Fab.

## Riferimento

- [SettingsReference.md](SettingsReference.md): ogni impostazione importante dell'actor e la configurazione di base raccomandata.
- [LandscapeAndWalls.md](LandscapeAndWalls.md): allineamento, deformazione dell'altezza, muri di contenimento, interruzioni e muri di dislivello.
- [TechnicalOverview.md](TechnicalOverview.md): architettura e flusso di build a livello di manutentore.
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md): problemi comuni di configurazione, build, tracciamento e geometria.

Gli audit riservati ai manutentori, le note di completamento, i comandi di automazione, le note legacy e le checklist di rilascio possono esistere nel repository sorgente, ma sono esclusi dal pacchetto acquirente.

## Flusso di lavoro rapido

1. Abilitare il plugin e riavviare l'editor se richiesto.
2. Aprire **Tools > Track Tools > Async Spline Builder**.
3. Posizionare o selezionare un `ASplineGeneratingActor` dal pannello del flusso di lavoro.
4. Assegnare `MainMesh` nella sezione di configurazione del pannello.
5. Modificare i punti della `TrackSpline` nel viewport.
6. Utilizzare **Build Now** per una build immediata o **Rebuild** per il batching asincrono.
7. Utilizzare gli assistenti di segmento per creare righe per segmento prima di modifiche avanzate per segmento.
8. Opzionale: abilitare i muri di contenimento e configurare i tipi di oggetto di tracciamento nel pannello Details.
9. Opzionale: assegnare un paesaggio, eseguire **Deform Height**, quindi **Paint Layer** (richiede `PaintLayer` sull'actor) per la pittura additiva del peso.

## Caratteristiche principali

- Generazione di mesh per strade o piste lungo una spline.
- Track Shape Editor per la creazione nativa di punti di percorso/layout, con controlli designer per layout, ancore e segmenti.
- Validate Layout Connectors per verificare i metadati passivi dei connettori (`PitEntry`, `PitExit`, `Link`, `ServiceAccess` o personalizzati) prima di affidarsi alle relazioni di percorso.
- Apply Layout Connector per aggiungere o aggiornare record passivi di relazione di layout senza creare rami di mesh nascosti.
- Rigenerazioni asincrone nell'editor con `SegmentsPerTick`.
- Rigenerazioni asincrone in fase di runtime tramite una pompa timer al tick successivo.
- Selezione della mesh per segmento e pianificazione della lunghezza della mesh.
- Mesh aggiuntive di inizio, metà e fine per guardrail, barriere, recinzioni, tubi o mesh di dettaglio.
- Interruzioni di salto che sopprimono le mesh stradali e laterali.
- Regioni di dislivello e muri di dislivello procedurali tra livelli di altezza.
- Muri di contenimento procedurali che tracciano verso il basso fino al terreno o ad altri tipi di oggetto configurati.
- Pulizia dei componenti generati basata su tag, resistente a array obsoleti e rigenerazioni di costruzione.
- Salvataggio/caricamento dei punti spline tramite `USplinePointListAsset`.
- Deformazione dell'altezza del paesaggio riservata all'editor e pittura di livello globale additiva.
- Test di automazione per i comportamenti a più alto rischio.

## Posizione runtime supportata

Il modulo runtime contiene l'actor, la generazione delle mesh spline, la generazione dei muri di contenimento, la generazione dei muri di dislivello, l'accesso agli asset di dati e la pompa asincrona runtime.

Il modulo editor contiene il pannello del flusso di lavoro, la deformazione del paesaggio e la pittura dei livelli riservate all'editor, oltre agli assistenti di selezione dell'editor. I giochi pacchettizzati possono generare le mesh spline e i muri procedurali, ma le modifiche all'altezza/peso del paesaggio e il pannello del flusso di lavoro sono riservati all'editor.

## Pannello del flusso di lavoro dell'editor

La superficie principale dell'editor è **Tools > Track Tools > Async Spline Builder**. Raggruppa il flusso di lavoro comune nelle schede **Build**, **Segments** e **Terrain** per mantenere compatte le attività quotidiane senza nascondere lo stato di validazione.

Utilizzare il Track Shape Editor quando un percorso necessita di creazione nativa di punti/layout e utilizzare i controlli dei connettori di layout quando le corsie box, gli accessi di servizio o i percorsi alternativi necessitano di metadati di relazione espliciti.

Utilizzare il pannello per il lavoro quotidiano. Utilizzare il pannello Details di Unreal per campi grezzi avanzati come array di mesh aggiuntive per segmento, impostazioni dettagliate UV dei muri, array di oggetti di tracciamento, impostazioni di collisione personalizzate e campi sperimentali.

## Limitazioni importanti

- Paesaggio: deformazione dell'altezza più pittura del peso del livello **globale additiva** quando `PaintLayer` è impostato (`PaintLandscapeLayerNow` o pannello **Paint Layer**). La modalità di pittura sostituisci/cancella non è implementata.
- La deformazione del paesaggio è un'operazione puntuale nell'editor, non una fase automatica di ogni rigenerazione della pista.
- I paesaggi di produzione complessi richiedono comunque un QA manuale, specialmente per curve strette, terreni molto ripidi e impostazioni di muri misti per segmento.
- L'automazione asincrona runtime è coperta da un hook di test deterministico; una passe di integrazione completa nel mondo timer PIE è comunque raccomandata per le mappe di rilascio.

## Validazione

Per una passe di validazione del pacchetto locale, compilare il target editor per il progetto ed eseguire il gruppo di automazione AsyncSplineBuilder dagli strumenti di automazione di Unreal. Mantenere i percorsi dei comandi specifici per manutentori nelle note di rilascio locali anziché nel pacchetto acquirente spedito.

## Prima passe di produzione raccomandata

Utilizzare prima una breve spline di test aperta, poi un loop chiuso e infine la pista reale. Mantenere `bUseAsyncBuild` abilitato, iniziare con `SegmentsPerTick = 2` e aumentarlo solo dopo aver confermato la reattività dell'editor. Configurare i tipi di oggetto di tracciamento prima di abilitare l'allineamento o i muri di contenimento, poiché la validazione blocca intenzionalmente le build che altrimenti distruggerebbero la vecchia geometria senza produrre una sostituzione valida.

## Nota legale

Async Spline Builder è fornito secondo i termini di licenza inclusi con la distribuzione del prodotto. Il plugin non concede diritti su mesh, materiali, paesaggi o contenuti di terze parti utilizzati con le piste generate.

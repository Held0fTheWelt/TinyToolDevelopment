<!-- doc-provenance: product-facts.yml reconciled 2026-07-15; source AKDB:plugins/AsyncSplineBuilder/architecture.md -->
# Manuale utente

Questo manuale spiega come utilizzare Async Spline Builder in Unreal Editor e come si integrano le funzionalità principali.

## Scopo

Async Spline Builder crea componenti generati da una spline modificabile. L'output tipico è una strada o una pista composta da sezioni `USplineMeshComponent`, con opzionali mesh spline aggiuntive e mesh di muro procedurali.

L'actor può rigenerare in modo sincrono o a blocchi (batch). Il batching mantiene l'editor reattivo su piste lunghe ed è disponibile anche in fase di runtime tramite una pompa timer al tick successivo.

## Apertura e abilitazione

1. Aprire **Edit > Plugins**.
2. Abilitare **AsyncSplineBuilder**.
3. Riavviare l'editor se richiesto.
4. Aprire o creare un livello.
5. Aprire **Tools > Track Tools > Async Spline Builder**.

Il plugin contiene sia moduli runtime che editor. L'actor è pronto per il runtime; il pannello del flusso di lavoro e gli strumenti di deformazione del paesaggio sono riservati all'editor.

## Pannello del flusso di lavoro

Il pannello Async Spline Builder è il modo raccomandato per configurare tracciati normali. Evita di disperdere il flusso di lavoro comune tra diverse categorie Details.

Il pannello è organizzato in schede:

- **Build**: selezione dell'actor, configurazione mesh, convalida/build/rebuild/annulla, batching asincrono, loop chiuso, etichette di debug per punti o segmenti ed etichette di estremità dei connettori di layout opzionali.
- **Segments**: `TrackSplineData` per segmento, creazione di righe per segmento, interruzioni di salto e dislivelli.
- **Terrain**: allineamento al paesaggio, assegnazione paesaggio, impostazioni pittura livello, deformazione altezza, pittura livello additiva e muri di contenimento.

Utilizzare il pannello Details per array avanzati e impostazioni rare non duplicate nel pannello del flusso di lavoro.

## Configurazione di base dell'actor

1. Nel pannello del flusso di lavoro, premere **Create Actor** oppure selezionare un `ASplineGeneratingActor` esistente e premere **Use Selection**.
2. In **Setup**, assegnare `MainMesh`.
3. Opzionalmente assegnare `StartMesh` e `EndMesh`.
4. Spostare i punti spline nel viewport.
5. Premere **Validate**.
6. Premere **Build Now** o **Rebuild**.

`MainMesh` è obbligatorio. La validazione blocca le build senza di esso per evitare che la geometria generata esistente venga cancellata e sostituita con il nulla.

## Requisiti per la creazione delle mesh

Le mesh stradali dovrebbero:

- Ripetersi lungo l'asse X locale.
- Avere un'estensione Y coerente poiché i limiti della mesh vengono usati per ricavare la semi-larghezza stradale.
- Usare pivot coerenti.
- Evitare complessità di collisione nascoste a meno che la collisione non sia necessaria.

Se i limiti della mesh non sono rappresentativi, impostare `GroundWallSettings.TrackHalfWidth` manualmente.

## Modifica della spline

Utilizzare gli strumenti standard di modifica spline di Unreal. Campi utili:

- `bClosedLoop`: collega l'ultimo punto al primo punto.
- `SplinePointType`: controlla il comportamento di interpolazione dei punti.
- `SplineZOffset`: applica uno spostamento verticale al componente spline.
- `bShowPointNumbers`: mostra gli indici dei punti.
- `bShowSegmentNumbers`: mostra gli indici dei segmenti.
- `bShowSplineVisualizationWidth`: mostra una spline dell'editor più ampia.

I numeri dei punti e dei segmenti sono componenti di debug generati e vengono puliti dallo stesso sistema di tag usato per la geometria generata.

## Track Shape Editor

Aprire **Tools > Track Tools > Track Shape Editor** quando è necessaria una superficie di creazione multi-layout compatta invece di modificare solo i punti spline grezzi dell'actor. L'editor lavora su un documento nativo `track_shape.v1` e può applicare layout compilati principali, corsie box, alternativi o strade di servizio all'actor `ASplineGeneratingActor` selezionato.

La sezione **Designer Tools** fornisce i controlli di modifica quotidiani:

- aggiungere layout di corsia box, alternativi o strade di servizio
- duplicare o eliminare il layout non principale selezionato
- modificare il tipo di layout e lo stato di loop chiuso
- selezionare layout, ancora o segmento precedente o successivo
- modificare le coordinate X/Y dell'ancora selezionata
- aggiungere, inserire o eliminare ancore mantenendo un numero minimo valido di ancore
- aggiungere o eliminare segmenti espliciti, cambiare i segmenti selezionati tra linea e bezier, o ricostruire segmenti sequenziali per il layout selezionato

Il viewport supporta la selezione diretta delle ancore e il trascinamento. L'elenco layout e l'ispettore riflettono la stessa selezione, e la sezione JSON può ancora importare o esportare il documento sottostante per revisione o controllo versione.

Utilizzare **Validate** prima di applicare modifiche complesse. Utilizzare **Apply** solo dopo aver selezionato o creato l'actor di destinazione, poiché l'applicazione modifica lo stato di spline/layout modificabile dell'actor.

## Generazione

Utilizzare:

- **Build Now** / `BuildTrack`: build sincrona completa.
- **Rebuild** / `RebuildTrack`: asincrono se `bUseAsyncBuild` è vero, altrimenti sincrono.
- **Cancel** / `CancelAsyncBuild`: annulla una build asincrona attiva o in sospeso.

L'actor rigenera a partire da un piano calcolato `FTrackBuildPlan`. Il piano decide intervalli di segmenti, numero di pezzi, stato dei dislivelli, interruzioni di salto, mesh stradale selezionata e conteggio mesh aggiuntive prima dell'inizio della generazione.

## Generazione asincrona

Impostazioni:

- `bUseAsyncBuild`: abilita la build a blocchi.
- `SegmentsPerTick`: numero di pezzi generati di strada/mesh aggiuntiva elaborati per tick.
- `bAutoRebuildOnConstruction`: pianifica le rigenerazioni quando si verificano modifiche di costruzione.

I mondi dell'editor applicano un debouncing alle modifiche di costruzione prima di cancellare o preparare i componenti generati, mantenendo la geometria spline esistente modificabile mentre si trascinano i punti. I mondi runtime utilizzano una pompa timer al tick successivo. Entrambi i percorsi chiamano lo stesso generatore a livello di pezzo, garantendo un comportamento allineato senza lasciare che un lungo segmento di spline monopolizzi un frame.

## Dati per segmento

`TrackSplineData` configura ciascun segmento. Se sono presenti meno voci rispetto ai segmenti spline, l'indice `0` viene usato come fallback.

Campi importanti:

- `RoadMesh`: mesh stradale specifica per il segmento opzionale.
- `MeshInstances`: numero esatto di pezzi di mesh per il segmento.
- `RoadMeshLength`: lunghezza desiderata della copertura della mesh stradale.
- `SegmentLength`: spaziatura di riserva quando `RoadMeshLength` non è impostato.
- `ExtraMeshStart`, `ExtraMesh`, `ExtraMeshEnd`: mesh spline aggiuntive.
- `ExtraMeshOffset`: offset laterali per gli slot delle mesh aggiuntive.
- `GroundWallSettings`: comportamento dei muri di contenimento per segmento.

## Mesh aggiuntive

Le mesh aggiuntive seguono lo stesso intervallo di pezzi spline del pezzo stradale. Sono utili per guardrail, cordoli, recinzioni e oggetti decorativi laterali.

Gli array di inizio, metà e fine consentono mesh diverse ai confini dei segmenti. Le mesh aggiuntive sono etichettate con `AsyncSplineBuilder.ExtraMesh`, non `AsyncSplineBuilder.RoadMesh`.

## Interruzioni (Gaps)

Aggiungere voci a `JumpGapsByPoints` per sopprimere la generazione della strada e delle mesh aggiuntive per intervalli di indici di punti.

Gli intervalli sono intervalli di segmenti:

```text
[StartPointIndex, EndPointIndex)
```

Ad esempio, `StartPointIndex = 2`, `EndPointIndex = 4` sopprime i segmenti `2` e `3`.

## Dislivelli (Drops)

Aggiungere voci a `StuntDropsByPoints` per spostare gli intervalli di segmenti verso il basso o a un Z assoluto nel mondo.

Campi:

- `DropHeight`: offset Z relativo. Valori negativi spostano la strada verso il basso.
- `bUseConstantGapHeight`: usa Z assoluto del mondo invece dell'offset.
- `ConstantGapWorldZ`: altezza assoluta quando abilitata.

Se due segmenti adiacenti non interrotti si incontrano ad altezze diverse, l'actor crea un muro di dislivello tra di essi.

## Muri di contenimento

Abilitare `bGenerateGroundWalls` per generare strisce di muro procedurali verso il basso dal bordo della strada.

Muri di contenimento:

- Utilizzano la larghezza stradale ricavata dalla mesh o sostituita.
- Rispettano le impostazioni del muro per segmento.
- Dividono le strisce in corrispondenza delle interruzioni di salto e dei campioni non validi.
- Possono essere a singolo o doppio lato.
- Utilizzano UV basate sulla distanza e sull'altezza reale del muro.

Vedere [LandscapeAndWalls.md](LandscapeAndWalls.md) per la configurazione dettagliata.

## Allineamento al paesaggio

Allineamento mesh:

- `bSnapMeshesToLandscape`
- `ObjectsToHitForLandscapeLineTrace`
- `LineTraceLength`

Allineamento punti:

- `bSnapPointsToLandscape`
- `bTangentPointsUpdate`

Utilizzare `ActorsToIgnoreForGenerationTraces` per escludere mesh ausiliarie o oggetti temporanei dalle query di tracciamento.

## Deformazione del paesaggio

La deformazione riservata all'editor viene eseguita con `DeformLandscapeNow`.

Requisiti:

- `Landscape` assegnato.
- Una spline valida.
- Valori ragionevoli per `FallOff` e `NumberOfSubdivisionsForDeform`.
- `bRaiseHeights` e/o `bLowerHeights` abilitati.

Altezza: `DeformLandscapeNow` o pannello **Deform Height**. Pittura livello: assegnare `PaintLayer`, regolare `PaintHalfWidth` / `PaintFallOff` nel pannello, quindi `PaintLandscapeLayerNow` o pannello **Paint Layer**. La pittura è additiva; non cancella le fasce più ampie precedenti quando si riduce il falloff. `PaintFallOff = 0` produce un bordo netto. Se le informazioni del livello selezionato usano `bNoWeightBlend`, il pannello/la validazione avverte che gli altri livelli del paesaggio non sono garantiti per essere ridotti sotto la strada.

## Quando utilizzare il pannello Details

Il pannello del flusso di lavoro è volutamente focalizzato. Utilizzare il pannello Details quando è necessario modificare:

- array `ExtraMeshStart`, `ExtraMesh`, `ExtraMeshEnd` e `ExtraMeshOffset` per segmento
- `FGroundWallSettings` dettagliati, incluse sostituzioni di tracciamento, UV, materiale, collisione e larghezza
- array di oggetti di tracciamento per allineamento al paesaggio e generazione muri
- campi di lettura/scrittura degli asset di dati dei punti spline
- impostazioni avanzate di debug e costruzione

## Connettori di layout

La scheda Build include una sezione **Layout Connectors** per i metadati passivi di percorso. Un connettore collega un layout/distanza di origine a un layout/distanza di destinazione e memorizza un tipo semantico come `PitEntry`, `PitExit`, `Link` o `ServiceAccess`. È anche possibile digitare un tipo personalizzato; i tipi personalizzati non vuoti vengono convalidati come avvisi anziché errori.

Utilizzare **Pit Entry** per aggiungere un connettore predefinito da `Main` al primo layout della corsia box. Utilizzare **Pit Exit** per aggiungere un connettore predefinito dal primo layout della corsia box di nuovo a `Main`. **Validate** in questa sezione esegue la convalida riservata ai connettori.

Le modifiche ai connettori non rigenerano la strada e non eliminano la geometria generata. Non creano neppure mesh di transizione automatiche, non tagliano spline, non estendono la deformazione del terreno alle corsie box e non abilitano un renderer speciale per le corsie box.

Abilitare **Show Connector Debug** per posizionare marcatori di testo solo visivi nei punti finali dei connettori validi. Un marcatore identifica l'indice e il tipo di connettore, se si tratta del ruolo `From` o `To`, l'id del layout e la distanza; la sua dimensione segue `DebugTextWorldSize`.

I layout mancanti e le distanze fuori dall'intervallo di una spline vengono ignorati; utilizzare **Validate** per ispezionare tali problemi.

I marcatori utilizzano uscite di debug `UTextRenderComponent` e non aggiungono geometria stradale, mesh aggiuntive, muri di contenimento o muri di dislivello. La modifica dei connettori aggiorna i marcatori mentre la casella di controllo è abilitata. Disabilitare **Show Connector Debug** per rimuovere solo le etichette dei connettori. L'attivazione o l'aggiornamento di queste etichette non rigenera la pista, non modifica il conteggio dei componenti stradali, non estende il comportamento del terreno e non influisce sul gate di convalida della build.

## Flusso di lavoro degli asset di dati

Assegnare un `USplinePointListAsset` a `SplinePointList`.

Utilizzare:

- `WriteSplineToDataAsset`: salva i punti spline attuali.
- `ReadSplineFromDataAsset`: carica i punti spline.

Questo è utile per preservare i layout della pista separatamente dai componenti generati.

## Flusso di lavoro di produzione raccomandato

1. Costruire una breve spline di test.
2. Convalidare i limiti della mesh stradale e la ripetizione.
3. Aggiungere i dati per segmento.
4. Aggiungere le mesh aggiuntive.
5. Aggiungere interruzioni e dislivelli.
6. Configurare il tracciamento dei muri di contenimento.
7. Eseguire la deformazione del paesaggio solo dopo che la forma della strada è stabile.
8. Eseguire i test di automazione prima del rilascio.
9. Testare il livello in PIE e nella build runtime pacchettizzata.

## Cosa non fa il plugin

- Non fornisce modalità di pittura del paesaggio sostituisci/cancella o per segmento.
- Non crea mesh al posto dell'utente.
- Non garantisce banchine di terreno perfette su ogni paesaggio.
- Non genera automaticamente mesh stradali di transizione per i connettori.
- Non sostituisce la direzione artistica manuale per il ritocco finale della pista.

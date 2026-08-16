<!-- doc-provenance: product-facts.yml reconciled 2026-07-15; source AKDB:plugins/AsyncSplineBuilder/architecture.md -->
# Riferimento impostazioni

Questo riferimento descrive le impostazioni necessarie alla maggior parte degli utenti durante la configurazione di `ASplineGeneratingActor`.

## Mappatura del pannello del flusso di lavoro

Aprire **Tools > Track Tools > Async Spline Builder** per l'interfaccia incentrata sulle attività. Il pannello è suddiviso nelle schede **Build**, **Segments** e **Terrain**. Copre selezione actor, configurazione mesh, convalida, comandi di build e rebuild, batching asincrono, stato loop chiuso, etichette di debug, assistenti per righe di segmento, interruzioni di salto, dislivelli, assegnazione paesaggio, impostazioni pittura livello, deformazione altezza, interruttori di allineamento e muri di contenimento a livello di actor.

Utilizzare questo riferimento quando un'impostazione è esposta solo nel pannello Details o quando è necessario il comportamento esatto del campo. Array di mesh aggiuntive per segmento, impostazioni dettagliate dei muri di contenimento, array di oggetti di tracciamento, flag di collisione, controlli UV e campi degli asset di dati rimangono impostazioni avanzate del pannello Details.

## Configurazione mesh

### StartMesh

Mesh opzionale usata per il primo pezzo stradale generato su una pista aperta. Se non impostata, viene usata la mesh stradale del segmento selezionato.

### MainMesh

Mesh stradale di riserva obbligatoria. La validazione blocca la generazione quando questo campo è mancante.

### EndMesh

Mesh opzionale usata per l'ultimo pezzo stradale generato su una pista aperta. Se non impostata, viene usata la mesh stradale del segmento selezionato.

## TrackTools

### bEditSpline

Quando abilitato, i componenti generati vengono cancellati e rimane attiva solo la modifica spline/debug durante la costruzione. Utilizzare questa opzione durante la modellazione della spline senza ricostruire le mesh.

### bShowSegmentNumbers / bShowPointNumbers

Crea componenti di testo di debug per gli indici di segmento o di punto. Questi vengono etichettati e puliti insieme agli altri componenti generati.

### bShowLayoutConnectorDebug

Booleano, predefinito `false`. La casella di controllo **Show Connector Debug** nella sezione **Layout Connectors** del pannello controlla questa stessa impostazione. Quando abilitata, l'editor mostra un marcatore di testo per ciascun punto finale del connettore risolvibile indipendentemente. Ogni etichetta include l'indice e il tipo di connettore, il ruolo `From` o `To`, l'id del layout e la distanza configurata; la sua dimensione segue `DebugTextWorldSize`.

I layout mancanti e le distanze fuori dall'intervallo vengono ignorati anziché essere visualizzati in una posizione errata. L'attivazione o l'aggiornamento delle etichette dei connettori è puramente visivo: non rigenera la pista, non crea geometria stradale per connettori, non modifica il conteggio delle strade generate e non estende il comportamento del terreno. La disabilitazione dell'impostazione rimuove solo le etichette dei connettori.

### bShowSplineVisualizationWidth / SplineVisualizationWidth

Controlla la larghezza di visualizzazione della spline nell'editor.

### bSnapPointsToLandscape

Sposta i punti spline sugli impatti di tracciamento. Richiede `ObjectsToHitForLandscapeLineTrace`.

### bTangentPointsUpdate

Aggiorna le tangenti dopo l'allineamento dei punti al paesaggio.

### bMirrorExtraMesh

Riflette le mesh aggiuntive invertendo la loro scala X.

### SplinePointType

Il tipo di punto spline applicato durante gli aggiornamenti della spline. `CurveCustomTangent` è un buon valore predefinito per le strade.

### SplineZOffset

Applica uno spostamento verticale al componente spline.

### TrackSplineData

Dati per segmento. Se non esiste alcuna voce per un segmento, la voce `0` viene usata come fallback.

### AdditionalLayouts

Record di percorso opzionali per corsie box, percorsi alternativi, strade di servizio e spline decorative. La spline dell'actor legacy rimane la facciata del layout `Main`.

### LayoutConnectors

Collegamenti semantici passivi tra due distanze di layout. Ogni connettore memorizza:

- `FromLayoutId` / `FromDistance`
- `ToLayoutId` / `ToDistance`
- `ConnectorKind`

I tipi noti sono `PitEntry`, `PitExit`, `Link` e `ServiceAccess`. `ConnectorKind` rimane un `FName` aperto; i tipi personalizzati non vuoti sono consentiti e convalidati come avvisi. Tipo vuoto, layout mancanti, distanze errate e punti finali quasi uguali sullo stesso layout sono errori dell'ambito del connettore segnalati dalla convalida del connettore, ma gli errori del connettore non bloccano le rigenerazioni della geometria.

Le righe del connettore non generano mesh di transizione, non si rigenerano automaticamente e non modificano il comportamento di deformazione del terreno.

## TrackSplineData

### RoadMesh

Mesh stradale opzionale per il segmento. Si ripiega su `MainMesh`.

### MeshInstances

Numero esatto di pezzi di strada nel segmento. Quando è maggiore di zero, sostituisce il conteggio automatico basato sulla lunghezza.

### SegmentLength

Spaziatura di riserva quando `RoadMeshLength` non è impostato. Vengono usati valori maggiori di `1`.

### RoadMeshLength

Lunghezza di copertura desiderata della mesh stradale esplicita. Utilizzare questa opzione quando i limiti della mesh non corrispondono alla lunghezza visiva ripetuta.

### ExtraMeshStart / ExtraMesh / ExtraMeshEnd

Array opzionali di mesh aggiuntive per il primo pezzo, i pezzi centrali e l'ultimo pezzo.

### ExtraMeshOffset

Offset laterale per slot di mesh aggiuntiva.

### GroundWallSettings

Impostazioni di generazione muro, tracciamento, larghezza, collisione e UV per segmento.

## Options

### bClosedLoop

Collega l'ultimo punto spline al primo.

### bEnableCollision

Abilita la collisione per la strada generata e i componenti di muro procedurali.

### bCastShadow / bCastContactShadow

Controlla i flag di ombra delle mesh spline generate.

### bMirrorMesh

Riflette la scala della mesh stradale.

### bSnapMeshesToLandscape

Allinea le estremità delle mesh stradali e delle mesh aggiuntive generate agli impatti di tracciamento. Richiede tipi di oggetto di tracciamento.

## Landscape

### Landscape

Proxy del paesaggio utilizzato dalla deformazione riservata all'editor.

### ActorsToIgnoreForGenerationTraces

Actor ignorati dai tracciamenti di allineamento e muro.

### bSnapTraceLandscapeOnly

Se vero, i tracciamenti di allineamento accettano solo impatti con il paesaggio.

### ObjectsToHitForLandscapeLineTrace

Tipi di oggetto utilizzati dall'allineamento di mesh e punti. Richiesto quando l'allineamento è abilitato.

### FallOff

Distanza all'esterno della larghezza stradale su cui la deformazione dell'altezza si raccorda al terreno esistente.

### NumberOfSubdivisionsForDeform

Risoluzione di campionamento della spline per la deformazione del paesaggio. Valori più alti possono migliorare l'adattamento ma aumentano i costi.

### bRaiseHeights / bLowerHeights

Controlla se la deformazione può alzare e/o abbassare i campioni del paesaggio.

### PaintHalfWidth

Semi-larghezza a pieno peso per la pittura dei livelli (cm). `0` usa la semi-larghezza stradale per ciascun campione di deformazione.

### PaintFallOff

Distanza di attenuazione graduale (smoothstep) per la pittura dei livelli (cm). Indipendente dal `FallOff` dell'altezza. `0` dà un bordo netto senza fascia morbida all'esterno di `PaintHalfWidth`.

### PaintLayer

`ULandscapeLayerInfoObject` dipinto lungo la strada da `PaintLandscapeLayerNow` / pannello **Paint Layer**. Deve essere registrato sul paesaggio di destinazione. Se le informazioni del livello usano `bNoWeightBlend`, il livello di destinazione può comunque ricevere pittura, ma non è garantito che gli altri livelli di materiale vengano ridotti sotto la strada.

### LandscapeEditLayerName

Nome del livello di modifica utilizzato per le alterazioni dell'altezza del paesaggio quando supportato dalla configurazione del paesaggio.

### LineTraceLength

Profondità di tracciamento per l'allineamento al paesaggio.

## Async Build

### bUseAsyncBuild

Abilita rigenerazioni a blocchi.

### SegmentsPerTick

Numero di unità di lavoro asincrone elaborate per tick. Un'unità di lavoro è un pezzo di strada o di mesh aggiuntiva generato, quindi un lungo segmento di spline con molti pezzi viene distribuito su più tick. Iniziare con valori bassi per mantenere la reattività e aumentare dopo i test.

### bAutoRebuildOnConstruction

Pianifica le rigenerazioni dopo le modifiche di costruzione.

## Ground Walls

### bGenerateGroundWalls

Abilita la generazione di muri di contenimento procedurali.

### GroundWallSubdivisions

Numero di campioni di muro lungo la spline. Valori più alti producono muri più lisci e più geometria.

### GroundWallOutset

Offset orizzontale aggiuntivo oltre la semi-larghezza stradale ricavata.

### GroundWallFallbackDepth

Profondità utilizzata quando un tracciamento di muro fallisce.

### bGroundWallsDoubleSided

Aggiunge triangoli inversi in modo che i muri vengano renderizzati da entrambi i lati.

### GroundWallObjectsToHitForLineTrace

Tipi di oggetto di tracciamento predefiniti per i muri di contenimento quando le impostazioni di tracciamento per segmento sono vuote.

## GroundWallSettings

### bGenerateGroundWalls

Abilitazione del muro per segmento.

### bGenerateBothSides

Se falso, il lato sinistro viene soppresso per quel segmento.

### TrackHalfWidth

Sostituzione manuale della semi-larghezza. Lasciare `0` per ricavare la larghezza dai limiti della mesh stradale selezionata.

### MinWallHeight / MaxWallHeight

Ignora muri piccolissimi e limita muri molto grandi.

### bCreateCollision

Controlla la collisione del muro procedurale, anch'essa regolata da `bEnableCollision` dell'actor.

### TraceSettings

Tipi di oggetto di tracciamento, lunghezza di tracciamento e complessità di tracciamento per segmento.

### UVSettings

Ripetizione UV e inversioni del muro per segmento.

## Drop Walls

### DropWallMaterial

Materiale applicato ai muri di dislivello generati.

### DropWallUVWorldUnitsU / DropWallUVWorldUnitsV

Ripetizione UV in unità mondo per i muri di dislivello.

## Configurazione di base raccomandata

- `bUseAsyncBuild = true`
- `SegmentsPerTick = 24`
- `bAutoRebuildOnConstruction = true`
- `MainMesh` assegnato
- `RoadMeshLength = 0` a meno che i limiti della mesh non siano errati
- `TrackHalfWidth = 0` a meno che i limiti della mesh non siano errati
- Tipi di oggetto di tracciamento per i muri di contenimento configurati prima di abilitare i muri
- Deformazione del paesaggio eseguita manualmente dopo che la forma della strada è stabile

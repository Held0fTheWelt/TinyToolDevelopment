<!-- doc-provenance: product-facts.yml reconciled 2026-07-15; source AKDB:plugins/AsyncSplineBuilder/architecture.md -->
# Risoluzione dei problemi

## L'Actor non genera nulla

Verificare:

- `MainMesh` è assegnato.
- La spline ha almeno due punti.
- La validazione non ha bloccato la build.
- `bEditSpline` non sta cancellando intenzionalmente i componenti generati.
- Le mesh generate non sono nascoste dalla visibilità del livello o dell'actor.

## La Build è bloccata dalla validazione

La validazione blocca build errate e distruttive. Cause comuni:

- `MainMesh` manca.
- I muri di contenimento sono abilitati ma non sono stati configurati tipi di oggetto di tracciamento per i muri.
- L'allineamento al paesaggio è abilitato ma non sono stati configurati tipi di oggetto di tracciamento per il paesaggio.
- Gli intervalli delle interruzioni di salto o dei dislivelli non sono validi.

Correggere l'impostazione ed eseguire di nuovo `RebuildTrack`.

## La validazione dei connettori segnala problemi

Connector Validation Reports Issues si verifica quando un connettore di layout passivo punta a un actor mancante, a un id di layout sconosciuto, a una distanza spline non valida o a metadati del connettore incompleti.

Correggere il record del connettore nel pannello del flusso di lavoro o nel pannello Details, quindi eseguire di nuovo `Validate Layout Connectors`. La convalida dei connettori è separata dalla generazione della geometria: i record dei connettori descrivono l'intenzione del percorso e non creano mesh di transizione da soli.

## Un'etichetta del punto finale del connettore manca

Abilitare **Show Connector Debug** nella sezione **Layout Connectors** del pannello. Se appare solo un lato del connettore, eseguire **Validate Layout Connectors** e correggere il layout mancante o la distanza fuori dall'intervallo segnalata per il punto finale nascosto. I punti finali vengono risolti in modo indipendente e le posizioni non valide vengono volutamente ignorate.

Le etichette dei connettori sono solo visive. Non è necessario ricostruire la pista per crearle o aggiornarle, e la correzione di un'etichetta non aggiunge geometria stradale per connettori e non modifica il comportamento del terreno.

## Il pannello del flusso di lavoro non si apre

Aprirlo tramite **Tools > Track Tools > Async Spline Builder**. Se la voce di menu manca:

- ricompilare il target editor
- confermare che il modulo `AsyncSplineBuilderEditor` sia abilitato
- riavviare l'editor dopo aver abilitato il plugin
- controllare l'Output Log per eventuali errori di avvio di `AsyncSplineBuilderEditor`

Il pannello è riservato all'editor e non è disponibile nelle build pacchettizzate.

## L'Editor si blocca durante il Rebuild

Utilizzare impostazioni asincrone:

- `bUseAsyncBuild = true`
- ridurre `SegmentsPerTick`
- disabilitare la collisione complessa dei muri durante l'iterazione
- ridurre `GroundWallSubdivisions`

Conteggi elevati di componenti possono comunque risultare onerosi poiché la registrazione dei componenti Unreal avviene nel thread di gioco (game thread).

## Le mesh aggiuntive appaiono nella posizione errata

Verificare:

- pivot della mesh e assi locali
- `ExtraMeshOffset`
- `bMirrorExtraMesh`
- ripiegamento dei dati di segmento sull'indice `0`
- se gli array di inizio/metà/fine contengono mesh diverse

Le mesh aggiuntive utilizzano lo stesso intervallo spline del pezzo stradale.

## Le mesh stradali si allungano troppo

Impostare uno dei seguenti campi:

- `MeshInstances` per un conteggio esatto
- `RoadMeshLength` per una lunghezza esplicita del pezzo
- `SegmentLength` per un conteggio automatico dalla spaziatura desiderata

Se nessuno è impostato, viene usata la dimensione X dei limiti della mesh.

## Il loop chiuso ha una brutta giunzione

Verificare:

- posizioni/tangenti del primo e dell'ultimo punto spline
- pivot della mesh e lunghezza della tessellatura
- uso di `StartMesh` su loop chiusi
- impostazioni di levigatura delle tangenti

I loop chiusi costruiscono un segmento di avvolgimento fino alla lunghezza della spline.

## I muri di contenimento non appaiono

Verificare:

- `bGenerateGroundWalls` abilitato sull'actor
- `GroundWallSettings.bGenerateGroundWalls` per segmento
- `GroundWallObjectsToHitForLineTrace`
- `TraceSettings.ObjectsToHit` per segmento
- lunghezza di tracciamento
- `MinWallHeight`
- interruzioni di salto

Se i tracciamenti falliscono, viene usata la profondità di riserva. Se l'altezza del muro è ancora inferiore a `MinWallHeight`, non viene creata alcuna sezione.

## I muri di contenimento scavalcano le interruzioni

Non dovrebbero. Se si verifica questo comportamento, confermare che l'intervallo dell'interruzione utilizzi la semantica dei segmenti:

```text
[StartPointIndex, EndPointIndex)
```

Eseguire anche la suite di automazione; `GroundWallGapStripValid` copre il comportamento di base per la divisione della striscia.

## La larghezza del muro di contenimento è errata

La larghezza è ricavata dai limiti Y della mesh stradale selezionata a meno che `TrackHalfWidth` non sia maggiore di zero. Se i limiti della mesh non sono rappresentativi, impostare `TrackHalfWidth` manualmente.

## I muri di dislivello non appaiono

Verificare:

- entrambi i segmenti adiacenti hanno la strada
- il confine non è all'interno di un'interruzione di salto
- i segmenti adiacenti si risolvono in valori Z assoluti del mondo diversi
- `DropHeight` o Z costante è impostato su un lato

Eseguire `AsyncSplineBuilder.DropWallCount` per il comportamento di base del muro di dislivello.

## L'allineamento al paesaggio non fa nulla

Verificare:

- `bSnapMeshesToLandscape` o `bSnapPointsToLandscape` è abilitato
- `ObjectsToHitForLandscapeLineTrace` ha tipi di oggetto
- il tipo di oggetto di collisione del paesaggio corrisponde alla query
- `ActorsToIgnoreForGenerationTraces` non include la destinazione
- la lunghezza di tracciamento raggiunge la superficie

## La deformazione del paesaggio non fa nulla

Verificare:

- `Landscape` è assegnato
- il modulo editor è caricato
- la spline ha punti validi
- `NumberOfSubdivisionsForDeform` è maggiore di zero
- almeno uno tra `bRaiseHeights` o `bLowerHeights` è abilitato
- la strada sovrappone l'area del paesaggio

Ricordare: la deformazione è un'azione manuale nell'editor tramite `DeformLandscapeNow`.

## Il livello di materiale del paesaggio non viene dipinto

La deformazione dell'altezza (`DeformLandscapeNow`) e la pittura del peso del livello (`PaintLandscapeLayerNow`) sono azioni distinte. La pittura del livello richiede un `PaintLayer` valido registrato sul paesaggio. L'annullamento è gestito dalla transazione del deformatore; testare l'undo sul pannello, in CallInEditor e con un livello di modifica paesaggio attivo.

Se le informazioni del livello selezionato utilizzano `bNoWeightBlend`, l'operazione dovrebbe avvertire. In tale configurazione il livello di destinazione può ricevere pittura, ma il consueto comportamento "gli altri livelli vengono ridotti sotto la strada" non è garantito.

## La geometria generata si duplica dopo il Rebuild

I componenti generati sono puliti tramite tag. Se appaiono duplicati:

- verificare se codice personalizzato crea componenti senza `GeneratedTag`
- controllare se un componente modificato è stato duplicato manualmente
- eseguire l'automazione `CleanupRemovesAllTagged`

## Il processo asincrono runtime non si completa

Verificare:

- `bUseAsyncBuild = true`
- il gestore dei timer del mondo sta eseguendo i tick
- l'actor è valido e non distrutto
- `SegmentsPerTick` è almeno `1`
- la validazione non ha interrotto l'esecuzione prima dell'avvio

La pompa runtime si riarma con `SetTimerForNextTick` durante la costruzione.

## BuildPlugin o Build fallisce con collisioni Unity

Alcuni moduli definiscono assistenti con nomi simili in namespace anonimi. Se il raggruppamento Unity combina questi file, MSVC può segnalare definizioni duplicate. Il modulo interessato dovrebbe utilizzare impostazioni di build non-Unity come `bUseUnity = false`.

## L'automazione non trova test

Verificare:

- il target editor è stato compilato
- i test di automazione di sviluppo sono abilitati
- il comando usa `Automation RunTests AsyncSplineBuilder`
- i test sono compilati nel modulo editor

## I log sono troppo rumorosi

Cercare nel log:

```text
AsyncSplineBuilder
Result={Fail}
Result={Success}
TEST COMPLETE
```

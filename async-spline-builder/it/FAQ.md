<!-- doc-provenance: product-facts.yml reconciled 2026-07-15; source AKDB:plugins/AsyncSplineBuilder/architecture.md -->
# FAQ

## A cosa serve Async Spline Builder?

Costruisce mesh lungo una spline, come strade, piste da corsa, rotaie, tubi, barriere e muri di sostegno procedurali. Il suo vantaggio principale è il batching asincrono, così le spline lunghe possono rigenerarsi senza causare blocchi nell'editor.

## Funziona in fase di runtime?

Sì. Mesh stradali, mesh aggiuntive, muri di contenimento, muri di dislivello e la pompa asincrona runtime si trovano nel modulo runtime. La deformazione dell'altezza del paesaggio riservata all'editor non è disponibile nelle build pacchettizzate.

## Quale direzione deve utilizzare la mia mesh stradale?

Creare mesh stradali ripetibili lungo l'asse X locale. Il generatore usa i limiti della mesh su X per la lunghezza predefinita e i limiti su Y per la larghezza predefinita.

## Posso usare mesh diverse per segmento?

Sì. Aggiungere voci a `TrackSplineData` e impostare `RoadMesh`, `RoadMeshLength`, `SegmentLength`, `MeshInstances` e gli array di mesh aggiuntive per segmento. I dati di segmento mancanti si ripiegano sulla voce `0`.

## Dove posso configurare il plugin?

Utilizzare **Tools > Track Tools > Async Spline Builder** per il flusso di lavoro normale. Offre la selezione dell'actor, la configurazione delle mesh, la convalida, i controlli di build, le impostazioni asincrone, gli interruttori di visualizzazione della spline, gli assistenti di segmento, le azioni sul paesaggio e l'abilitazione dei muri di contenimento in un unico pannello. Utilizzare il pannello Details per array avanzati per segmento e campi dettagliati di tracciamento, muri, collisioni, UV e asset di dati.

## Qual è la differenza tra BuildTrack e RebuildTrack?

`BuildTrack` è sincrono e immediato. `RebuildTrack` usa il batching asincrono quando `bUseAsyncBuild` è abilitato.

## La generazione asincrona usa thread di lavoro (worker threads)?

No. Ripartisce il lavoro su più tick. Questo mantiene la creazione dei componenti Unreal nel thread di gioco (game thread), che è la sede corretta per registrare le istanze di `UActorComponent`.

## Può creare guardrail o mesh laterali?

Sì. Utilizzare `ExtraMeshStart`, `ExtraMesh`, `ExtraMeshEnd` e `ExtraMeshOffset` in `FTrackSplineData`.

## Può creare salti o sezioni stradali mancanti?

Sì. Utilizzare `JumpGapsByPoints`. Le interruzioni sopprimono le mesh stradali e aggiuntive per intervalli di segmenti.

## Può creare dislivelli di altezza?

Sì. Utilizzare `StuntDropsByPoints`. Segmenti adiacenti non interrotti ad altezze diverse creano muri di dislivello.

## Può creare muri fino al terreno?

Sì. Abilitare `bGenerateGroundWalls` e configurare i tipi di oggetto di tracciamento. Le strisce di muro procedurali tracciano dai bordi della strada verso il basso fino ai tipi di oggetto configurati.

## Deforma i paesaggi?

Sì, nell'editor. Utilizzare `DeformLandscapeNow` per l'altezza e `PaintLandscapeLayerNow` (o il pannello **Paint Layer**) per la pittura del peso additiva quando `PaintLayer` è assegnato.

## Dipinge i livelli del paesaggio?

Sì, per un singolo `PaintLayer` globale usando la pittura additiva `max`. Impostare `PaintLayer` sull'actor, assegnare il paesaggio, quindi eseguire **Paint Layer**. Le informazioni sui livelli con fusione del peso riducono gli altri livelli sotto la strada. Le informazioni sui livelli con `bNoWeightBlend` possono dipingere il livello di destinazione, ma non garantiscono che gli altri livelli vengano ridotti. Non supportato: modalità sostituisci/cancella, livelli di pittura per segmento o cancellazione automatica dei vecchi pesi riducendo la fascia di pittura.

## Perché la validazione ha bloccato la mia build?

L'actor blocca le build per errata configurazione distruttiva, come la mancanza di `MainMesh` o funzionalità basate sul tracciamento abilitate senza tipi di oggetto di tracciamento. Questo protegge la geometria generata esistente dalla cancellazione prima che si possa creare una sostituzione valida.

## Perché i miei muri sono mancanti?

Le cause comuni sono tipi di oggetto di tracciamento mancanti, assenza di impatti di tracciamento, `MinWallHeight` troppo alto, interruzioni di salto che tagliano la striscia o `bGenerateGroundWalls` disabilitato nelle impostazioni per segmento.

## Pulisce i componenti generati in modo sicuro?

Sì. Ai componenti generati vengono assegnati tag stabili e la pulizia scansiona i tag anziché fidarsi solo di array temporanei.

## Posso salvare il layout della spline?

Sì. Assegnare `SplinePointList` e utilizzare `WriteSplineToDataAsset` / `ReadSplineFromDataAsset`.

## Posso usarlo per prodotti Fab o giochi commerciali?

Sì, fermo restando i termini della licenza del prodotto. Il plugin non concede diritti su mesh, materiali o contenuti di terze parti usati con esso.

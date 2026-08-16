<!-- doc-provenance: AKDB:plugins/ProceduralGeneratedStructures/architecture.md; docs/architecture/plugins/ProceduralGeneratedStructures/product-facts.yml; reconciled 2026-06-21 -->
# Risoluzione dei problemi

## Ho abilitato il plugin ma non succede nulla

Il plugin aggiunge la classe `AAsyncProceduralGeneratedActor` e il `UProceduralStructureDataAsset`.
Posizionare l'actor in un livello (Place Actors → *Async Procedural Generated Actor*); non c'è un menu —
il flusso di lavoro risiede nel pannello Details dell'actor.

## La build non produce istanze

- Confermare che l'actor abbia almeno un componente figlio `UInstancedStaticMeshComponent` con un **nome stabile**.
- Confermare che **ComponentConfiguration** abbia una voce il cui **Name** corrisponda a quel componente.
- Confermare che alla voce dell'asset di dati sia assegnata una **Mesh** valida.
- Se si utilizza la lettura, assicurarsi di aver catturato prima (**bReadInMeshComponentData**) con una voce **ReadInComponentConfiguration** corrispondente.
- Ispezionare **GetBuildPlan**. Riporta codici di problema precisi come `component_not_found:<Name>`, `data_asset_element_not_found:<Name>` e `data_asset_element_missing_mesh:<Name>`.

## L'anteprima riporta un conteggio istanze molto elevato

Il piano di build riporta sia le istanze potenzialmente generate prima della potatura sia il conteggio esatto generato dopo la potatura. Se entrambi sono troppo alti, ridurre i conteggi delle righe, aggiungere la potatura (pruning) o abilitare **bUseAsyncBuild** e ridurre **InstancesPerFrame**.

## Le istanze catturate si sono spostate/ricentrate in modo imprevisto

Le istanze esplicite catturate vengono riprodotte esattamente e non vengono mai ricentrate. Solo le trasformazioni delle **righe generate** sono influenzate da **bCenterGeneratedTransforms**.

## La build causa scatti nell'editor / gioco su strutture grandi

Abilitare **bUseAsyncBuild** e ridurre **InstancesPerFrame** in modo che le istanze vengano aggiunte su più tick anziché in un unico passaggio bloccante.

## La lettura ha catturato il componente sbagliato

`ReadInComponentConfiguration` effettua la corrispondenza in base al **Name** del componente. Assicurarsi che i nomi dei componenti siano stabili e unici e che il `Name` della voce di configurazione corrisponda esattamente.

## La griglia generata presenta lacune

Controllare gli array `Pruned*` sulle informazioni della riga — gli indici/istanze potati vengono ignorati intenzionalmente. Cancellarli per generare una griglia completa.

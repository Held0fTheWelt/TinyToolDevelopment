<!-- doc-provenance: AKDB:plugins/ProceduralGeneratedStructures/architecture.md; docs/architecture/plugins/ProceduralGeneratedStructures/product-facts.yml; reconciled 2026-06-21 -->
# Riferimento impostazioni

Ogni proprietà accessibile all'utente e campo dell'asset di dati, con il relativo scopo.

## `AAsyncProceduralGeneratedActor`

| Proprietà | Categoria | Tipo | Scopo |
| --- | --- | --- | --- |
| `InstancesPerFrame` | Procedural\|Performance | int32 (min 1) | Istanze aggiunte per tick tra tutti i task di build quando la build asincrona è abilitata. |
| `bAutoBuildOnConstruction` | Procedural\|Build | bool | Attiva una build durante `OnConstruction`. |
| `bUseAsyncBuild` | Procedural\|Build | bool | Distribuisce la build su più frame (non bloccante); altrimenti costruisce in un unico passaggio. |
| `bCenterGeneratedTransforms` | Procedural\|Build | bool | Centra le trasformazioni delle **righe generate** attorno all'origine XY locale. Le istanze esplicite catturate non vengono mai ricentrate. |
| `ProceduralStructure` | Procedural | `UProceduralStructureDataAsset` | Sorgente dati che definisce cosa viene costruito. |
| `ReadInComponentConfiguration` | Procedural | array di `FInstancedComponentConfiguration` | Mappa i `UInstancedStaticMeshComponent` della scena → voci dell'asset di dati (lettura). |
| `ComponentConfiguration` | Procedural | array di `FInstancedComponentConfiguration` | Mappa le voci dell'asset di dati → componenti su questo actor (rigenerazione). |
| `bClearProceduralStructureInformation` | Procedural\|Debug | bool | Cancella i dati `ProceduralStructure` (attivatore editor). |
| `bReadInMeshComponentData` | Procedural\|Debug | bool | Legge le istanze dei componenti della scena nell'asset di dati (attivatore editor). |
| `EstimatedBuildInstanceCount` | Procedural\|Debug | int64 | Conteggio stimato delle istanze per la rigenerazione attuale o più recente. |
| `AddedBuildInstanceCount` | Procedural\|Debug | int64 | Istanze aggiunte dalla rigenerazione attuale o più recente. |

### Funzioni ausiliarie dell'actor

| Funzione | Scopo |
| --- | --- |
| `GetBuildPlan` | Anteprima non mutativa con componenti di destinazione, problemi bloccanti, intenzione di mutazione e conteggi esatti delle istanze dopo la potatura. |
| `GetEstimatedBuildInstanceCount` | Restituisce il conteggio stimato delle istanze per la build attuale o più recente. |
| `GetAddedBuildInstanceCount` | Restituisce quante istanze sono state aggiunte dalla build attuale o più recente. |
| `GetBuildProgress` | Restituisce il progresso della build da `0.0` a `1.0` quando è disponibile una stima. |

## `FInstancedComponentConfiguration`

| Campo | Tipo | Scopo |
| --- | --- | --- |
| `Name` | FName | Nome del componente mesh istanziato sull'actor. |
| `StructureType` | `EStructureType` | Classificazione della struttura per la mappatura. |

## `EStructureType`

`None`, `Structure`, `Railing`, `Tribune`, `Stairs`.

## `UProceduralStructureDataAsset` → `FInstancedMeshInformation`

| Campo | Tipo | Scopo |
| --- | --- | --- |
| `Name` | FName | Nome voce (corrisponde a una configurazione componente). |
| `Type` | `EStructureType` | Classificazione della struttura. |
| `Mesh` | `UStaticMesh` | Mesh usata per le istanze. |
| `Instances` | array di `FTransform` | Trasformazioni esplicite, riprodotte esattamente. |
| `InstancedMeshRows` | array di `FInstancedMeshRowInformation` | Regole di generazione procedurale delle righe. |

### Funzioni ausiliarie di DataAsset

| Funzione | Scopo |
| --- | --- |
| `GetElementStats` | Restituisce `FProceduralStructureElementStats` per una voce nominata. |
| `GetAllElementStats` | Restituisce le statistiche per ogni voce. |
| `GetTotalExplicitInstanceCount` | Conta le istanze esplicite catturate tra tutte le voci. |
| `GetTotalPotentialGeneratedInstanceCount` | Conta la capacità delle righe generate prima della potatura. |
| `GetTotalGeneratedInstanceCount` | Conta le istanze delle righe generate dopo la potatura. |
| `GetTotalInstanceCount` | Conta le istanze esplicite più quelle generate dopo la potatura. |

## `FProceduralStructureBuildPlan`

| Campo | Tipo | Scopo |
| --- | --- | --- |
| `bHasDataAsset` / `bHasComponentConfiguration` / `bHasInstancedComponents` | bool | Flag di prontezza ad alto livello. |
| `ConfiguredComponentCount` / `AvailableInstancedComponentCount` | int32 | Conteggio mappature e conteggio componenti ISM scoperti di proprietà dell'actor. |
| `MutatingComponentCount` | int32 | Componenti che verrebbero cancellati e rigenerati. |
| `InstanceAddingComponentCount` | int32 | Componenti che riceverebbero una o più istanze. |
| `TotalExplicitInstanceCount` | int64 | Istanze esplicite catturate nelle voci edificabili. |
| `TotalPotentialGeneratedInstanceCount` | int64 | Capacità delle righe generate prima della potatura. |
| `TotalGeneratedInstanceCount` | int64 | Istanze delle righe generate dopo la potatura. |
| `TotalInstanceCount` | int64 | Istanze esplicite più quelle generate dopo la potatura. |
| `Entries` | array di `FProceduralStructureBuildPlanEntry` | Voci di anteprima per componente configurato. |
| `Issues` | array di string | Codici di problemi bloccanti. |

## `FProceduralStructureElementStats`

| Campo | Tipo | Scopo |
| --- | --- | --- |
| `Name` / `Type` / `Mesh` / `bHasMesh` | misto | Identità e prontezza mesh per una voce dell'asset di dati. |
| `ExplicitInstanceCount` | int32 | Conteggio delle trasformazioni esplicite catturate. |
| `RowRuleCount` | int32 | Conteggio delle regole di generazione delle righe. |
| `PotentialGeneratedInstanceCount` | int64 | Capacità delle righe prima della potatura. |
| `GeneratedInstanceCount` | int64 | Conteggio esatto generato dopo la potatura. |
| `TotalInstanceCount` | int64 | Conteggio esplicito più generato dopo la potatura. |

## `FInstancedMeshRowInformation` (generazione righe)

| Campo | Tipo | Scopo |
| --- | --- | --- |
| `Transform` | FTransform | Trasformazione di base per la riga. |
| `RowCount_FirstDimension` / `_SecondDimension` / `_ThirdDimension` | int32 (min 0) | Conteggi istanze per dimensione. |
| `Movement_First_Dimension` / `_Second_Dimension` / `_Third_Dimension` | FTransform | Trasformazione passo-passo applicata lungo ciascuna dimensione. |
| `MovementAdjustmentByRotation_First_Dimension` | FVector | Aggiustamento del movimento applicato dalla rotazione lungo la prima dimensione. |
| `DefinedSecondDimension` | array di FVector | Posizionamenti espliciti nella seconda dimensione. |
| `PrunedInstances` / `PrunedFirstDimension` / `PrunedSecondDimension` / `PrunedThirdDimension` / `PrunedSecondDimensionInThirdDimension` | array | Indici/istanze da saltare durante la generazione. |
| `bApplyRowCountAdjust` | bool | Applica aggiustamento del conteggio righe. |
| `bUseDefinedPlacementMethod` | bool | Usa il posizionamento `DefinedSecondDimension` invece del movimento passo-passo. |

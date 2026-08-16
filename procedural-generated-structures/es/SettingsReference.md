<!-- doc-provenance: AKDB:plugins/ProceduralGeneratedStructures/architecture.md; docs/architecture/plugins/ProceduralGeneratedStructures/product-facts.yml; reconciled 2026-06-21 -->
# Referencia de configuración

Cada propiedad orientada al usuario y campo de activo de datos, con su propósito.

## `AAsyncProceduralGeneratedActor`

| Propiedad | Categoría | Tipo | Propósito |
| --- | --- | --- | --- |
| `InstancesPerFrame` | Procedural\|Performance | int32 (min 1) | Instancias agregadas por tic en todas las tareas de compilación cuando la compilación asíncrona está habilitada. |
| `bAutoBuildOnConstruction` | Procedural\|Build | bool | Activa una compilación durante `OnConstruction`. |
| `bUseAsyncBuild` | Procedural\|Build | bool | Distribuye la compilación en varios fotogramas (no bloqueante); de lo contrario, compila en un solo pase. |
| `bCenterGeneratedTransforms` | Procedural\|Build | bool | Centra las transformaciones de **filas generadas** alrededor del origen XY local. Las instancias explícitas capturadas nunca se vuelven a centrar. |
| `ProceduralStructure` | Procedural | `UProceduralStructureDataAsset` | Fuente de datos que define lo que se compila. |
| `ReadInComponentConfiguration` | Procedural | arreglo de `FInstancedComponentConfiguration` | Mapea `UInstancedStaticMeshComponent` de la escena → entradas de activos de datos (lectura). |
| `ComponentConfiguration` | Procedural | arreglo de `FInstancedComponentConfiguration` | Mapea entradas de activos de datos → componentes en este actor (recompilación). |
| `bClearProceduralStructureInformation` | Procedural\|Debug | bool | Borra los datos de `ProceduralStructure` (activador del editor). |
| `bReadInMeshComponentData` | Procedural\|Debug | bool | Lee instancias de componentes de la escena en el activo de datos (activador del editor). |
| `EstimatedBuildInstanceCount` | Procedural\|Debug | int64 | Recuento estimado de instancias para la recompilación actual o más reciente. |
| `AddedBuildInstanceCount` | Procedural\|Debug | int64 | Instancias agregadas por la recompilación actual o más reciente. |

### Funciones auxiliares del actor

| Función | Propósito |
| --- | --- |
| `GetBuildPlan` | Vista previa no mutativa con componentes de destino, problemas de bloqueo, intención de mutación y recuentos exactos de instancias tras la poda. |
| `GetEstimatedBuildInstanceCount` | Devuelve el recuento estimado de instancias para la compilación actual o más reciente. |
| `GetAddedBuildInstanceCount` | Devuelve cuántas instancias han sido agregadas por la compilación actual o más reciente. |
| `GetBuildProgress` | Devuelve el progreso de la compilación de `0.0` a `1.0` cuando hay una estimación disponible. |

## `FInstancedComponentConfiguration`

| Campo | Tipo | Propósito |
| --- | --- | --- |
| `Name` | FName | Nombre del componente de malla instanciada en el actor. |
| `StructureType` | `EStructureType` | Clasificación de estructura para el mapeo. |

## `EStructureType`

`None`, `Structure`, `Railing`, `Tribune`, `Stairs`.

## `UProceduralStructureDataAsset` → `FInstancedMeshInformation`

| Campo | Tipo | Propósito |
| --- | --- | --- |
| `Name` | FName | Nombre de entrada (coincide con una configuración de componente). |
| `Type` | `EStructureType` | Clasificación de estructura. |
| `Mesh` | `UStaticMesh` | Malla utilizada para las instancias. |
| `Instances` | arreglo de `FTransform` | Transformaciones explícitas, reproducidas exactamente. |
| `InstancedMeshRows` | arreglo de `FInstancedMeshRowInformation` | Reglas de generación de filas procedimentales. |

### Funciones auxiliares de DataAsset

| Función | Propósito |
| --- | --- |
| `GetElementStats` | Devuelve `FProceduralStructureElementStats` para una entrada con nombre. |
| `GetAllElementStats` | Devuelve estadísticas para cada entrada. |
| `GetTotalExplicitInstanceCount` | Cuenta instancias explícitas capturadas en todas las entradas. |
| `GetTotalPotentialGeneratedInstanceCount` | Cuenta la capacidad de filas generadas antes de la poda. |
| `GetTotalGeneratedInstanceCount` | Cuenta instancias de filas generadas después de la poda. |
| `GetTotalInstanceCount` | Cuenta instancias explícitas más generadas después de la poda. |

## `FProceduralStructureBuildPlan`

| Campo | Tipo | Propósito |
| --- | --- | --- |
| `bHasDataAsset` / `bHasComponentConfiguration` / `bHasInstancedComponents` | bool | Banderas de preparación de alto nivel. |
| `ConfiguredComponentCount` / `AvailableInstancedComponentCount` | int32 | Recuento de mapeos y recuento de componentes ISM descubiertos propiedad del actor. |
| `MutatingComponentCount` | int32 | Componentes que se borrarían y recompilarían. |
| `InstanceAddingComponentCount` | int32 | Componentes que recibirían una o más instancias. |
| `TotalExplicitInstanceCount` | int64 | Instancias explícitas capturadas en entradas compilables. |
| `TotalPotentialGeneratedInstanceCount` | int64 | Capacidad de filas generadas antes de la poda. |
| `TotalGeneratedInstanceCount` | int64 | Instancias de filas generadas después de la poda. |
| `TotalInstanceCount` | int64 | Instancias explícitas más generadas después de la poda. |
| `Entries` | arreglo de `FProceduralStructureBuildPlanEntry` | Entradas de vista previa por componente configurado. |
| `Issues` | arreglo de string | Códigos de problemas de bloqueo. |

## `FProceduralStructureElementStats`

| Campo | Tipo | Propósito |
| --- | --- | --- |
| `Name` / `Type` / `Mesh` / `bHasMesh` | mixto | Identidad y preparación de malla para una entrada de activo de datos. |
| `ExplicitInstanceCount` | int32 | Recuento de transformaciones explícitas capturadas. |
| `RowRuleCount` | int32 | Recuento de reglas de generación de filas. |
| `PotentialGeneratedInstanceCount` | int64 | Capacidad de filas antes de la poda. |
| `GeneratedInstanceCount` | int64 | Recuento exacto generado después de la poda. |
| `TotalInstanceCount` | int64 | Recuento explícito más generado después de la poda. |

## `FInstancedMeshRowInformation` (generación de filas)

| Campo | Tipo | Propósito |
| --- | --- | --- |
| `Transform` | FTransform | Transformación base para la fila. |
| `RowCount_FirstDimension` / `_SecondDimension` / `_ThirdDimension` | int32 (min 0) | Recuentos de instancias por dimensión. |
| `Movement_First_Dimension` / `_Second_Dimension` / `_Third_Dimension` | FTransform | Transformación paso a paso aplicada a lo largo de cada dimensión. |
| `MovementAdjustmentByRotation_First_Dimension` | FVector | Ajuste de movimiento aplicado por rotación a lo largo de la primera dimensión. |
| `DefinedSecondDimension` | arreglo de FVector | Ubicaciones explícitas en la segunda dimensión. |
| `PrunedInstances` / `PrunedFirstDimension` / `PrunedSecondDimension` / `PrunedThirdDimension` / `PrunedSecondDimensionInThirdDimension` | arreglos | Índices/instancias a omitir durante la generación. |
| `bApplyRowCountAdjust` | bool | Aplicar ajuste de recuento de filas. |
| `bUseDefinedPlacementMethod` | bool | Usar ubicación `DefinedSecondDimension` en lugar de movimiento paso a paso. |

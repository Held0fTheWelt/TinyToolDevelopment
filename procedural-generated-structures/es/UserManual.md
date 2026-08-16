<!-- doc-provenance: AKDB:plugins/ProceduralGeneratedStructures/architecture.md; docs/architecture/plugins/ProceduralGeneratedStructures/product-facts.yml; reconciled 2026-06-21 -->
# Manual de usuario

Este manual explica cómo utilizar Procedural Generated Structures en Unreal Editor.

## Propósito

Procedural Generated Structures construye estructuras de malla estática instanciada reutilizables a partir de un activo de datos.
El actor en tiempo de ejecución puede leer instancias existentes de `UInstancedStaticMeshComponent` en un `UProceduralStructureDataAsset`, y luego recompilar esas instancias explícitas o generar estructuras adicionales basadas en filas.

## Objetos principales

- **`AAsyncProceduralGeneratedActor`** — posee el flujo de trabajo de compilación y puede recompilar componentes de forma síncrona o a través de tics del editor/juego.
- **`UProceduralStructureDataAsset`** — almacena entradas de malla con nombre (`FInstancedMeshInformation`) con transformaciones explícitas y reglas opcionales de generación de filas.
- **`FInstancedComponentConfiguration`** — mapea un componente de malla instanciada con nombre en el actor a una entrada de activo de datos almacenada (`Name` + `StructureType`).
- **`FProceduralStructureBuildPlan`** — informa qué haría una recompilación: componentes de destino, problemas de bloqueo, intención de mutación, recuentos asíncronos y totales exactos de instancias tras la poda.
- **`FProceduralStructureElementStats`** — informa recuentos de instancias explícitas, generadas, potencialmente generadas y totales por entrada.
- **`EStructureType`** — `None`, `Structure`, `Railing`, `Tribune`, `Stairs`.

## Flujo de trabajo

1. Agregue un `AAsyncProceduralGeneratedActor` a un nivel o blueprint.
2. Agregue uno o más componentes secundarios `UInstancedStaticMeshComponent` con **nombres de componentes estables**.
3. Asigne un `UProceduralStructureDataAsset` a **ProceduralStructure**.
4. Configure **ReadInComponentConfiguration** para capturar las instancias de componentes existentes en el activo (active con **bReadInMeshComponentData**).
5. Configure **ComponentConfiguration** para recompilar esas entradas de regreso en los componentes.
6. Inspeccione **GetBuildPlan** (Blueprint/C++) o la ruta de vista previa si utiliza automatización. Corrija cualquier problema informado antes de aplicar una recompilación.
7. Utilice **bClearProceduralStructureInformation** (borrar), **bReadInMeshComponentData** (leer) y la compilación (construcción / asíncrona) para iterar en la estructura.

## Notas de compilación

- Las transformaciones explícitas leídas desde los componentes de la escena se **reproducen exactamente** y no se vuelven a centrar durante la recompilación.
- Las transformaciones de filas generadas se pueden centrar alrededor del origen XY local con **bCenterGeneratedTransforms**.
- **InstancesPerFrame** limita cuántas instancias se agregan por tic cuando la compilación asíncrona está habilitada.
- Los recuentos de filas se limitan a valores no negativos antes de la generación.
- Los planes de compilación y las estadísticas del DataAsset informan tanto la capacidad de filas no podadas como el recuento exacto generado después de la poda, de modo que las recompilaciones grandes se puedan estimar antes de la mutación.
- **bAutoBuildOnConstruction** activa una compilación durante `OnConstruction` (similar al actor spline).
- **bUseAsyncBuild** distribuye la compilación entre fotogramas; de lo contrario, la compilación ocurre en un solo pase.
- **GetBuildProgress**, **GetEstimatedBuildInstanceCount** y **GetAddedBuildInstanceCount** informan el progreso de la compilación asíncrona para herramientas del editor y Blueprints.

## Plan de compilación y validación

`AAsyncProceduralGeneratedActor::GetBuildPlan` es una vista previa no mutativa. Utilícela antes de recompilar estructuras grandes o compartidas.

El plan de compilación informa:

- Si existen un activo de datos, una configuración de componentes y componentes de malla instanciada propiedad del actor.
- Una entrada por componente configurado, incluyendo ruta del componente, ruta de la malla, estadísticas de elementos de DataAsset, intención de mutación y códigos de problemas de bloqueo.
- Totales para instancias explícitas, instancias potencialmente generadas antes de la poda, instancias generadas después de la poda y recuento combinado de instancias.

Los códigos de problemas de bloqueo comunes incluyen:

- `missing_procedural_structure_data_asset`
- `missing_component_configuration`
- `actor_has_no_instanced_static_mesh_components`
- `component_not_found:<Name>`
- `data_asset_element_not_found:<Name>`
- `data_asset_element_missing_mesh:<Name>`
- `data_asset_element_type_none:<Name>`

## Entradas de activos de datos

Cada entrada `FInstancedMeshInformation` contiene:

- `Name`, `Type` (`EStructureType`), `Mesh` (`UStaticMesh`).
- `Instances` — transformaciones explícitas (por ejemplo, capturadas de la escena), reproducidas tal cual.
- `InstancedMeshRows` — reglas opcionales de generación de filas procedimentales (recuentos de filas por dimensión, transformaciones de movimiento por dimensión, opciones de poda/ubicación definida). Consulte [SettingsReference.md](SettingsReference.md) para cada campo.

## Lo que el complemento no hace

- No crea mallas estáticas por usted — usted proporciona las suyas.
- No vuelve a centrar las instancias capturadas explícitamente.
- No es un sistema de modelado procedimental completo; coloca y regenera mallas instanciadas a partir de datos.

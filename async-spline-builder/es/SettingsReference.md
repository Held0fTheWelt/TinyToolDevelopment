<!-- doc-provenance: product-facts.yml reconciled 2026-07-15; source AKDB:plugins/AsyncSplineBuilder/architecture.md -->
# Referencia de configuración

Esta referencia describe las configuraciones que la mayoría de los usuarios necesitan al configurar `ASplineGeneratingActor`.

## Mapeo del panel de flujo de trabajo

Abra **Tools > Track Tools > Async Spline Builder** para la interfaz centrada en tareas. El panel se divide en las pestañas **Build**, **Segments** y **Terrain**. Cubre selección de actor, configuración de mallas, validación, comandos de compilación y recompilación, procesamiento por lotes asíncrono, estado de bucle cerrado, etiquetas de depuración, asistentes de filas de segmentos, huecos de salto, desniveles, asignación de terreno, configuración de pintura de capas, deformación de altura, interruptores de ajuste y muros de contención a nivel de actor.

Utilice esta referencia cuando una configuración solo esté expuesta en el panel Details o cuando necesite el comportamiento exacto del campo. Arreglos de mallas adicionales por segmento, configuraciones detalladas de muros de contención, arreglos de objetos de trazado, banderas de colisión, controles UV y campos de activos de datos siguen siendo configuraciones avanzadas del panel Details.

## Configuración de mallas

### StartMesh

Malla opcional utilizada para la primera pieza de carretera generada en una pista abierta. Si no se establece, se utiliza la malla de carretera del segmento seleccionado.

### MainMesh

Malla de carretera de reserva obligatoria. La validación bloquea la generación cuando falta.

### EndMesh

Malla opcional utilizada para la última pieza de carretera generada en una pista abierta. Si no se establece, se utiliza la malla de carretera del segmento seleccionado.

## TrackTools

### bEditSpline

Cuando está habilitado, los componentes generados se borran y solo la edición de spline/depuración permanece activa durante la construcción. Utilice esto al dar forma a la spline sin recompilar mallas.

### bShowSegmentNumbers / bShowPointNumbers

Crea componentes de texto de depuración para índices de segmentos o puntos. Estos se etiquetan y limpian junto con otros componentes generados.

### bShowLayoutConnectorDebug

Booleano, predeterminado `false`. La casilla de verificación **Show Connector Debug** en la sección **Layout Connectors** del panel controla esta misma configuración. Cuando está habilitada, el editor muestra un marcador de texto para cada extremo de conector que se pueda resolver de forma independiente. Cada etiqueta incluye el índice y tipo de conector, el rol `From` o `To`, el id de diseño y la distancia configurada; su tamaño sigue `DebugTextWorldSize`.

Los diseños faltantes y las distancias fuera de rango se omiten en lugar de mostrarse en una posición errónea. Alternar o actualizar las etiquetas de conectores es puramente visual: no recompila la pista, no crea geometría de carretera para conectores, no cambia los recuentos de carreteras generadas y no extiende el comportamiento del terreno. Deshabilitar la configuración elimina solo las etiquetas de conectores.

### bShowSplineVisualizationWidth / SplineVisualizationWidth

Controla el ancho de visualización de la spline en el editor.

### bSnapPointsToLandscape

Mueve los puntos spline a los impactos de trazado. Requiere `ObjectsToHitForLandscapeLineTrace`.

### bTangentPointsUpdate

Actualiza las tangentes después de ajustar los puntos al terreno.

### bMirrorExtraMesh

Refleja mallas adicionales invirtiendo su escala X.

### SplinePointType

El tipo de punto spline aplicado durante las actualizaciones de spline. `CurveCustomTangent` es una buena opción predeterminada para carreteras.

### SplineZOffset

Aplica un desplazamiento vertical al componente spline.

### TrackSplineData

Datos por segmento. Si no existe ninguna entrada para un segmento, se utiliza la entrada `0` como reserva.

### AdditionalLayouts

Registros de ruta opcionales para carriles de boxes, rutas alternativas, carreteras de servicio y splines decorativas. La spline del actor heredado sigue siendo la fachada del diseño `Main`.

### LayoutConnectors

Enlaces semánticos pasivos entre dos distancias de diseño. Cada conector almacena:

- `FromLayoutId` / `FromDistance`
- `ToLayoutId` / `ToDistance`
- `ConnectorKind`

Los tipos conocidos son `PitEntry`, `PitExit`, `Link` y `ServiceAccess`. `ConnectorKind` sigue siendo un `FName` abierto; los tipos personalizados no vacíos están permitidos y se validan como advertencias. Tipo vacío, diseños faltantes, distancias erróneas y extremos casi iguales en el mismo diseño son errores del ámbito del conector informados por la validación del conector, pero los errores del conector no bloquean las recompilaciones de geometría.

Las filas de conectores no generan mallas de transición, no se recompilan automáticamente y no cambian el comportamiento de deformación del terreno.

## TrackSplineData

### RoadMesh

Malla de carretera opcional para el segmento. Se remite a `MainMesh`.

### MeshInstances

Número exacto de piezas de carretera en el segmento. Cuando es mayor que cero, anula el recuento automático basado en la longitud.

### SegmentLength

Espaciado de reserva cuando `RoadMeshLength` no está configurado. Se utilizan valores mayores que `1`.

### RoadMeshLength

Longitud de cobertura deseada de la malla de carretera explícita. Utilice esto cuando los límites de la malla no coincidan con la longitud visual repetida.

### ExtraMeshStart / ExtraMesh / ExtraMeshEnd

Arreglos opcionales de mallas adicionales para la primera pieza, las piezas centrales y la última pieza.

### ExtraMeshOffset

Desplazamiento lateral por ranura de malla adicional.

### GroundWallSettings

Configuración de generación de muros, trazado, ancho, colisión y UV por segmento.

## Options

### bClosedLoop

Conecta el último punto spline de regreso al primero.

### bEnableCollision

Habilita la colisión para la carretera generada y los componentes de muro procedimentales.

### bCastShadow / bCastContactShadow

Controla las banderas de sombra de las mallas spline generadas.

### bMirrorMesh

Refleja la escala de la malla de carretera.

### bSnapMeshesToLandscape

Ajusta los extremos de las mallas de carretera y mallas adicionales generadas a los impactos de trazado. Requiere tipos de objetos de trazado.

## Landscape

### Landscape

Proxy de terreno utilizado por la deformación exclusiva del editor.

### ActorsToIgnoreForGenerationTraces

Actores ignorados por los trazados de ajuste y muro.

### bSnapTraceLandscapeOnly

Si es verdadero, los trazados de ajuste solo aceptan impactos en el terreno.

### ObjectsToHitForLandscapeLineTrace

Tipos de objetos utilizados por el ajuste de mallas y puntos. Requerido cuando el ajuste está habilitado.

### FallOff

Distancia fuera del ancho de la carretera sobre la cual la deformación de altura se mezcla suavemente con el terreno existente.

### NumberOfSubdivisionsForDeform

Resolución de muestreo de la spline para la deformación del terreno. Valores más altos pueden mejorar el ajuste pero aumentan el costo.

### bRaiseHeights / bLowerHeights

Controla si la deformación puede elevar y/o bajar muestras de terreno.

### PaintHalfWidth

Ancho medio a peso completo para pintura de capas (cm). `0` utiliza el ancho medio de la carretera en cada muestra de deformación.

### PaintFallOff

Distancia de atenuación suave (smoothstep) para pintura de capas (cm). Independiente del `FallOff` de altura. `0` da un borde duro sin banda suave fuera de `PaintHalfWidth`.

### PaintLayer

`ULandscapeLayerInfoObject` pintado a lo largo de la carretera por `PaintLandscapeLayerNow` / panel **Paint Layer**. Debe estar registrado en el terreno de destino. Si la información de capa usa `bNoWeightBlend`, la capa de destino aún puede recibir pintura, pero no se garantiza que otras capas de material se reduzcan debajo de la carretera.

### LandscapeEditLayerName

Nombre de la capa de edición utilizada para alteraciones de altura de terreno cuando sea compatible con la configuración del terreno.

### LineTraceLength

Profundidad de trazado para ajuste al terreno.

## Async Build

### bUseAsyncBuild

Habilita recompilaciones por lotes.

### SegmentsPerTick

Número de unidades de trabajo asíncronas procesadas por tic. Una unidad de trabajo es una pieza de carretera o malla adicional generada, por lo que un segmento spline largo con muchas piezas se distribuye en varios tics. Comience bajo para mantener la capacidad de respuesta y aumente después de probar.

### bAutoRebuildOnConstruction

Programa recompilaciones después de cambios de construcción.

## Ground Walls

### bGenerateGroundWalls

Habilita la generación de muros de contención procedimentales.

### GroundWallSubdivisions

Número de muestras de muro a lo largo de la spline. Valores más altos producen muros más suaves y más geometría.

### GroundWallOutset

Desplazamiento horizontal adicional más allá del ancho medio derivado de la carretera.

### GroundWallFallbackDepth

Profundidad utilizada cuando falla un trazado de muro.

### bGroundWallsDoubleSided

Agrega triángulos inversos para que los muros se rendericen desde ambos lados.

### GroundWallObjectsToHitForLineTrace

Tipos de objetos de trazado predeterminados para muros de contención cuando la configuración de trazado por segmento está vacía.

## GroundWallSettings

### bGenerateGroundWalls

Habilitación de muro por segmento.

### bGenerateBothSides

Si es falso, el lado izquierdo se suprime para ese segmento.

### TrackHalfWidth

Reemplazo manual del ancho medio. Deje `0` para derivar el ancho de los límites de la malla de carretera seleccionada.

### MinWallHeight / MaxWallHeight

Omite muros diminutos y limita muros muy grandes.

### bCreateCollision

Controla la colisión del muro procedimental, también regulada por `bEnableCollision` del actor.

### TraceSettings

Tipos de objetos de trazado, longitud de trazado y complejidad de trazado por segmento.

### UVSettings

Repetición UV e inversiones del muro por segmento.

## Drop Walls

### DropWallMaterial

Material aplicado a los muros de desnivel generados.

### DropWallUVWorldUnitsU / DropWallUVWorldUnitsV

Repetición UV en unidades del mundo para muros de desnivel.

## Configuración base recomendada

- `bUseAsyncBuild = true`
- `SegmentsPerTick = 24`
- `bAutoRebuildOnConstruction = true`
- `MainMesh` asignado
- `RoadMeshLength = 0` a menos que los límites de la malla sean erróneos
- `TrackHalfWidth = 0` a menos que los límites de la malla sean erróneos
- Tipos de objetos de trazado para muros de contención configurados antes de habilitar muros
- Deformación de terreno ejecutada manualmente después de que la forma de la carretera sea estable

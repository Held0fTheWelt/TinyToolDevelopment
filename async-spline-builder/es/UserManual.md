<!-- doc-provenance: product-facts.yml reconciled 2026-07-15; source AKDB:plugins/AsyncSplineBuilder/architecture.md -->
# Manual de usuario

Este manual explica cómo usar Async Spline Builder en Unreal Editor y cómo se integran las características principales.

## Propósito

Async Spline Builder crea componentes generados a partir de una spline editable. La salida típica es una carretera o pista hecha de secciones `USplineMeshComponent`, con mallas spline adicionales opcionales y mallas de muro procedimentales.

El actor puede recompilar de forma síncrona o por lotes. El procesamiento por lotes mantiene el editor receptivo en pistas largas y también está disponible en tiempo de ejecución mediante una bomba de temporizador en el siguiente tic.

## Apertura y habilitación

1. Abra **Edit > Plugins**.
2. Habilite **AsyncSplineBuilder**.
3. Reinicie el editor si se le solicita.
4. Abra o cree un nivel.
5. Abra **Tools > Track Tools > Async Spline Builder**.

El complemento contiene módulos en tiempo de ejecución y del editor. El actor es compatible con el tiempo de ejecución; el panel de flujo de trabajo y las herramientas de deformación de terreno son exclusivas del editor.

## Panel de flujo de trabajo

El panel Async Spline Builder es la forma recomendada de configurar pistas normales. Evita dispersar el flujo de trabajo común en varias categorías de Details.

El panel está organizado en pestañas:

- **Build**: selección de actor, configuración de mallas, validar/compilar/recompilar/cancelar, procesamiento por lotes asíncrono, bucle cerrado, etiquetas de depuración de puntos o segmentos, y etiquetas de extremo de conectores de diseño opcionales.
- **Segments**: `TrackSplineData` por segmento, creación de filas de segmentos, huecos de salto y desniveles.
- **Terrain**: ajuste al terreno, asignación de terreno, configuración de pintura de capas, deformación de altura, pintura de capas aditiva y muros de contención.

Utilice el panel Details para arreglos avanzados y configuraciones poco comunes que intencionalmente no se duplican en el panel de flujo de trabajo.

## Configuración básica del actor

1. En el panel de flujo de trabajo, presione **Create Actor** o seleccione un `ASplineGeneratingActor` existente y presione **Use Selection**.
2. En **Setup**, asigne `MainMesh`.
3. Opcionalmente asigne `StartMesh` y `EndMesh`.
4. Mueva los puntos spline en el visor.
5. Presione **Validate**.
6. Presione **Build Now** o **Rebuild**.

`MainMesh` es requerido. La validación bloquea las compilaciones sin él para que la geometría generada existente no se borre y se reemplace por nada.

## Expectativas de creación de mallas

Las mallas de carretera deben:

- Repetirse a lo largo del eje X local.
- Tener una extensión Y razonable ya que los límites de la malla se utilizan para derivar el ancho medio de la carretera.
- Usar pivotes consistentes.
- Evitar complejidad de colisión oculta a menos que la colisión sea necesaria.

Si los límites de la malla no son representativos, configure `GroundWallSettings.TrackHalfWidth` manualmente.

## Edición de la spline

Utilice las herramientas estándar de edición de spline de Unreal. Campos útiles:

- `bClosedLoop`: conecta el último punto con el primer punto.
- `SplinePointType`: controla el comportamiento de interpolación de puntos.
- `SplineZOffset`: aplica un desplazamiento vertical al componente spline.
- `bShowPointNumbers`: muestra índices de puntos.
- `bShowSegmentNumbers`: muestra índices de segmentos.
- `bShowSplineVisualizationWidth`: muestra una spline de editor más ancha.

Los números de punto y segmento son componentes de depuración generados y se limpian con el mismo sistema de etiquetas utilizado para la geometría generada.

## Track Shape Editor

Abra **Tools > Track Tools > Track Shape Editor** cuando necesite una superficie de creación de múltiples diseños compacta en lugar de editar solo los puntos spline brutos del actor. El editor trabaja en un documento nativo `track_shape.v1` y puede aplicar diseños compilados principales, de boxes, alternativos o de carreteras de servicio al actor `ASplineGeneratingActor` seleccionado.

La sección **Designer Tools** proporciona los controles de edición diarios:

- agregar diseños de boxes, alternativos o carreteras de servicio
- duplicar o eliminar el diseño no principal seleccionado
- cambiar el tipo de diseño y el estado de bucle cerrado
- seleccionar el diseño, ancla o segmento anterior o siguiente
- editar coordenadas X/Y del ancla seleccionada
- agregar, insertar o eliminar anclas manteniendo un recuento mínimo válido de anclas
- agregar o eliminar segmentos explícitos, cambiar segmentos seleccionados entre línea y bézier, o reconstruir segmentos secuenciales para el diseño seleccionado

El visor admite la selección directa de anclas y el arrastre. La lista de diseños y el inspector reflejan la misma selección, y la sección JSON aún puede importar o exportar el documento subyacente para revisión o control de código fuente.

Utilice **Validate** antes de aplicar ediciones complejas. Utilice **Apply** solo después de seleccionar o crear el actor de destino, ya que la aplicación modifica el estado de spline/diseño editable del actor.

## Compilación

Utilice:

- **Build Now** / `BuildTrack`: compilación síncrona completa.
- **Rebuild** / `RebuildTrack`: asíncrono si `bUseAsyncBuild` es verdadero, de lo contrario síncrono.
- **Cancel** / `CancelAsyncBuild`: cancela una compilación asíncrona activa o pendiente.

El actor se recompila a partir de un plan calculado `FTrackBuildPlan`. El plan decide rangos de segmentos, recuentos de piezas, estado de desniveles, huecos de salto, malla de carretera seleccionada y recuento de mallas adicionales antes de que comience la generación.

## Compilación asíncrona

Configuraciones:

- `bUseAsyncBuild`: habilita la compilación por lotes.
- `SegmentsPerTick`: número de piezas generadas de carretera/malla adicional procesadas por tic.
- `bAutoRebuildOnConstruction`: programa recompilaciones cuando ocurren cambios de construcción.

Los mundos del editor suavizan los cambios de construcción antes de borrar o preparar componentes generados, lo que mantiene la geometría spline existente editable mientras arrastra puntos. Los mundos en tiempo de ejecución utilizan una bomba de temporizador en el siguiente tic. Ambos caminos llaman al mismo generador a nivel de pieza, por lo que el comportamiento se mantiene alineado sin dejar que un segmento spline largo monopolice un fotograma.

## Datos por segmento

`TrackSplineData` configura cada segmento. Si hay menos entradas que segmentos spline, se utiliza el índice `0` como reserva.

Campos importantes:

- `RoadMesh`: malla de carretera específica por segmento opcional.
- `MeshInstances`: número exacto de piezas de malla para el segmento.
- `RoadMeshLength`: longitud de cobertura deseada de la pieza de carretera.
- `SegmentLength`: espaciado de reserva cuando `RoadMeshLength` no está configurado.
- `ExtraMeshStart`, `ExtraMesh`, `ExtraMeshEnd`: mallas spline adicionales.
- `ExtraMeshOffset`: desplazamientos laterales para ranuras de malla adicional.
- `GroundWallSettings`: comportamiento de muros de contención por segmento.

## Mallas adicionales

Las mallas adicionales siguen el mismo intervalo de pieza spline que la pieza de carretera. Son útiles para guardarrailes, bordillos, cercas y objetos laterales decorativos.

Los arreglos de inicio, medio y fin permiten diferentes mallas en los límites de los segmentos. Las mallas adicionales se etiquetan con `AsyncSplineBuilder.ExtraMesh`, no `AsyncSplineBuilder.RoadMesh`.

## Huecos (Gaps)

Agregue entradas a `JumpGapsByPoints` para suprimir la generación de carretera y mallas adicionales para rangos de índices de puntos.

Los rangos son rangos de segmentos:

```text
[StartPointIndex, EndPointIndex)
```

Por ejemplo, `StartPointIndex = 2`, `EndPointIndex = 4` suprime los segmentos `2` y `3`.

## Desniveles (Drops)

Agregue entradas a `StuntDropsByPoints` para mover rangos de segmentos hacia abajo o a un Z absoluto en el mundo.

Campos:

- `DropHeight`: desplazamiento Z relativo. Los valores negativos mueven la carretera hacia abajo.
- `bUseConstantGapHeight`: utiliza Z absoluto en el mundo en lugar del desplazamiento.
- `ConstantGapWorldZ`: altura absoluta cuando está habilitado.

Si dos segmentos adyacentes sin hueco se encuentran a diferentes alturas, el actor crea un muro de desnivel entre ellos.

## Muros de contención

Habilite `bGenerateGroundWalls` para generar tiras de muro procedimentales hacia abajo desde el borde de la carretera.

Muros de contención:

- Utilizan el ancho de carretera derivado de la malla o reemplazado.
- Respetan la configuración de muro por segmento.
- Dividen las tiras en huecos de salto y muestras no válidas.
- Pueden ser de un solo lado o de doble lado.
- Utilizan UV basados en la distancia y la altura real del muro.

Consulte [LandscapeAndWalls.md](LandscapeAndWalls.md) para la configuración detallada.

## Ajuste al terreno

Ajuste de mallas:

- `bSnapMeshesToLandscape`
- `ObjectsToHitForLandscapeLineTrace`
- `LineTraceLength`

Ajuste de puntos:

- `bSnapPointsToLandscape`
- `bTangentPointsUpdate`

Utilice `ActorsToIgnoreForGenerationTraces` para excluir mallas de ayuda u objetos temporales de las consultas de trazado.

## Deformación de terreno

La deformación exclusiva del editor se ejecuta con `DeformLandscapeNow`.

Requisitos:

- `Landscape` asignado.
- Una spline válida.
- Valores razonables de `FallOff` y `NumberOfSubdivisionsForDeform`.
- `bRaiseHeights` y/o `bLowerHeights` habilitados.

Altura: `DeformLandscapeNow` o panel **Deform Height**. Pintura de capas: asigne `PaintLayer`, ajuste `PaintHalfWidth` / `PaintFallOff` en el panel, luego `PaintLandscapeLayerNow` o panel **Paint Layer**. La pintura es aditiva; no borra bandas más anchas anteriores cuando reduce la atenuación. `PaintFallOff = 0` da un borde duro. Si la información de capa seleccionada usa `bNoWeightBlend`, el panel/validación advierte que no se garantiza que otras capas del terreno se reduzcan debajo de la carretera.

## Cuándo usar el panel Details

El panel de flujo de trabajo está enfocado intencionalmente. Utilice el panel Details cuando necesite editar:

- arreglos `ExtraMeshStart`, `ExtraMesh`, `ExtraMeshEnd` y `ExtraMeshOffset` por segmento
- `FGroundWallSettings` detallados, incluyendo reemplazos de trazado, UV, material, colisión y ancho
- arreglos de objetos de trazado para ajuste a terreno y generación de muros
- campos de lectura/escritura de activos de datos de puntos spline
- configuraciones avanzadas de depuración y construcción

## Conectores de diseño

La pestaña Build incluye una sección **Layout Connectors** para metadatos pasivos de ruta. Un conector vincula un diseño/distancia de origen con un diseño/distancia de destino y almacena un tipo semántico como `PitEntry`, `PitExit`, `Link` o `ServiceAccess`. También puede escribir un tipo personalizado; los tipos personalizados no vacíos se validan como advertencias en lugar de errores.

Utilice **Pit Entry** para agregar un conector predeterminado de `Main` al primer diseño de carril de boxes. Utilice **Pit Exit** para agregar un conector predeterminado del primer diseño de carril de boxes de regreso a `Main`. **Validate** en esta sección ejecuta validación exclusiva de conectores.

Las ediciones de conectores no recompilan la carretera ni eliminan geometría generada. Tampoco crean mallas de transición automáticas, no cortan splines, no extienden la deformación del terreno a los carriles de boxes ni habilitan un renderizador especial de boxes.

Habilite **Show Connector Debug** para colocar marcadores de texto solo visuales en los extremos de conectores válidos. Un marcador identifica el índice y tipo de conector, si es el rol `From` o `To`, su id de diseño y su distancia; su tamaño sigue `DebugTextWorldSize`.

Los diseños faltantes y las distancias fuera de rango de una spline se omiten; utilice **Validate** para inspeccionar esos problemas.

Los marcadores utilizan salidas de depuración `UTextRenderComponent` y no agregan geometría de carretera, malla adicional, muro de contención o muro de desnivel. La edición de conectores actualiza los marcadores mientras la casilla de verificación está habilitada. Deshabilite **Show Connector Debug** para eliminar solo las etiquetas de conectores. Alternar o actualizar estas etiquetas no recompila la pista, no cambia los recuentos de componentes de carretera, no extiende el comportamiento del terreno ni afecta la puerta de validación de compilación.

## Flujo de trabajo de activos de datos

Asigne un `USplinePointListAsset` a `SplinePointList`.

Utilice:

- `WriteSplineToDataAsset`: guarda los puntos spline actuales.
- `ReadSplineFromDataAsset`: carga puntos spline.

Esto es útil para preservar los diseños de pistas de forma independiente de los componentes generados.

## Flujo de trabajo de producción recomendado

1. Compile una spline de prueba corta.
2. Valide los límites de la malla de carretera y la repetición.
3. Agregue datos por segmento.
4. Agregue mallas adicionales.
5. Agregue huecos y desniveles.
6. Configure el trazado de muros de contención.
7. Ejecute la deformación de terreno solo después de que la forma de la carretera sea estable.
8. Ejecute pruebas de automatización antes del lanzamiento.
9. Pruebe el nivel en PIE y en la versión empaquetada en tiempo de ejecución.

## Lo que el complemento no hace

- No proporciona modos de pintura de terreno reemplazar/borrar o por segmento.
- No crea mallas por usted.
- No garantiza hombros de terreno perfectos en todos los terrenos.
- No genera mallas de carretera de transición de conectores automáticamente.
- No reemplaza la dirección artística manual para el retoque final de la pista.

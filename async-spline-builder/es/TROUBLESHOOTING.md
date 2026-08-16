<!-- doc-provenance: product-facts.yml reconciled 2026-07-15; source AKDB:plugins/AsyncSplineBuilder/architecture.md -->
# Solución de problemas

## El actor no compila nada

Verifique:

- `MainMesh` está asignado.
- La spline tiene al menos dos puntos.
- La validación no bloqueó la compilación.
- `bEditSpline` no está borrando intencionalmente los componentes generados.
- Las mallas generadas no están ocultas por visibilidad de nivel o visibilidad de actor.

## La compilación está bloqueada por validación

La validación bloquea compilaciones defectuosas y destructivas. Causes comunes:

- `MainMesh` falta.
- Los muros de contención están habilitados pero no se configuraron tipos de objetos de trazado para muros.
- El ajuste al terreno está habilitado pero no se configuraron tipos de objetos de trazado para terreno.
- Los rangos de huecos de salto o desniveles no son válidos.

Corrija la configuración y ejecute `RebuildTrack` de nuevo.

## La validación de conectores informa problemas

Connector Validation Reports Issues ocurre cuando un conector de diseño pasivo apunta a un actor faltante, un id de diseño desconocido, una distancia spline no válida o metadatos de conector incompletos.

Corrija el registro del conector en el panel de flujo de trabajo o en el panel Details, luego ejecute `Validate Layout Connectors` de nuevo. La validación de conectores es independiente de la generación de geometría: los registros de conectores describen la intención de la ruta y no crean mallas de transición por sí mismos.

## Falta una etiqueta de extremo de conector

Habilite **Show Connector Debug** en la sección **Layout Connectors** del panel. Si solo aparece un lado de un conector, ejecute **Validate Layout Connectors** y corrija el diseño faltante o la distancia fuera de rango informada para el extremo oculto. Los extremos se resuelven de forma independiente y las posiciones no válidas se omiten intencionalmente.

Las etiquetas de conectores son solo visuales. No necesita recompilar la pista para crearlas o actualizarlas, y corregir una etiqueta no agrega geometría de carretera de conector ni cambia el comportamiento del terreno.

## El panel de flujo de trabajo no se abre

Ábralo a través de **Tools > Track Tools > Async Spline Builder**. Si falta la entrada del menú:

- recompile el destino del editor
- confirme que el módulo `AsyncSplineBuilderEditor` esté habilitado
- reinicie el editor después de habilitar el complemento
- verifique el Output Log para ver si hay errores de inicio de `AsyncSplineBuilderEditor`

El panel es exclusivo del editor y no está disponible en compilaciones empaquetadas.

## El editor se congela durante Rebuild

Utilice configuraciones asíncronas:

- `bUseAsyncBuild = true`
- reduzca `SegmentsPerTick`
- deshabilite colisiones de muros costosas durante la iteración
- reduzca `GroundWallSubdivisions`

Los recuentos de componentes muy grandes aún pueden ser costosos porque el registro de componentes de Unreal ocurre en el hilo del juego (game thread).

## Las mallas adicionales aparecen en el lugar equivocado

Verifique:

- pivote de la malla y ejes locales
- `ExtraMeshOffset`
- `bMirrorExtraMesh`
- reserva de datos de segmento al índice `0`
- si los arreglos inicio/medio/fin contienen mallas diferentes

Las mallas adicionales utilizan el mismo intervalo spline que la pieza de carretera.

## Las mallas de carretera se estiran demasiado

Configure uno de los siguientes campos:

- `MeshInstances` para un número exacto
- `RoadMeshLength` para una longitud de pieza explícita
- `SegmentLength` para un recuento automático desde el espaciado deseado

Si ninguno está configurado, se utiliza la dimensión X de los límites de la malla.

## El bucle cerrado tiene una costura defectuosa

Verifique:

- posiciones/tangentes del primer y último punto spline
- pivote de la malla y longitud de repetición
- uso de `StartMesh` en bucles cerrados
- configuraciones de suavizado de tangentes

Los bucles cerrados compilan un segmento de envoltura a la longitud de la spline.

## Los muros de contención no aparecen

Verifique:

- `bGenerateGroundWalls` habilitado en el actor
- `GroundWallSettings.bGenerateGroundWalls` por segmento
- `GroundWallObjectsToHitForLineTrace`
- `TraceSettings.ObjectsToHit` por segmento
- longitud de trazado
- `MinWallHeight`
- huecos de salto

Si los trazados fallan, se utiliza la profundidad de reserva. Si la altura del muro sigue estando por debajo de `MinWallHeight`, no se crea ninguna sección.

## Los muros de contención salvan los huecos

No deberían. Si observa esto, confirme que el rango de hueco utiliza la semántica de segmentos:

```text
[StartPointIndex, EndPointIndex)
```

También ejecute la suite de automatización; `GroundWallGapStripValid` cubre el comportamiento básico de división de tiras.

## El ancho del muro de contención es incorrecto

El ancho se deriva de los límites Y de la malla de carretera seleccionada a menos que `TrackHalfWidth` sea mayor que cero. Si los límites de la malla no son representativos, configure `TrackHalfWidth` manualmente.

## Los muros de desnivel no aparecen

Verifique:

- ambos segmentos vecinos tienen carretera
- el límite no está dentro de un hueco de salto
- los segmentos adyacentes se resuelven en valores Z absolutos del mundo diferentes
- `DropHeight` o Z constante está configurado en un lado

Ejecute `AsyncSplineBuilder.DropWallCount` para el comportamiento básico de muros de desnivel.

## El ajuste al terreno no hace nada

Verifique:

- `bSnapMeshesToLandscape` o `bSnapPointsToLandscape` está habilitado
- `ObjectsToHitForLandscapeLineTrace` tiene tipos de objetos
- el tipo de objeto de colisión del terreno coincide con la consulta
- `ActorsToIgnoreForGenerationTraces` no incluye el destino
- la longitud de trazado alcanza la superficie

## La deformación de terreno no hace nada

Verifique:

- `Landscape` está asignado
- el módulo del editor está cargado
- la spline tiene puntos válidos
- `NumberOfSubdivisionsForDeform` es mayor que cero
- al menos uno de `bRaiseHeights` o `bLowerHeights` está habilitado
- la carretera se superpone con el área del terreno

Recuerde: la deformación es una acción manual en el editor a través de `DeformLandscapeNow`.

## La capa de material del terreno no se pinta

La deformación de altura (`DeformLandscapeNow`) y la pintura de peso de capa (`PaintLandscapeLayerNow`) son acciones separadas. La pintura de capa requiere un `PaintLayer` válido registrado en el terreno. El deshacer es administrado por la transacción del deformador; pruebe el deshacer en el panel, en CallInEditor y con una capa de edición de terreno activa.

Si la información de capa seleccionada usa `bNoWeightBlend`, la operación debería advertir. En esa configuración la capa de destino puede recibir pintura, pero no se garantiza el comportamiento habitual "las otras capas se reducen debajo de la carretera".

## La geometría generada se duplica después de Rebuild

Los componentes generados se limpian mediante etiquetas. Si aparecen duplicados:

- verifique si el código personalizado crea componentes sin `GeneratedTag`
- verifique si un componente modificado se duplicó manualmente
- ejecute la automatización `CleanupRemovesAllTagged`

## El proceso asíncrono en tiempo de ejecución no se completa

Verifique:

- `bUseAsyncBuild = true`
- el administrador de temporizadores del mundo está ejecutando tics
- el actor es válido y no está destruido
- `SegmentsPerTick` es al menos `1`
- la validación no abortó antes de comenzar

La bomba en tiempo de ejecución se vuelve a armar con `SetTimerForNextTick` mientras compila.

## BuildPlugin o la compilación falla con colisiones Unity

Algunos módulos definen asistentes con nombres similares en espacios de nombres anónimos. Si la agrupación Unity combina esos archivos, MSVC puede informar definiciones duplicadas. El módulo afectado debe utilizar configuraciones de compilación fuera de Unity como `bUseUnity = false`.

## La automatización no encuentra pruebas

Verifique:

- se compiló el destino del editor
- las pruebas de automatización de desarrollo están habilitadas
- el comando usa `Automation RunTests AsyncSplineBuilder`
- las pruebas están compiladas en el módulo del editor

## Los registros hacen demasiado ruido

Busque en el registro:

```text
AsyncSplineBuilder
Result={Fail}
Result={Success}
TEST COMPLETE
```

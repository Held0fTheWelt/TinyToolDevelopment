<!-- doc-provenance: product-facts.yml reconciled 2026-07-15; source AKDB:plugins/AsyncSplineBuilder/architecture.md -->
# FAQ

## ¿Para qué se utiliza Async Spline Builder?

Construye mallas a lo largo de una spline, como carreteras, pistas de carreras, rieles, tuberías, barreras y muros de contención procedimentales. Su principal ventaja es el procesamiento por lotes asíncrono, por lo que las splines largas se pueden recompilar sin causar un bloqueo prolongado en el editor.

## ¿Funciona en tiempo de ejecución?

Sí. Las mallas de carretera, mallas adicionales, muros de contención, muros de desnivel y la bomba asíncrona en tiempo de ejecución residen en el módulo en tiempo de ejecución. La deformación de altura de terreno exclusiva del editor no está disponible en compilaciones empaquetadas.

## ¿Qué orientación debe usar mi malla de carretera?

Cree mallas de carretera repetibles a lo largo del eje X local. El generador utiliza los límites de la malla en X para la longitud predeterminada y los límites en Y para el ancho predeterminado.

## ¿Puedo usar diferentes mallas por segmento?

Sí. Agregue entradas a `TrackSplineData` y configure `RoadMesh`, `RoadMeshLength`, `SegmentLength`, `MeshInstances` y los arreglos de mallas adicionales por segmento. Los datos de segmento faltantes se remiten a la entrada `0`.

## ¿Dónde configuro el complemento?

Utilice **Tools > Track Tools > Async Spline Builder** para el flujo de trabajo normal. Le ofrece selección de actor, configuración de mallas, validación, controles de compilación, configuraciones asíncronas, interruptores de visualización de spline, asistentes de segmento, acciones de terreno y habilitación de muros de contención en un solo panel. Utilice el panel Details para arreglos avanzados por segmento y campos detallados de trazado, muro, colisión, UV y activos de datos.

## ¿Cuál es la diferencia entre BuildTrack y RebuildTrack?

`BuildTrack` es síncrono e inmediato. `RebuildTrack` utiliza procesamiento por lotes asíncrono cuando `bUseAsyncBuild` está habilitado.

## ¿La generación asíncrona utiliza hilos de trabajo (worker threads)?

No. Distribuye el trabajo entre tics. Esto mantiene la creación de componentes de Unreal en el hilo del juego (game thread), que es el lugar adecuado para registrar instancias de `UActorComponent`.

## ¿Puede crear guardarrailes o mallas laterales?

Sí. Utilice `ExtraMeshStart`, `ExtraMesh`, `ExtraMeshEnd` y `ExtraMeshOffset` en `FTrackSplineData`.

## ¿Puede crear saltos o secciones de carretera faltantes?

Sí. Utilice `JumpGapsByPoints`. Los huecos suprimen las mallas de carretera y adicionales para rangos de segmentos.

## ¿Puede crear desniveles de altura?

Sí. Utilice `StuntDropsByPoints`. Los segmentos adyacentes sin hueco situados a diferentes alturas crean muros de desnivel.

## ¿Puede crear muros hasta el suelo?

Sí. Habilite `bGenerateGroundWalls` y configure los tipos de objetos de trazado. Las tiras de muro procedimentales trazan desde los bordes de la carretera hacia abajo hasta los tipos de objetos configurados.

## ¿Deforma los terrenos?

Sí, en el editor. Utilice `DeformLandscapeNow` para la altura y `PaintLandscapeLayerNow` (o el panel **Paint Layer**) para la pintura de peso aditiva cuando `PaintLayer` está asignado.

## ¿Pinta capas de terreno?

Sí, para una sola capa global `PaintLayer` utilizando pintura aditiva `max`. Configure `PaintLayer` en el actor, asigne el terreno y luego ejecute **Paint Layer**. La información de capa con mezcla de peso reduce otras capas debajo de la carretera. La información de capa con `bNoWeightBlend` puede pintar la capa de destino, pero no garantiza que otras capas se reduzcan. No admitido: modo reemplazar/borrar, capas de pintura por segmento o borrado automático de pesos antiguos al reducir la banda de pintura.

## ¿Por qué la validación bloqueó mi compilación?

El actor bloquea compilaciones en caso de una mala configuración destructiva, como la falta de `MainMesh` o características basadas en trazado habilitadas sin tipos de objetos de trazado. Esto protege la geometría generada existente de ser borrada antes de que se pueda crear un reemplazo válido.

## ¿Por qué faltan mis muros?

Las causas comunes son tipos de objetos de trazado faltantes, ausencia de impactos de trazado, `MinWallHeight` demasiado alto, huecos de salto que cortan la tira o `bGenerateGroundWalls` deshabilitado en la configuración por segmento.

## ¿Limpia los componentes generados de forma segura?

Sí. Los componentes generados reciben etiquetas estables y la limpieza escanea las etiquetas en lugar de confiar solo en arreglos temporales.

## ¿Puedo guardar el diseño de la spline?

Sí. Asigne `SplinePointList` y utilice `WriteSplineToDataAsset` / `ReadSplineFromDataAsset`.

## ¿Puedo usarlo para productos Fab o juegos comerciales?

Sí, sujeto a los términos de la licencia del producto. El complemento no otorga derechos sobre mallas, materiales o contenidos de terceros que utilice con él.

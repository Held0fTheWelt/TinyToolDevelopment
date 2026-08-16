<!-- doc-provenance: product-facts.yml reconciled 2026-07-15; source AKDB:plugins/AsyncSplineBuilder/architecture.md -->
# Documentación de Async Spline Builder

Async Spline Builder genera mallas spline para carreteras, pistas de carreras, tuberías, rieles, muros y objetos secundarios sin causar bloqueos prolongados en el editor. Admite compilaciones síncronas, procesamiento por lotes asíncrono en el editor, procesamiento por lotes asíncrono en tiempo de ejecución, planes de malla por segmento, muros de contención opcionales, huecos de salto, muros de desnivel, activos de datos de puntos spline y deformación de altura de terreno exclusiva del editor más pintura de capas aditiva.

Esta carpeta contiene la documentación entregada con el complemento.

## Empiece aquí

- [BUYER_GUIDE.md](BUYER_GUIDE.md): descripción general a nivel de producto, flujos de trabajo, fortalezas y limitaciones.
- [UserManual.md](UserManual.md): flujo de trabajo completo en el editor desde la primera colocación del actor hasta las recompilaciones.
- [FAQ.md](FAQ.md): preguntas y respuestas preparadas para Fab.

## Referencia

- [SettingsReference.md](SettingsReference.md): cada configuración importante del actor y la línea base recomendada.
- [LandscapeAndWalls.md](LandscapeAndWalls.md): ajuste, deformación de altura, muros de contención, huecos y muros de desnivel.
- [TechnicalOverview.md](TechnicalOverview.md): arquitectura a nivel de mantenedor y flujo de compilación.
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md): problemas comunes de configuración, compilación, trazado y geometría.

Las auditorías exclusivas de mantenedores, notas de finalización, comandos de automatización, notas heredadas y listas de verificación de lanzamiento pueden existir en el repositorio fuente, pero se excluyen del paquete del comprador.

## Flujo de trabajo rápido

1. Habilite el complemento y reinicie el editor si es necesario.
2. Abra **Tools > Track Tools > Async Spline Builder**.
3. Coloque o seleccione un `ASplineGeneratingActor` desde el panel de flujo de trabajo.
4. Asigne `MainMesh` en la sección de configuración del panel.
5. Edite los puntos de la `TrackSpline` en el visor.
6. Use **Build Now** para una compilación inmediata o **Rebuild** para procesamiento por lotes asíncrono.
7. Use los asistentes de segmento para crear filas por segmento antes de realizar ediciones avanzadas por segmento.
8. Opcional: habilite muros de contención y configure tipos de objetos de trazado en el panel Details.
9. Opcional: asigne un terreno, ejecute **Deform Height**, luego **Paint Layer** (requiere `PaintLayer` en el actor) para pintura de peso aditiva.

## Características principales

- Generación de mallas de carretera o pista a lo largo de una spline.
- Track Shape Editor para la creación nativa de puntos de ruta/diseño con controles de diseñador para diseños, anclas y segmentos.
- Validate Layout Connectors para revisar metadatos pasivos de conectores (`PitEntry`, `PitExit`, `Link`, `ServiceAccess` o personalizados) antes de confiar en las relaciones de ruta.
- Apply Layout Connector para agregar o actualizar registros pasivos de relaciones de diseño sin crear ramas de malla ocultas.
- Recompilaciones asíncronas en el editor con `SegmentsPerTick`.
- Recompilaciones asíncronas en tiempo de ejecución mediante una bomba de temporizador en el siguiente tic.
- Selección de malla por segmento y planificación de longitud de malla.
- Mallas adicionales de inicio, medio y fin para guardarrailes, barreras, cercas, tuberías o mallas de detalle.
- Huecos de salto que suprimen las mallas de carretera y laterales.
- Regiones de desnivel y muros de desnivel procedimentales entre escalones de altura.
- Muros de contención procedimentales que trazan hacia abajo hasta el terreno u otros tipos de objetos configurados.
- Limpieza de componentes generados basada en etiquetas que sobrevive a arreglos obsoletos y recompilaciones de construcción.
- Guardado/carga de puntos spline mediante `USplinePointListAsset`.
- Deformación de altura de terreno exclusiva del editor más pintura de capas global aditiva.
- Pruebas de automatización para los comportamientos de mayor riesgo.

## Posición en tiempo de ejecución compatible

El módulo en tiempo de ejecución contiene el actor, la generación de mallas spline, la generación de muros de contención, la generación de muros de desnivel, el acceso a activos de datos y la bomba asíncrona en tiempo de ejecución.

El módulo del editor contiene el panel de flujo de trabajo, la deformación de terreno y pintura de capas exclusivas del editor, y los asistentes de selección del editor. Los juegos empaquetados pueden compilar las mallas spline y los muros procedimentales, pero las ediciones de altura/peso del terreno y el panel de flujo de trabajo son exclusivos del editor.

## Panel de flujo de trabajo del editor

La superficie principal del editor es **Tools > Track Tools > Async Spline Builder**. Agrupa el flujo de trabajo común en las pestañas **Build**, **Segments** y **Terrain** para que las tareas diarias se mantengan compactas sin ocultar el estado de validación.

Utilice el Track Shape Editor cuando una ruta necesite creación nativa de puntos/diseño y utilice controles de conectores de diseño cuando los carriles de boxes, accesos de servicio o rutas alternativas necesiten metadatos de relación explícitos.

Utilice el panel para el trabajo diario. Utilice el panel Details de Unreal para campos brutos avanzados como arreglos de mallas adicionales por segmento, configuraciones detalladas de UV de muro, arreglos de objetos de trazado, configuraciones de colisión personalizadas y campos experimentales.

## Limitaciones importantes

- Terreno: deformación de altura más pintura de peso de capa **global aditiva** cuando `PaintLayer` está configurado (`PaintLandscapeLayerNow` o panel **Paint Layer**). El modo de pintura reemplazar/borrar no está implementado.
- La deformación de terreno es una operación puntual en el editor, no una parte automática de cada recompilación de pista.
- Los terrenos de producción complejos aún necesitan control de calidad manual, especialmente en curvas cerradas, terrenos muy escarpados y configuraciones de muros mixtas por segmento.
- La automatización asíncrona en tiempo de ejecución se cubre mediante un gancho de prueba determinista; aún se recomienda un pase de integración completo en un mundo PIE con temporizador para mapas de lanzamiento.

## Validación

Para un pase de validación de paquete local, compile el destino del editor para su proyecto y ejecute el grupo de automatización AsyncSplineBuilder desde las herramientas de automatización de Unreal. Mantenga las rutas de comandos específicas del mantenedor en las notas de lanzamiento locales en lugar de en el paquete entregado al comprador.

## Primer pase de producción recomendado

Utilice primero una spline de prueba abierta corta, luego un bucle cerrado y finalmente la pista real. Mantenga `bUseAsyncBuild` habilitado, comience con `SegmentsPerTick = 2` y auméntelo solo después de confirmar la capacidad de respuesta del editor. Configure los tipos de objetos de trazado antes de habilitar el ajuste o los muros de contención, porque la validación bloquea intencionalmente las compilaciones que de otro modo destruirían la geometría antigua sin producir un reemplazo válido.

## Nota legal

Async Spline Builder se proporciona bajo los términos de licencia incluidos con la distribución del producto. El complemento no otorga derechos sobre mallas, materiales, terrenos o contenidos de terceros utilizados con las pistas generadas.

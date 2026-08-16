<!-- doc-provenance: AKDB:plugins/ProceduralGeneratedStructures/architecture.md; docs/architecture/plugins/ProceduralGeneratedStructures/product-facts.yml; reconciled 2026-06-21 -->
# Documentación de ProceduralGeneratedStructures

ProceduralGeneratedStructures construye estructuras de malla estática instanciada reutilizables a partir de un activo de datos. El actor en tiempo de ejecución puede leer instancias existentes de `UInstancedStaticMeshComponent` en un `UProceduralStructureDataAsset`, y luego recompilar esas instancias explícitas o generar estructuras adicionales basadas en filas. También expone datos del plan de compilación y estadísticas para que pueda inspeccionar componentes de destino, problemas de bloqueo, intención de mutación, progreso asíncrono y recuentos exactos de instancias tras la poda (pruning) antes de aplicar una recompilación.

## Documentación

- [QUICKSTART.md](QUICKSTART.md): instalar → colocar actor → capturar y recompilar, con resultados esperados.
- [UserManual.md](UserManual.md): flujo de trabajo completo, objetos principales y notas de compilación.
- [SettingsReference.md](SettingsReference.md): cada propiedad del actor y campo de activo de datos.
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md) · [FAQ.md](FAQ.md)
- [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md): declaración de software de terceros (ninguno incluido).

## Activos principales

- `AAsyncProceduralGeneratedActor` posee el flujo de trabajo de compilación y puede recompilar componentes de forma síncrona o a través de tics del editor/juego.
- `UProceduralStructureDataAsset` almacena entradas de malla con nombre con transformaciones explícitas y reglas opcionales de generación de filas.
- `FInstancedComponentConfiguration` mapea un componente de malla instanciada con nombre en el actor a una entrada de activo de datos almacenada.
- `FProceduralStructureBuildPlan` y `FProceduralStructureElementStats` exponen datos de vista previa exactos para herramientas, Blueprints y rutas UCM.

## Notas de compilación

- Las transformaciones explícitas leídas desde los componentes de la escena se reproducen exactamente y no se vuelven a centrar durante la recompilación.
- Las transformaciones de filas generadas se pueden centrar alrededor del origen XY local con `bCenterGeneratedTransforms`.
- `InstancesPerFrame` limita cuántas instancias se agregan por tic cuando la compilación asíncrona está habilitada.
- Los recuentos de filas se limitan a valores no negativos antes de la generación.
- Los planes de compilación informan la capacidad de filas generadas antes de la poda y el recuento exacto generado después de la poda.

## Flujo de trabajo recomendado

1. Agregue un `AAsyncProceduralGeneratedActor` a un nivel o blueprint.
2. Agregue uno o más componentes secundarios `UInstancedStaticMeshComponent` con nombres de componentes estables.
3. Asigne un `UProceduralStructureDataAsset`.
4. Configure `ReadInComponentConfiguration` para capturar las instancias de componentes existentes.
5. Configure `ComponentConfiguration` para recompilar esas entradas.
6. Inspeccione `GetBuildPlan` o la ruta de vista previa, luego use las acciones de lectura, borrado y compilación invocables en el editor para iterar en la estructura.

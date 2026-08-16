<!-- doc-provenance: AKDB:plugins/ProceduralGeneratedStructures/architecture.md; docs/architecture/plugins/ProceduralGeneratedStructures/product-facts.yml; reconciled 2026-06-21 -->
# Solución de problemas

## Habilité el complemento pero no pasa nada

El complemento agrega la clase `AAsyncProceduralGeneratedActor` y el `UProceduralStructureDataAsset`.
Coloque el actor en un nivel (Place Actors → *Async Procedural Generated Actor*); no hay menú —
el flujo de trabajo reside en el panel Details del actor.

## La compilación no produce instancias

- Confirme que el actor tenga al menos un componente secundario `UInstancedStaticMeshComponent` con un **nombre estable**.
- Confirme que **ComponentConfiguration** tenga una entrada cuyo **Name** coincida con ese componente.
- Confirme que la entrada del activo de datos tenga asignada una **Mesh** válida.
- Si utiliza lectura, asegúrese de haber capturado primero (**bReadInMeshComponentData**) con una entrada **ReadInComponentConfiguration** coincidente.
- Inspeccione **GetBuildPlan**. Informa códigos de problemas precisos como `component_not_found:<Name>`, `data_asset_element_not_found:<Name>` y `data_asset_element_missing_mesh:<Name>`.

## La vista previa informa un recuento de instancias muy alto

El plan de compilación informa tanto las instancias potencialmente generadas antes de la poda como el recuento exacto generado después de la poda. Si ambos son demasiado altos, reduzca los recuentos de filas, agregue poda (pruning) o habilite **bUseAsyncBuild** y reduzca **InstancesPerFrame**.

## Las instancias capturadas se movieron/descentraron inesperadamente

Las instancias explícitas capturadas se reproducen exactamente y nunca se vuelven a centrar. Solo las transformaciones de **filas generadas** se ven afectadas por **bCenterGeneratedTransforms**.

## La compilación congela el editor / juego en estructuras grandes

Habilite **bUseAsyncBuild** y reduzca **InstancesPerFrame** para que las instancias se agreguen a través de múltiples tics en lugar de un solo pase bloqueante.

## La lectura capturó el componente equivocado

`ReadInComponentConfiguration` coincide por el **Name** del componente. Asegúrese de que los nombres de los componentes sean estables y únicos, y que el `Name` de la entrada de configuración coincida exactamente.

## La cuadrícula generada tiene huecos

Verifique los arreglos `Pruned*` en la información de la fila — los índices/instancias podados se omiten intencionalmente. Bórrelos para generar una cuadrícula completa.

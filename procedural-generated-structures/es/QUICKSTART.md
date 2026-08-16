<!-- doc-provenance: AKDB:plugins/ProceduralGeneratedStructures/architecture.md; docs/architecture/plugins/ProceduralGeneratedStructures/product-facts.yml; reconciled 2026-06-21 -->
# Guía de inicio rápido

Esta guía lo lleva desde la instalación hasta un **resultado visible**: un `AAsyncProceduralGeneratedActor` que recompila estructuras de malla instanciada a partir de un activo de datos. El complemento funciona de forma autónoma — no se requiere ningún otro complemento.

## Lo que tendrá después de esta guía

Un actor en su nivel cuyas instancias de malla estática instanciada se capturan en un activo de datos y se recompilan a partir de él, de modo que la estructura sea reutilizable y regenerable.

## Requisitos

- Editor de Unreal Engine 5 y un nivel abierto.
- Un `UStaticMesh` de su proyecto para instanciar (por ejemplo, una malla de pared o pilar).
- Sin software de terceros, cuenta ni tiempo de ejecución. Consulte [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md).

## 1. Instalar y habilitar

1. Agregue **ProceduralGeneratedStructures** desde su biblioteca de Fab al proyecto (o instálelo en el motor).
2. Abra **Edit → Plugins**, habilite **ProceduralGeneratedStructures** y reinicie cuando se le solicite.

## 2. Colocar el actor (Primer resultado)

1. En el panel **Place Actors**, busque **Async Procedural Generated Actor** y arrástrelo al nivel (o agregue `AAsyncProceduralGeneratedActor` desde la lista de clases).
2. Agregue uno o más componentes secundarios **Instanced Static Mesh Component** al actor y asigne a cada uno un **nombre de componente estable** (por ejemplo, `Walls`). Asigne su malla estática y coloque algunas instancias.

## 3. Un ejemplo práctico real: capturar y recompilar

1. Cree un **Procedural Structure Data Asset** (`UProceduralStructureDataAsset`) en el Content Browser y asígnelo a la propiedad **ProceduralStructure** del actor.
2. En **ReadInComponentConfiguration**, agregue una entrada cuyo **Name** coincida con su componente (`Walls`) y elija un **StructureType** (por ejemplo, `Structure`).
3. Establezca **bReadInMeshComponentData** para capturar las instancias actuales del componente en el activo de datos.
4. En **ComponentConfiguration**, agregue una entrada que mapee el mismo **Name** (`Walls`) de regreso a la entrada del activo de datos.
5. Previsualice con **GetBuildPlan** desde Blueprint/C++ o la ruta de vista previa automatizada. Un plan limpio no tiene problemas de bloqueo e informa el total exacto de instancias que se recompilarán.
6. Recompilar — habilite **bAutoBuildOnConstruction** (recompila en la construcción) o mueva/edite el actor para activar una compilación.

**Resultado esperado:** las mallas instanciadas se recompilan a partir del activo de datos. Las transformaciones explícitas capturadas se reproducen exactamente (nunca se vuelven a centrar). Para iterar, configure **bClearProceduralStructureInformation** para borrar los datos almacenados y capture de nuevo.

## 4. Rendimiento / Asíncrono

- **bUseAsyncBuild**: distribuye la compilación entre fotogramas en lugar de un solo pase bloqueante.
- **InstancesPerFrame**: cuántas instancias se agregan por tic cuando la compilación asíncrona está habilitada.
- **GetBuildProgress** / **GetAddedBuildInstanceCount**: realiza un seguimiento del progreso de la compilación asíncrona para herramientas.
- **bCenterGeneratedTransforms**: centra las transformaciones de *filas generadas* alrededor del origen XY local (las instancias explícitas capturadas nunca se vuelven a centrar).

## 5. Generar estructuras basadas en filas (Opcional)

Más allá de reproducir instancias capturadas, una entrada de activo de datos puede definir **InstancedMeshRows** para generar cuadrículas/filas procedimentalmente (recuentos de filas por dimensión con transformaciones de movimiento por dimensión). Consulte [SettingsReference.md](SettingsReference.md) para cada campo.

## 6. Próximos pasos

- Flujo de trabajo completo y notas de compilación: [UserManual.md](UserManual.md).
- Cada propiedad del actor y campo de activo de datos: [SettingsReference.md](SettingsReference.md).
- Problemas y soluciones: [TROUBLESHOOTING.md](TROUBLESHOOTING.md) y [FAQ.md](FAQ.md).

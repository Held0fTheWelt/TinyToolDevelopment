<!-- doc-provenance: AKDB:plugins/ProceduralGeneratedStructures/architecture.md; docs/architecture/plugins/ProceduralGeneratedStructures/product-facts.yml; reconciled 2026-06-21 -->
# Preguntas frecuentes

**¿Este complemento requiere algún otro complemento?**
No. Funciona de forma totalmente autónoma.

**¿Incluye mallas?**
No. Usted proporciona sus propios activos `UStaticMesh`; el complemento los instancia.

**¿Qué versiones del motor son compatibles?**
Unreal Engine 5.4+ (Win64, Linux, Mac). El módulo es Runtime, por lo que el actor funciona en el editor y en juegos empaquetados.

**¿Incluye software de terceros, Python o modelos de IA?**
No. Consulte [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md).

**¿Cuál es la diferencia entre instancias explícitas y generación de filas?**
Las instancias explícitas son transformaciones exactas (a menudo capturadas de componentes existentes) y se reproducen tal cual. La generación de filas crea procedimentalmente instancias a partir de recuentos de filas y transformaciones de movimiento por dimensión definidas en el activo de datos.

**¿Puedo compilar en tiempo de ejecución, no solo en el editor?**
Sí. El actor es compatible con el tiempo de ejecución y puede compilar de forma síncrona o a través de tics (`bUseAsyncBuild`).

**¿Cómo evito tirones de fotogramas en estructuras grandes?**
Habilite `bUseAsyncBuild` y ajuste `InstancesPerFrame`.

**¿Puedo previsualizar lo que hará una recompilación antes de mutar componentes?**
Sí. Utilice `GetBuildPlan` o la ruta de vista previa de recompilación. El plan informa componentes de destino, problemas de bloqueo, intención de mutación y recuentos exactos de instancias tras la poda.

**¿Las herramientas pueden mostrar el progreso de la compilación asíncrona?**
Sí. `GetEstimatedBuildInstanceCount`, `GetAddedBuildInstanceCount` y `GetBuildProgress` exponen el progreso para herramientas del editor, Blueprints y rutas de automatización.

**¿Dónde puedo informar problemas u obtener soporte?**
Utilice el enlace de soporte en la página del producto en Fab.

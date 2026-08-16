<!-- doc-provenance: SAD architecture.md sections 1,2,7,8; facts product-facts.yml; reconciled 2026-07-16 -->
# Internal Index Service

Internal Index Service (IIS) es un plugin de Unreal Engine para indexación **local**, recuperación (retrieval), paquetes de contexto y búsqueda orientada a agentes. Es solo de lectura (retrieval-only): no modifica el contenido del proyecto ni genera parches.

## Módulos

| Módulo | Propósito |
| --- | --- |
| `InternalIndexServiceInterface` | Contratos públicos para fragmentos (chunks), búsqueda, importaciones, embeddings y acceso de agentes. |
| `InternalIndexService` | Subsistema en tiempo de ejecución del motor, catálogo de fragmentos, backends vectoriales, tareas de embedding, indexación incremental. |
| `InternalIndexServiceEditor` | Panel de control del editor, puente Python y entradas de menú de Tiny Tools. |

## Abrir el panel de control

```text
Tiny Tools -> AI -> Internal Index Service -> Open Internal Index Service
```

O utilice la pestaña nómada **Internal Index Service** si su interfaz ya la muestra.

El panel está organizado de la siguiente manera:

| Pestaña | Propósito |
| --- | --- |
| **Dashboard** | Tarjetas de estado para el índice e integraciones; acciones rápidas (Reconstruir catálogo). |
| **Overview** | Versión del servicio, raíz del índice, presencia de catálogo/vectores. |
| **Imports** | Transferencia UII y resúmenes de informes de importación. |
| **Catalog** | Crear catálogo y mostrar el resumen de creación bajo `Saved/InternalIndexService/reports`. |
| **Embeddings** | Crear y ejecutar tareas de embedding persistentes a través de un `IIISEmbeddingRouteExecutor` detectado. |
| **Search** | Búsqueda léxica / vectorial / híbrida integrada en el índice local. |
| **Agent/MCP** | Contratos de agentes, ID de rutas UCM e instrucciones de acceso MCP a través de Unified MCP Server. |
| **Reports** | Accesos directos a carpetas de informes y registros. |

El encabezado muestra el nombre del proyecto, un marcador de solo lectura, un botón **Settings** y un botón **Refresh**. La actualización pone al día todos los resúmenes de pestañas, fuerza una actualización de las tarjetas del panel y refresca el panel de Gobernanza.

Las tarjetas del panel se actualizan al abrir, mediante un **Refresh** explícito y tras acciones del panel como **Rebuild**. El panel no reconstruye las tarjetas mediante un temporizador periódico, lo que mantiene la interfaz estable mientras se edita o inspecciona.

## Configuración del proyecto

Configure IIS en:

```text
Edit -> Project Settings -> Plugins -> Internal Index Service
```

| Configuración | Predeterminado | Significado |
| --- | --- | --- |
| **Vector Backend** | `jsonl_bruteforce` | Implementación del índice vectorial local (`jsonl_bruteforce` o `hnsw`), con enrutamiento automático fuerza bruta/HNSW según el número de registros. |
| **Index Root (optional)** | *(vacío)* | Anulación para la raíz del índice en disco; vacío utiliza `Saved/InternalIndexService`. |
| **Brute Force Max Records** | `10000` | Umbral de búsqueda exacta antes de utilizar HNSW. |
| **Embedding Executor Id** | *(vacío)* | Ejecutor de embedding preferido. Vacío usa la detección habitual de IIS; el puente opcional IIS LLM Store establece esto en `llmstore` al cargarse. |
| **Vector Storage Format** | `Int8 Per-Vector Scale` | Política de almacenamiento HNSW. Mantenga el valor predeterminado int8 compacto por vector para uso normal; use `Float32` para ejecuciones de alta fidelidad/depuración; use `Experimental Global Scale` solo detrás de la puerta experimental. |
| **Allow Experimental Vector Formats** | `false` | Habilita diseños vectoriales solo de medición que pueden reducir la precisión (recall). |
| **Rebuild On Vector Format Mismatch** | `true` | Reconstruye particiones HNSW persistentes incompatibles en lugar de cargarlas con un diseño de bytes incorrecto. |
| **Quantization Recall Gate** | `0.7` | Límite mínimo de precisión utilizado por las pruebas de automatización de cuantización; auméntelo tras una validación representativa del proyecto. |
| **HNSW M / efConstruction / efSearch** | `16` / `200` / `64` | Ajuste fino de precisión, tiempo de creación, memoria y latencia de consulta para HNSW. |

El acceso MCP lo proporciona Unified MCP Server a través de las rutas Capability Mesh del proyecto. IIS ya no incluye ni requiere un puente UMCP IIS dedicado.

## Integraciones

La ejecución de embeddings se delega a través de `FIISEmbeddingDiscovery` (`IModularFeatures` / `IIISEmbeddingRouteExecutor`). Los plugins puente se registran en `StartupModule` y se dan de baja en `ShutdownModule`. `FIISEmbeddingRouteExecutorRegistry` es un adaptador obsoleto para llamadas heredadas.

La tarjeta **Integrations** del panel lista los ID de ejecutores de `FIISEmbeddingDiscovery::GetExecutorIds()` e indica si cada integración está activa.

El historial de tareas del editor se expone a través de rutas UCM (`iis.editor.jobs.list.v1`, `iis.editor.jobs.status.v1`) en lugar de un proveedor UMCP en tiempo de compilación. La ruta de lista combina el historial del panel con las filas recientes de tareas de embedding en SQLite.

## Documentación relacionada

| Documento | Audiencia |
| --- | --- |
| [QUICKSTART.md](QUICKSTART.md) | Configuración inicial, importación, creación de índices y búsqueda. |
| [UserManual.md](UserManual.md) | Flujo de trabajo completo del editor y comportamiento operativo. |
| [SettingsReference.md](SettingsReference.md) | Configuración, archivos generados y rutas de almacenamiento. |
| [TechnicalOverview.md](TechnicalOverview.md) | Arquitectura y flujo de datos a nivel de mantenedores. |
| [CodeDocumentation.md](CodeDocumentation.md) | Mapa de código C++, clases principales y rutas de ejecución. |
| [INTEGRATION.md](INTEGRATION.md) | Cómo UII, LLM Store y UMCP se conectan con IIS. |
| [FAQ.md](FAQ.md) | Preguntas frecuentes de compradores y revisores. |
| [TROUBLESHOOTING.md](TROUBLESHOOTING.md) | Fallos comunes y soluciones. |
| [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md) | Detalles de declaración de código fuente de terceros para el envío a Fab. |
| [../CHANGELOG.md](../CHANGELOG.md) | Notas de la versión. |

## Empaquetado

`Config/FilterPlugin.ini` incluye `/Documentation/...` para que los compradores reciban esta carpeta en los builds de Fab.
También conserva en la salida empaquetada los metadatos de precompilación generados por BuildPlugin. Cuando IIS se instala en una instalación de Unreal Engine, utilice un paquete creado para esa versión del motor y mantenga intactos sus binarios generados y metadatos.

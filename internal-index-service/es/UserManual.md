<!-- doc-provenance: SAD architecture.md sections 1,5,6,8; facts product-facts.yml; reconciled 2026-07-16 -->
# Manual del usuario

## Flujo de trabajo principal

IIS sigue un flujo de trabajo de recuperación en solo lectura:

1. Importar evidencia preparada.
2. Crear o actualizar el catálogo local.
3. Generar embeddings cuando se requiera búsqueda vectorial.
4. Buscar o crear paquetes de contexto.
5. Exponer las mismas herramientas de solo lectura a los agentes a través de UMCP.

IIS no aplica modificaciones (mutaciones) al proyecto.

## Mapa de funciones del producto

| Función en ficha técnica | Superficie orientada al comprador |
| --- | --- |
| `ImportPreparedChunks` | Importa archivos JSONL de fragmentos preparados desde la pestaña Imports del panel de control o la API del servicio. |
| `Search` | Ejecuta recuperación léxica, vectorial o híbrida desde la pestaña Search y la API del servicio. |
| `BuildContextPack` | Crea paquetes de contexto enfocados en evidencia a partir de una consulta o resultados seleccionados. |
| `RunPerfSelfCheck` | Ejecuta la autocomprobación de rendimiento sintético integrada desde Blueprint/API y superficies de consola. |
| `RuntimeControlDispatch` | Envía comandos observe, tune, act, persist y reset a través de la superficie de control en tiempo de ejecución. |
| `AgentRetrievalTools` | Ofrece operaciones de recuperación de agentes en solo lectura a través de contratos locales y rutas opcionales UCM/UMCP. |

## Panel de control

Abrir:

```text
Tiny Tools -> AI -> Internal Index Service -> Open Internal Index Service
```

Pestañas:

| Pestaña | Uso |
| --- | --- |
| Dashboard | Estado del índice, estado de integración, acceso directo para reconstruir, acceso directo para buscar. |
| Index | Importaciones, creación de catálogo, creación/ejecución de tareas de embedding. |
| Use | Búsqueda en la evidencia local. |
| Agents | Contratos de agentes y estado del puente UMCP. |
| Governance | Postura de solo lectura, rutas locales, visibilidad de puentes y herramientas. |
| Diagnostics | Informes, vista general y ubicaciones de artefactos generados. |
| Settings | Vista en el panel de `UIISSettings`. |

## Comportamiento de importación

La importación procesa archivos JSONL de fragmentos preparados. Cada fragmento contiene ID, contenido, referencias de origen, metadatos de assets/símbolos y estado del ciclo de vida. IIS valida la entrada, añade los fragmentos aceptados y escribe informes de importación.

Archivos importantes:

```text
Saved/InternalIndexService/chunks.jsonl
Saved/InternalIndexService/imports/
Saved/InternalIndexService/reports/
```

## Creación de catálogo

La creación del catálogo lee los fragmentos almacenados y produce estructuras locales buscables. Filtra los estados inactivos del ciclo de vida de los fragmentos y escribe un informe para que los usuarios puedan revisar las advertencias.

## Búsqueda

Los campos de consulta de búsqueda incluyen texto de consulta, modo de búsqueda, resultados máximos, filtros y opciones de paquetes de contexto. Los resultados contienen ID de fragmentos, información de puntuación, extractos (snippets) y referencias de origen.

Modos de búsqueda:

| Modo | Significado |
| --- | --- |
| Lexical | Utiliza coincidencia de texto local sobre el catálogo de fragmentos. |
| Vector | Utiliza embeddings persistentes y el backend vectorial configurado. |
| Hybrid | Combina candidatos léxicos y vectoriales. |

## Superficie de control en tiempo de ejecución

IIS incluye una superficie de control en tiempo de ejecución **autárquica** (autark) para observe → tune → act sin reiniciar el editor. Modifica el objeto `UIISSettings` activo en memoria (temporal por defecto) y vuelve a aplicar de inmediato los valores almacenados en caché, como el `efSearch` de HNSW y el núcleo int8 activo.

**Sin dependencia de UCM ni UMCP** — la superficie funciona desde Blueprint, C++ y la consola del editor de forma independiente.

### API de Blueprint tipada (`UIISSubsystem`)

| Método | Propósito |
| --- | --- |
| `GetControlState` | Captura del estado efectivo de controles y estado de la puerta de mutación. |
| `SetTuning` | Aplicar variaciones opcionales de ajuste por campo (`FIISTuningRequest`). |
| `PersistTuning` | Guardar invalidaciones actuales en la configuración (`SaveConfig`). |
| `ResetTuning` | Recargar configuración y revertir invalidaciones temporales. |
| `RunPerfSelfCheck` | Ejecutar cargas de trabajo de rendimiento SYN-2 contra los presupuestos configurados. |

### Comandos de consola

| Comando | Propósito |
| --- | --- |
| `iis.control.state` | Imprimir JSON del estado de control efectivo. |
| `iis.control.tune {json}` | Ajuste temporal (ej. `{"efSearch":128}`). |
| `iis.control.persist` | Guardar invalidaciones en la configuración. |
| `iis.control.reset` | Recargar configuración / revertir invalidaciones. |
| `iis.control.diagnostics.recent` | Diagnósticos recientes por consulta (cuando la retención está activa). |
| `iis.perf.run` / `iis.perf.last` | Ejecutar o leer la última autocomprobación de rendimiento. |
| `iis.index.sync` / `iis.index.rebuild` / `iis.index.import` | Comandos de acción para el mantenimiento del índice. |

Los comandos de modificación respetan **Enable Runtime Control Mutations** en la configuración del proyecto (activado por defecto).

## Embeddings

IIS no guarda credenciales de proveedores. La resolución y ejecución de rutas de embeddings se delega a través de `FIISEmbeddingDiscovery` (`IIISEmbeddingRouteExecutor` mediante `IModularFeatures`), provisto normalmente por un puente LLM Store que se registra en `StartupModule` y se da de baja en `ShutdownModule`.

El flujo de embeddings:

1. Crear tareas para los fragmentos que requieren vectores.
2. Resolver una ruta de embedding.
3. Ejecutar tareas a través del ejecutor registrado.
4. Persistir registros de vectores.
5. Actualizar informes.

## Herramientas de agente

Las herramientas de agente son de solo lectura y devuelven JSON estructurado. IIS define seis operaciones de recuperación autónomas. Los nombres de contratos locales permanecen disponibles para su uso dentro del motor y vía archivos JSON:

| Contrato local | ID de ruta UCM | Propósito |
| --- | --- | --- |
| `iis_search` | `iis.agent.search.v1` | Buscar fragmentos indexados (payload JSON integrado y ruta de artefacto). |
| `iis_get_context_pack` | `iis.agent.get_context_pack.v1` | Crear un paquete de contexto compacto a partir de los resultados de búsqueda (payload JSON integrado y ruta de artefacto). |
| `iis_get_chunk` | `iis.agent.get_chunk.v1` | Obtener un fragmento por su ID. |
| `iis_get_source_references` | `iis.agent.get_source_references.v1` | Devolver referencias de origen para un fragmento. |
| `iis_find_usages` | `iis.agent.find_usages.v1` | Buscar registros de uso. |
| `iis_explain_blueprint` | `iis.agent.explain_blueprint.v1` | Resumir evidencia Blueprint indexada (payload JSON integrado y ruta de artefacto). |

`iis.index.status.v1` informa además `catalog_exists`, `chunk_store_records` y `vector_records` para que los agentes puedan verificar si el índice se rellenó sin leer archivos.

El transporte MCP es responsabilidad de Unified MCP Server. IIS no registra herramientas MCP por sí mismo; la configuración Capability Mesh del proyecto declara una ruta por operación de agente y UMCP las publica como herramientas genéricas `mesh_route_*`. No se requiere ningún plugin puente.

## Datos y privacidad

IIS almacena los índices generados en la carpeta `Saved` del proyecto por defecto. Si se establece una raíz de índice personalizada, utilice una ruta local/privada a menos que su equipo comparta la evidencia generada intencionadamente.

La exposición a la nube solo ocurre si una ruta de ejecutor de embeddings en LLM Store utiliza un proveedor en la nube.

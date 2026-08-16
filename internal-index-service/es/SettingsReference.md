<!-- doc-provenance: SAD architecture.md sections 2,8,10; facts product-facts.yml; reconciled 2026-07-16 -->
# Referencia de configuración

La configuración de IIS se guarda en `UIISSettings`.

Abrir:

```text
Edit -> Project Settings -> Plugins -> Internal Index Service
```

## Campos

| Configuración | Predeterminado | Significado |
| --- | --- | --- |
| Vector Backend | `jsonl_bruteforce` | Selecciona el backend de búsqueda vectorial local. Los valores admitidos incluyen `jsonl_bruteforce` y `hnsw`. Con `jsonl_bruteforce`, IIS cambia automáticamente a HNSW cuando se supera el límite de registros de fuerza bruta indicado abajo. |
| Index Root | vacío | Anulación opcional para datos generados de IIS. Vacío utiliza `Saved/InternalIndexService`. |
| Brute Force Max Records | `10000` | Igual o por debajo de esta cantidad de registros, se utiliza búsqueda exacta de fuerza bruta; por encima, HNSW. |
| Embedding Executor Id | vacío | ID del ejecutor de embedding IIS preferido. Vacío utiliza la detección habitual; el puente opcional IIS LLM Store establece esto en `llmstore` mientras esté cargado. |
| Vector Storage Format | `Int8 Per-Vector Scale` | Política de almacenamiento vectorial HNSW. `Int8 Per-Vector Scale` es el valor compacto predeterminado admitido; `Float32` es útil para ejecuciones de alta fidelidad/depuración; `Experimental Global Scale` está bloqueado por puerta y es solo para mediciones. |
| Allow Experimental Vector Formats | `false` | Habilita formatos de almacenamiento HNSW experimentales. Cuando está desactivado, las selecciones experimentales recurren a `Int8 Per-Vector Scale`. |
| Rebuild On Vector Format Mismatch | `true` | Elimina particiones HNSW persistentes incompatibles para que se puedan reconstruir a partir de los vectores origen en lugar de leerse con un diseño de bytes incorrecto. |
| Quantization Recall Gate | `0.7` | Objetivo de precisión mínimo utilizado por las puertas de automatización de almacenamiento vectorial cuantizado. Auméntelo solo tras validar con embeddings representativos del proyecto. |
| HNSW M | `16` | Conectividad del grafo HNSW. Valores más altos mejoran la precisión a costa de memoria y tiempo de creación. Se aplica a los índices recién creados. |
| HNSW efConstruction | `200` | Tamaño de lista de candidatos en tiempo de creación. Valores más altos mejoran la calidad del grafo y la precisión a costa del tiempo de creación. Se aplica a los índices recién creados. |
| HNSW efSearch | `64` | Tamaño de lista de candidatos en tiempo de consulta. Valores más altos mejoran la precisión a costa de la latencia de consulta. Se aplica al cargar y reconstruir. |
| Enable Runtime Control Mutations | `true` | Puerta principal para la superficie de control en tiempo de ejecución. Cuando está desactivado, los comandos de consola y API de tune/act/persist se rechazan; las lecturas siguen funcionando. |
| Retain Recent Diagnostics | `false` | Cuando está activado, IIS mantiene un búfer circular en memoria de diagnósticos recientes por consulta para su inspección mediante `diagnostics.recent` / consola. |
| Recent Diagnostics Max Count | `64` | Cantidad máxima de diagnósticos conservados cuando Retain Recent Diagnostics está activado. |
| Estimate Recall By Default | `false` | Cuando está activado, las búsquedas estiman recall@K a menos que la consulta lo excluya explícitamente. Añade un escaneo de referencia exacto (SYN-1). |

> Los índices HNSW se almacenan utilizando cuantización escalar int8 por defecto (escalado por vector), lo que mantiene una alta precisión reduciendo al mismo tiempo la memoria del índice y el tamaño en disco. Float32 está disponible como política de alta fidelidad/depuración. El modo int8 a escala global experimental está intencionadamente bloqueado porque puede desperdiciar la mayoría de niveles int8 en embeddings multidimensionales normalizados. Los índices creados con otra política de almacenamiento se detectan y reconstruyen automáticamente por defecto.

## Rutas generadas

Raíz predeterminada:

```text
Saved/InternalIndexService
```

Áreas generadas importantes:

| Ruta | Propósito |
| --- | --- |
| `chunks.jsonl` | Almacenamiento de fragmentos importados. |
| `imports/` | Manifiestos de importación e informes. |
| `reports/` | Informes de catálogo, embedding y diagnóstico. |
| `agent_contracts/` | Contratos de herramientas de agentes y manifiesto MCP consumidos por puentes. |
| `vectors/` o archivos específicos del backend | Datos persistentes de embeddings/vectores. |

Los nombres exactos de archivos pueden variar según el flujo de trabajo y el backend.

## Configuración MCP

La configuración del servidor MCP no está en IIS. Configúrela en:

```text
Edit -> Editor Settings -> Plugins -> Unified MCP Server
```

El acceso a agentes IIS se publica a través de rutas Capability Mesh del proyecto como `iis.agent.search.v1`.

## Manejo de secretos

IIS no guarda secretos de proveedores. Las credenciales de proveedores de embeddings pertenecen a LLM Store o al entorno del proveedor.

## Valores predeterminados recomendados

| Escenario | Vector Backend | Vector Storage Format | Formatos experimentales | Index Root |
| --- | --- | --- | --- | --- |
| Primera configuración | `jsonl_bruteforce` | `Int8 Per-Vector Scale` | desactivado | vacío |
| Índice local más grande | `hnsw` | `Int8 Per-Vector Scale` | desactivado | vacío o ruta personalizada local del proyecto |
| Depuración de alta fidelidad | `hnsw` | `Float32` | desactivado | ruta de espacio de trabajo temporal |
| Experimento de precisión | `hnsw` | `Experimental Global Scale` | activado | ruta de espacio de trabajo temporal |
| Validación CI compartida | `jsonl_bruteforce` | `Int8 Per-Vector Scale` | desactivado | ruta de espacio de trabajo temporal |

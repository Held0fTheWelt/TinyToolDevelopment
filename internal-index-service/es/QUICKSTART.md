<!-- doc-provenance: SAD architecture.md sections 1,3,6,7,8; facts product-facts.yml; reconciled 2026-07-16 -->
# Inicio rápido

## 1. Habilitar el plugin

Habilite `Internal Index Service` en el navegador de plugins. Reinicie el editor si Unreal lo solicita.

## 2. Abrir el panel de control

Utilice:

```text
Tiny Tools -> AI -> Internal Index Service -> Open Internal Index Service
```

El panel de control se abre en el Dashboard.

## 3. Configurar los ajustes

Abra:

```text
Edit -> Project Settings -> Plugins -> Internal Index Service
```

Primeros pasos recomendados:

| Configuración | Valor |
| --- | --- |
| Vector Backend | `jsonl_bruteforce` |
| Vector Storage Format | `Int8 Per-Vector Scale` |
| Allow Experimental Vector Formats | `false` |
| Index Root | vacío |

Un valor de `Index Root` vacío significa que IIS utiliza:

```text
Saved/InternalIndexService
```

La política de almacenamiento predeterminada utiliza escalado int8 por vector para particiones HNSW. Es el modo compacto normal. `Float32` está disponible para ejecuciones de alta fidelidad/depuración; `Experimental Global Scale` debe permanecer deshabilitado a menos que esté evaluando deliberadamente los compromisos de precisión (recall).

## 4. Importar fragmentos (chunks) preparados

Utilice la pestaña "Imports" del panel de control o llame a la API del servicio con un archivo JSONL de fragmentos preparados. Los fragmentos preparados provienen normalmente de un pipeline de extracción complementario como Unreal Integration Intelligence.

La importación escribe informes en la carpeta de guardado de IIS y actualiza el almacenamiento de fragmentos.

## 5. Reconstruir el catálogo

Utilice la acción **Rebuild** del Dashboard o la pestaña "Catalog". IIS lee los fragmentos importados, normaliza el estado del ciclo de vida y escribe un informe de creación del catálogo.

## 6. Buscar

Utilice la pestaña "Search":

- la búsqueda léxica funciona a partir del catálogo local
- la búsqueda vectorial requiere embeddings
- la búsqueda híbrida combina ambas cuando existen vectores

## 7. Crear embeddings (Opcional – añade búsqueda vectorial, requiere LLM Store)

La búsqueda léxica (pasos 1–6) funciona de forma independiente sin ningún otro plugin. Las búsquedas vectorial e híbrida son una mejora opcional: configure primero el plugin **LLM Store**, luego IIS solicitará una ruta al registro de ejecutores de embeddings, creará tareas y escribirá informes de embeddings. Ejecute las tareas desde la pestaña "Embeddings". Sin LLM Store, IIS sigue importando, reconstruyendo y buscando de manera léxica.

## 8. Exponer herramientas de agente (Opcional – requiere Unified MCP Server + Capability Mesh)

Este paso es opcional y solo necesario si desea que agentes de IA llamen a IIS. Instale y habilite:

- Unified MCP Server
- Unreal Capability Mesh

Asegúrese de que el perfil Capability Mesh del proyecto incluya las rutas de agente de IIS (por ejemplo `iis.agent.search.v1`). Luego inicie Unified MCP Server. Cada función de agente de IIS se expone como su propia ruta UCM autónoma, aplanada a una herramienta MCP `mesh_route_*`, como por ejemplo:

```text
mesh_route_iis_agent_search_v1_<hash>
mesh_route_iis_agent_get_context_pack_v1_<hash>
mesh_route_iis_agent_get_chunk_v1_<hash>
mesh_route_iis_agent_get_source_references_v1_<hash>
mesh_route_iis_agent_find_usages_v1_<hash>
mesh_route_iis_agent_explain_blueprint_v1_<hash>
```

Alternativamente, llame a `mesh_execute_route` con `route_id` establecido en el ID de la ruta (por ejemplo `iis.agent.search.v1`).

## 9. Ajuste en tiempo de ejecución (Opcional – sin plugins adicionales)

La superficie de control en tiempo de ejecución incluida es **autárquica** (autark): no requiere UCM ni UMCP.

Abra la consola de registro de salida del editor y ejecute:

```text
iis.control.state
```

Ejemplo de extracto de respuesta (el valor predeterminado de `efSearch` es 64):

```json
{"ok":true,"errorCode":"","errorMessage":"","efSearch":64,...}
```

Aumente el parámetro `efSearch` de consulta en vivo:

```text
iis.control.tune {"efSearch":128}
```

Confirme el cambio:

```text
iis.control.state
```

Ejemplo tras el ajuste:

```json
{"ok":true,"errorCode":"","errorMessage":"","efSearch":128,...}
```

Las anulaciónes son **temporales** (transient) hasta que ejecute `iis.control.persist`. Utilice `iis.control.reset` para recargar la configuración. Consulte `UserManual.md` para ver la lista completa de comandos de consola y API de Blueprint.

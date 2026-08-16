<!-- doc-provenance: AKDB:plugins/UnrealCapabilityMesh/architecture.md; docs/architecture/plugins/UnrealCapabilityMesh/product-facts.yml; reconciled 2026-07-19 -->
# Manual de usuario

## Panel de control

Abra el panel desde:

```text
Tools -> Unreal Capability Mesh
```

El panel es una vista operativa técnica para la interoperabilidad orientada a manifiestos. Utiliza una barra de estado y páginas enfocadas en lugar de apilar todas las herramientas en una sola vista extensa.

Páginas:

- `Overview`: perfil activo, recuento de inventario, recuento de disponibilidad, flujo de configuración y contrato MCP.
- `Capabilities`: ID de capacidades cargadas, puntos de entrada, efectos secundarios, disponibilidad, advertencias y manifiestos de origen.
- `Routes`: catálogo de rutas más simulación (dry-run) y entrada/salida de ejecución.
- `Governance`: vocabulario activo de efectos secundarios y decisiones de reglas.
- `Tiny Tools`: conmutadores de paquetes de configuración para contenido de Tiny Tool Development.
- `Setup Editor`: editor JSON con reconocimiento de tipos para manifiestos de configuración del proyecto, muestras de referencia de solo lectura y el entorno de pruebas no vinculante (playground).
- `Config Admin`: objetivos de configuración permitidos y preajustes de ruta para operaciones de lista/lectura/escritura.
- `Diagnostics`: mensajes de validación de configuración, detección y recarga.
- `Adapter`: generador de manifiesto inicial para añadir capacidades declaradas en la configuración sin dependencia de puente.

## Tiny Tools

La página `Tiny Tools` se gestiona mediante los manifiestos de catálogo situados en:

```text
Config/UnrealCapabilityMesh/tool_catalogs/
```

El primer conmutador indica si el proyecto debe utilizar el contenido de configuración de Tiny Tool Development. Cuando se desactiva, todas las entradas de configuración pertenecientes al catálogo se eliminan del perfil activo. Los conmutadores de herramientas individuales añaden o desactivan las entradas de paquetes declaradas por el catálogo:

- manifiestos de capacidades
- manifiestos de puntos de entrada
- manifiestos de esquemas
- manifiestos de reglas
- manifiestos de rutas
- manifiestos de transformaciones
- manifiestos de adaptadores
- ID de objetivos de configuración

Este es un modelo de desactivación, no de eliminación de archivos. Los archivos de manifiesto permanecen en el proyecto y pueden volver a habilitarse posteriormente.

Los paquetes de Tiny Tool están separados deliberadamente por propiedad. IIS, LLM Store y UII se pueden habilitar de forma independiente. Los flujos de trabajo entre plugins son conmutadores de ruta independientes, por lo que un proyecto puede utilizar solo IIS, solo LLM Store, UII+IIS o IIS+LLM Store sin necesidad de poseer toda la pila.

El campo de perfil `enabled_config_target_ids` limita qué objetivos de configuración son visibles para Config Admin. Si el campo no está presente, Config Admin mantiene el comportamiento anterior y examina todos los manifiestos de objetivos.

## Setup Editor

La página `Setup Editor` edita manifiestos locales del proyecto situados en `Config/UnrealCapabilityMesh` con campos adaptados según el tipo:

- booleanos para conmutadores de directivas y perfiles
- matrices de cadenas para `enabled_*_manifests`
- campos enumerados como `invocation_mode` y `side_effects`
- objetos anidados y matrices de objetos a partir de manifiestos de rutas, capacidades y puntos de entrada

El árbol de la izquierda tiene tres raíces:

1. `Project Setup` — manifiestos del proyecto editables, incluido `project_profile.json`.
2. `Playground Sandbox` — manifiestos de pruebas editables en `playground/` sin vinculación real a un plugin. Utilice `Add playground to profile` para probar fallos de activación, o habilite el elemento de catálogo `Setup Editor Playground` desde `Tiny Tools`.
3. `Reference Samples` — manifiestos incluidos de Tiny Tool de solo lectura agrupados por plugin de catálogo, más muestras del núcleo de UCM. Utilice `Copy to project` para duplicar un manifiesto de referencia en la configuración del proyecto.

Acciones de la barra de herramientas:

- `Save` / `Revert` — guardar o descartar el archivo de manifiesto activo.
- `Validate file` — ejecutar `FCapabilityMeshSetupLoader::ValidateManifestFile` en el archivo seleccionado.
- `Reload Setup` — volver a cargar la malla activa tras realizar cambios en perfiles o manifiestos.
- `Open source folder` — abrir la ruta del plugin C++ asignada desde `editor/plugin_source_hints.json` al seleccionar un nodo de plugin de referencia.

Las reglas de tipos de campos se encuentran en `editor/manifest_field_schema.json`.

## Reload Setup

`Reload Setup` llama a `FCapabilityMeshService::ReloadSetup`.

Ejecuta la siguiente secuencia:

1. Limpia registros e informes anteriores.
2. Detecta la configuración predeterminada de UCM, las raíces de configuración locales de los plugins habilitados y la anulación opcional del proyecto.
3. Combina sus archivos `project_profile.json` por orden de prioridad.
4. Carga capacidades, puntos de entrada, esquemas, reglas, rutas, transformaciones y adaptadores.
5. Registra las definiciones cargadas.
6. Genera diagnósticos de configuración y registro.
7. Ejecuta la detección.
8. Genera informes de detección y compatibilidad.

Los manifiestos propiedad del proveedor deben permanecer en la carpeta `Config/UnrealCapabilityMesh/` del plugin proveedor. Los manifiestos locales del proyecto tienen mayor prioridad y se utilizan para anulaciones deliberadas o rutas compuestas del proyecto. Duplicar definiciones del proveedor en el proyecto puede generar advertencias de anulación y ocultar la propiedad.

Cuando el plugin opcional Tiny Tool Execution Integration Bridge está habilitado, su módulo de editor llama a `ReloadSetup` antes de registrar y detectar herramientas proyectadas de UCM. UCM sigue siendo propietario de las definiciones de rutas resultantes y de cada decisión de directiva.

## Discovered Capabilities

La vista de capacidades detectadas enumera el ID de la capacidad, ID del proveedor, modo de interoperabilidad y disponibilidad. La disponibilidad puede ser disponible, no disponible, no segura, esquema no encontrado, aprobación requerida o plugin no cargado.

## Diagnostics

La vista de diagnósticos muestra errores y advertencias de validación de configuración, así como los mensajes devueltos por la recarga o detección. Consúltela en primer lugar cuando no aparezca una ruta o punto de entrada.

## Routes

Introduzca un ID de ruta y ejecute una simulación (dry run). UCM resuelve los pasos de la ruta, comprueba la disponibilidad de capacidades, agrega efectos secundarios, evalúa reglas y genera un informe de ruta.

Introduzca la entrada JSON de la ruta y ejecútela si la simulación es limpia. UCM planifica la ruta primero, bloquea las violaciones de directivas y las rutas que requieren simulación, e invoca cada punto de entrada en el orden establecido. Las rutas que requieren aprobación deben incluir `approval_granted: true` o `approval: "granted"` en la entrada de la ruta antes de ejecutarse, a menos que la anulación de autoaprobación automática **EXPERIMENTACIÓN** esté activa para esa ruta. Las salidas de cada paso y la salida de la ruta se escriben en `Saved/UnrealCapabilityMesh/route_execution_reports/`.

### Route Catalog

El **Route Catalog** de la página Routes enumera cada ruta cargada desde los manifiestos de configuración en una tabla agrupada por plugin:

| Columna | Contenido |
| --- | --- |
| Plugin / Route | Grupos de plugins desplegables y filas de rutas con detalles de directivas, pasos, puntos de entrada, efectos secundarios y manifiestos de origen |
| Approve all at own risk | Controles para la autoaprobación automática **EXPERIMENTACIÓN** |

Encabezado de columna:

- **Approve all at own risk** — conmutador global para cada ruta que requiere aprobación en el perfil activo. Cuando está habilitado, las casillas de verificación individuales por ruta se desactivan porque todas las rutas con aprobación heredan la anulación.

Filas de plugin:

- Flecha de despliegue, nombre visible del plugin, cantidad de rutas y una casilla de aprobación por plugin si ese plugin posee rutas que requieren aprobación.

Filas de ruta:

- Flecha de despliegue, ID de ruta y texto de detalle de la ruta procedente del plan de simulación (dry-run).
- Rutas con aprobación requerida: casilla de verificación por ruta (salvo que **Approve all** esté activo).
- Rutas sin aprobación requerida: `n/a` con una ayuda emergente que explica que no se aplica ninguna puerta de aprobación.

Una advertencia naranja sobre el catálogo indica que la autoaprobación automática activa una omisión generalizada de directivas. Las reglas de denegación coincidentes, comprobaciones de modificación de activos/proyecto de la ruta, requisitos de aprobación y requisitos de simulación se ignoran; por tanto, las rutas habilitadas pueden modificar el estado del editor sin esas salvaguardas.

Los mismos ajustes persisten en `project_profile.json` (`experimental_self_approval_all_routes`, `experimental_self_approved_route_ids`) y se pueden leer o modificar por MCP mediante `mesh_configure_experimental_self_approval`; la habilitación por MCP requiere `acknowledge_experimental_risk: true`. Mantenga la autoaprobación desactivada para uso normal en producción.

La página `Config Admin` puede preparar los ID de rutas y sobres JSON estándar de administración de configuración en el ejecutor de rutas. Esto mantiene a MCP, usuarios del editor y automatización bajo el mismo contrato de ruta.

## Administración de DataAsset y DataTable

`UCapabilityMeshAssetAdminSubsystem` expone operaciones invocables mediante JSON para la administración de DataAsset/DataTable:

- `ExportAdminSurfaceJson`: exporta un DataAsset o una DataTable a un sobre de administración portable y puede guardarlo en `Saved/UnrealCapabilityMesh/asset_admin`.
- `ImportAdminSurfaceJson`: importa un sobre exportado previamente en un DataAsset o DataTable existente.
- `SyncAdminSurfaceJson`: copia campos editables de un DataAsset a una fila de DataTable o desde una fila de DataTable de vuelta a un DataAsset.

Las DataTables compuestas (Composite DataTables) son fuentes de exportación seguras. Las escrituras directas en una DataTable compuesta están bloqueadas; diríjase a la DataTable hija concreta a la que deba pertenecer la fila.

Ejemplo de entrada de ruta para una ruta de sincronización con modificación:

```json
{
  "approval_granted": true,
  "request_json": "{\"source_object_path\":\"/Game/Config/DA_Settings.DA_Settings\",\"target_object_path\":\"/Game/Config/DT_Settings.DT_Settings\",\"mode\":\"data_asset_to_data_table\",\"row_name\":\"Default\"}"
}
```

## Administración de configuración

`UCapabilityMeshConfigAdminSubsystem` expone objetivos de configuración permitidos. Esta es la ruta MCP estándar para ajustes de plugins y archivos de configuración del proyecto.

Los objetivos se declaran en:

```text
Config/UnrealCapabilityMesh/config_targets/
```

Rutas habituales:

- `capability_mesh.config_admin.list_targets.v1`
- `capability_mesh.config_admin.read_target.v1`
- `capability_mesh.config_admin.write_target.v1`

Ejemplo de lectura:

```json
{
  "request_json": "{\"target_id\":\"example_plugin.settings\"}"
}
```

Ejemplo de escritura:

```json
{
  "approval_granted": true,
  "request_json": "{\"target_id\":\"example_plugin.settings\",\"fields\":{\"bEnabled\":true}}"
}
```

Los objetivos de instancias de objetos, como un objeto de configuración respaldado por un activo, también requieren `object_path` en el JSON de la solicitud. Los objetivos de archivos JSON aceptan `payload` o `payload_json`.

## Acceso por MCP

`UCapabilityMeshMcpGatewaySubsystem` expone el rechargado de configuración, listado de capacidades, simulación de ruta, ejecución de ruta e invocación de puntos de entrada como funciones invocables en JSON. Unified MCP Server se conecta a esta pasarela mediante el proveedor genérico `mesh` cuando ambos plugins están cargados.

Nombres habituales de herramientas en UMCP:

- `mesh_reload_setup`
- `mesh_list_capabilities`
- `mesh_list_routes`
- `mesh_configure_experimental_self_approval`
- `mesh_dry_run_route`
- `mesh_execute_route`
- `mesh_invoke_endpoint`

Unified MCP Server también aplana las rutas declaradas en herramientas MCP directas llamadas `mesh_route_<sanitized_route_id>_<hash>`. Estas herramientas aceptan `mode: "dry_run"` para análisis o `mode: "execute"` para ejecución. Si no se indica ningún campo `input` o `input_json`, los argumentos restantes se convierten en el objeto de entrada de la ruta. UCM exporta `input_schema`, `output_schema` y `tool_annotations` derivados de rutas mediante `mesh_list_routes`; UMCP los publica como `inputSchema`, `outputSchema` y anotaciones de MCP para cada herramienta `mesh_route_*`. En rutas habituales vinculadas a `request_json`, UMCP también refleja argumentos aplanados en ese campo de solicitud serializado para que la IA pueda llamar a las herramientas con parámetros con nombre comprensibles.

Utilice `mesh_execute_route` para la importación, sincronización y escritura de configuración de DataAsset/DataTable a fin de que las directivas de ruta y las comprobaciones de aprobación permanezcan activas. Utilice `mesh_configure_experimental_self_approval` solo para pruebas o flujos a su propio riesgo **EXPERIMENTACIÓN**; puede activar el omisión general de directivas a nivel global o para ID de rutas seleccionados. Utilice `mesh_list_routes` para verificar el estado actual visible por MCP; informa sobre la marca experimental global, anulaciones de rutas seleccionadas y el plan efectivo omitido por ruta.

## Integración principal con UCM

El perfil de proyecto activo conecta los productos de Tiny Tool Development mediante rutas declaradas en la configuración. Utilice esta vía de UCM como el modelo de integración normal. Los Freebie Bridges solo están destinados a equipos sin UCM o desarrolladores que deseen ejemplos de adaptadores directos.

- `uii_to_iis_context_pack.v1`: pruebas de UII -> flujo de importación/búsqueda/paquete de contexto de IIS, con ejecución de rutas de incrustación de LLM Store si está configurado.
- `prs.build_asset_move_plan.v1`, `prs.preview_plan.v1`, `prs.apply_plan.v1`, `prs.rollback.v1`: flujos de trabajo de ubicación de PRS mediante directivas y aprobación de rutas en UCM.
- `scd.migration_advice_from_handoff.v1`: contrato/sobre de entrega de UII -> recomendaciones de migración de SmartContentDiet a través de UCM.
- `capability_mesh.asset_admin.export.v1`, `capability_mesh.asset_admin.import.v1`, `capability_mesh.asset_admin.sync.v1`: administración de DataAsset/DataTable mediante la malla.
- `capability_mesh.config_admin.list_targets.v1`, `capability_mesh.config_admin.read_target.v1`, `capability_mesh.config_admin.write_target.v1`: administración de ajustes y archivos de configuración permitidos a través de la malla.

Las rutas de modificación de proyectos o activos siguen requiriendo la aprobación explícita de la ruta, salvo que la anulación de autoaprobación automática **EXPERIMENTACIÓN** esté activa para esa ruta.

## Reglas

Las reglas determinan si una ruta está permitida, requiere aprobación, requiere simulación o está bloqueada. Las reglas se ordenan por prioridad y se declaran en JSON.

## Editor de adaptadores

El editor de adaptadores escribe un manifiesto de adaptador sencillo en `Config/UnrealCapabilityMesh/adapters`. Su propósito es servir como punto de partida para mapear otro plugin en UCM sin añadir dependencias C++ directas al núcleo.

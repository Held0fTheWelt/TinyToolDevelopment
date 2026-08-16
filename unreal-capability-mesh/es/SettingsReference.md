<!-- doc-provenance: AKDB:plugins/UnrealCapabilityMesh/architecture.md; docs/architecture/plugins/UnrealCapabilityMesh/product-facts.yml; reconciled 2026-07-19 -->
# Referencia de manifiestos y configuración

UCM no expone una página en `UDeveloperSettings`. La configuración se realiza mediante archivos JSON cargados desde tres clases de raíces de configuración:

1. La configuración predeterminada incluida en UCM.
2. Carpetas `Config/UnrealCapabilityMesh` suministradas por los plugins proveedores habilitados.
3. La anulación opcional del proyecto en `Config/UnrealCapabilityMesh`.

Los perfiles se combinan en ese orden, prevaleciendo la anulación del proyecto. No se requiere un perfil local en el proyecto para el primer uso ni para las rutas de un plugin proveedor habilitado. Cree uno únicamente cuando el proyecto anule intencionadamente la configuración o posea rutas compuestas.

## `project_profile.json`

| Campo | Propósito |
| --- | --- |
| `schema_version` | Debe comenzar por `capability_mesh.project_profile`. |
| `profile_id` | ID estable para el perfil activo. |
| `display_name` | Nombre del perfil en formato legible. |
| `enable_knowledge_store` | Escribe el historial de invocaciones cuando es verdadero. |
| `experimental_self_approval_all_routes` | **EXPERIMENTACIÓN, bajo su propio riesgo.** Cuando es verdadero, las rutas configuradas utilizan la omisión general de directivas descrita a continuación. Mantener en falso para uso normal. |
| `experimental_self_approved_route_ids` | **EXPERIMENTACIÓN, bajo su propio riesgo.** ID de rutas que utilizan la omisión de directivas cuando `experimental_self_approval_all_routes` es falso. |
| `active_ruleset_id` | Nombre del conjunto de reglas que se tratará como activo. |
| `enabled_capability_manifests` | Rutas de manifiestos de capacidades. |
| `enabled_endpoint_manifests` | Rutas de manifiestos de puntos de entrada. |
| `enabled_schema_manifests` | Rutas de manifiestos de esquemas. |
| `enabled_rule_manifests` | Rutas de manifiestos de reglas. |
| `enabled_route_manifests` | Rutas de manifiestos de rutas. |
| `enabled_transform_manifests` | Rutas de manifiestos de transformaciones. |
| `enabled_adapter_manifests` | Rutas de manifiestos de adaptadores. |
| `enabled_config_target_ids` | Lista de origen opcional para objetivos de Config Admin. Si no está presente, se examinan todos los manifiestos de objetivos. |
| `tiny_tool_development_plugins_enabled` | Conmutador de activación gestionado por IU para el catálogo de Tiny Tool Development. |
| `reflection_metadata_keys` | Claves de metadatos utilizadas al examinar capacidades expuestas por reflexión. |
| `optional_scan_paths` | Carpetas o archivos adicionales en los que buscar manifiestos JSON. |
| `setup_editor_playground_enabled` | Conmutador de activación gestionado por IU para el entorno de pruebas en Setup Editor. |
| `setup_editor_show_cpp_source_hints` | Marca de perfil opcional para mostrar sugerencias de código C++ en el árbol de referencia de Setup Editor. |

Las entradas de manifiestos relativas se resuelven a partir de la raíz de configuración propietaria del perfil, con opciones de reserva en el proyecto y la raíz del proyecto. Para personalizar, copie solo el perfil o los manifiestos que el proyecto vaya a anular. Dejar las definiciones de proveedores dentro de sus plugins mantiene clara la propiedad de las rutas y evita advertencias por definiciones duplicadas.

## Recursos de Setup Editor

| Ruta | Propósito |
| --- | --- |
| `editor/manifest_field_schema.json` | Asigna rutas de campos JSON a tipos de widgets del editor (`bool`, `enum`, `string_array`, etc.). |
| `editor/plugin_source_hints.json` | Asigna valores de `item_id` del catálogo a carpetas de código fuente C++ para exploración de referencias en solo lectura. |
| `playground/` | Manifiestos de pruebas editables sin vinculación real a un plugin. |
| `tool_catalogs/setup_editor_playground.json` | Elemento del catálogo que añade manifiestos de pruebas a `project_profile.json`. |

## Manifiesto de capacidad (Capability)

Las capacidades declaran lo que puede hacer un proveedor. Cada capacidad tiene un ID, título, categoría, efectos secundarios, puertos de entrada, puertos de salida e ID de punto de entrada.

## Manifiesto de punto de entrada (Endpoint)

Los puntos de entrada declaran cómo se invoca una capacidad. Campos importantes:

- `endpoint_id`
- `invocation_mode`
- `target`
- `parameters`
- `availability`

Los modos de invocación admitidos incluyen funciones de reflexión, contratos de archivos, proveedores de características modulares, puente de Python, commandlet y declaraciones de procesos externos. La reflexión, contratos de archivos y características modulares de UCM se ejecutan directamente; el puente de Python, commandlets y procesos externos se muestran solo en detección hasta que se implementen sus invocadores genéricos.

## Manifiesto de esquema (Schema)

Los esquemas describen la estructura esperada de los puertos de entrada y salida. UCM utiliza los ID de esquemas para comprobar la compatibilidad.

## Manifiesto de regla (Rule)

Las reglas determinan si una ruta está permitida. Efectos secundarios habituales:

- `read_only`
- `saved_folder_write`
- `project_config_write`
- `asset_mutation`
- `project_mutation`
- `network`
- `ai_completion`

## Manifiesto de ruta (Route)

Las rutas definen pasos ordenados. Cada paso hace referencia a un ID de capacidad y declara vinculaciones de entrada/salida.

Las rutas con modificación deben establecer `allow_asset_mutation` o `allow_project_mutation` únicamente cuando la operación sea intencionada. El ejecutor requiere normalmente aprobación durante el tiempo de ejecución; proporcione `approval_granted: true`, `approvalGranted: true` o `approval: "granted"` en la entrada de la ruta a menos que la anulación de autoaprobación automática **EXPERIMENTACIÓN** descrita a continuación esté activa.

### Autoaprobación automática experimental

`experimental_self_approval_all_routes` y `experimental_self_approved_route_ids` son opciones de escape explícitamente experimentales para pruebas y flujos de trabajo a su propio riesgo. Cuando están habilitadas, UCM transmite `bExperimentalPolicyBypass=true` durante la planificación y ejecución de rutas. Las reglas de denegación coincidentes con `allow=false` dejan de bloquear la ruta, los requisitos de aprobación y simulación a nivel de regla se ignoran, se omiten las comprobaciones de modificación de activos/proyecto a nivel de ruta, y el plan final elimina tanto los requisitos de aprobación como los de simulación.

Mantenga ambas opciones desactivadas para flujos de trabajo normales y de producción. El catálogo de rutas del editor etiqueta estos conmutadores como **EXPERIMENTACIÓN** e indica la totalidad del alcance de la omisión. Los hosts MCP pueden leer o modificar estas opciones a través de `mesh_configure_experimental_self_approval`; la habilitación mediante MCP requiere `acknowledge_experimental_risk: true`.

## Manifiesto de transformación (Transform)

Las transformaciones asignan JSON de origen a JSON de destino. Se utilizan para adaptar las salidas de una capacidad como entradas para otra.

## Manifiesto de adaptadores (Adapter)

Los adaptadores vinculan funciones de plugins de terceros en UCM sin añadir una dependencia C++ directa al núcleo.

## Configuración de administración de activos

La configuración predeterminada incluida en la propia carpeta `Config/UnrealCapabilityMesh` de UCM declara capacidades de administración de DataAsset/DataTable:

- `capability_mesh.asset_admin.export`
- `capability_mesh.asset_admin.import`
- `capability_mesh.asset_admin.sync`

Las tres invocan a `UCapabilityMeshAssetAdminSubsystem` a través de puntos de entrada de tipo `reflection_subsystem_function`. Los hosts MCP deben usar estas declaraciones en lugar de llamar a código puente específico del proyecto.

## Manifiesto de objetivos de configuración

Los objetivos de administración de configuración se aprueban por separado de los manifiestos de rutas en:

```text
Config/UnrealCapabilityMesh/config_targets/*.json
```

Los manifiestos de objetivos utilizan:

```json
{
  "schema_version": "capability_mesh.config_target_manifest.v1",
  "targets": [
    {
      "target_id": "example_plugin.settings",
      "display_name": "Example Plugin Settings",
      "description": "Explains what the target controls and when it should be edited.",
      "kind": "uobject_config",
      "class_path": "/Script/ExamplePlugin.ExamplePluginSettings",
      "required_plugin_names": ["ExamplePlugin"]
    }
  ]
}
```

Valores de `kind` admitidos:

- `uobject_config`: lee y escribe propiedades de configuración en un objeto predeterminado de clase (CDO) y guarda la configuración.
- `uobject_instance`: lee y escribe campos editables en una clase de objeto permitida. Las solicitudes deben incluir `object_path`.
- `json_file`: lee y escribe un archivo JSON declarado en un directorio base permitido.

Cada objetivo debe incluir una `description` no vacía; Config Admin muestra las descripciones faltantes como advertencias porque los usuarios necesitan contexto antes de leer o escribir en un objetivo.

Las rutas estándar son `capability_mesh.config_admin.list_targets.v1`, `capability_mesh.config_admin.read_target.v1` y `capability_mesh.config_admin.write_target.v1`. Las rutas de escritura declaran `project_config_write` y `asset_mutation` para que los archivos de configuración, objetos de configuración, DataAssets e instancias de objetos editables pasen todos por el mismo flujo de aprobación y simulación.

## Manifiesto del catálogo de herramientas

Los catálogos de herramientas se encuentran en:

```text
Config/UnrealCapabilityMesh/tool_catalogs/*.json
```

Agrupan entradas de configuración en paquetes activables mediante la interfaz de usuario. Un paquete puede declarar rutas de manifiestos de capacidades, puntos de entrada, esquemas, reglas, rutas, transformaciones, adaptadores e ID de objetivos de configuración. La IU desactiva los paquetes eliminando esas entradas de `project_profile.json`; no elimina los archivos de manifiesto.

Los paquetes del catálogo deben mantenerse tan reducidos como lo permita el límite de propiedad. El paquete de un plugin solo debe añadir las capacidades, puntos de entrada, esquemas y objetivos de configuración propios de dicho plugin. Los flujos entre plugins deben ser paquetes de rutas independientes que hagan referencia a los componentes ya habilitados. Esto mantiene válidas las configuraciones solo con IIS, solo con LLM Store, UII+IIS e IIS+LLM Store sin requerir la presencia de todos los plugins de Tiny Tool Development.

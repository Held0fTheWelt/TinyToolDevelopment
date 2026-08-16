<!-- doc-provenance: AKDB:plugins/UnrealCapabilityMesh/architecture.md; docs/architecture/plugins/UnrealCapabilityMesh/product-facts.yml; reconciled 2026-07-19 -->
# Solución de problemas

## Error al cargar la configuración

Compruebe `Saved/UnrealCapabilityMesh/setup_validation_report.json`.

Causas habituales:

- no se encuentra `project_profile.json` en las raíces de configuración predeterminadas, del plugin habilitado o del proyecto
- `schema_version` no válida
- errata en la ruta del manifiesto
- JSON con formato incorrecto
- faltan matrices requeridas como `capabilities` o `endpoints`

Para el primer uso, un perfil local del proyecto es opcional. UCM combina su perfil predeterminado con los perfiles suministrados por los plugins habilitados. Cree un perfil de proyecto solo para anulaciones intencionadas o rutas propias del proyecto, y haga clic en `Reload Setup`.

## No se detecta una capacidad

Compruebe si:

- el manifiesto de la capacidad está referenciado por el perfil en su raíz de configuración propietaria
- la capacidad tiene un `capability_id` no vacío
- el ID del punto de entrada existe
- los nombres de plugins requeridos están cargados
- los esquemas requeridos existen

Si la capacidad pertenece a otro plugin, confirme que dicho plugin esté habilitado y que su paquete contenga `Config/UnrealCapabilityMesh/project_profile.json`. No copie la definición del proveedor en el proyecto como solución alternativa; vuelva a cargar la configuración e inspeccione qué raíces se han detectado.

## El proyecto informa de advertencias por definiciones duplicadas

La misma capacidad, punto de entrada, esquema o ruta propiedad del proveedor existe probablemente tanto en el perfil local del plugin como en la anulación del proyecto.

Elimine la copia duplicada del proyecto a menos que el proyecto anule deliberadamente esa definición. Los perfiles del proyecto normalmente deben contener cambios de directivas o rutas compuestas del proyecto, mientras que los contratos del proveedor permanecen en el plugin.

## TTER no muestra una ruta válida de UCM tras el inicio

Confirme que el plugin opcional Tiny Tool Execution Integration Bridge está habilitado. Su módulo de editor vuelve a cargar la configuración de UCM antes de la detección de TTER. Tras habilitar un nuevo proveedor o editar la configuración, haga clic en `Reload Setup` y actualice la detección de herramientas.

## La ruta está bloqueada

Abra el informe de la ruta en `Saved/UnrealCapabilityMesh/route_reports`. El planificador de rutas registra las explicaciones y motivos de bloqueo.

Causas habituales:

- ninguna regla permite los efectos secundarios agregados
- la ruta utiliza `project_mutation` y la regla predeterminada la bloquea
- la modificación de activos requiere aprobación o simulación (dry-run)
- los esquemas de entrada y salida son incompatibles

Si la autoaprobación automática **EXPERIMENTACIÓN** está habilitada en la columna de aprobación del catálogo de rutas o en el perfil, desactívela antes de investigar el comportamiento de gobernanza. La anulación omite las reglas de denegación coincidentes, comprobaciones de modificación de activos/proyecto, requisitos de aprobación y requisitos de simulación, por lo que puede enmascarar cualquiera de esos resultados.

## Fallo en la invocación del punto de entrada

Compruebe `Saved/UnrealCapabilityMesh/invocation_reports`.

Causas habituales:

- la ruta de la clase no se resuelve
- el nombre de la función es incorrecto
- la vinculación de parámetros no coincide con el parámetro de la función
- el modo de invocación está declarado pero ningún invocador genérico lo admite todavía
- el plugin proveedor no está cargado

## Los informes están vacíos

Vuelva a hacer clic en `Reload Setup`. El panel vuelve a cargar los manifiestos y regenera los diagnósticos. Confirme también que la ruta de configuración del proyecto sea el proyecto activo, no una carpeta del motor o de ejemplo.

## La validación del código fuente informa de cadenas estáticas (hardcoding)

La validación del código fuente puede informar sobre nombres de plugins asociados o ID de capacidades específicas del producto en el código C++ de UCM. Mueva las cadenas específicas de integración a archivos JSON de configuración en lugar de añadir ramificaciones en C++.

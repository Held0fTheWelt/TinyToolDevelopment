<!-- doc-provenance: AKDB:plugins/UnifiedMcpServer/architecture.md; docs/architecture/plugins/UnifiedMcpServer/product-facts.yml; reconciled 2026-07-04 -->
# Solución de problemas

## El cliente recibe 401 Unauthorized

Compruebe que el cliente envíe:

```text
Authorization: Bearer <token>
```

Lea el token de compatibilidad actual o el token con ámbito de:

```text
Saved/UnifiedMcpServer/agent/mcp_endpoint.json
```

Si los tokens se rotaron, actualice la configuración del cliente.

## La respuesta de estado expondría tokens

Las respuestas de ciclo de vida y estado solo informan de la presencia del archivo de intercambio, su ruta, el puerto y el recuento de tokens. Nunca deben devolver el JSON del archivo de intercambio sin procesar ni los valores de los tokens Bearer. Utilice el archivo de intercambio local para una configuración de cliente autorizada en lugar de copiar secretos a través de diagnósticos.

## Falta el archivo de intercambio (handshake)

Posibles causas:

- el servidor no está en ejecución
- el servidor no pudo vincularse al puerto configurado
- el plugin está deshabilitado
- el editor aún no ha iniciado el módulo

Inicie el servidor desde:

```text
Tiny Tools -> AI -> Universal MCP -> Start Unified MCP Server
```

## El puerto ya está en uso

Cambie el puerto en:

```text
Edit -> Editor Settings -> Plugins -> Unified MCP Server
```

A continuación, reinicie el servidor.

## `tools/list` no devuelve ninguna herramienta

Unified MCP Server es solo el host. Habilite Unreal Capability Mesh para obtener las herramientas genéricas `mesh_*`, o habilite otro plugin de proveedor. Compruebe también que el proveedor informe del estado de preparación y haya registrado su función modular.

Compruebe el control de acceso en Editor Settings y en el panel de control. Los ID de proveedores deshabilitados, los perfiles de acceso restrictivos, las listas permitidas no vacías, los patrones de herramientas bloqueadas o los grupos de herramientas bloqueados ocultan intencionadamente las herramientas coincidentes de `tools/list`.

Si aparecen las herramientas genéricas `mesh_*` pero no aparece ninguna herramienta `mesh_route_*`, ejecute `mesh_reload_setup` o haga clic en **Reload Setup** en el panel de Capability Mesh y, a continuación, actualice el cliente MCP. Las herramientas de rutas se generan a partir de los manifiestos de rutas activos en `Config/UnrealCapabilityMesh`.

Si aparece `mesh_configure_experimental_self_approval`, trátela como una herramienta de prueba **EXPERIMENTAL** bajo su propio riesgo. Su habilitación requiere `acknowledge_experimental_risk: true` y cambia el comportamiento de aprobación de Capability Mesh para rutas seleccionadas o todas las rutas que requieren aprobación.

Si la autoaprobación automática se modificó en la UI de rutas UCM pero el cliente MCP sigue mostrando descripciones de rutas antiguas, llame de nuevo a `tools/list` o vuelva a conectar/actualizar el cliente. UMCP recarga la configuración de UCM antes de listar las herramientas de rutas, y `mesh_list_routes` devuelve directamente el estado actual de `experimental_self_approval_*`.

## Connected Functions parece desactualizado en el panel de control

El panel de control almacena en caché los metadatos de las herramientas para acelerar las visitas repetidas. Tras cambiar la configuración de UCM, añadir proveedores o recargar rutas, haga clic en **Refresh** en el panel de control para forzar una recarga completa de las funciones conectadas. El inicio/parada y el despliegue/repliegue reutilizan la caché cuando la captura subyacente no ha cambiado.

## Un cliente Stdio no puede conectarse directamente

El plugin proporciona transporte HTTP. Los clientes que solo admiten Stdio necesitan un puente instalado por el usuario como `mcp-remote`.

## La llamada a la herramienta devuelve una herramienta desconocida

Compruebe el nombre expuesto de `tools/list`. Utilice el nombre con prefijo:

```text
<providerId>_<toolName>
```

No llame directamente a los nombres locales del proveedor.

## La llamada a la herramienta devuelve `tool_access_denied`

El nombre de la herramienta existe, pero el control de acceso de UMCP lo bloqueó. Compruebe `AccessProfile`, elimine el ID del proveedor de `DisabledProviderIds`, ajuste `AllowedToolNames` o `AllowedToolGroups`, o elimine la entrada coincidente de `BlockedToolNames` o `BlockedToolGroups`.

## La compilación falla en UE 5.6 con errores del estándar C++

Asegúrese de que los módulos de UMCP y los módulos de puente dependientes se compilen con C++20. Los encabezados del motor UE 5.6 utilizan sintaxis C++20 en los encabezados principales.

## Ubicación del registro de solicitudes

Los metadatos de las solicitudes se escriben en:

```text
Saved/UnifiedMcpServer/logs/mcp_requests.jsonl
```

Utilícelo para inspeccionar nombres de métodos, códigos de estado, latencia y códigos de error.

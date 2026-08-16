<!-- doc-provenance: AKDB:plugins/UnifiedMcpServer/architecture.md; docs/architecture/plugins/UnifiedMcpServer/product-facts.yml; reconciled 2026-07-04 -->
# Inicio rápido

## 1. Habilitar el plugin

Habilite `Unified MCP Server` en el explorador de plugins y reinicie el editor si Unreal lo solicita.

## 2. Habilitar el servidor

Abra:

```text
Edit -> Editor Settings -> Plugins -> Unified MCP Server
```

Active **Enable MCP Server**. Mantenga el puerto predeterminado `8732` a menos que otro servicio local ya lo esté utilizando.

## 3. Iniciar el servidor

Utilice:

```text
Tiny Tools -> AI -> Universal MCP -> Start Unified MCP Server
```

Para consultar el estado, los botones de ciclo de vida y el árbol de funciones conectadas agrupadas por plugin, utilice:

```text
Tiny Tools -> AI -> Universal MCP -> Open Control Panel
```

El área de funciones conectadas agrupa herramientas por plugin, admite el despliegue diferido de esquemas y mantiene en caché los metadatos sin cambios entre visitas. Utilice **Refresh** después de realizar cambios en la configuración de UCM para forzar una recarga completa.

En UMCP 1.0.3 y versiones posteriores, el panel de control también muestra el estado de acceso. Deshabilite un grupo de proveedor único para ocultar sus herramientas de `tools/list` y bloquear la ejecución directa de `tools/call`.

Si la opción está habilitada antes de iniciar el editor, el servidor también intenta iniciarse al cargar el módulo del editor.

## 4. Leer el archivo de intercambio (handshake)

Tras iniciar, el editor escribe:

```text
Saved/UnifiedMcpServer/agent/mcp_endpoint.json
```

Estructura de ejemplo:

```json
{
  "host": "127.0.0.1",
  "port": 8732,
  "token": "<default-token>",
  "tokens": {
    "default": {"token": "<default-token>", "scope": "default", "profile": "Project Settings"},
    "read_only": {"token": "<read-only-token>", "scope": "read_only", "profile": "Read Only"},
    "automation": {"token": "<automation-token>", "scope": "automation", "profile": "Automation"},
    "experimental_admin": {"token": "<experimental-token>", "scope": "experimental_admin", "profile": "Experimental"}
  }
}
```

Utilice el campo de compatibilidad `token` o elija un token dentro de `tokens`:

```text
Authorization: Bearer <token-seleccionado>
```

## 5. Conectar un cliente

Los clientes MCP compatibles con HTTP pueden llamar a:

```text
http://127.0.0.1:8732/mcp
```

Con el servidor en ejecución, abra el panel de control y haga clic en **Copy MCP Client Config**.
Esto copiará un fragmento de `mcp.json` listo para pegar con la URL del punto de conexión en vivo y el token Bearer predeterminado actual. Péguelo en el archivo de configuración de su cliente MCP.
Después de **Rotate Tokens**, copie el fragmento de nuevo ya que el token Bearer habrá cambiado.

En `initialize`, UMCP negocia `protocolVersion`: cuando su cliente solicita una versión compatible (`2025-06-18`, `2025-03-26` o `2024-11-05`), el servidor responde con esa versión; de lo contrario, responde con `2024-11-05`. Una comprobación mediante `GET /mcp` devuelve HTTP 405 porque UMCP utiliza el subconjunto de respuestas JSON de Streamable-HTTP y no aloja una secuencia SSE de servidor a cliente.

Los clientes que solo admiten Stdio requieren un puente instalado por el usuario como `mcp-remote`. Dicho puente no se incluye con este plugin.

## 6. Agregar herramientas (opcional)

El servidor funciona de manera independiente; este paso añade herramientas que los clientes pueden llamar. Tiene dos opciones independientes y solo necesita la que se adapte a su proyecto:

- **Su propio plugin (o cualquier plugin):** registre una función modular `IUmcpToolProvider` y sus herramientas aparecerán automáticamente como `<providerId>_<toolName>`. No se requiere ningún plugin de catálogo. Consulte [INTEGRATION.md](INTEGRATION.md).
- **Opcional — Unreal Capability Mesh (UCM):** si también posee Unreal Capability Mesh, al habilitarlo se añaden las herramientas `mesh_*` declaradas en la configuración. De este modo, los llamadores pueden ejecutar rutas UCM configuradas (por ejemplo el paquete de contexto IIS, la colocación PRS, los consejos de migración SCD y la administración de DataAsset/DataTable) a través de `mesh_execute_route` o las herramientas directas generadas `mesh_route_*`. También expone `mesh_configure_experimental_self_approval`; esa herramienta es **EXPERIMENTAL**, requiere la confirmación explícita del riesgo al habilitarla y es solo para flujos de trabajo de prueba bajo su propio riesgo.

Ambas opciones son opcionales: el servidor, el intercambio de credenciales y la conexión del cliente (pasos 1 a 5) funcionan sin ningún proveedor instalado.

## 7. Detener o rotar

Utilice el menú Tiny Tools:

```text
Tiny Tools -> AI -> Universal MCP -> Stop Unified MCP Server
Tiny Tools -> AI -> Universal MCP -> Rotate MCP Token
```

Al detener se elimina el archivo de intercambio. Al rotar se vuelve a escribir con nuevos tokens con ámbito. Ambas acciones también están disponibles desde el panel de control.

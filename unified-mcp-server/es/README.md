<!-- doc-provenance: AKDB:plugins/UnifiedMcpServer/architecture.md; docs/architecture/plugins/UnifiedMcpServer/product-facts.yml; reconciled 2026-07-04 -->
# Unified MCP Server

Unified MCP Server es un plugin de editor de Unreal Engine que proporciona un único punto de conexión (endpoint) local de Model Context Protocol (MCP) para todo el proyecto. Otros plugins acoplan herramientas mediante una pequeña interfaz modular, por lo que el servidor puede exponer nuevas capacidades sin depender directamente de dichos plugins.

El plugin se diseñó intencionadamente como infraestructura pura. No incluye ningún ejecutable externo, paquete de Node ni entorno de ejecución de Python. Aloja un punto de conexión MCP JSON-RPC 2.0 en bucle local (loopback) dentro del editor y permite a los proveedores registrar herramientas en tiempo de ejecución.

## Módulos

| Módulo | Propósito |
| --- | --- |
| `UnifiedMcpServerInterface` | Contrato público `IUmcpToolProvider` y tipos de descriptores y resultados de herramientas. |
| `UnifiedMcpServerEditor` | Host de editor para el servidor, ajustes, gestión de tokens, registro de proveedores, panel de control de estado y entradas de menú en Tiny Tools. |

## Flujo de trabajo principal

1. Habilite el plugin en el proyecto.
2. Abra `Edit -> Editor Settings -> Plugins -> Unified MCP Server`.
3. Habilite el servidor local y elija un puerto, o mantenga el puerto predeterminado `8732`.
4. Utilice `Tiny Tools -> AI -> Universal MCP -> Open Control Panel` para consultar el estado, los botones de ciclo de vida y el árbol de funciones conectadas agrupadas por plugin.
5. Inicie el servidor desde el panel o a través de `Tiny Tools -> AI -> Universal MCP -> Start Unified MCP Server`.
6. Lea los datos de conexión en `Saved/UnifiedMcpServer/agent/mcp_endpoint.json`.
7. Configure un cliente MCP para llamar a `http://127.0.0.1:8732/mcp` con `Authorization: Bearer <token>`.

## Proveedores de herramientas (Tool Providers)

Los plugins de proveedores implementan `IUmcpToolProvider` y lo registran como una función modular de Unreal. Los nombres de las herramientas expuestas utilizan el esquema:

```text
<providerId>_<toolName>
```

Cuando Unreal Capability Mesh está cargado, el proveedor de mesh integrado expone herramientas genéricas como `mesh_list_capabilities`, `mesh_list_routes`, `mesh_configure_experimental_self_approval`, `mesh_dry_run_route` y `mesh_execute_route`. También aplanar las rutas UCM declaradas en la configuración en herramientas MCP directas `mesh_route_*`. Dichas herramientas de ruta publican esquemas `inputSchema`, `outputSchema` y anotaciones de herramientas derivados de las rutas, lo que permite a los clientes inspeccionar parámetros e indicaciones de riesgo antes de realizarlas. `mesh_configure_experimental_self_approval` es **EXPERIMENTAL** y se utiliza **bajo su propio riesgo**; su habilitación requiere una confirmación explícita del riesgo. Los puentes de proveedores directos heredados aún pueden registrar nombres de herramientas específicos del producto, pero las rutas UCM representan la vía de configuración preferida en el proyecto.

`tools/call` devuelve el JSON del proveedor como contenido de texto y, cuando el resultado es un objeto JSON, como `structuredContent` de MCP. `initialize` anuncia `tools.listChanged`, y `tools/list` incluye un valor `_meta.toolsRevision` para que los clientes puedan actualizar los descriptores de herramientas almacenados en caché tras realizar cambios en la configuración de UCM.

UMCP 1.0.3 añade control de acceso sobre el punto de conexión único. Los ID de proveedores se pueden deshabilitar y los nombres de herramientas expuestos se pueden permitir o bloquear mediante nombres exactos o patrones con caracteres comodín. UMCP 1.0.4 añade perfiles (`Default`, `Read Only`, `Automation`, `Experimental`) y grupos de herramientas derivados de anotaciones. UMCP 1.0.5 añade tokens de sesión con ámbito para que diferentes clientes puedan usar accesos `default`, `read_only`, `automation` o `experimental_admin` a través del mismo punto de conexión `/mcp`. UMCP 1.0.6 añade bloqueos de Access Guard en tiempo de ejecución y un Access Journal seguro para secretos para diagnósticos de las últimas llamadas `tools/call`. La misma política se aplica tanto a `tools/list` como a `tools/call`. El panel de control muestra si las funciones conectadas están expuestas, bloqueadas, ocultas o no disponibles.

## Seguridad

- El servidor se vincula exclusivamente a `127.0.0.1`.
- El servidor está deshabilitado de forma predeterminada.
- Las solicitudes requieren un token Bearer del archivo de intercambio (handshake).
- El control de acceso por proveedor/herramienta puede ocultar herramientas en `tools/list` y bloquear la ejecución directa de `tools/call`.
- Los bloqueos de Access Guard en tiempo de ejecución residen solo en memoria y se borran al detener el servidor.
- Los tokens se pueden rotar desde **Tiny Tools -> AI -> Universal MCP**.
- El archivo de intercambio se elimina cuando el servidor se detiene.
- Los metadatos de las solicitudes se registran en `Saved/UnifiedMcpServer/logs/mcp_requests.jsonl`.
- Los diagnósticos de acceso se registran en `Saved/UnifiedMcpServer/logs/access_audit.jsonl` omitiendo las claves de argumentos que parecen secretos.

## Documentación

| Documento | Propósito |
| --- | --- |
| [BUYER_GUIDE.md](BUYER_GUIDE.md) | Descripción general del producto, casos de uso y límites. |
| [QUICKSTART.md](QUICKSTART.md) | Primera configuración y conexión de clientes. |
| [UserManual.md](UserManual.md) | Trabajo diario en el editor. |
| [TechnicalOverview.md](TechnicalOverview.md) | Arquitectura y comportamiento del protocolo. |
| [INTEGRATION.md](INTEGRATION.md) | Cómo los plugins de proveedores acoplan herramientas. |
| [SettingsReference.md](SettingsReference.md) | Ajustes y archivos guardados. |
| [CodeDocumentation.md](CodeDocumentation.md) | Estructura del código fuente y contratos. |
| [FAQ.md](FAQ.md) | Preguntas frecuentes de compradores. |
| [TROUBLESHOOTING.md](TROUBLESHOOTING.md) | Fallos comunes y soluciones. |
| [ReleaseChecklist.md](ReleaseChecklist.md) | Lista de verificación para lanzamientos y empaquetado de Fab. |

## Empaquetado

`Config/FilterPlugin.ini` incluye `/Documentation/...` y `/CHANGELOG.md` para que los paquetes de Fab contengan esta documentación.

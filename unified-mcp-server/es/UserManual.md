<!-- doc-provenance: AKDB:plugins/UnifiedMcpServer/architecture.md; docs/architecture/plugins/UnifiedMcpServer/product-facts.yml; reconciled 2026-07-04 -->
# Manual del usuario

## Apertura de los ajustes

Unified MCP Server se configura en:

```text
Edit -> Editor Settings -> Plugins -> Unified MCP Server
```

Ajustes:

| Ajuste | Predeterminado | Significado |
| --- | --- | --- |
| Enable MCP Server | deshabilitado | Permite que el módulo del editor ejecute el servidor MCP local. |
| Server Port | 8732 | Puerto TCP utilizado en `127.0.0.1`. |
| Validate Tool Arguments | deshabilitado | Valida de forma opcional los argumentos de `tools/call` con respecto al `inputSchema` de cada herramienta antes de llamar al proveedor. |
| Access Profile | Default | Modo de exposición de alto nivel: Default, Read Only, Automation o Experimental. |
| Disabled Provider IDs | vacío | Oculta y bloquea todas las herramientas de los ID de proveedores coincidentes. |
| Allowed Tool Names | vacío | Lista permitida opcional de nombres de herramientas o patrones con caracteres comodín expuestos. Vacío significa permitir todas las herramientas a menos que estén bloqueadas. |
| Blocked Tool Names | vacío | Oculta y bloquea los nombres de herramientas o patrones con caracteres comodín expuestos. |
| Allowed Tool Groups | vacío | Lista permitida opcional de grupos derivados de anotaciones como `read_only`, `non_destructive` o `idempotent`. |
| Blocked Tool Groups | vacío | Oculta y bloquea grupos derivados de anotaciones como `risky`, `destructive` o `open_world`. |
| Enable Access Journal | habilitado | Escribe diagnósticos de acceso seguros para secretos para `tools/call`. |
| Access Journal Ring Capacity | 500 | Entradas recientes conservadas en memoria para el panel de control y diagnósticos de Blueprint. |
| Access Journal Max File Bytes | 5242880 | Tamaño máximo de `access_audit.jsonl` antes de la rotación de un archivo. |

## Menú Tiny Tools

El editor añade acciones de ciclo de vida y estado en **Tiny Tools -> AI -> Universal MCP**:

| Acción | Resultado |
| --- | --- |
| Open Control Panel | Abre el panel de control de UMCP con botones de ciclo de vida y el árbol de funciones conectadas agrupadas por plugin. |
| Start Unified MCP Server | Inicia el punto de conexión HTTP en bucle local. |
| Stop Unified MCP Server | Detiene el punto de conexión y elimina el archivo de intercambio. |
| Rotate MCP Token | Genera nuevos tokens Bearer con ámbito y vuelve a escribir el archivo de intercambio. |

La sección **AI** agrupa Unified MCP Server con otros plugins de IA de Tiny Tool Development como Internal Index Service.

## Panel de control (Control Panel)

El panel de control muestra:

| Área | Detalles |
| --- | --- |
| Status | Estado ejecutándose/detenido, ajuste de inicio, URL del punto de conexión, presencia/recuento de tokens, recuento de solicitudes, recuento de proveedores, recuento de herramientas y ruta del archivo de intercambio. |
| Actions | Iniciar, detener, rotar tokens, abrir la carpeta de agentes y actualizar. |
| Tabs | Connected Functions para proveedores/herramientas/esquemas, y Access Activity para llamadas recientes a herramientas y controles de bloqueo en tiempo de ejecución. |
| Connected Functions | Grupos de plugins desplegables con conmutadores de proveedores, filas de herramientas, estado de acceso/preparación, nombres de herramientas MCP, descripciones y tablas de esquemas de entrada/salida cargadas de forma diferida. |
| Access Activity | Llamadas recientes a herramientas con detalles de token/cliente/resultado, recuento de bloqueos en tiempo de ejecución, actualizar, bloquear/desbloquear tokens/herramientas y acciones para limpiar bloqueos en tiempo de ejecución. |

### Disposición de Connected Functions

Connected Functions utiliza un árbol jerárquico similar al catálogo de rutas de Capability Mesh:

1. **Grupo de plugins** — una fila por plugin con el recuento de interfaces y, cuando el grupo se asigna a un solo proveedor, un botón para habilitar/deshabilitar el acceso. Haga clic en la flecha para mostrar u ocultar las herramientas de ese plugin.
2. **Fila de herramienta** — una fila por herramienta MCP acoplada o capacidad UCM declarada en la configuración. Haga clic en la flecha para mostrar u ocultar las tablas de esquemas de entrada/salida de esa herramienta.

La disposición de las columnas depende del estado de despliegue **dentro de cada grupo de plugins**:

| Estado | Columnas |
| --- | --- |
| Todas las herramientas replegadas | `Provider`, `Ready`, `Tool`, `Description` (ancha) |
| Cualquier herramienta desplegada | `Provider`, `Ready`, `Tool`, `Input`, `Output`, `Description` |

**Agrupación de proveedores:** las herramientas directas del proveedor aparecen bajo su `GetProviderDisplayName()`. Las herramientas de rutas UCM aplanadas (`mesh_route_*`) aparecen bajo el **plugin propietario** obtenido de los metadatos de capacidad de Capability Mesh (por ejemplo Internal Index Service o SmartContentDiet), no bajo la entrada del host de mesh. Las herramientas genéricas del host de mesh como `mesh_list_routes` y `mesh_reload_setup` permanecen bajo **Unreal Capability Mesh**.

**Rendimiento:** el panel carga los metadatos de las herramientas de forma asíncrona. Los datos no modificados se sirven desde la caché en visitas repetidas, inicios/paradas y despliegues/repliegues. Utilice **Refresh** para forzar una recarga completa tras realizar cambios en la configuración de UCM.

Las filas marcadas como `Needs approval` son capacidades UCM que requieren aprobación. Su información emergente apunta a la ruta de autoaprobación automática **EXPERIMENTAL** en las rutas UCM o `mesh_configure_experimental_self_approval`; utilícela solo para pruebas bajo su propio riesgo.

Las filas marcadas como `Blocked` u `Hidden` no se exponen a los clientes MCP. UMCP las elimina de `tools/list` y devuelve `tool_access_denied` si un cliente intenta llamar directamente al nombre de la herramienta.

Los bloqueos en tiempo de ejecución de la pestaña **Access Activity** son bloqueos temporales de la sesión del editor. No se escriben en los ajustes del editor, ocultan la herramienta de `tools/list` para el token afectado, rechazan llamadas directas con `runtime_access_denied` y se borran al detener el servidor.

Las descripciones de herramientas incluyen indicaciones de anotaciones MCP cuando los proveedores las publican, como comportamiento de solo lectura, destructivo, idempotente o de mundo abierto. El panel también muestra los grupos derivados utilizados por las políticas de acceso por perfil y por grupo.

## Archivos de conexión

Archivo de intercambio (handshake):

```text
Saved/UnifiedMcpServer/agent/mcp_endpoint.json
```

Registro de solicitudes:

```text
Saved/UnifiedMcpServer/logs/mcp_requests.jsonl
```

Diario de acceso (Access Journal):

```text
Saved/UnifiedMcpServer/logs/access_audit.jsonl
```

El archivo de intercambio contiene el host local, el puerto, el `token` de compatibilidad y los `tokens` con ámbito. Trátelo como una credencial local.

El diario de acceso omite las claves de argumentos que parecen secretos como token, secret, password, API key, authorization y bearer.

## Llamadas MCP admitidas

El servidor gestiona estos métodos JSON-RPC:

| Método | Comportamiento |
| --- | --- |
| `initialize` | Devuelve la versión del protocolo, capacidades de herramientas e información del servidor. |
| `notifications/initialized` | Acusa recibo de la inicialización del cliente. |
| `ping` | Devuelve un resultado vacío. |
| `tools/list` | Devuelve todas las herramientas de los proveedores registrados, incluyendo `inputSchema`, `outputSchema` opcional, `annotations` opcionales y `_meta.toolsRevision`. |
| `tools/call` | Enruta un nombre de herramienta con prefijo a su proveedor y devuelve resultados JSON como texto y como `structuredContent` cuando es posible. |

Los métodos desconocidos devuelven un error JSON-RPC de método no encontrado.

## Herramientas de tareas del editor (Editor Job Tools)

UMCP expone herramientas de agregación de tareas del editor en solo lectura cuando Unreal Capability Mesh está disponible:

| Herramienta | Propósito |
| --- | --- |
| `jobs_list` | Combina las tareas recientes de rutas UCM fijas para IIS, SmartContentDiet, LLM Store y UMCP. Los argumentos opcionales `provider_id` y `max_count` reducen el resultado. |
| `jobs_status` | Busca un ID de tarea en la misma tabla de rutas y devuelve el ID del proveedor origen coincidente. |

Los plugins de origen publican su propia lista/estado de tareas del editor a través de rutas UCM y no dependen de UMCP. Si UCM o una ruta no están disponibles, la agregación omite esa ruta y sigue devolviendo tareas de los proveedores disponibles.

## Trabajo con proveedores

Unified MCP Server no contiene herramientas de proyecto por sí mismo. Los proveedores las añaden. Un proveedor suministra descriptores, esquemas de entrada y lógica de invocación mediante `IUmcpToolProvider`.

Cuando un proveedor está instalado, las herramientas aparecen como:

```text
provider_tool
```

Por ejemplo:

```text
mesh_route_iis_agent_search_v1_<hash>
```

Cuando Unreal Capability Mesh está cargado, UMCP expone herramientas genéricas de mesh:

```text
mesh_reload_setup
mesh_list_capabilities
mesh_list_routes
mesh_configure_experimental_self_approval
mesh_dry_run_route
mesh_execute_route
mesh_invoke_endpoint
```

UMCP también publica cada ruta declarada de Capability Mesh como una herramienta MCP aplanada:

```text
mesh_route_<sanitized_route_id>_<hash>
```

Las herramientas de rutas aplanadas aceptan `mode: "execute"` o `mode: "dry_run"`. Si se omite `input` o `input_json`, los argumentos restantes se tratan como el objeto de entrada de la ruta. Para las rutas que internamente vinculan un `request_json` serializado, UMCP traslada automáticamente los argumentos aplanados a `request_json`. Cada herramienta de ruta aplanada publica un `inputSchema`, un `outputSchema` y anotaciones MCP derivados de la ruta, como `readOnlyHint`, `destructiveHint` y `openWorldHint`. Las rutas mutativas siguen pasando por las comprobaciones de política y aprobación de Capability Mesh.

Utilice `mesh_execute_route` para operaciones mutativas de modo que las comprobaciones de política y aprobación de la ruta de Capability Mesh permanezcan activas.

`mesh_configure_experimental_self_approval` es explícitamente **EXPERIMENTAL** y **bajo su propio riesgo**. Puede leer o cambiar la autoaprobación automática de Capability Mesh a nivel global o por ID de ruta. Su habilitación requiere `acknowledge_experimental_risk: true`.

## Notas operativas

- Utilice un puerto único por instancia del editor.
- Rote los tokens tras compartir registros o capturas de pantalla que puedan mostrar el archivo de intercambio.
- Detenga el servidor cuando un agente externo ya no necesite acceso.
- Si no hay plugins de proveedores habilitados, `tools/list` puede devolver legítimamente una lista vacía.

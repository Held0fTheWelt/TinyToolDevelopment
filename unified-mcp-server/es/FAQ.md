<!-- doc-provenance: AKDB:plugins/UnifiedMcpServer/architecture.md; docs/architecture/plugins/UnifiedMcpServer/product-facts.yml; reconciled 2026-07-04 -->
# Preguntas frecuentes (FAQ)

## ¿Incluye este plugin un modelo de IA?

No. Unified MCP Server es una infraestructura de conexión. Expone herramientas de plugins de proveedores a clientes MCP locales.

## ¿Incluye un ejecutable independiente?

No. El servidor se ejecuta dentro de Unreal Editor y no incluye ningún ejecutable externo.

## ¿Incluye Node.js, Python o mcp-remote?

No. Los clientes que solo admiten Stdio pueden necesitar un puente instalado por el usuario como `mcp-remote`, pero no viene empaquetado.

## ¿Está habilitado el servidor de forma predeterminada?

No. Está deshabilitado de forma predeterminada y debe habilitarse en Editor Settings o iniciarse manualmente desde **Tiny Tools -> AI -> Universal MCP**.

## ¿Escucha en la red?

No. Se vincula exclusivamente a `127.0.0.1`.

## ¿Cómo se autentican las solicitudes?

El servidor genera tokens Bearer con ámbito al iniciar. Los clientes los leen de `Saved/UnifiedMcpServer/agent/mcp_endpoint.json` y envían un token en el encabezado `Authorization`.

## ¿Admite múltiples tokens con ámbito?

Sí. UMCP 1.0.5 escribe los tokens de sesión `default`, `read_only`, `automation` y `experimental_admin` en el archivo de intercambio. Todos los tokens utilizan el mismo punto de conexión local `/mcp`; el ámbito cambia qué perfil de acceso se fuerza para `tools/list` y `tools/call`.

## ¿Por qué está vacía mi lista de herramientas?

El servidor base es infraestructura. Habilite Unreal Capability Mesh para obtener el proveedor genérico `mesh_*`, o habilite otro plugin que registre un `IUmcpToolProvider`. Compruebe también el control de acceso de UMCP: los proveedores deshabilitados, los perfiles restrictivos, las listas permitidas activas, los patrones de herramientas bloqueadas o los grupos de herramientas bloqueados pueden ocultar intencionadamente herramientas de `tools/list`.

## ¿Puedo ocultar o bloquear proveedores y herramientas específicos?

Sí. UMCP mantiene un único punto de conexión local y aplica el control de acceso antes de que las herramientas lleguen a los clientes MCP. Deshabilite ID de proveedores, elija un perfil de acceso, añada nombres de herramientas o grupos exactos o con caracteres comodín a las listas de permisos/bloqueos, o utilice el conmutador de proveedores del panel de control para grupos de proveedores individuales. Se aplica la misma política para `tools/list` y `tools/call`.

## ¿Puedo bloquear temporalmente una herramienta durante una sesión?

Sí. UMCP 1.0.6 añade bloqueos de Access Guard en tiempo de ejecución desde el panel de control y los diagnósticos de Blueprint. Los bloqueos en tiempo de ejecución pueden ocultar una herramienta para un token con ámbito o globalmente, rechazar llamadas directas con `runtime_access_denied` y se borran al detener el servidor.

## ¿Almacena secretos el diario de acceso (Access Journal)?

Está diseñado para diagnósticos seguros de secretos. Las claves de argumentos que parecen secretos como token, secret, password, API key, authorization y bearer se omiten en la memoria y en el diario de acceso JSONL. Las cadenas redactadas y las entradas sanitizadas en RAM están limitadas por los ajustes.

## ¿Qué es `mesh_configure_experimental_self_approval`?

Es una herramienta del proveedor Capability Mesh para autoaprobación automática **EXPERIMENTAL**. Puede cambiar si las rutas UCM que requieren aprobación se autoaprueban a nivel global o por ID de ruta. Su habilitación requiere `acknowledge_experimental_risk: true` y es solo para flujos de trabajo de prueba bajo su propio riesgo.

## ¿Pueden varios plugins añadir herramientas?

Sí. Cualquier plugin puede registrar un `IUmcpToolProvider`. Los nombres de las herramientas llevan como prefijo el ID del proveedor.

## ¿Pueden los clientes ver los parámetros de las herramientas y el riesgo?

Sí. `tools/list` incluye el `inputSchema` de cada herramienta, el `outputSchema` opcional y las anotaciones opcionales de la herramienta. Las herramientas de rutas UCM los derivan de las vinculaciones de rutas, los manifiestos de esquemas, la política y los efectos secundarios.

## ¿Cómo inspecciono las herramientas acopladas en el editor?

Abra **Tiny Tools -> AI -> Universal MCP -> Open Control Panel**. El área de funciones conectadas agrupa herramientas por plugin, admite el despliegue diferido de esquemas de entrada/salida y mantiene en caché los metadatos sin cambios entre visitas. Haga clic en **Refresh** tras realizar cambios en la configuración de UCM para forzar una recarga completa.

## ¿Por qué rechazó UMCP los argumentos de mi herramienta antes de que se ejecutara el proveedor?

La opción `Validate Tool Arguments` está habilitada. UMCP comprueba entonces los argumentos entrantes con respecto al `inputSchema` de la herramienta seleccionada y devuelve `invalid_tool_arguments` en caso de faltar campos obligatorios, campos desconocidos no permitidos, discrepancias de tipo o discrepancias de enumeración.

## ¿A qué versiones de Unreal Engine se dirige?

El plugin está diseñado para plugins de código de Unreal Engine 5.x y utiliza C++20 para compatibilidad actual con UE 5.6.

## ¿Está pensado para juegos empaquetados (Packaged Games)?

No. El servidor actual es infraestructura de editor para herramientas y agentes locales.

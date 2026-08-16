<!-- doc-provenance: AKDB:plugins/UnifiedMcpServer/architecture.md; docs/architecture/plugins/UnifiedMcpServer/product-facts.yml; reconciled 2026-07-04 -->
# Referencia de ajustes

Los ajustes residen en `UUmcpSettings` y se almacenan en la configuración del editor.

Abra:

```text
Edit -> Editor Settings -> Plugins -> Unified MCP Server
```

## Servidor

| Ajuste | Campo de configuración | Predeterminado | Notas |
| --- | --- | --- | --- |
| Enable MCP Server | `bEnableServer` | `false` | Deshabilitado por defecto. Si es verdadero, el módulo del editor intenta iniciar el servidor al iniciar. |
| Server Port | `ServerPort` | `8732` | Puerto TCP local para el punto de conexión en bucle local. Rango válido: 1-65535. |

## Herramientas (Tools)

| Ajuste | Campo de configuración | Predeterminado | Notas |
| --- | --- | --- | --- |
| Validate Tool Arguments | `bValidateToolArguments` | `false` | Cuando está habilitado, UMCP valida los argumentos entrantes de `tools/call` con respecto al `inputSchema` de cada herramienta antes de llamar al proveedor. La validación es ligera: campos obligatorios, campos desconocidos para `additionalProperties:false`, tipos primitivos y enumeraciones. |

## Control de acceso (Access Control)

| Ajuste | Campo de configuración | Predeterminado | Notas |
| --- | --- | --- | --- |
| Access Profile | `AccessProfile` | `Default` | Modo de exposición de alto nivel. `Default` conserva el comportamiento heredado, `Read Only` solo expone herramientas anotadas como solo lectura, `Automation` oculta herramientas arriesgadas/destructivas/de mundo abierto/no clasificadas, y `Experimental` permite intencionadamente herramientas arriesgadas a menos que se bloqueen manualmente. |
| Disabled Provider IDs | `DisabledProviderIds` | vacío | ID de proveedores ocultos en `tools/list` y bloqueados en el momento de llamar a `tools/call`. El panel de control puede conmutar grupos de proveedores individuales a esta lista. |
| Allowed Tool Names | `AllowedToolNames` | vacío | Lista permitida opcional de nombres de herramientas MCP expuestos o patrones con caracteres comodín como `iis_search` o `mesh_route_*`. Vacío significa que se permiten todas las herramientas a menos que estén deshabilitadas o bloqueadas. |
| Blocked Tool Names | `BlockedToolNames` | vacío | Nombres de herramientas MCP expuestos o patrones con caracteres comodín ocultos en `tools/list` y bloqueados en el momento de llamar a `tools/call`. |
| Allowed Tool Groups | `AllowedToolGroups` | vacío | Lista permitida opcional de grupos derivados de anotaciones como `read_only`, `non_destructive`, `idempotent`, `risky`, `destructive`, `open_world` o `unclassified`. |
| Blocked Tool Groups | `BlockedToolGroups` | vacío | Grupos derivados de anotaciones ocultos en `tools/list` y bloqueados en el momento de llamar a `tools/call`. |

El orden de las políticas es: proveedor deshabilitado, bloqueo explícito de herramienta, perfil de acceso, grupo bloqueado, listas permitidas opcionales de herramientas/grupos, y luego expuesto. Si cualquiera de las listas permitidas contiene entradas, la herramienta se expone cuando coincide su nombre o al menos un grupo. Se aplica la misma política para `tools/list` y `tools/call`.

Los bloqueos de Access Guard en tiempo de ejecución creados desde el panel de control o mediante asistentes de Blueprint son locales de la sesión y se aplican después de la política permanente. Ocultan las herramientas coincidentes en `tools/list`, rechazan llamadas directas a `tools/call` y se borran al detener el servidor.

Las herramientas de agregación de tareas son de solo lectura, pero siguen pasando por la misma política de proveedor/herramienta/perfil que cualquier otra herramienta MCP. Bloquear `jobs_*` o el proveedor `jobs` oculta tanto `jobs_list` como `jobs_status`.

## Diario de acceso (Access Journal)

| Ajuste | Campo de configuración | Predeterminado | Notas |
| --- | --- | --- | --- |
| Enable Access Journal | `bEnableAccessJournal` | `true` | Escribe diagnósticos semánticos de acceso para `tools/call`. |
| Access Journal Ring Capacity | `AccessJournalRingCapacity` | `500` | Entradas recientes conservadas en RAM para el panel de control y diagnósticos de Blueprint. |
| Access Journal Max File Bytes | `AccessJournalMaxFileBytes` | `5242880` | Tamaño máximo de `access_audit.jsonl` antes de la rotación de un archivo. |
| Access Journal Redacted String Limit | `AccessJournalRedactedStringLimit` | `128` | Longitud máxima de cadena en argumentos JSONL redactados. |
| Access Journal Max RAM Entry Bytes | `AccessJournalMaxRamEntryBytes` | `8192` | Tamaño máximo del JSON de argumentos sanitizado conservado en memoria por entrada. Las claves que parecen secretos se omiten. |

## Archivos generados

| Archivo | Propósito |
| --- | --- |
| `Saved/UnifiedMcpServer/agent/mcp_endpoint.json` | Intercambio de credenciales de conexión que contiene host, puerto, token de compatibilidad y tokens de sesión con ámbito. |
| `Saved/UnifiedMcpServer/logs/mcp_requests.jsonl` | Registro de metadatos de solicitudes. |
| `Saved/UnifiedMcpServer/logs/access_audit.jsonl` | Diario de acceso semántico seguro para secretos para `tools/call`. |

## Valores de seguridad predeterminados

- Servidor deshabilitado por defecto.
- Solo host de bucle local.
- Se requiere token Bearer.
- Los tokens se pueden rotar desde **Tiny Tools -> AI -> Universal MCP**.
- El archivo de intercambio se elimina cuando el servidor se detiene.
- UMCP 1.0.5 escribe los tokens de sesión `default`, `read_only`, `automation` y `experimental_admin`. El campo heredado `token` se mantiene como token predeterminado por compatibilidad.
- UMCP 1.0.6 omite de los diagnósticos de acceso las claves de argumentos que parecen secretos, incluidos token, secret, password, API key, authorization y bearer.

## Selección de puerto

Utilice un puerto diferente si:

- otra instancia del editor ya está utilizando `8732`
- un servicio local está vinculado al mismo puerto
- proyectos separados necesitan puntos de conexión MCP independientes

La URL del cliente es:

```text
http://127.0.0.1:<ServerPort>/mcp
```

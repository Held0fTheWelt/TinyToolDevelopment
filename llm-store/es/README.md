<!-- doc-provenance: AKDB:plugins/LLMStore/architecture.md; docs/architecture/plugins/LLMStore/product-facts.yml; reconciled 2026-06-20 -->
# LLM Store

LLM Store es un plugin de Unreal Engine para administrar de forma centralizada proveedores de IA, modelos, rutas de tareas (task routes), políticas (policies), costos, secretos (secrets) y agentes externos opcionales. Está diseñado como un plugin de infraestructura: las herramientas del editor y los sistemas en tiempo de ejecución no necesitan saber si una solicitud la atiende Ollama, llama.cpp, OpenAI, Claude, Gemini, Azure OpenAI, Mistral, OpenRouter o un proveedor simulado (mock). Llama a una ruta estable como `asset.explain`, `docs.summarize` o `naming.review`.

## ¿Para quién es?

LLM Store es útil cuando un proyecto incluye más de una función de IA y esas funciones no deben codificar de forma rígida credenciales de proveedores, nombres de modelos, reglas de la nube o lógica de costos.

Casos de uso típicos:

- utilizar modelos locales para desarrollo, pruebas, CI o flujos de trabajo adyacentes a distribución
- permitir modelos en la nube durante el desarrollo pero bloquearlos en compilaciones de distribución (shipping)
- enrutar tareas de IA mediante nombres de tareas estables en lugar de nombres de modelos directos
- evaluar costos por proveedor, modelo y ruta
- mantener las claves API fuera de la configuración del proyecto enviada al repositorio
- ofrecer la misma superficie de integración a los equipos de C++ y Blueprint
- conectar agentes opcionales como Codex, Claude, Cursor o herramientas específicas del estudio
- permitir que plugins específicos del proyecto proporcionen contexto sin que LLM Store dependa de ellos
- exponer el historial de tareas del editor mediante rutas UCM sin depender de Unified MCP Server

## Módulos

| Módulo | Propósito |
| --- | --- |
| `LLMStoreInterface` | Estructuras públicas, interfaz fachada, contratos de proveedores, contratos de complementos y clases base de Blueprint. |
| `LLMStore` | Subsistema del motor, enrutamiento, ejecución, gobernanza, secretos, libro de costos (cost ledger) y puente de agentes. |
| `LLMStoreEditor` | Pestaña del editor para configuración, rutas, estado, ayuda, agentes, costos y gobernanza. |

## Conceptos clave

| Concepto | Significado |
| --- | --- |
| Proveedor (Provider) | Servicio técnico o servidor local, por ejemplo `ollama`, `llamacpp` u `openai`. |
| Modelo | Un modelo concreto servido por un proveedor. |
| Ruta (Route) | Nombre de tarea estable que se resuelve en un modelo, una cadena de respaldo (fallback) y una política. |
| Política (Policy) | Regla para acceso a la nube, comportamiento exclusivo local, presupuesto de contexto, listas de inclusión/exclusión de proveedores y límites de costo. |
| Regla de costo (Cost Rule) | Regla de precios usada para estimar el costo de la solicitud a partir de los tokens de solicitud (prompt) y respuesta (completion). |
| Agente | Adaptador opcional para una herramienta externa como Codex, Claude, Cursor o un asistente del estudio. |
| Proveedor de contexto | Complemento que proporciona paquetes de contexto neutrales desde fuentes del proyecto, assets, documentación u otros sistemas. |

## Interfaz de usuario del editor

Abra el plugin en:

```text
Tiny Tools -> LLM Store
```

Pestañas principales:

- `Setup`: **Quick-Start** con un solo clic en el primer uso (Mock / Ollama / nube), luego creación de proveedores y modelos, edición de URL base, establecimiento de claves y prueba de conectividad.
- `Routes`: configuración de rutas de tareas, cadenas de respaldo, modelos simulados, plantillas de solicitudes y políticas.
- `Agents`: inspección de adaptadores para agentes Codex, Claude, Cursor y personalizados; apertura de diálogos de autenticación.
- `Costs`: análisis de solicitudes, tokens, costo estimado, aciertos de caché y exportación de informes CSV.
- `Governance`: inspección de estado, eventos de auditoría, preajustes (presets), estado de caché y reglas de compilación.
- `Status`: lectura del estado actual de la configuración, advertencias, bloqueos e inventario.
- `Help`: explicación en el editor de conceptos y flujos de trabajo previstos.
- `Advanced`: secciones opcionales de la interfaz aportadas por complementos.

## Inicio rápido

1. Abra `Tiny Tools -> LLM Store`.
2. En **Setup**, utilice la tarjeta **Quick-Start** (Mock, Ollama local o nube OpenAI/Anthropic) para obtener con un solo clic una ruta `default` funcional.
3. O cree manualmente un proveedor y un modelo, y luego agregue rutas en la pestaña `Routes`.
4. Pruebe el proveedor, el modelo y la ruta; confirme que el cartel de disponibilidad cambie a verde.
5. Agregue reglas de costos si el análisis de la nube o del presupuesto es importante.
6. Ejecute una solicitud y revise las pestañas `Costs` y `Status`.

Consulte [QUICKSTART.md](QUICKSTART.md) para ver detalles paso a paso (tarjeta Quick-Start y configuración manual).

## Proveedores locales

Tipos de proveedores locales o alojados de forma autónoma admitidos:

- `ollama`
- `llamacpp`
- `lmstudio`
- `vllm`
- `tgi`
- `mock`

Estos proveedores no requieren claves API por defecto.

## Proveedores en la nube

Tipos de proveedores en la nube admitidos:

- `openai`
- `anthropic`
- `gemini`
- `azure-openai`
- `mistral`
- `openrouter`

Los proveedores en la nube suelen requerir una clave API. Las claves se almacenan en el backend de secretos configurado, nunca en `Config/LLMStore.json`.

## Blueprint y C++

La funcionalidad orientada al consumidor está disponible tanto desde C++ como desde Blueprints.

Clases base de Blueprint:

- `ULLMBlueprintProviderAddOn`
- `ULLMBlueprintEmbeddingProviderAddOn`
- `ULLMBlueprintContractAddOn`
- `ULLMBlueprintPolicyAddOn`
- `ULLMBlueprintTestAddOn`
- `ULLMBlueprintContextProviderAddOn`
- `ULLMBlueprintAgentAddOn`

Consulte [INTEGRATION.md](INTEGRATION.md) y [CodeDocumentation.md](CodeDocumentation.md).

La ejecución de rutas con y sin transmisión continua (streaming) comparte una cola controlada por concurrencia. Utilice `EnqueueRoute` para tareas locales largas; `ExecuteRouteStreaming` sigue la misma protección de solicitud activa mientras devuelve fragmentos de transmisión a través de su API de devolución de llamada.

## Autenticación de agentes

La pestaña `Agents` puede mostrar un botón `Authenticate...` para cada agente. El diálogo muestra el comando de inicio de sesión, las instrucciones, el enlace de ayuda y las acciones para ejecutar o copiar el comando. Las credenciales permanecen en la herramienta externa; LLM Store solo almacena el estado y las instrucciones.

Consulte [AGENT_AUTHENTICATION.md](AGENT_AUTHENTICATION.md).

## Seguimiento de costos

LLM Store estima el costo a partir de:

- tokens de solicitud reportados por el proveedor o estimados por la tienda
- tokens de respuesta reportados por el proveedor o estimados por la tienda
- entradas `FLLMCostRule` coincidentes

El libro de costos se almacena en:

```text
Saved/LLMStore/CostLedger.json
```

Las exportaciones a CSV se guardan por defecto en:

```text
Saved/LLMStore/CostReports/LLMStoreCostReport.csv
```

Consulte [COST_TRACKING.md](COST_TRACKING.md).

## Privacidad y seguridad

- Las claves API no deben incluirse en `Config/LLMStore.json`.
- Los proveedores locales son la opción predeterminada preferida para datos confidenciales del proyecto.
- Las políticas pueden restringir el uso de la nube por ruta.
- Las reglas de compilación pueden bloquear proveedores en la nube para compilaciones de distribución.
- La ejecución de agentes es explícita y se controla mediante indicadores de solicitud.

Consulte [SECRET_BACKENDS.md](SECRET_BACKENDS.md) para archivos locales cifrados, Windows Credential Manager, macOS Keychain, 1Password y Azure Key Vault.

## Comience aquí

- [BUYER_GUIDE.md](BUYER_GUIDE.md): descripción general para compradores, propuesta de valor y flujos de trabajo prácticos.
- [QUICKSTART.md](QUICKSTART.md): primera configuración funcional de proveedor/modelo/ruta.
- [UserManual.md](UserManual.md): flujo de trabajo completo del editor y uso de la interfaz.
- [FAQ.md](FAQ.md): preguntas y respuestas para compradores preparadas para Fab.

## Referencia

- [SettingsReference.md](SettingsReference.md): campos de configuración, valores predeterminados, archivos JSON de configuración y líneas base recomendadas.
- [ProviderReference.md](ProviderReference.md): tipos de proveedores locales/nube admitidos, URL base y notas.
- [RoutePolicyReference.md](RoutePolicyReference.md): políticas de rutas, restricciones nube/local, reglas de presupuesto y reglas de compilación.
- [COST_TRACKING.md](COST_TRACKING.md): libro de costos, reglas de costos, exportación a CSV y flujo de trabajo de análisis.
- [SECRET_BACKENDS.md](SECRET_BACKENDS.md): almacenamiento local cifrado y comportamiento de backends de secretos externos.
- [AGENT_AUTHENTICATION.md](AGENT_AUTHENTICATION.md): adaptadores de agentes de estilo Codex/Claude/Cursor y comportamiento del diálogo de autenticación.
- [INTEGRATION.md](INTEGRATION.md): patrones de integración en C++ y Blueprint para otros plugins.
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md): problemas comunes y soluciones.
- [TechnicalOverview.md](TechnicalOverview.md): descripción general de la arquitectura a nivel de mantenedores.

## Assets incluidos

- [Screenshots/](Screenshots): capturas de pantalla de la documentación y diagramas visuales del flujo de trabajo.

## Descripciones visuales

- [Screenshots/01-workflow-overview.svg](Screenshots/01-workflow-overview.svg)
- [Screenshots/02-editor-tabs.svg](Screenshots/02-editor-tabs.svg)
- [Screenshots/03-agent-cost-governance.svg](Screenshots/03-agent-cost-governance.svg)

## Flujo de trabajo rápido con JSON de configuración

1. Abra `Tiny Tools -> LLM Store`.
2. Configure proveedores, modelos, rutas, políticas y reglas de costos.
3. Abra `Governance`.
4. Utilice `Export Setup JSON` para guardar la configuración actual en cualquier archivo elegido.
5. Utilice `Validate JSON` para inspeccionar un archivo de configuración sin aplicarlo.
6. Utilice `Import JSON` solo después de que la validación sea correcta.

Los secretos nunca se escriben en el JSON de configuración. Vuelva a conectar las claves del proveedor a través del backend de secretos o mediante variables de entorno después de importar una configuración compartida.

## Visibilidad de tareas de UCM

LLM Store publica el historial de tareas del editor en solo lectura mediante `llmstore.editor.jobs.list.v1` y `llmstore.editor.jobs.status.v1` cuando Unreal Capability Mesh está habilitado. Unified MCP Server puede agregar esas rutas a través de `jobs_list` / `jobs_status`; LLM Store en sí sigue siendo autárquico y no requiere una dependencia en tiempo de compilación con UMCP.

## Commandlet

Ejecute las comprobaciones de políticas de CI desde una terminal local o un ejecutor de automatización:

```powershell
<UnrealEditorCommand> "D:\PluginProjectGit\PluginProject.uproject" -run=LLMStoreCIPolicy -unattended -nop4 -nosplash -NoShaderCompile
```

`<UnrealEditorCommand>` es el destino de la línea de comandos de Unreal Editor para su instalación local del motor.

El commandlet comprueba los proveedores, modelos, rutas, políticas y reglas de compilación configurados. Está pensado para la gobernanza de versiones, no para pruebas comparativas de proveedores en vivo.

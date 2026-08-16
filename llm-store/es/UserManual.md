<!-- doc-provenance: AKDB:plugins/LLMStore/architecture.md; docs/architecture/plugins/LLMStore/product-facts.yml; reconciled 2026-06-20 -->
# Manual del usuario

Este manual describe LLM Store desde la perspectiva de un comprador, artista técnico, desarrollador de Blueprint o programador de herramientas. Explica los flujos de trabajo del editor y remite a referencias técnicas más profundas cuando resulta útil.

## Objetivo del plugin

LLM Store es una capa de control centralizada de IA para proyectos de Unreal Engine. Otros plugins y herramientas no necesitan saber si una instrucción se envía a Ollama, llama.cpp, OpenAI, Claude, Gemini, Azure OpenAI, Mistral, OpenRouter o a una prueba simulada. Llaman a una ruta de tarea estable como:

```text
docs.summarize
asset.explain
naming.review
rag.embed
agent.patch
```

La ruta determina el proveedor, modelo, respaldo (fallback), política, regla de costos y backend de secretos.

## Abrir el editor

Abrir:

```text
Tiny Tools -> LLM Store
```

La pestaña está diseñada para el uso diario. No solo muestra la configuración básica; guía en la instalación, rutas, estado, ayuda, agentes, costos y gobernanza.

## Primera configuración

### Tarjeta Quick-Start (vía más rápida)

1. Abra `Tiny Tools -> LLM Store`.
2. Vaya a `Setup`. La sección **Quick Start — get running in one click** está en la parte superior.
3. Elija una opción:
   - **Just try it (Mock)** — completamente fuera de línea; sin clave API; ideal para CI y primer contacto.
   - **Local (Ollama)** — crea `quickstart_ollama` en `localhost:11434`; inicie Ollama antes de probar.
   - **Create OpenAI** o **Create Anthropic** — pegue una clave API en el campo de contraseña y haga clic en el botón del proveedor. La clave se almacena solo en el backend de secretos.
4. Lea la línea de estado debajo de los botones y el cartel de disponibilidad situado sobre las pestañas.
5. Si la disponibilidad está en verde, vuelva a desplegar la sección Quick-Start solo si necesita otra pila inicial (las entradas `quickstart_*` existentes no se duplican; su propia ruta `default` nunca se sobrescribe).

Las pilas iniciales utilizan ID estables (`quickstart_mock`, `quickstart_ollama`, `quickstart_openai`, `quickstart_anthropic`) y siempre conectan una ruta de tarea `default` a menos que ya haya definido una.

### Configuración manual (control total)

1. Abra `Tiny Tools -> LLM Store`.
2. Vaya a `Setup` (debajo de la tarjeta Quick-Start).
3. Cree un proveedor, por ejemplo `ollama`, `llamacpp`, `openai` o `anthropic`.
4. Confirme que la URL base predeterminada sea adecuada.
5. Cree un modelo para el proveedor.
6. Vaya a `Routes`.
7. Cree una ruta, por ejemplo `docs.summarize`.
8. Elija el modelo preferido.
9. Haga clic en `Test Route`.
10. Compruebe `Status` para revisar advertencias o bloqueos.

## Configuración del proveedor

Un proveedor describe el servicio técnico, no el modelo en sí.

| Campo | Signification |
| --- | --- |
| `Id` | ID estable local del proyecto, ej. `local-ollama`. |
| `DisplayName` | Nombre legible en la interfaz e informes. |
| `Type` | Tipo de proveedor como `ollama`, `llamacpp` u `openai`. |
| `BaseUrl` | Punto de conexión HTTP. Los proveedores conocidos reciben valores predeterminados útiles. |
| `Enabled` | Deshabilita el proveedor sin eliminar su configuración. |
| `RetryCount` | Intentos de reintento para errores temporales. |
| `TimeoutSeconds` | Límite de tiempo específico del proveedor. |
| `CircuitBreaker...` | Protección contra fallos repetidos o servidores bloqueados. |

Los proveedores locales no suelen requerir clave. Los proveedores en la nube suelen necesitar una clave en el almacén de secretos.

## Proveedores conocidos

| Tipo de proveedor | URL base predeterminada | Uso típico |
| --- | --- | --- |
| `ollama` | `http://localhost:11434` | Modelos locales a través de Ollama. |
| `llamacpp` | `http://localhost:8080` | Inferencia local con servidor llama.cpp. |
| `lmstudio` | `http://localhost:1234/v1` | Modelos locales de LM Studio. |
| `vllm` | `http://localhost:8000/v1` | Inferencia de alto rendimiento local o en servidor. |
| `tgi` | `http://localhost:8080` | Inferencia de generación de texto de Hugging Face. |
| `openai` | `https://api.openai.com/v1` | API de OpenAI. |
| `anthropic` | `https://api.anthropic.com` | API de Claude. |
| `gemini` | `https://generativelanguage.googleapis.com/v1beta` | API de Google Gemini. |
| `azure-openai` | específico del proyecto | Punto de conexión de Azure y lógica de despliegue. |
| `mistral` | `https://api.mistral.ai/v1` | API de Mistral. |
| `openrouter` | `https://openrouter.ai/api/v1` | Enrutador para múltiples modelos en la nube. |
| `mock` | vacío | Pruebas, desarrollo de interfaz, CI y trabajo fuera de línea. |

## Modelos

Un modelo pertenece a un solo proveedor.

| Campo | Significado |
| --- | --- |
| `Id` | ID de modelo estable local del proyecto. |
| `Name` | Nombre de red del proveedor, ej. `llama3.1:8b` o `gpt-4o-mini`. |
| `ProviderId` | Proveedor que ofrece el modelo. |
| `Role` | Rol opcional como `fast`, `reasoning`, `embedding` o `local`. |
| `Structured` | Marca los modelos que se espera que manejen bien salidas JSON/esquemas. |
| `TimeoutSeconds` | Límite de tiempo específico del modelo. |
| `Enabled` | Deshabilita el modelo sin eliminar rutas. |

## Rutas

Las rutas son el concepto más importante de la tienda. Una función solicita una tarea, no un modelo.

Ejemplo:

```text
TaskKind: docs.summarize
PreferredModelId: local-fast
FallbackModelIds:
  - cloud-reasoning
  - mock-docs
Policy: local-only for shipping
```

Ventajas:

- las funciones permanecen estables cuando los modelos cambian
- las políticas se pueden aplicar por tarea
- las cadenas de respaldo pueden combinar modelos locales, en la nube y simulados
- el costo se puede analizar por tarea
- la CI puede validar la política de rutas sin conocer cada herramienta

## Probar una ruta

Utilice `Test Route` en la pestaña `Routes`. La prueba comprueba:

- ¿existe la ruta?
- ¿está habilitada la ruta?
- ¿existe el modelo?
- ¿existe el proveedor?
- ¿está habilitado el proveedor?
- ¿existe la clave requerida?
- ¿responde el proveedor a una solicitud pequeña?

Los errores aparecen en el área de estado y en el panel de salud del proveedor.

## Políticas (Policies)

Las políticas deciden si se puede utilizar una ruta.

Reglas típicas:

- prohibir la nube para datos confidenciales
- permitir solo modelos locales para la versión de distribución
- establecer un presupuesto máximo de contexto
- establecer un costo máximo por solicitud
- permitir o denegar tipos de proveedores específicos

Las políticas deben configurarse en LLM Store. Otro plugin puede aportar contexto o llamar a una ruta, pero la decisión de gobernanza centralizada permanece en la tienda.

## Agentes

La pestaña `Agents` muestra adaptadores opcionales como Codex, Claude, Cursor o herramientas personalizadas del estudio.

| Estado | Significado |
| --- | --- |
| `NotInstalled` | No se encontró la herramienta. |
| `Installed` | La herramienta existe, la autenticación no está clara o falta. |
| `AuthRequired` | La autenticación debe completarse. |
| `Available` | La herramienta está lista para usarse. |
| `Disabled` | El adaptador está deshabilitado. |
| `Error` | El adaptador informa de un error. |

El botón `Authenticate...` abre un diálogo con el comando, instrucciones, enlace de ayuda y una acción de copia para uso manual en terminal. LLM Store no almacena credenciales de herramientas externas.

## Análisis de costos

La pestaña `Costs` recopila y analiza el libro de costos (cost ledger).

Muestra:

- eventos totales
- eventos exitosos
- aciertos de caché
- tokens de solicitud (prompt)
- tokens de respuesta (completion)
- costo estimado
- desglose por proveedor, modelo y ruta
- exportación a CSV

Los costos son tan precisos como los datos de uso del proveedor y las reglas de costos configuradas. Los modelos locales pueden ser gratuitos o tener asignado un costo de hardware interno.

## Almacén de secretos (Secret Store)

Las claves API no deben incluirse en `Config/LLMStore.json`.

Backends admitidos:

- archivo local cifrado
- Windows Credential Manager
- macOS Keychain
- 1Password CLI
- Azure Key Vault mediante Azure CLI

Las variables de entorno tienen prioridad:

```text
LLMSTORE_<PROVIDER_ID>_KEY
```

Ejemplo:

```text
LLMSTORE_OPENAI_MAIN_KEY
```

## Pestaña Status

La pestaña `Status` responde a: "¿Se puede utilizar mi tienda en este momento?"

Muestra:

- disponibilidad global
- bloqueos
- advertencias
- inventario de proveedores
- claves faltantes
- proveedores o modelos deshabilitados
- problemas en las rutas

Utilice esta pestaña antes de compartir la configuración con un equipo, ejecutar CI o empaquetar una versión.

## Exportación, validación e importación de JSON de configuración

La pestaña `Governance` incluye acciones de JSON de configuración para compartir o mover configuraciones completas de LLM Store.

Acciones disponibles:

| Acción | Propósito |
| --- | --- |
| `Export Setup JSON` | Elija cualquier carpeta y nombre de archivo y guarde la configuración actual como JSON. Los secretos no se incluyen. |
| `Validate JSON` | Elija un archivo JSON y valide el esquema, los ID de proveedor, las referencias de modelos, las rutas y las advertencias sin aplicarlo. |
| `Import JSON` | Elija un archivo JSON, valídelo y aplíquelo solo cuando la validación sea correcta. |

El importador acepta tanto el formato de configuración envuelto de LLM Store como un objeto JSON `FLLMStoreConfig` sin envolver. Esto lo hace adecuado para preajustes, copias de seguridad, archivos de entrega entre equipos y capturas de configuración revisadas manualmente.

## Pestaña Help

La pestaña `Help` explica directamente en el editor:

- qué es un proveedor
- qué es un modelo
- por qué se usan rutas en lugar de nombres de modelos directos
- cómo funcionan juntos los proveedores locales y en la nube
- cómo se aplican las políticas y las reglas de compilación
- qué mide el seguimiento de costos
- cómo se conectan los agentes

La sección de ayuda está incluida en el plugin para que los compradores no tengan que saltar entre un sitio web, README e interfaz del editor para entender los conceptos básicos.

## Uso en Blueprint

Los puntos de integración principales para los consumidores están disponibles en Blueprints.

| Clase | Propósito |
| --- | --- |
| `ULLMBlueprintProviderAddOn` | Conectar un proveedor desde Blueprint. |
| `ULLMBlueprintEmbeddingProviderAddOn` | Conectar un proveedor de embeddings desde Blueprint. |
| `ULLMBlueprintContractAddOn` | Validar contratos de modelos. |
| `ULLMBlueprintPolicyAddOn` | Permitir o rechazar rutas en tiempo de ejecución. |
| `ULLMBlueprintTestAddOn` | Agregar pruebas de configuración o de estado. |
| `ULLMBlueprintContextProviderAddOn` | Proporcionar contexto de proyecto como paquetes de contexto. |
| `ULLMBlueprintAgentAddOn` | Conectar CLI externas o asistentes del editor. |

## Uso en C++

Los usuarios de C++ obtienen la tienda desde el subsistema del motor:

```cpp
ULLMStoreSubsystem* Store = GEngine->GetEngineSubsystem<ULLMStoreSubsystem>();
```

Posteriormente se pueden resolver rutas, ejecutar solicitudes, crear paquetes de contexto, llamar a agentes y leer informes de costos.

Consulte [INTEGRATION.md](INTEGRATION.md) y [CodeDocumentation.md](CodeDocumentation.md).

## Flujos de trabajo recomendados

### Desarrollo local

1. Cree un proveedor `ollama` o `llamacpp`.
2. Agregue un modelo local.
3. Apunte las rutas al modelo local.
4. Deshabilite la nube mediante políticas.
5. Mantenga una ruta `mock` para pruebas.

### Desarrollo híbrido

1. Utilice modelos locales para tareas rápidas.
2. Agregue respaldo en la nube para tareas más complejas.
3. Establezca límites de costos.
4. Revise el seguimiento de costos periódicamente.
5. Mantenga las reglas de compilación de distribución exclusivamente locales/simuladas.

### Configuración de equipo

1. Guarde en el repositorio `Config/LLMStore.json`.
2. No guarde las claves.
3. Documente el backend de secretos.
4. Exporte un preajuste.
5. Revise la pestaña `Status`.
6. Habilite comprobaciones de políticas de CI.

## Límites

LLM Store no es una herramienta terminada de explicación de assets, revisión de Blueprints o producto RAG. Proporciona rutas, proveedores, políticas, seguimiento de costos, secretos e interfaces. Las herramientas con funciones concretas se pueden conectar a él sin que LLM Store dependa de ellas.

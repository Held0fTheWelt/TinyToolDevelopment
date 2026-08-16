<!-- doc-provenance: AKDB:plugins/LLMStore/architecture.md; docs/architecture/plugins/LLMStore/product-facts.yml; reconciled 2026-06-20 -->
# Solución de problemas

Esta guía enumera problemas comunes con la configuración, el tiempo de ejecución, la interfaz de usuario, las políticas y las compilaciones de LLM Store.

## La entrada de menú de LLM Store no aparece

Compruebe:

- el plugin está habilitado
- el editor se reanudó/reinició después de habilitar el plugin
- el módulo `LLMStoreEditor` fue compilado
- está ejecutando Unreal Editor y no una compilación empaquetada (cooked) en tiempo de ejecución

Ubicación esperada:

```text
Tiny Tools -> LLM Store
```

## El proveedor no está accesible

Compruebe:

- el proveedor está habilitado
- la URL base es correcta
- el servidor local está ejecutándose
- el cortafuegos o proxy no bloquean la solicitud
- el límite de tiempo (timeout) es lo suficientemente largo
- el tipo de proveedor coincide con el servidor

Valores predeterminados locales comunes:

| Proveedor | Predeterminado |
| --- | --- |
| `ollama` | `http://127.0.0.1:11434` |
| `llamacpp` | `http://127.0.0.1:8080` |
| `lmstudio` | `http://127.0.0.1:1234/v1` |
| `vllm` | `http://127.0.0.1:8000/v1` |
| `tgi` | `http://127.0.0.1:8080/v1` |

Utilice primero `Test Provider`, luego `Test Model` y finalmente `Test Route`.

## La ruta no se resuelve

Compruebe:

- el `TaskKind` de la ruta está escrito exactamente como se requiere
- la ruta está habilitada
- el modelo preferido existe
- el modelo está habilitado
- el modelo hace referencia a un proveedor existente
- el proveedor está habilitado
- la clave en la nube existe si se requiere
- la política de la ruta permite el tipo de proveedor
- el modo de compilación/tiempo de ejecución no rechaza la ruta

Si `bUseMock` está habilitado, verifique que `MockModelId` exista.

## Clave API faltante

Las claves no se guardan en `Config/LLMStore.json`.

Utilice una de las siguientes soluciones:

- campo de clave del proveedor en el editor
- sustitución mediante variable de entorno
- backend de secretos configurado

Formato de variable de entorno:

```text
LLMSTORE_<PROVIDER_ID>_KEY
```

Ejemplo:

```text
ProviderId: openai-main
Variable: LLMSTORE_OPENAI_MAIN_KEY
```

## La variable de entorno se ignora

Compruebe:

- el nombre de la variable usa el ID del proveedor normalizado
- el proceso del editor se reinició después de establecerla
- la variable es visible para el proceso que inicia Unreal
- no hay espacios ocultos en el valor

En Windows, los cambios en variables de entorno desde la configuración del sistema suelen requerir reiniciar el iniciador o la terminal.

## Windows Credential Manager no funciona

Compruebe:

- ejecución en Windows
- `Advapi32` está vinculado desde la compilación del plugin
- el nombre del destino de la credencial coincide con el nombre del secreto generado para el proveedor
- la cuenta de usuario tiene permisos
- el ID del proveedor no ha cambiado

En caso de duda, establezca una variable de entorno temporal para confirmar el resto de la configuración del proveedor.

## macOS Keychain no funciona

Compruebe:

- el comando `security` está disponible
- el llavero está desbloqueado
- el proceso tiene permisos para leer el elemento
- el nombre del secreto generado coincide con el valor esperado

## El backend de 1Password no funciona

Compruebe:

- la CLI `op` está instalada
- `op whoami` tiene éxito en el mismo contexto de terminal
- `Vault` está configurado o `SecretBackend.Meta` contiene una referencia `op://...` completa
- la sustitución específica del proveedor apunta al elemento y campo correctos

## El backend de Azure Key Vault no funciona

Compruebe:

- la CLI `az` está instalada
- `az account show` tiene éxito
- `Vault` es el nombre correcto de Key Vault
- la identidad actual tiene permisos get/set/delete en los secretos
- la sustitución específica del proveedor coincide con el nombre del secreto

## El proveedor en la nube falla pero el local funciona

Compruebe:

- la clave API está presente
- la URL base coincide con la documentación del proveedor
- el nombre del modelo del proveedor es correcto
- la cuenta tiene acceso al modelo
- la solicitud no está bloqueada por políticas de la organización
- la política de costos de la ruta no rechaza la solicitud

Inspeccione el estado de salud del proveedor y el último evento de auditoría.

## llama.cpp no responde

Compruebe:

- `llama-server` está ejecutándose
- el host y puerto coinciden con `BaseUrl`
- el servidor expone un punto de conexión compatible con OpenAI
- el modelo está cargado
- el tiempo de espera de la solicitud es lo suficientemente largo

Inicio típico:

```text
llama-server -m C:\Models\model.gguf --host 127.0.0.1 --port 8080
```

Proveedor:

```text
Type: llamacpp
BaseUrl: http://127.0.0.1:8080
```

## Ollama no responde

Compruebe:

```text
ollama list
ollama serve
```

Asegúrese de que el modelo en `FLLMModelConfig.Name` exista en Ollama.

## El JSON estructurado no es válido

Compruebe:

- la ruta usa un modelo adecuado para salidas estructuradas
- `bStructured` está configurado en el modelo si el flujo de trabajo lo requiere
- `FLLMStructuredOutputSpec.bRequireJson` es verdadero solo cuando es necesario
- el esquema es un JSON válido
- la solicitud no requiere texto plano alrededor del JSON

Algunos modelos locales requieren solicitudes más estrictas para producir JSON válido.

## Faltan llamadas a herramientas (Tool Calls)

Compruebe:

- el proveedor admite llamadas a herramientas
- `FLLMToolSpec.ParametersJsonSchema` es válido
- el modelo admite herramientas
- el adaptador del proveedor asigna la especificación de herramientas al formato de red del proveedor

## La transmisión (Streaming) emite un solo bloque

Algunos proveedores no admiten transmisión nativa o el adaptador actual solo puede analizar respuestas completas. Esto está permitido. La API de transmisión emite un bloque final único que permite a los usuarios utilizar un solo camino de código.

## Los costos resultan ser cero

Compruebe:

- existen reglas de costos
- el tipo de proveedor coincide con la regla
- el ID del modelo coincide con la regla o el ID del modelo en la regla está vacío
- el proveedor informa sobre el uso o la estimación de tokens está habilitada
- la solicitud no fue atendida completamente por un modelo local de costo cero

## El informe de costos parece demasiado alto

Compruebe:

- las unidades de costo son por 1000 tokens
- los valores de entrada y salida no se invirtieron
- la moneda es coherente
- la regla específica del modelo no está duplicada por una regla más general
- los datos de uso del proveedor no están expresados en otra unidad

## El agente no está instalado

Compruebe:

- la CLI o el IDE está instalado
- el comando de la herramienta está presente en el `PATH`
- Unreal se inició desde un entorno que puede ver el comando
- la comprobación de estado del adaptador conoce el nombre de comando correcto

Utilice el diálogo `Authenticate...` para ver las instrucciones de configuración.

## La autenticación del agente no funciona

Pruebe lo siguiente:

1. Haga clic en `Copy Command`.
2. Ejecute el comando en una terminal normal.
3. Complete el inicio de sesión.
4. Reinicie Unreal o actualice el estado del agente.

LLM Store no almacena credenciales. Se limita a mostrar y copiar el comando de inicio de sesión externo.

## El agente rechaza la escritura de archivos

Compruebe `FLLMAgentRequest`:

```text
bAllowFileWrites
bAllowShellExecution
bRequireDiffPreview
```

Los adaptadores deben rechazar escrituras o comandos de shell cuando la solicitud no los permite.

## La política de empaquetado (Shipping) falla

Compruebe:

- `BuildRules` para `Shipping`
- las políticas de las rutas
- el uso de proveedores en la nube
- la disponibilidad de respaldos locales o simulados
- las listas de inclusión de proveedores

Ejecute el commandlet localmente:

```text
<UnrealEditorCommand> Project.uproject -run=LLMStoreCIPolicy -Config=Shipping -Unattended -NoSplash -NoSound
```

## El estado de la configuración no está claro

Abra la pestaña `Status`. Resume proveedores, modelos, rutas, bloqueos, advertencias, claves faltantes e inventario.

Si el estado parece desactualizado:

- haga clic en recargar si está disponible
- cierre y vuelva a abrir la pestaña
- reinicie el editor
- compruebe si `Config/LLMStore.json` se modificó manualmente

## La compilación falla porque Live Coding está activo

En Unreal, Live Coding puede bloquear una compilación externa completa mientras el editor está en ejecución. Cierre el editor o deshabilite Live Coding antes de realizar una compilación completa desde la línea de comandos.

Esto no afecta al uso normal de la interfaz, pero puede bloquear compilaciones de tipo CI o la validación UHT.

## Referencias útiles

- Primera configuración: [QUICKSTART.md](QUICKSTART.md)
- Detalles del proveedor: [ProviderReference.md](ProviderReference.md)
- Políticas de rutas: [RoutePolicyReference.md](RoutePolicyReference.md)
- Secretos: [SECRET_BACKENDS.md](SECRET_BACKENDS.md)
- Costos: [COST_TRACKING.md](COST_TRACKING.md)
- Integración: [INTEGRATION.md](INTEGRATION.md)
- CI: [CommandletAndCI.md](CommandletAndCI.md)

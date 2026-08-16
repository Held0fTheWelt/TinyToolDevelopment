<!-- doc-provenance: AKDB:plugins/LLMStore/architecture.md; docs/architecture/plugins/LLMStore/product-facts.yml; reconciled 2026-06-20 -->
# Inicio rápido

Esta guía explica cómo configurar la primera ruta funcional en LLM Store.

## 1. Abrir la pestaña del editor

Abrir:

```text
Tiny Tools -> LLM Store
```

La zona superior resume los proveedores, modelos, rutas, rutas de embeddings cargados, el estado de disponibilidad e información de costos estimados.

## 2. Usar la tarjeta Quick-Start (recomendado para el primer uso)

En la pestaña **Setup**, la tarjeta **Quick Start** aparece sobre las secciones de proveedores y modelos. Elija una opción:

| Botón | Qué crea | Clave API |
| --- | --- | --- |
| **Just try it (Mock)** | Proveedor simulado fuera de línea, modelo y ruta `default` | Ninguna |
| **Local (Ollama)** | Ollama en `http://localhost:11434`, modelo predeterminado `llama3`, ruta `default` | Ninguna (Ollama debe estar ejecutándose) |
| **Create OpenAI** | Proveedor OpenAI, modelo `gpt-4o-mini`, ruta `default` | Pegue la clave en el campo (se guarda solo en el almacén de secretos) |
| **Create Anthropic** | Proveedor Anthropic, modelo `claude-3-5-haiku-latest`, ruta `default` | Pegue la clave en el campo (se guarda solo en el almacén de secretos) |

Después de hacer clic en un botón, LLM Store:

1. Aplica el conjunto inicial de forma idempotente (ID `quickstart_*` estables; nunca sobrescribe sus proveedores existentes ni una ruta `default` configurada por usted).
2. Almacena una clave API en la nube a través de `SetProviderKey` si proporcionó una (nunca se escribe en `Config/LLMStore.json`).
3. Ejecuta **Test Connection** y actualiza el cartel de disponibilidad.

Cuando la disponibilidad ya está en verde, la tarjeta se pliega con el título corto “ready — expand to run Quick-Start again”.

Para URL personalizadas, modelos adicionales o rutas para tareas específicas, continúe con los pasos manuales a continuación.

## 3. Crear un proveedor local (manual)

Un proveedor local es la prueba inicial más sencilla porque no requiere clave API.

### Opción A: Ollama

1. Inicie Ollama localmente.
2. Descargue un modelo:

```text
ollama pull llama3.1
```

3. En `Setup`, cree un proveedor:

```text
Id: ollama-local
DisplayName: Ollama Local
Type: ollama
BaseUrl: http://127.0.0.1:11434
Enabled: true
```

4. Cree un modelo:

```text
Id: local-chat
Name: llama3.1
DisplayName: Local Chat
ProviderId: ollama-local
Role: fast
Enabled: true
```

### Opción B: llama.cpp

Inicie un servidor local de llama.cpp:

```text
llama-server -m C:\Models\model.gguf --host 127.0.0.1 --port 8080
```

A continuación, cree:

```text
Provider:
  Id: llamacpp-local
  Type: llamacpp
  BaseUrl: http://127.0.0.1:8080

Model:
  Id: local-llamacpp
  Name: local-model
  ProviderId: llamacpp-local
```

## 4. Crear un proveedor en la nube (manual)

Los proveedores en la nube suelen requerir una clave API. La clave se almacena en el backend de secretos, no en `Config/LLMStore.json`.

Ejemplo:

```text
Provider:
  Id: openai-main
  Type: openai
  BaseUrl: https://api.openai.com/v1

Model:
  Id: openai-fast
  Name: gpt-4o-mini
  ProviderId: openai-main
```

Luego establezca la clave en la sección del proveedor o mediante una variable de entorno:

```text
LLMSTORE_OPENAI_MAIN_KEY
```

## 5. Crear una ruta

Cree una ruta en la pestaña `Routes`:

```text
TaskKind: docs.summarize
PreferredModelId: local-chat
FallbackModelIds:
  - openai-fast
MockModelId: mock-docs
bUseMock: false
```

Si comenzó con llama.cpp, utilice `local-llamacpp` como modelo preferido.

## 6. Agregar una política (Policy)

Para una ruta segura que priorice lo local:

```text
bAllowCloud: false
bLocalOnly: true
MaxContextTokens: 0
MaxEstimatedCost: 0
AllowedProviderTypes:
  - ollama
  - llamacpp
  - mock
```

Para una ruta de desarrollo híbrida, permita la nube y agregue un límite de costo:

```text
bAllowCloud: true
bLocalOnly: false
MaxEstimatedCost: 0.05
```

## 7. Probar proveedor, modelo y ruta

Utilice los botones de prueba del editor.

Si la ruta no se resuelve, compruebe:

- ¿está habilitado el proveedor?
- ¿está habilitado el modelo?
- ¿el modelo hace referencia al proveedor correcto?
- ¿la ruta utiliza el ID de modelo correcto?
- ¿está configurada la clave API para el proveedor en la nube?
- ¿está ejecutándose el servidor local?
- ¿la política permite el tipo de proveedor seleccionado?

## 8. Agregar reglas de costos

La pestaña `Costs` resulta útil una vez definidas las reglas de precios.

Ejemplo:

```text
ProviderType: openai
ModelId: openai-fast
InputCostPer1KTokens: 0.00015
OutputCostPer1KTokens: 0.00060
Currency: USD
```

Los proveedores locales pueden mantenerse en `0` o utilizar un modelo de costo interno.

## 9. Ejecutar una solicitud

Tras realizar una solicitud, la pestaña `Costs` muestra:

- recuento de eventos
- recuento de éxitos
- aciertos de caché
- tokens de solicitud
- tokens de respuesta
- costo estimado
- desglose por proveedor/modelo/tarea
- eventos recientes

Utilice `Export CSV` para guardar informes en:

```text
Saved/LLMStore/CostReports
```

## 10. Comprobar el estado

Abra la pestaña `Status`. La sección más importante es `Attention`, ya que muestra claves faltantes, rutas rotas, proveedores deshabilitados y problemas de políticas.

## 11. Configuración opcional de agentes

Para conectar Codex, Claude, Cursor o un agente personalizado:

1. Abra la pestaña `Agents`.
2. Seleccione un agente.
3. Haga clic en `Authenticate...`.
4. Utilice `Copy Command` y ejecute el comando manualmente en su terminal.
5. Actualice el estado.

Ejemplos:

```text
codex login
claude auth login
```

LLM Store no almacena credenciales de agentes.

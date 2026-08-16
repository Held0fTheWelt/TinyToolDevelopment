<!-- doc-provenance: AKDB:plugins/LLMStore/architecture.md; docs/architecture/plugins/LLMStore/product-facts.yml; reconciled 2026-06-20 -->
# Referencia de configuración

Esta referencia describe los principales datos de configuración utilizados por LLM Store.

Ruta de configuración del proyecto:

```text
Config/LLMStore.json
```

Los secretos no se guardan en este archivo.

## Archivo JSON de configuración

La interfaz de gobernanza puede exportar, validar e importar archivos JSON de configuración desde cualquier carpeta seleccionada.

El formato envuelto exportado contiene:

| Campo | Significado |
| --- | --- |
| `Format` | `LLMStoreSetup`. |
| `FormatVersion` | Versión del formato JSON de configuración. |
| `SetupName` | Nombre de la configuración legible por el usuario. |
| `ExportedUtc` | Marca de tiempo UTC de la exportación. |
| `Config` | Objeto `FLLMStoreConfig` anidado. |

El importador también acepta un objeto JSON `FLLMStoreConfig` sin envolver para mayor compatibilidad.

## FLLMStoreConfig

| Campo | Tipo | Significado |
| --- | --- | --- |
| `Providers` | `TArray<FLLMProviderConfig>` | Proveedores conocidos. |
| `Models` | `TArray<FLLMModelConfig>` | Modelos ofrecidos por los proveedores. |
| `Routes` | `TArray<FLLMTaskRoute>` | Rutas para tareas de chat/herramientas/reordenamiento. |
| `EmbeddingRoutes` | `TArray<FLLMStoreEmbeddingRoute>` | Rutas específicas para embeddings. |
| `RoutePolicies` | `TArray<FLLMRoutePolicy>` | Políticas globales o específicas de tareas. |
| `PromptTemplates` | `TArray<FLLMPromptTemplate>` | Plantillas de solicitudes reutilizables. |
| `CostRules` | `TArray<FLLMCostRule>` | Reglas de precios para el seguimiento de costos. |
| `BuildRules` | `TArray<FLLMBuildConfigRule>` | Gobernanza para la configuración de compilación. |
| `SecretBackend` | `FLLMSecretBackendConfig` | Backend de secretos activo. |
| `Modes` | `FLLMRuntimeModes` | Etiquetas de perfil en tiempo de ejecución. |

## FLLMProviderConfig

| Campo | Significado |
| --- | --- |
| `Id` | Clave de proveedor estable local del proyecto. |
| `DisplayName` | Nombre legible en la interfaz e informes. |
| `Type` | Tipo de proveedor como `openai`, `ollama` o `llamacpp`. |
| `BaseUrl` | Punto de conexión del servidor o la API. |
| `bEnabled` | Deshabilita el proveedor sin eliminarlo. |
| `Meta` | Metadatos específicos del proveedor, ej. nombres de despliegue en Azure. |
| `RetryCount` | Reintentos para errores temporales. |
| `TimeoutSeconds` | Límite de tiempo del proveedor; `0` usa los valores predeterminados. |
| `CircuitBreakerFailureThreshold` | Número de errores antes de abrir el disyuntor. |
| `CircuitBreakerCooldownSeconds` | Tiempo de enfriamiento antes de reintentar tras la apertura. |

## FLLMModelConfig

| Campo | Significado |
| --- | --- |
| `Id` | Clave de modelo estable local del proyecto. |
| `Name` | Nombre del modelo en el proveedor. |
| `DisplayName` | Nombre legible en la interfaz de usuario. |
| `ProviderId` | Referencia a `FLLMProviderConfig.Id`. |
| `Role` | Rol opcional como `fast`, `reasoning`, `local` o `embedding`. |
| `bStructured` | El modelo está previsto para manejar bien salidas JSON estructuradas. |
| `TimeoutSeconds` | Límite de tiempo específico del modelo. |
| `bEnabled` | Deshabilita el modelo sin eliminarlo. |

## FLLMTaskRoute

| Campo | Significado |
| --- | --- |
| `TaskKind` | Nombre de tarea estable, ej. `docs.summarize`. |
| `PreferredModelId` | Primer modelo que intenta esta ruta. |
| `FallbackModelId` | Respaldo único heredado. |
| `FallbackModelIds` | Cadena ordenada de respaldos. |
| `MockModelId` | Modelo utilizado para el modo simulado. |
| `bUseMock` | Forza el uso de la simulación. |
| `WorkflowScope` | Ámbito opcional como `Editor`, `CI` o `Runtime`. |
| `PromptTemplateId` | Plantilla predeterminada para esta ruta. |
| `Policy` | Política específica de la ruta. |
| `bEnabled` | Deshabilita la ruta. |

## FLLMRoutePolicy

| Campo | Significado |
| --- | --- |
| `TaskKind` | Vacío puede ser usado por herramientas como global; de lo contrario específico de la tarea. |
| `bAllowCloud` | Se pueden usar tipos de proveedores en la nube. |
| `bLocalOnly` | Solo se permiten proveedores locales o simulados. |
| `MaxContextTokens` | Presupuesto máximo de contexto; `0` deshabilita el límite. |
| `MaxEstimatedCost` | Costo estimado máximo por solicitud; `0` deshabilita el límite. |
| `AllowedProviderTypes` | Lista de inclusión de tipos de proveedores. |
| `DeniedProviderTypes` | Lista de exclusión de tipos de proveedores. |

## FLLMStoreEmbeddingRoute

| Campo | Significado |
| --- | --- |
| `RouteId` | ID de ruta de embedding estable. |
| `TaskKind` | Tarea, ej. `docs.embed`. |
| `ProviderId` | Proveedor de embeddings. |
| `ModelId` | Modelo de embeddings. |
| `Dimensions` | Dimensión vectorial esperada; `0` significa el valor predeterminado del proveedor. |
| `bEnabled` | La ruta está activa. |
| `bLocalOnly` | Preferir o requerir ejecución local. |
| `bAllowFallback` | Se pueden usar rutas de respaldo. |
| `FallbackRouteIds` | Rutas de respaldo para embeddings. |
| `AllowedRuntimeModes` | Lista de inclusión opcional de perfiles en tiempo de ejecución. |

## FLLMCostRule

| Campo | Significado |
| --- | --- |
| `ProviderType` | Tipo de proveedor cubierto por la regla. |
| `ModelId` | ID de modelo opcional; vacío se aplica de forma amplia. |
| `InputCostPer1KTokens` | Precio por 1000 tokens de solicitud. |
| `OutputCostPer1KTokens` | Precio por 1000 tokens de respuesta. |
| `Currency` | Etiqueta de moneda, por defecto `USD`. |

## FLLMSecretBackendConfig

| Campo | Significado |
| --- | --- |
| `Backend` | `EncryptedFile`, `WindowsCredentialManager`, `MacOSKeychain`, `OnePassword` o `AzureKeyVault`. |
| `Vault` | Almacén, llavero o nombre de espacio de nombres específico del backend. |
| `KeyPrefix` | Prefijo para nombres de secretos generados. |
| `Meta` | Anulaciones de proveedores específicas del backend. |

## FLLMBuildConfigRule

| Campo | Significado |
| --- | --- |
| `BuildConfiguration` | Configuración de Unreal como `Development`, `Test` o `Shipping`. |
| `bAllowCloud` | Los proveedores en la nube están permitidos en esta configuración. |
| `bRequireLocalOrMock` | Cada ruta debe tener una ruta local o simulada. |
| `AllowedProviderTypes` | Tipos de proveedores permitidos en esta configuración. |

## FLLMRuntimeModes

| Campo | Significado |
| --- | --- |
| `GenerationMode` | Etiqueta libre como `Local`, `Hybrid` o `Cloud`. |
| `RetrievalMode` | Etiqueta libre para el comportamiento de recuperación/RAG. |
| `ValidationMode` | Etiqueta libre para el comportamiento de validación/revisión. |
| `RuntimeProfile` | Perfil general como `LocalOnly`, `OpenAICloud` o `Hybrid`. |

## FLLMPromptTemplate

| Campo | Significado |
| --- | --- |
| `Id` | Clave de la plantilla. |
| `Description` | Descripción para la interfaz y los miembros del equipo. |
| `Template` | Texto de la solicitud con variables. |
| `Variables` | Nombres de variables esperados. |

## Recomendaciones para el equipo

- Guarde en el repositorio `Config/LLMStore.json`.
- No guarde las claves API.
- Utilice `SecretBackend` para hacer visibles las expectativas del equipo.
- Utilice `BuildRules` para detectar tempranamente errores de empaquetado.
- Agregue `CostRules` antes del uso real de la nube.
- Documente cada ruta de producción con responsable, propósito y clase de datos.

## Ajustes de desarrollador del editor

Las preferencias del editor residen en **Editor Settings -> Plugins -> LLM Store** y se guardan por separado de `Config/LLMStore.json`.

| Campo | Predeterminado | Significado |
| --- | --- | --- |
| `MaxJobHistoryCount` | `50` | Número máximo de registros de panel/trabajos conservados para el historial del editor y los puntos de conexión de trabajos UCM. |
| `DefaultPanelPage` | `Setup` | Página del panel mostrada al abrir LLM Store. |
| `bAutoOpenPanelOnStartup` | `false` | Abre automáticamente el panel al iniciar el módulo del editor. |
| `bRunValidationOnReload` | `false` | Ejecuta la comprobación de idoneidad de validación tras recargar la configuración. |

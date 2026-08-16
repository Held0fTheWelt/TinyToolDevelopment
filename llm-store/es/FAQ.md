<!-- doc-provenance: AKDB:plugins/LLMStore/architecture.md; docs/architecture/plugins/LLMStore/product-facts.yml; reconciled 2026-06-20 -->
# Preguntas frecuentes (FAQ)

## ¿Existe un asistente de configuración por primera vez?

Sí. La pestaña **Setup** incluye una tarjeta **Quick-Start**. Puede crear con un solo clic una pila completa simulada, de Ollama o en la nube de OpenAI/Anthropic (proveedor, modelo y ruta `default`), ejecutar una prueba de conexión y actualizar la disponibilidad. No sobrescribe proveedores creados previamente ni una ruta `default` configurada por usted.

## ¿Es LLM Store un chatbot?

No. LLM Store es una infraestructura para proveedores, modelos, rutas, políticas, secretos, seguimiento de costos y agentes. Un chatbot o asistente de assets puede utilizar LLM Store, pero es una herramienta independiente.

## ¿Por qué debería usar rutas en lugar de nombres de modelos?

Las rutas mantienen estable el código de las funciones. Si una herramienta llama a `docs.summarize`, el equipo puede cambiar posteriormente de Ollama a llama.cpp o a OpenAI sin modificar el código de la herramienta.

## ¿Puedo ejecutar todo localmente?

Sí. Utilice proveedores como `ollama`, `llamacpp`, `lmstudio`, `vllm`, `tgi` o `mock`, configure políticas exclusivas para uso local y bloquee la nube mediante reglas de compilación.

## ¿Está admitido llama.cpp?

Sí. El tipo de proveedor `llamacpp` está diseñado para servidores llama.cpp locales. La URL base típica es:

```text
http://localhost:8080
```

## ¿Las claves API se almacenan en el archivo del proyecto?

No. `Config/LLMStore.json` almacena proveedores, modelos, rutas y políticas, pero no las claves. Las claves permanecen en el almacén de secretos o en variables de entorno.

## ¿Qué backend de secretos debería usar?

Para la configuración de un solo desarrollador, `EncryptedFile` es sencillo. Para equipos, Windows Credential Manager, macOS Keychain, 1Password o Azure Key Vault suelen ser la mejor opción.

## ¿Puede Blueprint hacer todo lo que hace C++?

Los principales puntos de integración orientados al usuario disponen de versiones para Blueprint. Esto incluye proveedores, embeddings, políticas, pruebas, proveedores de contexto, agentes y funciones de fachada del subsistema.

## ¿Puedo conectar Codex, Claude o Cursor?

Sí, mediante complementos de agentes. La tienda puede unificar el estado, la guía de autenticación y la ejecución de tareas. La integración concreta de la herramienta sigue siendo un adaptador y debe cumplir las reglas de seguridad.

## ¿LLM Store ejecuta comandos de shell automáticamente?

Solo cuando un adaptador de agente implementa explícitamente la ejecución y las marcas de la solicitud lo permiten. `bAllowShellExecution`, `bAllowFileWrites` y `bRequireDiffPreview` comunican los requisitos de seguridad del solicitante.

## ¿Qué tan preciso es el seguimiento de costos?

La precisión depende de los datos de uso del proveedor y de las reglas `CostRules`. Si un proveedor no devuelve recuentos de tokens, la tienda los estima. La facturación del proveedor sigue siendo la fuente primaria de verdad para el cobro.

## ¿Puedo asignar costos a modelos locales?

Sí. Los modelos locales pueden tener costo `0` o utilizar valores contables internos como el costo aproximado de GPU por 1000 tokens.

## ¿Qué no pertenece directamente a LLM Store?

Herramientas con funciones concretas como explicación de assets, documentación de Blueprints, revisión de nombres o RAG del proyecto deben utilizar LLM Store, pero suelen residir en plugins o complementos independientes. LLM Store se mantiene autónomo.

## ¿Qué ocurre si un proveedor está fuera de línea?

La tienda actualiza el estado de salud del proveedor, puede intentar alternativas de respaldo y registra los errores en el registro de auditoría. Las configuraciones del disyuntor (circuit breaker) evitan reintentos costosos o bloqueados.

## ¿Puedo usar LLM Store en CI?

Sí. Utilice el commandlet `LLMStoreCIPolicy` y las pruebas de automatización. En `Documentation/CI` se incluye un ejemplo para GitHub Actions.

## ¿Debo probar los proveedores en la nube en vivo?

No siempre. Para la seguridad del lanzamiento, las pruebas simuladas, la validación de configuración y las pruebas manuales opcionales de funcionamiento son suficientes. Las pruebas en la nube solo deben ejecutarse con secretos configurados intencionadamente.

## ¿Qué archivos debería enviar al repositorio (commit)?

Envíe:

- `Config/LLMStore.json`
- preajustes opcionales
- documentación del equipo para rutas de producción

No envíe:

- claves API
- archivos de secretos locales
- archivos del libro de costos si contienen datos operativos confidenciales

## ¿Puedo exportar e importar configuraciones completas?

Sí. La pestaña Gobernanza puede exportar la configuración actual a cualquier archivo JSON, validar un archivo JSON sin aplicarlo e importar una configuración JSON solo después de que la validación sea correcta. Los archivos de configuración exportados no incluyen claves API.

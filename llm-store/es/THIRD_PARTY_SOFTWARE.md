<!-- doc-provenance: AKDB:plugins/LLMStore/architecture.md; docs/architecture/plugins/LLMStore/product-facts.yml; reconciled 2026-06-20 -->
# Software de terceros

LLM Store **no incluye código fuente de terceros, binarios en tiempo de ejecución, modelos de IA, Node.js, Python ni ejecutables independientes**. Es un plugin C++ para Unreal Engine que utiliza módulos propios de Unreal Engine y las API estándar de HTTP/JSON de Unreal.

## Integraciones opcionales de proveedores (proporcionadas por el comprador, no incluidas)

LLM Store es una bóveda y una capa de enrutamiento frente a proveedores de LLM. Usted elige qué proveedor, si lo hay, conectar. Ninguno de ellos es necesario para instalar el plugin, y el proveedor **Mock** integrado funciona completamente fuera de línea sin cuentas ni descargas.

| Proveedor | Qué es | Cómo integrarlo |
| --- | --- | --- |
| Mock | Proveedor fuera de línea integrado | No se requiere ninguna acción — funciona desde el primer momento. |
| Ollama | Servidor LLM local para instalar y ejecutar | Instale Ollama, ejecútelo (`http://localhost:11434` predeterminado), luego agregue un proveedor `ollama`. Consulte [QUICKSTART.md](QUICKSTART.md) §3. |
| llama.cpp | Servidor `llama-server` local para ejecutar | Inicie `llama-server`, luego agregue un proveedor `llamacpp`. Consulte [QUICKSTART.md](QUICKSTART.md) §3. |
| OpenAI | API en la nube (su propia cuenta) | Cree un proveedor `openai` y pegue su clave API (se guarda en el backend de secretos, nunca en la configuración). Consulte [QUICKSTART.md](QUICKSTART.md) §4 y [SECRET_BACKENDS.md](SECRET_BACKENDS.md). |
| Anthropic | API en la nube (su propia cuenta) | Cree un proveedor `anthropic` y pegue su clave API. Consulte [QUICKSTART.md](QUICKSTART.md) §4. |

Estos proveedores representan software/servicios externos propiedad de sus respectivos proveedores y se obtienen directamente de ellos. LLM Store no los redistribuye. Las claves API y las credenciales de agentes pertenecen al comprador; consulte [SECRET_BACKENDS.md](SECRET_BACKENDS.md) y [AGENT_AUTHENTICATION.md](AGENT_AUTHENTICATION.md).

**Declaración de software de terceros para Fab:** no se incluye software de terceros.

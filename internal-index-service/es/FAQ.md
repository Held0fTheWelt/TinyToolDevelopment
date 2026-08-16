<!-- doc-provenance: SAD architecture.md sections 1,2,7,8; facts product-facts.yml; reconciled 2026-07-16 -->
# Preguntas frecuentes (FAQ)

## ¿IIS modifica mi proyecto?

No. IIS es solo de lectura (retrieval-only). Escribe archivos de índices e informes generados, pero no aplica modificaciones en código fuente, Blueprints, assets o configuración como acción de agente.

## ¿IIS incluye un servidor MCP?

No, no en las versiones actuales. El transporte MCP lo proporciona Unified MCP Server. Las operaciones de agentes de IIS se exponen a través de las rutas Capability Mesh del proyecto, no mediante un servidor MCP o plugin puente propio de IIS.

## ¿Dónde se guardan los datos?

Por defecto:

```text
Saved/InternalIndexService
```

Puede invalidar la raíz en la configuración del proyecto.

## ¿IIS envía datos del proyecto a la nube?

Solo si una ruta de ejecutor de embeddings en LLM Store utiliza un proveedor en la nube. La búsqueda, catálogo, importación y archivos de informes son locales.

## ¿Por qué no hay resultados vectoriales?

La búsqueda vectorial requiere embeddings. Cree y ejecute tareas de embedding tras configurar una ruta de embedding a través de LLM Store.

## ¿Para qué se utiliza hnswlib?

hnswlib impulsa el backend vectorial opcional para los vecinos más cercanos aproximados `hnsw`. Se incluye como código fuente en `Source/ThirdParty/hnswlib`.

## ¿Por qué mi lista de herramientas MCP no incluye las herramientas de IIS?

Asegúrese de que los siguientes plugins estén habilitados:

- Internal Index Service
- Unified MCP Server
- Unreal Capability Mesh

Asegúrese de que el perfil Capability Mesh del proyecto incluya las rutas de agentes de IIS (`iis.agent.*.v1`), luego escriba/actualice los contratos de agentes de IIS y llame a `mesh_reload_setup` o actualice el cliente MCP.

## ¿Puedo llamar a IIS desde C++?

Sí. Utilice `FInternalIndexServiceModule::Get().GetService()` y la interfaz `IInternalIndexService`.

## ¿Puedo llamar a IIS desde Blueprint?

IIS expone principalmente la interfaz de usuario del editor y servicios C++. Las rutas para agentes y de integración se basan en C++/JSON.

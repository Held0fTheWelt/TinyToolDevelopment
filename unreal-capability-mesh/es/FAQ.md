<!-- doc-provenance: AKDB:plugins/UnrealCapabilityMesh/architecture.md; docs/architecture/plugins/UnrealCapabilityMesh/product-facts.yml; reconciled 2026-07-19 -->
# Preguntas frecuentes (FAQ)

## ¿UCM es un modelo o agente de IA?

No. UCM es un núcleo de interoperabilidad. Puede describir capacidades relacionadas con IA, pero no incluye modelos, prompts, proveedores ni motores de ejecución para agentes.

## ¿UCM modifica activos?

No por sí mismo. Solo carga manifiestos, planifica rutas, invoca puntos de entrada declarados y genera diagnósticos. La modificación de activos debe ejecutarla un punto de entrada del proveedor y estar permitida por las directivas.

## ¿Se puede omitir la aprobación?

Solo a través de los controles de autoaprobación automática etiquetados como **EXPERIMENTACIÓN** en la columna de aprobación del catálogo de rutas en la página Routes, los campos correspondientes en `project_profile.json` o la herramienta MCP `mesh_configure_experimental_self_approval`. Se trata de una omisión general de directivas: las reglas de denegación, comprobaciones de modificación de activos/proyecto, aprobación y requisitos de simulación se ignoran. Está diseñado únicamente para pruebas o flujos bajo su propio riesgo; mantenga **Approve all at own risk** y todos los conmutadores por ruta desactivados para uso normal.

## ¿Por qué usar manifiestos en lugar de dependencias C++ directas?

Los manifiestos permiten a los proyectos conectar herramientas sin crear cadenas de dependencias en tiempo de compilación entre plugins. Esto mantiene el núcleo neutro y más sencillo de empaquetar.

## ¿Dónde se guardan los informes?

Los informes se guardan en `Saved/UnrealCapabilityMesh`.

## ¿Dónde se almacenan los manifiestos del proyecto?

Los manifiestos del proyecto se almacenan en `Config/UnrealCapabilityMesh`.

## ¿UCM puede integrar plugins de terceros de la tienda (Marketplace)?

Sí, siempre que dichos plugins expongan funciones invocables, contratos de archivos o características modulares que puedan describirse mediante manifiestos o adaptadores.

## ¿UCM incluye código de terceros?

No se incluye código fuente de terceros ni dependencias en tiempo de ejecución en el paquete del plugin.

<!-- doc-provenance: AKDB:plugins/SmartContentDiet/architecture.md; docs/architecture/plugins/SmartContentDiet/product-facts.yml; reconciled 2026-07-16 -->
# Software de terceros

Smart Content Diet **no incluye código fuente de terceros, binarios de tiempo de ejecución, modelos de IA, Node.js, Python ni ejecutables independientes**. Es un complemento de editor C++ de Unreal Engine que utiliza solo módulos de Unreal Engine y API estándar de Unreal (registro de activos, análisis de activos, interfaz de usuario de editor, commandlet).

El bucle principal de escaneo → revisión → corrección segura se ejecuta completamente dentro del editor **sin servicio de IA ni herramienta externa**. Las rutas opcionales del ecosistema entre complementos (a través de **Unreal Capability Mesh (UCM)**) están declaradas en JSON y no agregan ningún software de terceros a este paquete.

No se requiere ningún software externo, cuenta o tiempo de ejecución para instalar o usar el complemento.

**Declaración de software de terceros de Fab:** sin software de terceros incluido.

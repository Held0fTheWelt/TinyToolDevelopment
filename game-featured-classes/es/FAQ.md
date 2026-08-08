# Preguntas frecuentes

## ¿GameFeaturedClasses incluye clases de juego?

No. La versión 1.0.1 es una carcasa de plugin de tiempo de ejecución ligera con descriptores, límites de módulo, metadatos de empaquetado, icono y registro de cambios. El comportamiento premium de GameFeature Workbench está especificado para el destino, pero aún no está implementado en este paquete.

## ¿Se requiere algún otro plugin de Tiny Tool?

No. La carcasa de módulo actual se carga por sí misma. Las futuras integraciones con LightweightDummyActorSystem, Unreal Capability Mesh o Project Intelligence Orchestrator son parte de la arquitectura de destino opcional, no un requisito de tiempo de ejecución para este paquete.

## ¿Qué versiones del motor son compatibles?

La matriz de lanzamiento empaquetado apunta a Unreal Engine 5.4 hasta 5.8 (descriptor `EngineVersion` 5.4.0 en esta rama).

## ¿Incluye software de terceros o servicios externos?

No. El paquete no incluye software de terceros ni requiere una cuenta, proveedor de IA o tiempo de ejecución externo. Consulta [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md).

## ¿Dónde obtengo soporte?

Utiliza `mailto:support@tiny-tool-development.com` (descriptor `SupportURL`) o el enlace de soporte en la página del producto de Fab.

## ¿Por qué no hay un panel de configuración?

La versión 1.0.1 no expone DeveloperSettings ni descriptores de clases destacadas. Consulta [SettingsReference.md](SettingsReference.md).

## ¿Puedo colocar las clases destacadas de mi proyecto dentro de la carpeta de este plugin?

No para su distribución como contenido de GFC en la versión 1.0.1. Mantén las clases de juego de tu proyecto en tus propios módulos hasta que un paquete posterior distribuya explícitamente los activos de clases destacadas.

## ¿Cómo verifico que la carcasa se cargó correctamente?

Habilita el plugin, reinicia el editor y confirma que el módulo de tiempo de ejecución `GameFeaturedClasses` está presente. Consulta el ejemplo detallado en [QUICKSTART.md](QUICKSTART.md).

## ¿Dónde está la documentación en línea?

https://docs.tiny-tool-development.com/game-featured-classes/

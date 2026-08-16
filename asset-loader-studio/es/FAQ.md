<!-- doc-provenance: product-facts.yml reconciled 2026-07-01; source AKDB:plugins/AssetLoaderStudio/architecture.md -->
# Preguntas frecuentes (FAQ)

## ¿Asset Loader Studio es independiente?

Sí. El espacio de trabajo del editor, el subsistema de tiempo de ejecución, la biblioteca de Blueprint, los ejemplos, los perfiles de gobernanza y la documentación para compradores funcionan sin UCM, UMCP, MCP u otros plugins de Tiny Tool.

## ¿Reemplaza al Asset Manager de Unreal?

No. Se basa en las rutas de activos de Unreal, ID de activos primarios, tablas, paquetes y la Asset Registry. Añade trabajos de carga estructurados, diagnósticos, instantáneas de tabla, gráficos de dependencias, vistas previas y gobernanza.

## ¿Puede modificar los activos del proyecto?

Sí, pero las modificaciones priorizan la vista previa. Las operaciones de creación, duplicación, cambio de nombre, reorientación (retargeting), reparación, guardado, reversión y eliminación deben superar las comprobaciones del perfil de permisos y deben revisarse antes de aplicarse.

## ¿Dónde se almacenan los registros de auditoría?

El directorio de auditoría predeterminado es `Saved/AssetLoaderStudio/Audit`. La ruta se puede ajustar a través de la configuración de gobernanza.

## ¿Son obligatorias las rutas de automatización?

No. Los archivos opcionales UCM/MCP exponen los mismos servicios para la automatización gobernada, pero el producto principal sigue siendo utilizable sin ellos.

## ¿Asset Loader Studio está disponible en Fab?

El estado actual del paquete es "In Publishment" (En proceso de publicación). Trátelo como preparado para la entrega a Fab, pero no disponible hasta que se publique la ficha en el propio portal de Fab.

<!-- doc-provenance: product-facts.yml reconciled 2026-07-01; source AKDB:plugins/AssetLoaderStudio/architecture.md -->
# Solución de problemas

## Activos faltantes

Utilice rutas de objeto completas con el sufijo de objeto, por ejemplo `/Game/Data/DA_Item.DA_Item`. Si la validación informa `ALS.Table.MissingReferencedAsset`, redirija el campo a un activo existente o vacíelo.

## Rutas incorrectas

`ALS.InvalidSoftObjectPath` y `ALS.Table.InvalidReferencePath` significan que la ruta no se puede analizar como una ruta de objeto de Unreal. Vuelva a copiar la referencia desde el Content Browser.

## Fallos en la aplicación

Las aplicaciones requieren una vista previa permitida y un token de aprobación. En el espacio de trabajo del editor, el botón Apply aprueba la última vista previa. En automatización, establezca `approval_token` con el ID de la vista previa o con `approved`.

## Denegaciones de permisos

Utilice `asset_loader_studio.state.read.v1` para inspeccionar los perfiles activos. Las denegaciones habituales se deben al modo de solo lectura, modo exclusivo de simulación (dry-run), límites de filas/activos afectados, rutas fuera de `allowed_roots` o falta de permiso destructivo.

## Fallos al guardar

La aplicación genérica marca los paquetes como "sucios" (dirty) y proporciona instrucciones de recuperación. Guarde mediante la ventana para guardar del editor de Unreal o el flujo de trabajo de control de código fuente tras revisar los activos modificados.

## Filas vacías o duplicadas

Las DataTables con ID de fila vacíos o duplicados no se pueden mapear con seguridad a operaciones de fila estables. Cambie el nombre o repare las filas en la tabla propietaria y vuelva a capturar una instantánea.

## Acciones destructivas bloqueadas

La eliminación y otras operaciones destructivas requieren un perfil que las permita y un token explícito de aprobación destructiva. Es preferible previsualizar el plan, guardar copias de seguridad o el estado en el control de código fuente y aplicar únicamente la vista previa revisada.

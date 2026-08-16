<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/CodeCopyrightEditor/architecture.md -->
# Solución de problemas

Esta página enumera problemas comunes y soluciones prácticas.

## La herramienta no aparece en el menú Tools

Verifique:

- El plugin está activado para el proyecto.
- Se reinició Unreal Editor tras activar el plugin.
- El plugin se compiló para la versión actual de Unreal Engine.

Ruta de menú esperada:

```text
Tools > Code Tools > Code Copyright Editor
```

## La página en Project Settings no aparece

Verifique:

- El módulo del plugin se cargó correctamente.
- El proyecto utiliza una compilación de editor, no una compilación de tiempo de ejecución empaquetada.
- El plugin está instalado en la carpeta de plugins del proyecto o del motor.

## El escaneo no encuentra archivos

Verifique:

- `ScanRootPaths` contiene carpetas existentes.
- Los archivos utilizan extensiones compatibles.
- Los fragmentos de ruta excluidos no son demasiado amplios.

## Los archivos están marcados como PROTECTED

El escáner encontró texto similar a un aviso que no coincide con los marcadores propios, o coincidió con marcadores protegidos.

Opciones de resolución:

- Deje el archivo intacto si se trata de código de terceros o de Epic.
- Añada la carpeta del proveedor a las exclusiones.
- Añada un marcador propio únicamente si el archivo realmente pertenece a su proyecto.

## Errores de escritura (Write Errors)

Causas comunes:

- El archivo es de solo lectura.
- El archivo está bloqueado por otro proceso.
- Se requiere la desprotección (checkout) en el control de código fuente.
- La cuenta de usuario carece de permisos de escritura.

Corrija el estado del archivo y vuelva a ejecutar el escaneo/aplicación.

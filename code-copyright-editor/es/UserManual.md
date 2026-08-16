<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/CodeCopyrightEditor/architecture.md -->
# Manual de usuario

Este manual explica el flujo de trabajo completo del editor para Code Copyright Editor.

## Propósito

Code Copyright Editor gestiona el texto de los avisos de derechos de autor en dos lugares:

- El aviso de derechos de autor a nivel de proyecto de Unreal Engine.
- Los encabezados de archivos fuente en las carpetas de proyecto y plugins configuradas.

El plugin está diseñado para reescrituras de código fuente controladas. Escanea primero, muestra una vista previa, permite al usuario seleccionar archivos y solo reescribe los archivos modificables seleccionados tras la confirmación.

## Abrir la herramienta

Tras activar el plugin, abra:

```text
Tools > Code Tools > Code Copyright Editor
```

El plugin también expone su configuración en:

```text
Project Settings > Plugins > Code Copyright Editor
```

## Flujo de trabajo principal

1. Configure la identidad, licencia, plantilla, alcance y ajustes de protección.
2. Guarde la configuración.
3. Actualice el aviso de la configuración del proyecto si es necesario.
4. Escanee el código base.
5. Revise las insignias de estado y las vistas previas.
6. Añada metadatos opcionales por archivo.
7. Seleccione únicamente los archivos que deban reescribirse.
8. Aplique a los archivos seleccionados.
9. Ejecute otro escaneo para verificar.
10. Exporte informes o ejecute el commandlet en CI.

El escaneo nunca escribe en los archivos fuente. La aplicación solo reescribe los archivos marcados clasificados como modificables.

## Pestañas del editor

La ventana principal del editor está organizada en pestañas orientadas a tareas específicas:

| Pestaña | Propósito |
| --- | --- |
| `Configure` | Editar plantillas, configuración de propietario/licencia, alcance de escaneo, reglas de protección y avisos del proyecto. |
| `Scan & Review` | Ejecutar escaneos, inspeccionar estados de archivos, seleccionar archivos modificables, excluir archivos y comparar avisos existentes/propuestos. |
| `File Metadata` | Añadir o borrar información y descripciones de los archivos seleccionados que se muestran mediante tokens de metadatos. |
| `Apply & Reports` | Confirmar las reescrituras seleccionadas y exportar el último informe de escaneo JSON del editor. |
| `Help` | Leer la guía del flujo de trabajo integrada y la leyenda de estados. |

## Valores de estado

| Estado | Significado | Comportamiento de aplicación |
| --- | --- | --- |
| `OK` | El archivo ya coincide con la plantilla generada. | No requerido. |
| `MISSING` | No se encontró ningún aviso compatible. | Se puede insertar si está activado. |
| `REPLACE` | Se puede reemplazar un aviso propio o marcador de posición de Unreal. | Se puede reescribir. |
| `PROTECTED` | Se encontró un aviso externo, de Epic o de terceros. | No se reescribe automáticamente. |
| `CONFLICT` | Aparecen juntos marcadores propios y protegidos. | Se requiere revisión manual. |
| `EXCLUDED` | El archivo coincide con una regla de exclusión. | No procesado. |
| `READ_ERROR` | No se pudo leer el archivo. | No procesado. |
| `WRITE_ERROR` | No se pudo guardar el archivo. | No procesado. |
| `UPDATED` | El archivo se escribió en el último paso de aplicación. | Ejecute otro escaneo para verificar. |

## Metadatos por archivo

Los metadatos por archivo añaden contexto a un solo archivo sin modificar la plantilla global.

Metadatos disponibles:

- `File Information`
- `Description`

Flujo de trabajo recomendado:

1. Escanee archivos.
2. Seleccione un archivo.
3. Ingrese información o descripción del archivo.
4. Haga clic en `Save File Metadata`.
5. Asegúrese de que la plantilla contenga `{FileMetadataBlock}`.
6. Revise la vista previa.
7. Aplique el archivo si el aviso generado es correcto.

`Clear File Metadata` elimina los metadatos guardados para el archivo seleccionado.

## Aplicar seleccionados (Apply Selected)

Antes de aplicar, el editor solicita confirmación. Los archivos protegidos y en conflicto se mantienen intactos.

Tras aplicar, la herramienta ejecuta otro escaneo y muestra:

- Resultado de la aplicación.
- Resultado del escaneo actual.
- Líneas de estado actualizadas.

Utilice el control de código fuente antes de realizar reescrituras masivas. Para obtener una red de seguridad adicional en la primera pasada, active `Create Backup Before Write`.

## Lo que el plugin no hace

Code Copyright Editor no realiza lo siguiente:

- Decidir la titularidad legal.
- Conceder derechos de licencia.
- Validar licencias de terceros.
- Sustituir el asesoramiento legal.
- Reescribir automáticamente avisos protegidos.
- Ejecutarse en juegos empaquetados.

Proporciona un flujo de trabajo técnico coherente para avisos, informes y comprobaciones de CI.

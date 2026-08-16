<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/LogLevelEditor/architecture.md -->
# Documentación de LogLevelEditor

LogLevelEditor es un plugin para el editor de Unreal Engine diseñado para descubrir categorías de registro (logs) y cambiar su nivel de detalle (verbosity) desde un panel enfocado dentro del editor. Ayuda a los equipos a reducir registros ruidosos durante el trabajo diario, elevar temporalmente los canales de diagnóstico durante la depuración y conservar modificaciones intencionadas en un DataAsset.

Las acciones principales son **Scan**, **Set Verbosity** y **Hide Category**.

Esta carpeta contiene la documentación completa entregada con el plugin.

## Empiece aquí

- [BUYER_GUIDE.md](BUYER_GUIDE.md): visión general para compradores, adecuación y valor práctico.
- [UserManual.md](UserManual.md): flujo de trabajo completo en el editor, desde la configuración hasta la aplicación de modificaciones.
- [FAQ.md](FAQ.md): preguntas y respuestas preparadas para Fab.

## Referencia

- [SettingsReference.md](SettingsReference.md): cada ajuste, comportamiento predeterminado y línea base recomendada.
- [TechnicalOverview.md](TechnicalOverview.md): arquitectura y comportamiento en tiempo de ejecución para mantenedores.
- [CodeDocumentation.md](CodeDocumentation.md): estructura del código fuente, contratos y puntos de extensión.
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md): problemas comunes y soluciones.
- [ReleaseChecklist.md](ReleaseChecklist.md): pasos de validación antes de publicar una actualización en Fab.

## Assets incluidos

- `../Readme.pdf`: leído tradicional empaquetado.
- `../LogLevelEditor_Changelog.txt`: notas de la versión.
- `../Content/DA_LogLevelVerbosity.uasset`: DataAsset predeterminado utilizado para modificaciones persistentes de nivel de detalle.
- `../Content/Map_Tutorial_LogLevelEditor.umap`: contenido de tutorial y demostración.

## Flujo de trabajo rápido

1. Active el plugin y reinicie el editor cuando se le solicite.
2. Abra la pestaña Log Level Editor desde **Tools → Log Tools → Log Level Editor** o mediante el acceso directo opcional de la barra de herramientas.
3. Deje que el escáner descubra las categorías de log del proyecto y de los plugins.
4. Utilice la búsqueda y la configuración para ocultar y enfocarse en los canales importantes.
5. Cambie el nivel de detalle de una categoría mediante los botones de nivel de detalle en la fila correspondiente.
6. Guarde las modificaciones en el `ULogLevelDataAsset` configurado cuando el cambio sea intencionado.
7. Restablezca una categoría a su valor predeterminado detectado seleccionando nuevamente ese valor predeterminado.

## Lo que cambia la herramienta

El plugin aplica comandos de consola de Unreal en la forma:

```text
Log <CategoryName> <VerbosityName>
```

No modifica la declaración en código fuente de una categoría de registro. Los cambios persistentes se almacenan en el DataAsset configurado y el módulo del editor los vuelve a aplicar cuando el motor está listo para aceptar comandos de consola.

## Nombres de verbosidad compatibles

El asistente de nivel de detalle compartido admite los niveles de registro estándar de Unreal:

- `NoLogging`
- `Fatal`
- `Error`
- `Warning`
- `Display`
- `Log`
- `Verbose`
- `VeryVerbose`

El editor utiliza intencionadamente los mismos nombres que muestra la configuración de registro de Unreal para que los usuarios puedan asociar los cambios en la interfaz con el comportamiento de los comandos de consola.

## Modelo de seguridad

LogLevelEditor evita mostrar estados incorrectos al usuario:

- La etiqueta `Current` se obtiene del estado en tiempo de ejecución de Unreal cuando la categoría se puede consultar.
- El estado de la interfaz se actualiza solo después de que un comando de consola se ejecuta con éxito.
- Las modificaciones persistentes se eliminan cuando el valor seleccionado coincide con el valor predeterminado detectado.
- Los ajustes de ocultación temporal permanecen volátiles y no se escriben en la configuración.
- Las modificaciones guardadas se aplican con una lógica de reintento por categoría durante el inicio, ya que el editor no siempre está listo para aceptar comandos de consola al iniciar el módulo.

## Usos típicos

- Reducir el ruido de un plugin muy ruidoso mientras se mantiene el plugin activado.
- Elevar temporalmente un subsistema de gameplay, compilación, asset o editor a `Verbose`.
- Restaurar valores predeterminados limpios tras investigar un problema.
- Compartir un DataAsset de equipo con modificaciones intencionadas de nivel de detalle para todo el proyecto.
- Mantener las categorías del motor y del proyecto separadas mediante ajustes para que los escaneos sigan siendo rápidos y relevantes.

## Limitaciones importantes

- Las categorías de registro deben existir en el código fuente o estar registradas previamente por módulos de ejecución o del editor.
- El escaneo de código fuente solo puede deducir valores predeterminados a partir de macros comunes de Unreal.
- El código en tiempo de ejecución puede cambiar el nivel de detalle después de que el editor aplique las modificaciones guardadas.
- Las versiones empaquetadas finales (Shipping builds) no se ven afectadas por este plugin del editor.

## Nota legal

LogLevelEditor es una herramienta de productividad para el editor. No cambia la semántica de registro de Unreal Engine, el código fuente del motor ni los términos de licencia del proyecto.

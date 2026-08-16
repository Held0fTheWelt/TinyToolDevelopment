<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/LogLevelEditor/architecture.md -->
# Manual del usuario

Este manual explica el flujo de trabajo diario en el editor para LogLevelEditor.

## Instalación

1. Añada el plugin a la carpeta `Plugins` de su proyecto o instálelo a través de Fab.
2. Active **LogLevelEditor** en **Edit > Plugins**.
3. Reinicie el editor si Unreal lo solicita.
4. Confirme que el contenido del plugin es visible si desea inspeccionar el DataAsset predeterminado.

## Abrir la herramienta

Abra LogLevelEditor desde **Tools → Log Tools → Log Level Editor** o mediante el acceso directo opcional de la barra de herramientas. El plugin se abre como una pestaña acoplable para permanecer en el espacio de trabajo del editor.

## Primer escaneo

Al abrirse, la herramienta escanea las ubicaciones configuradas en busca de categorías de registro.

Por defecto se centra en:

- Archivos de código fuente del proyecto.
- Archivos de código fuente de los plugins del proyecto.

Las opciones adicionales pueden incluir:

- Archivos de código fuente de plugins del motor.
- Archivos de código fuente del motor.

Los escaneos del motor pueden llevar tiempo. Actívelos solo cuando realmente necesite categorías del motor en su panel.

## Lectura de la lista

Cada fila representa una categoría de registro.

Campos importantes:

- Nombre de categoría: el nombre de la categoría de registro en Unreal, por ejemplo `LogTemp`.
- Valor predeterminado detectado: la verbosidad predeterminada deducida de la macro de declaración/definición cuando es posible.
- Nivel actual: el nivel de detalle que Unreal informa actualmente para la categoría registrada. Si Unreal aún no puede informarlo, la fila muestra `Unavailable`. Tras el escaneo inicial, este valor se actualiza periódicamente a partir del estado en tiempo de ejecución.
- Ruta fuente: dónde encontró el escáner la categoría, cuando está disponible.

## Cambiar el nivel de detalle

1. Busque la categoría mediante la búsqueda/filtrado.
2. Elija un valor de nivel de detalle en los botones de la fila.
3. El plugin ejecuta el comando de consola de Unreal.
4. La fila y el DataAsset se actualizan solo tras la ejecución correcta del comando.

Opciones comunes:

- `Warning`: reducir el ruido manteniendo los problemas importantes.
- `Log`: estándar habitual para salidas normales.
- `Verbose`: útil para diagnóstico.
- `VeryVerbose`: salida muy detallada y normalmente temporal.
- `NoLogging`: silenciar una categoría todo lo que Unreal permita.

## Restaurar valores predeterminados

Cuando el nivel de detalle seleccionado coincide con el valor predeterminado detectado, el plugin elimina la modificación persistente para esa categoría. Esto mantiene el DataAsset enfocado en cambios reales.

Si no se detectó ningún valor predeterminado, trate la fila como informativa y restablezca manualmente al valor que su proyecto espera.

## Modificaciones persistentes

Los valores persistentes se almacenan en el `ULogLevelDataAsset` configurado.

Flujo de trabajo recomendado:

1. Mantenga las modificaciones deliberadas para todo el proyecto en el DataAsset predeterminado.
2. Incluya el asset en el control de versiones solo si esas modificaciones representan la política del equipo.
3. Evite guardar ruido de depuración temporal en el control de código fuente compartido.
4. Utilice ajustes de ocultación temporal para su enfoque personal en la interfaz.

## Aplicación en el inicio

Las modificaciones guardadas se vuelven a aplicar durante el inicio del editor. El módulo espera hasta que el motor pueda aceptar comandos de consola y reintenta un pequeño número de veces si el inicio es demasiado temprano.

## Ocultar categorías

Lista de ocultación permanente:

- Almacenada en la configuración.
- Útil para categorías que rara vez deberían aparecer en la herramienta.

Lista de ocultación temporal:

- Almacenada de forma volátil.
- Útil para el enfoque local durante una sesión de edición.
- No se escribe en la configuración.

## Ajustes

Abra los ajustes del plugin en la sección de configuración registrada del editor/proyecto.

Ajustes clave:

- `LogLevelDataAsset`: DataAsset utilizado para almacenar modificaciones persistentes.
- `bAutoSaveLogLevelDataAsset`: guarda el DataAsset automáticamente tras cambios intencionados.
- `bShowToolbarButton`: muestra u oculta el acceso directo en la barra de herramientas.
- `bAlsoListEnginePluginChannels`: incluye categorías de plugins del motor en los escaneos.
- `bAlsoListEngineSourceChannels`: incluye categorías del código fuente del motor en los escaneos.
- `LogChannelsToHide`: categorías ocultas de forma permanente.
- `LogChannelsToHideTemporary`: categorías ocultas solo durante la sesión.

## Flujo de trabajo de equipo recomendado

Para uso en equipo:

1. Mantenga el DataAsset predeterminado en el control de código fuente.
2. Guarde solo modificaciones estables que representen la política del proyecto.
3. No incluya ocultaciones temporales locales en sus commits.
4. Documente perfiles de depuración en la wiki de su proyecto.

## Eliminar el plugin

Antes de eliminar el plugin:

1. Restablezca los cambios temporales de nivel de detalle.
2. Elimine o ignore el DataAsset del plugin si ya no se utiliza.
3. Desactive el plugin y reinicie el editor.

El plugin no modifica las declaraciones en código fuente de las categorías de registro, por lo que su eliminación no requiere limpieza en C++.

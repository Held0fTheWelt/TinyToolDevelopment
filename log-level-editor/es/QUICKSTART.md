<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/LogLevelEditor/architecture.md -->
# Guía de inicio rápido

Esta guía le acompañará desde la instalación hasta un **resultado real**: el nivel de detalle (verbosity) de una categoría de registro modificado y guardado como una modificación persistente que sobrevive a los reinicios del editor. Log Level Editor funciona de forma autónoma: no se requiere ningún otro plugin.

## Lo que obtendrá tras esta guía

La herramienta abierta con las categorías de registro de su proyecto enumeradas, el nivel de detalle de una categoría modificado y esa modificación guardada de forma persistente en el DataAsset del plugin.

## Requisitos

- Editor de Unreal Engine 5.
- No se requiere software de terceros, cuenta ni runtime adicional. Consulte [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md).

## 1. Instalación y activación

1. Añada **LogLevelEditor** desde su biblioteca Fab al proyecto (o instálelo en el motor).
2. Abra **Edit → Plugins**, active **LogLevelEditor** y reinicie cuando se le solicite.

## 2. Abrir la herramienta (Primer resultado)

1. Abra **Tools → Log Tools → Log Level Editor**. Se abrirá una pestaña acoplable que escaneará el código fuente de su proyecto (y de los plugins de su proyecto) en busca de categorías de registro.
2. Cada fila muestra el **nombre de la categoría** (ej. `LogTemp`), su **valor predeterminado detectado**, el **nivel actual** y la **ruta del código fuente** cuando esté disponible.

Ahora puede ver cada categoría de registro descubierta y su nivel de detalle en tiempo real.

## 3. Un ejemplo práctico: Cambiar el nivel de detalle de una categoría

1. Utilice el cuadro de búsqueda para encontrar `LogTemp`.
2. Haga clic en el botón de nivel de detalle **Warning** en esa fila.

**Resultado esperado:** el plugin ejecuta el comando de consola de Unreal correspondiente, la fila se actualiza a `Warning` y el cambio se escribe como una modificación persistente en el DataAsset del plugin (de modo que se vuelve a aplicar en el próximo inicio del editor).

3. Para deshacer: seleccione el **valor predeterminado detectado** de la fila. Cuando el valor seleccionado coincide con el predeterminado detectado, el plugin elimina la modificación persistente de forma automática para mantener el DataAsset centrado en cambios reales.

## 4. Dónde residen las modificaciones

Las modificaciones persistentes se almacenan en el `ULogLevelDataAsset` configurado (establecido a través de **LogLevelDataAsset** en los ajustes). Las modificaciones guardadas se aplican de nuevo durante el inicio del editor una vez que el motor puede aceptar comandos de consola.

## 5. Configuración

Abra los ajustes del plugin (Project/Editor settings → Log Level Editor) para controlar:

- `LogLevelDataAsset`, `bAutoSaveLogLevelDataAsset`
- `bShowToolbarButton`
- `bAlsoListEnginePluginChannels`, `bAlsoListEngineSourceChannels` (los escaneos del motor son costosos)
- `LogChannelsToHide`, `LogChannelsToHideTemporary`

Consulte [SettingsReference.md](SettingsReference.md).

## 6. Siguientes pasos

- Flujo de trabajo completo (ocultación temporal frente a permanente, trabajo en equipo, aplicación en el inicio):
  [UserManual.md](UserManual.md).
- Problemas: [TROUBLESHOOTING.md](TROUBLESHOOTING.md) y [FAQ.md](FAQ.md).

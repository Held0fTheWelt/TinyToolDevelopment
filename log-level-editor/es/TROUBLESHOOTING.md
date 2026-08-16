<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/LogLevelEditor/architecture.md -->
# Solución de problemas

## La herramienta no muestra mi categoría

Compruebe:

- La categoría está declarada o definida en una ruta fuente escaneada.
- La extensión del archivo es `.h`, `.hpp`, `.cpp` o `.inl`.
- La categoría no está oculta por ajustes de ocultación permanente o temporal.
- El escaneo ha finalizado o sigue en proceso.
- La macro pertenece a una de las formas de macros de registro de Unreal compatibles.

## El nivel predeterminado no aparece o es incorrecto

El escáner solo puede deducir valores predeterminados a partir de argumentos de macro reconocibles. Algunas categorías pueden aparecer con un valor predeterminado vacío o alternativo.

Soluciones:

- Utilice el formato de macro estándar de Unreal cuando sea posible.
- Añada una modificación persistente si necesita un valor conocido.

## Cambiar el nivel de detalle no hace nada

Causas posibles:

- La categoría aún no está registrada por ningún módulo cargado.
- Unreal rechazó el comando de consola.
- El código en tiempo de ejecución modificó la categoría de nuevo tras el comando del editor.

Consulte el Output Log para ver los mensajes de `LogLogLevelEditor`.

## El nivel de detalle guardado no se aplica al iniciar

Compruebe:

- `LogLevelDataAsset` apunta a un asset válido.
- El DataAsset contiene entradas de modificación.
- La categoría existe cuando se ejecuta el reintento de aplicación en el inicio.

## Mi DataAsset contiene demasiadas entradas

El DataAsset solo debe contener modificaciones intencionadas. Restablezca las filas a sus valores predeterminados detectados para eliminar entradas innecesarias.

## Los valores ocultos temporalmente han vuelto a aparecer

Los valores ocultos temporalmente son volátiles y no persisten entre sesiones. Utilice `LogChannelsToHide` para una ocultación permanente.

## El escaneo tarda demasiado

Desactive el escaneo de plugins y código fuente del motor a menos que sea necesario.

Configuración normal recomendada:

```text
bAlsoListEnginePluginChannels = false
bAlsoListEngineSourceChannels = false
```

## El Output Log sigue siendo ruidoso

Algunos sistemas pueden registrar información a través de múltiples categorías. Busque prefijos de categorías relacionados y ajuste cada canal relevante.

## El plugin se abre pero no muestra modificaciones del DataAsset

El escáner y el DataAsset son independientes:

- Escáner: descubre las categorías disponibles.
- DataAsset: almacena las modificaciones persistentes.

Un DataAsset vacío es totalmente normal si no se han configurado modificaciones persistentes.

## El control de código fuente muestra constantemente que mi DataAsset ha cambiado

Probablemente cambió modificaciones persistentes. Mantenga los cambios como política de equipo o restablezca las filas a sus valores predeterminados antes de incluir los cambios en su commit.

## Información de soporte que recopilar

Al informar sobre un problema, incluya:

- Versión de Unreal Engine.
- Versión del plugin.
- Si el escaneo de código fuente/plugins del motor está activado.
- Ejemplo de declaración de categoría de registro.
- Salida relevante de `LogLogLevelEditor`.

<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/LightweightEditorMode/architecture.md -->
# Solución de problemas

Esta guía cubre los problemas comunes y sus causas probables.

## Falta la ventana del plugin

Compruebe lo siguiente:

- El plugin está activado en Edit > Plugins.
- Se reinició el proyecto tras activar el plugin.
- El módulo está listado en la matriz Plugins del archivo .uproject.
- Está ejecutando el editor y no un commandlet.

La ventana debería aparecer bajo Tools > Performance > Lightweight Editor Mode.

## El modo no se activa al iniciar

La activación al iniciar espera hasta que existan los clientes de viewport del editor. En un proyecto lento, esto puede tardar un momento tras iniciar el módulo.

Compruebe:

- Enable on Editor startup está marcado.
- El plugin está activado en el proyecto.
- El editor creó efectivamente viewports del level editor.
- Los registros contienen "Scheduling Lightweight Mode auto-enable".
- Los registros contienen más adelante "Auto-enabling Lightweight Mode after editor viewports became available".

Si la opción se desmarca antes de que los viewports estén disponibles, el temporizador se cancela.

## El porcentaje de pantalla parece no cambiar

Los viewports del editor no siempre obedecen a r.ScreenPercentage. Lightweight Editor Mode utiliza CVars específicas para el viewport del editor:

- r.Editor.Viewport.ScreenPercentage
- r.Editor.Viewport.ScreenPercentageMode.RealTime
- r.Editor.Viewport.ScreenPercentageMode.NonRealTime

Si el viewport sigue pareciendo no haber cambiado, compruebe:

- El valor de ScreenPercentage del perfil seleccionado.
- Si el viewport usa una ruta del motor que anula el porcentaje de pantalla.
- Si otro plugin o comando de consola modifica las mismas CVars de editor después de que se ejecute Lightweight Editor Mode.

## Los viewports permanecen en Unlit tras desactivar

La restauración en la misma sesión usa copias de seguridad por viewport. La recuperación tras reiniciar solo cuenta con el valor guardado LastViewModeBeforeLightweight.

Pruebe:

1. Abra la ventana del plugin.
2. Haga clic en Disable Lightweight Mode.
3. Si es necesario, cambie manualmente el viewport de nuevo a Lit.
4. Active y desactive el modo de nuevo en la misma sesión para confirmar la restauración normal.

Si esto ocurre con frecuencia, compruebe si se está cerrando el editor mientras el modo sigue activado.

Tras un bloqueo o cierre forzado, el botón principal puede mostrar Restore Lightweight State. Haga clic en él para ejecutar la restauración conservadora del viewport y borrar la marca de sesión obsoleto.

## El tiempo real permanece desactivado

La desactivación del tiempo real utiliza el sistema de anulación temporal de tiempo real de Unreal. En la misma sesión, Disable elimina la anulación del modo sin cambiar la preferencia de tiempo real guardada del viewport.

Si el tiempo real sigue desactivado, compruebe si otro sistema del editor tiene su propia anulación activa. Vuelva a activar manualmente el tiempo real desde el menú del viewport si es necesario.

## Lumen sigue apareciendo activado

Compruebe si:

- El perfil seleccionado tiene bDisableLumen activado.
- El proyecto utiliza realmente Lumen.
- Otro plugin o código del proyecto establece CVars de Lumen después de activar el modo.
- Una rama personalizada del motor renombró o eliminó las CVars correspondientes.

El plugin se dirige a:

- r.Lumen.DiffuseIndirect.Allow
- r.Lumen.Reflections.Allow

Las CVars que no existen se omiten y se registran en el log con nivel Verbose.

## Las sombras siguen pareciendo costosas

bDisableVirtualShadows se dirige a los mapas de sombras virtuales (Virtual Shadow Maps):

- r.Shadow.Virtual.Enable

Esto no desactiva todos los costes de sombra posibles en cada ruta del renderer. Si su escena usa sombras no virtuales, sistemas de sombras personalizados, sombras trazadas por rayos o renderizado por plugin, se pueden requerir ajustes adicionales específicos del proyecto.

## La niebla sigue apareciendo

bDisableVolumetricFog establece:

- r.VolumetricFog = 0
- r.Fog = 0

Algunos materiales, volúmenes de posprocesado, sistemas de cielo o efectos de atmósfera personalizados aún pueden generar una apariencia similar a la niebla.

## El editor se ve con una calidad demasiado baja

Utilice un perfil menos agresivo:

- Cambie de Extreme a Aggressive.
- Cambie de Aggressive a Balanced.
- Aumente ScreenPercentage.
- Aumente OverallQuality.
- Desactive Force Unlit para un perfil personalizado.

Tras cambiar el perfil estando el modo activado, la herramienta actualiza los ajustes activos automáticamente.

## El editor sigue yendo lento

Lightweight Editor Mode se centra en el coste de renderizado del viewport del editor. No puede solucionar todos los problemas de rendimiento del editor.

Otros posibles cuellos de botella:

- Compilación de assets.
- Compilación de shaders.
- Operaciones de control de código fuente.
- Construction scripts de Blueprints.
- Editor Utility Widgets.
- Lógica de Tick pesada en los mundos del editor.
- Cantidad masiva de actors.
- Carga de disco o antivirus.

Utilice Unreal Insights, comandos Stat y perfiles del proyecto para diagnosticar cuellos de botella que no sean de renderizado.

## Disable no restaura una CVar

La ruta de restauración elimina la anulación etiquetada del plugin. Si otro sistema cambió la misma CVar mientras Lightweight Editor Mode estaba activo, ese valor más reciente permanecerá en lugar de ser sobrescrito por la copia de seguridad anterior.

Consulte el Output Log para ver el nombre de la CVar. El plugin registra las operaciones de copia de seguridad y restauración.

## La página de Project Settings está oculta o falta

La página de configuración debería aparecer en Project Settings > Plugins > Lightweight Editor Mode.

Si falta:

- Confirme que el módulo se cargó.
- Confirme que el módulo Settings está disponible.
- Reinicie el editor tras activar el plugin.
- Compruebe que no haya ningún descriptor de plugin o problema de compilación que impidiera la carga del módulo.

## La compilación falla tras añadir una nueva CVar

Causas comunes:

- Se añadió la constante del nombre de la CVar pero no se usó de forma coherente.
- Se añadió el ajuste a la estructura de perfil pero no a los campos activos.
- La instrucción switch de la interfaz no se actualizó para un nuevo perfil.
- Falta la inclusión de un tipo de Unreal.
- Error de sintaxis en un bloque de metadatos UPROPERTY.

Compile la meta del editor tras realizar cambios en el código fuente.

## Registros que inspeccionar

Busque en el Output Log:

- [Module]
- [Lightweight]
- Backup CVar
- Restore CVar
- ApplyActiveSettings
- ApplyViewportSettings
- Lightweight mode ENABLED
- Lightweight mode DISABLED

Los registros son deliberadamente explícitos para que las solicitudes de asistencia puedan incluir la secuencia relevante.

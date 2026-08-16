<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/LightweightEditorMode/architecture.md -->
# Referencia de configuración

Lightweight Editor Mode almacena su configuración en EditorPerProjectUserSettings y la expone en Project Settings > Plugins > Lightweight Editor Mode.

## Modelo de configuración

El objeto de configuración consta de tres capas:

- Opciones de alto nivel, como el comportamiento de inicio y el índice de perfil seleccionado.
- Valores activos en tiempo de ejecución consumidos por el modo cuando está activado.
- Cuatro estructuras de perfil editables: Mild, Balanced, Aggressive y Extreme.

La interfaz de usuario Slate copia el perfil seleccionado en los valores activos en tiempo de ejecución antes de activar o actualizar el modo.

## Opciones de alto nivel

### bEnableOnStartup

Activa automáticamente Lightweight Editor Mode al iniciar el editor.

Notas de implementación:

- El módulo no se activa inmediatamente durante StartupModule.
- Inicia un breve temporizador.
- El temporizador espera hasta que GEditor disponga de clientes de viewport del editor.
- El modo se activa únicamente cuando los viewports están disponibles.
- La recuperación de sesiones obsoletas se ejecuta antes de la activación automática si la sesión previa del editor terminó mientras el modo aún estaba activo.

Esto evita perder cambios en los viewports durante el inicio temprano del editor.

### AggressivenessLevel

Almacena el índice del perfil actualmente seleccionado.

| Valor | Perfil |
| --- | --- |
| 0 | Mild |
| 1 | Balanced |
| 2 | Aggressive |
| 3 | Extreme |

El valor se limita al rango válido.

## Valores activos en tiempo de ejecución

Estos valores los aplica FEditorLightweightMode.

### OverallQuality

Un único nivel de calidad de escalabilidad de Unreal.

| Valor | Significado |
| --- | --- |
| 0 | Low (Baja) |
| 1 | Medium (Media) |
| 2 | High (Alta) |
| 3 | Epic (Épica) |
| 4 | Cinematic (Cinematográfica) |

El plugin limita este valor al rango 0..4 antes de aplicarlo.

### ScreenPercentage

Porcentaje de pantalla objetivo para el renderizado del viewport del editor y las rutas de vista previa PIE/juego.

| Rango | Significado |
| --- | --- |
| 25..59 | Muy agresivo, baja fidelidad visual |
| 60..79 | Edición orientada al rendimiento |
| 80..99 | Edición equilibrada |
| 100 | Resolución interna completa |
| 101..200 | Supersampling, raras veces útil para el modo ligero |

El plugin limita este valor al rango 25..200.

Detalle de implementación importante: los viewports del editor utilizan CVars de porcentaje de pantalla específicas para el editor. El plugin establece:

- r.Editor.Viewport.ScreenPercentage
- r.Editor.Viewport.ScreenPercentageMode.RealTime
- r.Editor.Viewport.ScreenPercentageMode.NonRealTime

También establece r.ScreenPercentage para las rutas PIE y de vista previa del juego donde esa CVar sigue siendo relevante.

### bDisableLumen

Desactiva la iluminación indirecta difusa Lumen y los reflejos Lumen mientras el modo está activo.

CVars:

- r.Lumen.DiffuseIndirect.Allow = 0
- r.Lumen.Reflections.Allow = 0

Cuando se desactiva en el perfil, el plugin restaura cualquier copia de seguridad existente para estas CVars eliminando su anulación etiquetada. Si otra fuente cambió la misma CVar mientras el modo estaba activo, ese valor más reciente permanecerá activo.

### bDisableVirtualShadows

Desactiva los mapas de sombras virtuales (Virtual Shadow Maps).

CVar:

- r.Shadow.Virtual.Enable = 0

Esto puede hacer que las escenas pesadas con Nanite y grandes mundos sean más fluidas, pero también cambia significativamente la apariencia de las sombras.

### bDisableVolumetricFog

Desactiva la niebla volumétrica y la niebla estándar.

CVars:

- r.VolumetricFog = 0
- r.Fog = 0

Esto es útil en escenas atmosféricas donde la niebla domina el tiempo de renderizado del editor por fotograma.

### bForceUnlitViewports

Cambia los viewports del editor a Unlit (sin iluminación) mientras el modo está activo.

El plugin almacena el modo de visualización original por viewport antes de cambiarlo. Cuando el modo se desactiva en la misma sesión del editor, se restauran los modos de visualización originales.

### bDisableViewportRealtime

Desactiva el renderizado en tiempo real en los viewports del editor mientras el modo está activo.

El plugin utiliza el sistema de anulación temporal en tiempo real de Unreal en lugar de cambiar la preferencia persistente del viewport. Cuando se desactiva, elimina su propia anulación.

## Valores por perfil

Cada perfil contiene los mismos campos:

- OverallQuality
- ScreenPercentage
- bDisableLumen
- bDisableVirtualShadows
- bDisableVolumetricFog
- bForceUnlitViewports
- bDisableViewportRealtime

Los perfiles son editables en Project Settings. Modificar un perfil no lo aplica de inmediato a menos que la interfaz de usuario copie ese perfil en los valores activos.

## LastViewModeBeforeLightweight

Este ajuste oculto-visible almacena el último modo de visualización observado antes de activar el modo. Se utiliza como alternativa persistente tras reiniciar el editor.

La restauración en la misma sesión utiliza primero las copias de seguridad por viewport. La recuperación tras el reinicio no puede usar esas copias de seguridad en memoria, por lo que el valor alternativo solo se usa para devolver los viewports Unlit a un modo razonable.

## bWasLightweightModeActiveLastSession

Este ajuste de diagnóstico visible registra si el modo estuvo activo antes de la última salida del editor. Se establece cuando Enable comienza a aplicar anulaciones y se borra con Disable.

Si sigue siendo verdadero (true) tras reiniciar, la interfaz de usuario ofrece Restore Lightweight State y la activación automática al inicio restaura el estado anterior del viewport antes de activarlo de nuevo.

## Propósito de los perfiles predeterminados

| Perfil | Propósito |
| --- | --- |
| Mild | Ligero alivio manteniendo el contexto visual |
| Balanced | Opción recomendada por defecto para edición general |
| Aggressive | Edición de escenas pesadas donde prima la fluidez |
| Extreme | Edición de emergencia o en equipos de muy bajos recursos |

## Personalización recomendada

Para equipos centrados en el arte, haga que Mild sea menos destructivo y deje activa la vista Lit. Para flujos de trabajo de grandes mundos o portátiles, haga que Balanced sea más agresivo. Para depuración técnica, mantenga al menos un perfil que no fuerce Unlit para poder inspeccionar los problemas de renderizado rápidamente.

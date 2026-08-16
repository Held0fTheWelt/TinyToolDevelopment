<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/LightweightEditorMode/architecture.md -->
# Manual del usuario

Este manual explica cómo utilizar Lightweight Editor Mode en el trabajo diario dentro del editor de Unreal Engine.

## Propósito

Las escenas de gran tamaño en Unreal Engine pueden hacer que los viewports del editor sean muy exigentes, incluso cuando el rendimiento final del juego es aceptable. La alta resolución del viewport, Lumen, las sombras virtuales, la niebla volumétrica, la actualización continua en tiempo real y los niveles de escalabilidad altos pueden consumir un valioso tiempo de renderizado durante la edición.

Lightweight Editor Mode ofrece un conmutador rápido para un perfil de edición temporal y reversible. Es especialmente útil cuando se necesita agilidad para el diseño de niveles, blocking, trabajo en Blueprints, vegetación, colocación de assets o limpieza del proyecto.

## Abrir la ventana

1. Abra el editor de Unreal Engine.
2. Asegúrese de que el plugin Lightweight Editor Mode esté activado.
3. Vaya a Tools > Performance > Lightweight Editor Mode.
4. El plugin abrirá una pestaña acoplable en el editor.

La pestaña contiene un menú desplegable de perfiles, un botón de activación y una casilla opcional para el inicio.

## Elegir un perfil

El perfil controla la agresividad con la que el editor reduce el coste de renderizado.

### Mild

Mild está destinado a proyectos que solo necesitan un pequeño impulso. Mantiene el comportamiento del viewport más cercano a lo normal y es una buena primera opción cuando aún necesita contexto visual.

Comportamiento típico:

- Mayor porcentaje de pantalla (Screen Percentage).
- Mayor escalabilidad que los perfiles agresivos.
- No fuerza el modo Unlit de forma predeterminada.
- No desactiva el tiempo real del viewport de forma predeterminada.

### Balanced

Balanced es la opción predeterminada recomendada. Reduce la iluminación costosa y el coste del viewport manteniéndose práctico para la edición general.

Comportamiento típico:

- Porcentaje de pantalla medio.
- Menor escalabilidad general.
- Desactiva funciones de renderizado exigentes.
- Fuerza el modo Unlit y desactiva el tiempo real de forma predeterminada.

### Aggressive

Aggressive es para escenas pesadas donde la agilidad del viewport importa más que la fidelidad visual.

Comportamiento típico:

- Menor porcentaje de pantalla.
- Escalabilidad baja.
- Iluminación, sombras y niebla costosas desactivadas.
- Viewports forzados al modo Unlit.
- Actualización del viewport en tiempo real desactivada.

### Extreme

Extreme es para proyectos sobrecargados, edición en portátiles, grandes mundos o necesidades urgentes de fluidez. Utilícelo cuando solo necesite la estructura de la escena y velocidad de interacción.

Comportamiento típico:

- Porcentaje de pantalla muy bajo.
- Escalabilidad mínima.
- Funciones de renderizado exigentes desactivadas.
- Viewports en Unlit y edición sin tiempo real.

## Activar el modo

1. Seleccione un perfil.
2. Haga clic en Enable Lightweight Mode.
3. El plugin aplicará el perfil activo.
4. Los viewports se actualizarán inmediatamente.

Cuando está activado, el plugin guarda una copia de seguridad del estado original del editor que necesitará restaurar:

- Niveles de calidad de escalabilidad.
- Valores de variables de consola modificados.
- Modos de visualización de los viewports cuando se fuerza Unlit.
- Anulaciones temporales de tiempo real en el viewport.

## Cambiar de perfil mientras está activado

Puede elegir otro perfil mientras el modo ya está activado. El plugin actualiza los ajustes activos y conserva las copias de seguridad originales anteriores a la activación del modo. Esto significa que Disable Lightweight Mode seguirá restaurando el estado previo al modo en lugar de un perfil intermedio.

## Desactivar el modo

Haga clic en Disable Lightweight Mode para restaurar el estado del editor.

El plugin restaura:

- Niveles de escalabilidad guardados en la copia de seguridad.
- Las anulaciones de variables de consola del plugin. Si otro sistema cambió el mismo valor mientras el modo estaba activo, se conservará ese valor más reciente.
- Modos de visualización del viewport guardados.
- Anulaciones temporales de tiempo real.

Si el editor se reinició antes de desactivar el modo, las copias de seguridad por sesión ya no existirán. En ese caso, el plugin utiliza el modo de visualización alternativo guardado en la configuración y realiza solo una restauración conservadora del viewport. Cuando se detecta este estado obsoleto, el botón muestra Restore Lightweight State.

## Activar al iniciar el editor (Enable on Editor startup)

La casilla Enable on Editor startup guarda un ajuste de usuario. Cuando está activada, el plugin espera a que existan los viewports del editor y luego activa automáticamente Lightweight Editor Mode.

Este comportamiento de inicio diferido es intencionado. Durante el inicio temprano del módulo, es posible que Unreal aún no haya creado los clientes de viewport del editor, por lo que se podrían perder cambios inmediatos. El plugin utiliza un breve temporizador y activa el modo cuando el editor está listo.

Si el inicio automático se ejecuta después de que una sesión anterior terminara antes de desactivar el modo, el plugin realiza primero la restauración conservadora del viewport y luego vuelve a activar el perfil seleccionado.

## Flujos de trabajo recomendados

### Blocking de niveles

Utilice Balanced o Aggressive. Normalmente no necesita iluminación final mientras define espacios, comprueba la navegación o mueve grandes grupos de actors.

### Edición de vegetación o mundo

Utilice Aggressive. Las escenas con mucha vegetación pueden ser costosas en vista Lit con sombras y actualizaciones en tiempo real.

### Iteración en Blueprints o Gameplay

Utilice Mild o Balanced. Mantenga suficiente contexto visual mientras hace que la respuesta del editor sea más cómoda.

### Revisión de iluminación

Desactive Lightweight Editor Mode. El plugin oculta o reduce intencionadamente las funciones de iluminación, por lo que no es adecuado para la aprobación visual final.

### Captura cinematográfica o capturas de pantalla

Desactive Lightweight Editor Mode, restaure la escalabilidad de producción y revise la toma en el modo de viewport previsto.

## Ajustes del proyecto (Project Settings)

Abra Project Settings > Plugins > Lightweight Editor Mode para editar perfiles y valores activos.

Las estructuras de perfil son la fuente de verdad para Mild, Balanced, Aggressive y Extreme. Los valores activos son los que aplica el asistente de tiempo de ejecución cuando el modo está activado. La interfaz de usuario copia el perfil seleccionado en los valores activos antes de aplicar el modo.

## Qué esperar visualmente

Dependiendo del perfil, el viewport puede pasar a ser:

- De menor resolución.
- Sin iluminación (Unlit).
- Menos detallado.
- Con menos sombras.
- Sin niebla.
- Sin actualización en tiempo real hasta que interactúe o lo actualice manualmente.

Esto es lo esperado. El objetivo es la velocidad de interacción, no la calidad de renderizado final.

## Lo que el plugin no hace

- No cambia la configuración de tiempo de ejecución de los juegos empaquetados.
- No edita de forma permanente la configuración del renderer del proyecto.
- No sobrescribe de forma permanente los assets de mapa.
- No reemplaza el trabajo de escalabilidad de Unreal, LOD, HLOD, Nanite ni optimización de contenido.
- No garantiza resultados idénticos en todas las versiones del motor y bifurcaciones personalizadas del renderer.

## Hábito práctico

Utilice Lightweight Editor Mode como un modo de trabajo. Desactívelo antes de revisiones finales, antes de reportar errores de renderizado y antes de capturar imágenes para el marketplace o producción.

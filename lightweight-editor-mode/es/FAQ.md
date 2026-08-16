<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/LightweightEditorMode/architecture.md -->
# Preguntas frecuentes (FAQ)

Esta lista de preguntas frecuentes está redactada tanto para compradores como para soporte técnico. Responde a las dudas que un usuario suele tener antes de la compra, durante la configuración inicial y al validar la restauración en un proyecto real.

## Respuestas rápidas

### ¿Qué es Lightweight Editor Mode?

Lightweight Editor Mode es un plugin para el editor de Unreal Engine que reduce temporalmente el coste de renderizado del viewport del editor mediante perfiles configurables. Está pensado para hacer más fluida la edición de escenas pesadas.

### ¿Es un plugin de optimización en tiempo de ejecución?

No. Es una herramienta para el flujo de trabajo del editor. No optimiza su juego empaquetado ni sustituye el profiling en tiempo de ejecución o la optimización de contenidos.

### ¿Afecta a las versiones empaquetadas?

No. El plugin es exclusivo para el editor. Cambia el estado de la sesión de edición mientras trabaja en Unreal Editor y no tiene ningún efecto en juegos empaquetados.

### ¿Cambia mi proyecto de forma permanente?

No. El modo está diseñado como una capa temporal. Guarda una copia de seguridad de los valores que modifica y los restaura cuando se desactiva. Los ajustes de perfil se guardan como preferencias del usuario del editor, pero los mapas, assets y ajustes de renderizado del proyecto no se modifican.

### ¿A quién va dirigido?

Está dirigido a usuarios de Unreal que trabajan en escenas pesadas: mundos extensos, mapas con entornos densos, escenas cargadas de Lumen, niveles con niebla abundante, vegetación densa o proyectos donde el viewport del editor se vuelve lento.

## Funciones y comportamiento

### ¿Qué puede cambiar el plugin cuando está activado?

Según el perfil seleccionado, puede:

- Reducir el porcentaje de pantalla del viewport del editor.
- Reducir la calidad de escalabilidad general.
- Desactivar la iluminación indirecta difusa Lumen.
- Desactivar los reflejos Lumen.
- Desactivar los mapas de sombras virtuales.
- Desactivar la niebla volumétrica y la niebla estándar.
- Forzar los viewports del editor al modo Unlit.
- Desactivar el renderizado en tiempo real en los viewports del editor.

### ¿Por qué el viewport se ve peor mientras está activado?

Es lo esperado. El plugin intercambia fidelidad visual por fluidez en el editor. Utilícelo mientras edita el diseño, la estructura, la colocación o la lógica de Blueprints. Desactívelo para la iluminación final, materiales, capturas de pantalla, secuencias de vídeo o aprobaciones visuales.

### ¿Por qué el viewport pasa a modo Unlit?

Algunos perfiles fuerzan Unlit porque la iluminación puede ser uno de los costes más elevados del viewport del editor. Puede editar cualquier perfil y desactivar bForceUnlitViewports si necesita mantener el contexto de iluminación.

### ¿Por qué se desactiva el tiempo real?

Algunos perfiles desactivan el tiempo real para que los viewports dejen de redibujarse continuamente. Esto ayuda en escenas pesadas o portátiles. Puede desactivar este comportamiento en cada perfil.

### ¿Desactiva Nanite?

No. El plugin no desactiva Nanite directamente. Se centra en el porcentaje de pantalla del viewport del editor, la escalabilidad, Lumen, sombras virtuales, niebla, modo de visualización y tiempo real.

### ¿Sustituye la configuración de escalabilidad de Unreal?

No. Utiliza la escalabilidad como parte de un flujo de trabajo más amplio en el editor. La escalabilidad de Unreal por sí sola no cubre todos los costes del viewport, por lo que el plugin también controla el porcentaje de pantalla, ciertas CVars del renderer, el modo de visualización y el tiempo real.

## Perfiles

### ¿Qué perfiles se incluyen?

El plugin incluye cuatro perfiles editables:

- Mild
- Balanced
- Aggressive
- Extreme

Balanced es el punto de partida recomendado.

### ¿Puedo personalizar los perfiles?

Sí. Abra Project Settings > Plugins > Lightweight Editor Mode. Cada perfil tiene su propia calidad, porcentaje de pantalla y opciones de comportamiento.

### ¿Puedo cambiar de perfil con el modo activado?

Sí. El plugin actualiza los ajustes activos de inmediato y conserva las copias de seguridad originales hechas antes de activar el modo. Al desactivar, se restaurará el estado previo a la activación inicial.

### ¿Qué perfil debo utilizar?

Utilice Mild cuando aún necesite contexto visual. Utilice Balanced para la edición general. Utilice Aggressive para el trabajo con vegetación, escenarios o terrenos pesados. Utilice Extreme cuando necesite máxima fluidez y la calidad visual no importe.

## Restauración y seguridad

### ¿Qué se restaura cuando desactivo el modo?

Durante la misma sesión del editor, el plugin restaura:

- Niveles de calidad de escalabilidad guardados.
- Valores de CVars guardados.
- Modos de visualización modificados por el plugin.
- Estados de tiempo real modificados por el plugin.

### ¿Qué ocurre si el editor se cierra mientras el modo está activado?

El cierre normal del módulo intenta desactivar el modo. Si el editor se bloquea o se cierra de forma inesperada, las copias de seguridad en memoria se pierden. El plugin almacena un modo de visualización alternativo para evitar quedarse atascado en Unlit tras reiniciar, pero no puede reconstruir cada valor tras un cierre imprevisto.

### ¿Qué ocurre si los viewports permanecen en Unlit tras reiniciar?

Abra la ventana de Lightweight Editor Mode y haga clic en Disable Lightweight Mode. Si la copia de seguridad de la sesión no está disponible, el plugin usa el modo alternativo guardado para devolver los viewports Unlit a un modo normal. Si es necesario, también puede cambiar manualmente el viewport a Lit desde su menú.

### ¿Puede otro plugin anular las mismas CVars?

Sí. Las CVars de Unreal se pueden modificar desde la configuración del proyecto, la línea de comandos, perfiles de dispositivos, escalabilidad, plugins y código del editor. Lightweight Editor Mode escribe las CVars con prioridad de plugin y restaura sus copias de seguridad, pero una escritura posterior por otro sistema prevalecerá.

### ¿Por qué las CVars no encontradas no se tratan como errores?

Las funciones del renderer varían según la versión del motor, configuración del proyecto, plataforma y ramas personalizadas. Si una CVar no existe, el plugin la omite y registra la situación en lugar de hacer fallar el modo por completo.

## Compatibilidad

### ¿Qué versión de Unreal Engine es compatible?

La implementación está orientada a las API del editor y CVars del renderer de Unreal Engine 5.4. Valide cada versión del motor que pretenda ofrecer como compatible, especialmente versiones más recientes donde las CVars pueden cambiar.

### ¿Funciona con ramas personalizadas del motor?

Debería funcionar siempre que existan las API del editor y las CVars requeridas. Si una rama personalizada renombra o elimina CVars del renderer, esas opciones específicas se omitirán. Consulte el Output Log para ver los detalles.

### ¿Funciona en Windows, Linux y Mac?

El plugin contiene solo código fuente C++ para el editor y evita código de tiempo de ejecución específico de plataforma. Cada plataforma objetivo del editor debe compilarse y probarse antes de ofrecer soporte oficial.

### ¿Funciona en commandlets?

No se ofrece ningún flujo de trabajo para commandlets. El comportamiento principal depende de los clientes interactivos de viewport del editor, la interfaz Slate y el estado de la sesión.

## Flujo de trabajo

### ¿Cómo lo abro?

Utilice Tools > Performance > Lightweight Editor Mode en el editor de Unreal.

### ¿Cómo lo activo automáticamente?

Marque Enable on Editor startup en la ventana del plugin. El plugin esperará a que existan los viewports del editor y luego aplicará el perfil actual.

### ¿Por qué la activación al inicio espera antes de aplicarse?

Durante el inicio temprano del módulo, es posible que Unreal aún no haya creado los clientes de viewport del editor. El plugin usa un temporizador corto y activa el modo una vez que los viewports están disponibles para capturar y modificar su estado con fiabilidad.

### ¿Debo dejarlo activado todo el día?

Puede hacerlo, pero el mejor hábito es activarlo para obtener fluidez y desactivarlo antes de tomar decisiones visuales. No evalúe iluminación final, sombras, niebla, materiales o capturas de pantalla mientras el modo esté activo.

### ¿Ayuda si mi cuello de botella es la compilación de shaders o el control de código fuente?

No. El plugin se enfoca únicamente en el coste de renderizado del viewport del editor. No resolverá la compilación de shaders, la carga de assets, retrasos del control de versiones, discos lentos, análisis de antivirus ni herramientas personalizadas pesadas.

## Soporte técnico

### ¿Qué debo incluir en una solicitud de soporte?

Incluya:

- Versión de Unreal Engine.
- Sistema operativo.
- Si el motor es estándar o personalizado.
- Perfil seleccionado.
- Si el problema ocurrió al activar, cambiar de perfil, desactivar, iniciar o tras reiniciar.
- Líneas del Output Log que contengan "[Lightweight]".
- Cualquier otro plugin o script que modifique CVars del renderer.

### ¿Dónde puedo comprobar lo que hizo el plugin?

Abra el Output Log de Unreal y busque:

- [Lightweight]
- Backup CVar
- Restore CVar
- ApplyActiveSettings
- ApplyViewportSettings
- Lightweight mode ENABLED
- Lightweight mode DISABLED

### ¿Cuál es la regla de uso más importante?

Utilice Lightweight Editor Mode para velocidad de edición. Desactívelo para la verdad visual.

<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/LogLevelEditor/architecture.md -->
# Preguntas frecuentes (FAQ)

## ¿Cambia LogLevelEditor mis declaraciones de categorías C++?

No. No reescribe código fuente. Descubre categorías y utiliza el sistema de comandos de consola de Unreal para cambiar el nivel de detalle activo.

## ¿Son permanentes los cambios?

Solo son permanentes las modificaciones intencionadas guardadas en el `ULogLevelDataAsset` configurado. Los cambios en la consola en tiempo de ejecución sin actualizar el DataAsset son temporales.

## ¿Por qué desapareció una categoría de la lista?

Puede estar oculta por la lista de ocultación permanente, por la lista temporal, filtrada por texto de búsqueda o excluida del alcance de escaneo actual.

## ¿Por qué falta un nivel predeterminado?

El escáner reconoce macros comunes de Unreal. Si un proyecto utiliza macros personalizadas o formatos inusuales, la categoría se encontrará pero no se podrá deducir su nivel predeterminado.

## ¿Puedo incluir categorías de registro del motor?

Sí. Active el escaneo de plugins y/o código fuente del motor en la configuración.

## ¿Funciona esto en juegos empaquetados?

No. LogLevelEditor es un plugin del editor para flujos de trabajo de desarrollo.

## ¿Puedo compartir una configuración de registro con mi equipo?

Sí. Guarde las modificaciones en el DataAsset y manténgalo en el control de versiones con su proyecto.

## ¿Por qué el plugin reintenta aplicar los niveles guardados en el inicio?

Los módulos del editor de Unreal pueden iniciarse antes de que el motor esté listo para procesar comandos de consola. La lógica de reintento evita perder modificaciones guardadas.

## ¿Qué ocurre si un comando de consola falla?

La interfaz y el DataAsset no se actualizan como si el comando hubiera tenido éxito. El fallo queda registrado.

## ¿Puedo silenciar una categoría por completo?

Utilice `NoLogging`, pero recuerde que las reglas de nivel de detalle en tiempo de compilación y en tiempo de ejecución de Unreal se siguen aplicando.

## ¿Admite nombres de nivel de detalle personalizados?

No. Soporta los nombres de nivel de detalle estándar de Unreal.

## ¿Es obligatorio el DataAsset?

La interfaz puede inspeccionar y aplicar cambios en tiempo de ejecución, pero la reaplicación persistente en el inicio requiere un DataAsset configurado.

## ¿Puede el plugin detectar categorías de otros plugins?

Sí. Los plugins del proyecto forman parte de la ruta de escaneo normal. Los plugins del motor son opcionales.

## ¿Es seguro para el control de código fuente?

Sí, cuando se utiliza intencionadamente. El elemento compartido principal es el DataAsset con modificaciones persistentes.

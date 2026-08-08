# Manual del usuario

Editor Extension Base empaqueta primitivas de interfaz de usuario del Editor de Unreal y bibliotecas auxiliares para que los plugins de características puedan mantener un comportamiento consistente en la selección, comprobación, guardado y deshacer.

## Público objetivo

- Autores de plugins que crean Editor Utility Widgets o herramientas del editor.
- Equipos que estandarizan la experiencia de usuario del editor en Tiny Tool Development sin copiar la estructura básica de los widgets.

Este plugin **no** es una herramienta para el usuario final con su propia entrada de menú de Tiny Tools.

## Módulos

| Módulo | Carga | Contenido |
| --- | --- | --- |
| `EditorExtensionBase` | Editor / Predeterminado | Widgets, `UEditorManagerUtilityLibrary`, utilidades de deshacer / acción de activos. |
| `EditorExtensionRuntimeBase` | Runtime / Predeterminado | Macros compartidas (`UsefulMacros.h`) y punto de entrada del módulo. |

## Widgets compartidos

<!-- image slot: eeb-widget-overview -->

| Clase | Propósito |
| --- | --- |
| `UEditorToolHeaderWidget` | Fila de encabezado con ranuras BindWidget de título/subtítulo y texto de visualización editable. |
| `UEditorUtilityButtonWidget` | Botón con estilo que incluye BindWidgets de bloque de texto y delegado de clic. |
| `UEditorUtilityTabButtonWidget` | Botón de estilo pestaña con ranuras de icono seleccionado/no seleccionado. |
| `UTwoPaneUserWidget` | Contenedor de diseño de dos paneles para pantallas de Editor Utility Widget. |

Las subclases de Blueprint de Widget deben vincular las ranuras BindWidget declaradas; las vinculaciones faltantes registran advertencias en `LogEditorExtensionBase`.

## Biblioteca de utilidades del Editor Manager

`UEditorManagerUtilityLibrary` extiende `UEditorUtilityLibrary` con auxiliares de selección y persistencia:

| Función | Comportamiento |
| --- | --- |
| `GetSelectedAssetsForAction` | Devuelve la selección actual, opcionalmente anclada por un objeto principal. |
| `CheckoutAndSaveAssets` | Intenta la comprobación y el guardado del control de versiones; informa el éxito mediante parámetros de salida. |
| `GetEditorWorld` | Devuelve el mundo del editor actual cuando está disponible. |
| `BeginTransactionAndGetSelectedAssets` | **Obsoleto en 5.4** — los llamadores deben gestionar `FScopedTransaction` por sí mismos. |

## Deshacer y acciones de activos

| Clase | Comportamiento |
| --- | --- |
| `UEditorUtilityTask_PrepareUndo` | Tarea de Editor Utility Widget que prepara las opciones de deshacer para los activos transaccionales seleccionados; omite objetos nulos, inválidos o no transaccionales con advertencias. |
| `UUndoableAssetActionUtility` | Codifica los resultados de acciones de activos deshacibles, incluyendo `SucceededWithCheckoutWarning` cuando las advertencias de comprobación acompañan al éxito. |

## Reglas de diseño

1. Mantenga la lógica empresarial específica de la característica en el plugin consumidor.
2. No trate este plugin como un requisito de configuración para plugins de escenas o IA no relacionados.
3. Prefiera las transacciones gestionadas por el llamador sobre el auxiliar de inicio de transacción obsoleto.

## Integraciones opcionales

Los plugins del editor de Tiny Tool que consumen pueden depender de Editor Extension Base para la coherencia de la interfaz de usuario. Estas integraciones son responsabilidad del consumidor; este paquete se degrada a "auxiliares no disponibles" únicamente cuando no está habilitado; no sustituye el comportamiento de otros plugins.

## Documentos relacionados

- [QUICKSTART.md](QUICKSTART.md)
- [SettingsReference.md](SettingsReference.md)
- [FAQ.md](FAQ.md)
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md)

# Preguntas frecuentes

## ¿Para qué sirve Editor Extension Base?

Es una base compartida para plugins de interfaz de usuario del editor de Tiny Tool Development: widgets de utilidad del editor reutilizables, ayudantes de selección / confirmación / guardado, utilidades de preparación para deshacer y un módulo ligero de macros en tiempo de ejecución.

## ¿Es una herramienta para el usuario final?

No. No registra un menú de productos Tiny Tools propio. Los plugins de características lo consumen como dependencia.

## ¿Qué módulos de Unreal carga?

`EditorExtensionBase` (Editor) y `EditorExtensionRuntimeBase` (Runtime), según se declara en `EditorExtensionBase.uplugin`.

## ¿Requiere otros plugins de Tiny Tool?

No. Requiere el plugin **Editor Scripting Utilities** de Unreal (habilitado en el descriptor). Los plugins de escena, IA u otros plugins de Tiny Tool son consumidores opcionales, no requisitos de configuración.

## ¿Cómo leo la selección actual del Content Browser?

Llama a `UEditorManagerUtilityLibrary::GetSelectedAssetsForAction` desde Blueprint o C++ después de habilitar el plugin. Consulta [QUICKSTART.md](QUICKSTART.md).

## ¿Cómo debo abrir una transacción de deshacer?

Debes tener una `FScopedTransaction` en el llamador. `BeginTransactionAndGetSelectedAssets` está obsoleto desde Unreal Engine 5.4.

## ¿Por qué mis Blueprints de widget generan advertencias en tiempo de ejecución?

Los slots vinculados con BindWidget, como botones, bloques de texto o iconos, son nulos. Asegúrate de que el Blueprint del Widget de utilidad vincule cada slot requerido declarado en la clase base de C++.

## ¿CheckoutAndSaveAssets siempre tiene éxito?

No. Informa los resultados de la confirmación y el guardado a través de parámetros de salida booleanos. Las fallas de control de versiones o de guardado se reflejan allí y en códigos de resultado relacionados como `SucceededWithCheckoutWarning`.

## ¿Hay DeveloperSettings a nivel de proyecto?

No. Los campos configurables residen en los widgets y utilidades compartidos. Consulta [SettingsReference.md](SettingsReference.md).

## ¿Incluye el paquete software de terceros?

No. Consulta [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md).

## ¿Qué versiones del motor son compatibles?

El descriptor empaquetado apunta a Unreal Engine 5.4.0 en Win64, Linux y Mac para la lista permitida del módulo del editor.

## ¿Dónde obtengo soporte?

Utiliza `mailto:support@tiny-tool-development.com` (descriptor `SupportURL`) o el enlace de soporte en la página del producto de Fab.

## ¿Puedo usar solo las macros de tiempo de ejecución sin el módulo del editor?

Sí. `EditorExtensionRuntimeBase` es un módulo de tiempo de ejecución separado diseñado para mantenerse ligero en dependencias para consumidores que no sean del editor.

## ¿ModifyAssets inmediatamente PrepareUndo?

Prepara las opciones de deshacer para los assets transaccionales seleccionados y omite las selecciones no válidas con advertencias. La persistencia aún se realiza a través de los ayudantes de confirmación/guardado cuando escribes intencionalmente.

## ¿Pueden las macros de tiempo de ejecución extraer módulos solo del editor?

No. Mantén `EditorExtensionRuntimeBase` ligero en dependencias. Los widgets del editor y los ayudantes de selección permanecen en el módulo del Editor.

---
lang: es
title: EditorExtensionBase Quick Start
audience: [end_user]
owner_ref: plugin:EditorExtensionBase
applies_to:
  component: EditorExtensionBase
preconditions:
  - Unreal Engine project open with the plugin package available
  - Edit > Plugins can enable EditorExtensionBase
expected_result:
  text: GetSelectedAssetsForAction returns the current Content Browser selection after the plugin is enabled.
version:
  since: "1.0"
---
# Inicio rápido

Esta guía te lleva desde la instalación hasta un **primer uso real**: habilitar Editor Extension Base y llamar a un editor compartido desde una utilidad de Blueprint o una herramienta de editor en C++. Editor Extension Base es una capa de soporte para otros plugins de editor; no es un producto independiente del menú Tiny Tools.

## Lo que tendrás después de esta guía

El plugin habilitado y una llamada exitosa a `UEditorManagerUtilityLibrary::GetSelectedAssetsForAction` (o su equivalente callable desde Blueprint) que devuelve la selección actual del Content Browser.

## Requisitos

- Unreal Engine 5.4 o posterior (descriptor `EngineVersion` 5.4.0).
- Editor Scripting Utilities habilitado (dependencia declarada en `EditorExtensionBase.uplugin`).
- Sin software de terceros, cuenta ni runtime externo. Consulta [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md).

## 1. Instalar y habilitar

1. Añade **EditorExtensionBase** desde tu biblioteca de Fab al proyecto (o instálalo bajo el directorio Plugins del motor).
2. Abre **Edit → Plugins**, habilita **EditorExtensionBase** y reinicia cuando se te solicite.
3. Confirma que **Editor Scripting Utilities** siga habilitado.

## 2. Verificar que los módulos se hayan cargado

Tras el reinicio, el paquete expone dos módulos:

| Módulo | Tipo | Función |
| --- | --- | --- |
| `EditorExtensionBase` | Editor | Widgets, ayudantes de selección, utilidades de deshacer. |
| `EditorExtensionRuntimeBase` | Runtime | Macros ligeras seguras para consumidores que no sean de editor. |

## 3. Ejemplo práctico: leer la selección actual

1. Selecciona uno o más activos en el Content Browser.
2. Desde un Editor Utility Widget o una herramienta de editor en C++ que dependa de este plugin, llama a:

```cpp
TArray<UObject*> Selected = UEditorManagerUtilityLibrary::GetSelectedAssetsForAction(nullptr);
```

3. Guarda o actúa sobre los objetos devueltos con `CheckoutAndSaveAssets` cuando escribas intencionalmente:

```cpp
bool bCheckoutOk = false;
bool bSaveOk = false;
const bool bOk = UEditorManagerUtilityLibrary::CheckoutAndSaveAssets(
	Selected, bCheckoutOk, bSaveOk);
```

## Resultado esperado

- `Selected` contiene la selección del Content Browser (o está vacío cuando no hay nada seleccionado).
- Al llamar a `CheckoutAndSaveAssets`, los parámetros de salida booleanos informan de los resultados de checkout y guardado sin inventar una transacción por ti; el llamante es responsable del ámbito de `FScopedTransaction`.

## Próximos pasos

- Lee [UserManual.md](UserManual.md) para el catálogo de widgets y utilidades.
- Lee [SettingsReference.md](SettingsReference.md) para las propiedades editables en los widgets compartidos.
- Usa [TROUBLESHOOTING.md](TROUBLESHOOTING.md) cuando los BindWidget slots o los ayudantes de selección generen advertencias en el registro.

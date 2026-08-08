---
lang: es
title: EditorExtensionBase Settings Reference
audience: [end_user]
owner_ref: plugin:EditorExtensionBase
applies_to:
  component: EditorExtensionBase
contract_ref: plugin:EditorExtensionBase/widget-properties
version:
  since: "1.0"
---
# Referencia de configuración

EditorExtensionBase **no** incluye una clase `UDeveloperSettings` ni un objeto de configuración `.ini` del proyecto. Los valores configurables se encuentran en las subclases del Editor Utility Widget compartidas y en los objetos de utilidad como campos `UPROPERTY`.

## UEditorToolHeaderWidget

| Nombre | Tipo | Predeterminado | Efecto |
| --- | --- | --- | --- |
| `TitleText` | `FText` | predeterminado del widget | Título visible en la cabecera. |
| `SubtitleText` | `FText` | predeterminado del widget | Línea secundaria debajo del título. |
| Bloques de título / subtítulo (BindWidget) | referencias de widget | deben estar vinculados | Ranuras Slate/UMG requeridas; las vinculaciones faltantes generan advertencias en tiempo de ejecución. |

## UEditorUtilityButtonWidget

| Nombre | Tipo | Predeterminado | Efecto |
| --- | --- | --- | --- |
| Propiedades de estilo del botón | campos de estilo en el widget | establecidos por el diseñador | Estilo visual para el botón compartido. |
| Botón / bloque de texto (BindWidget) | referencias de widget | deben estar vinculados | Objetivo del clic y etiqueta; un botón o texto nulo genera un registro de advertencia. |

## UEditorUtilityTabButtonWidget

| Nombre | Tipo | Predeterminado | Efecto |
| --- | --- | --- | --- |
| Presentación seleccionada / no seleccionada | campos de estado + icono | establecidos por el diseñador | Controla la apariencia de la pestaña seleccionada. |
| Ranuras de botón / icono (BindWidget) | referencias de widget | deben estar vinculados | Las faltas de iconos seleccionados/no seleccionados generan advertencias. |

## UUndoableAssetActionUtility

| Nombre | Tipo | Predeterminado | Efecto |
| --- | --- | --- | --- |
| Campos de descripción de acción / activos | campos de utilidad editanywhere | establecidos por el llamador | Describe la acción de activo deshacible que ejecuta la utilidad. |
| Código de resultado | enumeración | tiempo de ejecución | Incluye `SucceededWithCheckoutWarning` cuando las advertencias de checkout acompañan al éxito. |

## UEditorUtilityTask_PrepareUndo

| Nombre | Tipo | Predeterminado | Efecto |
| --- | --- | --- | --- |
| Entradas de activos seleccionados | campos de utilidad editanywhere | establecidos por el llamador | Activos considerados para la preparación del deshacer; los activos nulos, no válidos o no transaccionales se omiten con advertencias. |

## Lo que no está presente

| Superficie esperada | Estado |
| --- | --- |
| `UEditorExtensionBaseSettings` DeveloperSettings | aún no disponible en el código fuente |
| `Config/DefaultEditorExtensionBase.ini` | no incluido |
| Panel de Preferencias del proyecto | aún no disponible |

## Documentos relacionados

- [UserManual.md](UserManual.md) — catálogo de comportamiento.
- [QUICKSTART.md](QUICKSTART.md) — primera llamada al helper de selección.
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md) — advertencias de BindWidget y selección.

# Documentación base de la extensión del editor

Editor Extension Base es una base compartida del Editor de Unreal para plugins de interfaz de usuario de Tiny Tool Development. Incluye widgets de utilidad del editor reutilizables, selectores de selección / verificación / guardado del Content Browser, utilidades de preparación para deshacer y un módulo ligero de macros en tiempo de ejecución.

Público objetivo: autores de plugins y equipos que necesitan una experiencia de usuario (UX) consistente en el editor sin copiar la estructura repetitiva de widgets y selección. Este paquete es una capa de soporte; no registra su propio menú de productos de Tiny Tools.

## Características

- Widgets de utilidad del editor compartidos (encabezado, botón, botón de pestaña, diseño de dos paneles).
- `UEditorManagerUtilityLibrary` para selección, verificación/guardado y utilidades del mundo del editor.
- Utilidades de preparación para deshacer y acciones de activos deshacibles.
- Módulo en tiempo de ejecución (`EditorExtensionRuntimeBase`) con macros compartidas para consumidores que no son del editor.

## Primeros pasos

1. Habilita el plugin (y las Utilidades de scripting del editor) — consulta [QUICKSTART.md](QUICKSTART.md).
2. Llama a `GetSelectedAssetsForAction` desde una utilidad del editor o una herramienta de editor en C++.
3. Lee [UserManual.md](UserManual.md) y [SettingsReference.md](SettingsReference.md) para ver el catálogo completo.

## Archivos relacionados

- [../README.md](../README.md) — descripción general del producto.
- [../CHANGELOG.md](../CHANGELOG.md) — historial de versiones.
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md) · [FAQ.md](FAQ.md) · [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md)

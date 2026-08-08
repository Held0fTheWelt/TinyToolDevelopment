---
lang: es
title: EditorExtensionBase Third-Party Software
audience: [end_user]
owner_ref: plugin:EditorExtensionBase
applies_to:
  component: EditorExtensionBase
contract_ref: plugin:EditorExtensionBase/third-party-software
version:
  since: "1.0"
---
# Software de terceros

Editor Extension Base **no incluye código fuente de terceros, binarios de tiempo de ejecución, modelos de IA, Node.js, Python ni ejecutables independientes**. Es un complemento de Unreal Engine escrito en C++ basado en módulos del Editor de Unreal y en las Utilidades de scripting del editor.

## Método de medición

Se buscó en `GovernanceDevelopmentPlugins/EditorExtensionBase` los términos `ThirdParty`, `LICENSE-` y marcadores de derechos de autor. Los encabezados de los archivos identifican la EULA de Tiny Tool Development / Fab. No se encuentra ningún árbol de dependencias de terceros integrado.

## Dependencias del motor (no incluidas)

| Dependencia | ¿Incluida? | Notas |
| --- | --- | --- |
| Módulos del Editor de Unreal Engine | No | Proporcionados por la instalación del motor. |
| Utilidades de scripting del editor | No | Habilitadas mediante la entrada `Plugins` del archivo `.uplugin`; es un complemento propiedad de Epic. |

## Integraciones opcionales

Los complementos de características pueden depender de Editor Extension Base para compartir widgets. Estos consumidores son paquetes separados y no se redistribuyen aquí.

**Declaración de software de terceros de Fab:** ninguna.

## Documentos relacionados

- [README.md](README.md)
- [QUICKSTART.md](QUICKSTART.md)
- [FAQ.md](FAQ.md)

## Encabezados de derechos de autor

Las fuentes del editor y del tiempo de ejecución utilizan los encabezados de la EULA estándar de Tiny Tool Development / Fab. No se encontraron archivos de licencia adicionales dentro de un directorio `ThirdParty`.

## Lista de verificación de la declaración del comprador

1. Declarar **ningún** software de terceros integrado para Fab.
2. Las Utilidades de scripting del editor siguen siendo una dependencia del complemento del motor de Epic, no un árbol de dependencias de terceros integrado.
3. Volver a ejecutar la búsqueda tras cualquier cambio futuro de integración antes de actualizar este archivo.

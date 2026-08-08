---
lang: es
title: GameFeaturedClasses Quick Start
audience: [end_user]
owner_ref: plugin:GameFeaturedClasses
applies_to:
  component: GameFeaturedClasses
preconditions:
  - Unreal Engine project open with the plugin package available
  - Edit > Plugins can enable GameFeaturedClasses
expected_result:
  text: GameFeaturedClasses runtime module is enabled and loads after editor restart.
version:
  since: "1.0"
---
# Inicio rápido

Esta guía instala y habilita **GameFeaturedClasses** y verifica que el módulo de tiempo de ejecución se cargue. La versión `1.0.1` es un **esqueleto de módulo**: incluye el descriptor, los metadatos de empaquetado, el icono y el registro de cambios. Aún **no** incluye clases de juego, acciones de Game Feature ni un banco de trabajo del editor.

## Qué tendrás después de seguir esta guía

El plugin habilitado en tu proyecto, con el módulo de tiempo de ejecución `GameFeaturedClasses` presente en la lista de módulos tras reiniciar el editor.

## Requisitos

- Unreal Engine 5.4–5.8 (matriz de versiones empaquetadas).
- No se requiere ningún otro plugin de Tiny Tool para el esqueleto.
- No se necesita software de terceros, cuenta ni tiempo de ejecución externo. Consulta [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md).

## 1. Instalar y habilitar

1. Obtén **GameFeaturedClasses** de Fab y añádelo al proyecto (o instálalo en el directorio Plugins del motor).
2. Abre **Editar → Plugins**, busca **GameFeaturedClasses**, habilítalo y reinicia cuando se te solicite.

## 2. Confirmar el límite del módulo

Tras el reinicio, verifica que el módulo de tiempo de ejecución se haya cargado (Registro de salida / administrador de módulos). La interfaz pública del módulo es `FGameFeaturedClassesModule` en `Source/GameFeaturedClasses/Public/GameFeaturedClasses.h`, con únicamente `StartupModule` / `ShutdownModule`.

## 3. Ejemplo práctico: verificación básica del esqueleto

1. Crea o abre un proyecto en Unreal Engine 5.4 o posterior.
2. Habilita el plugin como se indica arriba y reinicia.
3. En el Registro de salida, filtra el ruido de inicio de módulo para `GameFeaturedClasses` tras la carga.

No hay interfaz de usuario para el registro de clases destacadas ni ninguna acción de Game Feature de ejemplo que ejecutar en esta versión del paquete. Se espera que las llamadas a menús del banco de trabajo inexistentes fallen, ya que esas superficies **aún no están disponibles**.

## Resultado esperado

- El plugin aparece como habilitado bajo **Editar → Plugins**.
- El módulo de tiempo de ejecución se inicia y se detiene sin requerir plugins peer de Tiny Tool.
- No aparecen activos de clases destacadas de juego en el Content Browser de este paquete (no se incluyen).

## Próximos pasos

- Lee [UserManual.md](UserManual.md) para conocer el límite actual frente al objetivo.
- Lee [FAQ.md](FAQ.md) para resolver dudas sobre el alcance.
- Considera el comportamiento del banco de trabajo GameFeature premium como la arquitectura objetivo hasta que una versión posterior incluya esas clases y superficies del editor.

## Límites a tener en cuenta

- No añadas clases de juego del proyecto a esta carpeta del plugin esperando que se distribuyan como contenido GFC en 1.0.1.
- No habilites plugins peer únicamente para “desbloquear” un banco de trabajo que aún no está empaquetado.
- Cuando una versión posterior incluya clases destacadas, actualiza este inicio rápido con los nombres reales de las clases y un ejemplo práctico de esa versión.

<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/CodeCopyrightEditor/architecture.md -->
# Preguntas frecuentes (FAQ)

## ¿Para qué se utiliza Code Copyright Editor?

Code Copyright Editor ayuda a los desarrolladores de Unreal Engine a mantener avisos de derechos de autor coherentes en Project Settings y en los archivos fuente. Puede escanear, previsualizar, actualizar e informar sobre los encabezados de archivos fuente desde un único flujo de trabajo del editor.

## ¿Afecta el plugin al código del juego en tiempo de ejecución?

No. Code Copyright Editor es una herramienta de uso exclusivo en el editor. Está concebida para flujos de trabajo de desarrollo, revisión, documentación y CI.

## ¿Puede actualizar automáticamente todo un código base?

Sí, pero solo tras el escaneo y la revisión. El editor muestra qué archivos se pueden cambiar, cuáles están protegidos y cómo quedará el reemplazo propuesto antes de aplicar los cambios.

## ¿Protege los avisos de terceros o de Epic?

Sí. El escáner está diseñado para proteger avisos externos, de Epic y de terceros frente a reescrituras automáticas. Los archivos protegidos y en conflicto se deben revisar manualmente.

## ¿Puedo personalizar la plantilla de derechos de autor?

Sí. Puede editar la plantilla de avisos para archivos fuente y la plantilla de avisos para Project Settings. Tokens como nombre de producto, ruta de archivo, año, identificador de licencia y descripción por archivo se pueden incluir automáticamente.

## ¿Admite flujos de trabajo SPDX o REUSE?

El plugin proporciona plantillas e informes orientados a REUSE/SPDX. Estos informes están destinados a respaldar flujos de trabajo de revisión y CI, pero no constituyen certificación legal.

## ¿Existe un commandlet para CI?

Sí. El commandlet `CodeCopyrightCheck` incluido puede escanear el proyecto, corregir opcionalmente los archivos modificables, escribir informes y hacer fallar la CI cuando los avisos de derechos de autor no estén sincronizados.

## ¿Sustituye al asesoramiento legal?

No. Ayuda a aplicar y revisar el texto de los avisos de forma coherente. No decide sobre la titularidad legal, no valida licencias de terceros ni proporciona asesoramiento legal.

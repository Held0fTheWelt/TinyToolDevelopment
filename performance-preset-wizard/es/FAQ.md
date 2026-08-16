<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/PerformancePresetWizard/architecture.md -->
# Preguntas frecuentes (FAQ)

## ¿Es Performance Preset Wizard un optimizador automático?

No. Es una herramienta de creación y aplicación de preajustes. No realiza pruebas de rendimiento del hardware.

## ¿Funciona en tiempo de ejecución?

Sí, los juegos empaquetados pueden aplicar manualmente los preajustes mediante `UPerformancePresetRuntimeSubsystem`, Blueprint, C++ o el widget UMG incluido.

## ¿La aplicación de un preajuste guarda los ajustes del proyecto?

No. Modifica el estado actual del motor/tiempo de ejecución mediante las API de escalabilidad y CVar.

## ¿Puedo deshacer una aplicación?

En el asistente del editor, utilice **Restore Previous**. En tiempo de ejecución, utilice `RestoreLatestBackup` o `RestoreBackupById`.

## ¿Qué ocurre si una CVar no existe?

El plugin la notifica como no encontrada y continúa aplicando el resto del preajuste.

## ¿Por qué los valores de CVar se guardan como cadenas de texto?

Las CVar pueden ser enteros, flotantes, booleanos o texto. Una cadena de texto cubre todos estos casos.

## ¿Qué significa "Editor Only"?

Una modificación reservada al editor solo se aplica en el contexto del editor y se ignora en juegos empaquetados.

## ¿El plugin reemplaza a los Device Profiles?

No. Los Device Profiles siguen siendo el lugar adecuado para las reglas relativas a las plataformas.

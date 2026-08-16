<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/PerformancePresetWizard/architecture.md -->
# Resolución de problemas

## El plugin no aparece en el menú Tools

Compruebe que el plugin está habilitado en **Edit > Plugins** y reinicie el editor.

## No aparece ningún preajuste en la lista

Utilice **Refresh** en el asistente. Compruebe que los assets son efectivamente DataAssets de tipo `UPerformancePresetAsset`.

## No se puede aplicar un preajuste

Asegúrese de seleccionar un preajuste. Si el asset fue eliminado o movido, actualice la lista.

## Algunas CVar se notifican como no encontradas

El nombre de la CVar no se pudo resolver en el gestor de consola de Unreal (error de escritura, plugin deshabilitado o versión de motor diferente). Las CVar no encontradas no impiden la aplicación del resto del preajuste.

## Las CVar se contabilizan como no válidas

Las entradas no válidas tienen un nombre o valor vacío. Corrija la línea en el editor en lote.

## "Restore Previous" no está disponible

La restauración solo está disponible tras haber aplicado un preajuste durante la sesión actual del editor.

## El preajuste al iniciar no se aplica

Compruebe que **Apply Preset On Editor Startup** está habilitado y que **Startup Preset** apunta a un asset válido.

<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/PerformancePresetWizard/architecture.md -->
# Manual del usuario

Este manual describe el flujo de trabajo normal en el editor para Performance Preset Wizard.

## Abrir el asistente

1. Habilite **Performance Preset Wizard** en **Edit > Plugins**.
2. Reinicie Unreal Editor si se le solicita.
3. Abra **Tools > Performance > Performance Preset Wizard**.

El asistente escanea el registro de assets en busca de assets `UPerformancePresetAsset` y muestra los preajustes detectados.

## Panel principal

El asistente consta de dos áreas principales:

- Lista de preajustes: todos los assets de preajustes de rendimiento detectados.
- Panel de detalles: nombre del preajuste seleccionado, descripción, niveles de escalabilidad, modificaciones de CVar, texto de estado y botones de acción.

Utilice **Refresh** cuando se hayan creado, renombrado, movido o importado nuevos preajustes.

## Seleccionar un preajuste

Haga clic en un preajuste de la lista para cargar su resumen.

## Aplicar un preajuste

1. Seleccione un preajuste.
2. Revise el resumen.
3. Haga clic en **Apply Preset**.

El orden de las operaciones es el siguiente:

1. Guardado de un punto de restauración.
2. Limitación de los valores de escalabilidad al rango `0..4` de Unreal.
3. Aplicación de la escalabilidad mediante `Scalability::SetQualityLevels`.
4. Procesamiento de modificaciones de CVar.
5. Omisión de entradas no válidas.
6. Omisión de entradas `editor-only` fuera del contexto del editor.
7. Informe en la zona de estado y notificaciones.

## Restaurar la configuración anterior

Haga clic en **Restore Previous** para regresar a la configuración guardada inmediatamente antes de la última aplicación con éxito.

La restauración incluye:

- La estructura completa de escalabilidad anterior a la aplicación.
- Los valores anteriores para las CVar específicas sobrescritas por el preajuste.

La aplicación de otro preajuste reemplaza el punto de restauración anterior.

## Preajuste al iniciar el editor

Abra **Edit > Project Settings > Plugins > Performance Preset Wizard**.

Ajustes disponibles:

- **Apply Preset On Editor Startup**: habilita o deshabilita la aplicación al iniciar.
- **Startup Preset**: referencia blanda (soft reference) al asset de preajuste que se aplicará tras la inicialización del editor.

## Preajustes en tiempo de ejecución

Los preajustes en tiempo de ejecución utilizan los mismos assets `UPerformancePresetAsset`. Los juegos empaquetados los aplican manualmente mediante `UPerformancePresetRuntimeSubsystem`.

Flujo Blueprint típico:

1. Obtener la `GameInstance` actual.
2. Obtener el `Performance Preset Runtime Subsystem`.
3. Pasar un asset de preajuste a `ApplyRuntimePreset`.
4. Llamar a `RestoreLatestBackup` en caso de cancelación.

## Widget selector en tiempo de ejecución

`UPerformancePresetRuntimeSelectorWidget` se incluye como punto de partida UMG. Puede listar los preajustes configurados, aplicar el preajuste seleccionado y restaurar la última copia de seguridad.

Los preajustes mostrados por el widget predeterminado se pueden configurar en **Project Settings > Plugins > Performance Preset Wizard Runtime**.

## Editor de CVar en lote

Utilice el editor de texto de CVar para copiar modificaciones desde notas o sesiones de consola.

Sintaxis admitida:

```text
# Las líneas de comentario están permitidas
r.ScreenPercentage=85
r.Nanite=1
r.Shadow.Virtual.Enable=1,editor
```

Utilice **Export** para escribir la matriz actual en el editor y **Apply** para procesar el texto de nuevo en el asset.

## Nombres recomendados

Utilice nombres explícitos:

- `Laptop Dev`
- `Desktop Mid Range 60 FPS`
- `Console Like Review`
- `VR Mobile Stable`
- `Cinematic Capture 4k`

## Mover o eliminar preajustes

Si el preajuste al iniciar deja de aplicarse, vuelva a seleccionar el asset en Project Settings y guarde la configuración.

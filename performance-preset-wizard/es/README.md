<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/PerformancePresetWizard/architecture.md -->
# Documentación de Performance Preset Wizard

Performance Preset Wizard crea preajustes (presets) de rendimiento objetivo en tiempo de ejecución, editados y revisados en Unreal Editor, y aplicados manualmente mediante el asistente del editor, C++, Blueprint o el widget selector de ejecución incluido. Un preajuste combina niveles de escalabilidad del motor con modificaciones de variables de consola (CVar) opcionales, permitiendo a los equipos cambiar rápidamente entre gamas de hardware, presupuestos para VR, configuraciones de captura, configuraciones de desarrollo en portátiles y objetivos de calidad específicos del proyecto.

Esta carpeta contiene la documentación completa suministrada con el plugin.

## Empieza aquí

- [BUYER_GUIDE.md](BUYER_GUIDE.md): resumen para compradores, valor incluido y flujos de trabajo de producción comunes.
- [UserManual.md](UserManual.md): flujo de trabajo completo en el editor para abrir el asistente, aplicar preajustes, restaurar configuraciones anteriores y configurar el preajuste al iniciar.
- [RuntimeUsage.md](RuntimeUsage.md): subsistema de ejecución, API de Blueprint, historial de copias de seguridad, proveedor de almacenamiento y widget selector.
- [FAQ.md](FAQ.md): respuestas prácticas para compradores de Fab, diseñadores y artistas técnicos.

## Referencia

- [PresetAuthoringGuide.md](PresetAuthoringGuide.md): cómo diseñar preajustes fiables, elegir niveles de escalabilidad y escribir modificaciones de CVar.
- [RuntimeUsage.md](RuntimeUsage.md): cómo los juegos empaquetados pueden aplicar y restaurar manualmente los preajustes.
- [SettingsReference.md](SettingsReference.md): cada ajuste del plugin y campo de asset con valores predeterminados y usos recomendados.
- [SamplePresetsReference.md](SamplePresetsReference.md): ejemplos de preajustes `DA_*` incluidos y cómo adaptarlos.
- [CodeDocumentation.md](CodeDocumentation.md): estructura del código fuente, contratos públicos, notas de implementación y puntos de extensión.
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md): problemas comunes de configuración, assets, CVar y compilación con sus soluciones.

## Recursos incluidos

- [Screenshots/](Screenshots): esquemas de documentación que muestran el flujo de trabajo del asistente, la creación de preajustes y el comportamiento de restauración e inicio.
- `../Content/DA_*.uasset`: assets de datos de muestra para escritorio, VR, estilo consola, prototipos móviles, desarrollo en portátiles y uso cinematográfico.
- `../PerformancePresetWizard_Changelog.txt`: notas de la versión incluidas con el plugin.

## Flujo de trabajo rápido en el editor

1. Habilite el plugin y reinicie el editor si Unreal lo solicita.
2. Abra **Tools > Performance > Performance Preset Wizard**.
3. Seleccione un preajuste de la lista. Utilice **Refresh** si se han creado o importado nuevos preajustes recientemente.
4. Revise el nombre visible, la descripción, la plataforma de destino, el resumen de escalabilidad y las modificaciones de CVar.
5. Haga clic en **Apply Preset**. El asistente aplica primero la escalabilidad y luego las modificaciones de CVar válidas.
6. Haga clic en **Restore Previous** para volver a la configuración guardada inmediatamente antes de la última aplicación.
7. Active **Apply on Editor Startup** en Project Settings si desea aplicar automáticamente un preajuste al abrir el editor.

## Flujo de trabajo rápido en tiempo de ejecución

1. Cree y revise los preajustes `UPerformancePresetAsset` en el editor.
2. Añada preajustes de ejecución en **Project Settings > Plugins > Performance Preset Wizard Runtime**, o páselos directamente al subsistema de ejecución.
3. En C++ o Blueprint, obtenga `UPerformancePresetRuntimeSubsystem` de la `GameInstance` actual.
4. Llame a `ApplyRuntimePreset` para una acción explícita del usuario o del proyecto.
5. Utilice `GetBackupHistory`, `RestoreLatestBackup` o `RestoreBackupById` cuando el proyecto necesite deshacer cambios.
6. Utilice `UPerformancePresetRuntimeSelectorWidget` como un widget UMG reemplazable para menús de prueba o pantallas de opciones.

## Formato rápido de CVar

El editor de CVar en lote acepta una modificación por línea:

```text
r.ScreenPercentage=85
r.Nanite=1
r.Lumen.Reflections.Allow=0
r.Shadow.Virtual.Enable=1,editor
```

Reglas:

- Las líneas vacías se ignoran.
- Las líneas que comienzan por `#` o `//` se tratan como comentarios.
- `Name=Value` crea una modificación normal.
- `Name=Value,editor` marca la modificación como solo para el editor (editor-only).
- Las CVar desconocidas se notifican pero no detienen la aplicación del preajuste.
- Los nombres o valores vacíos se ignoran.

## Niveles de escalabilidad

Performance Preset Wizard sigue la escala de calidad estándar de Unreal Engine:

- `0`: Low
- `1`: Medium
- `2`: High
- `3`: Epic
- `4`: Cinematic

El plugin gestiona las categorías de escalabilidad de UE5, incluyendo distancia de visión, anti-aliasing, sombras, iluminación global, reflexiones, postprocesado, texturas, efectos, follaje, sombreado y terreno.

## Notas importantes de alcance

Performance Preset Wizard no es un framework de pruebas de rendimiento (benchmarking), ni un detector de hardware, ni un optimizador automático, ni un reemplazo para los Device Profiles. Los preajustes deben probarse en el proyecto y la plataforma de destino antes de ser considerados predeterminados de producción.

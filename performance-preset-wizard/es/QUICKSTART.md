<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/PerformancePresetWizard/architecture.md -->
# Guía de inicio rápido

Esta guía le acompañará desde la instalación hasta un **resultado concreto**: un preajuste de rendimiento aplicado a su editor (escalabilidad + variables de consola) que puede restaurar completamente con un solo clic. Performance Preset Wizard funciona de forma autónoma.

## Lo que obtendrá tras esta guía

El asistente abierto con los preajustes detectados, un preajuste aplicado (niveles de escalabilidad + modificaciones de CVar) y la capacidad de restaurar sus ajustes anteriores.

## Requisitos

- Editor de Unreal Engine 5. La aplicación en juegos empaquetados es opcional.
- No se requiere software de terceros, cuentas ni entornos de ejecución adicionales. Consulte [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md).

## 1. Instalación y habilitación

1. Añada **Performance Preset Wizard** desde su biblioteca de Fab al proyecto (o instálelo en el motor).
2. Abra **Edit → Plugins**, habilite **Performance Preset Wizard** y reinicie cuando se le solicite.

## 2. Abrir el asistente

1. Abra **Tools → Performance → Performance Preset Wizard**.
2. El asistente escanea el registro de assets en busca de assets `UPerformancePresetAsset` y los enumera por nombre visible, plataforma de destino y ruta.
3. Haga clic en un preajuste para cargar su panel de detalles.

## 3. Un ejemplo práctico: aplicar y restaurar

1. Seleccione un preajuste de muestra incluido.
2. Haga clic en **Apply Preset**.

**Resultado esperado:** El asistente guarda un punto de restauración, limita la escalabilidad al rango `0..4` de Unreal y la aplica, y luego aplica cada modificación de CVar.

3. Haga clic en **Restore Previous**.

**Resultado esperado:** La estructura de escalabilidad y las CVar modificadas por el preajuste vuelven a los valores guardados inmediatamente antes de la aplicación.

## 4. Crear su propio preajuste

Abra cualquier `PerformancePresetAsset` en el Content Browser. El panel Details le ofrece menús desplegables por categoría y un **editor de CVar en lote**:

```text
# Las líneas de comentario están permitidas
r.ScreenPercentage=85
r.Nanite=1
r.Shadow.Virtual.Enable=1,editor
```

`,editor` marca una modificación como solo para el editor. Utilice **Export** para volcar la matriz en el editor de texto y **Apply** para procesarla de nuevo en el asset. Consulte [PresetAuthoringGuide.md](PresetAuthoringGuide.md).

## 5. Opcional: Uso al inicio y en tiempo de ejecución

- **Inicio del editor:** *Project Settings → Plugins → Performance Preset Wizard* → **Apply Preset On Editor Startup** + **Startup Preset**.
- **Juego empaquetado:** Aplique preajustes mediante `UPerformancePresetRuntimeSubsystem.ApplyRuntimePreset` y `RestoreLatestBackup`, o utilice el widget `UPerformancePresetRuntimeSelectorWidget`. Consulte [RuntimeUsage.md](RuntimeUsage.md).

## 6. Siguientes pasos

- Flujo de trabajo completo e historial de copias de seguridad: [UserManual.md](UserManual.md).
- Preajustes incluidos: [SamplePresetsReference.md](SamplePresetsReference.md).
- Ajustes: [SettingsReference.md](SettingsReference.md). Problemas: [TROUBLESHOOTING.md](TROUBLESHOOTING.md), [FAQ.md](FAQ.md).

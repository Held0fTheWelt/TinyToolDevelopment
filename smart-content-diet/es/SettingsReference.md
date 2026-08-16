<!-- doc-provenance: AKDB:plugins/SmartContentDiet/architecture.md; docs/architecture/plugins/SmartContentDiet/product-facts.yml; reconciled 2026-07-16 -->
# Referencia de configuración

## Rol / Audiencia

Se establece en **Configuración** o en el selector de audiencia del encabezado. Controla la profundidad de la explicación y la visibilidad de las pestañas:

- **Principiante**: Resumen, Optimizar, Hallazgos, Configuración.
- **Ingeniero / Productor (avanzado)**: agrega Preajuste y Gobernanza (Tendencia, Deuda, Presupuesto, Propiedad, Escaneo profundo); Redundancia aparece solo cuando hay un proveedor de similitud externo registrado.

## Profundidad de escaneo (encabezado)

| Profundidad | ¿Carga activos? | Notas |
| --- | --- | --- |
| `Quick Safe` (predeterminado) | No | Ruta de registro/metadatos; primer paso rápido. |
| `Full` | Sí | Canalización completa del analizador; hallazgos accionables de malla/textura/material. |
| `Deep` | Sí | Métricas profundas de material/malla estática; utiliza Gobernanza → Escaneo profundo; el más lento. |

La profundidad seleccionada se respeta en cada ejecución del analizador (editor y commandlet).

Quick Safe es la ruta basada primero en AssetRegistry: los escaneos amplios evitan la carga pesada de activos a menos que un candidato supere las comprobaciones de metadatos económicos. Full y Deep pueden cargar activos para obtener detalles del analizador accionables.

## Ubicaciones de salida

```text
Saved/SmartContentDiet/OptimizationQueue/<timestamp>/   ← informes de aplicación de la cola segura
```

## Aprobación / Seguridad

Las capacidades mutantes (`scd.optimize.apply_safe`, `scd.optimize.apply_fix`) están **sujetas a aprobación de forma predeterminada**. Las correcciones destructivas requieren un `allow_destructive: true` explícito. Ejecute mutaciones solo en un espacio de trabajo con copia de seguridad, bajo control de versiones y desechable.

## Commandlet (CI / sin interfaz)

Interruptores: `-QuickSafe`, `-FullScan`, `-DeepScan`, `-OptimizationQueueReport`, `-ApplySafeQueue`, `-Path=`, `-Limit=`, `-NoFail`, más los interruptores estándar `-unattended -nop4 -nosplash`. Los interruptores de aplicación solo deben dirigirse a proyectos con copia de seguridad.

## Rutas del ecosistema opcionales

Cuando **Unreal Capability Mesh (UCM)** está habilitado, SCD expone capacidades de proveedor de solo lectura y dos rutas de optimización mutantes sujetas a aprobación a través de rutas UCM declaradas en JSON. SCD nunca vincula un complemento par en el código; esta integración es completamente opcional. Consulte el [índice de documentación](README.md) y [../Resources/SMART_ANALYSIS_ARCHITECTURE.md](../Resources/SMART_ANALYSIS_ARCHITECTURE.md).

SCD también expone rutas de trabajo del editor de solo lectura (`scd.editor.jobs.list.v1`, `scd.editor.jobs.status.v1`) para la agregación de UMCP a través de UCM.

Para obtener una configuración más profunda del analizador/preajuste/gobernanza, consulte [../Resources/SMART_ANALYSIS_ARCHITECTURE.md](../Resources/SMART_ANALYSIS_ARCHITECTURE.md).

<!-- doc-provenance: AKDB:plugins/SmartContentDiet/architecture.md; docs/architecture/plugins/SmartContentDiet/product-facts.yml; reconciled 2026-07-16 -->
# Guía de inicio rápido

Esta guía lo lleva desde la instalación hasta un **resultado real**: un escaneo de los activos de su proyecto con hallazgos de optimización y (opcionalmente) una corrección segura revisada aplicada con informes de antes/después. El bucle principal de Smart Content Diet funciona por sí solo: **no se requiere IA, complemento par ni herramienta externa**.

> **⚠ La seguridad es lo primero.** La aplicación de correcciones, reducciones, movimientos/eliminaciones de activos, actualizaciones de la línea base o escrituras de gobernanza **modifica los activos del proyecto**. Solo hágalo en un espacio de trabajo **con copia de seguridad, bajo control de versiones y desechable**, nunca en código fuente no protegido. Escanear y previsualizar son acciones de solo lectura y seguras.

## Lo que tendrá después de esta guía

La herramienta abierta en el rol elegido, un escaneo Quick Safe completado con hallazgos y una comprensión de cómo previsualizar y aplicar optimizaciones seguras y leer el delta antes/después.

## Requisitos

- Editor de Unreal Engine 5.4+ con un proyecto que tenga activos de contenido.
- Sin software de terceros, cuenta, modelo de IA o tiempo de ejecución externo. Consulte [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md).

## 1. Instalar y habilitar

1. Agregue **SmartContentDiet** desde su biblioteca de Fab al proyecto (o instálelo en el motor).
2. Abra **Editar → Complementos**, habilite **SmartContentDiet** y reinicie cuando se le solicite.

## 2. Abrir la herramienta y elegir un rol (Primer resultado)

1. Abra **Tools → Content Tools → Smart Content Diet**.
2. En el selector de audiencia del encabezado (o en **Configuración**), elija su rol:
   - **Principiante**: Resumen, Optimizar, Hallazgos, Configuración; más explicación.
   - **Ingeniero / Productor (avanzado)**: agrega Preajuste y Gobernanza (Tendencia, Deuda, Presupuesto, Propiedad, Escaneo profundo), y Redundancia cuando hay un proveedor de similitud externo registrado.
3. Deje la **profundidad de escaneo** en **Quick Safe** (predeterminado: solo registro/metadatos, sin carga de activos; rápido).
4. Haga clic en **Quick Safe Scan** en el encabezado.

**Resultado esperado:** el escaneo se completa y la pestaña **Resumen** resume los hallazgos (lo que se puede mejorar de manera segura). Esto es de solo lectura.

## 3. Un ejemplo práctico trabajado: previsualizar y aplicar una corrección segura

> Haga una copia de seguridad / commit de su proyecto primero (consulte la nota de seguridad anterior).

1. Abra la pestaña **Optimizar** → **Cola de optimización segura**.
2. Haga clic en **Vista previa segura** para ver las optimizaciones seguras en cola y el delta proyectado antes/después (todavía de solo lectura).
3. Haga clic en **Aplicar de forma segura** para aplicar la cola segura. Después de una aplicación exitosa (o una corrección de un solo activo desde el detalle de **Hallazgos**), la shell **vuelve a escanear automáticamente**.
4. Compare los conteos de la cola y el resumen delta en el panel Optimizar.

**Resultado esperado:** se aplican optimizaciones seguras y se escribe un informe de aplicación JSON en:

```text
Saved/SmartContentDiet/OptimizationQueue/<timestamp>/
```

## 4. Profundidades de escaneo

| Profundidad | ¿Carga activos? | Uso |
| --- | --- | --- |
| **Quick Safe** (predeterminado) | No | Rápido "¿qué puedo mejorar de forma segura?" |
| **Full** | Sí | Hallazgos accionables de malla/textura/material |
| **Deep** | Sí | Más lento; métricas profundas de material/malla estática (Gobernanza → Escaneo profundo) |

La etiqueta del botón del encabezado y la sugerencia se actualizan con la profundidad seleccionada, que respeta cada ejecución del analizador.

## 5. Próximos pasos

- Shell del editor, pestañas, hallazgos, gobernanza: [../Resources/UI_AND_BEHAVIOR.md](../Resources/UI_AND_BEHAVIOR.md).
- Cola de optimización segura (depósitos, reglas de seguridad, esquema del informe): [../Resources/OPTIMIZATION_QUEUE.md](../Resources/OPTIMIZATION_QUEUE.md).
- Configuración y roles: [SettingsReference.md](SettingsReference.md).
- Problemas: [TROUBLESHOOTING.md](TROUBLESHOOTING.md) y [FAQ.md](FAQ.md).

> **Opcional / avanzado:** SCD también ofrece un commandlet sin interfaz para CI (`-QuickSafe`, `-FullScan`, `-DeepScan`, `-OptimizationQueueReport`, `-ApplySafeQueue`) y, solo si también posee **Unreal Capability Mesh (UCM)**, rutas opcionales del ecosistema declaradas en la configuración. Ninguno es necesario para el flujo de trabajo del editor anterior; consulte el [índice de documentación](README.md).

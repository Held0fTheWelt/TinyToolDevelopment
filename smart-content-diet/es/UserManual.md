<!-- doc-provenance: AKDB:plugins/SmartContentDiet/architecture.md; docs/architecture/plugins/SmartContentDiet/product-facts.yml; reconciled 2026-07-16 -->
# Manual de usuario

Este manual resume el flujo de trabajo del editor Smart Content Diet y señala las guías detalladas.

## Punto de entrada

Abra **Tools → Content Tools → Smart Content Diet**. La ventana es una shell adaptada a roles.

## Roles y pestañas

Establezca el rol (Principiante / Ingeniero / Productor) y el nivel de explicación en **Configuración** o en el selector de audiencia del encabezado. La visibilidad de la pestaña sigue al rol:

| Pestaña | Principiante | Avanzado (Ingeniero / Productor) |
| --- | --- | --- |
| Resumen, Optimizar, Hallazgos, Configuración | ✓ | ✓ |
| Preajuste | — | ✓ |
| Gobernanza (Tendencia, Deuda, Presupuesto, Propiedad, Escaneo profundo) | — | ✓ |
| Redundancia | — | ✓ (solo con un proveedor de similitud externo) |

## Profundidades de escaneo

Elija en el encabezado: **Quick Safe** (registro/metadatos, sin carga de activos), **Full** (carga activos), **Deep** (métricas profundas de material/malla; Gobernanza → Escaneo profundo). Cada ejecución del analizador respeta la profundidad seleccionada; el commandlet respeta `-QuickSafe` / `-FullScan` / `-DeepScan`.

Los escaneos amplios utilizan una canalización primero en AssetRegistry. SCD recopila candidatos una vez, lee metadatos económicos de textura/material de las etiquetas cuando es posible, compara primero las etiquetas y solo carga profundamente el conjunto de candidatos supervivientes que necesitan datos de objetos. La etapa de comparación de solo lectura se puede ejecutar en paralelo; las QuickFixes mutantes aún requieren una acción explícita del usuario o del commandlet.

Las rutas de duplicados y alfa comparten código auxiliar entre los hallazgos de escaneo y las reducciones. Las comprobaciones de alfa de textura/material utilizan la misma lógica de opacidad de instancia de material, y las salidas tempranas de reducción utilizan claves duplicadas alineadas con la reducción para que no se omita una consolidación segura solo porque el índice de escaneo más estricto no agrupó los activos.

## Flujo de trabajo principal: Bucle de optimización segura (sin IA)

1. Abra la herramienta.
2. Elija la profundidad de escaneo (Quick Safe / Full / Deep).
3. Ejecute el escaneo desde el encabezado.
4. Revise **Resumen**, luego **Optimizar → Cola de optimización segura**.
5. **Vista previa segura** → copia de seguridad / control de código fuente → **Aplicar de forma segura**.
6. La shell vuelve a escanear automáticamente después de una aplicación exitosa o una corrección de un solo activo.
7. Compare los conteos de la cola y el delta; los informes JSON se ubican en `Saved/SmartContentDiet/OptimizationQueue/<timestamp>/`.

## Flujo de trabajo de análisis general

1. Ejecute un escaneo (alcance de selección, carpeta o proyecto).
2. Revise los hallazgos por gravedad, impacto, dimensión y cadena de explicabilidad.
3. Utilice **Preajuste** (avanzado) para ver cómo los pesos de evaluación afectan las puntuaciones.
4. Utilice **Gobernanza** (avanzado) para tendencia, deuda, presupuesto, propiedad y escaneo profundo opcional.
5. Aplique QuickFixes solo después de confirmar la copia de seguridad/control de código fuente.
6. Vuelva a escanear y valide en el contexto del proyecto de destino.

## Seguridad

Las acciones mutantes modifican los activos del proyecto y están sujetas a aprobación de forma predeterminada. Ejecútelas solo en un espacio de trabajo con copia de seguridad, bajo control de versiones y desechable. Consulte el aviso de seguridad en [QUICKSTART.md](QUICKSTART.md).

## Trabajos del editor y UCM

El trabajo reciente del editor se registra como historial de trabajos para escaneos, validaciones y acciones de optimización. Cuando Unreal Capability Mesh está habilitado, SCD expone rutas de trabajo de solo lectura:

```text
scd.editor.jobs.list.v1
scd.editor.jobs.status.v1
```

Unified MCP Server puede agregar esas rutas a través de `jobs_list` / `jobs_status`; SCD en sí no depende de UMCP.

## Guías detalladas

- Shell del editor, pestañas, hallazgos, QuickFixes, gobernanza: [../Resources/UI_AND_BEHAVIOR.md](../Resources/UI_AND_BEHAVIOR.md).
- Cola de optimización segura (depósitos, reglas de seguridad, esquema del informe): [../Resources/OPTIMIZATION_QUEUE.md](../Resources/OPTIMIZATION_QUEUE.md).
- Arquitectura: [../Resources/SMART_ANALYSIS_ARCHITECTURE.md](../Resources/SMART_ANALYSIS_ARCHITECTURE.md).

<!-- doc-provenance: AKDB:plugins/SmartContentDiet/architecture.md; docs/architecture/plugins/SmartContentDiet/product-facts.yml; reconciled 2026-07-16 -->
# Documentación de SmartContentDiet

SmartContentDiet escanea los activos del proyecto de Unreal Engine, explica los hallazgos de optimización en contexto, expone vistas de gobernanza y ofrece flujos de trabajo de QuickFix / reducción revisados. El bucle de producto predeterminado es **escanear → revisar → aplicar correcciones seguras → volver a escanear → medir la mejora**, sin requerir IA ni herramientas externas.

## Aviso de seguridad

SmartContentDiet puede modificar los activos del proyecto cuando se aplican QuickFixes, reducciones de malla, cambios de textura/material, movimientos/eliminaciones de revisión de activos, actualizaciones de línea base o escrituras de gobernanza. Úselo únicamente en una rama o espacio de trabajo con copia de seguridad, bajo control de versiones y desechable. Nunca lo ejecute en código fuente no protegido. Úselo bajo su propio riesgo.

La funcionalidad se implementa cuidadosamente dentro de su alcance establecido, pero no reemplaza las copias de seguridad, el control de versiones, la revisión de código/contenido ni la validación específica del proyecto.

## Mapa de documentación

| Documento | Audiencia | Contenido |
|----------|-----------|-----------|
| [UI_AND_BEHAVIOR.md](../Resources/UI_AND_BEHAVIOR.md) | Artistas, artistas técnicos, productores | Shell del editor, pestañas, flujo de escaneo, hallazgos, QuickFixes, gobernanza |
| [OPTIMIZATION_QUEUE.md](../Resources/OPTIMIZATION_QUEUE.md) | Todos los usuarios del editor | Cola de optimización segura, depósitos, aplicar/vista previa, delta antes/después |
| [SMART_ANALYSIS_ARCHITECTURE.md](../Resources/SMART_ANALYSIS_ARCHITECTURE.md) | Ingenieros, integradores | Analizadores, preajustes, impacto, reducción, tendencia, arquitectura de gobernanza |
| [DIMENSION_INTEGRATION_STATUS.md](../Resources/DIMENSION_INTEGRATION_STATUS.md) | Ingenieros | FindingType, mapeo de dimensiones, convertidor, estado de integración de interfaz |
| [SmartAnalysisResult_Usage.md](../Resources/SmartAnalysisResult_Usage.md) | Ingenieros | Uso del modelo de resultados, metadatos de corrección automática |
| [CHANGELOG.md](../CHANGELOG.md) | Operadores de lanzamiento | Historial de versiones |

**¿Nuevo aquí?** Comience con [QUICKSTART.md](QUICKSTART.md) para la instalación y el bucle seguro de escaneo→corrección.

## Paquete para motor instalado

Utilice un paquete BuildPlugin de Smart Content Diet producido para la versión del motor instalada. El paquete conserva los binarios generados y los metadatos de precompilación requeridos por las compilaciones instaladas. No elimine esos archivos al copiar o archivar el complemento.

> **Para mantenedores:** la puerta de enlace de lanzamiento de SCD y los documentos de ejecución residen en el repositorio de desarrollo y **no** forman parte del paquete Fab; no los necesita para instalar o usar SCD.

## Punto de entrada del editor

Abra **Tools → Content Tools → Smart Content Diet**.

### Shell adaptada a roles

La ventana principal utiliza la configuración de audiencia (Principiante / Ingeniero / Productor) para controlar la profundidad de la explicación y qué pestañas son visibles.

| Pestaña | Principiante | Avanzado (Ingeniero / Productor + modo avanzado) |
|-----|----------|--------------------------------------------------|
| Resumen | ✓ | ✓ |
| Optimizar | ✓ | ✓ |
| Hallazgos | ✓ | ✓ |
| Preajuste | — | ✓ |
| Gobernanza | — | ✓ (Tendencia, Deuda, Presupuesto, Propiedad, Escaneo profundo como subpestañas) |
| Redundancia | — | ✓ solo cuando hay un proveedor de similitud externo registrado |
| Configuración | ✓ | ✓ |

Cambie el rol y el nivel de explicación en **Configuración** o mediante el selector de audiencia en el encabezado.

### Profundidades de escaneo (encabezado)

| Profundidad | ¿Carga activos? | Uso típico |
|-------|---------------|------------|
| **Quick Safe** (predeterminado) | No: ruta de registro/metadatos | Primera ejecución, rápido "¿qué puedo mejorar de forma segura?" |
| **Full** | Sí: canalización completa del analizador | Hallazgos accionables de malla/textura/material |
| **Deep** | Sí: incluye métricas profundas de material/malla estática | Más lento; trabajo de estadísticas de sombreador y malla profunda |

El cuadro combinado del encabezado actualiza la etiqueta del botón de escaneo principal (`Quick Safe Scan` / `Full Scan` / `Deep Scan`) y muestra una sugerencia de profundidad debajo de los controles.

La profundidad seleccionada se respeta en **cada** ejecución del analizador: las ejecuciones de análisis del editor (Hallazgos / Gobernanza → Ejecutar análisis) la pasan a `FSmartAnalysisOrchestrator`, y la línea de estado de gobernanza nombra la profundidad que se utilizó. **Commandlet y CI** respetan `-QuickSafe`, `-FullScan` y `-DeepScan` como antes. Las métricas profundas de material/malla utilizan además el flujo de trabajo Governance Deep Scan (`Governance → Deep Scan`), igual que el commandlet.

## Flujos de trabajo rápidos

### Rutas del ecosistema UCM

Cuando Unreal Capability Mesh (UCM) está habilitado, SmartContentDiet se puede utilizar a través de rutas declaradas en la configuración en lugar de puentes de proveedores directos. SCD nunca vincula un complemento par y nunca enumera uno en `required_plugin_names` o `Build.cs`; el valor entre complementos proviene de rutas JSON, no de dependencias de código. El perfil de proyecto activo expone **12 capacidades de SCD**:

| Capacidad | Tipo | Política |
| --- | --- | --- |
| `scd.migration.advice_from_handoff` | consultivo | solo lectura |
| `scd.scan.run` | proveedor | solo lectura |
| `scd.findings.get` | proveedor | solo lectura |
| `scd.findings.explain` | proveedor | solo lectura |
| `scd.health.snapshot` | proveedor | solo lectura |
| `scd.health.evidence` | proveedor | solo lectura |
| `scd.governance.snapshot` | proveedor | solo lectura |
| `scd.similarity.groups` | similitud | solo lectura |
| `scd.similarity.ingest_groups` | similitud | solo lectura |
| `scd.optimize.preview_safe` | optimización | solo lectura |
| `scd.optimize.apply_safe` | optimización | **mutante: requiere aprobación** |
| `scd.optimize.apply_fix` | optimización | **mutante: requiere aprobación** |

**Contrato de degradación.** Cada capacidad devuelve la envoltura compartida `smart_content_diet.capability_mesh_endpoint.v1` (`status` de `ok`/`degraded`/`error`). Las capacidades se reducen, en lugar de fallar, cuando falta una precondición: las rutas de optimización/hallazgos devuelven una envoltura `error` pidiéndole que ejecute `scd.scan.run` primero; `scd.optimize.apply_fix` devuelve una envoltura `degraded` (sin mutación) cuando se solicita una corrección destructiva sin `allow_destructive: true`. Conectar SCD a un par nunca se asume: una ruta que hace referencia a otro complemento (por ejemplo, el ejemplo `scd_ingest_from_iis.v1`, `iis.search.hybrid → scd.similarity.ingest_groups`) es informada por el descubrimiento de UCM como *disponible pero complemento no cargado* cuando ese par está ausente, mientras que cada capacidad exclusiva de SCD permanece *disponible*.

**Puerta de aprobación (y Opción 3).** Las dos rutas mutantes llevan `requires_user_approval: true`, por lo que UCM las bloquea con `ApprovalRequired` hasta que un humano apruebe la ejecución; ningún activo se toca antes de eso. Los operadores que desean una aplicación segura desatendida pueden cambiar la política de la ruta para eliminar el requisito de aprobación (Opción 3); la versión predeterminada se envía con aprobación bloqueada.

Los flujos de trabajo de colocación de PRS siguen siendo rutas UCM propiedad de PRS. Los puentes gratuitos siguen estando disponibles solo para equipos sin UCM y como implementaciones de referencia para adaptadores directos; no son necesarios en el proyecto principal.

### Bucle de optimización segura autónomo (sin IA)

### Corrección y rendimiento del escaneo

La ruta actual del analizador es primero en AssetRegistry. Construye el conjunto amplio de candidatos una vez, lee los metadatos de etiquetas antes de cargar los activos, paraleliza el trabajo de comparación de solo lectura y solo carga profundamente los candidatos finales. Una caché de metadatos por activo con invalidación de marca de tiempo/versión evita repetir el trabajo no cambiado.

El análisis de duplicados y alfa comparte asistentes con el motor de reducción. Salidas tempranas de reducción utilizan claves duplicadas alineadas con la reducción (`DuplicateTextureReduction`, `DuplicateStaticMeshReduction`) para que las comprobaciones de consolidación segura coincidan con la lógica de huella digital utilizada por el reductor real. Las heurísticas de alfa de textura están centralizadas en `SCDMaterialAlpha` para mantener alineado el comportamiento del analizador y la reducción.

El historial de trabajos del editor está disponible a través de rutas UCM (`scd.editor.jobs.list.v1`, `scd.editor.jobs.status.v1`) para la agregación de UMCP sin agregar una dependencia de UMCP a SCD.

1. Abra Smart Content Diet.
2. Deje la profundidad de escaneo en **Quick Safe** o elija **Full** / **Deep**.
3. Ejecute el escaneo desde el encabezado.
4. Revise **Resumen**, luego abra **Optimizar** → Cola de optimización segura.
5. **Vista previa segura** → **Aplicar de forma segura** (copia de seguridad / control de código fuente primero).
6. Después de una aplicación exitosa o una corrección de un solo activo desde el detalle de **Hallazgos**, la shell vuelve a escanear automáticamente.
7. Compare los conteos de la cola y el resumen delta en el panel Optimizar; los informes de aplicación JSON se ubican en `Saved/SmartContentDiet/OptimizationQueue/<timestamp>/`.

Consulte [OPTIMIZATION_QUEUE.md](../Resources/OPTIMIZATION_QUEUE.md) para conocer las definiciones de depósitos, las reglas de seguridad y el esquema del informe.

### Flujo de trabajo de análisis general

1. Ejecute un escaneo (alcance de selección, carpeta o proyecto).
2. Revise los hallazgos por gravedad, impacto, dimensión y cadena de explicabilidad.
3. Utilice **Preajuste** (avanzado) para comprender cómo los pesos de evaluación afectan las puntuaciones.
4. Utilice **Gobernanza** (avanzado) para tendencia, deuda, presupuesto, propiedad y escaneo profundo opcional.
5. Aplique QuickFixes solo después de confirmar la copia de seguridad/control de código fuente.
6. Vuelva a escanear y valide en el contexto del proyecto de destino.

## Commandlet (CI / sin interfaz)

```powershell
UnrealEditor-Cmd.exe "<Project>.uproject" -run=SmartContentDiet `
  -QuickSafe -OptimizationQueueReport -Path=/Game -Limit=50 `
  -NoFail -unattended -nop4 -nosplash
```

Aplicar filas de cola segura (solo proyecto con copia de seguridad):

```powershell
UnrealEditor-Cmd.exe "<Project>.uproject" -run=SmartContentDiet `
  -QuickSafe -ApplySafeQueue -OptimizationQueueReport -Path=/Game `
  -NoFail -unattended -nop4 -nosplash
```

| Flag | Efecto |
|------|--------|
| `-QuickSafe` | Escaneo de registro/dependencias; no carga activos |
| `-FullScan` | Carga activos y ejecuta analizadores (predeterminado cuando falta `-QuickSafe`) |
| `-DeepScan` | Profundidad más lenta; métricas profundas de material/malla |
| `-OptimizationQueueReport` | Escribe la cola JSON/Markdown (autohabilitado con `-QuickSafe`) |
| `-ApplySafeQueue` | Aplica solo las filas **Safe Now**; las filas destructivas son rechazadas |
| `-Path=/Game/...` | Alcance del escaneo |
| `-NoFail` | Sale con 0 incluso cuando existen advertencias de política (usar con precaución en CI) |

El commandlet imprime la advertencia de seguridad durante el uso y el inicio de la ejecución. Las actualizaciones de la línea base y las escrituras de informes son operaciones que mutan el espacio de trabajo.

## Ubicaciones de artefactos (gitignored)

| Artefacto | Ruta |
|----------|------|
| Informe de aplicación de cola de optimización | `Saved/SmartContentDiet/OptimizationQueue/<timestamp>/apply_report.json` |
| Informe de cola del commandlet | `-ReportDir` / predeterminado en `Saved/SmartContentDiet/` |
| Salida de validación de lanzamiento | `Saved/SCDValidation/` cuando se ejecuta la validación del mantenedor |

## Alcance de QuickFix implementado (resumen)

SmartContentDiet ofrece QuickFixes revisados para higiene de texturas, mallas estáticas/esqueléticas, materiales, animaciones, audio/VFX y revisión/consolidación de activos. Las acciones destructivas o entre activos requieren una confirmación explícita y no son seguras por lotes de forma predeterminada.

Catálogo completo: [UI_AND_BEHAVIOR.md § Optimization Packs](../Resources/UI_AND_BEHAVIOR.md#71-optimization-packs).

## Validación de lanzamiento

La validación de lanzamiento es un flujo de trabajo del mantenedor. El uso del comprador no requiere scripts de puerta de enlace locales, módulos de prueba de proyectos alojados ni rutas específicas del repositorio.

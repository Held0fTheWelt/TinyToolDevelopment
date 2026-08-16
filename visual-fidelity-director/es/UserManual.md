<!-- doc-provenance: AKDB:plugins/VisualFidelityDirector/architecture.md; docs/architecture/plugins/VisualFidelityDirector/product-facts.yml; reconciled 2026-07-12 -->
# Manual de usuario

Visual Fidelity Director es una herramienta local de Unreal Editor. La versión `2.0.0` se centra en un cockpit centrado en perfiles, al tiempo que conserva el panel Expert Tools 1.x integrado para flujos de trabajo de capturas y recetas.

## Abrir la herramienta

Utilice **Tiny Tools > Visual Fidelity Director**.

La pestaña acoplable ofrece las páginas **Cockpit**, **Evidence** y **Expert Tools**.

Opcional: **Editar > Editor Configurations > Visual Fidelity Director Editor Settings** abre las preferencias del editor de complementos (el acceso directo del menú se puede deshabilitar en la configuración).

## Página Cockpit

### Banner de estado

Muestra el titular de disponibilidad y el texto detallado del estado de compilación y validación del perfil activo.

### Tarjeta de acción

| Acción | Resultado esperado |
| --- | --- |
| **Refresh** | Vuelve a cargar perfiles, recompila la vista previa del perfil activo, reinicia el muestreo de métricas multicuadro y actualiza las franjas de ejes. |
| **Compile Preview** | Recompila los objetivos de configuración deseados para el perfil activo sin escribir la configuración. |
| **Open Reports** | Abre la carpeta de informes VFD local en el explorador de archivos del sistema operativo. |

### Barra de perfiles

Seleccione el perfil de fidelidad activo. La barra muestra el estado de validación y los perfiles conocidos cargados desde `Saved/VisualFidelityDirector/profiles/`.

### Barra de métricas

Muestra métricas del editor en vivo multicuadro (cuadro, hilo de juego, hilo de renderizado, GPU, cuello de botella y participación de costo por eje cuando esté disponible). Los valores de `-1` o las cadenas no disponibles explícitas significan que la medición no está disponible en el contexto actual del editor: VFD nunca inventa números.

### Franjas de ejes

Cada franja de eje de composición incluye:

- etiqueta de eje y color de disponibilidad;
- cuadro combinado **Variant** (las variantes no disponibles permanecen visibles pero deshabilitadas con evidencia de compatibilidad);
- deslizador **Intent** (`0.00`–`1.00`);
- resalte de selección para el cajón de detalles del eje activo.

### Cajón de detalles del eje

Para el eje seleccionado:

- **Ruta de herencia**: cadena ordenada desde el ancestro raíz hasta el perfil activo;
- **Procedencia**: filas a nivel de campo para configuraciones compiladas (destino, valor, fuente);
- **Hallazgos**: hallazgos de compilación y compatibilidad locales al control.

### Tarjeta de comparación de perfiles

Elija un segundo perfil e inspeccione las diferencias del estado deseado compilado por eje. Utiliza el mismo tiempo de ejecución de comparación que la biblioteca Blueprint.

### Cajón de aplicación gobernada

| Acción | Resultado esperado |
| --- | --- |
| **Build Destinations** | Resúmenes de solo lectura para destinos de Scalability, ini de renderizador y Device Profiles. |
| **Apply Approved** | Escribe solo destinos verificados y aprobados por el usuario mediante copia de seguridad → escritura → verificación → manifiesto de reversión. |
| **Rollback** | Restaura los últimos archivos respaldados desde el manifiesto de reversión. |

Los destinos bloqueados (activos, materiales, MRQ, accesibilidad, ejes de solo revisión) nunca aparecen como destinos modificables.

## Página Evidence

Muestra once bloques de evidencia de carril fijo (Lumen y otros carriles de revisión) con asignaciones de ejes declaradas, confianza y límites de revisión manual. Esta página es de solo lectura.

## Página Expert Tools

El panel de control 1.x integrado para flujos de trabajo heredados:

### Intent Mixer

Cada deslizador acepta de `0.00` a `1.00` y solo afecta la evaluación de prueba de la receta hasta que exporte o aplique.

| Deslizador | Significado |
| --- | --- |
| Image Stability | Prefiere detalles subpíxel más calmos y menos parpadeo. |
| Motion Clarity | Prefiere menos emborronamiento/fantasma en contenido en movimiento. |
| Fine Detail Preservation | Prefiere detalles aparentes más nítidos. |
| Specular Calmness | Prefiere menos parpadeo en zonas de brillo/destellos. |
| UI Crispness | Prefiere claridad en HUD/UMG. |
| Cinematic Accumulation | Prefiere acumulación de muestras de renderizado final. |
| Performance Headroom | Prefiere recomendaciones menos costosas. |

### Recetas integradas

Mismas quince ID de recetas integradas que la versión `1.0.0` (consulte [SettingsReference.md](SettingsReference.md)).

### Acciones de Expert Tools

| Acción | Resultado esperado |
| --- | --- |
| Export Snapshot (Expert Tools) | `quality_snapshot.json/.md` más copias más recientes. |
| Export Recipe Dry Run (Expert Tools) | `recipe_evaluation.json` y `settings_diff.md`; sin mutación. |
| Duplicate Recipe | JSON propiedad del proyecto en `Saved/VisualFidelityDirector/recipes/`. |
| Import Recipe | Actualiza la receta activa y los deslizadores desde el JSON importado. |
| Export Scanner Report | `visual_quality_report.json/.md`. |
| Lumen Deep Scan (Expert Tools) | Hallazgos de metadatos de caché de superficie de Lumen; sin mutación de malla/material. |
| Preview Apply + Rollback (Expert Tools) | Vista previa de CVar de sesión con reversión; `visual_fidelity_apply_report.*`. |
| Export A/B Report | `comparison_report.json/.md`. |
| Export Cinematic Report | `cinematic_quality_report.*` y `mrq_recommendation.md`. |
| Validate Schemas | `schema_validation_report.*`. |
| Export Diagnostics | `experimental_diagnostics_report.*`. |
| Productization Report | `productization_readiness_report.*`. |
| Open Output Folder | Abre la raíz de informes. |

## Biblioteca Blueprint

`UVFDCockpitBlueprintLibrary` expone los mismos servicios sin interfaz que el cockpit:

- cargar, resolver, validar y compilar perfiles de fidelidad;
- comparar perfiles;
- detectar capacidades de canalización;
- construir estado de evidencia;
- previsualizar, aplicar y revertir configuración permanente gobernada.

Demostración empaquetada: `Content/Blueprints/BPF_VFD_API`.

## Modelo de seguridad

- La revisión del cockpit, evidencia, comparación y vista previa de destino son de solo lectura.
- La aplicación permanente gobernada es la única ruta de mutación del cockpit y requiere aprobación explícita por destino.
- La vista previa de aplicación de Expert Tools permanece solo para CVar de sesión con reversión.
- VFD no modifica activos, materiales, Post Process Volumes, preajustes MRQ ni configuraciones de accesibilidad.

## Informes y perfiles

```text
Saved/VisualFidelityDirector/profiles/
Saved/VisualFidelityDirector/reports/
Saved/VisualFidelityDirector/recipes/
```

Trate las salidas como locales/privadas porque pueden contener nombres de proyectos, valores de CVar y dirección de calidad.

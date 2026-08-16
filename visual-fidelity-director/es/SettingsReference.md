<!-- doc-provenance: AKDB:plugins/VisualFidelityDirector/architecture.md; docs/architecture/plugins/VisualFidelityDirector/product-facts.yml; reconciled 2026-07-12 -->
# Referencia de configuración

VFD agrega configuraciones de complementos de editor en **Editar > Editor Configurations > Visual Fidelity Director Editor Settings**. La configuración de renderizado del proyecto se cambia solo a través de la aplicación permanente gobernada o la vista previa de sesión de Expert Tools.

## Controles del Cockpit

| Control | Valores | Efecto |
| --- | --- | --- |
| Selector de perfiles | Perfiles conocidos de `Saved/VisualFidelityDirector/profiles/` | Establece el perfil de fidelidad activo para compilación, evidencia y comparación. |
| Cuadro combinado de variante de eje | Variantes de canalización por eje | Selecciona la variante activa; las opciones no disponibles permanecen visibles con evidencia de compatibilidad. |
| Deslizador de intención de eje | `0.00`–`1.00` | Ajusta el nivel de intención para el eje dentro de la variante seleccionada. |
| Compare against | Segundo perfil | Controla la diferencia por eje lado a lado en la tarjeta de comparación. |
| Casillas de aprobación de destino | Scalability / ini de renderizador / Device Profiles | Bloquean escrituras permanentes gobernadas; los destinos no marcados nunca se escriben. |

## Destinos de aplicación gobernada (Configuración permanente)

| Destino | Archivo | ¿Escritura permanente? |
| --- | --- | --- |
| Niveles de calidad de Scalability | `DefaultGameUserSettings.ini` `[ScalabilityGroups]` | Sí, cuando se aprueba. |
| Configuración del renderizador | Sección de renderizador de `DefaultEngine.ini` | Sí, cuando se aprueba. |
| Perfiles de dispositivos | `DefaultDeviceProfiles.ini` | Sí, cuando se aprueba. |
| Variables de consola (sesión) | Solo sesión del editor | Ruta de vista previa de Expert Tools; no permanente. |
| Activos, materiales, MRQ, accesibilidad | Bloqueado | Nunca escrito por VFD. |

Flujo de aplicación: construir destinos → aprobar → copia de seguridad → escribir → verificar → manifiesto de reversión.

## Funciones de biblioteca Blueprint

Categorías de `UVFDCockpitBlueprintLibrary`:

| Función | Categoría | Salida |
| --- | --- | --- |
| LoadFidelityProfiles | Visual Fidelity\|Profiles | Arreglo de perfiles + advertencias |
| ResolveFidelityProfile | Visual Fidelity\|Profiles | Perfil resuelto o errores |
| ValidateFidelityProfile | Visual Fidelity\|Profiles | Resultado de validación |
| CompileFidelityProfile | Visual Fidelity\|Profiles | Objetivos de configuración compilados + hallazgos |
| CompareFidelityProfiles | Visual Fidelity\|Profiles | Resultado de comparación por eje |
| DetectPipelineCapabilities | Visual Fidelity\|Capability | Informe de capacidad |
| BuildEvidenceState | Visual Fidelity\|Evidence | Estado de evidencia |
| PreviewPersistentDestinations | Visual Fidelity\|Apply | Resúmenes de destino de solo lectura |
| ApplyPersistentConfiguration | Visual Fidelity\|Apply | Informe de aplicación (requiere aprobación) |
| RollbackPersistentConfiguration | Visual Fidelity\|Apply | Informe de reversión |

Activo de demostración: `Content/Blueprints/BPF_VFD_API`.

## Valores de deslizadores de intención (Expert Tools)

Todos los deslizadores de intención utilizan valores de punto flotante de `0.00` a `1.00`.

| Control | Fuente predeterminada | Efecto |
| --- | --- | --- |
| Image Stability | Receta seleccionada | Valores más altos favorecen una estabilidad temporal más calma. |
| Motion Clarity | Receta seleccionada | Valores más altos favorecen menos emborronamiento/fantasma. |
| Fine Detail Preservation | Receta seleccionada | Valores más altos favorecen detalles más nítidos con mayor riesgo de aliasing. |
| Specular Calmness | Receta seleccionada | Valores más altos favorecen un menor parpadeo en reflejos. |
| UI Crispness | Receta seleccionada | Valores más altos priorizan la claridad de HUD/UMG. |
| Cinematic Accumulation | Receta seleccionada | Valores más altos favorecen la acumulación de renderizado final. |
| Performance Headroom | Receta seleccionada | Valores más altos favorecen recomendaciones menos costosas. |

## ID de recetas integradas

Utilice estas ID en JSON de recetas e informes exportados:

```text
stable_gameplay
sharp_gameplay
cinematic_calm
vegetation_heavy_scene
specular_heavy_scene
ui_safe_temporal
vr_clarity
low_end_stable
marketing_screenshot
debug_no_temporal
lumen_static_material_performance
lumen_dynamic_material_safe
lumen_low_end_atlas_budget
lumen_surface_cache_debug
lumen_archviz_many_instances
```

## CVar capturadas

La captura de snapshot lee este registro de CVar curado cuando está disponible:

```text
r.AntiAliasingMethod
r.ScreenPercentage
r.TemporalAA.Upsampling
r.PostProcessAAQuality
r.TSR.History.ScreenPercentage
r.TSR.ShadingRejection.Flickering
r.DefaultFeature.MotionBlur
r.MotionBlurQuality
r.LumenScene.SurfaceCache.CardCapturesPerFrame
r.LumenScene.SurfaceCache.CardCaptureRefreshFraction
r.LumenScene.SurfaceCache.CardMaxResolution
r.LumenScene.SurfaceCache.AtlasSize
r.LumenScene.SurfaceCache.AllowCardSharing
r.LumenScene.SurfaceCache.DetectCardSharingCompatibility
r.LumenScene.SurfaceCache.MeshCardsMinSize
r.LumenScene.SurfaceCache.MeshCardsMergeComponents
r.LumenScene.SurfaceCache.MeshCardsMergeInstances
r.LumenScene.DirectLighting.UpdateFactor
r.LumenScene.Radiosity.UpdateFactor
```

Las CVar no disponibles se registran como no disponibles en lugar de hacer fallar todo el informe.

## Revisión de caché de superficie de Lumen

El carril de revisión de caché de superficie de Lumen es solo de informe para contenido de malla y material. Puede capturar CVar de Lumen curadas, evaluar recetas de Lumen, agrupar hallazgos de Lumen en `visual_quality_report.md` y ejecutar **Lumen Deep Scan** para obtener pistas de metadatos de Asset Registry solo para el editor. No cambia la configuración de tarjetas de malla estática, grafos de materiales, banderas de uso compartido de tarjetas, configuración de proyecto ni preajustes MRQ.

## Soporte de vista previa de aplicación (Expert Tools)

| Objetivo compatible | Modos compatibles | ¿Escritura permanente? |
| --- | --- | --- |
| Variables de consola | Preview Only, Editor Session Only | Sin escritura de configuración de proyecto. |
| Configuración de proyecto | Cajón de aplicación gobernada en la página Cockpit | Sí, cuando se aprueba explícitamente. |
| Post Process Volumes | Solo recomendación/exportación | No. |
| Preajustes MRQ | Solo recomendación/exportación | No. |
| Activos | Solo recomendación/exportación | No. |
| Configuración de malla/material de Lumen | Solo recomendación/exportación/revisión manual | No. |

## Archivos de informe

| Flujo de trabajo | Archivos |
| --- | --- |
| Captura | `quality_snapshot.json`, `quality_snapshot.md` |
| Evaluación a prueba de receta | `recipe_evaluation.json`, `settings_diff.md` |
| Escáner | `visual_quality_report.json`, `visual_quality_report.md` |
| Escaneo profundo de Lumen | `visual_quality_report.json`, `visual_quality_report.md` |
| Aplicar (sesión) | `visual_fidelity_apply_report.json`, `visual_fidelity_apply_report.md` |
| Aplicar permanente | Informe de aplicación gobernada bajo raíces de copia de seguridad/informes VFD |
| Comparación A/B | `comparison_report.json`, `comparison_report.md` |
| Cinematográfico | `cinematic_quality_report.json`, `cinematic_quality_report.md`, `mrq_recommendation.md` |
| Validar esquemas | `schema_validation_report.json`, `schema_validation_report.md` |
| Diagnósticos | `experimental_diagnostics_report.json`, `experimental_diagnostics_report.md` |
| Productización | `productization_readiness_report.json`, `productization_readiness_report.md` |

Las copias más recientes utilizan los mismos nombres con el prefijo `latest_` bajo `Saved/VisualFidelityDirector/reports/`.

El JSON de perfil utiliza esquemas bajo la carpeta `Schemas/` del complemento y se guarda en `Saved/VisualFidelityDirector/profiles/`.

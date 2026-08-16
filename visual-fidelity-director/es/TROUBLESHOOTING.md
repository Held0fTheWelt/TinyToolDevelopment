<!-- doc-provenance: AKDB:plugins/VisualFidelityDirector/architecture.md; docs/architecture/plugins/VisualFidelityDirector/product-facts.yml; reconciled 2026-07-12 -->
# Solución de problemas

## Habilité el complemento y no pasó nada

Causa: VFD se abre desde una entrada de menú; no muestra una ventana de inicio.

Solución:

1. Reinicie Unreal Editor después de habilitar el complemento.
2. Abra **Tiny Tools > Visual Fidelity Director**.
3. Si el menú sigue faltando, confirme que el complemento esté habilitado en **Editar > Complementos**.

## Métricas en vivo no disponibles

Causa: las métricas en vivo requieren un contexto de medición de visor del editor disponible. Algunas plataformas, sesiones sin interfaz o tics iniciales del editor pueden no exponer datos de pases de GPU.

Solución:

1. Haga clic en **Refresh** después de que el visor sea visible.
2. Espere a que se complete la ventana de muestreo multicuadro (varios tics del editor).
3. Trate `-1` o las cadenas no disponibles explícitas como una degradación honesta: VFD no inventa números.

## No aparecen perfiles en la barra de perfiles

Causa: aún no existen perfiles de fidelidad bajo `Saved/VisualFidelityDirector/profiles/`.

Solución:

1. Importe o duplique un perfil a través del flujo de trabajo de su proyecto, o migre desde una receta integrada usando Expert Tools y herramientas de proyecto.
2. Haga clic en **Refresh** en la página Cockpit.

## La aplicación gobernada omitió todo

Causa: no se marcó ningún destino, la diferencia compilada ya coincide o el destino está bloqueado.

Solución:

1. Haga clic primero en **Build Destinations**.
2. Revise cada resumen y marque la aprobación solo para los destinos previstos.
3. Confirme que el perfil activo se compile con cambios (`Compile Preview`).

## La comparación de perfiles no muestra diferencias

Causa: los dos perfiles se compilan en el mismo estado deseado para todos los ejes, o un perfil falló la validación.

Solución:

1. Valide que ambos perfiles se compilen sin errores.
2. Cambie una variante o nivel de intención en un perfil y actualice.

## El panel de control / Expert Tools se abre pero no se escribe ningún informe

Causa: la carpeta `Saved` del proyecto puede ser de solo lectura o no estar disponible.

Solución:

1. Cambie a **Expert Tools** y haga clic en **Open Output Folder**.
2. Confirme que el proyecto pueda escribir en `Saved/VisualFidelityDirector/`.
3. Intente **Export Snapshot** nuevamente y lea la fila **Status**.

## La vista previa de aplicación omitió todo

Causa: la receta seleccionada puede contener solo recomendaciones de exportación, el valor recomendado ya coincide con el valor actual, o la CVar no está disponible en este contexto del motor.

Solución:

1. Exporte primero una prueba de evaluación de receta.
2. Abra `settings_diff.md`.
3. Verifique las columnas **Mode**, **Supported** y **Risk**.

## Una CVar dice No disponible

Causa: algunas CVar dependen de la versión del motor, renderizador, plataforma o contexto.

Solución: trate la recomendación como una revisión manual. VFD registra valores no disponibles en lugar de hacer fallar todo el flujo de trabajo.

## Las recomendaciones de MRQ no cambiaron mi preajuste

Causa: la mutación de preajuste de MRQ intencionalmente no es compatible.

Solución: abra `mrq_recommendation.md` y aplique cualquier configuración cinematográfica manualmente después de la revisión.

## La recomendación de Lumen no cambió una malla o material

Causa: las configuraciones de tarjetas de malla de Lumen, los grafos de materiales y las banderas de uso compartido de tarjetas de materiales son intencionalmente solo para revisión manual.

Solución: exporte **Lumen Deep Scan** o una prueba de receta de Lumen, luego inspeccione los informes y aplique cambios de malla o material manualmente solo después de la validación visual.

## Los diagnósticos experimentales se ven demasiado gruesos

Causa: el informe de diagnóstico es un mapa de calor de enrutamiento de revisión basado en metadatos. No es un mapa de calor de diferencia de cuadros basado en píxeles y no captura vectores de movimiento.

Solución: use informes de capturas y escáneres para una revisión estructurada; capture evidencia visual manualmente cuando sea necesario.

## La aplicación de la biblioteca Blueprint no escribió nada

Causa: `ApplyPersistentConfiguration` requiere `Request.bUserApproved` y resúmenes de destino aprobados.

Solución: llame primero a `PreviewPersistentDestinations`, marque solo los destinos previstos como aprobados en la solicitud, luego llame a aplicar con `bUserApproved=true`.

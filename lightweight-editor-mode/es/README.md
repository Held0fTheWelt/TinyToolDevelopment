<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/LightweightEditorMode/architecture.md -->
# Documentación de Lightweight Editor Mode

Lightweight Editor Mode es un plugin para el editor de Unreal Engine que permite a artistas, diseñadores de niveles, artistas técnicos y programadores reducir temporalmente el coste de renderizado del editor mientras trabajan en proyectos pesados. Está diseñado como una herramienta de trabajo reversible: actívelo cuando un viewport sea demasiado exigente, continúe editando y luego desactívelo para volver al estado anterior del editor.

Esta documentación ofrece el nivel de detalle esperado para un plugin de editor listo para el marketplace. Cubre las expectativas de los compradores, el uso cotidiano, la configuración, el comportamiento técnico, la validación, el empaquetado y el mantenimiento.

## Empiece aquí

- [UserManual.md](UserManual.md) explica el flujo de trabajo normal en el editor.
- [BUYER_GUIDE.md](BUYER_GUIDE.md) explica qué hace el plugin y a quién va dirigido.
- [SettingsReference.md](SettingsReference.md) enumera cada ajuste disponible.
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md) ayuda a diagnosticar casos comunes en el editor.
- [TechnicalOverview.md](TechnicalOverview.md) describe el diseño en tiempo de ejecución.
- [CodeDocumentation.md](CodeDocumentation.md) relaciona los archivos fuente con el comportamiento.
- [PerformanceTuningReference.md](PerformanceTuningReference.md) ayuda a ajustar los perfiles.
- [ValidationAndQA.md](ValidationAndQA.md) proporciona pasos de prueba y validación de lanzamientos.
- [CompatibilityAndPackaging.md](CompatibilityAndPackaging.md) cubre notas sobre el motor y el empaquetado.
- [FAQ.md](FAQ.md) responde a preguntas frecuentes.
- [ReleaseChecklist.md](ReleaseChecklist.md) es la lista de comprobación final antes de la publicación.

## Lo que cambia el plugin

Cuando está activado, Lightweight Editor Mode puede aplicar estas optimizaciones en el editor:

- Reducir el porcentaje de pantalla (Screen Percentage) del viewport del editor.
- Reducir la calidad de escalabilidad general (Scalability Quality).
- Desactivar la iluminación indirecta difusa Lumen y los reflejos Lumen.
- Desactivar los mapas de sombras virtuales (Virtual Shadow Maps).
- Desactivar la niebla volumétrica y la niebla estándar.
- Forzar los viewports del editor al modo de visualización Unlit (sin iluminación).
- Desactivar el renderizado en tiempo real (Realtime) en los viewports del editor.

El comportamiento exacto depende del perfil seleccionado y de los ajustes de perfil editables en Project Settings.

## Promesa de diseño fundamental

El plugin es intencionadamente reversible:

- Guarda una copia de seguridad de la configuración de escalabilidad antes de cambiarla.
- Guarda una copia de seguridad de las variables de consola (CVars) modificadas antes de establecer los valores del plugin.
- Almacena los modos de visualización y estados en tiempo real por viewport para la sesión activa.
- Almacena un modo de visualización alternativo persistente para la recuperación tras reiniciar.
- Restaura el estado del editor cuando el modo se desactiva o el módulo se cierra.

Esto hace que el plugin sea ideal para un alivio rápido del rendimiento mientras mantiene intacta la configuración principal del proyecto.

## Flujo de trabajo rápido

1. Active el plugin en Edit > Plugins.
2. Abra Tools > Performance > Lightweight Editor Mode.
3. Elija un perfil: Mild, Balanced, Aggressive o Extreme.
4. Haga clic en Enable Lightweight Mode.
5. Trabaje en el editor con un coste de viewport reducido.
6. Haga clic en Disable Lightweight Mode antes de los trabajos finales de iluminación, materiales o capturas.

## Guías visuales

La carpeta Documentation/Screenshots contiene diagramas de flujo de trabajo en SVG:

- [01-workflow-overview.svg](Screenshots/01-workflow-overview.svg)
- [02-profile-and-settings.svg](Screenshots/02-profile-and-settings.svg)
- [03-restore-flow.svg](Screenshots/03-restore-flow.svg)

Estos diagramas son recursos de documentación, no elementos de interfaz de usuario en tiempo de ejecución.

## Alcance del motor

La implementación se enfoca en las API del editor y variables de consola de renderizado al estilo de Unreal Engine 5.4. El detalle de implementación más importante es que los viewports del editor no siguen de manera fiable el mismo camino de porcentaje de pantalla que el renderizado de juego o PIE, por lo que el plugin utiliza CVars de porcentaje de pantalla específicas para el editor.

## Notas de seguridad

Lightweight Editor Mode es una herramienta de rendimiento para el editor, no un sistema de optimización en tiempo de ejecución para proyectos empaquetados. No debe utilizarse como la única vía de validación para iluminación final, sombras, niebla, materiales o entregas cinematográficas.

Antes de capturas finales o aprobaciones visuales, desactive el modo y revise la escena con la configuración de calidad de producción prevista.

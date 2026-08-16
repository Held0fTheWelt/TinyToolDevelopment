<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/LightweightEditorMode/architecture.md -->
# Guía de inicio rápido

Esta guía le acompañará desde la instalación hasta un **resultado visible**: un viewport de editor más rápido y reactivo que podrá restaurar por completo con un solo clic. Lightweight Editor Mode funciona de forma autónoma: no se requiere ningún otro plugin.

## Lo que obtendrá tras esta guía

Un perfil de edición "ligero" y reversible activado (viewport más rápido), y los conocimientos para cambiar de perfil y restaurar el estado original del editor según lo necesite.

## Requisitos

- Editor de Unreal Engine 5 (el plugin afecta únicamente al viewport del editor, nunca al juego empaquetado en tiempo de ejecución).
- No se requiere software de terceros, cuenta ni runtime adicional. Consulte [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md).

## 1. Instalación y activación

1. Añada **Lightweight Editor Mode** desde su biblioteca Fab al proyecto (o instálelo en el motor).
2. Abra **Edit → Plugins**, active **Lightweight Editor Mode** y reinicie cuando se le solicite.

## 2. Abrir la herramienta (Primer resultado)

1. Abra **Tools → Performance → Lightweight Editor Mode**. Se abrirá una pestaña acoplable con un menú desplegable de perfiles, un botón de activación y la casilla *Enable on Editor startup*.
2. Seleccione el perfil **Balanced** (la opción predeterminada recomendada).
3. Haga clic en **Enable Lightweight Mode**.

**Resultado esperado:** el viewport se actualiza de inmediato: Balanced reduce el porcentaje de pantalla y la escalabilidad, desactiva la iluminación costosa y fuerza el modo Unlit / sin tiempo real. El editor se siente más ágil al instante.

## 3. Un ejemplo práctico: Cambiar de perfil y restaurar

1. Con el modo activado, cambie el perfil en el desplegable a **Aggressive**. El viewport se actualiza con los ajustes más agresivos (porcentaje de pantalla más bajo, escalabilidad baja, sin sombras/niebla costosas). Su estado original anterior a la activación permanece preservado.
2. Haga clic en **Disable Lightweight Mode**.

**Resultado esperado:** el editor restaura los niveles de escalabilidad guardados, las modificaciones de variables de consola, los modos de visualización del viewport y el estado en tiempo real: vuelve exactamente a donde empezó.

> Los perfiles están optimizados para la reactividad y no para la fidelidad visual, por lo que debe esperar viewports de menor resolución, sin iluminación (Unlit) y con menos sombras mientras esté activo. **Desactive el modo antes de revisar la iluminación o realizar capturas de pantalla.**

## 4. Personalizar perfiles

Abra **Project Settings → Plugins → Lightweight Editor Mode** para editar los valores de los perfiles Mild / Balanced / Aggressive / Extreme. El perfil seleccionado se copia en los valores activos antes de aplicar el modo. Consulte [PerformanceTuningReference.md](PerformanceTuningReference.md).

## 5. Opcional: Activar al iniciar el editor

Marque **Enable on Editor startup** para que el modo se active automáticamente una vez que existan viewports de editor en el próximo inicio.

## 6. Siguientes pasos

- Comportamiento completo por perfil y flujos de trabajo recomendados: [UserManual.md](UserManual.md).
- Referencia de todos los ajustes: [SettingsReference.md](SettingsReference.md).
- Problemas (ej. estado obsoleto tras reiniciar → *Restore Lightweight State*):
  [TROUBLESHOOTING.md](TROUBLESHOOTING.md) y [FAQ.md](FAQ.md).

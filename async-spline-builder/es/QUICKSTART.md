<!-- doc-provenance: product-facts.yml reconciled 2026-07-15; source AKDB:plugins/AsyncSplineBuilder/architecture.md -->
# Guía de inicio rápido

Esta guía lo lleva desde la instalación hasta un **resultado visible**: una malla de carretera/pista generada a lo largo de una spline que usted controla. Async Spline Builder funciona de forma autónoma — no se requiere ningún otro complemento.

## Lo que tendrá después de esta guía

Un `Spline Generating Actor` en su nivel con una carretera construida a partir de secciones de malla spline que puede remodelar moviendo puntos spline y recompilar a pedido.

## Requisitos

- Editor de Unreal Engine 5 y un nivel abierto.
- Al menos una **malla de carretera** que se repita a lo largo de su eje X local (consulte el paso 3 / Creación de mallas en el manual de usuario). Puede utilizar cualquier malla repetible de su proyecto para comenzar.
- Sin software de terceros, cuenta ni tiempo de ejecución. Consulte [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md).

## 1. Instalar y habilitar

1. Agregue **AsyncSplineBuilder** desde su biblioteca de Fab al proyecto (o instálelo en el motor).
2. Abra **Edit → Plugins**, habilite **AsyncSplineBuilder** y reinicie cuando se le solicite.

## 2. Abrir el panel (Primer resultado)

1. Abra o cree un nivel.
2. Abra **Tools → Track Tools → Async Spline Builder**. El panel tiene las pestañas **Build**, **Segments** y **Terrain**.

## 3. Un ejemplo práctico real: compilar una pista

1. En la pestaña **Build**, haga clic en **Create Actor** (esto genera un `ASplineGeneratingActor`), o seleccione uno existente y haga clic en **Use Selection**.
2. En **Setup**, asigne una malla repetible a `MainMesh` (requerido). Opcionalmente asigne `StartMesh` y `EndMesh`.
3. En el visor, mueva los puntos spline del actor para dar forma al camino.
4. Haga clic en **Validate** (esto verifica que `MainMesh` esté configurado y que la spline se pueda compilar).
5. Haga clic en **Build Now**.

**Resultado esperado:** El actor genera secciones de carretera `USplineMeshComponent` a lo largo de la spline. Mueva un punto spline y haga clic en **Rebuild** para ver la actualización de la carretera.

> Para pistas largas, habilite **Use Async Build** y configure **SegmentsPerTick** para que la generación se procese por lotes entre tics y el editor se mantenga receptivo. Use **Cancel** para detener una compilación asíncrona en curso.

## 4. Ir más allá (Opcional)

- Pestaña **Segments**: mallas por segmento, huecos de salto (`JumpGapsByPoints`) y desniveles.
- Pestaña **Terrain**: ajustar al terreno, deformación de altura y **muros de contención** procedimentales (`bGenerateGroundWalls`). Consulte [LandscapeAndWalls.md](LandscapeAndWalls.md).
- **Activo de datos:** guardar/cargar diseños con `WriteSplineToDataAsset` / `ReadSplineFromDataAsset`.

## 5. Próximos pasos

- Flujo de trabajo completo, datos por segmento, huecos, desniveles, muros, deformación de terreno: [UserManual.md](UserManual.md).
- Configuraciones: [SettingsReference.md](SettingsReference.md).
- Problemas y soluciones: [TROUBLESHOOTING.md](TROUBLESHOOTING.md) y [FAQ.md](FAQ.md).

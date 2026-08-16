<!-- doc-provenance: AKDB:plugins/SmartContentDiet/architecture.md; docs/architecture/plugins/SmartContentDiet/product-facts.yml; reconciled 2026-07-16 -->
# Solución de problemas

## Habilité el complemento pero no lo veo

Abra **Tools → Content Tools → Smart Content Diet**. Si falta la entrada del menú, confirme que el complemento esté habilitado en *Editar → Complementos* y que haya reiniciado el editor.

## Una pestaña que esperaba (Preajuste / Gobernanza / Redundancia) no es visible

La visibilidad de las pestañas depende del rol. **Preajuste** y **Gobernanza** aparecen para **Ingeniero / Productor** (modo avanzado); **Redundancia** aparece solo cuando hay un proveedor de similitud externo registrado. Cambie su rol/nivel de explicación en **Configuración** o en el selector de audiencia del encabezado.

## El escaneo devuelve poco o nada

**Quick Safe** utiliza solo la ruta de registro/metadatos (sin carga de activos), por lo que algunos hallazgos necesitan un paso más pesado. Cambie la profundidad del encabezado a **Full** (carga activos) o **Deep** (métricas profundas de material/malla) y vuelva a ejecutar.

## "Ejecutar escaneo primero" / hallazgos u optimización vacíos

Los hallazgos y las acciones de optimización requieren un escaneo completado. Ejecute primero un escaneo desde el encabezado y luego abra **Hallazgos** u **Optimizar**.

## La aplicación está bloqueada o solicita aprobación

Las acciones mutantes están sujetas a aprobación de forma predeterminada y deben ejecutarse en un espacio de trabajo con copia de seguridad, bajo control de versiones y desechable. Confirme su copia de seguridad/control de código fuente y luego apruebe la acción. Las correcciones destructivas requieren además un consentimiento explícito (`allow_destructive: true` en la ruta correspondiente).

## ¿Dónde están los informes de aplicación?

```text
Saved/SmartContentDiet/OptimizationQueue/<timestamp>/
```

## Una ruta entre complementos muestra "disponible pero complemento no cargado"

Eso es algo esperado y seguro: SCD nunca requiere de forma obligatoria un complemento par. Las rutas que hacen referencia a otro complemento (por ejemplo, una ingesta de similitud de IIS) se informan como *disponibles pero complemento no cargado* cuando ese par está ausente, mientras que cada capacidad exclusiva de SCD permanece disponible.

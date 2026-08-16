<!-- doc-provenance: product-facts.yml reconciled 2026-07-04; source AKDB:plugins/NamingConventionUtility/architecture.md -->
# Resolución de problemas

## El menú contextual no aparece

Compruebe que:

- El plugin está habilitado.
- El editor se ha reiniciado.
- Hace clic derecho en una carpeta del Content Browser.

## La herramienta indica que no se renombrará ningún asset

Causas posibles:

- Todos los assets ya cumplen la convención.
- Los tipos de assets no son compatibles.
- El DataAsset configurado está vacío.
- Los nombres generados no serían válidos.

## El Workbench bloquea el plan como obsoleto (Stale)

El plan cambió tras el escaneo (cambio de carpeta, edición de reglas, etc.). Haga clic de nuevo en **Scan**.

## No se puede modificar un perfil integrado

`epic_recommended` y `tiny_legacy` son de solo lectura. Utilice **Copy to Project** para duplicar sus reglas en su perfil personalizado.

## Una textura recibió el prefijo genérico `T_`

La detección automática de subtipos es heurística. Si los tokens de nombre no son explícitos, se aplica la regla genérica.

## El renombrado falló tras la confirmación

Causas comunes:

- Referencias existentes.
- Bloqueo en el control de código fuente.
- Paquetes bloqueados.

Consulte el registro de salida (Output Log).

## Información necesaria para soporte

- Versión de Unreal Engine.
- Versión del plugin.
- Ruta de la carpeta seleccionada.
- Ruta del DataAsset configurado.

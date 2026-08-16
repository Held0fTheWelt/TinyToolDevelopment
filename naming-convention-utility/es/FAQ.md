<!-- doc-provenance: product-facts.yml reconciled 2026-07-04; source AKDB:plugins/NamingConventionUtility/architecture.md -->
# Preguntas frecuentes (FAQ)

## ¿El plugin renombra los assets de verdad o solo genera informes?

Renombra realmente los assets tras su confirmación mediante `IAssetTools::RenameAssets`.

## ¿Renombra carpetas?

No. Escanea carpetas y renombra los assets que contienen.

## ¿Puedo ver una vista previa de los cambios?

Sí. El Workbench crea un plan de renombrado detallado y permite exportar un informe antes de aplicar los cambios.

## ¿Qué ocurre si dos assets obtienen el mismo nombre?

Ambas entradas en conflicto se excluyen del plan para evitar sobrescrituras.

## ¿Puede detectar subtipos de textura?

Sí, parcialmente mediante la compresión y los tokens de texto más comunes (`normal`, `roughness`, `metallic`, etc.).

## ¿Modifica los nombres de las clases Blueprint?

Renombra el asset como archivo/paquete, no reescribe el código interno.

## ¿Puedo importar reglas desde una hoja de cálculo?

Sí, importando una DataTable compatible y utilizando la función de conversión integrada.

## ¿Genera informes?

Sí, se guardan informes en formato JSON y Markdown en `Saved/NamingConventionUtility/Reports/`.

## ¿Corrije los redireccionadores (redirectors)?

Sí, se puede ejecutar una corrección automática de redireccionadores tras el renombrado si está habilitada.

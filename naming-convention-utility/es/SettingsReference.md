<!-- doc-provenance: product-facts.yml reconciled 2026-07-04; source AKDB:plugins/NamingConventionUtility/architecture.md -->
# Referencia de ajustes

Naming Convention Utility almacena sus ajustes a nivel de proyecto en `UNamingConventionUtility_Settings`.

## Objeto de ajustes

Archivo fuente:

```text
Source/NamingConventionUtility/Public/NamingConventionUtility_Settings.h
```

Ubicación en el editor:

```text
Edit > Project Settings > Plugins > Naming Convention Utility
```

## NamingConventionDataAssetPath

Tipo:

```text
FSoftObjectPath
```

Predeterminado:

```text
/NamingConventionUtility/Editor/Data/DA_NamingConvention.DA_NamingConvention
```

Propósito:

- Apunta al DataAsset que contiene las reglas de renombrado.
- Utilizado por el flujo de trabajo de renombrado de carpetas.
- Utilizado como destino para la conversión de DataTable.

## bConfirmBeforeApplyingConventions

Predeterminado:

```text
true
```

Propósito:

- Muestra una vista previa y solicita confirmación antes de aplicar renombres masivos.

## bFixRedirectorsAfterRename

Predeterminado:

```text
true
```

Propósito:

- Intenta corregir automáticamente los redireccionadores en las carpetas seleccionadas tras el renombrado.

## DataAsset: NamingConventions

Cada entrada define la regla para un `EFileTypeIdentifier`.

Campos:

- `FileTypeIdentifier`: tipo de asset de destino.
- `NamingsToRemove`: fragmentos antiguos a eliminar.
- `PreFix`: prefijo a añadir.
- `PostFix`: sufijo a añadir.

## Perfiles del Workbench

El Workbench ofrece tres opciones:

- `epic_recommended`: reglas en solo lectura alineadas con las directrices de Epic.
- `tiny_legacy`: reglas en solo lectura compatibles con la versión 1.0.x.
- `project_custom`: el archivo especificado en `NamingConventionDataAssetPath`.

## Informes

Generados en:

```text
Saved/NamingConventionUtility/Reports/
```

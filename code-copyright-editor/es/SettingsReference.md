<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/CodeCopyrightEditor/architecture.md -->
# Referencia de configuración

La configuración de Code Copyright Editor está disponible en:

```text
Project Settings > Plugins > Code Copyright Editor
```

La ventana del editor también expone las acciones de plantilla y flujo de trabajo más importantes.

## Identidad

| Configuración | Valor predeterminado | Usado por |
| --- | --- | --- |
| `OwnerName` | `Your Company or Name` | `{OwnerName}`, `{CopyrightText}`, informes |
| `ContactEmail` | Vacío | `{ContactEmail}` |
| `ProductNameFallback` | `PluginProject` | `{ProductName}` cuando no se encuentra ningún nombre visible del plugin |
| `CopyrightStartYear` | `2025` | `{Year}`, `{CopyrightText}` |

`{Year}` se genera como el año de inicio cuando es igual al año actual. Si el año difiere, se genera como un rango tipo `2025-2026`.

## Licencia

| Configuración | Valor predeterminado | Usado por |
| --- | --- | --- |
| `LicenseName` | `Fab Standard End User License Agreement` | `{LicenseName}` |
| `LicenseUrl` | `https://www.fab.com/eula` | `{LicenseUrl}` |
| `LicenseIdentifier` | `LicenseRef-Fab-Standard-EULA` | `{LicenseIdentifier}`, informes |

Utilice identificadores SPDX estándar para licencias estándar, como `MIT` o `Apache-2.0`. Utilice `LicenseRef-*` para licencias personalizadas o específicas de tiendas de aplicaciones como un CLUF de producto.

## Plantillas

| Configuración | Propósito |
| --- | --- |
| `SourceNoticeTemplate` | Encabezado generado en los archivos fuente. |
| `ProjectSettingsNoticeTemplate` | Aviso generado en el campo de derechos de autor a nivel de proyecto de Unreal. |

## Alcance (Scope)

| Configuración | Valor predeterminado | Propósito |
| --- | --- | --- |
| `ScanRootPaths` | `Source`, `Plugins` | Carpetas escaneadas por `Scan Files`. |
| `SourceFileExtensions` | `.h`, `.hpp`, `.hh`, `.inl`, `.c`, `.cc`, `.cpp`, `.cxx`, `.cs`, `.usf`, `.ush` | Extensiones tratadas como archivos fuente. |
| `ExcludedPathFragments` | `.git`, `.vs`, `Binaries`, `Content`, `DerivedDataCache`, `External`, `Intermediate`, `Resources`, `Saved`, `ThirdParty` | Fragmentos de carpeta/ruta omitidos durante los escaneos. |
| `ExcludedFilePaths` | Vacío por defecto | Archivos exactos relativos al proyecto omitidos durante los escaneos. |
| `ExcludedFilePatterns` | `*.generated.h` | Patrones de comodines omitidos durante los escaneos. |

## Protección

| Configuración | Valor predeterminado | Propósito |
| --- | --- | --- |
| `ProtectForeignNotices` | Activado | Evita que textos de avisos desconocidos se reescriban automáticamente. |
| `TreatUnrealDefaultNoticesAsReplaceable` | Activado | Permite reemplazar los avisos predeterminados/marcadores de posición de Unreal. |
| `OwnNoticeMarkers` | Nombre de propietario, identificador de licencia, texto EULA Fab, texto marcador Unreal | Identifica avisos que pertenecen a este proyecto. |
| `ProtectedNoticeMarkers` | Marcadores de derechos de autor de terceros y de Epic | Identifica avisos que no deben reescribirse automáticamente. |

## Línea base recomendada

Para la mayoría de productos de plugin para Fab:

- Mantenga `ProtectForeignNotices` activado.
- Mantenga `TreatUnrealDefaultNoticesAsReplaceable` activado.
- Mantenga `ThirdParty`, `External`, `Binaries`, `Intermediate` y `Saved` excluidos.
- Utilice `LicenseRef-Fab-Standard-EULA` para productos con EULA de Fab.
- Mantenga las líneas SPDX cerca de la parte superior de la plantilla de fuentes.
- Utilice `{FileMetadataBlock}` para contexto opcional a nivel de archivo.

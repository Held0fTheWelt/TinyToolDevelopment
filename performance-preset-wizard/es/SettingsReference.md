<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/PerformancePresetWizard/architecture.md -->
# Referencia de ajustes

Referencia de los ajustes del plugin y de los campos de los assets de preajustes.

## Ajustes del proyecto

Abra **Edit > Project Settings > Plugins > Performance Preset Wizard**.

| Ajuste | Tipo | Predeterminado | Descripción |
| --- | --- | --- | --- |
| Apply Preset On Editor Startup | Boolean | `false` | Si está habilitado, el preajuste de inicio seleccionado se aplica al finalizar la inicialización del editor. |
| Startup Preset | Soft object pointer | Vacío | El `UPerformancePresetAsset` que se aplicará al iniciar el editor. |

## Ajustes del proyecto en tiempo de ejecución

Abra **Edit > Project Settings > Plugins > Performance Preset Wizard Runtime**.

| Ajuste | Tipo | Predeterminado | Descripción |
| --- | --- | --- | --- |
| Max Backup History | Integer | `10` | Número máximo de copias de seguridad en tiempo de ejecución. Limitado a `1..100`. |
| Runtime Preset Library | Array of soft object pointers | Vacío | Assets de preajustes mostrados por el widget selector predeterminado. |
| Storage Provider Class | Class | `PerformancePresetGameUserSettingsStorage` | Proveedor de almacenamiento utilizado por el subsistema de ejecución. |

## Campos de un asset de preajuste

Los assets de preajustes utilizan la clase `UPerformancePresetAsset`.

| Campo | Tipo | Predeterminado | Descripción |
| --- | --- | --- | --- |
| Display Name | `FText` | Vacío | Nombre visible mostrado en el asistente. |
| Description | `FText` | Vacío | Breve explicación del hardware de destino o caso de uso. |
| Target Platform | Enum | Desktop Mid Range | Indicación de agrupación y ordenación. |
| View Distance Quality | Integer | `2` | Nivel de escalabilidad para la distancia de visión. |
| Anti-Aliasing Quality | Integer | `2` | Nivel de escalabilidad para el anti-aliasing. |
| Shadow Quality | Integer | `2` | Nivel de escalabilidad para las sombras. |
| Global Illumination Quality | Integer | `2` | Nivel de escalabilidad para la iluminación global. |
| Reflection Quality | Integer | `2` | Nivel de escalabilidad para las reflexiones. |
| Post Process Quality | Integer | `2` | Nivel de escalabilidad para el postprocesado. |
| Texture Quality | Integer | `2` | Nivel de escalabilidad para las texturas. |
| Effects Quality | Integer | `2` | Nivel de escalabilidad para los efectos. |
| Foliage Quality | Integer | `1` | Nivel de escalabilidad para el follaje. |
| Shading Quality | Integer | `2` | Nivel de escalabilidad para el sombreado. |
| Landscape Quality | Integer | `2` | Nivel de escalabilidad para el terreno. |
| CVar Overrides | Array | Vacío | Modificaciones de variables de consola adicionales. |

Todos los valores de calidad están limitados al rango `0..4`:

- `0`: Low
- `1`: Medium
- `2`: High
- `3`: Epic
- `4`: Cinematic

## Campos de las modificaciones de CVar

Cada `FPerformanceCVarOverride` contiene:

| Campo | Tipo | Descripción |
| --- | --- | --- |
| Name | `FString` | Nombre de la variable de consola, por ejemplo `r.ScreenPercentage`. |
| Value | `FString` | Valor pasado a la CVar. |
| Editor Only | Boolean | Si es verdadero, la modificación solo se aplica en el editor. |

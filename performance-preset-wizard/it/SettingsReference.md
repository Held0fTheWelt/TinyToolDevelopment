<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/PerformancePresetWizard/architecture.md -->
# Riferimento delle impostazioni

Riferimento per le impostazioni del plugin e i campi degli asset dei preset.

## Impostazioni del progetto

Apri **Edit > Project Settings > Plugins > Performance Preset Wizard**.

| Impostazione | Tipo | Predefinito | Descrizione |
| --- | --- | --- | --- |
| Apply Preset On Editor Startup | Boolean | `false` | Se abilitato, il preset all'avvio selezionato viene applicato al termine dell'inizializzazione dell'editor. |
| Startup Preset | Soft object pointer | Vuoto | Il `UPerformancePresetAsset` da applicare all'avvio dell'editor. |

## Impostazioni del progetto in runtime

Apri **Edit > Project Settings > Plugins > Performance Preset Wizard Runtime**.

| Impostazione | Tipo | Predefinito | Descrizione |
| --- | --- | --- | --- |
| Max Backup History | Integer | `10` | Numero massimo di voci di backup in runtime. Limitato a `1..100`. |
| Runtime Preset Library | Array of soft object pointers | Vuoto | Asset dei preset mostrati dal widget di selezione predefinito. |
| Storage Provider Class | Class | `PerformancePresetGameUserSettingsStorage` | Provider di archiviazione utilizzato dal sottosistema runtime. |

## Campi degli asset dei preset

Gli asset dei preset utilizzano la classe `UPerformancePresetAsset`.

| Campo | Tipo | Predefinito | Descrizione |
| --- | --- | --- | --- |
| Display Name | `FText` | Vuoto | Nome leggibile mostrato nella procedura guidata. |
| Description | `FText` | Vuoto | Breve spiegazione dell'hardware di destinazione o del caso d'uso. |
| Target Platform | Enum | Desktop Mid Range | Indicazione di raggruppamento e ordinamento. |
| View Distance Quality | Integer | `2` | Livello di scalabilità per la distanza di visualizzazione. |
| Anti-Aliasing Quality | Integer | `2` | Livello di scalabilità per l'anti-aliasing. |
| Shadow Quality | Integer | `2` | Livello di scalabilità per le ombre. |
| Global Illumination Quality | Integer | `2` | Livello di scalabilità per l'illuminazione globale. |
| Reflection Quality | Integer | `2` | Livello di scalabilità per i riflessi. |
| Post Process Quality | Integer | `2` | Livello di scalabilità per il post-processing. |
| Texture Quality | Integer | `2` | Livello di scalabilità per le texture. |
| Effects Quality | Integer | `2` | Livello di scalabilità per gli effetti. |
| Foliage Quality | Integer | `1` | Livello di scalabilità per il fogliame. |
| Shading Quality | Integer | `2` | Livello di scalabilità per lo shading. |
| Landscape Quality | Integer | `2` | Livello di scalabilità per il paesaggio. |
| CVar Overrides | Array | Vuoto | Sovrascritture di variabili di console aggiuntive. |

Tutti i valori di qualità sono limitati all'intervallo `0..4`:

- `0`: Low
- `1`: Medium
- `2`: High
- `3`: Epic
- `4`: Cinematic

## Campi delle sovrascritture CVar

Ogni `FPerformanceCVarOverride` contiene:

| Campo | Tipo | Descrizione |
| --- | --- | --- |
| Name | `FString` | Nome della variabile di console, ad esempio `r.ScreenPercentage`. |
| Value | `FString` | Valore passato alla CVar. |
| Editor Only | Boolean | Se vero, la sovrascrittura viene applicata solo nell'editor. |

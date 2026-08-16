<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/PerformancePresetWizard/architecture.md -->
# Référence des paramètres

Cette référence liste les paramètres du plugin et les champs d'asset de préréglage.

## Paramètres du projet

Ouvrez **Edit > Project Settings > Plugins > Performance Preset Wizard**.

| Paramètre | Type | Valeur par défaut | Description |
| --- | --- | --- | --- |
| Apply Preset On Editor Startup | Boolean | `false` | Lorsqu'il est activé, le préréglage de démarrage sélectionné est appliqué une fois l'initialisation de l'éditeur terminée. |
| Startup Preset | Soft object pointer | Vide | Le `UPerformancePresetAsset` à appliquer au démarrage de l'éditeur. |

## Paramètres du projet à l'exécution

Ouvrez **Edit > Project Settings > Plugins > Performance Preset Wizard Runtime**.

| Paramètre | Type | Valeur par défaut | Description |
| --- | --- | --- | --- |
| Max Backup History | Integer | `10` | Nombre maximal d'entrées de sauvegarde à l'exécution. Limité à `1..100`. |
| Runtime Preset Library | Array of soft object pointers | Vide | Assets de préréglages affichés par le widget de sélection par défaut. |
| Storage Provider Class | Class | `PerformancePresetGameUserSettingsStorage` | Fournisseur de stockage utilisé par le sous-système d'exécution. |

## Champs d'un asset de préréglage

Les assets de préréglage utilisent la classe `UPerformancePresetAsset`.

| Champ | Type | Valeur par défaut | Description |
| --- | --- | --- | --- |
| Display Name | `FText` | Vide | Nom lisible affiché dans l'assistant. |
| Description | `FText` | Vide | Courte explication du matériel cible ou du cas d'utilisation. |
| Target Platform | Enum | Desktop Mid Range | Indication de regroupement et de tri. |
| View Distance Quality | Integer | `2` | Niveau de scalabilité pour la distance d'affichage. |
| Anti-Aliasing Quality | Integer | `2` | Niveau de scalabilité pour l'antialiasing. |
| Shadow Quality | Integer | `2` | Niveau de scalabilité pour les ombres. |
| Global Illumination Quality | Integer | `2` | Niveau de scalabilité pour l'illumination globale. |
| Reflection Quality | Integer | `2` | Niveau de scalabilité pour les réflexions. |
| Post Process Quality | Integer | `2` | Niveau de scalabilité pour le post-traitement. |
| Texture Quality | Integer | `2` | Niveau de scalabilité pour les textures. |
| Effects Quality | Integer | `2` | Niveau de scalabilité pour les effets. |
| Foliage Quality | Integer | `1` | Niveau de scalabilité pour le feuillage. |
| Shading Quality | Integer | `2` | Niveau de scalabilité pour l'ombrage. |
| Landscape Quality | Integer | `2` | Niveau de scalabilité pour le paysage. |
| CVar Overrides | Array | Vide | Recharges de variables de console supplémentaires. |

Toutes les valeurs de qualité sont limitées à la plage `0..4` :

- `0` : Low
- `1` : Medium
- `2` : High
- `3` : Epic
- `4` : Cinematic

## Champs de rechargement CVar

Chaque `FPerformanceCVarOverride` contient :

| Champ | Type | Description |
| --- | --- | --- |
| Name | `FString` | Nom de la variable de console, par exemple `r.ScreenPercentage`. |
| Value | `FString` | Valeur transmise à la CVar. |
| Editor Only | Boolean | Si vrai, la rechargement est appliquée uniquement dans l'éditeur. |

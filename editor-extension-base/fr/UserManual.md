# Manuel utilisateur

Editor Extension Base regroupe les primitives d'interface utilisateur de l'éditeur Unreal et les bibliothèques utilitaires afin que les plugins de fonctionnalités puissent conserver une cohérence dans les comportements de sélection, de vérification, d'enregistrement et d'annulation.

## Public cible

- Auteurs de plugins créant des Editor Utility Widgets ou des outils d'éditeur.
- Équipes standardisant l'expérience utilisateur (UX) de l'éditeur pour le Tiny Tool Development sans réutiliser le code boilerplate des widgets.

Ce plugin **n'est pas** un outil destiné aux utilisateurs finaux avec sa propre entrée de menu Tiny Tools.

## Modules

| Module | Chargement | Contenu |
| --- | --- | --- |
| `EditorExtensionBase` | Éditeur / Défaut | Widgets, `UEditorManagerUtilityLibrary`, utilitaires d'annulation / d'action sur les actifs. |
| `EditorExtensionRuntimeBase` | Runtime / Défaut | Macros partagées (`UsefulMacros.h`) et point d'entrée du module. |

## Widgets partagés

<!-- image slot: eeb-widget-overview -->

| Classe | Objectif |
| --- | --- |
| `UEditorToolHeaderWidget` | Ligne d'en-tête avec des slots BindWidget pour le titre / le sous-titre et le texte d'affichage modifiable. |
| `UEditorUtilityButtonWidget` | Bouton stylisé avec des BindWidgets de bloc de texte et un délégué de clic. |
| `UEditorUtilityTabButtonWidget` | Bouton de type onglet avec des slots d'icône sélectionné / non sélectionné. |
| `UTwoPaneUserWidget` | Conteneur de mise en page à deux panneaux pour les écrans d'utilitaires d'éditeur. |

Les sous-classes de Blueprint de Widget doivent lier les slots BindWidget déclarés ; les liaisons manquantes génèrent des avertissements sous `LogEditorExtensionBase`.

## Bibliothèque d'utilitaires du gestionnaire d'éditeurs

`UEditorManagerUtilityLibrary` étend `UEditorUtilityLibrary` avec des utilitaires de sélection et de persistance :

| Fonction | Comportement |
| --- | --- |
| `GetSelectedAssetsForAction` | Retourne la sélection actuelle, éventuellement ancrée par un objet principal. |
| `CheckoutAndSaveAssets` | Tente la vérification et l'enregistrement du contrôle de version ; rapporte le succès via des paramètres de sortie. |
| `GetEditorWorld` | Retourne le monde de l'éditeur actuel lorsqu'il est disponible. |
| `BeginTransactionAndGetSelectedAssets` | **Déprécié en 5.4** — les appelants doivent gérer eux-mêmes `FScopedTransaction`. |

## Annulation et actions sur les actifs

| Classe | Comportement |
| --- | --- |
| `UEditorUtilityTask_PrepareUndo` | Tâche d'utilitaire d'éditeur qui prépare les options d'annulation pour les actifs transactionnels sélectionnés ; ignore les objets nuls, invalides ou non transactionnels avec des avertissements. |
| `UUndoableAssetActionUtility` | Encode les résultats d'actions sur les actifs annulables, y compris `SucceededWithCheckoutWarning` lorsque des avertissements de vérification accompagnent le succès. |

## Règles de conception

1. Gardez la logique métier spécifique à la fonctionnalité dans le plugin consommateur.
2. Ne considérez pas ce plugin comme une exigence de configuration pour des plugins de scène ou d'IA non liés.
3. Privilégiez les transactions gérées par l'appelant plutôt que l'utilitaire de début de transaction déprécié.

## Intégrations optionnelles

Les plugins d'éditeur Tiny Tool consommateurs peuvent dépendre de Editor Extension Base pour la cohérence de l'interface utilisateur. Ces intégrations sont gérées par le consommateur ; ce package se dégrade en « utilitaires indisponibles » uniquement lorsqu'il n'est pas activé — il ne substitue pas le comportement d'autres plugins.

## Documents associés

- [QUICKSTART.md](QUICKSTART.md)
- [SettingsReference.md](SettingsReference.md)
- [FAQ.md](FAQ.md)
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md)

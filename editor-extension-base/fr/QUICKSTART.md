---
lang: fr
title: EditorExtensionBase Quick Start
audience: [end_user]
owner_ref: plugin:EditorExtensionBase
applies_to:
  component: EditorExtensionBase
preconditions:
  - Unreal Engine project open with the plugin package available
  - Edit > Plugins can enable EditorExtensionBase
expected_result:
  text: GetSelectedAssetsForAction returns the current Content Browser selection after the plugin is enabled.
version:
  since: "1.0"
---
# Démarrage rapide

Ce guide vous accompagne de l'installation à une **première utilisation réelle** : activation d'Editor Extension Base et appel d'un utilitaire d'éditeur partagé depuis un Blueprint Utility ou un outil d'éditeur C++. Editor Extension Base est une couche de support pour d'autres plugins d'éditeur ; il ne s'agit pas d'un produit de menu Tiny Tools autonome.

## Ce que vous aurez après ce guide

Le plugin activé, et un appel réussi à `UEditorManagerUtilityLibrary::GetSelectedAssetsForAction` (ou à son équivalent appelable depuis Blueprint) retournant la sélection actuelle du Content Browser.

## Prérequis

- Unreal Engine 5.4 ou version ultérieure (descripteur `EngineVersion` 5.4.0).
- Editor Scripting Utilities activé (dépendance déclarée dans `EditorExtensionBase.uplugin`).
- Aucun logiciel tiers, compte ou runtime externe requis. Consultez [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md).

## 1. Installation et activation

1. Ajoutez **EditorExtensionBase** depuis votre bibliothèque Fab au projet (ou installez-le dans le répertoire Plugins du moteur).
2. Ouvrez **Edit → Plugins**, activez **EditorExtensionBase**, puis redémarrez lorsque cela est demandé.
3. Confirmez que **Editor Scripting Utilities** reste activé.

## 2. Vérification du chargement des modules

Après le redémarrage, le package expose deux modules :

| Module | Type | Rôle |
| --- | --- | --- |
| `EditorExtensionBase` | Editor | Widgets, utilitaires de sélection, utilitaires d'annulation. |
| `EditorExtensionRuntimeBase` | Runtime | Macros légères sûres pour les consommateurs non-éditeur. |

## 3. Exemple complet : lecture de la sélection actuelle

1. Sélectionnez un ou plusieurs assets dans le Content Browser.
2. Depuis un Editor Utility Widget ou un outil d'éditeur C++ dépendant de ce plugin, appelez :

```cpp
TArray<UObject*> Selected = UEditorManagerUtilityLibrary::GetSelectedAssetsForAction(nullptr);
```

3. Persistez ou agissez sur les objets retournés avec `CheckoutAndSaveAssets` lorsque vous écrivez intentionnellement :

```cpp
bool bCheckoutOk = false;
bool bSaveOk = false;
const bool bOk = UEditorManagerUtilityLibrary::CheckoutAndSaveAssets(
	Selected, bCheckoutOk, bSaveOk);
```

## Résultat attendu

- `Selected` contient la sélection du Content Browser (ou est vide lorsqu'aucun élément n'est sélectionné).
- Lorsque vous appelez `CheckoutAndSaveAssets`, les paramètres de sortie booléens rapportent les résultats de la validation et de l'enregistrement sans créer de transaction pour vous ; l'appelant gère la portée de `FScopedTransaction`.

## Prochaines étapes

- Lisez [UserManual.md](UserManual.md) pour le catalogue de widgets et d'utilitaires.
- Lisez [SettingsReference.md](SettingsReference.md) pour les propriétés modifiables sur les widgets partagés.
- Utilisez [TROUBLESHOOTING.md](TROUBLESHOOTING.md) lorsque les slots BindWidget ou les utilitaires de sélection génèrent des avertissements dans les journaux.

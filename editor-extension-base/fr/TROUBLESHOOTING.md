---
lang: fr
title: EditorExtensionBase Troubleshooting
audience: [end_user]
owner_ref: plugin:EditorExtensionBase
applies_to:
  component: EditorExtensionBase
symptom: Editor utility BindWidget slots are null or selection helpers warn in the log.
recovery:
  steps:
    - Confirm the plugin is enabled under Edit > Plugins and restart the editor
    - Re-read the matching troubleshooting entry and apply the documented fix
    - Re-run the quick start smoke check
version:
  since: "1.0"
---
# Dépannage

Format : Symptôme → Cause → Solution.

## 0. Je l'ai activé et rien ne s'est passé

**Symptôme :** Après avoir activé **EditorExtensionBase** et redémarré, aucun nouveau menu Tiny Tools n'apparaît et aucun changement d'interface utilisateur évident n'est visible.  
**Cause :** Ce plugin constitue une couche de base partagée ; il n'enregistre pas de menu produit propre.  
**Solution :** Vérifiez que le plugin est activé sous **Édition → Plugins**, puis appelez `UEditorManagerUtilityLibrary::GetSelectedAssetsForAction` depuis un **Editor Utility Widget** ou un outil d'éditeur en C++ (voir [QUICKSTART.md](QUICKSTART.md)). L'absence d'un nouveau menu est normale.

## 1. Le plugin est activé, mais les Blueprints d'aide ne trouvent pas la bibliothèque

**Symptôme :** Les nœuds Blueprint de `Editor Manager Utility Library` manquent après l'activation.  
**Cause :** Le module d'éditeur ne s'est pas chargé, ou l'actif Editor Utility a été compilé avant que le plugin ne soit activé.  
**Solution :** Confirmez que **EditorExtensionBase** est activé sous **Édition → Plugins**, redémarrez l'éditeur, puis actualisez/compilez le Blueprint Editor Utility.

## 2. `EditorUtilityButtonWidget : Le bouton est null`

**Symptôme :** Le journal `LogEditorExtensionBase` avertit que le bouton est null.  
**Cause :** La sous-classe Blueprint du Widget Utilitaire n'a pas lié l'emplacement de bouton BindWidget requis.  
**Solution :** Ouvrez le Blueprint du widget, liez l'emplacement de bouton déclaré sur `UEditorUtilityButtonWidget`, compilez, puis rouvrez l'outil.

## 3. `EditorUtilityButtonWidget : Le bloc de texte est null`

**Symptôme :** Avertissement indiquant que le BindWidget du bloc de texte est null.  
**Cause :** Le bloc de texte du libellé n'est pas lié dans le Blueprint.  
**Solution :** Liez l'emplacement du bloc de texte sur la classe de base C++, définissez le texte d'affichage, puis compilez.

## 4. `EditorUtilityTabButtonWidget : SelectedIcon est null` / `UnselectedIcon est null`

**Symptôme :** Le bouton d'onglet avertit de l'absence d'icônes.  
**Cause :** Les emplacements d'icône sélectionnée ou non sélectionnée ne sont pas liés ou les actifs manquent.  
**Solution :** Attribuez et liez les deux emplacements d'icône ; vérifiez que les références soft/object se résolvent correctement.

## 5. `EditorUtilityTask_PrepareUndo : Aucun actif sélectionné`

**Symptôme :** La préparation de l'annulation indique qu'aucun actif n'a été sélectionné.  
**Cause :** La sélection du Content Browser est vide lors de l'exécution de la tâche.  
**Solution :** Sélectionnez d'abord les actifs transactionnels, puis exécutez l'utilitaire de préparation de l'annulation.

## 6. Actifs ignorés car non transactionnels

**Symptôme :** Avertissements indiquant qu'un actif n'est pas transactionnel / n'est pas un `UObject` / n'est pas valide.  
**Cause :** La tâche de préparation de l'annulation n'accepte que les actifs `UObject` transactionnels valides.  
**Solution :** Limitez la sélection aux actifs qui prennent en charge les transactions de l'éditeur ; ignorez les objets non-actifs ou transitoires.

## 7. L'ancien helper de début de transaction est encore utilisé

**Symptôme :** Avertissements de dépréciation faisant référence à `BeginTransactionAndGetSelectedAssets`.  
**Cause :** Les points d'appel utilisent encore le helper déprécié dans UE 5.4.  
**Solution :** Remplacez-le par `GetSelectedAssetsForAction` accompagné d'un `FScopedTransaction` géré par l'appelant, et utilisez `CheckoutAndSaveAssets` pour la persistance.

## 8. Checkout réussi avec des avertissements

**Symptôme :** Code de résultat `SucceededWithCheckoutWarning` ou paramètre de sortie false pour le checkout, tandis que certains fichiers ont été enregistrés.  
**Cause :** Le système de contrôle de source a renvoyé des avertissements lors du checkout.  
**Solution :** Inspectez l'état du contrôle de source pour les actifs, résolvez les verrous/conflits, puis réessayez `CheckoutAndSaveAssets`.

## Documents associés

- [QUICKSTART.md](QUICKSTART.md)
- [UserManual.md](UserManual.md)
- [SettingsReference.md](SettingsReference.md)
- [FAQ.md](FAQ.md)

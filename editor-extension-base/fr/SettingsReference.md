---
lang: fr
title: EditorExtensionBase Settings Reference
audience: [end_user]
owner_ref: plugin:EditorExtensionBase
applies_to:
  component: EditorExtensionBase
contract_ref: plugin:EditorExtensionBase/widget-properties
version:
  since: "1.0"
---
# Référence des paramètres

EditorExtensionBase ne fournit **pas** de classe `UDeveloperSettings` ni d'objet de configuration de projet `.ini`. Les valeurs configurables sont définies sur les sous-classes de l'Editor Utility Widget partagées et sur les objets utilitaires en tant que champs `UPROPERTY`.

## UEditorToolHeaderWidget

| Nom | Type | Défaut | Effet |
| --- | --- | --- | --- |
| `TitleText` | `FText` | défaut du widget | Titre affiché dans l'en-tête. |
| `SubtitleText` | `FText` | défaut du widget | Ligne secondaire sous le titre. |
| Blocs de titre/sous-titre (BindWidget) | références de widget | doivent être liés | Emplacements Slate/UMG requis ; des avertissements sont émis à l'exécution en cas de liaisons manquantes. |

## UEditorUtilityButtonWidget

| Nom | Type | Défaut | Effet |
| --- | --- | --- | --- |
| Propriétés de style du bouton | champs de style du widget | définis par le concepteur | Style visuel du bouton partagé. |
| Bouton / bloc de texte (BindWidget) | références de widget | doivent être liés | Cible du clic et étiquette ; un bouton ou un texte nul génère un avertissement. |

## UEditorUtilityTabButtonWidget

| Nom | Type | Défaut | Effet |
| --- | --- | --- | --- |
| Présentation sélectionnée/non sélectionnée | champs d'état + icône | définis par le concepteur | Contrôle l'apparence de l'onglet sélectionné. |
| Emplacements de bouton/icône (BindWidget) | références de widget | doivent être liés | Des avertissements sont émis en cas d'icônes sélectionnées/non sélectionnées manquantes. |

## UUndoableAssetActionUtility

| Nom | Type | Défaut | Effet |
| --- | --- | --- | --- |
| Description de l'action / champs d'actif | champs utilitaires editanywhere | définis par l'appelant | Décrit l'action d'actif réversible exécutée par l'utilitaire. |
| Code de résultat | enum | exécution | Inclut `SucceededWithCheckoutWarning` lorsque des avertissements de validation accompagnent le succès. |

## UEditorUtilityTask_PrepareUndo

| Nom | Type | Défaut | Effet |
| --- | --- | --- | --- |
| Entrées d'actif sélectionné | champs utilitaires editanywhere | définis par l'appelant | Actifs pris en compte pour la préparation de l'annulation ; les actifs nuls, invalides ou non transactionnels sont ignorés avec des avertissements. |

## Ce qui n'est pas présent

| Surface attendue | Statut |
| --- | --- |
| `UEditorExtensionBaseSettings` DeveloperSettings | pas encore disponible dans le code source |
| `Config/DefaultEditorExtensionBase.ini` | non fourni |
| Panneau des préférences du projet | pas encore disponible |

## Documents associés

- [UserManual.md](UserManual.md) — catalogue comportemental.
- [QUICKSTART.md](QUICKSTART.md) — premier appel de l'assistant de sélection.
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md) — avertissements BindWidget et de sélection.

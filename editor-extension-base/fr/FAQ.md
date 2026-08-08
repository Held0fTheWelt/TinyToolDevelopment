# FAQ

## À quoi sert Editor Extension Base ?

Il s'agit d'une base commune pour les plugins d'interface utilisateur d'éditeur de Tiny Tool Development : des widgets utilitaires d'éditeur réutilisables, des assistants de sélection / validation / enregistrement, des utilitaires de préparation de l'annulation et un module de macros d'exécution léger.

## S'agit-il d'un outil destiné aux utilisateurs finaux ?

Non. Il ne crée pas de menu de produit Tiny Tools propre. Les plugins de fonctionnalités l'utilisent comme dépendance.

## Quels modules Unreal charge-t-il ?

`EditorExtensionBase` (Éditeur) et `EditorExtensionRuntimeBase` (Exécution), tels que déclarés dans `EditorExtensionBase.uplugin`.

## Requiert-il d'autres plugins Tiny Tool ?

Non. Il nécessite le plugin **Editor Scripting Utilities** d'Unreal (activé dans le descripteur). Les plugins de scène, d'IA ou d'autres plugins Tiny Tool sont des consommateurs optionnels, pas des exigences d'installation.

## Comment lire la sélection actuelle du Content Browser ?

Appelez `UEditorManagerUtilityLibrary::GetSelectedAssetsForAction` depuis Blueprint ou C++ après avoir activé le plugin. Consultez [QUICKSTART.md](QUICKSTART.md).

## Comment dois-je ouvrir une transaction d'annulation ?

Possédezz une `FScopedTransaction` dans l'appelant. `BeginTransactionAndGetSelectedAssets` est déprécié depuis Unreal Engine 5.4.

## Pourquoi mes Blueprints de widget génèrent-ils des avertissements au moment de l'exécution ?

Les slots bindés via BindWidget, tels que les boutons, les blocs de texte ou les icônes, sont nuls. Assurez-vous que le Blueprint du widget utilitaire lie chaque slot requis déclaré sur la classe de base C++.

## CheckoutAndSaveAssets réussit-il toujours ?

Non. Il rapporte les résultats de la validation et de l'enregistrement via des paramètres de sortie booléens. Les échecs de contrôle de version ou d'enregistrement y sont signalés ainsi que dans les codes de résultat associés tels que `SucceededWithCheckoutWarning`.

## Existe-t-il des DeveloperSettings à l'échelle du projet ?

Non. Les champs configurables sont situés sur les widgets et utilitaires partagés. Consultez [SettingsReference.md](SettingsReference.md).

## Le package inclut-il des logiciels tiers ?

Non. Consultez [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md).

## Quelles versions du moteur sont prises en charge ?

Le descripteur du package cible Unreal Engine 5.4.0 sur Win64, Linux et Mac pour la liste autorisée du module éditeur.

## Où puis-je obtenir de l'aide ?

Utilisez `mailto:support@tiny-tool-development.com` (descripteur `SupportURL`) ou le lien de support sur la page produit Fab.

## Puis-je utiliser uniquement les macros d'exécution sans le module éditeur ?

Oui. `EditorExtensionRuntimeBase` est un module d'exécution distinct conçu pour rester léger en dépendances pour les consommateurs non-éditeur.

## PrepareUndo modifie-t-il les assets immédiatement ?

Il prépare les options d'annulation pour les assets transactionnels sélectionnés et ignore les sélections invalides avec des avertissements. La persistance passe toujours par les assistants de validation/enregistrement lorsque vous écrivez intentionnellement.

## Les macros d'exécution peuvent-elles extraire des modules réservés à l'éditeur ?

Non. Gardez la dépendance `EditorExtensionRuntimeBase` légère. Les widgets éditeur et les assistants de sélection restent dans le module Éditeur.

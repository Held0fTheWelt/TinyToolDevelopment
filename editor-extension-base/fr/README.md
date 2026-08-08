# Documentation de base de l'extension de l'éditeur

Editor Extension Base est une fondation partagée de l'éditeur Unreal pour les plugins d'interface utilisateur de Tiny Tool Development. Il fournit des widgets utilitaires de l'éditeur réutilisables, des assistants de sélection / validation / enregistrement du Content Browser, des utilitaires de préparation à l'annulation et un module de macros runtime léger.

Public cible : auteurs de plugins et équipes ayant besoin d'une expérience utilisateur (UX) de l'éditeur cohérente sans copier le code boilerplate des widgets et de la sélection. Ce package est une couche de support — il n'enregistre pas son propre menu produit Tiny Tools.

## Fonctionnalités

- Widgets utilitaires de l'éditeur partagés (en-tête, bouton, bouton d'onglet, mise en page à deux panneaux).
- `UEditorManagerUtilityLibrary` pour la sélection, la validation/l'enregistrement et les assistants du monde de l'éditeur.
- Utilitaires de préparation à l'annulation et d'actions sur les assets annulables.
- Module runtime (`EditorExtensionRuntimeBase`) avec des macros partagées pour les consommateurs non-éditeur.

## Prise en main

1. Activez le plugin (et les Editor Scripting Utilities) — consultez [QUICKSTART.md](QUICKSTART.md).
2. Appelez `GetSelectedAssetsForAction` depuis un widget utilitaire de l'éditeur ou un outil d'éditeur en C++.
3. Lisez [UserManual.md](UserManual.md) et [SettingsReference.md](SettingsReference.md) pour le catalogue complet.

## Fichiers associés

- [../README.md](../README.md) — aperçu du produit.
- [../CHANGELOG.md](../CHANGELOG.md) — historique des versions.
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md) · [FAQ.md](FAQ.md) · [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md)

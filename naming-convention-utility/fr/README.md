<!-- doc-provenance: product-facts.yml reconciled 2026-07-04; source AKDB:plugins/NamingConventionUtility/architecture.md -->
# Documentation de Naming Convention Utility

Naming Convention Utility est un plugin d'éditeur Unreal Engine permettant d'appliquer des préfixes et suffixes d'assets cohérents dans les dossiers sélectionnés du Content Browser. Il découvre les types d'assets, construit un plan de renommage, valide les noms cibles, prévisualise les modifications prévues dans un étal de travail (workbench) ancrable et applique les renommages d'assets Unreal sélectionnés via les outils d'assets de l'éditeur.

Ce dossier contient la documentation complète livrée avec le plugin.

## Commencez ici

- [BUYER_GUIDE.md](BUYER_GUIDE.md) : vue d'ensemble pour les acheteurs, cas d'utilisation et adéquation.
- [QUICKSTART.md](QUICKSTART.md) : guide rapide de l'installation au résultat.
- [UserManual.md](UserManual.md) : flux de travail complet pour la configuration, l'analyse, l'édition, la création de rapports et l'application des conventions.
- [FAQ.md](FAQ.md) : questions et réponses prêtes pour Fab.

## Référence

- [SettingsReference.md](SettingsReference.md) : paramètres, champs du DataAsset et configurations recommandées.
- [TechnicalOverview.md](TechnicalOverview.md) : architecture et modèle de sécurité pour les mainteneurs.
- [CodeDocumentation.md](CodeDocumentation.md) : structure du code, contrats et points d'extension.
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md) : problèmes courants et solutions.
- [ReleaseChecklist.md](ReleaseChecklist.md) : liste de contrôle de validation avant livraison.

## Ressources incluses

- `../Readme.pdf` : fichier lisez-moi traditionnel.
- `../Content/Editor/Data/DA_NamingConvention.uasset` : DataAsset de conventions par défaut.
- `../Content/Editor/Data/DT_NamingConvention.uasset` : exemple de DataTable.
- `../Resources/NamingConvention.csv` : référence d'importation CSV.
- `../Resources/NamingConvention.json` : référence d'importation JSON.
- `../Resources/NamingConvention_EpicRecommended.csv` : référence d'importation du profil recommandé par Epic.
- `../Resources/NamingConvention_TinyLegacy.csv` : référence d'importation du profil hérité 1.0.x.
- `../Resources/FileTypeValues.txt` : référence des énumérations de types de fichiers.
- `../Resources/ToolTypeValues.txt` : référence des types d'outils DataTable.

## Flux de travail rapide

1. Activez le plugin et redémarrez l'éditeur si nécessaire.
2. Ouvrez les Project Settings et vérifiez le DataAsset de conventions sélectionné.
3. Ouvrez le Naming Workbench depuis le menu du plugin ou l'action contextuelle d'un dossier.
4. Choisissez **Epic Recommended**, **Tiny Legacy** ou **Project Custom**.
5. Analysez le dossier, inspectez la conformité, les motifs d'exclusion et les chemins cibles.
6. Sélectionnez les lignes acceptées à appliquer, puis exportez un rapport ou appliquez après révision.
7. Enregistrez les assets/paquets affectés une fois qu'Unreal a terminé le renommage.

## Modèle de sécurité

Le plugin traite les opérations de renommage comme des actions à fort impact. Avant d'appeler les outils de renommage d'Unreal, il construit un plan et exclut les entrées risquées.

Le plan vérifie :

- Les types d'assets non pris en charge.
- Les règles de convention manquantes.
- Les noms générés vides ou invalides.
- Les chemins d'objets cibles invalides.
- Les assets cibles déjà existants.
- Les paquets cibles déjà existants sur le disque.
- Les doublons cibles au sein du même lot.
- Les assets sources dupliqués sélectionnés via des dossiers chevauchants.

Le Workbench affiche un aperçu avant d'appliquer le plan, protège l'application avec le hash du plan révisé et écrit des rapports JSON/Markdown sous `Saved/NamingConventionUtility/Reports/`.

## Ce que l'outil modifie

Le plugin me renomme les assets Unreal via `IAssetTools::RenameAssets`.

Il ne fait pas :

- Renommer des fichiers bruts en dehors du système d'assets.
- Modifier des fichiers sources importés.
- Modifier des noms de classes en C++.
- Modifier des noms de classes Blueprint dans le code généré.
- Décider de la politique de nommage de votre studio à votre place.

## Familles de nommage par défaut

Le DataAsset par défaut inclut des préfixes Unreal courants tels que :

- `T_`, `T_N_`, `T_D_` pour les textures.
- `M_`, `MI_`, `MF_` pour les matériaux.
- `SM_`, `SK_`, `SKEL_` pour les maillages et squelettes.
- `BP_`, `BPI_`, `BPF_`, `WB_` pour les Blueprints et widgets.
- `NS_`, `NE_`, `PS_` pour les effets.
- `DT_`, `CT_`, `CF_`, `CV_`, `CLC_` pour les données et courbes.

Le Workbench inclut également :

- `epic_recommended` : préfixes alignés sur Epic avec remappages de collisions documentés.
- `tiny_legacy` : le style rétrocompatible par défaut 1.0.x.
- `project_custom` : vos règles DataAsset personnalisées.

Vous pouvez modifier ou remplacer le DataAsset selon vos normes. Le Workbench peut également copier un profil intégré dans le DataAsset du projet.

## Limitations importantes

- La détection de sous-types de textures combine des paramètres de compression et des jetons de nom.
- Les types d'assets non reconnus par le plugin sont ignorés.
- Unreal peut afficher des boîtes de dialogue ou échouer en raison de références, du contrôle de code source ou de paquets verrouillés.
- Le renommage de grands dossiers doit être révisé avec soin.

## Note légale

Naming Convention Utility est un outil de productivité. Il aide à appliquer des normes mais ne garantit pas qu'une norme soit adaptée à tous les studios ou pipelines.

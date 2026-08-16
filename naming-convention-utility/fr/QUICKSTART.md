<!-- doc-provenance: product-facts.yml reconciled 2026-07-04; source AKDB:plugins/NamingConventionUtility/architecture.md -->
# Guide de démarrage rapide

Ce guide vous accompagne de l'installation à un résultat réel : des assets dans un dossier me renommés selon vos règles de nommage après une étape d'aperçu et de confirmation. Naming Convention Utility fonctionne de manière autonome.

## Ce que vous obtiendrez après ce guide

Les règles de nommage révisées, un dossier analysé dans le Naming Workbench et des assets sélectionnés renommés (par exemple `OldWall` -> `SM_OldWall`) via le système d'assets d'Unreal.

## Prérequis

- Éditeur Unreal Engine 5 avec un projet contenant des assets de contenu à renommer.
- Aucun logiciel tiers, compte ou runtime supplémentaire n'est requis. Voir [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md).

## 1. Installation et activation

1. Ajoutez **Naming Convention Utility** depuis votre bibliothèque Fab à votre projet ou installez-le dans le moteur.
2. Ouvrez **Edit > Plugins**, activez **Naming Convention Utility** et redémarrez l'éditeur.

## 2. Révision des règles

1. Ouvrez **Edit > Project Settings > Plugins > Naming Convention Utility**.
2. Le paramètre clé est **NamingConventionDataAssetPath**, pointant par défaut sur le fichier fourni `/NamingConventionUtility/Editor/Data/DA_NamingConvention`.
3. Ouvrez ce DataAsset pour consulter les règles personnalisées. Chaque règle possède un `FileTypeIdentifier`, `NamingsToRemove`, `PreFix` et `PostFix`.

Exemple :

```text
FileTypeIdentifier = FTC_STATICMESH
NamingsToRemove    = ["StaticMesh_", "Mesh_"]
PreFix             = "SM_"
PostFix            = ""
```

Recommandation : dupliquez le DataAsset par défaut dans votre dossier de contenu de projet et faites pointer `NamingConventionDataAssetPath` sur cette copie.

## 3. Analyse dans le Naming Workbench

1. Ouvrez le **Naming Workbench** depuis le menu du plugin ou via le clic droit sur un dossier du Content Browser.
2. Choisissez un profil :
   - **Epic Recommended** pour une base alignée sur Epic.
   - **Tiny Legacy** pour le style par défaut 1.0.x.
   - **Project Custom** pour votre DataAsset configuré.
3. Cliquez sur **Scan**. Le workbench affiche les renommages acceptés, les assets déjà conformes, les assets ignorés et le pourcentage de conformité.

## 4. Appliquer un renommage réel

1. Trouvez un maillage statique nommé `OldWall` dans les lignes acceptées.
2. Confirmez que le chemin cible se termine par `SM_OldWall.SM_OldWall`.
3. Laissez la ligne sélectionnée.
4. Optionnel : cliquez sur **Export** pour écrire un rapport.
5. Cliquez sur **Apply** et confirmez.

Résultat attendu : `OldWall` devient `SM_OldWall` ; Unreal termine le renommage. Enregistrez les paquets concernés.

## 5. Motifs d'exclusion courants

Un renommage prévu est ignoré lorsque le type d'asset n'est pas pris en charge, qu'aucune règle ne correspond, que le nom est déjà conforme, que le nom généré est invalide ou que le nom cible existe déjà.

## 6. Étapes suivantes

- Flux de travail complet, champs de règles, conversion de DataTable : [UserManual.md](UserManual.md).
- Paramètres : [SettingsReference.md](SettingsReference.md).
- Problèmes : [TROUBLESHOOTING.md](TROUBLESHOOTING.md) et [FAQ.md](FAQ.md).

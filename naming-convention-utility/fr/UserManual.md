<!-- doc-provenance: product-facts.yml reconciled 2026-07-04; source AKDB:plugins/NamingConventionUtility/architecture.md -->
# Manuel de l'utilisateur

Ce manuel explique comment configurer et utiliser Naming Convention Utility dans Unreal Editor.

## Installation

1. Ajoutez le plugin au dossier `Plugins` de votre projet ou installez-le via Fab.
2. Activez **Naming Convention Utility** dans **Edit > Plugins**.
3. Redémarrez l'éditeur si demandé.

## Configuration du DataAsset

Ouvrez **Edit > Project Settings > Plugins > Naming Convention Utility**.

Le paramètre clé est :

```text
NamingConventionDataAssetPath
```

Par défaut :

```text
/NamingConventionUtility/Editor/Data/DA_NamingConvention.DA_NamingConvention
```

Vous pouvez :

- Utiliser l'asset par défaut.
- Le dupliquer dans votre projet.
- Modifier les préfixes et suffixes.
- Copier un profil du Workbench dans votre DataAsset.
- Convertir une DataTable compatible en DataAsset.

## Champs des règles

Chaque règle contient :

- `FileTypeIdentifier` : la catégorie d'asset Unreal ciblée.
- `NamingsToRemove` : chaînes retirées avant d'ajouter préfixe/suffixe.
- `PreFix` : préfixe ajouté.
- `PostFix` : suffixe ajouté.

Exemple :

```text
FileTypeIdentifier = FTC_STATICMESH
NamingsToRemove = ["StaticMesh_", "Mesh_"]
PreFix = "SM_"
PostFix = ""
```

`OldWall` devient `SM_OldWall`.

## Naming Workbench

Le Naming Workbench est l'interface principale pour la révision, l'édition et l'application des règles.

Permet de :

- Sélectionner un dossier.
- Choisir `epic_recommended`, `tiny_legacy` ou `project_custom`.
- Analyser les assets de façon récursive.
- Vérifier les lignes acceptées, conformes ou ignorées.
- Inspecter les chemins cibles.
- Exporter des rapports JSON/Markdown.
- Appliquer les lignes sélectionnées de manière sécurisée via un hash de plan.

## Application rapide via le Content Browser

L'action sur le dossier du Content Browser reste disponible :

1. Clic droit sur un dossier.
2. Choisissez **Apply Naming Conventions**.
3. Révisez la boîte de dialogue d'aperçu.
4. Confirmez pour lancer le renommage.
5. Enregistrez les paquets affectés.

## Aperçu et motifs d'exclusion

L'aperçu résume :

- Nombre d'assets analysés.
- Nombre de renommages prévus.
- Nombre d'assets ignorés.
- Paires ancien nom / nouveau nom.
- Motifs d'exclusion.

## Rapports d'audit

L'exportation et l'application génèrent des rapports sous :

```text
Saved/NamingConventionUtility/Reports/
```

## Conversion de DataTable

Le plugin peut convertir une DataTable compatible dans le DataAsset configuré.

Structure de ligne attendue :

```text
FNamingConventionTableInformation
```

Champs :

- `FileType`
- `ToolType`
- `Value`

Types d'outils pris en charge :

- `NCTT_TOREMOVE`
- `NCTT_PREFIX`
- `NCTT_POSTFIX`

## Détection du sous-type de texture

La détection utilise la compression `TC_Normalmap` et des mots-clés de nom (`normal`, `albedo`, `roughness`, `metallic`, etc.).

## Annulation et contrôle de code source

Le renommage d'assets affecte les paquets et les références. Testez d'abord sur un petit dossier, vérifiez les redirecteurs générés et enregistrez les paquets modifiés.

## Suppression du plugin

Avant de supprimer le plugin :

1. Terminez ou annulez les opérations en attente.
2. Enregistrez les paquets.
3. Désactivez le plugin et redémarrez.

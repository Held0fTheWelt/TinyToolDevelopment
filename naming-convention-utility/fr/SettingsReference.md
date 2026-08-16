<!-- doc-provenance: product-facts.yml reconciled 2026-07-04; source AKDB:plugins/NamingConventionUtility/architecture.md -->
# Référence des paramètres

Naming Convention Utility stocke ses paramètres au niveau du projet dans `UNamingConventionUtility_Settings`.

## Objet de paramètres

Fichier source :

```text
Source/NamingConventionUtility/Public/NamingConventionUtility_Settings.h
```

Emplacement dans l'éditeur :

```text
Edit > Project Settings > Plugins > Naming Convention Utility
```

## NamingConventionDataAssetPath

Type :

```text
FSoftObjectPath
```

Par défaut :

```text
/NamingConventionUtility/Editor/Data/DA_NamingConvention.DA_NamingConvention
```

Objectif :

- Pointe vers le DataAsset contenant les règles de renommage.
- Utilisé par le flux de travail de renommage de dossier.
- Utilisé comme cible par la conversion de DataTable.

## bConfirmBeforeApplyingConventions

Par défaut :

```text
true
```

Objectif :

- Affiche un aperçu et demande une confirmation avant d'appliquer les renommages par lot.

## bFixRedirectorsAfterRename

Par défaut :

```text
true
```

Objectif :

- Tente de corriger les redirecteurs dans les dossiers sélectionnés après les renommages.

## DataAsset : NamingConventions

Chaque entrée définit la règle pour un `EFileTypeIdentifier`.

Champs :

- `FileTypeIdentifier` : type d'asset ciblé.
- `NamingsToRemove` : anciens fragments à retirer.
- `PreFix` : préfixe à ajouter.
- `PostFix` : suffixe à ajouter.

## Profils du Workbench

Le Workbench propose trois choix :

- `epic_recommended` : règles en lecture seule alignées sur Epic.
- `tiny_legacy` : règles en lecture seule compatibles 1.0.x.
- `project_custom` : le fichier défini par `NamingConventionDataAssetPath`.

## Rapports

Générés sous :

```text
Saved/NamingConventionUtility/Reports/
```

<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/CodeCopyrightEditor/architecture.md -->
# Référence des paramètres

Les paramètres de Code Copyright Editor sont disponibles sous :

```text
Project Settings > Plugins > Code Copyright Editor
```

La fenêtre de l'éditeur expose également les actions de modèle et de flux de travail les plus importantes.

## Identité

| Paramètre | Valeur par défaut | Utilisé par |
| --- | --- | --- |
| `OwnerName` | `Your Company or Name` | `{OwnerName}`, `{CopyrightText}`, rapports |
| `ContactEmail` | Vide | `{ContactEmail}` |
| `ProductNameFallback` | `PluginProject` | `{ProductName}` lorsqu'aucun nom d'affichage de plugin n'est trouvé |
| `CopyrightStartYear` | `2025` | `{Year}`, `{CopyrightText}` |

`{Year}` s'affiche comme l'année de début lorsqu'elle est égale à l'année en cours. Si l'année diffère, il s'affiche sous forme de plage telle que `2025-2026`.

## Licence

| Paramètre | Valeur par défaut | Utilisé par |
| --- | --- | --- |
| `LicenseName` | `Fab Standard End User License Agreement` | `{LicenseName}` |
| `LicenseUrl` | `https://www.fab.com/eula` | `{LicenseUrl}` |
| `LicenseIdentifier` | `LicenseRef-Fab-Standard-EULA` | `{LicenseIdentifier}`, rapports |

Utilisez des identifiants SPDX standard pour les licences standard, par exemple `MIT` ou `Apache-2.0`. Utilisez `LicenseRef-*` pour les licences personnalisées ou spécifiques aux places de marché comme un CLUF de produit.

## Modèles

| Paramètre | Objectif |
| --- | --- |
| `SourceNoticeTemplate` | En-tête affiché dans les fichiers sources. |
| `ProjectSettingsNoticeTemplate` | Notice affichée dans le champ de droit d'auteur du projet Unreal. |

## Portée (Scope)

| Paramètre | Valeur par défaut | Objectif |
| --- | --- | --- |
| `ScanRootPaths` | `Source`, `Plugins` | Dossiers analysés par `Scan Files`. |
| `SourceFileExtensions` | `.h`, `.hpp`, `.hh`, `.inl`, `.c`, `.cc`, `.cpp`, `.cxx`, `.cs`, `.usf`, `.ush` | Extensions traitées comme fichiers sources. |
| `ExcludedPathFragments` | `.git`, `.vs`, `Binaries`, `Content`, `DerivedDataCache`, `External`, `Intermediate`, `Resources`, `Saved`, `ThirdParty` | Fragments de dossier/chemin ignorés lors des analyses. |
| `ExcludedFilePaths` | Vide par défaut | Fichiers exacts relatifs au projet ignorés lors des analyses. |
| `ExcludedFilePatterns` | `*.generated.h` | Motifs génériques ignorés lors des analyses. |

## Protection

| Paramètre | Valeur par défaut | Objectif |
| --- | --- | --- |
| `ProtectForeignNotices` | Activé | Empêche le texte de notice inconnu d'être réécrit automatiquement. |
| `TreatUnrealDefaultNoticesAsReplaceable` | Activé | Permet de remplacer les notices d'espace réservé/par défaut d'Unreal. |
| `OwnNoticeMarkers` | Nom du propriétaire, identifiant de licence, texte du CLUF Fab, texte d'espace réservé Unreal | Identifie les notices appartenant à ce projet. |
| `ProtectedNoticeMarkers` | Marqueurs de droit d'auteur de tiers et d'Epic | Identifie les notices qui ne doivent pas être réécrites automatiquement. |

## Baseline recommandée

Pour la plupart des produits de plugin Fab :

- Conservez `ProtectForeignNotices` activé.
- Conservez `TreatUnrealDefaultNoticesAsReplaceable` activé.
- Conservez `ThirdParty`, `External`, `Binaries`, `Intermediate` et `Saved` exclus.
- Utilisez `LicenseRef-Fab-Standard-EULA` pour les produits sous CLUF Fab.
- Conservez les lignes SPDX près du haut du modèle de source.
- Utilisez `{FileMetadataBlock}` pour un contexte optionnel au niveau du fichier.

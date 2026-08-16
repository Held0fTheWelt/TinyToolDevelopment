<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/CodeCopyrightEditor/architecture.md -->
# Manuel utilisateur

Ce manuel explique le flux de travail complet dans l'éditeur pour Code Copyright Editor.

## Objectif

Code Copyright Editor gère le texte de la notice de droit d'auteur à deux endroits :

- La notice de droit d'auteur au niveau du projet Unreal Engine.
- Les en-têtes de fichiers sources dans les dossiers configurés du projet et des plugins.

Le plugin est conçu pour des réécritures de sources contrôlées. Il analyse d'abord, affiche un aperçu, permet à l'utilisateur de sélectionner des fichiers et n'écrit les fichiers modifiables sélectionnés qu'après confirmation.

## Ouvrir l'outil

Après avoir activé le plugin, ouvrez :

```text
Tools > Code Tools > Code Copyright Editor
```

Le plugin expose également sa configuration sous :

```text
Project Settings > Plugins > Code Copyright Editor
```

## Flux de travail principal

1. Configurez l'identité, la licence, le modèle, la portée et les paramètres de protection.
2. Enregistrez les paramètres.
3. Mettez à jour la notice des paramètres du projet si nécessaire.
4. Analysez la base de code.
5. Examinez les badges de statut et les aperçus.
6. Ajoutez des métadonnées optionnelles par fichier.
7. Sélectionnez uniquement les fichiers qui doivent être réécrits.
8. Appliquez aux fichiers sélectionnés.
9. Lancez une nouvelle analyse pour vérifier.
10. Exportez les rapports ou exécutez le commandlet en CI.

L'analyse n'écrit jamais dans les fichiers sources. L'application réécrit uniquement les fichiers cochés classés comme modifiables.

## Onglets de l'éditeur

La fenêtre principale de l'éditeur est organisée en onglets ciblés :

| Onglet | Objectif |
| --- | --- |
| `Configure` | Modifier les modèles, paramètres de propriétaire/licence, portée d'analyse, règles de protection et notice du projet. |
| `Scan & Review` | Exécuter les analyses, inspecter les statuts de fichiers, sélectionner les fichiers modifiables, exclure des fichiers et comparer les notices existantes/proposées. |
| `File Metadata` | Ajouter ou effacer des informations et descriptions de fichiers sélectionnés affichées par les jetons de métadonnées. |
| `Apply & Reports` | Confirmer les réécritures sélectionnées et exporter le dernier rapport d'analyse JSON de l'éditeur. |
| `Help` | Lire le guide de flux de travail intégré et la légende des statuts. |

## Valeurs de statut

| Statut | Signification | Comportement lors de l'application |
| --- | --- | --- |
| `OK` | Le fichier correspond déjà au modèle rendu. | Non requis. |
| `MISSING` | Aucune notice compatible n'a été trouvée. | Peut être insérée si activée. |
| `REPLACE` | Une notice possédée ou un espace réservé Unreal peut être remplacé. | Peut être réécrite. |
| `PROTECTED` | Une notice étrangère, Epic ou tierce a été trouvée. | Non réécrite automatiquement. |
| `CONFLICT` | Des marqueurs possédés et protégés apparaissent ensemble. | Révision manuelle requise. |
| `EXCLUDED` | Le fichier correspond à une règle d'exclusion. | Non traité. |
| `READ_ERROR` | Le fichier n'a pas pu être lu. | Non traité. |
| `WRITE_ERROR` | Le fichier n'a pas pu être enregistré. | Non traité. |
| `UPDATED` | Le fichier a été écrit lors de la dernière passe d'application. | Lancez une nouvelle analyse pour vérifier. |

## Métadonnées par fichier

Les métadonnées par fichier ajoutent du contexte à un seul fichier sans modifier le modèle global.

Métadonnées disponibles :

- `File Information`
- `Description`

Flux de travail recommandé :

1. Analysez les fichiers.
2. Sélectionnez un fichier.
3. Saisissez des informations ou une description de fichier.
4. Cliquez sur `Save File Metadata`.
5. Assurez-vous que le modèle contient `{FileMetadataBlock}`.
6. Examinez l'aperçu.
7. Appliquez le fichier si la notice rendue est correcte.

`Clear File Metadata` supprime les métadonnées enregistrées pour le fichier sélectionné.

## Appliquer les éléments sélectionnés (Apply Selected)

Avant d'appliquer, l'éditeur demande une confirmation. Les fichiers protégés et en conflit restent inchangés.

Après l'application, l'outil lance une nouvelle analyse et affiche :

- Le résultat de l'application.
- Le résultat de l'analyse actuelle.
- Les lignes de statut mises à jour.

Utilisez le contrôle de source avant des réécritures en masse. Pour une sécurité renforcée lors du premier passage, activez `Create Backup Before Write`.

## Ce que le plugin ne fait pas

Code Copyright Editor ne fait pas ce qui suit :

- Décider de la propriété juridique.
- Conférer des droits de licence.
- Valider des licences tierces.
- Remplacer un conseil juridique.
- Réécrire automatiquement les notices protégées.
- S'exécuter dans des jeux paquetés.

Il fournit un flux de travail technique cohérent pour les notices, les rapports et les vérifications CI.

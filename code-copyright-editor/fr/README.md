<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/CodeCopyrightEditor/architecture.md -->
# Documentation de Code Copyright Editor

Code Copyright Editor maintient les en-têtes de code source cohérents dans un projet Unreal Engine. Il peut mettre à jour la notice de droit d'auteur des paramètres du projet (Project Settings), analyser l'arborescence des sources, réécrire les fichiers sélectionnés et s'exécuter comme une vérification CI sans interface.

Ce dossier contient la documentation complète livrée avec le plugin.

## Commencer ici

- [QUICKSTART.md](QUICKSTART.md) : installation, première analyse et passage d'application réel avec résultats attendus.
- [UserManual.md](UserManual.md) : flux de travail complet de l'éditeur et utilisation de l'interface.
- [SettingsReference.md](SettingsReference.md) : chaque paramètre, valeurs par défaut et configuration initiale recommandée.
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md) : problèmes fréquents et solutions.
- [FAQ.md](FAQ.md) : questions et réponses pour les acheteurs et ressources Fab.
- [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md) : déclaration sur les logiciels tiers (aucun inclus).

## Flux de travail rapide dans l'éditeur

1. Ouvrez **Tools > Code Tools > Code Copyright Editor**.
2. Modifiez les modèles de notices de source et de projet.
3. Utilisez **Scan Files** pour classifier la base de code sans écrire de fichiers.
4. Examinez les badges de statut et sélectionnez uniquement les fichiers à réécrire.
5. Ajoutez des informations et descriptions optionnelles par fichier pour les fichiers sélectionnés.
6. Utilisez **Apply Selected** après avoir examiné l'aperçu.

## Jetons de modèle rapides

Jetons courants :

- `{CopyrightText}`
- `{OwnerName}`
- `{ContactEmail}`
- `{ProductName}`
- `{ModuleName}`
- `{FileName}`
- `{RelativeFilePath}`
- `{Year}`
- `{LicenseName}`
- `{LicenseUrl}`
- `{LicenseIdentifier}`
- `{FileInformation}`
- `{FileDescription}`
- `{FileMetadataBlock}`

Pour des en-têtes conformes REUSE/SPDX, conservez ces deux balises près du haut du modèle :

```text
/* {CopyrightText}
 * SPDX-FileCopyrightText: {CopyrightText}
 * SPDX-License-Identifier: {LicenseIdentifier}
```

## Commandlet

Exécutez le même scanner depuis la CI ou un terminal local :

```powershell
UnrealEditor-Cmd.exe "D:\PluginProjectGit\PluginProject.uproject" -run=CodeCopyrightCheck -unattended -nop4 -nosplash -NoShaderCompile -ReportDir="Saved\CodeCopyrightEditor\Reports"
```

Commutateurs utiles :

- `-Fix` : réécrire les fichiers modifiables avant de produire le rapport final.
- `-ReportDir=<Path>` : écrire les rapports dans un répertoire relatif au projet ou absolu.
- `-FailOnProtected` : traiter les notices étrangères protégées comme des échecs CI.
- `-NoJson`, `-NoSpdx`, `-NoReuse` : ignorer les formats de rapport individuels.
- `-NoFail` : écrire les rapports mais toujours retourner le code de sortie `0`.

Par défaut, la CI échoue lorsque des fichiers seraient modifiés, que des conflits existent ou que des fichiers n'ont pas pu être lus/écrits. Les notices tierces protégées sont signalées mais ne font pas échouer le build à moins que `-FailOnProtected` ne soit défini.

## Rapports rapides

Le commandlet écrit :

- `CodeCopyrightReport.json` : résumé d'analyse lisible par machine.
- `CodeCopyrightReport.spdx` : rapport au style SPDX 2.3 Tag/Value.
- `REUSE-Report.md` : rapport de révision REUSE/SPDX lisible par l'homme.

## Note juridique

Code Copyright Editor aide à appliquer et réviser le texte des notices de manière cohérente. Il ne décide pas de la propriété juridique, ne valide pas les licences tierces, ne confère aucun droit et ne remplace pas un conseil juridique.

## Références

- Spécification REUSE 3.3 : https://reuse.software/spec-3.3/
- Spécification SPDX 2.3 : https://spdx.github.io/spdx-spec/v2.3/
- API UCommandlet Unreal Engine : https://dev.epicgames.com/documentation/en-us/unreal-engine/API/Runtime/Engine/Commandlets/UCommandlet

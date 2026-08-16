<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/CodeCopyrightEditor/architecture.md -->
# FAQ (Foire aux questions)

## À quoi sert Code Copyright Editor ?

Code Copyright Editor aide les développeurs Unreal Engine à gérer des notices de droit d'auteur cohérentes dans les paramètres du projet et les fichiers sources. Il peut analyser, prévisualiser, mettre à jour et rapporter les en-têtes de fichiers sources dans un flux de travail unique de l'éditeur.

## Le plugin affecte-t-il le code de jeu à l'exécution ?

Non. Code Copyright Editor est un outil réservé à l'éditeur. Il est destiné aux flux de travail de développement, de révision, de documentation et de CI.

## Peut-il mettre à jour une base de code entière automatiquement ?

Oui, mais uniquement après analyse et révision. L'éditeur montre quels fichiers peuvent être modifiés, quels fichiers sont protégés et à quoi ressemblera le remplacement proposé avant d'appliquer les modifications.

## Protège-t-il les notices de tiers ou d'Epic ?

Oui. Le scanner est conçu pour protéger les notices étrangères, d'Epic et de tiers contre une réécriture automatique. Les fichiers protégés et en conflit doivent être révisés manuellement.

## Puis-je personnaliser le modèle de droit d'auteur ?

Oui. Vous pouvez modifier le modèle de notice des fichiers sources et le modèle de notice des paramètres du projet. Des jetons tels que le nom du produit, le chemin du fichier, l'année, l'identifiant de licence et la description par fichier peuvent être affichés automatiquement.

## Prend-il en charge les flux de travail SPDX ou REUSE ?

Le plugin fournit des modèles et des rapports orientés REUSE/SPDX. Ces rapports sont destinés à soutenir les flux de travail de révision et de CI, mais ne constituent pas une certification juridique.

## Existe-t-il un commandlet pour la CI ?

Oui. Le commandlet `CodeCopyrightCheck` inclus peut analyser le projet, corriger éventuellement les fichiers modifiables, écrire des rapports et faire échouer la CI lorsque les notices de droit d'auteur ne sont pas synchronisées.

## Remplace-t-il un conseil juridique ?

Non. Il aide à appliquer et réviser le texte des notices de manière cohérente. Il ne décide pas de la propriété juridique, ne valide pas les licences tierces et ne fournit pas de conseil juridique.

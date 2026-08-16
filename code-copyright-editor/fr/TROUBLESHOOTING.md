<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/CodeCopyrightEditor/architecture.md -->
# Dépannage

Cette page répertorie les problèmes courants et les solutions pratiques.

## L'outil n'apparaît pas dans le menu Tools

Vérifiez :

- Le plugin est activé pour le projet.
- Unreal Editor a été redémarré après l'activation du plugin.
- Le plugin a été compilé pour la version actuelle d'Unreal Engine.

Chemin de menu attendu :

```text
Tools > Code Tools > Code Copyright Editor
```

## La page dans Project Settings est manquante

Vérifiez :

- Le module du plugin s'est chargé avec succès.
- Le projet utilise un build éditeur, pas un build d'exécution paqueté.
- Le plugin est installé dans le dossier de plugins du projet ou du moteur.

## L'analyse ne trouve aucun fichier

Vérifiez :

- `ScanRootPaths` contient des dossiers qui existent.
- Les fichiers utilisent des extensions prises en charge.
- Les fragments de chemin exclus ne sont pas trop larges.

## Les fichiers sont marqués PROTECTED

Le scanner a trouvé un texte ressemblant à une notice qui ne correspond pas aux marqueurs possédés, ou il a correspondu à des marqueurs protégés.

Options de résolution :

- Laissez le fichier inchangé s'il s'agit de code tiers ou Epic.
- Ajoutez le dossier du fournisseur aux exclusions.
- Ajoutez un marqueur possédé uniquement si le fichier appartient vraiment à votre projet.

## Erreurs d'écriture (Write Errors)

Causes fréquentes :

- Le fichier est en lecture seule.
- Le fichier est verrouillé par un autre processus.
- Un extrait de contrôle de source est requis.
- Le compte utilisateur ne dispose pas des permissions d'écriture.

Réglez l'état du fichier, puis relancez l'analyse/application.

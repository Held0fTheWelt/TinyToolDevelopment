<!-- doc-provenance: product-facts.yml reconciled 2026-07-04; source AKDB:plugins/NamingConventionUtility/architecture.md -->
# FAQ (Foire aux questions)

## Le plugin renomme-t-il les assets ou génère-t-il seulement des rapports ?

Il renomme réellement les assets après votre confirmation via `IAssetTools::RenameAssets`.

## Renomme-t-il les dossiers ?

Non. Il analyse les dossiers et renomme les assets s'y trouvant.

## Puis-je prévisualiser les modifications ?

Oui. Le Workbench crée un plan de renommage détaillé et vous permet d'exporter un rapport avant toute modification.

## Que se passe-t-il si deux assets obtiennent le même nom ?

Les deux entrées en conflit sont exclues du plan pour éviter tout écrasement.

## Peut-il détecter les types de textures ?

Oui, partiellement via la compression et les jetons de nom courants (`normal`, `roughness`, `metallic`, etc.).

## Modifie-t-il les noms des classes Blueprint ?

Il renomme l'asset en tant que fichier/package, il ne réécrit pas le code interne.

## Puis-je importer des règles depuis un tableur ?

Oui, via l'importation d'une DataTable compatible et la fonction de conversion intégrée.

## Génère-t-il des rapports ?

Oui, des rapports au format JSON et Markdown sont enregistrés sous `Saved/NamingConventionUtility/Reports/`.

## Corrige-t-il les redirecteurs ?

Oui, une étape de correction automatique des redirecteurs peut s'exécuter après le renommage si elle est activée.

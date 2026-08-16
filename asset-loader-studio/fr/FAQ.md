<!-- doc-provenance: product-facts.yml reconciled 2026-07-01; source AKDB:plugins/AssetLoaderStudio/architecture.md -->
# FAQ

## Asset Loader Studio est-il autonome ?

Oui. L'espace de travail de l'éditeur, le sous-système runtime, la bibliothèque Blueprint, les exemples, les profils de gouvernance et la documentation acheteur fonctionnent sans UCM, UMCP, MCP ou autres plugins Tiny Tool.

## Remplace-t-il l'Asset Manager d'Unreal ?

Non. Il s'appuie sur les chemins d'actifs Unreal, les identifiants d'actifs principaux, les tables, les packages et l'Asset Registry. Il ajoute des jobs de chargement structurés, des diagnostics, des instantanés de table, des graphes de dépendances, des prévisualisations et de la gouvernance.

## Peut-il modifier les actifs du projet ?

Oui, mais la modification privilégie la prévisualisation. Les opérations de création, duplication, renommage, retargeting, réparation, sauvegarde, annulation et suppression doivent passer les vérifications du profil de permission et doivent être révisées avant l'application.

## Où sont stockés les enregistrements d'audit ?

Le répertoire d'audit par défaut est `Saved/AssetLoaderStudio/Audit`. Le chemin peut être ajusté via les paramètres de gouvernance.

## Les routes d'automatisation sont-elles obligatoires ?

Non. Des fichiers UCM/MCP optionnels exposent les mêmes services pour l'automatisation gouvernée, mais le produit de base reste utilisable sans eux.

## Asset Loader Studio est-il en ligne sur Fab ?

L'état actuel du package est "In Publishment" (En cours de publication). Considérez-le comme préparé pour la remise à Fab, mais pas encore en ligne tant que la fiche du portail Fab elle-même n'est pas publiée.

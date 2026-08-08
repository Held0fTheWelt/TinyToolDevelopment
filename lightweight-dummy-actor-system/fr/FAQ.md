# FAQ

## Que fait LightweightDummyActorSystem ?

Il fournit un service de représentation en temps réel pour les workflows d'acteurs factices, incluant l'enregistrement des sujets, la représentation des acteurs factices, les transitions de promotion et de rétrogradation, les diagnostics, un inspecteur dans l'éditeur et un commandlet de validation.

## Peut-il être utilisé sans d'autres plugins Tiny Tool ?

Oui. Les modules Runtime, Editor et DeveloperTool sont implémentés en tant que package principal. Les adaptateurs WarCollection, LightningCore, UCM, PIO et BPJ sont des intégrations optionnelles spécifiques à la cible et ne sont pas requis pour le comportement principal livré.

## Quelles versions du moteur sont prises en charge ?

La matrice de version emballée cible Unreal Engine 5.4 à 5.8 sur Win64, Linux et Mac, là où les listes autorisées de modules permettent ces plateformes.

## Modifie-t-il les actifs du projet par lui-même ?

Non. Le service principal gère l'état de représentation et de transition. Toute mutation spécifique au projet ou comportement d'adaptateur doit être examiné dans le workflow du projet propriétaire.

## Où puis-je obtenir du support ?

Utilisez le lien de support sur la page produit Fab.

<!-- doc-provenance: product-facts.yml reconciled 2026-07-04; source AKDB:plugins/NamingConventionUtility/architecture.md -->
# Dépannage

## Le menu contextuel n'apparaît pas

Vérifiez :

- Le plugin est activé.
- L'éditeur a été redémarré.
- Vous faites un clic droit sur un dossier du Content Browser.

## L'outil indique qu'aucun asset ne sera renommé

Raisons possibles :

- Tous les assets respectent déjà la convention.
- Les types d'assets ne sont pas pris en charge.
- Le DataAsset configuré est vide.
- Les noms générés seraient invalides.

## Le Workbench bloque l'application comme obsolète (Stale)

Le plan a été modifié après l'analyse (changement de dossier, édition de règle, etc.). Cliquez de nouveau sur **Scan**.

## Impossible de modifier un profil intégré

`epic_recommended` et `tiny_legacy` sont en lecture seule. Utilisez **Copy to Project** pour dupliquer leurs règles dans votre profil personnalisé.

## Une texture a reçu le préfixe générique `T_`

La détection automatique de sous-type est heuristique. Si les jetons de nom ne sont pas explicites, la règle générique est appliquée.

## Un renommage a échoué après confirmation

Raisons courantes :

- Références existantes.
- Problème de verrouillage dans le contrôle de code source.
- Paquets verrouillés.

Consultez le Output Log.

## Informations à fournir pour le support

- Version d'Unreal Engine.
- Version du plugin.
- Chemin du dossier sélectionné.
- Chemin du DataAsset configuré.

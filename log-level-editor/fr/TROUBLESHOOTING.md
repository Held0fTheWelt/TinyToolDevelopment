<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/LogLevelEditor/architecture.md -->
# Dépannage

## L'outil n'affiche pas ma catégorie

Vérifiez :

- La catégorie est déclarée ou définie dans un chemin source analysé.
- L'extension de fichier est `.h`, `.hpp`, `.cpp` ou `.inl`.
- La catégorie n'est pas masquée par les paramètres de masquage permanent ou temporaire.
- L'analyse est terminée ou encore en cours.
- La macro fait partie des formes de macros de journalisation Unreal prises en charge.

## Le niveau par défaut est manquant ou incorrect

Le scanner ne peut déduire les niveaux par défaut qu'à partir de macros reconnaissables. Certaines catégories peuvent être affichées sans niveau par défaut ou avec une valeur de secours.

Solutions :

- Utilisez la mise en forme standard des macros Unreal lorsque c'est possible.
- Ajoutez une surcharge persistante si vous avez besoin d'une valeur connue.

## La modification d'un niveau de verbosité n'a aucun effet

Causes possibles :

- La catégorie n'est pas encore enregistrée par un module chargé.
- Unreal a rejeté la commande de console.
- Du code à l'exécution a de nouveau modifié la catégorie après la commande d'éditeur.

Consultez le Output Log pour lire les messages `LogLogLevelEditor`.

## La verbosité enregistrée n'est pas appliquée au démarrage

Vérifiez :

- `LogLevelDataAsset` pointe vers un asset valide.
- Le DataAsset contient des entrées de surcharge.
- La catégorie existe lorsque la réapplication au démarrage s'exécute.

## Mon DataAsset contient trop d'entrées

Le DataAsset ne doit contenir que des surcharges volontaires. Réinitialisez les lignes vers leurs niveaux par défaut détectés pour supprimer les entrées inutilement enregistrées.

## Les catégories masquées temporairement sont réapparues

Les valeurs de masquage temporaires sont éphémères et ne persistent pas d'une session à l'autre. Utilisez `LogChannelsToHide` pour un masquage permanent.

## L'analyse prend trop de temps

Désactivez l'analyse des plugins et du code source du moteur, sauf si nécessaire.

Configuration normale recommandée :

```text
bAlsoListEnginePluginChannels = false
bAlsoListEngineSourceChannels = false
```

## Le journal de sortie reste trop encombré

Certains systèmes peuvent écrire des journaux via plusieurs catégories. Recherchez les préfixes de catégories associés et ajustez chaque canal concerné.

## Le plugin s'ouvre mais n'affiche aucune surcharge du DataAsset

Le scanner et le DataAsset sont distincts :

- Scanner : découvre les catégories disponibles.
- DataAsset : stocke les surcharges persistantes.

Un DataAsset vide est tout à fait normal si aucune surcharge persistante n'a été configurée.

## Le contrôle de code source indique constamment que mon DataAsset est modifié

Vous avez probablement modifié des surcharges persistantes. Conservez ces modifications si elles font partie des règles d'équipe, ou réinitialisez les lignes vers leurs niveaux par défaut avant de soumettre.

## Informations à rassembler pour le support

Lors du signalement d'un problème, incluez :

- La version d'Unreal Engine.
- La version du plugin.
- Si l'analyse des plugins/sources du moteur est activée.
- Un exemple de déclaration de catégorie de journal.
- La sortie pertinente liée à `LogLogLevelEditor`.

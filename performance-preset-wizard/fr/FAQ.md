<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/PerformancePresetWizard/architecture.md -->
# FAQ (Foire aux questions)

## Performance Preset Wizard est-il un optimiseur automatique ?

Non. C'est un outil de création et d'application de préréglages. Il ne teste pas automatiquement votre matériel.

## Fonctionne-t-il à l'exécution ?

Oui, les jeux empaquetés peuvent appliquer manuellement les préréglages via `UPerformancePresetRuntimeSubsystem`, Blueprint, C++ ou le widget UMG inclus.

## L'application d'un préréglage enregistre-t-elle les paramètres du projet ?

Non. Elle modifie l'état actuel du moteur/de l'exécution via les API de scalabilité et de CVar.

## Puis-je annuler une application ?

Dans l'assistant de l'éditeur, utilisez **Restore Previous**. À l'exécution, utilisez `RestoreLatestBackup` ou `RestoreBackupById`.

## Que se passe-t-il si une CVar n'existe pas ?

Le plugin la signale comme manquante et continue d'appliquer le reste du préréglage.

## Pourquoi les valeurs de CVar sont-elles stockées sous forme de chaînes de caractères ?

Les CVar peuvent être des entiers, des flottants, des booléens ou du texte. Une chaîne couvre tous ces cas.

## Que signifie "Editor Only" ?

Une rechargement réservée à l'éditeur s'applique uniquement dans l'éditeur et est ignorée dans les jeux empaquetés.

## Le plugin remplace-t-il les Device Profiles ?

Non. Les Device Profiles restent le lieu approprié pour les règles relatives aux plateformes.

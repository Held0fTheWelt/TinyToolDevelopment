<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/PerformancePresetWizard/architecture.md -->
# Manuel de l'utilisateur

Ce manuel décrit le flux de travail normal dans l'éditeur pour Performance Preset Wizard.

## Ouvrir l'assistant

1. Activez **Performance Preset Wizard** dans **Edit > Plugins**.
2. Redémarrez Unreal Editor si demandé.
3. Ouvrez **Tools > Performance > Performance Preset Wizard**.

L'assistant scanne le registre d'assets pour trouver les assets `UPerformancePresetAsset` et liste les préréglages détectés.

## Panneau principal

L'assistant comprend deux zones principales :

- Liste des préréglages : tous les assets de préréglages de performances détectés.
- Panneau de détails : nom du préréglage sélectionné, description, niveaux de scalabilité, recharges CVar, texte de statut et boutons d'action.

Utilisez **Refresh** lorsque de nouveaux préréglages ont été créés, renommés, déplacés ou importés.

## Sélectionner un préréglage

Cliquez sur un préréglage dans la liste pour charger son résumé.

## Appliquer un préréglage

1. Sélectionnez un préréglage.
2. Révisez le résumé.
3. Cliquez sur **Apply Preset**.

L'ordre des opérations est le suivant :

1. Capture d'un point de restauration.
2. Limitation des valeurs de scalabilité à la plage `0..4` d'Unreal.
3. Application de la scalabilité via `Scalability::SetQualityLevels`.
4. Parcours des recharges CVar.
5. Ignorer les entrées invalides ou mal formées.
6. Ignorer les entrées `editor-only` hors du contexte de l'éditeur.
7. Rapport dans la zone de statut et de notification.

## Restaurer les paramètres précédents

Cliquez sur **Restore Previous** pour revenir aux paramètres capturés immédiatement avant la dernière application réussie.

La restauration inclut :

- La structure complète de scalabilité avant l'application.
- Les valeurs précédentes pour les CVar spécifiques réécrites par le préréglage.

L'application d'un autre préréglage remplace le point de restauration précédent.

## Préréglage au démarrage de l'éditeur

Ouvrez **Edit > Project Settings > Plugins > Performance Preset Wizard**.

Paramètres disponibles :

- **Apply Preset On Editor Startup** : active ou désactive l'application au démarrage.
- **Startup Preset** : référence douce vers l'asset de préréglage à appliquer après l'initialisation de l'éditeur.

## Préréglages à l'exécution

Les préréglages d'exécution utilisent les mêmes assets `UPerformancePresetAsset`. Les jeux empaquetés les appliquent manuellement via `UPerformancePresetRuntimeSubsystem`.

Flux Blueprint type :

1. Obtenir la `GameInstance` actuelle.
2. Obtenir le `Performance Preset Runtime Subsystem`.
3. Passer un asset de préréglage à `ApplyRuntimePreset`.
4. Appeler `RestoreLatestBackup` en cas d'annulation.

## Widget de sélection d'exécution

`UPerformancePresetRuntimeSelectorWidget` est inclus comme point de départ UMG. Il peut lister les préréglages configurés, appliquer le préréglage sélectionné et restaurer la dernière sauvegarde.

Les préréglages affichés par le widget par défaut peuvent être configurés sous **Project Settings > Plugins > Performance Preset Wizard Runtime**.

## Éditeur de CVar en bloc

Utilisez l'éditeur de texte CVar pour copier des recharges à partir de notes ou de sessions console.

Syntaxe prise en charge :

```text
# Les lignes de commentaire sont autorisées
r.ScreenPercentage=85
r.Nanite=1
r.Shadow.Virtual.Enable=1,editor
```

Utilisez **Export** pour écrire le tableau actuel dans l'éditeur et **Apply** pour réanalyser le texte dans l'asset.

## Nommage recommandé

Utilisez des noms explicites :

- `Laptop Dev`
- `Desktop Mid Range 60 FPS`
- `Console Like Review`
- `VR Mobile Stable`
- `Cinematic Capture 4k`

## Déplacer ou supprimer des préréglages

Si le préréglage au démarrage cesse de s'appliquer, re-sélectionnez l'asset dans Project Settings et enregistrez les paramètres.

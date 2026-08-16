<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/PerformancePresetWizard/architecture.md -->
# Guide de démarrage rapide

Ce guide vous accompagne de l'installation à un **résultat concret** : un préréglage de performances appliqué à votre éditeur (scalabilité + variables de console) que vous pouvez entièrement restaurer en un clic. Performance Preset Wizard fonctionne de manière autonome.

## Ce que vous obtiendrez après ce guide

L'assistant ouvert avec les préréglages détectés, un préréglage appliqué (niveaux de scalabilité + recharges CVar), et la possibilité de restaurer vos paramètres précédents.

## Prérequis

- Éditeur Unreal Engine 5. L'application à l'exécution dans un jeu empaqueté est optionnelle.
- Aucun logiciel tiers, compte ou runtime supplémentaire n'est requis. Voir [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md).

## 1. Installation et activation

1. Ajoutez **Performance Preset Wizard** depuis votre bibliothèque Fab à votre projet (ou installez-le dans le moteur).
2. Ouvrez **Edit → Plugins**, activez **Performance Preset Wizard** et redémarrez lorsque demandé.

## 2. Ouvrir l'assistant

1. Ouvrez **Tools → Performance → Performance Preset Wizard**.
2. L'assistant scanne le registre d'assets pour trouver les assets `UPerformancePresetAsset` et les liste par nom d'affichage, plateforme cible et chemin.
3. Cliquez sur un préréglage pour charger son panneau de détails.

## 3. Un exemple concret : appliquer, puis restaurer

1. Sélectionnez un exemple de préréglage inclus.
2. Cliquez sur **Apply Preset**.

**Résultat attendu :** L'assistant capture un point de restauration, limite la scalabilité à la plage `0..4` d'Unreal et l'applique, puis applique chaque rechargement CVar.

3. Cliquez sur **Restore Previous**.

**Résultat attendu :** La structure de scalabilité et les CVar spécifiques modifiées par le préréglage reviennent aux valeurs capturées immédiatement avant l'application.

## 4. Créer votre propre préréglage

Ouvrez n'importe quel `PerformancePresetAsset` dans le Content Browser. Le panneau Details vous propose des menus déroulants par catégorie et un **éditeur de CVar en bloc** :

```text
# Les lignes de commentaire sont autorisées
r.ScreenPercentage=85
r.Nanite=1
r.Shadow.Virtual.Enable=1,editor
```

`,editor` marque une rechargement comme réservée à l'éditeur. Utilisez **Export** pour écrire le tableau dans l'éditeur de texte et **Apply** pour le réanalyser dans l'asset. Voir [PresetAuthoringGuide.md](PresetAuthoringGuide.md).

## 5. Optionnel : Utilisation au démarrage et à l'exécution

- **Démarrage de l'éditeur :** *Project Settings → Plugins → Performance Preset Wizard* → **Apply Preset On Editor Startup** + **Startup Preset**.
- **Jeu empaqueté :** Appliquez les préréglages via `UPerformancePresetRuntimeSubsystem.ApplyRuntimePreset` et `RestoreLatestBackup`, ou utilisez le widget `UPerformancePresetRuntimeSelectorWidget`. Voir [RuntimeUsage.md](RuntimeUsage.md).

## 6. Étapes suivantes

- Flux de travail complet et historique de sauvegarde : [UserManual.md](UserManual.md).
- Préréglages inclus : [SamplePresetsReference.md](SamplePresetsReference.md).
- Paramètres : [SettingsReference.md](SettingsReference.md). Problèmes : [TROUBLESHOOTING.md](TROUBLESHOOTING.md), [FAQ.md](FAQ.md).

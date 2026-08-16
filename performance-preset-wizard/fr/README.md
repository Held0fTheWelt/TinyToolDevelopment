<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/PerformancePresetWizard/architecture.md -->
# Documentation de Performance Preset Wizard

Performance Preset Wizard crée des préréglages de performances cibles au moment de l'exécution, créés et révisés dans Unreal Editor, puis appliqués manuellement via l'assistant de l'éditeur, C++, Blueprint ou le widget de sélection d'exécution inclus. Un préréglage combine les niveaux de scalabilité du moteur avec des recharges de variables de console (CVar) optionnelles, permettant aux équipes de basculer rapidement entre des niveaux matériels, des budgets VR, des paramètres de capture, des configurations pour ordinateurs portables et des objectifs de qualité spécifiques.

Ce dossier contient la documentation complète livrée avec le plugin.

## Commencez ici

- [BUYER_GUIDE.md](BUYER_GUIDE.md) : vue d'ensemble pour les acheteurs, valeur incluse et flux de travail de production courants.
- [UserManual.md](UserManual.md) : flux de travail complet de l'éditeur pour ouvrir l'assistant, appliquer les préréglages, restaurer les paramètres précédents et configurer les préréglages au démarrage.
- [RuntimeUsage.md](RuntimeUsage.md) : sous-système d'exécution, API Blueprint, historique de sauvegarde, fournisseur de stockage et widget de sélection.
- [FAQ.md](FAQ.md) : réponses pratiques pour les acheteurs Fab, les designers et les artistes techniques.

## Référence

- [PresetAuthoringGuide.md](PresetAuthoringGuide.md) : comment concevoir des préréglages fiables, choisir les niveaux de scalabilité et écrire des recharges CVar.
- [RuntimeUsage.md](RuntimeUsage.md) : comment les jeux empaquetés peuvent appliquer et restaurer manuellement les préréglages.
- [SettingsReference.md](SettingsReference.md) : chaque paramètre du plugin et champ d'asset avec les valeurs par défaut et l'utilisation recommandée.
- [SamplePresetsReference.md](SamplePresetsReference.md) : exemples de préréglages `DA_*` inclus et comment les adapter.
- [CodeDocumentation.md](CodeDocumentation.md) : structure du code source, contrats publics, notes d'implémentation et points d'extension.
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md) : problèmes courants de configuration, d'assets, de CVar et de build avec leurs solutions.

## Assets inclus

- [Screenshots/](Screenshots) : schémas légers montrant le flux de travail de l'assistant, la création de préréglages et le comportement de restauration/démarrage.
- `../Content/DA_*.uasset` : exemples d'assets de données de préréglages couvrant les ordinateurs de bureau, la VR, les environnements de type console, les prototypes mobiles, le développement sur ordinateur portable et les cas d'utilisation cinématographiques.
- `../PerformancePresetWizard_Changelog.txt` : notes de version livrées avec le plugin.

## Flux de travail rapide de l'éditeur

1. Activez le plugin et redémarrez l'éditeur si Unreal le demande.
2. Ouvrez **Tools > Performance > Performance Preset Wizard**.
3. Sélectionnez un préréglage dans la liste. Utilisez **Refresh** si de nouveaux préréglages ont été créés ou importés.
4. Révisez le nom d'affichage, la description, la plateforme cible, le résumé de scalabilité et les recharges CVar.
5. Cliquez sur **Apply Preset**. L'assistant applique d'abord les paramètres de scalabilité, puis les recharges CVar valides.
6. Cliquez sur **Restore Previous** pour revenir aux paramètres capturés immédiatement avant la dernière application.
7. Activez **Apply on Editor Startup** dans Project Settings si un préréglage doit être appliqué automatiquement à l'ouverture de l'éditeur.

## Flux de travail rapide à l'exécution

1. Créez et révisez les préréglages `UPerformancePresetAsset` dans l'éditeur.
2. Ajoutez des préréglages d'exécution dans **Project Settings > Plugins > Performance Preset Wizard Runtime**, ou passez-les directement au sous-système d'exécution.
3. En C++ ou Blueprint, obtenez `UPerformancePresetRuntimeSubsystem` à partir de la `GameInstance` actuelle.
4. Appelez `ApplyRuntimePreset` pour une action utilisateur ou projet explicite.
5. Utilisez `GetBackupHistory`, `RestoreLatestBackup` ou `RestoreBackupById` lorsque le projet nécessite une annulation.
6. Utilisez `UPerformancePresetRuntimeSelectorWidget` comme un petit widget UMG remplaçable pour les menus de test ou les écrans d'options.

## Format rapide des CVar

L'éditeur de CVar en bloc accepte une rechargement par ligne :

```text
r.ScreenPercentage=85
r.Nanite=1
r.Lumen.Reflections.Allow=0
r.Shadow.Virtual.Enable=1,editor
```

Règles :

- Les lignes vides sont ignorées.
- Les lignes commençant par `#` ou `//` sont traitées comme des commentaires.
- `Name=Value` crée une rechargement normal.
- `Name=Value,editor` marque la rechargement comme réservée à l'éditeur (editor-only).
- Les CVar inconnues sont signalées mais n'arrêtent pas l'application du préréglage.
- Les noms ou valeurs vides sont ignorés.

## Niveaux de scalabilité

Performance Preset Wizard suit l'échelle de qualité standard d'Unreal Engine :

- `0` : Low
- `1` : Medium
- `2` : High
- `3` : Epic
- `4` : Cinematic

Le plugin gère les catégories de scalabilité actuelles d'UE5, notamment la distance d'affichage, l'antialiasing, les ombres, l'illumination globale, les réflexions, le post-traitement, les textures, les effets, le feuillage, l'ombrage et le paysage.

## Notes importantes sur la portée

Performance Preset Wizard n'est pas un outil de benchmark, un détecteur matériel, un optimiseur automatique ou un remplacement des Device Profiles. Les préréglages doivent être vérifiés sur la plateforme et le projet cibles avant d'être considérés comme des paramètres de production définitifs.

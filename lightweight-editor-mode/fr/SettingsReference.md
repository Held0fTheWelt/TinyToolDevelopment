<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/LightweightEditorMode/architecture.md -->
# Référence des paramètres

Lightweight Editor Mode stocke ses paramètres dans EditorPerProjectUserSettings et les expose sous Project Settings > Plugins > Lightweight Editor Mode.

## Modèle de paramètres

L'objet de paramètres comporte trois couches :

- Options de haut niveau telles que le comportement au démarrage et l'index de profil sélectionné.
- Valeurs d'exécution actives consommées par le mode lorsqu'il est activé.
- Quatre structures de profil modifiables : Mild, Balanced, Aggressive et Extreme.

L'interface Slate copie le profil sélectionné dans les valeurs d'exécution actives avant d'activer ou de rafraîchir le mode.

## Options de haut niveau

### bEnableOnStartup

Active automatiquement Lightweight Editor Mode au lancement de l'éditeur.

Notes d'implémentation :

- Le module ne s'active pas immédiatement lors de StartupModule.
- Il démarre un court temporisateur.
- Le temporisateur attend que GEditor dispose de clients de viewport d'éditeur.
- Le mode est activé seulement après que les viewports sont disponibles.
- La récupération d'une session obsolète s'exécute avant l'auto-activation si la session précédente de l'éditeur s'est terminée alors que le mode était encore actif.

Cela évite de perdre des modifications de viewport lors du démarrage précoce de l'éditeur.

### AggressivenessLevel

Stocke l'index du profil actuellement sélectionné.

| Valeur | Profil |
| --- | --- |
| 0 | Mild |
| 1 | Balanced |
| 2 | Aggressive |
| 3 | Extreme |

La valeur est limitée à la plage valide.

## Valeurs d'exécution actives

Ces valeurs sont appliquées par FEditorLightweightMode.

### OverallQuality

Un niveau unique de qualité de scalabilité Unreal.

| Valeur | Signification |
| --- | --- |
| 0 | Low (Faible) |
| 1 | Medium (Moyen) |
| 2 | High (Élevé) |
| 3 | Epic (Épique) |
| 4 | Cinematic (Cinématographique) |

Le plugin limite cette valeur à la plage 0..4 avant de l'appliquer.

### ScreenPercentage

Pourcentage d'écran cible pour le rendu du viewport de l'éditeur et les chemins de prévisualisation PIE/jeu.

| Plage | Signification |
| --- | --- |
| 25..59 | Très agressif, faible fidélité visuelle |
| 60..79 | Édition orientée performance |
| 80..99 | Édition équilibrée |
| 100 | Résolution interne complète |
| 101..200 | Supersampling, rarement utile pour le mode léger |

Le plugin limite cette valeur à la plage 25..200.

Détail d'implémentation important : les viewports de l'éditeur utilisent des CVars de pourcentage d'écran spécifiques. Le plugin définit :

- r.Editor.Viewport.ScreenPercentage
- r.Editor.Viewport.ScreenPercentageMode.RealTime
- r.Editor.Viewport.ScreenPercentageMode.NonRealTime

Il définit également r.ScreenPercentage pour les parcours PIE et prévisualisation jeu où cette CVar reste pertinente.

### bDisableLumen

Désactive l'éclairage indirect diffus Lumen et les réflexions Lumen lorsque le mode est actif.

CVars :

- r.Lumen.DiffuseIndirect.Allow = 0
- r.Lumen.Reflections.Allow = 0

Lorsqu'il est désactivé dans le profil, le plugin restaure les sauvegardes existantes pour ces CVars en retirant sa surcharge marquée. Si une autre source a modifié la même CVar pendant que le mode était actif, cette valeur plus récente reste active.

### bDisableVirtualShadows

Désactive les cartes d'ombres virtuelles (Virtual Shadow Maps).

CVar :

- r.Shadow.Virtual.Enable = 0

Cela peut rendre les scènes Nanite et grands mondes plus réactives, mais modifie également considérablement l'aspect des ombres.

### bDisableVolumetricFog

Désactive le brouillard volumétrique et le brouillard standard.

CVars :

- r.VolumetricFog = 0
- r.Fog = 0

Utile dans les scènes atmosphériques où le brouillard domine le temps de rendu par image dans l'éditeur.

### bForceUnlitViewports

Fait passer les viewports de l'éditeur en mode Unlit (non éclairé) lorsque le mode est actif.

Le plugin stocke le mode d'affichage d'origine par viewport avant le basculement. Lorsque le mode est désactivé dans la même session d'éditeur, les modes d'affichage d'origine sont restaurés.

### bDisableViewportRealtime

Désactive le rendu en temps réel dans les viewports de l'éditeur lorsque le mode est actif.

Le plugin utilise le système de surcharge temporaire de temps réel d'Unreal au lieu de modifier le paramètre persistant de temps réel du viewport. Lorsqu'il est désactivé, il supprime sa propre surcharge.

## Valeurs par profil

Chaque profil contient les mêmes champs :

- OverallQuality
- ScreenPercentage
- bDisableLumen
- bDisableVirtualShadows
- bDisableVolumetricFog
- bForceUnlitViewports
- bDisableViewportRealtime

Les profils sont modifiables dans Project Settings. La modification d'un profil ne l'applique pas immédiatement sauf si l'interface copie ce profil dans les valeurs actives.

## LastViewModeBeforeLightweight

Ce paramètre masqué-visible stocke le dernier mode d'affichage observé avant l'activation du mode. Il sert de valeur de secours persistante après un redémarrage de l'éditeur.

La restauration au sein de la même session utilise d'abord les sauvegardes par viewport. La récupération après redémarrage ne peut pas utiliser ces sauvegardes en mémoire, la valeur de secours est donc utilisée uniquement pour ramener les viewports Unlit vers un mode non-Unlit raisonnable.

## bWasLightweightModeActiveLastSession

Ce paramètre de diagnostic visible enregistre si le Lightweight Mode était actif avant la dernière fermeture de l'éditeur. Il est défini au début de l'application des surcharges et effacé lors de la désactivation.

S'il est toujours vrai (true) après le redémarrage, l'interface propose Restore Lightweight State et le démarrage automatique restaure l'état obsolète du viewport avant d'activer à nouveau le mode.

## Intention des profils par défaut

| Profil | Intention |
| --- | --- |
| Mild | Légère réduction tout en conservant le contexte visuel |
| Balanced | Valeur par défaut recommandée pour l'édition générale |
| Aggressive | Édition de scènes lourdes où la réactivité prévaut |
| Extreme | Édition d'urgence ou dans des environnements très limités en ressources |

## Personnalisation recommandée

Pour les équipes axées sur la direction artistique, rendez Mild moins destructif et laissez la vue Lit active. Pour les flux de travail grands mondes ou sur ordinateur portable, rendez Balanced plus agressif. Pour le débogage technique, conservez au moins un profil qui ne force pas Unlit afin de pouvoir inspecter rapidement les problèmes de rendu.

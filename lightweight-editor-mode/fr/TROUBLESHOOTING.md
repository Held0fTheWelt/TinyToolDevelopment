<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/LightweightEditorMode/architecture.md -->
# Dépannage

Ce guide couvre les problèmes courants et leurs causes probables.

## La fenêtre du plugin est introuvable

Vérifiez les points suivants :

- Le plugin est activé dans Edit > Plugins.
- Le projet a été redémarré après l'activation du plugin.
- Le module est répertorié dans le tableau Plugins du fichier .uproject.
- Vous exécutez l'éditeur et non un commandlet.

La fenêtre doit apparaître sous Tools > Performance > Lightweight Editor Mode.

## Le mode ne s'active pas au démarrage

L'activation au démarrage attend que les clients de viewport de l'éditeur existent. Dans un projet lourd, cela peut prendre un moment après le démarrage du module.

Vérifiez :

- Enable on Editor startup est coché.
- Le plugin est activé dans le projet.
- L'éditeur a bien créé les viewports de l'éditeur de niveau.
- Les journaux contiennent "Scheduling Lightweight Mode auto-enable".
- Les journaux contiennent ultérieurement "Auto-enabling Lightweight Mode after editor viewports became available".

Si le paramètre est décoché avant que les viewports deviennent disponibles, le temporisateur s'annule automatiquement.

## Le pourcentage d'écran semble inchangé

Les viewports de l'éditeur ne suivent pas toujours r.ScreenPercentage. Lightweight Editor Mode utilise des CVars spécifiques aux viewports de l'éditeur :

- r.Editor.Viewport.ScreenPercentage
- r.Editor.Viewport.ScreenPercentageMode.RealTime
- r.Editor.Viewport.ScreenPercentageMode.NonRealTime

Si le viewport semble toujours inchangé, vérifiez :

- La valeur ScreenPercentage du profil sélectionné.
- Si le viewport utilise un chemin du moteur qui surcharge le pourcentage d'écran.
- Si un autre plugin ou une commande de console modifie les mêmes CVars d'éditeur après l'exécution de Lightweight Editor Mode.

## Les viewports restent en Unlit après la désactivation

La restauration dans la même session utilise des sauvegardes par viewport. La récupération après redémarrage ne dispose que de la valeur enregistrée LastViewModeBeforeLightweight.

Essayez :

1. Ouvrez la fenêtre du plugin.
2. Cliquez sur Disable Lightweight Mode.
3. Si nécessaire, repassez manuellement le viewport en Lit.
4. Réactivez et désactivez le mode au cours de la même session pour confirmer la restauration normale.

Si cela se produit fréquemment, vérifiez si l'éditeur est fermé pendant que le mode est toujours activé.

Après un plantage ou une fermeture forcée, le bouton principal peut afficher Restore Lightweight State. Cliquez dessus pour exécuter la restauration conservatrice du viewport et effacer le marqueur de session obsolète.

## Le temps réel reste désactivé

La désactivation du temps réel utilise le système de surcharge temporaire d'Unreal. Dans la même session d'éditeur, Disable supprime la surcharge Lightweight au lieu de modifier la préférence de temps réel enregistrée du viewport.

Si le temps réel semble toujours désactivé, vérifiez si un autre système de l'éditeur possède sa propre surcharge active. Réactivez manuellement le temps réel depuis le menu du viewport si besoin.

## Lumen semble toujours activé

Vérifiez si :

- Le profil sélectionné a bDisableLumen activé.
- Le projet utilise réellement Lumen.
- Un autre plugin ou code de projet définit les CVars Lumen après l'activation du mode.
- Une branche personnalisée du moteur a renommé ou supprimé les CVars concernées.

Le plugin cible :

- r.Lumen.DiffuseIndirect.Allow
- r.Lumen.Reflections.Allow

Les CVars manquantes sont ignorées et consignées dans le journal au niveau Verbose.

## Les ombres restent coûteuses

bDisableVirtualShadows cible les cartes d'ombres virtuelles (Virtual Shadow Maps) :

- r.Shadow.Virtual.Enable

Cela ne désactive pas tous les coûts d'ombrage possibles dans chaque chemin de rendu. Si votre scène utilise des ombres non virtuelles, des systèmes d'ombres personnalisés, du ray tracing ou du rendu par plugin, des ajustements spécifiques au projet peuvent être nécessaires.

## Le brouillard apparaît toujours

bDisableVolumetricFog définit :

- r.VolumetricFog = 0
- r.Fog = 0

Certains matériaux, volumes de post-traitement, systèmes de ciel ou effets d'atmosphère personnalisés peuvent encore créer une apparence similaire au brouillard.

## L'éditeur semble de trop faible qualité

Utilisez un profil moins agressif :

- Passez de Extreme à Aggressive.
- Passez de Aggressive à Balanced.
- Augmentez ScreenPercentage.
- Augmentez OverallQuality.
- Désactivez Force Unlit pour un profil personnalisé.

Après avoir modifié le profil pendant que le mode est activé, le système rafraîchit automatiquement les paramètres actifs.

## L'éditeur est toujours lent

Lightweight Editor Mode cible le coût de rendu du viewport de l'éditeur. Il ne peut pas résoudre tous les problèmes de performance de l'éditeur.

Autres goulots d'étranglement possibles :

- Compilation d'assets.
- Compilation de shaders.
- Opérations de contrôle de source.
- Construction scripts des Blueprints.
- Widgets d'outils d'éditeur.
- Logique de Tick lourde dans le monde de l'éditeur.
- Nombre massif d'actors.
- Surcharge liée au disque ou à l'antivirus.

Utilisez Unreal Insights, les commandes Stat et le profilage classique pour diagnostiquer les goulots d'étranglement hors rendu.

## Disable ne restaure pas une CVar

Le chemin de restauration supprime la surcharge marquée du plugin. Si un autre système a modifié la même CVar pendant que Lightweight Editor Mode était actif, cette valeur plus récente reste active au lieu d'être écrasée par l'ancienne sauvegarde.

Consultez le journal de sortie pour connaître le nom de la CVar. Le plugin consigne les opérations de sauvegarde et de restauration.

## La page Project Settings est masquée ou introuvable

La page de paramètres doit apparaître sous Project Settings > Plugins > Lightweight Editor Mode.

Si elle est absente :

- Confirmez que le module a été chargé.
- Confirmez que le module Settings est disponible.
- Redémarrez l'éditeur après avoir activé le plugin.
- Vérifiez qu'aucun problème de descripteur de plugin ou de compilation n'a empêché le chargement du module.

## La compilation échoue après l'ajout d'une nouvelle CVar

Causes courantes :

- Constante de nom de CVar ajoutée mais non utilisée de manière cohérente.
- Paramètre ajouté à la structure de profil mais pas aux champs actifs.
- Instruction switch de l'interface non mise à jour pour le nouveau profil.
- Include manquant pour un type Unreal.
- Erreur de syntaxe dans un bloc de métadonnées UPROPERTY.

Exécutez la compilation de la cible d'éditeur après avoir modifié le code source.

## Journaux à inspecter

Recherchez dans le Output Log :

- [Module]
- [Lightweight]
- Backup CVar
- Restore CVar
- ApplyActiveSettings
- ApplyViewportSettings
- Lightweight mode ENABLED
- Lightweight mode DISABLED

Les journaux sont volontairement explicites afin que les demandes d'assistance puissent inclure la séquence pertinente.

<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/LightweightEditorMode/architecture.md -->
# Manuel de l'utilisateur

Ce manuel explique comment utiliser Lightweight Editor Mode dans le travail quotidien au sein de l'éditeur Unreal Engine.

## Objectif

Les scènes volumineuses dans Unreal Engine peuvent rendre les viewports de l'éditeur très gourmands, même lorsque les performances finales du jeu sont acceptables. Une résolution de viewport élevée, Lumen, les ombres virtuelles, le brouillard volumétrique, le rendu en temps réel et des niveaux de scalabilité élevés peuvent consommer un temps d'image précieux lors de l'édition.

Lightweight Editor Mode vous offre un commutateur rapide pour activer un profil d'édition temporaire et réversible. Il est particulièrement utile lorsque vous avez besoin de réactivité pour le layout, le blockout, le travail sur les Blueprints, les passes de feuillage, le placement d'assets ou le nettoyage de projet.

## Ouverture de la fenêtre

1. Ouvrez l'éditeur Unreal Engine.
2. Assurez-vous que le plugin Lightweight Editor Mode est activé.
3. Allez dans Tools > Performance > Lightweight Editor Mode.
4. Le plugin ouvre un onglet ancrable dans l'éditeur.

L'onglet contient un menu déroulant de profils, un bouton de bascule et une case à cocher optionnelle pour le démarrage.

## Choix d'un profil

Le profil contrôle l'agressivité avec laquelle l'éditeur réduit les coûts de rendu.

### Mild

Mild est destiné aux projets qui n'ont besoin que d'un léger gain de performance. Il conserve un comportement de viewport proche de la normale et constitue un bon premier choix si vous devez garder un contexte visuel.

Comportement typique :

- Pourcentage d'écran (Screen Percentage) plus élevé.
- Scalabilité plus élevée que sur les profils agressifs.
- Ne force pas le mode Unlit par défaut.
- Ne désactive pas le temps réel du viewport par défaut.

### Balanced

Balanced est le choix par défaut recommandé. Il réduit l'éclairage coûteux et les coûts de viewport tout en restant pratique pour l'édition générale.

Comportement typique :

- Pourcentage d'écran moyen.
- Scalabilité globale plus basse.
- Désactive les fonctionnalités de rendu coûteuses.
- Force le mode Unlit et désactive le temps réel par défaut.

### Aggressive

Aggressive s'adresse aux scènes lourdes où la réactivité du viewport prime sur la fidélité visuelle.

Comportement typique :

- Pourcentage d'écran plus bas.
- Faible scalabilité.
- Éclairage, ombres et brouillard coûteux désactivés.
- Viewports forcés en mode Unlit.
- Rendu en temps réel désactivé dans les viewports.

### Extreme

Extreme est conçu pour les projets surchargés, le travail sur ordinateur portable, les grands mondes ou les besoins urgents de réactivité. Utilisez-le lorsque seule la structure de la scène et la vitesse d'interaction comptent.

Comportement typique :

- Pourcentage d'écran très bas.
- Scalabilité la plus basse.
- Fonctionnalités de rendu coûteuses désactivées.
- Viewports en Unlit et édition hors temps réel.

## Activation du mode

1. Sélectionnez un profil.
2. Cliquez sur Enable Lightweight Mode.
3. Le plugin applique le profil actif.
4. Les viewports se mettent à jour immédiatement.

Lorsqu'il est activé, le plugin sauvegarde l'état d'origine de l'éditeur qu'il devra restaurer :

- Les niveaux de qualité de scalabilité.
- Les valeurs de variables de console modifiées.
- Les modes d'affichage des viewports, lorsque Unlit est forcé.
- Les surcharges temporaires de rendu temps réel.

## Modification du profil lorsque le mode est activé

Vous pouvez choisir un autre profil alors que le mode est déjà activé. Le plugin rafraîchit les paramètres actifs tout en conservant les sauvegardes d'origine faites avant l'activation initiale. Cela signifie que Disable Lightweight Mode restaurera toujours l'état antérieur au mode plutôt que le profil intermédiaire.

## Désactivation du mode

Cliquez sur Disable Lightweight Mode pour restaurer l'état de l'éditeur.

Le plugin restaure :

- Les niveaux de scalabilité sauvegardés.
- Les surcharges de variables de console du plugin. Si un autre système a modifié la même valeur pendant que le mode était actif, cette valeur plus récente est conservée.
- Les modes d'affichage des viewports sauvegardés.
- Les surcharges temporaires de temps réel.

Si l'éditeur a été redémarré avant la désactivation du mode, les sauvegardes par session n'existent plus. Dans ce cas, le plugin utilise le mode d'affichage de secours enregistré dans les paramètres et effectue uniquement une restauration conservatrice du viewport. Lorsque cet état obsolète est détecté, le bouton affiche Restore Lightweight State.

## Activer au démarrage de l'éditeur (Enable on Editor startup)

La case à cocher Enable on Editor startup enregistre un paramètre utilisateur. Lorsqu'elle est activée, le plugin attend que les viewports de l'éditeur existent puis active automatiquement Lightweight Editor Mode.

Ce comportement de démarrage différé est intentionnel. Lors du démarrage précoce des modules, Unreal n'a parfois pas encore créé les clients de viewport, ce qui pourrait faire manquer les modifications. Le plugin utilise un court temporisateur et active le mode une fois l'éditeur prêt.

Si le démarrage automatique s'exécute après une session précédente terminée sans désactiver le mode, le plugin effectue d'abord la restauration conservatrice du viewport puis applique à nouveau le profil sélectionné.

## Flux de travail recommandés

### Blockout de niveau

Utilisez Balanced ou Aggressive. Vous n'avez généralement pas besoin de l'éclairage final pour bloquer des espaces, vérifier la navigation ou déplacer de grands groupes d'actors.

### Édition de feuillage ou de monde

Utilisez Aggressive. Les scènes avec beaucoup de feuillage peuvent être coûteuses en vue Lit avec ombres et mises à jour en temps réel.

### Iteration Blueprint ou Gameplay

Utilisez Mild ou Balanced. Conservez suffisamment de contexte visuel tout en rendant la réactivité de l'éditeur plus confortable.

### Évaluation de l'éclairage

Désactivez Lightweight Editor Mode. Le plugin masque ou réduit intentionnellement les fonctionnalités d'éclairage, il ne convient donc pas pour une validation visuelle finale.

### Capture cinématographique ou capture d'écran

Désactivez Lightweight Editor Mode, restaurez la scalabilité de production et évaluez le rendu dans le mode de viewport souhaité.

## Settings du projet

Ouvrez Project Settings > Plugins > Lightweight Editor Mode pour modifier les profils et les valeurs actives.

Les structures de profil sont la source de vérité pour Mild, Balanced, Aggressive et Extreme. Les valeurs actives sont ce que le runtime applique lorsque le mode est activé. L'interface copie le profil sélectionné dans les valeurs actives avant d'appliquer le mode.

## À quoi s'attendre visuellement

Selon le profil, le viewport peut devenir :

- De résolution inférieure.
- Non éclairé (Unlit).
- Moins détaillé.
- Moins ombragé.
- Sans brouillard.
- Non rafraîchi en temps réel jusqu'à interaction ou rafraîchissement manuel.

C'est le comportement attendu. L'objectif est la vitesse d'interaction et non la qualité de rendu finale.

## Ce que le plugin ne fait pas

- Il ne modifie pas les paramètres d'exécution des jeux packagés.
- Il ne modifie pas de manière permanente les paramètres de rendu du projet.
- Il ne réécrit pas définitivement les assets de cartes.
- Il ne remplace pas le travail de scalabilité Unreal, LOD, HLOD, Nanite ou d'optimisation de contenu.
- Il ne garantit pas des résultats identiques sur toutes les versions du moteur et les forks de rendu personnalisés.

## Habitude pratique

Utilisez Lightweight Editor Mode comme un mode d'édition. Désactivez-le avant l'évaluation finale, avant de signaler des bugs de rendu et avant de prendre des captures d'écran de production ou pour le Marketplace.

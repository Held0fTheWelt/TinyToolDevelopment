<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/LightweightEditorMode/architecture.md -->
# Guide de démarrage rapide

Ce guide vous accompagne de l'installation jusqu'à un **résultat visible** : un viewport d'éditeur plus rapide et réactif que vous pouvez restaurer intégralement en un clic. Lightweight Editor Mode fonctionne en toute autonomie — aucun autre plugin n'est requis.

## Ce que vous obtiendrez après ce guide

Un profil d'édition réversible "léger" activé (viewport plus rapide), et les connaissances nécessaires pour changer de profil et restaurer l'état d'origine de votre éditeur à la demande.

## Prérequis

- Éditeur Unreal Engine 5 (le plugin affecte uniquement le viewport de l'éditeur, jamais le jeu packagé à l'exécution).
- Aucun logiciel tiers, compte ou runtime supplémentaire n'est requis. Voir [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md).

## 1. Installation et activation

1. Ajoutez **Lightweight Editor Mode** depuis votre bibliothèque Fab à votre projet (ou installez-le dans le moteur).
2. Ouvrez **Edit → Plugins**, activez **Lightweight Editor Mode** et redémarrez l'éditeur lorsque demandé.

## 2. Ouvrir l'outil (Premier résultat)

1. Ouvrez **Tools → Performance → Lightweight Editor Mode**. Un onglet ancrable s'ouvre avec un menu déroulant de profils, un bouton de bascule et une case à cocher *Enable on Editor startup*.
2. Sélectionnez le profil **Balanced** (le paramètre par défaut recommandé).
3. Cliquez sur **Enable Lightweight Mode**.

**Résultat attendu :** le viewport se met à jour immédiatement — Balanced réduit le pourcentage d'écran et la scalabilité, désactive l'éclairage coûteux et force le mode Unlit / non temps réel. L'éditeur devient immédiatement plus réactif.

## 3. Un exemple concret : Changer de profil puis restaurer

1. Lorsque le mode est activé, changez le menu déroulant de profil pour **Aggressive**. Le viewport se rafraîchit avec des paramètres plus agressifs (pourcentage d'écran plus bas, faible scalabilité, suppression des ombres et du brouillard coûteux). Votre état d'origine avant l'activation reste préservé.
2. Cliquez sur **Disable Lightweight Mode**.

**Résultat attendu :** l'éditeur restaure vos niveaux de scalabilité sauvegardés, vos surcharges de variables de console, vos modes d'affichage de viewport et l'état temps réel — vous revenez exactement là où vous avez commencé.

> Les profils sont optimisés pour la réactivité et non pour la fidélité visuelle, attendez-vous donc à des viewports en plus basse résolution, non éclairés (Unlit) et moins ombragés lorsque le mode est actif. **Désactivez le mode avant d'évaluer l'éclairage ou de prendre des captures d'écran.**

## 4. Personnaliser les profils

Ouvrez **Project Settings → Plugins → Lightweight Editor Mode** pour modifier les valeurs des profils Mild / Balanced / Aggressive / Extreme. Le profil sélectionné est copié dans les valeurs actives avant l'application du mode. Voir [PerformanceTuningReference.md](PerformanceTuningReference.md).

## 5. Optionnel : Activer au démarrage de l'éditeur

Cochez **Enable on Editor startup** pour que le mode s'active automatiquement dès que les viewports de l'éditeur existent au prochain lancement.

## 6. Étapes suivantes

- Comportement complet par profil et flux de travail recommandés : [UserManual.md](UserManual.md).
- Référence de tous les paramètres : [SettingsReference.md](SettingsReference.md).
- Problèmes (ex. état obsolète après redémarrage → *Restore Lightweight State*) :
  [TROUBLESHOOTING.md](TROUBLESHOOTING.md) et [FAQ.md](FAQ.md).

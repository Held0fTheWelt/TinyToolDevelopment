<!-- doc-provenance: AKDB:plugins/SmartContentDiet/architecture.md; docs/architecture/plugins/SmartContentDiet/product-facts.yml; reconciled 2026-07-16 -->
# Démarrage rapide

Ce guide vous accompagne de l'installation jusqu'à un **résultat concret** : un scan des actifs de votre projet avec des résultats d'optimisation, et (en option) une correction sûre appliquée après révision, avec un rapport avant/après. La boucle principale de Smart Content Diet fonctionne de manière autonome — **aucun AI, plugin pair ou outil externe n'est requis**.

> **⚠ Sécurité avant tout.** L'application de corrections, de réductions, de déplacements/suppressions d'actifs, de mises à jour de la ligne de base ou d'écritures de gouvernance **modifie les actifs du projet**. Effectuez ces actions uniquement dans un espace de travail **sauvegardé, sous contrôle de version et jetable** — jamais sur des sources non protégées. Les scans et les aperçus sont en lecture seule et sûrs.

## Ce que vous aurez après ce guide

L'outil ouvert dans votre rôle choisi, un scan Quick Safe terminé avec des résultats, et une compréhension de la manière d'apercu et d'appliquer des optimisations sûres, ainsi que de lire le delta avant/après.

## Prérequis

- Éditeur Unreal Engine 5.4+ avec un projet contenant des actifs de contenu.
- Aucun logiciel tiers, compte, modèle AI ou runtime externe requis. Voir
  [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md).

## 1. Installation et activation

1. Ajoutez **SmartContentDiet** depuis votre bibliothèque Fab au projet (ou installez-le dans le moteur).
2. Ouvrez **Édition → Plugins**, activez **SmartContentDiet**, et redémarrez lorsque demandé.

## 2. Ouvrir l'outil et choisir un rôle (Premier résultat)

1. Ouvrez **Outils → Outils de contenu → Smart Content Diet**.
2. Dans le sélecteur d'audience de l'en-tête (ou **Paramètres**), choisissez votre rôle :
   - **Débutant** — Aperçu, Optimiser, Résultats, Paramètres ; plus d'explications.
   - **Ingénieur / Producteur (avancé)** — ajoute Préréglage et Gouvernance (Tendance, Dette, Budget,
     Propriété, Scan profond), et Redondance lorsqu'un fournisseur de similarité externe est enregistré.
3. Laissez la **profondeur de scan** sur **Quick Safe** (par défaut — registre/métadonnées uniquement, aucun chargement d'actif ; rapide).
4. Cliquez sur **Scan Quick Safe** dans l'en-tête.

**Sortie attendue :** le scan se termine et l'onglet **Aperçu** résume les résultats (ce qui peut être amélioré en toute sécurité). Ceci est en lecture seule.

## 3. Exemple concret : Aperçu et application d'une correction sûre

> Sauvegardez / validez votre projet au préalable (voir la note de sécurité ci-dessus).

1. Ouvrez l'onglet **Optimiser** → **File d'attente d'optimisation sûre**.
2. Cliquez sur **Aperçu sûr** pour voir les optimisations sûres en file d'attente et le delta avant/après projeté (toujours en lecture seule).
3. Cliquez sur **Appliquer sûr** pour appliquer la file d'attente sûre. Après une application réussie (ou une correction d'actif unique issue d'un détail des **Résultats**), le shell **relance automatiquement un scan**.
4. Comparez les compteurs de file d'attente et le résumé du delta dans le panneau Optimiser.

**Sortie attendue :** les optimisations sûres sont appliquées et un rapport d'application JSON est écrit sous :

```text
Saved/SmartContentDiet/OptimizationQueue/<timestamp>/
```

## 4. Profondeurs de scan

| Profondeur | Charge les actifs ? | Utilisation |
| --- | --- | --- |
| **Quick Safe** (par défaut) | Non | Rapide « Que puis-je améliorer en toute sécurité ? » |
| **Complet** | Oui | Résultats actionnables sur maillage/texture/matériau |
| **Profond** | Oui | Le plus lent ; métriques profondes de matériau/maillage statique (Gouvernance → Scan profond) |

L'étiquette et l'info-bulle du bouton de l'en-tête se mettent à jour avec la profondeur sélectionnée, que chaque exécution d'analyseur respecte.

## 5. Prochaines étapes

- Shell éditeur, onglets, résultats, gouvernance : [../Resources/UI_AND_BEHAVIOR.md](../Resources/UI_AND_BEHAVIOR.md).
- File d'attente d'optimisation sûre (seaux, règles de sécurité, schéma de rapport) :
  [../Resources/OPTIMIZATION_QUEUE.md](../Resources/OPTIMIZATION_QUEUE.md).
- Paramètres et rôles : [SettingsReference.md](SettingsReference.md).
- Problèmes : [TROUBLESHOOTING.md](TROUBLESHOOTING.md) et [FAQ.md](FAQ.md).

> **Optionnel / avancé :** SCD propose également un commandlet sans tête pour CI (`-QuickSafe`, `-FullScan`,
> `-DeepScan`, `-OptimizationQueueReport`, `-ApplySafeQueue`) et — uniquement si vous possédez également
> **Unreal Capability Mesh (UCM)** — des routes d'écosystème déclarées lors de l'installation. Aucun n'est nécessaire
> pour le flux de travail éditeur ci-dessus ; voir l'[index de documentation](README.md).

<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/LogLevelEditor/architecture.md -->
# Guide de démarrage rapide

Ce guide vous accompagne de l'installation jusqu'à un **résultat concret** : le niveau de détail (verbosity) d'une catégorie de journal modifié et enregistré comme une surcharge persistante résistant aux redémarrages de l'éditeur. Log Level Editor fonctionne de manière autonome — aucun autre plugin n'est requis.

## Ce que vous obtiendrez après ce guide

L'outil ouvert affichant la liste des catégories de journaux de votre projet, la verbosité d'une catégorie modifiée, et cette surcharge enregistrée de manière persistante dans le DataAsset du plugin.

## Prérequis

- Éditeur Unreal Engine 5.
- Aucun logiciel tiers, compte ou runtime supplémentaire n'est requis. Voir [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md).

## 1. Installation et activation

1. Ajoutez **LogLevelEditor** depuis votre bibliothèque Fab à votre projet (ou installez-le dans le moteur).
2. Ouvrez **Edit → Plugins**, activez **LogLevelEditor** et redémarrez l'éditeur lorsque cela vous est demandé.

## 2. Ouvrir l'outil (Premier résultat)

1. Ouvrez **Tools → Log Tools → Log Level Editor**. Un onglet ancrable s'ouvre et analyse le code source de votre projet (et de vos plugins) à la recherche de catégories de journaux.
2. Chaque ligne affiche le **nom de la catégorie** (ex. `LogTemp`), son **niveau par défaut détecté**, son **niveau actuel**, et le **chemin source** si disponible.

Vous voyez désormais chaque catégorie de journal découverte avec sa verbosité en direct.

## 3. Un exemple concret : Modifier la verbosité d'une catégorie

1. Utilisez la zone de recherche pour trouver `LogTemp`.
2. Cliquez sur le bouton de verbosité **Warning** dans cette ligne.

**Résultat attendu :** le plugin exécute la commande de console Unreal correspondante, la ligne se met à jour vers `Warning`, et la modification est enregistrée sous forme de surcharge persistante dans le DataAsset du plugin (pour être réappliquée au prochain démarrage de l'éditeur).

3. Pour annuler : sélectionnez la valeur **par défaut détectée** pour la ligne. Lorsque la valeur sélectionnée correspond au niveau par défaut détecté, le plugin supprime automatiquement la surcharge persistante afin de garder le DataAsset concentré sur les vraies modifications.

## 4. Emplacement des surcharges

Les surcharges persistantes sont stockées dans le `ULogLevelDataAsset` configuré (défini via **LogLevelDataAsset** dans les paramètres). Les surcharges enregistrées sont réappliquées lors du démarrage de l'éditeur dès que le moteur peut accepter les commandes de console.

## 5. Settings

Ouvrez les paramètres du plugin (Project/Editor settings → Log Level Editor) pour contrôler :

- `LogLevelDataAsset`, `bAutoSaveLogLevelDataAsset`
- `bShowToolbarButton`
- `bAlsoListEnginePluginChannels`, `bAlsoListEngineSourceChannels` (les scans du moteur sont coûteux)
- `LogChannelsToHide`, `LogChannelsToHideTemporary`

Voir [SettingsReference.md](SettingsReference.md).

## 6. Étapes suivantes

- Flux de travail complet (masquage temporaire vs permanent, travail en équipe, application au démarrage) :
  [UserManual.md](UserManual.md).
- Problèmes : [TROUBLESHOOTING.md](TROUBLESHOOTING.md) et [FAQ.md](FAQ.md).

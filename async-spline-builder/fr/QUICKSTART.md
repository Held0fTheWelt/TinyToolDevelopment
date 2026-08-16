<!-- doc-provenance: product-facts.yml reconciled 2026-07-15; source AKDB:plugins/AsyncSplineBuilder/architecture.md -->
# Guide de démarrage rapide

Ce guide vous accompagne de l'installation jusqu'à un **résultat visible** : un maillage de route/piste généré le long d'une spline que vous contrôlez. Async Spline Builder fonctionne de manière autonome — aucun autre plugin n'est requis.

## Ce que vous obtiendrez après ce guide

Un `Spline Generating Actor` dans votre niveau avec une route construite à partir de sections de maillage de spline que vous pouvez remodeler en déplaçant des points de spline et régénérer à la demande.

## Prérequis

- Éditeur Unreal Engine 5 et un niveau ouvert.
- Au moins un **maillages de route** qui se répète le long de son axe X local (voir étape 3 / Création de maillage dans le manuel utilisateur). Vous pouvez utiliser n'importe quel maillage répétitif de votre projet pour commencer.
- Aucun logiciel tiers, compte ou runtime. Voir [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md).

## 1. Installer et activer

1. Ajoutez **AsyncSplineBuilder** depuis votre bibliothèque Fab au projet (ou installez-le dans le moteur).
2. Ouvrez **Edit → Plugins**, activez **AsyncSplineBuilder** et redémarrez quand demandé.

## 2. Ouvrir le panneau (Premier résultat)

1. Ouvrez ou créez un niveau.
2. Ouvrez **Tools → Track Tools → Async Spline Builder**. Le panneau comporte les onglets **Build**, **Segments** et **Terrain**.

## 3. Un exemple pratique : construire une piste

1. Dans l'onglet **Build**, cliquez sur **Create Actor** (cela instancie un `ASplineGeneratingActor`), ou sélectionnez-en un existant et cliquez sur **Use Selection**.
2. Dans **Setup**, assignez un maillage répétitif à `MainMesh` (requis). Optionnellement, assignez `StartMesh` et `EndMesh`.
3. Dans le viewport, déplacez les points de spline de l'actor pour former le parcours.
4. Cliquez sur **Validate** (ceci vérifie que `MainMesh` est défini et que la spline est générable).
5. Cliquez sur **Build Now**.

**Résultat attendu :** L'actor génère des sections de route `USplineMeshComponent` le long de la spline. Déplacez un point de spline et cliquez sur **Rebuild** pour voir la route se mettre à jour.

> Pour les longues pistes, activez **Use Async Build** et définissez **SegmentsPerTick** pour que la génération soit fractionnée sur plusieurs ticks et que l'éditeur reste réactif. Utilisez **Cancel** pour arrêter une génération asynchrone en cours.

## 4. Aller plus loin (Optionnel)

- Onglet **Segments** : maillages par segment, interruptions de saut (`JumpGapsByPoints`) et dénivelés.
- Onglet **Terrain** : alignement sur le paysage, déformation de hauteur et **murs de tènement** procéduraux (`bGenerateGroundWalls`). Voir [LandscapeAndWalls.md](LandscapeAndWalls.md).
- **Asset de données :** sauvegardez/chargez des agencements avec `WriteSplineToDataAsset` / `ReadSplineFromDataAsset`.

## 5. Étapes suivantes

- Flux de travail complet, données par segment, interruptions, dénivelés, murs, déformation du paysage : [UserManual.md](UserManual.md).
- Paramètres : [SettingsReference.md](SettingsReference.md).
- Problèmes : [TROUBLESHOOTING.md](TROUBLESHOOTING.md) et [FAQ.md](FAQ.md).

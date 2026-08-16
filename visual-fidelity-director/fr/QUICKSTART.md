<!-- doc-provenance: AKDB:plugins/VisualFidelityDirector/architecture.md; docs/architecture/plugins/VisualFidelityDirector/product-facts.yml; reconciled 2026-07-12 -->
# Démarrage rapide

Ce guide vous accompagne de l'installation à un résultat concret : le cockpit Visual Fidelity Director ouvert avec une vue de profil rafraîchie et une comparaison de profils côte à côte.

## Ce que vous obtiendrez après ce guide

Le cockpit VFD ouvert dans Unreal Editor, l'échantillonnage des métriques en direct démarré, un axe de composition examiné avec les détails de variante et de provenance, et une comparaison effectuée par rapport à un second profil.

## Exigences

- Éditeur Unreal Engine 5.4 sur Win64, Linux ou Mac.
- Un projet capable de charger des plugins d'éditeur.
- Aucun logiciel tiers, compte, service d'IA ni autre plugin Tiny Tool.

## 1. Installer et activer

1. Ajoutez **VisualFidelityDirector** depuis votre bibliothèque Fab au projet, ou installez-le dans l'engine.
2. Ouvrez **Édition > Plugins**.
3. Recherchez **Visual Fidelity Director**.
4. Activez le plugin et redémarrez Unreal Editor lorsque cela vous est demandé.

Si vous installez un package de plugin avec code source uniquement dans un projet C++, laissez Unreal compiler les modules du projet au prochain démarrage de l'éditeur.

## 2. Ouvrir le Cockpit

1. Ouvrez **Tiny Tools > Visual Fidelity Director**.
2. Confirmez que la page **Cockpit** est active (par défaut).
3. Examinez la bannière d'état, le sélecteur de profils et la barre de métriques.

Résultat attendu :

- Le titre de l'onglet ancrable est **Visual Fidelity Director**.
- La barre de profils liste les profils connus à partir de `Saved/VisualFidelityDirector/profiles/` ainsi que le contexte intégré/projet.
- La barre de métriques se remplit sur plusieurs ticks de l'éditeur (échantillonnage multi-images) ou affiche un état indisponible explicite.

## 3. Exemple concret : Examiner un axe

1. Cliquez sur **Refresh** sur la carte d'action du Cockpit.
2. Sélectionnez n'importe quelle bande d'axe de composition (par exemple **Anti-Aliasing** ou **Upscaling**).
3. Dans le tiroir de détails de l'axe, examinez :
   - le **chemin d'héritage** depuis le profil racine jusqu'au profil actif ;
   - les lignes de **provenance** pour les paramètres compilés ;
   - les **résultats locaux à la commande** pour cet axe.
4. Modifiez la boîte combinée **Variant** lorsque plusieurs variantes de pipeline sont disponibles. Les variantes indisponibles restent visibles mais désactivées avec la preuve de compatibilité.

Résultat attendu :

- Les mises à jour des curseurs d'intention reflètent la variante sélectionnée.
- La provenance et les résultats se rafraîchissent pour l'axe sélectionné.
- Aucun fichier de projet ne change tant que vous n'utilisez pas l'application gouvernée ou l'aperçu d'application des Expert Tools.

## 4. Exemple concret : Comparer deux profils

1. Faites défiler jusqu'à la carte **Profile Comparison** sur la page Cockpit.
2. Choisissez un profil dans **Compare against** dans le menu déroulant.
3. Lisez le résumé de la différence par axe.

Résultat attendu :

- Les axes divergents sont listés avec les détails au niveau des paramètres.
- Les axes correspondants ne montrent aucune ligne de différence.
- La comparaison utilise le même comparateur au moment de l'exécution que `UVFDCockpitBlueprintLibrary::CompareFidelityProfiles`.

## 5. Optionnel : Snapshot des Expert Tools

1. Basculez sur la page **Expert Tools**.
2. Cliquez sur **Export Snapshot**.

Résultat attendu :

- `Saved/VisualFidelityDirector/reports/<timestamp>/quality_snapshot.json` existe.
- Les dernières copies apparaissent sous `Saved/VisualFidelityDirector/reports/`.

Ce chemin préserve le workflow de snapshot et de recette 1.x pour les utilisateurs qui préfèrent un examen basé sur les rapports.

## 6. Optionnel : Application permanente gouvernée

Ne continuez que si vous avez l'intention d'écrire des fichiers de configuration de projet.

1. Sur la page Cockpit, cliquez sur **Build Destinations** dans le tiroir d'application.
2. Examinez chaque résumé de destination (Scalability, fichier renderer ini, Device Profiles).
3. Cochez l'approbation uniquement pour les destinations que vous acceptez.
4. Cliquez sur **Apply Approved**.

Résultat attendu :

- Des sauvegardes horodatées et un manifeste de restauration sous la racine de sauvegarde de configuration VFD.
- Rapport d'application avec les résultats de vérification.
- **Rollback** restaure les fichiers sauvegardés si une vérification échoue.

## 7. Emplacement des sorties

```text
Saved/VisualFidelityDirector/profiles/
Saved/VisualFidelityDirector/reports/<timestamp>/
Saved/VisualFidelityDirector/recipes/
```

## 8. Étapes suivantes

- Liste complète des opérations : [UserManual.md](UserManual.md)
- Commandes et fonctions Blueprint : [SettingsReference.md](SettingsReference.md)
- Problèmes et solutions : [TROUBLESHOOTING.md](TROUBLESHOOTING.md)
- Réponses sur la compatibilité et la sécurité : [FAQ.md](FAQ.md)

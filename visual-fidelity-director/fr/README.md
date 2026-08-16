<!-- doc-provenance: AKDB:plugins/VisualFidelityDirector/architecture.md; docs/architecture/plugins/VisualFidelityDirector/product-facts.yml; reconciled 2026-07-12 -->
# Documentation de Visual Fidelity Director

Ce dossier contient la documentation acheteur fournie pour Visual Fidelity Director. Le workflow principal est autonome : activez le plugin, ouvrez le cockpit, examinez les profils de fidélité et les axes de composition, inspectez les preuves, approuvez éventuellement les écritures de configuration gouvernées et utilisez les Expert Tools pour les workflows classiques de snapshots/recettes sans nécessiter un autre plugin ou un service externe.

La documentation actuelle du package est harmonisée pour la version `2.0.0` et l'état de publication `In Publishment`.

## Commencez ici

- [QUICKSTART.md](QUICKSTART.md) : installation, activation, rafraîchissement du premier cockpit et tâche de comparaison de profils.
- [UserManual.md](UserManual.md) : chaque action du cockpit, des preuves et des Expert Tools.
- [SettingsReference.md](SettingsReference.md) : commandes, chemins de profils, fonctions de bibliothèque Blueprint, sorties de rapports et comportement d'application.
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md) : problèmes courants et solutions.
- [FAQ.md](FAQ.md) : réponses sur la compatibilité, la sécurité, MRQ, les captures d'écran et le support.
- [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md) : déclaration de dépendances externes.

## Entrée dans le Cockpit

Ouvrez Visual Fidelity Director depuis **Tiny Tools > Visual Fidelity Director** (section Performance).

L'onglet ancrable propose trois pages :

| Page | Objectif |
| --- | --- |
| **Cockpit** | Barre de profils, métriques en direct multi-images, neuf axes de composition, sélecteur de variantes, curseurs d'intention, détails de l'axe avec chemin d'héritage, provenance, résultats, comparaison de profils et application gouvernée permanente. |
| **Evidence** | Onze blocs de preuves à voies fixes associés aux axes de composition. |
| **Expert Tools** | Panneau de commande 1.x intégré pour les snapshots, recettes, scanner, aperçu d'application et rapports hérités. |

## Profils et rapports

Les profils de fidélité se trouvent sous :

```text
Saved/VisualFidelityDirector/profiles/
```

Les rapports des Expert Tools et des workflows de validation se trouvent sous :

```text
Saved/VisualFidelityDirector/reports/
```

Les copies de recettes restent sous :

```text
Saved/VisualFidelityDirector/recipes/
```

## Surface Blueprint

Les appelants Blueprint d'exécution utilisent `UVFDCockpitBlueprintLibrary` (mêmes services C++ que l'interface du cockpit). Un asset de démonstration empaqueté est livré à l'emplacement `Content/Blueprints/BPF_VFD_API`.

## Modèle de sécurité

- L'examen du cockpit, les preuves et les actions de comparaison sont en lecture seule, sauf si vous utilisez le tiroir d'application gouvernée.
- **L'application permanente gouvernée** écrit uniquement dans les groupes Scalability de `DefaultGameUserSettings.ini`, les paramètres de rendu de `DefaultEngine.ini` et `DefaultDeviceProfiles.ini`, et uniquement après approbation explicite par destination avec prise en charge de la sauvegarde, de la vérification et de la restauration.
- **Expert Tools > Preview Apply + Rollback** reste le chemin de prévisualisation CVar de la session.
- Les assets, matériaux, Post Process Volumes, préréglages MRQ, LevelSequences, Blueprints et paramètres d'accessibilité restent bloqués.

## Schémas

Les fichiers de schéma d'exécution empaquetés se trouvent sous `Schemas/` à la racine du plugin.

## Fichiers associés

- [../README.md](../README.md) : aperçu du produit.
- [../CHANGELOG.md](../CHANGELOG.md) : historique des versions.

<!-- doc-provenance: product-facts.yml reconciled 2026-07-01; source AKDB:plugins/AssetLoaderStudio/architecture.md -->
# Manuel utilisateur d'Asset Loader Studio

Ouvrez l'espace de travail via **Tiny Tools -> Asset Loader Studio -> Asset Loader Studio**.

Asset Loader Studio est conçu autour d'une seule boucle de révision : inspecter, valider, prévisualiser, appliquer, auditer. Vous pouvez vous arrêter à l'étape d'inspection, ou poursuivre avec des modifications gouvernées si le profil de permissions actif le permet.

L'espace de travail contient sept vues :

- **Graph** affiche les nœuds d'actifs, de lignes, de champs, de références et de diagnostics.
- **Table** affiche les lignes DataAsset/DataTable conscientes du schéma et les champs modifiables.
- **Validation** explique les références manquantes, les chemins invalides, les doublons d'identifiants et les blocages de permissions.
- **Jobs** affiche l'état de la dernière demande de chargement en temps d'exécution.
- **Inspector** affiche le mode actif, le profil de permissions, la dernière prévisualisation et le dernier rapport d'application.
- **History** conserve les actions récentes de l'espace de travail.
- **Governance** affiche le profil actif, les remplacements de route, l'état d'audit et les actions de profil.

Les modes contrôlent l'autorité de mutation :

- **Simple** utilise le profil en lecture seule.
- **Guided** permet des modifications échelonnées sûres avec approbation.
- **Expert** permet des prévisualisations de masse/persistantes plus étendues et nécessite toujours une approbation avant l'application.

Utilisez **Inspect** après avoir saisi un chemin d'objet complet tel que `/Game/Data/DT_Items.DT_Items`. Utilisez les entrées Row, Field et New Value pour prévisualiser une mise à jour structurée de champ. **Apply** exécute uniquement la dernière prévisualisation approuvée et marque les packages modifiés comme « sales » (dirty) pour un enregistrement explicite.

## Boucle de révision

1. Inspectez l'actif source.
2. Vérifiez l'état du graphe/table et les diagnostics.
3. Sélectionnez un profil correspondant au niveau d'autorité dont vous avez besoin.
4. Prévisualisez l'opération et vérifiez les cibles, le hachage du plan, les comptes affectés, le risque et les conseils de récupération.
5. Appliquez uniquement la prévisualisation que vous venez de réviser.
6. Inspectez le rapport d'application et l'historique d'audit.
7. Enregistrez manuellement les packages sales après la révision.

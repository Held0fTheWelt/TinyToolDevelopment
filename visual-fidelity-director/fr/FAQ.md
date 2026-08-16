<!-- doc-provenance: AKDB:plugins/VisualFidelityDirector/architecture.md; docs/architecture/plugins/VisualFidelityDirector/product-facts.yml; reconciled 2026-07-12 -->
# FAQ

## VFD remplace-t-il le rendu ou l'anti-aliasing d'Unreal ?

Non. Il s'agit d'une couche de diagnostic, de profil, de preuves, de comparaison, de recette, d'évaluation à blanc, de scanner et de recommandation au-dessus des systèmes de rendu existants d'Unreal.

## Qu'est-ce qui a changé dans la version 2.0.0 ?

La version `2.0.0` ajoute le cockpit centré sur le profil (sélecteur de variantes, chemin d'héritage, provenance, résultats, comparaison de profils, application gouvernée permanente, métriques en direct multi-images), `UVFDCockpitBlueprintLibrary` et les assets de démonstration Blueprint empaquetés. La page Expert Tools intégrée conserve le workflow de snapshot et de recette 1.x.

## Nécessite-t-il une IA ou des services cloud ?

Non. VFD n'a aucune exigence en matière d'IA externe, de cloud, de Python, de Node.js ou de compte.

## A-t-il besoin d'autres plugins Tiny Tool ?

Non. Le workflow principal est autonome.

## Quelle version d'Unreal est ciblée ?

Visual Fidelity Director prend en charge Unreal Engine 5.4 à 5.8 via le descripteur de branche d'engine correspondant et prend en charge Win64, Linux et Mac.

## Peut-il modifier mon projet ?

Par défaut, non. L'application permanente gouvernée ne peut écrire dans seulement trois destinations de configuration lorsque vous les approuvez explicitement : les groupes Scalability dans `DefaultGameUserSettings.ini`, les paramètres de rendu dans `DefaultEngine.ini` et Device Profiles dans `DefaultDeviceProfiles.ini`. Expert Tools **Preview Apply + Rollback** peut définir temporairement des CVars de session d'éditeur prises en charge puis les restaurer. Les assets, matériaux, Post Process Volumes et préréglages MRQ ne sont pas modifiés.

## Lumen Deep Scan modifie-t-il les maillages ou les matériaux ?

Non. L'analyse approfondie Lumen écrit des résultats de révision à partir des métadonnées du snapshot et de l'Asset Registry. Elle ne modifie pas les paramètres des cartes Static Mesh, les graphes de matériaux, les drapeaux de partage de cartes de matériaux, la configuration du projet ou les préréglages MRQ.

## Capture-t-il des captures d'écran ?

Le workflow A/B des Expert Tools écrit des rapports de comparaison basés sur les métadonnées uniquement, à moins qu'un workflow futur ne fournisse des chemins de captures d'écran. Utilisez les rapports pour lier les décisions et capturer les preuves visuelles manuellement lorsque cela est nécessaire.

## Pourquoi certains résultats sont-ils « Confiance moyenne » ?

De nombreux artefacts visuels dépendent du contenu et du mouvement. VFD sépare les faits des heuristiques afin que vous puissiez diriger un examen manuel sans traiter les métadonnées comme une preuve.

## Où vont les profils et les rapports ?

```text
Saved/VisualFidelityDirector/profiles/
Saved/VisualFidelityDirector/reports/
Saved/VisualFidelityDirector/recipes/
```

## Puis-je utiliser VFD depuis les Blueprints ?

Oui. `UVFDCockpitBlueprintLibrary` expose les fonctions de profils, de preuves, de capacités et d'application gouvernée. Consultez `Content/Blueprints/BPF_VFD_API` pour des exemples câblés.

## Qui contacter pour obtenir de l'aide ?

Utilisez l'e-mail de support figurant dans le descripteur du plugin :
`support@tiny-tool-development.com`.

Discord : `#support` (voir la fiche du produit une fois publiée).

<!-- doc-provenance: AKDB:plugins/UnrealCapabilityMesh/architecture.md; docs/architecture/plugins/UnrealCapabilityMesh/product-facts.yml; reconciled 2026-07-19 -->
# Dépannage

## Échec du chargement de la configuration

Vérifiez `Saved/UnrealCapabilityMesh/setup_validation_report.json`.

Causes fréquentes :

- pas de fichier `project_profile.json` dans les racines de configuration intégrées, des plugins ou du projet
- `schema_version` non valide
- faute de frappe dans le chemin d'un manifeste
- JSON mal formé
- tableaux obligatoires manquants tels que `capabilities` ou `endpoints`

Pour une première utilisation, un profil local au projet est optionnel. UCM fusionne son profil par défaut intégré avec les profils fournis par les plugins activés. Créez un profil de projet uniquement pour des surcharges intentionnelles ou des routes propres au projet, puis cliquez sur `Reload Setup`.

## Capacité non découverte

Vérifiez :

- le manifeste de la capacité est référencé par le profil dans sa racine de configuration propriétaire
- la capacité possède un `capability_id` non vide
- l'identifiant de point d'entrée existe
- les noms de plugins requis sont chargés
- les schémas requis existent

Si la capacité appartient à un autre plugin, confirmez que ce plugin est activé et que son package contient `Config/UnrealCapabilityMesh/project_profile.json`. Ne copiez pas la définition du fournisseur dans le projet comme solution de contournement ; rechargez la configuration et inspectez les racines de configuration découvertes.

## Avertissements de définitions en double

La même capacité, le même point d'entrée, le même schéma ou la même route appartenant à un fournisseur existe probablement à la fois dans un profil local au plugin et dans la surcharge du projet.

Supprimez la copie en double du projet, à moins que le projet ne surcharge intentionnellement cette définition. Les profils de projet doivent normalement contenir des modifications de politiques propres au projet ou des routes composées, tandis que les contrats des fournisseurs restent locaux aux plugins.

## TTER n'affiche pas de route UCM valide après le démarrage

Confirmez que l'option Tiny Tool Execution Integration Bridge est activée. Son module d'éditeur recharge la configuration d'UCM avant la découverte TTER. Après avoir activé un nouveau fournisseur ou modifié la configuration, cliquez sur `Reload Setup` et actualisez la découverte des outils.

## Route bloquée

Ouvrez le rapport de route sous `Saved/UnrealCapabilityMesh/route_reports`. Le planificateur de routes enregistre les explications et les motifs de blocage.

Causes fréquentes :

- aucune règle n'autorise les effets secondaires agrégés
- la route utilise `project_mutation` et la règle par défaut la bloque
- la mutation d'actifs exige une approbation ou un essai à blanc (dry-run)
- les schémas d'entrée et de sortie sont incompatibles

Si l'auto-approbation automatique **EXPÉRIMENTALE** est activée dans la colonne d'approbation du catalogue de routes ou dans le profil, désactivez-la avant d'analyser le comportement de gouvernance. La surcharge globale ignore les règles de refus correspondantes, les contrôles de mutation d'actifs/projet de la route, les exigences d'approbation et les exigences d'essai à blanc, et peut donc masquer chacun de ces résultats de politique.

## Échec de l'invocation d'un point d'entrée

Vérifiez `Saved/UnrealCapabilityMesh/invocation_reports`.

Causes fréquentes :

- le chemin de classe ne se résout pas
- le nom de la fonction est incorrect
- la liaison de paramètre ne correspond pas au paramètre de la fonction
- le mode d'invocation est déclaré mais aucun invocateur générique ne le prend encore en charge
- le plugin fournisseur n'est pas chargé

## Rapports vides

Cliquez à nouveau sur `Reload Setup`. Le panneau recharge les manifestes et régénère les diagnostics. Confirmez également que le chemin de configuration du projet est le projet actif, et non un dossier de moteur ou d'exemple.

## Rapport de validation du code source sur le codage en dur

La validation des sources peut signaler des noms de plugins partenaires ou des identifiants de capacités spécifiques au produit dans le code C++ d'UCM. Déplacez les chaînes spécifiques à l'intégration dans le JSON de configuration au lieu d'ajouter des branches C++.

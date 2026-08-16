<!-- doc-provenance: AKDB:plugins/UnrealCapabilityMesh/architecture.md; docs/architecture/plugins/UnrealCapabilityMesh/product-facts.yml; reconciled 2026-07-19 -->
# Référence des manifestes et paramètres

UCM n'expose pas de page `UDeveloperSettings`. La configuration s'effectue via JSON chargé à partir de trois classes de racines de configuration :

1. La configuration par défaut intégrée d'UCM.
2. Les dossiers `Config/UnrealCapabilityMesh` fournis par les plugins fournisseurs activés.
3. La surcharge de projet optionnelle `Config/UnrealCapabilityMesh`.

Les profils sont fusionnés dans cet ordre, la surcharge de projet étant prioritaire. Un profil local au projet n'est pas requis pour une première utilisation ni pour les routes d'un plugin fournisseur activé. Créez-en un uniquement lorsque le projet surcharge intentionnellement la configuration ou possède des routes composées.

## `project_profile.json`

| Champ | Objectif |
| --- | --- |
| `schema_version` | Doit commencer par `capability_mesh.project_profile`. |
| `profile_id` | Identifiant stable du profil actif. |
| `display_name` | Nom de profil lisible par l'utilisateur. |
| `enable_knowledge_store` | Enregistre l'historique d'invocation si vrai. |
| `experimental_self_approval_all_routes` | **EXPÉRIMENTAL, à utiliser à vos propres risques.** Si vrai, les routes configurées utilisent le contournement global décrit ci-dessous. Conservez à false pour un usage normal. |
| `experimental_self_approved_route_ids` | **EXPÉRIMENTAL, à utiliser à vos propres risques.** Identifiants de routes qui utilisent le contournement global lorsque `experimental_self_approval_all_routes` est false. |
| `active_ruleset_id` | Nom de l'ensemble de règles à traiter comme actif. |
| `enabled_capability_manifests` | Chemins des manifestes de capacités. |
| `enabled_endpoint_manifests` | Chemins des manifestes de points d'entrée. |
| `enabled_schema_manifests` | Chemins des manifestes de schémas. |
| `enabled_rule_manifests` | Chemins des manifestes de règles. |
| `enabled_route_manifests` | Chemins des manifestes de routes. |
| `enabled_transform_manifests` | Chemins des manifestes de transformations. |
| `enabled_adapter_manifests` | Chemins des manifestes d'adaptateurs. |
| `enabled_config_target_ids` | Liste autorisée optionnelle pour les cibles Config Admin. Si absent, tous les manifestes cibles sont analysés. |
| `tiny_tool_development_plugins_enabled` | Commutateur d'activation géré par l'IU pour le catalogue Tiny Tool Development. |
| `reflection_metadata_keys` | Clés de métadonnées utilisées lors de la recherche des capacités exposées par réflexion. |
| `optional_scan_paths` | Dossiers ou fichiers supplémentaires à analyser pour rechercher des manifestes JSON. |
| `setup_editor_playground_enabled` | Commutateur d'activation géré par l'IU pour le bac à sable (playground) dans Setup Editor. |
| `setup_editor_show_cpp_source_hints` | Indicateur de profil optionnel pour afficher les indices de code source C++ dans l'arborescence de référence de Setup Editor. |

Les entrées de manifestes relatives sont résolues à partir de la racine de configuration propriétaire du profil, avec des solutions de repli sur le projet et la racine du projet. Pour la personnalisation, ne copiez que le profil ou les manifestes que le projet souhaite surcharger. Conserver les définitions des fournisseurs au niveau du plugin maintient la propriété des routes claire et évite les avertissements de définitions en double.

## Actifs de l'éditeur de configuration (Setup Editor)

| Chemin | Objectif |
| --- | --- |
| `editor/manifest_field_schema.json` | Mappe les chemins de champs JSON aux types de widgets de l'éditeur (`bool`, `enum`, `string_array`, etc.). |
| `editor/plugin_source_hints.json` | Mappe les valeurs `item_id` du catalogue aux dossiers sources des plugins C++ pour la navigation de référence en lecture seule. |
| `playground/` | Manifestes de bac à sable éditables sans liaison de plugin réelle. |
| `tool_catalogs/setup_editor_playground.json` | Élément de catalogue qui ajoute les manifestes du bac à sable à `project_profile.json`. |

## Manifeste de capacité (Capability)

Les capacités déclarent ce qu'un fournisseur peut faire. Chaque capacité possède un identifiant, un titre, une catégorie, des effets secondaires, des ports d'entrée, des ports de sortie et un identifiant de point d'entrée.

## Manifeste de point d'entrée (Endpoint)

Les points d'entrée déclarent comment une capacité est invoquée. Champs importants :

- `endpoint_id`
- `invocation_mode`
- `target`
- `parameters`
- `availability`

Les modes d'invocation pris en charge incluent les fonctions de réflexion, les contrats de fichiers, les fournisseurs de fonctionnalités modulaires, le bridge Python, les commandlets et les déclarations de processus externes. La réflexion, les contrats de fichiers et les fonctionnalités modulaires de fournisseurs d'UCM s'exécutent directement ; le bridge Python, les commandlets et les processus externes sont en découverte uniquement tant que leurs invocateurs génériques ne sont pas implémentés.

## Manifeste de schéma (Schema)

Les schémas décrivent la structure attendue des ports d'entrée et de sortie. UCM utilise les identifiants de schéma pour vérifier la compatibilité.

## Manifeste de règle (Rule)

Les règles décident si une route est autorisée. Effets secondaires courants :

- `read_only`
- `saved_folder_write`
- `project_config_write`
- `asset_mutation`
- `project_mutation`
- `network`
- `ai_completion`

## Manifeste de route (Route)

Les routes définissent des étapes ordonnées. Chaque étape référence un identifiant de capacité et déclare des liaisons d'entrée/sortie.

Les routes de mutation doivent définir `allow_asset_mutation` ou `allow_project_mutation` uniquement lorsque l'opération est intentionnelle. L'exécuteur exige normalement une approbation lors de l'exécution ; fournissez `approval_granted: true`, `approvalGranted: true` ou `approval: "granted"` dans l'entrée de la route à moins que la surcharge d'auto-approbation **EXPÉRIMENTALE** ci-dessous ne soit intentionnellement active.

### Auto-approbation automatique expérimentale

`experimental_self_approval_all_routes` et `experimental_self_approved_route_ids` sont des options de secours explicitement expérimentales pour les tests et les flux de travail locaux à vos propres risques. Lorsqu'elles sont activées, UCM transmet `bExperimentalPolicyBypass=true` lors de la planification et de l'exécution des routes. Les règles de refus correspondantes avec `allow=false` ne bloquent plus la route, les exigences d'approbation et d'essai à blanc au niveau des règles sont ignorées, les contrôles de mutation d'actifs/projet au niveau de la route sont ignorés, et le plan final annule les exigences d'approbation et d'essai à blanc.

Conservez ces deux paramètres désactivés pour les flux de travail normaux et de production. Le catalogue de routes de l'éditeur étiquette ces commutateurs comme **EXPÉRIMENTAL** et précise la portée du contournement. Les hôtes MCP peuvent lire ou modifier ces mêmes paramètres via `mesh_configure_experimental_self_approval` ; l'activation via MCP nécessite `acknowledge_experimental_risk: true`.

## Manifeste de transformation (Transform)

Les transformations associent un JSON source à un JSON cible. Elles sont utilisées pour adapter les sorties d'une capacité en entrées pour une autre.

## Manifeste d'adaptateur (Adapter)

Les adaptateurs associent les fonctions de plugins tiers dans UCM sans ajouter de dépendance C++ directe au hub.

## Configuration de l'administration des actifs

La configuration intégrée sous le propre dossier `Config/UnrealCapabilityMesh` d'UCM déclare les capacités d'administration des DataAsset/DataTable :

- `capability_mesh.asset_admin.export`
- `capability_mesh.asset_admin.import`
- `capability_mesh.asset_admin.sync`

Toutes trois appellent `UCapabilityMeshAssetAdminSubsystem` via des points d'entrée `reflection_subsystem_function`. Les hôtes MCP doivent passer par ces déclarations au lieu d'appeler du code de bridge spécifique au projet.

## Manifeste de cible de configuration

Les cibles d'administration de la configuration sont autorisées séparément des manifestes de routes sous :

```text
Config/UnrealCapabilityMesh/config_targets/*.json
```

Les manifestes cibles utilisent :

```json
{
  "schema_version": "capability_mesh.config_target_manifest.v1",
  "targets": [
    {
      "target_id": "example_plugin.settings",
      "display_name": "Example Plugin Settings",
      "description": "Explains what the target controls and when it should be edited.",
      "kind": "uobject_config",
      "class_path": "/Script/ExamplePlugin.ExamplePluginSettings",
      "required_plugin_names": ["ExamplePlugin"]
    }
  ]
}
```

Valeurs de `kind` prises en charge :

- `uobject_config` : lit et écrit les propriétés de configuration sur un objet par défaut de classe (CDO), puis enregistre la configuration.
- `uobject_instance` : lit et écrit les champs éditables sur une classe d'objet autorisée. Les requêtes doivent inclure `object_path`.
- `json_file` : lit et écrit un fichier JSON déclaré sous un répertoire de base autorisé.

Chaque cible doit inclure une description non vide (`description`) ; Config Admin affiche les descriptions manquantes sous forme d'avertissements car les utilisateurs ont besoin de contexte avant de lire ou d'écrire une cible.

Les routes standard sont `capability_mesh.config_admin.list_targets.v1`, `capability_mesh.config_admin.read_target.v1` et `capability_mesh.config_admin.write_target.v1`. Les routes d'écriture déclarent `project_config_write` et `asset_mutation` afin que les fichiers de configuration, objets de configuration, DataAssets et instances d'objets éditables passent tous par le même parcours d'approbation et d'essai à blanc.

## Manifeste de catalogue d'outils

Les catalogues d'outils se trouvent sous :

```text
Config/UnrealCapabilityMesh/tool_catalogs/*.json
```

Ils regroupent les entrées de configuration en packages basculables par l'IU. Un package peut déclarer des chemins de manifestes de capacités, points d'entrée, schémas, règles, routes, transformations, adaptateurs et identifiants de cibles de configuration. L'IU désactive les packages en supprimant ces entrées de `project_profile.json` ; elle ne supprime pas les fichiers de manifestes.

Les packages de catalogue doivent rester aussi réduits que le permet la limite de propriété. Un package de plugin ne doit ajouter que les capacités, points d'entrée, schémas et cibles de configuration propres à ce plugin. Les flux de travail inter-plugins doivent être des packages de routes distincts faisant référence aux briques déjà activées. Cela permet de conserver des configurations IIS seul, LLM Store seul, UII+IIS et IIS+LLM Store valides sans nécessiter chaque plugin Tiny Tool Development.

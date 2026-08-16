<!-- doc-provenance: AKDB:plugins/UnrealCapabilityMesh/architecture.md; docs/architecture/plugins/UnrealCapabilityMesh/product-facts.yml; reconciled 2026-07-19 -->
# Manuel de l'utilisateur

## Panneau de configuration

Ouvrez le panneau depuis :

```text
Tools -> Unreal Capability Mesh
```

Le panneau est une vue d'opérations techniques pour l'interopérabilité pilotée par des manifestes. Il utilise désormais une bannière d'état et des pages ciblées au lieu d'empiler tous les outils dans une seule vue.

Pages :

- `Overview` : profil actif, comptage d'inventaire, comptage de disponibilité, flux de configuration et contrat MCP.
- `Capabilities` : identifiants de capacités chargées, points d'entrée, effets secondaires, disponibilité, avertissements et manifestes sources.
- `Routes` : catalogue de routes plus planification d'essai (dry-run) et entrée/sortie d'exécution.
- `Governance` : vocabulaire d'effets secondaires actif et décisions de règles.
- `Tiny Tools` : commutateurs de packages de configuration pour le contenu Tiny Tool Development.
- `Setup Editor` : éditeur JSON adapté aux types pour les manifestes de configuration du projet, échantillons de référence en lecture seule et le bac à sable (playground) non contraignant.
- `Config Admin` : cibles de configuration autorisées et préconfigurations de routes pour les opérations de liste/lecture/écriture.
- `Diagnostics` : validation de la configuration, découverte et messages de rechargement.
- `Adapter` : générateur de manifeste de démarrage pour ajouter des capacités déclarées dans la configuration sans dépendance de bridge.

## Tiny Tools

La page `Tiny Tools` est pilotée par les manifestes de catalogue sous :

```text
Config/UnrealCapabilityMesh/tool_catalogs/
```

Le premier commutateur indique si le projet doit utiliser le contenu de configuration de Tiny Tool Development. S'il est désactivé, toutes les entrées de configuration appartenant au catalogue sont supprimées du profil actif. Les commutateurs d'outils individuels ajoutent ou désactivent ensuite les entrées de package déclarées par le catalogue :

- manifestes de capacités
- manifestes de points d'entrée
- manifestes de schémas
- manifestes de règles
- manifestes de routes
- manifestes de transformations
- manifestes d'adaptateurs
- identifiants de cibles de configuration

Il s'agit d'un modèle de désactivation, et non d'une suppression de fichiers. Les fichiers de manifeste restent dans le projet et peuvent être réactivés ultérieurement.

Les packages Tiny Tool sont intentionnellement séparés par propriété. IIS, LLM Store et UII peuvent être activés indépendamment. Les flux de travail inter-plugins sont des commutateurs de routes distincts, de sorte qu'un projet peut utiliser IIS seul, LLM Store seul, UII+IIS ou IIS+LLM Store sans posséder toute la pile.

Le champ de profil `enabled_config_target_ids` limite les cibles de configuration visibles dans Config Admin. Si le champ est absent, Config Admin conserve l'ancien comportement et analyse tous les manifestes cibles.

## Setup Editor

La page `Setup Editor` modifie les manifestes locaux du projet sous `Config/UnrealCapabilityMesh` avec des champs adaptés aux types :

- booléens pour les commutateurs de politique et de profil
- tableaux de chaînes pour `enabled_*_manifests`
- champs énumérés tels que `invocation_mode` et `side_effects`
- objets imbriqués et tableaux d'objets à partir des manifestes de routes, capacités et points d'entrée

L'arborescence de gauche comporte trois racines :

1. `Project Setup` — manifestes de projet éditables, y compris `project_profile.json`.
2. `Playground Sandbox` — manifestes de bac à sable éditables sous `playground/` sans liaison de plugin réelle. Utilisez `Add playground to profile` pour tester l'échec d'activation, ou activez l'élément de catalogue `Setup Editor Playground` dans `Tiny Tools`.
3. `Reference Samples` — manifestes Tiny Tool intégrés en lecture seule groupés par plugin de catalogue, plus les exemples principaux UCM. Utilisez `Copy to project` pour dupliquer un manifeste de référence dans la configuration du projet.

Actions de la barre d'outils :

- `Save` / `Revert` — écrire ou annuler le fichier de manifeste actif.
- `Validate file` — exécuter `FCapabilityMeshSetupLoader::ValidateManifestFile` sur le fichier sélectionné.
- `Reload Setup` — recharger le maillage actif après des modifications de profil ou de manifeste.
- `Open source folder` — ouvrir le chemin du plugin C++ associé à partir de `editor/plugin_source_hints.json` lorsqu'un nœud de plugin de référence est sélectionné.

Les règles de typage des champs se trouvent dans `editor/manifest_field_schema.json`.

## Reload Setup

`Reload Setup` appelle `FCapabilityMeshService::ReloadSetup`.

Il exécute la séquence suivante :

1. Efface les registres et rapports précédents.
2. Découvre la configuration UCM intégrée, les racines de configuration locales aux plugins activés et la surcharge optionnelle du projet.
3. Fusionne leurs fichiers `project_profile.json` par ordre de priorité.
4. Charge les capacités, points d'entrée, schémas, règles, routes, transformations et adaptateurs.
5. Enregistre les définitions chargées.
6. Écrit les diagnostics de configuration et de registre.
7. Exécute la découverte.
8. Écrit les rapports de découverte et de compatibilité.

Les manifestes appartenant à un fournisseur doivent rester sous le dossier `Config/UnrealCapabilityMesh/` du plugin fournisseur. Les manifestes locaux au projet ont une priorité plus élevée et servent aux surcharges intentionnelles ou aux routes composées propres au projet. La duplication des définitions de fournisseur dans le projet peut générer des avertissements de surcharge et masquer la propriété.

Lorsque l'option Tiny Tool Execution Integration Bridge est activée, son module d'éditeur appelle `ReloadSetup` avant d'enregistrer et de découvrir les outils UCM projetés. UCM reste propriétaire des définitions de routes résultantes et de chaque décision de politique.

## Discovered Capabilities

La vue des capacités découvertes affiche l'identifiant de capacité, l'identifiant de fournisseur, le mode d'interopérabilité et la disponibilité. La disponibilité peut être disponible, indisponible, non sécurisée, schéma manquant, approbation requise ou plugin non chargé.

## Diagnostics

La vue des diagnostics affiche les erreurs et avertissements de validation de la configuration ainsi que les messages renvoyés par le rechargement/la découverte. Consultez-la en premier lorsqu'une route ou un point d'entrée n'apparaît pas.

## Routes

Saisissez un identifiant de route et lancez un essai à blanc (dry run). UCM résout les étapes de la route, vérifie la disponibilité des capacités, agrège les effets secondaires, évalue les règles et rédige un rapport de route.

Saisissez l'entrée JSON de la route et exécutez la route lorsque l'essai à blanc est propre. UCM planifie d'abord la route, bloque les violations de politique et les routes nécessitant un essai à blanc, puis invoque chaque point d'entrée dans l'ordre des étapes. Les routes nécessitant une approbation doivent inclure `approval_granted: true` ou `approval: "granted"` dans l'entrée de la route avant d'être exécutées, à moins que l'auto-approbation automatique **EXPÉRIMENTALE** ne soit active pour cette route. Les sorties des étapes et la sortie de la route sont écrites dans `Saved/UnrealCapabilityMesh/route_execution_reports/`.

### Route Catalog

Le **Route Catalog** sur la page Routes répertorie chaque route chargée à partir des manifestes de configuration dans un tableau groupé par plugin :

| Colonne | Contenu |
| --- | --- |
| Plugin / Route | Groupes de plugins extensibles et lignes de routes avec politique, étapes, points d'entrée, effets secondaires et détails des manifestes sources |
| Approve all at own risk | Commandes d'auto-approbation automatique **EXPÉRIMENTALE** |

En-tête de colonne :

- **Approve all at own risk** — commutateur global pour chaque route nécessitant une approbation dans le profil actif. S'il est activé, les cases à cocher par route sont désactivées car toutes les routes soumises à approbation héritent de la surcharge.

Lignes de plugins :

- Flèche d'extension/réduction, nom d'affichage du plugin, nombre de routes et une case à cocher d'approbation par plugin lorsque ce plugin possède des routes soumises à approbation.

Lignes de routes :

- Flèche d'extension/réduction, identifiant de route et texte de détail de la route issu du plan d'essai (dry-run).
- Routes soumises à approbation : case à cocher par route (sauf si **Approve all** est actif).
- Routes ne nécessitant aucune approbation : `n/a` avec une info-bulle expliquant qu'aucune porte d'approbation ne s'applique.

Un avertissement orange au-dessus du catalogue indique que l'auto-approbation automatique active un contournement global des politiques. Les règles de refus correspondantes, les contrôles de mutation d'actifs/projet de la route, les exigences d'approbation et les exigences d'essai à blanc sont ignorés ; les routes activées peuvent donc modifier l'état de l'éditeur sans ces protections.

Les mêmes paramètres persistent dans `project_profile.json` (`experimental_self_approval_all_routes`, `experimental_self_approved_route_ids`) et peuvent être lus ou modifiés via MCP avec `mesh_configure_experimental_self_approval` ; l'activation via MCP exige `acknowledge_experimental_risk: true`. Conservez l'auto-approbation désactivée pour une utilisation normale en production.

La page `Config Admin` peut préparer les identifiants de routes et enveloppes JSON standard dans le lanceur de routes. Cela permet à MCP, aux utilisateurs de l'éditeur et à l'automatisation de partager le même contrat de route.

## Administration des DataAsset et DataTable

`UCapabilityMeshAssetAdminSubsystem` expose des opérations appelables par JSON pour l'administration des DataAsset/DataTable :

- `ExportAdminSurfaceJson` : exporte un DataAsset ou une DataTable dans une enveloppe d'administration portable et peut l'écrire sous `Saved/UnrealCapabilityMesh/asset_admin`.
- `ImportAdminSurfaceJson` : importe une enveloppe précédemment exportée dans un DataAsset ou une DataTable existant.
- `SyncAdminSurfaceJson` : copie les champs éditables d'un DataAsset vers une ligne de DataTable ou d'une ligne de DataTable vers un DataAsset.

Les DataTables composées (Composite DataTables) sont des sources d'exportation sûres. Les écritures directes dans une DataTable composée sont bloquées ; ciblez la DataTable enfant concrète qui doit posséder la ligne.

Exemple d'entrée de route pour une route de synchronisation avec mutation :

```json
{
  "approval_granted": true,
  "request_json": "{\"source_object_path\":\"/Game/Config/DA_Settings.DA_Settings\",\"target_object_path\":\"/Game/Config/DT_Settings.DT_Settings\",\"mode\":\"data_asset_to_data_table\",\"row_name\":\"Default\"}"
}
```

## Administration de la configuration

`UCapabilityMeshConfigAdminSubsystem` expose les cibles de configuration autorisées. C'est la route MCP standard pour les paramètres de plugins et les fichiers de configuration de projet.

Les cibles sont déclarées sous :

```text
Config/UnrealCapabilityMesh/config_targets/
```

Routes courantes :

- `capability_mesh.config_admin.list_targets.v1`
- `capability_mesh.config_admin.read_target.v1`
- `capability_mesh.config_admin.write_target.v1`

Exemple de lecture :

```json
{
  "request_json": "{\"target_id\":\"example_plugin.settings\"}"
}
```

Exemple d'écriture :

```json
{
  "approval_granted": true,
  "request_json": "{\"target_id\":\"example_plugin.settings\",\"fields\":{\"bEnabled\":true}}"
}
```

Les cibles d'instances d'objets, telles qu'un objet de configuration basé sur un actif, nécessitent également `object_path` dans le JSON de la requête. Les cibles de fichiers JSON acceptent `payload` ou `payload_json`.

## Accès MCP

`UCapabilityMeshMcpGatewaySubsystem` expose le rechargement de la configuration, la liste des capacités, l'essai à blanc de route, l'exécution de route et l'invocation de point d'entrée sous forme de fonctions appelables en JSON. Le serveur Unified MCP s'attache à cette passerelle via le fournisseur générique `mesh` lorsque les deux plugins sont chargés.

Noms d'outils UMCP courants :

- `mesh_reload_setup`
- `mesh_list_capabilities`
- `mesh_list_routes`
- `mesh_configure_experimental_self_approval`
- `mesh_dry_run_route`
- `mesh_execute_route`
- `mesh_invoke_endpoint`

Unified MCP Server aplatit également les routes déclarées en outils MCP directs nommés `mesh_route_<sanitized_route_id>_<hash>`. Ces outils acceptent `mode: "dry_run"` pour l'analyse ou `mode: "execute"` pour l'exécution. Si aucun champ `input` ou `input_json` n'est fourni, les arguments restants deviennent l'objet d'entrée de la route. UCM exporte les schemas `input_schema`, `output_schema` et `tool_annotations` issus des routes via `mesh_list_routes` ; UMCP les publie sous forme d'MCP `inputSchema`, `outputSchema` et d'annotations pour chaque outil `mesh_route_*`. Pour les routes courantes qui se lient à `request_json`, UMCP reflète également les arguments aplatis dans ce champ de requête sérialisé afin que l'IA puisse appeler des outils avec des paramètres nommés compréhensibles.

Utilisez `mesh_execute_route` pour l'importation, la synchronisation et les écritures de configuration DataAsset/DataTable afin que la politique de route et les vérifications d'approbation restent actives. Utilisez `mesh_configure_experimental_self_approval` uniquement pour des flux de travail de test ou à vos propres risques **EXPÉRIMENTAUX** ; il peut activer le contournement global des politiques ou pour des identifiants de routes sélectionnés. Utilisez `mesh_list_routes` pour vérifier l'état actuel visible par MCP ; il signale le drapeau expérimental global, les surcharges de routes sélectionnées et le plan effectif contourné par route.

## Intégration UCM principale

Le profil de projet actif connecte les produits Tiny Tool Development avec des routes déclarées dans la configuration. Utilisez cette voie UCM comme modèle d'intégration normal. Les Freebie Bridges sont uniquement destinés aux équipes sans UCM ou aux développeurs qui souhaitent des exemples d'adaptateurs directs.

- `uii_to_iis_context_pack.v1` : preuves UII -> flux d'importation/recherche/pack de contexte IIS, avec exécution de route d'intégration LLM Store si configuré.
- `prs.build_asset_move_plan.v1`, `prs.preview_plan.v1`, `prs.apply_plan.v1`, `prs.rollback.v1` : flux de travail de placement PRS via la politique de route UCM et l'approbation.
- `scd.migration_advice_from_handoff.v1` : contrat/enveloppe de transmission UII -> conseils de migration SmartContentDiet via UCM.
- `capability_mesh.asset_admin.export.v1`, `capability_mesh.asset_admin.import.v1`, `capability_mesh.asset_admin.sync.v1` : administration DataAsset/DataTable via le maillage.
- `capability_mesh.config_admin.list_targets.v1`, `capability_mesh.config_admin.read_target.v1`, `capability_mesh.config_admin.write_target.v1` : administration des paramètres autorisés et des fichiers de configuration via le maillage.

Les routes de mutation de projet ou d'actifs nécessitent toujours une approbation explicite de la route, à moins que la surcharge d'auto-approbation automatique **EXPÉRIMENTALE** ne soit active pour cette route.

## Règles

Les règles décident si une route est autorisée, exige une approbation, exige un essai à blanc (dry-run) ou est bloquée. Les règles sont ordonnées par priorité et sont déclarées en JSON.

## Éditeur d'adaptateur

L'éditeur d'adaptateur écrit un manifeste d'adaptateur simple sous `Config/UnrealCapabilityMesh/adapters`. Il est conçu comme point de départ pour intégrer un autre plugin dans UCM sans ajouter de dépendances C++ directes au hub.

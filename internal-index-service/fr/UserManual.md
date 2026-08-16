<!-- doc-provenance: SAD architecture.md sections 1,5,6,8; facts product-facts.yml; reconciled 2026-07-16 -->
# Manuel de l'utilisateur

## Flux de travail principal

IIS suit un flux de travail de recherche en lecture seule :

1. Importer les preuves préparées.
2. Construire ou rafraîchir le catalogue local.
3. Construire des embeddings lorsque la recherche vectorielle est nécessaire.
4. Rechercher ou construire des packs de contexte.
5. Exposer les mêmes outils en lecture seule aux agents via UMCP.

IIS n'applique pas de mutations au projet.

## Carte des fonctions du produit

| Fonction de la fiche technique | Surface visible par l'acheteur |
| --- | --- |
| `ImportPreparedChunks` | Importe des JSONL de chunks préparés depuis l'onglet Imports du panneau de contrôle ou l'API du service. |
| `Search` | Exécute des recherches lexicales, vectorielles ou hybrides depuis l'onglet Search et l'API du service. |
| `BuildContextPack` | Reconstruit des packs de contexte axés sur les preuves à partir d'une requête ou de résultats sélectionnés. |
| `RunPerfSelfCheck` | Exécute le contrôle automatique de performance synthétique intégré depuis Blueprint/API et les surfaces de console. |
| `RuntimeControlDispatch` | Transmet les verbes observe, tune, act, persist et reset via la surface de contrôle runtime. |
| `AgentRetrievalTools` | Fournit des opérations de recherche d'agent en lecture seule via des contrats locaux et des routes optionnelles UCM/UMCP. |

## Panneau de contrôle

Ouvrir :

```text
Tiny Tools -> AI -> Internal Index Service -> Open Internal Index Service
```

Onglets :

| Onglet | Utilisation |
| --- | --- |
| Dashboard | État de l'index, état des intégrations, raccourci de reconstruction, raccourci de recherche. |
| Index | Importations, construction du catalogue, création/exécution de jobs d'embedding. |
| Use | Recherche parmi les preuves locales. |
| Agents | Contrats d'agent et état de la bridge UMCP. |
| Governance | Posture de lecture seule, chemins locaux, visibilité des bridges et des outils. |
| Diagnostics | Rapports, vue d'ensemble et emplacements des artefacts générés. |
| Settings | Vue intégrée dans le panneau pour `UIISSettings`. |

## Comportement d'importation

L'importation consomme des fichiers JSONL de chunks préparés. Chaque chunk porte des ID, du contenu, des références sources, des métadonnées d'assets/symboles et un état de cycle de vie. IIS valide l'entrée, ajoute les chunks acceptés et écrit des rapports d'importation.

Fichiers importants :

```text
Saved/InternalIndexService/chunks.jsonl
Saved/InternalIndexService/imports/
Saved/InternalIndexService/reports/
```

## Construction du catalogue

La construction du catalogue lit les chunks stockés et produit des structures locales recherchables. Elle filtre les états de cycle de vie inactifs des chunks et écrit un rapport afin que les utilisateurs puissent vérifier les avertissements.

## Recherche

Les champs de requête de recherche incluent le texte de la requête, le mode de recherche, les résultats maximaux, les filtres et les options de pack de contexte. Les résultats contiennent des ID de chunks, des informations de score, des extraits (snippets) et des références sources.

Modes de recherche :

| Mode | Signification |
| --- | --- |
| Lexical | Utilise une correspondance de texte locale sur le catalogue de chunks. |
| Vector | Utilise les embeddings persistés et le back-end vectoriel configuré. |
| Hybrid | Combine les candidats lexicaux et vectoriels. |

## Surface de contrôle en runtime

IIS fournit une surface de contrôle runtime **autarconique** (autark) pour observe → tune → act sans recharger l'éditeur. Elle modifie l'objet `UIISSettings` actif en mémoire (temporaire par défaut) et réapplique immédiatement les leviers en cache tels que `efSearch` de HNSW et le noyau int8 actif.

**Aucune dépendance UCM ou UMCP** — la surface fonctionne de manière autonome depuis Blueprint, C++ et la console de l'éditeur.

### API Blueprint typée (`UIISSubsystem`)

| Méthode | Objectif |
| --- | --- |
| `GetControlState` | Instantané des leviers effectifs et de l'état de la porte de mutation. |
| `SetTuning` | Appliquer des deltas de réglage optionnels par champ (`FIISTuningRequest`). |
| `PersistTuning` | Écrire les surcharges actuelles dans la configuration (`SaveConfig`). |
| `ResetTuning` | Recharger la configuration et annuler les surcharges temporaires. |
| `RunPerfSelfCheck` | Exécuter les charges de travail de performance SYN-2 selon les budgets configurés. |

### Commandes de console

| Commande | Objectif |
| --- | --- |
| `iis.control.state` | Afficher le JSON de l'état de contrôle effectif. |
| `iis.control.tune {json}` | Réglage temporaire (ex: `{"efSearch":128}`). |
| `iis.control.persist` | Persister les surcharges dans la configuration. |
| `iis.control.reset` | Recharger la configuration / annuler les surcharges. |
| `iis.control.diagnostics.recent` | Diagnostics récents par requête (lorsque la rétention est activée). |
| `iis.perf.run` / `iis.perf.last` | Exécuter ou lire le dernier contrôle automatique de performance. |
| `iis.index.sync` / `iis.index.rebuild` / `iis.index.import` | Verbes d'action de maintenance d'index. |

Les verbes de mutation respectent le paramètre **Enable Runtime Control Mutations** dans les paramètres du projet (activé par défaut).

## Embeddings

IIS ne possède pas les identifiants des fournisseurs. La résolution et l'exécution des routes d'embedding sont déléguées via `FIISEmbeddingDiscovery` (`IIISEmbeddingRouteExecutor` via `IModularFeatures`), normalement fournies par une bridge LLM Store qui s'enregistre dans `StartupModule` et se désenregistre dans `ShutdownModule`.

Le flux d'embedding :

1. Construire des jobs pour les chunks nécessitant des vecteurs.
2. Résoudre une route d'embedding.
3. Exécuter les jobs via l'exécuteur enregistré.
4. Persister les enregistrements vectoriels.
5. Mettre à jour les rapports.

## Outils d'agent

Les outils d'agent sont en lecture seule et renvoient du JSON structuré. IIS définit six opérations de recherche autonomes. Les noms de contrats locaux restent disponibles pour l'invocation dans le moteur et via fichier JSON :

| Contrat local | ID de route UCM | Objectif |
| --- | --- | --- |
| `iis_search` | `iis.agent.search.v1` | Rechercher des chunks indexés (charge utile JSON intégrée plus chemin de l'artefact). |
| `iis_get_context_pack` | `iis.agent.get_context_pack.v1` | Construire un pack de contexte compact à partir des résultats de recherche (charge utile JSON intégrée plus chemin de l'artefact). |
| `iis_get_chunk` | `iis.agent.get_chunk.v1` | Récupérer un chunk par son ID. |
| `iis_get_source_references` | `iis.agent.get_source_references.v1` | Renvoyer les références sources pour un chunk. |
| `iis_find_usages` | `iis.agent.find_usages.v1` | Rechercher les enregistrements d'utilisation. |
| `iis_explain_blueprint` | `iis.agent.explain_blueprint.v1` | Résumer les preuves Blueprint indexées (charge utile JSON intégrée plus chemin de l'artefact). |

`iis.index.status.v1` rapporte en outre `catalog_exists`, `chunk_store_records` et `vector_records` afin que les agents puissent vérifier si l'index a été rempli sans lire les fichiers.

Le transport MCP est détenu par Unified MCP Server. IIS ne enregistre pas d'outils MCP lui-même ; la configuration Capability Mesh du projet déclare une route par opération d'agent et UMCP les publie sous forme d'outils génériques `mesh_route_*`. Aucun plugin bridge n'est requis.

## Données et confidentialité

IIS stocke les index générés dans le dossier `Saved` du projet par défaut. Si une racine d'index personnalisée est définie, utilisez un chemin local/privé à moins que votre équipe ne partage intentionnellement les preuves générées.

L'exposition au cloud ne se produit que si une route d'exécuteur d'embedding dans LLM Store utilise un fournisseur cloud.

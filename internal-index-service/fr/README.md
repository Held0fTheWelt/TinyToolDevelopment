<!-- doc-provenance: SAD architecture.md sections 1,2,7,8; facts product-facts.yml; reconciled 2026-07-16 -->
# Internal Index Service

Internal Index Service (IIS) est un plugin Unreal Engine pour l'indexation **locale**, la recherche (retrieval), les packs de contexte et la recherche dédiée aux agents. Il fonctionne exclusivement en lecture seule (retrieval-only) : il ne modifie pas le contenu du projet et ne génère pas de patchs.

## Modules

| Module | Objectif |
| --- | --- |
| `InternalIndexServiceInterface` | Contrats publics pour les chunks, la recherche, les imports, les embeddings et l'accès agent. |
| `InternalIndexService` | Sous-système moteur runtime, catalogue de chunks, back-ends vectoriels, jobs d'embedding, indexation incrémentale. |
| `InternalIndexServiceEditor` | Panneau de contrôle éditeur, bridge Python et entrées de menu Tiny Tools. |

## Ouvrir le panneau de contrôle

```text
Tiny Tools -> AI -> Internal Index Service -> Open Internal Index Service
```

Ou utilisez l'onglet nomade **Internal Index Service** si votre disposition d'interface l'affiche déjà.

Le panneau est organisé comme suit :

| Onglet | Objectif |
| --- | --- |
| **Dashboard** | Cartes d'état pour l'index et les intégrations ; actions rapides (Reconstruire le catalogue). |
| **Overview** | Version du service, racine de l'index, présence du catalogue/vecteur. |
| **Imports** | Transmission UII et résumés des rapports d'importation. |
| **Catalog** | Construire le catalogue et afficher le résumé de génération du catalogue sous `Saved/InternalIndexService/reports`. |
| **Embeddings** | Créer et exécuter des jobs d'embedding persistés via un `IIISEmbeddingRouteExecutor` détecté. |
| **Search** | Recherche lexicale / vectorielle / hybride intégrée dans l'index local. |
| **Agent/MCP** | Contrats d'agent, identifiants de routes UCM et instructions d'accès MCP via Unified MCP Server. |
| **Reports** | Raccourcis vers les dossiers de rapports et de journaux. |

L'en-tête affiche le nom du projet, un marqueur de lecture seule, un bouton **Settings** et un bouton **Refresh**. L'actualisation met à jour tous les résumés d'onglets, force la mise à jour des cartes du tableau de bord et rafraîchit le panneau de gouvernance.

Les cartes du tableau de bord sont rafraîchies à l'ouverture, par un **Refresh** explicite et après des actions du tableau de bord telles que **Rebuild**. Le panneau ne reconstruit pas les cartes sur un minuteur périodique, ce qui garde l'interface utilisateur stable lors de l'édition ou de l'inspection.

## Paramètres du projet

Configurez IIS sous :

```text
Edit -> Project Settings -> Plugins -> Internal Index Service
```

| Paramètre | Valeur par défaut | Signification |
| --- | --- | --- |
| **Vector Backend** | `jsonl_bruteforce` | Implémentation de l'index vectoriel local (`jsonl_bruteforce` ou `hnsw`), avec routage automatique force brute/HNSW selon le nombre d'enregistrements. |
| **Index Root (optional)** | *(vide)* | Surcharge pour la racine de l'index sur disque ; vide utilise `Saved/InternalIndexService`. |
| **Brute Force Max Records** | `10000` | Seuil de recherche exacte avant l'utilisation de HNSW. |
| **Embedding Executor Id** | *(vide)* | Exécuteur d'embedding préféré. Vide utilise la détection IIS normale ; la bridge optionnelle IIS LLM Store définit cela sur `llmstore` une fois chargée. |
| **Vector Storage Format** | `Int8 Per-Vector Scale` | Politique de stockage HNSW. Conservez la valeur par défaut int8 compacte par vecteur pour une utilisation normale ; utilisez `Float32` pour les exécutions haute fidélité/débogage ; utilisez `Experimental Global Scale` uniquement derrière la porte expérimentale. |
| **Allow Experimental Vector Formats** | `false` | Active les dispositions vectorielles de mesure uniquement qui peuvent réduire le rappel (recall). |
| **Rebuild On Vector Format Mismatch** | `true` | Reconstruit les partitions HNSW persistées incompatibles au lieu de les charger avec une mauvaise disposition d'octets. |
| **Quantization Recall Gate** | `0.7` | Seuil de rappel minimal utilisé par les tests d'automatisation de quantification ; à augmenter après validation représentative du projet. |
| **HNSW M / efConstruction / efSearch** | `16` / `200` / `64` | Réglage fin du rappel HNSW, du temps de construction, de la mémoire et de la latence de requête. |

L'accès MCP est fourni par Unified MCP Server via les routes Capability Mesh du projet. IIS ne fournit plus et ne requiert plus de bridge UMCP dédiée.

## Intégrations

L'exécution de l'embedding est déléguée via `FIISEmbeddingDiscovery` (`IModularFeatures` / `IIISEmbeddingRouteExecutor`). Les plugins bridges s'enregistrent dans `StartupModule` et se désenregistrent dans `ShutdownModule`. `FIISEmbeddingRouteExecutorRegistry` est un adaptateur obsolète pour les appelants hérités.

La carte **Integrations** du tableau de bord liste les ID d'exécuteurs de `FIISEmbeddingDiscovery::GetExecutorIds()` et indique si chaque intégration est active.

L'historique des jobs de l'éditeur est exposé via des routes UCM (`iis.editor.jobs.list.v1`, `iis.editor.jobs.status.v1`) au lieu d'un fournisseur UMCP au temps de compilation. La route de liste fusionne l'historique du panneau avec les lignes récentes de jobs d'embedding SQLite.

## Documentation associée

| Document | Public cible |
| --- | --- |
| [QUICKSTART.md](QUICKSTART.md) | Première configuration, importation, construction de l'index et recherche. |
| [UserManual.md](UserManual.md) | Flux de travail complet de l'éditeur et comportement opérationnel. |
| [SettingsReference.md](SettingsReference.md) | Paramètres, fichiers générés et chemins de stockage. |
| [TechnicalOverview.md](TechnicalOverview.md) | Architecture et flux de données au niveau des mainteneurs. |
| [CodeDocumentation.md](CodeDocumentation.md) | Carte du code C++, classes principales et chemins d'exécution. |
| [INTEGRATION.md](INTEGRATION.md) | Comment UII, LLM Store et UMCP s'intègrent dans IIS. |
| [FAQ.md](FAQ.md) | Questions courantes des acheteurs et réviseurs. |
| [TROUBLESHOOTING.md](TROUBLESHOOTING.md) | Panne courantes et solutions. |
| [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md) | Déclaration du code source tiers pour la soumission Fab. |
| [../CHANGELOG.md](../CHANGELOG.md) | Notes de version. |

## Paquetage

`Config/FilterPlugin.ini` inclut `/Documentation/...` afin que les acheteurs reçoivent ce dossier dans les builds Fab.
Il conserve également les métadonnées de précompilation générées par BuildPlugin dans le résultat paqueté. Lorsque IIS est installé dans une installation Unreal Engine, utilisez un paquet construit pour cette version de l'moteur et conservez ses binaires générés et ses métadonnées intacts.

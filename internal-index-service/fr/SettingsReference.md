<!-- doc-provenance: SAD architecture.md sections 2,8,10; facts product-facts.yml; reconciled 2026-07-16 -->
# Référence des paramètres

Les paramètres IIS sont stockés dans `UIISSettings`.

Ouvrir :

```text
Edit -> Project Settings -> Plugins -> Internal Index Service
```

## Champs

| Paramètre | Valeur par défaut | Signification |
| --- | --- | --- |
| Vector Backend | `jsonl_bruteforce` | Sélectionne le back-end de recherche vectorielle locale. Les valeurs prises en charge incluent `jsonl_bruteforce` et `hnsw`. Avec `jsonl_bruteforce`, IIS bascule automatiquement sur HNSW au-dessus de la limite d'enregistrements en force brute ci-dessous. |
| Index Root | vide | Surcharge optionnelle pour les données IIS générées. Vide utilise `Saved/InternalIndexService`. |
| Brute Force Max Records | `10000` | À cette quantité d'enregistrements ou en dessous, la recherche exacte en force brute est utilisée ; au-dessus, HNSW. |
| Embedding Executor Id | vide | ID de l'exécuteur d'embedding préféré pour IIS. Vide utilise la détection normale ; la bridge optionnelle IIS LLM Store définit cela sur `llmstore` lorsqu'elle est chargée. |
| Vector Storage Format | `Int8 Per-Vector Scale` | Politique de stockage vectoriel HNSW. `Int8 Per-Vector Scale` est la valeur par défaut compacte prise en charge ; `Float32` est utile pour les exécutions haute fidélité/débogage ; `Experimental Global Scale` est sous porte et destinée à la mesure uniquement. |
| Allow Experimental Vector Formats | `false` | Active les formats de stockage HNSW expérimentaux. Lorsqu'ils sont désactivés, les sélections expérimentales basculent sur `Int8 Per-Vector Scale`. |
| Rebuild On Vector Format Mismatch | `true` | Supprime les partitions HNSW persistées incompatibles afin qu'elles puissent être reconstruites à partir des vecteurs sources au lieu d'être lues avec une mauvaise disposition d'octets. |
| Quantization Recall Gate | `0.7` | Cible de rappel minimale utilisée par les portes d'automatisation de stockage vectoriel quantifié. Augmenter uniquement après validation sur des embeddings de projet représentatifs. |
| HNSW M | `16` | Connectivité du graphe HNSW. Une valeur plus élevée améliore le rappel au détriment de la mémoire et du temps de construction. S'applique aux index nouvellement construits. |
| HNSW efConstruction | `200` | Taille de la liste des candidats au moment de la construction. Une valeur plus élevée améliore la qualité du graphe et le rappel au détriment du temps de construction. S'applique aux index nouvellement construits. |
| HNSW efSearch | `64` | Taille de la liste des candidats au moment de la requête. Une valeur plus élevée améliore le rappel au détriment de la latence de requête. Appliqué lors du chargement et de la reconstruction. |
| Enable Runtime Control Mutations | `true` | Porte principale pour la surface de contrôle en runtime. Lorsque désactivé, les verbes de console et d'API tune/act/persist sont rejetés ; les lectures fonctionnent toujours. |
| Retain Recent Diagnostics | `false` | Lorsqu'activé, IIS conserve une mémoire tampon circulaire en RAM des récents diagnostics par requête pour l'inspection via `diagnostics.recent` / console. |
| Recent Diagnostics Max Count | `64` | Nombre maximal de diagnostics conservés lorsque Retain Recent Diagnostics est activé. |
| Estimate Recall By Default | `false` | Lorsqu'activé, les recherches estiment recall@K à moins que la requête ne l'exclue explicitement. Ajoute un balayage de référence exact (SYN-1). |

> Les index HNSW sont stockés en utilisant par défaut une quantification scalaire int8 (mise à l'échelle par vecteur), ce qui maintient un rappel élevé tout en réduisant la mémoire de l'index et la taille sur disque. Float32 est disponible en tant que politique haute fidélité/débogage. Le mode int8 à l'échelle globale expérimentale est délibérément sous porte car il peut gaspiller la plupart des niveaux int8 sur des embeddings multidimensionnels normalisés. Les index construits avec une autre politique de stockage sont détectés et reconstruits automatiquement par défaut.

## Chemins générés

Racine par défaut :

```text
Saved/InternalIndexService
```

Zones générées importantes :

| Chemin | Objectif |
| --- | --- |
| `chunks.jsonl` | Stockage des chunks importés. |
| `imports/` | Manifestes d'importation et rapports. |
| `reports/` | Rapports de catalogue, d'embedding et de diagnostic. |
| `agent_contracts/` | Contrats d'outils d'agent et manifeste MCP consommés par les bridges. |
| `vectors/` ou fichiers spécifiques au back-end | Données d'embedding/vecteurs persistées. |

Les noms exacts des fichiers peuvent varier selon le flux de travail et le back-end.

## Paramètres MCP

Les paramètres du serveur MCP ne se trouvent pas dans IIS. Configurez-les sous :

```text
Edit -> Editor Settings -> Plugins -> Unified MCP Server
```

L'accès agent IIS est publié via les routes Capability Mesh du projet telles que `iis.agent.search.v1`.

## Gestion des secrets

IIS ne stocke pas les secrets des fournisseurs. Les identifiants du fournisseur d'embedding appartiennent à LLM Store ou à l'environnement du fournisseur.

## Valeurs par défaut recommandées

| Scénario | Vector Backend | Vector Storage Format | Formats expérimentaux | Index Root |
| --- | --- | --- | --- | --- |
| Première configuration | `jsonl_bruteforce` | `Int8 Per-Vector Scale` | désactivé | vide |
| Index local plus grand | `hnsw` | `Int8 Per-Vector Scale` | désactivé | vide ou chemin personnalisé local au projet |
| Débogage haute fidélité | `hnsw` | `Float32` | désactivé | chemin d'espace de travail temporaire |
| Expérimentation de rappel | `hnsw` | `Experimental Global Scale` | activé | chemin d'espace de travail temporaire |
| Validation CI partagée | `jsonl_bruteforce` | `Int8 Per-Vector Scale` | désactivé | chemin d'espace de travail temporaire |

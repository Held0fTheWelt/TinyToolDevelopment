<!-- doc-provenance: SAD architecture.md sections 1,3,6,7,8; facts product-facts.yml; reconciled 2026-07-16 -->
# Démarrage rapide

## 1. Activer le plugin

Activez `Internal Index Service` dans le navigateur de plugins. Redémarrez l'éditeur si Unreal le demande.

## 2. Ouvrir le panneau de contrôle

Utilisez :

```text
Tiny Tools -> AI -> Internal Index Service -> Open Internal Index Service
```

Le panneau de contrôle s'ouvre sur le tableau de bord.

## 3. Configurer les paramètres

Ouvrez :

```text
Edit -> Project Settings -> Plugins -> Internal Index Service
```

Première configuration recommandée :

| Paramètre | Valeur |
| --- | --- |
| Vector Backend | `jsonl_bruteforce` |
| Vector Storage Format | `Int8 Per-Vector Scale` |
| Allow Experimental Vector Formats | `false` |
| Index Root | vide |

Une valeur vide pour `Index Root` signifie que IIS utilise :

```text
Saved/InternalIndexService
```

La politique de stockage par défaut utilise un mises à l'échelle int8 par vecteur pour les partitions HNSW. C'est le mode compact normal. `Float32` est disponible pour les exécutions haute fidélité/débogage ; `Experimental Global Scale` doit rester désactivé sauf si vous mesurez délibérément les compromis de rappel.

## 4. Importer des chunks préparés

Utilisez l'onglet "Imports" du panneau de contrôle ou appelez l'API du service avec un fichier JSONL de chunks préparés. Les chunks préparés proviennent normalement d'un pipeline d'extraction compagnon tel que Unreal Integration Intelligence.

L'importation écrit des rapports sous le dossier Saved de IIS et met à jour le stockage de chunks.

## 5. Construire le catalogue

Utilisez l'action **Rebuild** du tableau de bord ou l'onglet "Catalog". IIS lit les chunks importés, normalise l'état du cycle de vie et écrit un rapport de construction du catalogue.

## 6. Rechercher

Utilisez l'onglet "Search" :

- la recherche lexicale fonctionne à partir du catalogue local
- la recherche vectorielle nécessite des embeddings
- la recherche hybride combine les deux lorsque des vecteurs existent

## 7. Construire les embeddings (Optionnel – ajoute la recherche vectorielle, nécessite LLM Store)

La recherche lexicale (étapes 1 à 6) fonctionne de manière autonome sans autre plugin. Les recherches vectorielles et hybrides sont une amélioration optionnelle : configurez d'abord le plugin **LLM Store**, puis IIS demande une route au registre d'exécuteurs d'embedding, crée des jobs et écrit des rapports d'embedding. Exécutez les jobs depuis l'onglet "Embeddings". Sans LLM Store, IIS importe, construit et recherche toujours en mode lexical.

## 8. Exposer les outils d'agent (Optionnel – nécessite Unified MCP Server + Capability Mesh)

Cette étape est optionnelle et n'est nécessaire que si vous souhaitez que des agents IA appellent IIS. Installez et activez :

- Unified MCP Server
- Unreal Capability Mesh

Assurez-vous que le profil Capability Mesh du projet inclut les routes d'agent IIS (par exemple `iis.agent.search.v1`). Démarrez ensuite Unified MCP Server. Chaque capacité d'agent IIS est exposée comme sa propre route UCM autonome, aplatie en un outil MCP `mesh_route_*`, tel que :

```text
mesh_route_iis_agent_search_v1_<hash>
mesh_route_iis_agent_get_context_pack_v1_<hash>
mesh_route_iis_agent_get_chunk_v1_<hash>
mesh_route_iis_agent_get_source_references_v1_<hash>
mesh_route_iis_agent_find_usages_v1_<hash>
mesh_route_iis_agent_explain_blueprint_v1_<hash>
```

Alternativement, appelez `mesh_execute_route` avec `route_id` défini sur l'identifiant de la route (par exemple `iis.agent.search.v1`).

## 9. Réglage en runtime (Optionnel – aucun plugin supplémentaire)

La surface de contrôle runtime fournie est **autarconique** (autark) : aucun UCM ou UMCP requis.

Ouvrez la console du journal de sortie de l'éditeur et exécutez :

```text
iis.control.state
```

Exemple d'extrait de réponse (`efSearch` par défaut est 64) :

```json
{"ok":true,"errorCode":"","errorMessage":"","efSearch":64,...}
```

Augmentez le `efSearch` lors de la requête en direct :

```text
iis.control.tune {"efSearch":128}
```

Confirmez le changement :

```text
iis.control.state
```

Exemple après réglage :

```json
{"ok":true,"errorCode":"","errorMessage":"","efSearch":128,...}
```

Les surcharges sont **temporaires** (transient) jusqu'à ce que vous exécutiez `iis.control.persist`. Utilisez `iis.control.reset` pour recharger la configuration. Consultez `UserManual.md` pour la liste complète des commandes de console et de l'API Blueprint.

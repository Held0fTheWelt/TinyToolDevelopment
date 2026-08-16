<!-- doc-provenance: SAD architecture.md sections 1,2,7,8; facts product-facts.yml; reconciled 2026-07-16 -->
# FAQ (Foire aux questions)

## IIS modifie-t-il mon projet ?

Non. IIS est en lecture seule (retrieval-only). Il écrit des fichiers d'index et de rapport générés, mais n'applique aucune mutation au code source, aux Blueprints, aux assets ou à la configuration en tant qu'action d'agent.

## IIS inclut-il un serveur MCP ?

Non, pas dans les versions actuelles. Le transport MCP est fourni par Unified MCP Server. Les opérations de l'agent IIS sont exposées via les routes Capability Mesh du projet, et non via un serveur MCP ou plugin bridge propre à IIS.

## Où vont les données ?

Par défaut :

```text
Saved/InternalIndexService
```

Vous pouvez surcharger la racine dans Project Settings.

## IIS envoie-t-il des données de projet dans le cloud ?

Uniquement si une route d'exécuteur d'embedding dans LLM Store utilise un fournisseur cloud. La recherche, le catalogue, l'importation et les fichiers de rapport sont locaux.

## Pourquoi n'y a-t-il aucun résultat vectoriel ?

La recherche vectorielle nécessite des embeddings. Construisez et exécutez des jobs d'embedding après avoir configuré une route d'embedding via LLM Store.

## À quoi sert hnswlib ?

hnswlib alimente le back-end vectoriel optionnel des plus proches voisins approximatifs `hnsw`. Il est fourni sous forme de code source sous `Source/ThirdParty/hnswlib`.

## Pourquoi ma liste d'outils MCP manque-t-elle d'outils IIS ?

Vérifiez que ces plugins sont activés :

- Internal Index Service
- Unified MCP Server
- Unreal Capability Mesh

Assurez-vous que le profil Capability Mesh du projet liste les routes d'agent IIS (`iis.agent.*.v1`), puis écrivez/rafraîchissez les contrats d'agent IIS et appelez `mesh_reload_setup` ou rafraîchissez le client MCP.

## Puis-je appeler IIS depuis C++ ?

Oui. Utilisez `FInternalIndexServiceModule::Get().GetService()` et l'interface `IInternalIndexService`.

## Puis-je appeler IIS depuis Blueprint ?

IIS expose principalement l'interface utilisateur de l'éditeur et des services C++. Les parcours d'agent et d'intégration sont basés sur C++/JSON.

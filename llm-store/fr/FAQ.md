<!-- doc-provenance: AKDB:plugins/LLMStore/architecture.md; docs/architecture/plugins/LLMStore/product-facts.yml; reconciled 2026-06-20 -->
# FAQ (Foire aux questions)

## Y a-t-il une configuration initiale guidée ?

Oui. L'onglet **Setup** contient une carte **Quick-Start**. Elle peut créer en un clic une pile complète factice (mock), Ollama ou cloud OpenAI/Anthropic (fournisseur, modèle et route `default`), exécuter un test de connexion et rafraîchir la disponibilité. Elle ne réécrit pas les fournisseurs que vous avez déjà créés ni une route `default` que vous avez configurée vous-même.

## LLM Store est-il un chatbot ?

Non. LLM Store est une infrastructure pour les fournisseurs, modèles, routes, politiques, secrets, le suivi des coûts et les agents. Un chatbot ou un assistant d'assets peut utiliser LLM Store, mais il s'agit d'un outil distinct.

## Pourquoi devrais-je utiliser des routes au lieu de noms de modèles ?

Les routes gardent le code des fonctionnalités stable. Si un outil appelle `docs.summarize`, l'équipe peut ultérieurement passer d'Ollama à llama.cpp ou OpenAI sans modifier le code de l'outil.

## Puis-je tout exécuter en local ?

Oui. Utilisez des fournisseurs tels que `ollama`, `llamacpp`, `lmstudio`, `vllm`, `tgi` ou `mock`, définissez des politiques locales uniquement et bloquez le cloud via les règles de build.

## llama.cpp est-il pris en charge ?

Oui. Le type de fournisseur `llamacpp` est destiné aux serveurs llama.cpp locaux. L'URL de base typique est :

```text
http://localhost:8080
```

## Les clés API sont-elles stockées dans le fichier de projet ?

Non. `Config/LLMStore.json` stocke les fournisseurs, modèles, routes et politiques, mais pas les clés. Les clés résident dans le magasin de secrets ou les variables d'environnement.

## Quel back-end de secrets devrais-je utiliser ?

Pour une configuration par un développeur unique, `EncryptedFile` est simple. Pour les équipes, Windows Credential Manager, macOS Keychain, 1Password ou Azure Key Vault sont généralement préférables.

## Blueprint peut-il faire tout ce que C++ fait ?

Les points d'intégration importants destinés aux consommateurs disposent de versions Blueprint. Cela inclut les fournisseurs, les embeddings, les politiques, les tests, les fournisseurs de contexte, les agents et les fonctions de façade de sous-système.

## Puis-je connecter Codex, Claude ou Cursor ?

Oui, via des extensions d'agents. Le store peut unifier le statut, le guidage d'authentification et l'exécution des tâches. L'intégration concrète de l'outil reste un adaptateur et doit respecter les règles de sécurité.

## LLM Store exécute-t-il automatiquement des commandes shell ?

Uniquement lorsqu'un adaptateur d'agent implémente explicitement l'exécution et que les drapeaux de requête l'autorisent. `bAllowShellExecution`, `bAllowFileWrites` et `bRequireDiffPreview` communiquent les exigences de sécurité de l'appelant.

## Quelle est la précision du suivi des coûts ?

La précision dépend des données d'utilisation du fournisseur et des `CostRules`. Si un fournisseur ne renvoie pas le nombre de tokens, le store estime les tokens. La facturation du fournisseur reste la source de vérité pour les factures.

## Puis-je attribuer des coûts à des modèles locaux ?

Oui. Les modèles locaux peuvent coûter `0` ou utiliser des valeurs comptables internes telles que le coût matériel approximatif par 1000 tokens.

## Qu'est-ce qui n'a pas sa place directement dans LLM Store ?

Les outils de fonctionnalités concrets tels que l'explication d'assets, la documentation de Blueprints, l'examen de nommage ou le RAG de projet doivent utiliser LLM Store mais résident généralement dans des plugins ou extensions séparés. LLM Store reste autonome.

## Que se passe-t-il si un fournisseur est hors ligne ?

Le store met à jour la santé du fournisseur, peut tenter des solutions de secours (fallbacks) et enregistre les erreurs dans le journal d'audit. Les paramètres de coupe-circuit (circuit breaker) empêchent les tentatives répétées coûteuses ou bloquées.

## Puis-je utiliser LLM Store en CI ?

Oui. Utilisez le commandlet `LLMStoreCIPolicy` et les tests d'automatisation. Un exemple GitHub Actions est inclus dans `Documentation/CI`.

## Dois-je tester les fournisseurs cloud en direct ?

Pas toujours. Pour la sécurité de livraison, les tests factices, la validation de configuration et les tests de fumée manuels optionnels sur les fournisseurs sont souvent suffisants. Les tests cloud ne doivent s'exécuter qu'avec des secrets intentionnellement configurés.

## Quels fichiers devrais-je valider (commit) ?

Valider :

- `Config/LLMStore.json`
- préréglages optionnels
- documentation d'équipe pour les routes de production

Ne pas valider :

- clés API
- fichiers de secrets locaux
- fichiers de livre de comptes si ils contiennent des données opérationnelles sensibles

## Puis-je exporter et importer des configurations complètes ?

Oui. L'onglet Governance peut exporter la configuration actuelle dans n'importe quel fichier JSON, valider un fichier JSON sans l'appliquer et importer une configuration JSON uniquement si la validation réussit. Les fichiers de configuration exportés ne contiennent pas de clés API.

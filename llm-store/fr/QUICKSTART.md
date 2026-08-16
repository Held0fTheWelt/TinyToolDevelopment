<!-- doc-provenance: AKDB:plugins/LLMStore/architecture.md; docs/architecture/plugins/LLMStore/product-facts.yml; reconciled 2026-06-20 -->
# Démarrage rapide

Ce guide vous accompagne lors de la première configuration d'une route fonctionnelle LLM Store.

## 1. Ouvrir l'onglet de l'éditeur

Ouvrir :

```text
Tiny Tools -> LLM Store
```

La zone supérieure résume les fournisseurs, modèles, routes, routes d'embedding chargés, l'état de disponibilité et les informations de coût estimé.

## 2. Utiliser la carte Quick-Start (recommandé pour le premier lancement)

Dans l'onglet **Setup**, la carte **Quick Start** apparaît au-dessus des sections de fournisseurs et modèles. Choisissez une option :

| Bouton | Ce que cela crée | Clé API |
| --- | --- | --- |
| **Just try it (Mock)** | Fournisseur factice hors ligne, modèle et route `default` | Aucune |
| **Local (Ollama)** | Ollama sur `http://localhost:11434`, modèle par défaut `llama3`, route `default` | Aucune (Ollama doit être en cours d'exécution) |
| **Create OpenAI** | Fournisseur OpenAI, modèle `gpt-4o-mini`, route `default` | Collez la clé dans le champ (stockée dans le magasin de secrets uniquement) |
| **Create Anthropic** | Fournisseur Anthropic, modèle `claude-3-5-haiku-latest`, route `default` | Collez la clé dans le champ (stockée dans le magasin de secrets uniquement) |

Après avoir cliqué sur un bouton, LLM Store :

1. Applique la pile de démarrage de manière idempotente (ID `quickstart_*` stables ; ne réécrit jamais vos fournisseurs existants ni une route `default` existante que vous auriez déjà configurée).
2. Stocke une clé API cloud via `SetProviderKey` si vous en avez fourni une (jamais écrite dans `Config/LLMStore.json`).
3. Exécute **Test Connection** et rafraîchit la bannière de disponibilité.

Lorsque la disponibilité est déjà verte, la carte apparaît réduite avec un court titre « ready — expand to run Quick-Start again ».

Pour des URL personnalisées, des modèles supplémentaires ou des routes spécifiques à des tâches, poursuivez avec les étapes manuelles ci-dessous.

## 3. Créer un fournisseur local (manuel)

Un fournisseur local est le test le plus simple car aucune clé API n'est requise.

### Option A : Ollama

1. Démarrez Ollama localement.
2. Téléchargez un modèle :

```text
ollama pull llama3.1
```

3. Dans `Setup`, créez un fournisseur :

```text
Id: ollama-local
DisplayName: Ollama Local
Type: ollama
BaseUrl: http://127.0.0.1:11434
Enabled: true
```

4. Créez un modèle :

```text
Id: local-chat
Name: llama3.1
DisplayName: Local Chat
ProviderId: ollama-local
Role: fast
Enabled: true
```

### Option B : llama.cpp

Démarrez un serveur llama.cpp local :

```text
llama-server -m C:\Models\model.gguf --host 127.0.0.1 --port 8080
```

Créez ensuite :

```text
Provider:
  Id: llamacpp-local
  Type: llamacpp
  BaseUrl: http://127.0.0.1:8080

Model:
  Id: local-llamacpp
  Name: local-model
  ProviderId: llamacpp-local
```

## 4. Créer un fournisseur cloud (manuel)

Les fournisseurs cloud nécessitent généralement une clé API. La clé est stockée dans le back-end de secrets, pas dans `Config/LLMStore.json`.

Exemple :

```text
Provider:
  Id: openai-main
  Type: openai
  BaseUrl: https://api.openai.com/v1

Model:
  Id: openai-fast
  Name: gpt-4o-mini
  ProviderId: openai-main
```

Définissez ensuite la clé dans la section du fournisseur ou via une variable d'environnement :

```text
LLMSTORE_OPENAI_MAIN_KEY
```

## 5. Créer une route

Créez une route dans l'onglet `Routes` :

```text
TaskKind: docs.summarize
PreferredModelId: local-chat
FallbackModelIds:
  - openai-fast
MockModelId: mock-docs
bUseMock: false
```

Si vous avez commencé avec llama.cpp, utilisez `local-llamacpp` comme modèle préféré.

## 6. Ajouter une politique (Policy)

Pour une route locale d'abord sécurisée :

```text
bAllowCloud: false
bLocalOnly: true
MaxContextTokens: 0
MaxEstimatedCost: 0
AllowedProviderTypes:
  - ollama
  - llamacpp
  - mock
```

Pour une route de développement hybride, autorisez le cloud et ajoutez une limite de coût :

```text
bAllowCloud: true
bLocalOnly: false
MaxEstimatedCost: 0.05
```

## 7. Tester le fournisseur, le modèle et la route

Utilisez les boutons de test dans l'éditeur.

Si la route ne se résout pas, vérifiez :

- le fournisseur est-il activé ?
- le modèle est-il activé ?
- le modèle fait-il référence au bon fournisseur ?
- la route utilise-t-elle le bon ID de modèle ?
- la clé API est-elle définie pour le fournisseur cloud ?
- le serveur local est-il en cours d'exécution ?
- la politique autorise-t-elle le type de fournisseur sélectionné ?

## 8. Ajouter des règles de coût

L'onglet `Costs` devient utile une fois que les règles de prix existent.

Exemple :

```text
ProviderType: openai
ModelId: openai-fast
InputCostPer1KTokens: 0.00015
OutputCostPer1KTokens: 0.00060
Currency: USD
```

Les fournisseurs locaux peuvent rester à `0` ou utiliser un modèle de coût interne.

## 9. Exécuter une requête

Après une requête, l'onglet `Costs` affiche :

- le nombre d'événements
- le nombre de succès
- les succès de cache
- les tokens d'invite
- les tokens de réponse
- le coût estimé
- la répartition par fournisseur/modèle/tâche
- les événements récents

Utilisez `Export CSV` pour écrire des rapports dans :

```text
Saved/LLMStore/CostReports
```

## 10. Vérifier le statut

Ouvrez l'onglet `Status`. La section la plus importante est `Attention`, car elle affiche les clés manquantes, les routes cassées, les fournisseurs désactivés et les problèmes de politique.

## 11. Configuration optionnelle d'agent

Pour connecter Codex, Claude, Cursor ou un agent personnalisé :

1. Ouvrez l'onglet `Agents`.
2. Sélectionnez un agent.
3. Cliquez sur `Authenticate...`.
4. Utilisez `Copy Command` et exécutez la commande manuellement dans votre terminal.
5. Rafraîchissez le statut.

Exemples :

```text
codex login
claude auth login
```

LLM Store ne stocke pas les identifiants de l'agent.

<!-- doc-provenance: AKDB:plugins/LLMStore/architecture.md; docs/architecture/plugins/LLMStore/product-facts.yml; reconciled 2026-06-20 -->
# Manuel de l'utilisateur

Ce manuel décrit LLM Store du point de vue d'un acheteur, d'un artiste technique, d'un développeur Blueprint ou d'un programmeur d'outils. Il explique les flux de travail de l'éditeur et pointe vers des références techniques plus approfondies si nécessaire.

## Objectif du plugin

LLM Store est une couche de contrôle IA centralisée pour les projets Unreal Engine. Les autres plugins et outils n'ont pas besoin de savoir si une invite est envoyée à Ollama, llama.cpp, OpenAI, Claude, Gemini, Azure OpenAI, Mistral, OpenRouter ou un mock. Ils appellent une route de tâche stable telle que :

```text
docs.summarize
asset.explain
naming.review
rag.embed
agent.patch
```

La route décide du fournisseur, du modèle, du secours, de la politique, de la règle de coût et du back-end de secret.

## Ouvrir l'éditeur

Ouvrir :

```text
Tiny Tools -> LLM Store
```

L'onglet est conçu pour un usage quotidien. Il n'expose pas seulement des paramètres bruts ; il guide la configuration, les routes, le statut, l'aide, les agents, les coûts et la gouvernance.

## Première configuration

### Carte Quick-Start (voie la plus rapide)

1. Ouvrez `Tiny Tools -> LLM Store`.
2. Allez sur `Setup`. La section **Quick Start — get running in one click** se trouve en haut.
3. Choisissez une option :
   - **Just try it (Mock)** — entièrement hors ligne ; aucune clé API ; idéal pour la CI et le premier contact.
   - **Local (Ollama)** — crée `quickstart_ollama` sur `localhost:11434` ; démarrez Ollama avant de tester.
   - **Create OpenAI** ou **Create Anthropic** — collez une clé API dans le champ mot de passe, puis cliquez sur le bouton du fournisseur. La clé est stockée uniquement dans le back-end de secrets.
4. Lisez la ligne de statut sous les boutons et la bannière de disponibilité au-dessus des onglets.
5. Si la disponibilité est verte, ne développez à nouveau la zone Quick-Start que si vous avez besoin d'une autre pile de démarrage (les entrées `quickstart_*` existantes ne sont pas dupliquées ; votre propre route `default` n'est jamais réécrite).

Les piles de démarrage utilisent des ID stables (`quickstart_mock`, `quickstart_ollama`, `quickstart_openai`, `quickstart_anthropic`) et relient toujours une route de tâche `default` sauf si vous en avez déjà défini une.

### Configuration manuelle (contrôle total)

1. Ouvrez `Tiny Tools -> LLM Store`.
2. Allez dans `Setup` (sous la carte Quick-Start).
3. Créez un fournisseur, par exemple `ollama`, `llamacpp`, `openai` ou `anthropic`.
4. Confirmez que l'URL de base par défaut est appropriée.
5. Créez un modèle pour le fournisseur.
6. Allez dans `Routes`.
7. Créez une route, par exemple `docs.summarize`.
8. Choisissez le modèle préféré.
9. Cliquez sur `Test Route`.
10. Vérifiez `Status` pour les avertissements ou les bloqueurs.

## Configuration du fournisseur

Un fournisseur décrit le service technique, pas le modèle lui-même.

| Champ | Signification |
| --- | --- |
| `Id` | ID stable local au projet, par exemple `local-ollama`. |
| `DisplayName` | Nom lisible dans l'UI et les rapports. |
| `Type` | Type de fournisseur comme `ollama`, `llamacpp` ou `openai`. |
| `BaseUrl` | Point de terminaison HTTP. Les fournisseurs connus reçoivent des valeurs par défaut utiles. |
| `Enabled` | Désactive le fournisseur sans supprimer ses paramètres. |
| `RetryCount` | Tentatives de réessai pour les erreurs temporaires. |
| `TimeoutSeconds` | Délai d'expiration spécifique au fournisseur. |
| `CircuitBreaker...` | Protection contre les échecs répétés ou les serveurs bloqués. |

Les fournisseurs locaux n'ont généralement pas besoin de clé. Les fournisseurs cloud ont généralement besoin d'une clé dans le magasin de secrets.

## Fournisseurs connus

| Type de fournisseur | URL de base par défaut | Utilisation typique |
| --- | --- | --- |
| `ollama` | `http://localhost:11434` | Modèles locaux via Ollama. |
| `llamacpp` | `http://localhost:8080` | Inférence de serveur llama.cpp local. |
| `lmstudio` | `http://localhost:1234/v1` | Modèles LM Studio locaux. |
| `vllm` | `http://localhost:8000/v1` | Inférence haute performance locale ou sur serveur. |
| `tgi` | `http://localhost:8080` | Hugging Face Text Generation Inference. |
| `openai` | `https://api.openai.com/v1` | API OpenAI. |
| `anthropic` | `https://api.anthropic.com` | API Claude. |
| `gemini` | `https://generativelanguage.googleapis.com/v1beta` | API Google Gemini. |
| `azure-openai` | spécifique au projet | Point de terminaison et logique de déploiement Azure. |
| `mistral` | `https://api.mistral.ai/v1` | API Mistral. |
| `openrouter` | `https://openrouter.ai/api/v1` | Routeur pour de nombreux modèles cloud. |
| `mock` | vide | Tests, développement d'UI, CI et travail hors ligne. |

## Modèles

Un modèle appartient à un seul fournisseur.

| Champ | Signification |
| --- | --- |
| `Id` | ID de modèle stable local au projet. |
| `Name` | Nom du modèle côté fournisseur, par exemple `llama3.1:8b` ou `gpt-4o-mini`. |
| `ProviderId` | Fournisseur qui sert le modèle. |
| `Role` | Rôle optionnel comme `fast`, `reasoning`, `embedding` ou `local`. |
| `Structured` | Marque les modèles censés bien gérer la sortie JSON/schéma. |
| `TimeoutSeconds` | Délai d'expiration spécifique au modèle. |
| `Enabled` | Désactive le modèle sans supprimer les routes. |

## Routes

Les routes sont le concept le plus important du store. Une fonctionnalité demande une tâche, pas un modèle.

Exemple :

```text
TaskKind: docs.summarize
PreferredModelId: local-fast
FallbackModelIds:
  - cloud-reasoning
  - mock-docs
Policy: local-only for shipping
```

Avantages :

- les fonctionnalités restent stables lorsque les modèles changent
- les politiques peuvent être appliquées par tâche
- les chaînes de secours peuvent mélanger des modèles locaux, cloud et factices
- les coûts peuvent être analysés par tâche
- la CI peut valider les politiques de route sans connaître chaque outil

## Tester une route

Utilisez `Test Route` dans l'onglet `Routes`. Le test vérifie :

- la route existe-t-elle ?
- la route est-elle activée ?
- le modèle existe-t-il ?
- le fournisseur existe-t-il ?
- le fournisseur est-il activé ?
- la clé requise existe-t-elle ?
- le fournisseur répond-il à une petite requête ?

Les erreurs apparaissent dans la zone de statut et le tableau de bord de santé du fournisseur.

## Politiques (Policies)

Les politiques décident si une route peut être utilisée.

Règles typiques :

- interdire le cloud pour les données sensibles
- autoriser uniquement les modèles locaux pour la livraison
- définir un budget de contexte maximal
- définir un coût maximal par requête
- autoriser ou refuser des types de fournisseurs spécifiques

Les politiques doivent être placées dans LLM Store. Un autre plugin peut fournir du contexte ou appeler une route, mais la décision de gouvernance centralisée reste dans le store.

## Agents

L'onglet `Agents` affiche des adaptateurs optionnels tels que Codex, Claude, Cursor ou des outils de studio personnalisés.

| Statut | Signification |
| --- | --- |
| `NotInstalled` | L'outil n'a pas été trouvé. |
| `Installed` | L'outil existe, l'authentification est floue ou manquante. |
| `AuthRequired` | L'authentification doit être effectuée. |
| `Available` | L'outil est utilisable. |
| `Disabled` | L'adaptateur est désactivé. |
| `Error` | L'adaptateur signale une erreur. |

Le bouton `Authenticate...` ouvre une boîte de dialogue avec la commande, les instructions, le lien d'aide et une action de copie pour une utilisation manuelle dans le terminal. LLM Store ne stocke pas les identifiants d'outils externes.

## Analyse des coûts

L'onglet `Costs` collecte et analyse le livre de comptes des coûts.

Il affiche :

- le total des événements
- les événements réussis
- les succès de cache
- les tokens d'invite
- les tokens de réponse
- le coût estimé
- la répartition par fournisseur, modèle et route
- l'exportation CSV

Les coûts ne sont aussi précis que les données d'utilisation du fournisseur et les règles de coût configurées. Les modèles locaux peuvent être gratuits ou se voir attribuer un coût matériel interne.

## Magasin de secrets (Secret Store)

Les clés API n'ont pas leur place dans `Config/LLMStore.json`.

Back-ends pris en charge :

- fichier local chiffré
- Windows Credential Manager
- macOS Keychain
- 1Password CLI
- Azure Key Vault via Azure CLI

Les variables d'environnement sont prioritaires :

```text
LLMSTORE_<PROVIDER_ID>_KEY
```

Exemple :

```text
LLMSTORE_OPENAI_MAIN_KEY
```

## Onglet Status

L'onglet `Status` répond à : « Mon store est-il utilisable dès maintenant ? »

Il affiche :

- la disponibilité globale
- les bloqueurs
- les avertissements
- l'inventaire des fournisseurs
- les clés manquantes
- les fournisseurs ou modèles désactivés
- les problèmes de route

Utilisez cet onglet avant de partager des paramètres avec une équipe, d'exécuter la CI ou de paqueter une version.

## Exportation, validation et importation du JSON de configuration

L'onglet `Governance` inclut des actions sur le JSON de configuration pour partager ou déplacer des configurations LLM Store complètes.

Actions disponibles :

| Action | Objectif |
| --- | --- |
| `Export Setup JSON` | Choisissez n'importe quel dossier et nom de fichier, puis écrivez la configuration actuelle sous forme de JSON. Les secrets ne sont pas inclus. |
| `Validate JSON` | Choisissez un fichier JSON et validez le schéma, les ID de fournisseurs, les références de modèles, les routes et les avertissements sans l'appliquer. |
| `Import JSON` | Choisissez un fichier JSON, validez-le et appliquez-le uniquement si la validation réussit. |

L'importateur accepte à la fois le format de configuration enveloppé de LLM Store et un objet JSON brut `FLLMStoreConfig`. Cela le rend adapté aux préréglages, aux sauvegardes, aux fichiers de transmission d'équipe et aux instantanés de configuration vérifiés manuellement.

## Onglet Help

L'onglet `Help` explique directement dans l'éditeur :

- ce qu'est un fournisseur
- ce qu'est un modèle
- pourquoi les routes sont utilisées à la place des noms de modèles directs
- comment les fournisseurs locaux et cloud fonctionnent ensemble
- comment s'appliquent les politiques et les règles de build
- ce que mesure le suivi des coûts
- comment les agents sont connectés

La section d'aide est incluse dans le plugin afin que les acheteurs n'aient pas à basculer entre un site web, un README et l'interface utilisateur de l'éditeur pour les concepts de base.

## Utilisation de Blueprint

Les points d'intégration importants destinés aux consommateurs sont disponibles dans Blueprints.

| Classe | Objectif |
| --- | --- |
| `ULLMBlueprintProviderAddOn` | Connecter un fournisseur depuis Blueprint. |
| `ULLMBlueprintEmbeddingProviderAddOn` | Connecter un fournisseur d'embedding depuis Blueprint. |
| `ULLMBlueprintContractAddOn` | Valider les contrats de modèles. |
| `ULLMBlueprintPolicyAddOn` | Autoriser ou rejeter des routes au moment de l'exécution. |
| `ULLMBlueprintTestAddOn` | Ajouter des tests de configuration ou de statut. |
| `ULLMBlueprintContextProviderAddOn` | Fournir le contexte du projet sous forme de packs de contexte. |
| `ULLMBlueprintAgentAddOn` | Connecter des CLI externes ou des assistants d'éditeur. |

## Utilisation de C++

Les utilisateurs C++ obtiennent le store à partir du sous-système moteur :

```cpp
ULLMStoreSubsystem* Store = GEngine->GetEngineSubsystem<ULLMStoreSubsystem>();
```

Ensuite, les routes peuvent être résolues, les requêtes exécutées, les packs de contexte construits, les agents appelés et les rapports de coûts lus.

Consultez [INTEGRATION.md](INTEGRATION.md) et [CodeDocumentation.md](CodeDocumentation.md).

## Flux de travail recommandés

### Développement local

1. Créez un fournisseur `ollama` ou `llamacpp`.
2. Ajoutez un modèle local.
3. Orientez les routes vers le modèle local.
4. Désactivez le cloud via la politique.
5. Conservez un chemin `mock` pour les tests.

### Développement hybride

1. Utilisez des modèles locaux pour les tâches rapides.
2. Ajoutez un secours cloud pour les tâches plus complexes.
3. Définissez des limites de coût.
4. Examinez régulièrement le suivi des coûts.
5. Conservez les règles de build de livraison exclusivement locales/mock.

### Configuration d'équipe

1. Validez `Config/LLMStore.json`.
2. Ne validez pas les clés.
3. Documentez le back-end de secrets.
4. Exportez un préréglage.
5. Vérifiez l'onglet `Status`.
6. Activez les vérifications de politiques en CI.

## Limites

LLM Store n'est pas un outil fini d'explication d'assets, d'examen de Blueprints ou un produit RAG. Il fournit des routes, des fournisseurs, des politiques, le suivi des coûts, des secrets et des interfaces. Des outils de fonctionnalités concrets peuvent s'y connecter sans que LLM Store ne dépendra de ces outils.

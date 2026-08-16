<!-- doc-provenance: AKDB:plugins/LLMStore/architecture.md; docs/architecture/plugins/LLMStore/product-facts.yml; reconciled 2026-06-20 -->
# Référence des paramètres

Cette référence décrit les principales données de configuration utilisées par LLM Store.

Chemin de configuration du projet :

```text
Config/LLMStore.json
```

Les secrets ne sont pas stockés dans ce fichier.

## Fichiers JSON de configuration

L'UI Governance peut exporter, valider et importer des fichiers JSON de configuration depuis n'importe quel dossier sélectionné.

Le format enveloppé exporté contient :

| Champ | Signification |
| --- | --- |
| `Format` | `LLMStoreSetup`. |
| `FormatVersion` | Version du format JSON de configuration. |
| `SetupName` | Nom de configuration lisible par l'utilisateur. |
| `ExportedUtc` | Horodatage d'exportation UTC. |
| `Config` | Objet `FLLMStoreConfig` imbriqué. |

L'importateur accepte également un objet JSON `FLLMStoreConfig` brut pour des raisons de compatibilité.

## FLLMStoreConfig

| Champ | Type | Signification |
| --- | --- | --- |
| `Providers` | `TArray<FLLMProviderConfig>` | Fournisseurs connus. |
| `Models` | `TArray<FLLMModelConfig>` | Modèles servis par les fournisseurs. |
| `Routes` | `TArray<FLLMTaskRoute>` | Routes de tâches de chat/outil/reclassement. |
| `EmbeddingRoutes` | `TArray<FLLMStoreEmbeddingRoute>` | Routes spécifiques aux embeddings. |
| `RoutePolicies` | `TArray<FLLMRoutePolicy>` | Politiques globales ou spécifiques aux tâches. |
| `PromptTemplates` | `TArray<FLLMPromptTemplate>` | Modèles d'invites réutilisables. |
| `CostRules` | `TArray<FLLMCostRule>` | Règles de tarification pour le suivi des coûts. |
| `BuildRules` | `TArray<FLLMBuildConfigRule>` | Gouvernance par configuration de build. |
| `SecretBackend` | `FLLMSecretBackendConfig` | Back-end de secrets actif. |
| `Modes` | `FLLMRuntimeModes` | Libellés de profil d'exécution. |

## FLLMProviderConfig

| Champ | Signification |
| --- | --- |
| `Id` | Clé de fournisseur stable locale au projet. |
| `DisplayName` | Nom lisible dans l'UI/les rapports. |
| `Type` | Type de fournisseur tel que `openai`, `ollama` ou `llamacpp`. |
| `BaseUrl` | Serveur ou point de terminaison d'API. |
| `bEnabled` | Désactive le fournisseur sans le supprimer. |
| `Meta` | Métadonnées spécifiques au fournisseur, par exemple noms de déploiement Azure. |
| `RetryCount` | Tentatives de réessai pour les erreurs temporaires. |
| `TimeoutSeconds` | Délai d'expiration spécifique au fournisseur ; `0` utilise les valeurs par défaut. |
| `CircuitBreakerFailureThreshold` | Nombre d'échecs avant l'ouverture du coupe-circuit. |
| `CircuitBreakerCooldownSeconds` | Temps de refroidissement avant réessai après ouverture du coupe-circuit. |

## FLLMModelConfig

| Champ | Signification |
| --- | --- |
| `Id` | Clé de modèle stable locale au projet. |
| `Name` | Nom du modèle côté fournisseur. |
| `DisplayName` | Nom lisible dans l'UI. |
| `ProviderId` | Référence à `FLLMProviderConfig.Id`. |
| `Role` | Rôle optionnel tel que `fast`, `reasoning`, `local` ou `embedding`. |
| `bStructured` | Le modèle est censé bien gérer la sortie JSON structurée. |
| `TimeoutSeconds` | Délai d'expiration spécifique au modèle. |
| `bEnabled` | Désactive le modèle sans le supprimer. |

## FLLMTaskRoute

| Champ | Signification |
| --- | --- |
| `TaskKind` | Nom de tâche stable, par exemple `docs.summarize`. |
| `PreferredModelId` | Premier modèle essayé par cette route. |
| `FallbackModelId` | Modèle de secours unique hérité. |
| `FallbackModelIds` | Chaîne de secours ordonnée. |
| `MockModelId` | Modèle utilisé pour le mode factice (mock). |
| `bUseMock` | Force l'utilisation du mode factice. |
| `WorkflowScope` | Portée optionnelle telle que `Editor`, `CI` ou `Runtime`. |
| `PromptTemplateId` | Modèle par défaut pour cette route. |
| `Policy` | Politique spécifique à la route. |
| `bEnabled` | Désactive la route. |

## FLLMRoutePolicy

| Champ | Signification |
| --- | --- |
| `TaskKind` | Si vide, peut être utilisé par les outils comme global ; sinon spécifique à la tâche. |
| `bAllowCloud` | Les types de fournisseurs cloud peuvent être utilisés. |
| `bLocalOnly` | Seuls les fournisseurs locaux ou factices sont autorisés. |
| `MaxContextTokens` | Budget de contexte maximal ; `0` désactive la limite. |
| `MaxEstimatedCost` | Coût estimé maximal par requête ; `0` désactive la limite. |
| `AllowedProviderTypes` | Liste d'autorisation des types de fournisseurs. |
| `DeniedProviderTypes` | Liste d'interdiction des types de fournisseurs. |

## FLLMStoreEmbeddingRoute

| Champ | Signification |
| --- | --- |
| `RouteId` | ID de route d'embedding stable. |
| `TaskKind` | Tâche, par exemple `docs.embed`. |
| `ProviderId` | Fournisseur d'embedding. |
| `ModelId` | Modèle d'embedding. |
| `Dimensions` | Dimension vectorielle attendue ; `0` signifie la valeur par défaut du fournisseur. |
| `bEnabled` | La route est active. |
| `bLocalOnly` | Préférer ou exiger une exécution locale. |
| `bAllowFallback` | Les routes de secours peuvent être utilisées. |
| `FallbackRouteIds` | Routes de secours d'embedding. |
| `AllowedRuntimeModes` | Liste d'autorisation optionnelle des profils d'exécution. |

## FLLMCostRule

| Champ | Signification |
| --- | --- |
| `ProviderType` | Type de fournisseur couvert par la règle. |
| `ModelId` | ID de modèle optionnel ; si vide, s'applique largement. |
| `InputCostPer1KTokens` | Prix pour 1000 tokens d'invite. |
| `OutputCostPer1KTokens` | Prix pour 1000 tokens de réponse. |
| `Currency` | Libellé de la devise, par défaut `USD`. |

## FLLMSecretBackendConfig

| Champ | Signification |
| --- | --- |
| `Backend` | `EncryptedFile`, `WindowsCredentialManager`, `MacOSKeychain`, `OnePassword` ou `AzureKeyVault`. |
| `Vault` | Coffre, trousseau ou nom d'espace de noms spécifique au back-end. |
| `KeyPrefix` | Préfixe pour les noms de secrets générés. |
| `Meta` | Surcharges de fournisseurs spécifiques au back-end. |

## FLLMBuildConfigRule

| Champ | Signification |
| --- | --- |
| `BuildConfiguration` | Configuration Unreal telle que `Development`, `Test` ou `Shipping`. |
| `bAllowCloud` | Les fournisseurs cloud sont autorisés dans cette configuration. |
| `bRequireLocalOrMock` | Chaque route doit avoir un chemin local ou factice. |
| `AllowedProviderTypes` | Types de fournisseurs autorisés dans cette configuration. |

## FLLMRuntimeModes

| Champ | Signification |
| --- | --- |
| `GenerationMode` | Libellé libre tel que `Local`, `Hybrid` ou `Cloud`. |
| `RetrievalMode` | Libellé libre pour le comportement de recherche/RAG. |
| `ValidationMode` | Libellé libre pour le comportement de validation/examen. |
| `RuntimeProfile` | Profil global tel que `LocalOnly`, `OpenAICloud` ou `Hybrid`. |

## FLLMPromptTemplate

| Champ | Signification |
| --- | --- |
| `Id` | Clé du modèle. |
| `Description` | Description pour l'UI et les membres de l'équipe. |
| `Template` | Texte de l'invite avec des variables. |
| `Variables` | Noms des variables attendues. |

## Recommandations pour l'équipe

- Validez `Config/LLMStore.json`.
- Ne validez pas les clés d'API.
- Utilisez `SecretBackend` pour rendre visibles les attentes de l'équipe.
- Utilisez `BuildRules` pour détecter rapidement les erreurs de livraison.
- Ajoutez des `CostRules` avant une utilisation productive en cloud.
- Documentez chaque route de production avec son propriétaire, son objectif et sa classe de données.

## Paramètres de développement de l'éditeur

Les préférences spécifiques à l'éditeur se trouvent sous **Editor Settings -> Plugins -> LLM Store** et sont stockées séparément de `Config/LLMStore.json`.

| Champ | Valeur par défaut | Signification |
| --- | --- | --- |
| `MaxJobHistoryCount` | `50` | Nombre maximal d'enregistrements d'historique de panneau/job conservés pour l'historique de l'éditeur et les points de terminaison de jobs UCM. |
| `DefaultPanelPage` | `Setup` | Page du panneau affichée lorsque LLM Store s'ouvre. |
| `bAutoOpenPanelOnStartup` | `false` | Ouvre automatiquement le panneau lorsque le module de l'éditeur démarre. |
| `bRunValidationOnReload` | `false` | Exécute la vérification de disponibilité de validation après le rechargement de la configuration. |

<!-- doc-provenance: AKDB:plugins/LLMStore/architecture.md; docs/architecture/plugins/LLMStore/product-facts.yml; reconciled 2026-06-20 -->
# Dépannage

Ce guide répertorie les problèmes courants de configuration, d'exécution, d'interface utilisateur, de politique et de build de LLM Store.

## L'entrée de menu LLM Store est manquante

Vérifier :

- Le plugin est activé.
- L'éditeur a été redémarré après l'activation du plugin.
- Le module `LLMStoreEditor` est compilé.
- Vous exécutez Unreal Editor, et non un build runtime préparé (cooked).

Emplacement attendu :

```text
Tiny Tools -> LLM Store
```

## Le fournisseur n'est pas accessible

Vérifier :

- le fournisseur est activé
- l'URL de base est correcte
- le serveur local est en cours d'exécution
- le pare-feu ou le proxy ne bloque pas la requête
- le délai d'expiration est suffisamment long
- le type de fournisseur correspond au serveur

Valeurs par défaut locales courantes :

| Fournisseur | Par défaut |
| --- | --- |
| `ollama` | `http://127.0.0.1:11434` |
| `llamacpp` | `http://127.0.0.1:8080` |
| `lmstudio` | `http://127.0.0.1:1234/v1` |
| `vllm` | `http://127.0.0.1:8000/v1` |
| `tgi` | `http://127.0.0.1:8080/v1` |

Utiliser d'abord `Test Provider`, puis `Test Model`, puis `Test Route`.

## La route ne se résout pas

Vérifier :

- `TaskKind` de la route est orthographié exactement comme demandé
- la route est activée
- le modèle préféré existe
- le modèle est activé
- le modèle fait référence à un fournisseur existant
- le fournisseur est activé
- la clé cloud existe si nécessaire
- la politique de la route autorise le type de fournisseur
- le mode build/runtime ne rejette pas la route

Si `bUseMock` est activé, vérifier que `MockModelId` existe.

## Clé API manquante

Les clés ne sont pas stockées dans `Config/LLMStore.json`.

Utiliser l'une des options suivantes :

- le champ de clé du fournisseur dans l'éditeur
- la surcharge par variable d'environnement
- le back-end de secrets configuré

Format de variable d'environnement :

```text
LLMSTORE_<PROVIDER_ID>_KEY
```

Exemple :

```text
ProviderId: openai-main
Variable: LLMSTORE_OPENAI_MAIN_KEY
```

## La variable d'environnement est ignorée

Vérifier :

- le nom de la variable utilise l'ID de fournisseur normalisé
- le processus de l'éditeur a été redémarré après l'avoir définie
- la variable est visible par le processus qui lance Unreal
- il n'y a pas d'espaces cachés dans la valeur

Sous Windows, les modifications d'environnement apportées via les paramètres système nécessitent souvent le redémarrage du lanceur ou du terminal.

## Windows Credential Manager ne fonctionne pas

Vérifier :

- vous êtes sous Windows
- `Advapi32` est lié par la compilation du plugin
- le nom de la cible des identifiants correspond au nom de secret généré pour le fournisseur
- le compte utilisateur possède la permission
- l'ID du fournisseur n'a pas changé

En cas de doute, définir une variable d'environnement temporaire pour confirmer le reste de la configuration du fournisseur.

## macOS Keychain ne fonctionne pas

Vérifier :

- la commande `security` est disponible
- le trousseau est déverrouillé
- le processus a la permission de lire l'élément
- le nom de secret généré correspond à la valeur attendue

## Le back-end 1Password ne fonctionne pas

Vérifier :

- la CLI `op` est installée
- `op whoami` réussit dans le même contexte de terminal
- `Vault` est défini, ou `SecretBackend.Meta` contient une référence `op://...` complète
- la surcharge spécifique au fournisseur pointe vers le bon élément et le bon champ

## Le back-end Azure Key Vault ne fonctionne pas

Vérifier :

- la CLI `az` est installée
- `az account show` réussit
- `Vault` est le bon nom de Key Vault
- l'identité actuelle possède les permissions d'obtention/définition/suppression des secrets
- la surcharge spécifique au fournisseur correspond au nom du secret

## Le fournisseur cloud échoue mais le fournisseur local fonctionne

Vérifier :

- la clé API est présente
- l'URL de base correspond à la documentation du fournisseur
- le nom de modèle du fournisseur est correct
- le compte a accès au modèle
- la requête n'est pas bloquée par la politique de l'organisation
- la politique de coût de la route ne rejette pas la requête

Regarder l'état de santé du fournisseur et le dernier événement d'audit.

## llama.cpp ne répond pas

Vérifier :

- `llama-server` est en cours d'exécution
- l'hôte et le port correspondent à `BaseUrl`
- le serveur expose un point de terminaison compatible OpenAI
- le modèle est chargé
- le délai d'expiration de la requête est suffisamment long

Démarrage typique :

```text
llama-server -m C:\Models\model.gguf --host 127.0.0.1 --port 8080
```

Fournisseur :

```text
Type: llamacpp
BaseUrl: http://127.0.0.1:8080
```

## Ollama ne répond pas

Vérifier :

```text
ollama list
ollama serve
```

S'assurer que le modèle dans `FLLMModelConfig.Name` existe dans Ollama.

## Le JSON structuré est invalide

Vérifier :

- la route utilise un modèle adapté aux sorties structurées
- `bStructured` est défini sur le modèle si votre flux de travail le requiert
- `FLLMStructuredOutputSpec.bRequireJson` est vrai uniquement si nécessaire
- le schéma est un JSON valide
- l'invite ne demande pas de prose autour du JSON

Certains modèles locaux nécessitent des invites plus strictes pour produire un JSON valide.

## Les appels d'outils (Tool Calls) sont manquants

Vérifier :

- le fournisseur prend en charge l'appel d'outils
- `FLLMToolSpec.ParametersJsonSchema` est valide
- le modèle prend en charge les outils
- l'adaptateur du fournisseur associe les spécifications d'outils au format réseau du fournisseur

## Le flux (streaming) n'émet qu'un seul bloc

Certains fournisseurs ne prennent pas en charge le flux natif ou l'adaptateur actuel ne peut analyser que des réponses complètes. Cela est autorisé. L'API de flux émet toujours un bloc final afin que les appelants puissent utiliser un seul chemin de code.

## Les coûts sont nuls

Vérifier :

- des règles de coût existent
- le type de fournisseur correspond à la règle
- l'ID de modèle correspond à la règle ou l'ID de modèle de la règle est vide
- le fournisseur rapporte l'utilisation ou l'estimation des tokens est activée
- la requête n'a pas été servie entièrement par un modèle local à coût nul

## Le rapport de coût semble trop élevé

Vérifier :

- les unités de coût sont par 1000 tokens
- les valeurs d'entrée et de sortie ne sont pas inversées
- la devise est cohérente
- la règle spécifique au modèle n'est pas dupliquée par une règle plus large
- les données d'utilisation du fournisseur ne sont pas déjà dans une autre unité

## L'agent n'est pas installé

Vérifier :

- la CLI ou l'IDE est installé
- la commande de l'outil est dans le `PATH`
- Unreal a été lancé depuis un environnement capable de voir la commande de l'outil
- la vérification du statut de l'adaptateur connaît le nom de commande correct

Utiliser la boîte de dialogue `Authenticate...` pour les instructions de configuration.

## L'authentification de l'agent ne fonctionne pas

Essayer :

1. Clic sur `Copy Command`.
2. Exécuter la commande dans un terminal normal.
3. Compléter la connexion.
4. Redémarrer Unreal ou rafraîchir le statut de l'agent.

LLM Store ne stocke pas les identifiants. Il affiche et copie seulement la commande de connexion externe.

## L'agent me refuse les écritures de fichiers

Vérifier `FLLMAgentRequest` :

```text
bAllowFileWrites
bAllowShellExecution
bRequireDiffPreview
```

Les adaptateurs doivent refuser les écritures ou les commandes shell lorsque la requête ne les autorise pas.

## La politique de livraison (Shipping) échoue

Vérifier :

- `BuildRules` pour `Shipping`
- les politiques de route
- l'utilisation de fournisseurs cloud
- la disponibilité d'un secours local ou factice
- les listes d'autorisation de fournisseurs

Exécuter le commandlet localement :

```text
<UnrealEditorCommand> Project.uproject -run=LLMStoreCIPolicy -Config=Shipping -Unattended -NoSplash -NoSound
```

## Le statut des paramètres n'est pas clair

Ouvrir l'onglet `Status`. Il résume les fournisseurs, modèles, routes, bloqueurs, avertissements, clés manquantes et l'inventaire.

Si le statut semble obsolète :

- cliquer sur recharger si disponible
- fermer et rouvrir l'onglet
- redémarrer l'éditeur
- vérifier si `Config/LLMStore.json` a été modifié manuellement

## Le build échoue parce que Live Coding est actif

Live Coding dans Unreal peut bloquer un build externe complet pendant que l'éditeur est en cours d'exécution. Fermer l'éditeur ou désactiver Live Coding avant un build complet en ligne de commande.

Cela n'affecte pas l'utilisation normale de l'interface utilisateur, mais peut bloquer les builds de type CI ou la validation UHT.

## Références utiles

- Première configuration : [QUICKSTART.md](QUICKSTART.md)
- Détails des fournisseurs : [ProviderReference.md](ProviderReference.md)
- Politiques de route : [RoutePolicyReference.md](RoutePolicyReference.md)
- Secrets : [SECRET_BACKENDS.md](SECRET_BACKENDS.md)
- Coûts : [COST_TRACKING.md](COST_TRACKING.md)
- Intégration : [INTEGRATION.md](INTEGRATION.md)
- CI : [CommandletAndCI.md](CommandletAndCI.md)

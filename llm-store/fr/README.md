<!-- doc-provenance: AKDB:plugins/LLMStore/architecture.md; docs/architecture/plugins/LLMStore/product-facts.yml; reconciled 2026-06-20 -->
# LLM Store

LLM Store est un plugin Unreal Engine permettant de gérer de manière centralisée les fournisseurs d'IA, les modèles, les routes de tâches (task routes), les politiques (policies), les coûts, les secrets et les agents externes optionnels. Il est conçu comme un plugin d'infrastructure : les outils d'édition et les systèmes runtime n'ont pas besoin de savoir si une requête est traitée par Ollama, llama.cpp, OpenAI, Claude, Gemini, Azure OpenAI, Mistral, OpenRouter ou un fournisseur factice (mock). Ils appellent une route stable telle que `asset.explain`, `docs.summarize` ou `naming.review`.

## À qui s'adresse-t-il ?

LLM Store est utile lorsqu'un projet comporte plusieurs fonctionnalités d'IA et que ces fonctionnalités ne doivent pas coder en dur les identifiants de fournisseur, les noms de modèles, les règles cloud ou la logique de coût.

Cas d'utilisation typiques :

- utiliser des modèles locaux pour le développement, les tests, la CI ou les flux proches de la livraison
- autoriser les modèles cloud en développement mais les bloquer pour les builds de livraison (shipping)
- router les tâches d'IA via des noms de tâches stables plutôt que des noms de modèles directs
- évaluer les coûts par fournisseur, modèle et route
- conserver les clés API hors de la configuration du projet validée (committed)
- offrir la même surface d'intégration aux équipes C++ et Blueprint
- connecter des agents optionnels tels que Codex, Claude, Cursor ou des outils spécifiques au studio
- laisser les plugins spécifiques au projet fournir du contexte sans que LLM Store ne dépende d'eux
- exposer l'historique des jobs de l'éditeur via les routes UCM sans dépendre de Unified MCP Server

## Modules

| Module | Objectif |
| --- | --- |
| `LLMStoreInterface` | Structures publiques, interface façade, contrats de fournisseurs, contrats d'extensions et classes de base Blueprint. |
| `LLMStore` | Sous-système moteur, routage, exécution, gouvernance, secrets, livre de comptes (cost ledger) et bridge d'agent. |
| `LLMStoreEditor` | Onglet éditeur pour la configuration, les routes, le statut, l'aide, les agents, les coûts et la gouvernance. |

## Concepts clés

| Concept | Signification |
| --- | --- |
| Fournisseur (Provider) | Service technique ou serveur local, par exemple `ollama`, `llamacpp` ou `openai`. |
| Modèle | Un modèle concret servi par un fournisseur. |
| Route | Nom de tâche stable qui se résout en un modèle, une chaîne de secours (fallback) et une politique. |
| Politique (Policy) | Règle pour l'accès cloud, le comportement local uniquement, le budget de contexte, les listes d'autorisation/refus et les limites de coût. |
| Règle de coût | Règle de tarification utilisée pour estimer le coût d'une requête à partir des tokens d'invite et de réponse. |
| Agent | Adaptateur optionnel vers un outil externe comme Codex, Claude, Cursor ou un assistant de studio. |
| Fournisseur de contexte | Extension fournissant des packs de contexte neutres à partir des sources du projet, d'assets, de docs ou d'autres systèmes. |

## Interface utilisateur de l'éditeur

Ouvrez le plugin via :

```text
Tiny Tools -> LLM Store
```

Onglets principaux :

- `Setup` : **Quick-Start** en un clic pour la première exécution (Mock / Ollama / cloud), puis création de fournisseurs et modèles, édition des URL de base, définition des clés et test de connectivité.
- `Routes` : configuration des routes de tâches, chaînes de secours, modèles factices, modèles d'invites et politiques.
- `Agents` : inspection des adaptateurs d'agents Codex, Claude, Cursor et personnalisés ; ouverture des dialogues d'authentification.
- `Costs` : analyse des requêtes, tokens, coût estimé, succès de cache et exportation de rapports CSV.
- `Governance` : inspection du statut, événements d'audit, préréglages, état du cache et règles de build.
- `Status` : lecture du statut actuel des paramètres, avertissements, bloqueurs et inventaire.
- `Help` : explication dans l'éditeur des concepts et flux de travail prévus.
- `Advanced` : sections UI optionnelles apportées par les extensions.

## Démarrage rapide

1. Ouvrez `Tiny Tools -> LLM Store`.
2. Dans **Setup**, utilisez la carte **Quick-Start** (Mock, Ollama local ou cloud OpenAI/Anthropic) pour obtenir une route `default` fonctionnelle en un clic.
3. Ou créez manuellement un fournisseur et un modèle, puis ajoutez des routes dans l'onglet `Routes`.
4. Testez le fournisseur, le modèle et la route ; confirmez que la bannière de disponibilité devient verte.
5. Ajoutez des règles de coût si l'analyse du cloud ou du budget est importante.
6. Exécutez une requête et inspectez les onglets `Costs` et `Status`.

Consultez [QUICKSTART.md](QUICKSTART.md) pour les détails étape par étape (carte Quick-Start et configuration manuelle).

## Fournisseurs locaux

Types de fournisseurs locaux ou hébergés pris en charge :

- `ollama`
- `llamacpp`
- `lmstudio`
- `vllm`
- `tgi`
- `mock`

Ces fournisseurs ne nécessitent pas de clés API par défaut.

## Fournisseurs cloud

Types de fournisseurs cloud pris en charge :

- `openai`
- `anthropic`
- `gemini`
- `azure-openai`
- `mistral`
- `openrouter`

Les fournisseurs cloud nécessitent généralement une clé API. Les clés sont stockées dans le back-end de secret configuré, jamais dans `Config/LLMStore.json`.

## Blueprint et C++

Les fonctionnalités destinées aux consommateurs sont disponibles en C++ et en Blueprints.

Classes de base Blueprint :

- `ULLMBlueprintProviderAddOn`
- `ULLMBlueprintEmbeddingProviderAddOn`
- `ULLMBlueprintContractAddOn`
- `ULLMBlueprintPolicyAddOn`
- `ULLMBlueprintTestAddOn`
- `ULLMBlueprintContextProviderAddOn`
- `ULLMBlueprintAgentAddOn`

Consultez [INTEGRATION.md](INTEGRATION.md) et [CodeDocumentation.md](CodeDocumentation.md).

L'exécution de routes en flux (streaming) et hors flux partage une file d'attente contrôlée en concurrence. Utilisez `EnqueueRoute` pour les longs jobs locaux ; `ExecuteRouteStreaming` suit le même contrôle de requête active tout en renvoyant des blocs de flux via son API de rappel.

## Authentification des agents

L'onglet `Agents` peut afficher un bouton `Authenticate...` pour chaque agent. La boîte de dialogue affiche la commande de connexion, les instructions, le lien d'aide et les actions pour exécuter ou copier la commande. Les identifiants restent avec l'outil externe ; LLM Store ne stocke que le statut et les instructions.

Consultez [AGENT_AUTHENTICATION.md](AGENT_AUTHENTICATION.md).

## Suivi des coûts

LLM Store estime le coût à partir de :

- tokens d'invite rapportés par le fournisseur ou estimés par le store
- tokens de réponse rapportés par le fournisseur ou estimés par le store
- entrées `FLLMCostRule` correspondantes

Le livre de comptes des coûts est stocké à :

```text
Saved/LLMStore/CostLedger.json
```

Les exportations CSV sont enregistrées par défaut dans :

```text
Saved/LLMStore/CostReports/LLMStoreCostReport.csv
```

Consultez [COST_TRACKING.md](COST_TRACKING.md).

## Confidentialité et sécurité

- Les clés API n'ont pas leur place dans `Config/LLMStore.json`.
- Les fournisseurs locaux sont le choix par défaut préféré pour les données sensibles du projet.
- Les politiques peuvent restreindre l'utilisation du cloud par route.
- Les règles de build peuvent bloquer les fournisseurs cloud pour les builds de livraison.
- L'exécution des agents est explicite et contrôlée par les drapeaux de requête.

Consultez [SECRET_BACKENDS.md](SECRET_BACKENDS.md) pour les fichiers locaux chiffrés, Windows Credential Manager, macOS Keychain, 1Password et Azure Key Vault.

## Commencer ici

- [BUYER_GUIDE.md](BUYER_GUIDE.md) : vue d'ensemble, proposition de valeur et flux de travail pratiques pour les acheteurs.
- [QUICKSTART.md](QUICKSTART.md) : première configuration fonctionnelle de fournisseur/modèle/route.
- [UserManual.md](UserManual.md) : flux de travail complet de l'éditeur et utilisation de l'UI.
- [FAQ.md](FAQ.md) : questions et réponses prêtes pour Fab.

## Référence

- [SettingsReference.md](SettingsReference.md) : champs de configuration, valeurs par défaut, fichiers JSON de configuration et lignes directrices.
- [ProviderReference.md](ProviderReference.md) : types de fournisseurs locaux/cloud pris en charge, URL de base et remarques.
- [RoutePolicyReference.md](RoutePolicyReference.md) : politiques de routes, restrictions cloud/locales, règles de budget et règles de build.
- [COST_TRACKING.md](COST_TRACKING.md) : livre de comptes, règles de coût, exportation CSV et flux de travail d'analyse.
- [SECRET_BACKENDS.md](SECRET_BACKENDS.md) : stockage local chiffré et comportement des back-ends de secrets externes.
- [AGENT_AUTHENTICATION.md](AGENT_AUTHENTICATION.md) : adaptateurs d'agents de type Codex/Claude/Cursor et comportement de la boîte de dialogue d'authentification.
- [INTEGRATION.md](INTEGRATION.md) : modèles d'intégration C++ et Blueprint pour d'autres plugins.
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md) : problèmes courants et solutions.
- [TechnicalOverview.md](TechnicalOverview.md) : vue d'ensemble de l'architecture au niveau du mainteneur.

## Assets inclus

- [Screenshots/](Screenshots) : captures d'écran de documentation et schémas de flux de travail visuels.

## Vue d'ensemble visuelle

- [Screenshots/01-workflow-overview.svg](Screenshots/01-workflow-overview.svg)
- [Screenshots/02-editor-tabs.svg](Screenshots/02-editor-tabs.svg)
- [Screenshots/03-agent-cost-governance.svg](Screenshots/03-agent-cost-governance.svg)

## Flux de travail rapide JSON de configuration

1. Ouvrez `Tiny Tools -> LLM Store`.
2. Configurez les fournisseurs, modèles, routes, politiques et règles de coût.
3. Ouvrez `Governance`.
4. Utilisez `Export Setup JSON` pour écrire la configuration actuelle dans n'importe quel fichier choisi.
5. Utilisez `Validate JSON` pour inspecter un fichier de configuration sans l'appliquer.
6. Utilisez `Import JSON` uniquement après la réussite de la validation.

Les secrets ne sont jamais écrits dans le JSON de configuration. Reconnectez les clés de fournisseur via le back-end de secret ou les variables d'environnement après l'importation d'une configuration partagée.

## Visibilité des jobs UCM

LLM Store publie l'historique des jobs de l'éditeur en lecture seule via `llmstore.editor.jobs.list.v1` et `llmstore.editor.jobs.status.v1` lorsque Unreal Capability Mesh est activé. Unified MCP Server peut agréger ces routes via `jobs_list` / `jobs_status` ; LLM Store lui-même reste autarconique et ne nécessite pas de dépendance au temps de compilation envers UMCP.

## Commandlet

Exécutez les vérifications de politique CI depuis un terminal local ou un exécutant d'automatisation :

```powershell
<UnrealEditorCommand> "D:\PluginProjectGit\PluginProject.uproject" -run=LLMStoreCIPolicy -unattended -nop4 -nosplash -NoShaderCompile
```

`<UnrealEditorCommand>` est la cible Unreal Editor en ligne de commande pour votre installation locale du moteur.

Le commandlet vérifie les fournisseurs, modèles, routes, politiques et règles de build configurés. Il est destiné à la gouvernance de livraison, non à l'évaluation comparative en direct des fournisseurs.

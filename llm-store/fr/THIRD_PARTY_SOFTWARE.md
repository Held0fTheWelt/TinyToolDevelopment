<!-- doc-provenance: AKDB:plugins/LLMStore/architecture.md; docs/architecture/plugins/LLMStore/product-facts.yml; reconciled 2026-06-20 -->
# Logiciels tiers

LLM Store **ne comprend aucun code source tiers, binaire d'exécution, modèle d'IA, Node.js, Python ou exécutable autonome**. Il s'agit d'un plugin Unreal Engine en C++ utilisant les modules Unreal Engine et les API standard HTTP/JSON d'Unreal.

## Intégrations de fournisseurs optionnelles (fournies par l'acheteur, non incluses)

LLM Store est un coffre-fort et une couche de routage devant les fournisseurs de LLM. Vous choisissez quel fournisseur, le cas échéant, connecter. Aucun n'est requis pour installer le plugin, et le fournisseur **Mock** intégré fonctionne entièrement hors ligne sans compte ni téléchargement.

| Fournisseur | Ce que c'est | Comment l'intégrer |
| --- | --- | --- |
| Mock | Fournisseur hors ligne intégré | Aucun — fonctionne directement. |
| Ollama | Serveur LLM local que vous installez et exécutez | Installez Ollama, exécutez-le (`http://localhost:11434` par défaut), puis ajoutez un fournisseur `ollama`. Voir [QUICKSTART.md](QUICKSTART.md) §3. |
| llama.cpp | Serveur `llama-server` local que vous exécutez | Démarrez `llama-server`, puis ajoutez un fournisseur `llamacpp`. Voir [QUICKSTART.md](QUICKSTART.md) §3. |
| OpenAI | API cloud (votre compte) | Créez un fournisseur `openai` et collez votre clé API (stockée dans le back-end de secrets, jamais dans la configuration). Voir [QUICKSTART.md](QUICKSTART.md) §4 et [SECRET_BACKENDS.md](SECRET_BACKENDS.md). |
| Anthropic | API cloud (votre compte) | Créez un fournisseur `anthropic` et collez votre clé API. Voir [QUICKSTART.md](QUICKSTART.md) §4. |

Ces fournisseurs sont des logiciels/services externes appartenant à leurs éditeurs respectifs et sont obtenus directement auprès d'eux. LLM Store ne les redistribue pas. Les clés API et les identifiants d'agents vous appartiennent ; voir [SECRET_BACKENDS.md](SECRET_BACKENDS.md) et [AGENT_AUTHENTICATION.md](AGENT_AUTHENTICATION.md).

**Déclaration de logiciels tiers Fab :** aucun logiciel tiers inclus.

<!-- doc-provenance: AKDB:plugins/LLMStore/architecture.md; docs/architecture/plugins/LLMStore/product-facts.yml; reconciled 2026-06-20 -->
# Software di terze parti

LLM Store **non include codice sorgente di terze parti, file binari runtime, modelli IA, Node.js, Python o eseguibili autonomi**. È un plugin per Unreal Engine in C++ che utilizza moduli Unreal Engine e API HTTP/JSON standard di Unreal.

## Integrazioni provider opzionali (fornite dall'acquirente, non incluse)

LLM Store è un caveau e un livello di instradamento di fronte ai provider LLM. Scegli tu quale provider, se presente, connettere. Nessuno di essi è richiesto per installare il plugin, e il provider **Mock** integrato funziona completamente offline senza account o download.

| Provider | Che cos'è | Come integrarlo |
| --- | --- | --- |
| Mock | Provider offline integrato | Nessuna azione richiesta — funziona direttamente. |
| Ollama | Server LLM locale da installare ed eseguire | Installa Ollama, eseguilo (`http://localhost:11434` predefinito), quindi aggiungi un provider `ollama`. Vedi [QUICKSTART.md](QUICKSTART.md) §3. |
| llama.cpp | Server `llama-server` locale da eseguire | Avvia `llama-server`, quindi aggiungi un provider `llamacpp`. Vedi [QUICKSTART.md](QUICKSTART.md) §3. |
| OpenAI | API Cloud (tuo account) | Crea un provider `openai` e incolla la tua chiave API (salvata nel backend dei segreti, mai nella configurazione). Vedi [QUICKSTART.md](QUICKSTART.md) §4 e [SECRET_BACKENDS.md](SECRET_BACKENDS.md). |
| Anthropic | API Cloud (tuo account) | Crea un provider `anthropic` e incolla la tua chiave API. Vedi [QUICKSTART.md](QUICKSTART.md) §4. |

Questi provider rappresentano software/servizi esterni di proprietà dei rispettivi fornitori e sono ottenuti direttamente da essi. LLM Store non li ridistribuisce. Le chiavi API e le credenziali degli agenti sono di tua proprietà; vedi [SECRET_BACKENDS.md](SECRET_BACKENDS.md) e [AGENT_AUTHENTICATION.md](AGENT_AUTHENTICATION.md).

**Dichiarazione software di terze parti per Fab:** nessun software di terze parti incluso.

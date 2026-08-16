<!-- doc-provenance: AKDB:plugins/LLMStore/architecture.md; docs/architecture/plugins/LLMStore/product-facts.yml; reconciled 2026-06-20 -->
# Software von Drittanbietern

LLM Store **enthält keinen mitgelieferten Quellcode von Drittanbietern, keine Runtime-Binärdateien, KI-Modelle, Node.js, Python oder eigenständigen ausführbaren Dateien**. Es ist ein C++ Unreal Engine-Plugin, das Unreal Engine-Module und standardmäßige Unreal HTTP/JSON-APIs verwendet.

## Optionale Provider-Integrationen (vom Käufer bereitgestellt, nicht mitgeliefert)

LLM Store ist ein Tresor und eine Routing-Schicht vor LLM-Providern. Sie wählen aus, welcher Provider, falls vorhanden, verbunden wird. Keiner ist für die Installation des Plugins erforderlich, und der eingebaute **Mock**-Provider läuft vollständig offline ohne Konto oder Download.

| Provider | Was es ist | Wie man es integriert |
| --- | --- | --- |
| Mock | Eingebauter Offline-Provider | Keine — funktioniert direkt nach der Installation. |
| Ollama | Lokaler LLM-Server, den Sie installieren und ausführen | Installieren Sie Ollama, führen Sie es aus (Standard `http://localhost:11434`), fügen Sie dann einen `ollama`-Provider hinzu. Siehe [QUICKSTART.md](QUICKSTART.md) §3. |
| llama.cpp | Lokaler `llama-server`, den Sie ausführen | Starten Sie `llama-server`, fügen Sie dann einen `llamacpp`-Provider hinzu. Siehe [QUICKSTART.md](QUICKSTART.md) §3. |
| OpenAI | Cloud-API (Ihr Konto) | Erstellen Sie einen `openai`-Provider und fügen Sie Ihren API-Schlüssel ein (gespeichert im Geheimnis-Backend, niemals in der Konfiguration). Siehe [QUICKSTART.md](QUICKSTART.md) §4 und [SECRET_BACKENDS.md](SECRET_BACKENDS.md). |
| Anthropic | Cloud-API (Ihr Konto) | Erstellen Sie einen `anthropic`-Provider und fügen Sie Ihren API-Schlüssel ein. Siehe [QUICKSTART.md](QUICKSTART.md) §4. |

Diese Provider sind externe Software/Dienste, die den jeweiligen Anbietern gehören und direkt von diesen bezogen werden. LLM Store verteilt sie nicht weiter. API-Schlüssel und Agenten-Zugangsdaten sind Ihre eigenen; siehe [SECRET_BACKENDS.md](SECRET_BACKENDS.md) und [AGENT_AUTHENTICATION.md](AGENT_AUTHENTICATION.md).

**Fab-Erklärung zu Drittanbietersoftware:** Keine mitgelieferte Drittanbietersoftware.

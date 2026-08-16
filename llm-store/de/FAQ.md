<!-- doc-provenance: AKDB:plugins/LLMStore/architecture.md; docs/architecture/plugins/LLMStore/product-facts.yml; reconciled 2026-06-20 -->
# FAQ (Häufig gestellte Fragen)

## Gibt es eine geführte Erstkonfiguration?

Ja. Die Registerkarte **Setup** enthält eine **Quick-Start**-Karte. Sie kann mit einem Klick einen vollständigen Mock-, Ollama- oder Cloud-OpenAI/Anthropic-Stack (Provider, Modell und `default`-Route) erstellen, einen Verbindungstest ausführen und die Bereitschaft aktualisieren. Bereits erstellte Provider oder eine von Ihnen konfigurierte `default`-Route werden dabei nicht überschrieben.

## Ist LLM Store ein Chatbot?

Nein. LLM Store ist eine Infrastruktur für Provider, Modelle, Routen, Richtlinien, Geheimnisse, Kostenverfolgung und Agenten. Ein Chatbot oder Asset-Assistent kann LLM Store verwenden, ist aber ein separates Tool.

## Warum sollte ich Routen anstelle von Modellnamen verwenden?

Routen halten den Code von Funktionen stabil. Wenn ein Tool `docs.summarize` aufruft, kann das Team später von Ollama zu llama.cpp oder OpenAI wechseln, ohne den Code des Tools zu ändern.

## Kann ich alles lokal ausführen?

Ja. Verwenden Sie Provider wie `ollama`, `llamacpp`, `lmstudio`, `vllm`, `tgi` oder `mock`, setzen Sie Richtlinien auf "nur lokal" und blockieren Sie Cloud über Build-Regeln.

## Wird llama.cpp unterstützt?

Ja. Der Provider-Typ `llamacpp` ist für lokale llama.cpp-Server gedacht. Die typische Basis-URL ist:

```text
http://localhost:8080
```

## Werden API-Schlüssel in der Projektdatei gespeichert?

Nein. `Config/LLMStore.json` speichert Provider, Modelle, Routen und Richtlinien, aber keine Schlüssel. Schlüssel befinden sich im Geheimnis-Speicher oder in Umgebungsvariablen.

## Welches Geheimnis-Backend sollte ich verwenden?

Für die Einrichtung durch einen einzelnen Entwickler ist `EncryptedFile` einfach. Für Teams sind Windows Credential Manager, macOS Keychain, 1Password oder Azure Key Vault gewöhnlich besser geeignet.

## Kann Blueprint alles, was C++ kann?

Die wichtigen konsumentenseitigen Integrationspunkte verfügen über Blueprint-Versionen. Dies umfasst Provider, Embeddings, Richtlinien, Tests, Kontext-Provider, Agenten und Subsystem-Fassadenfunktionen.

## Kann ich Codex, Claude oder Cursor verbinden?

Ja, über Agenten-Add-Ons. Der Store kann Status, Authentifizierungshinweise und Aufgabenausführung vereinheitlichen. Die konkrete Tool-Integration bleibt ein Adapter und muss Sicherheitsregeln beachten.

## Führt LLM Store automatisch Shell-Befehle aus?

Nur wenn ein Agenten-Adapter die Ausführung explizit implementiert und die Anfrage-Flags dies zulassen. `bAllowShellExecution`, `bAllowFileWrites` und `bRequireDiffPreview` teilen die Sicherheitsanforderungen des Aufrufers mit.

## Wie genau ist die Kostenverfolgung?

Die Genauigkeit hängt von den Nutzungsdaten des Providers und den `CostRules` ab. Wenn ein Provider keine Token-Anzahlen zurückgibt, schätzt der Store die Tokens. Die Abrechnung des Providers bleibt die primäre Quelle der Wahrheit für Rechnungen.

## Kann ich lokalen Modellen Kosten zuweisen?

Ja. Lokale Modelle können `0` kosten oder interne Abrechnungswerte wie geschätzte GPU-Kosten pro 1000 Tokens verwenden.

## Was gehört nicht direkt in den LLM Store?

Konkrete Funktions-Tools wie Asset-Erklärungen, Blueprint-Dokumentation, Benennungsprüfungen oder Projekt-RAG sollten den LLM Store verwenden, befinden sich jedoch normalerweise in separaten Plugins oder Add-Ons. LLM Store bleibt in sich geschlossen.

## Was passiert, wenn ein Provider offline ist?

Der Store aktualisiert die Gesundheit des Providers, kann Fallbacks versuchen und zeichnet Fehler im Audit-Log auf. Schutzeinstellungen (Circuit Breaker) verhindern wiederholte teure oder hängende Versuche.

## Kann ich LLM Store in der CI verwenden?

Ja. Verwenden Sie das `LLMStoreCIPolicy`-Commandlet und Automatisierungstests. Ein GitHub Actions-Beispiel ist in `Documentation/CI` enthalten.

## Muss ich Cloud-Provider live testen?

Nicht immer. Für die Release-Sicherheit reichen Mock-Tests, Konfigurationsvalidierung und optionale manuelle Provider-Smoke-Tests oft aus. Cloud-Tests sollten nur mit bewusst konfigurierten Geheimnissen ausgeführt werden.

## Welche Dateien sollte ich committen?

Committen:

- `Config/LLMStore.json`
- optionale Voreinstellungen (Presets)
- Teamdokumentation für Produktionsrouten

Nicht committen:

- API-Schlüssel
- lokale Geheimnis-Dateien
- Kostenbuch-Dateien, wenn sie sensible Betriebsdaten enthalten

## Kann ich vollständige Setups exportieren und importieren?

Ja. Die Registerkarte Governance kann das aktuelle Setup in eine beliebige JSON-Datei exportieren, eine JSON-Datei ohne Anwendung validieren und ein JSON-Setup erst importieren, wenn die Validierung erfolgreich war. Exportierte Setup-Dateien enthalten keine API-Schlüssel.

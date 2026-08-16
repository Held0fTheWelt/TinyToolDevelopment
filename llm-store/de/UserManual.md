<!-- doc-provenance: AKDB:plugins/LLMStore/architecture.md; docs/architecture/plugins/LLMStore/product-facts.yml; reconciled 2026-06-20 -->
# Benutzerhandbuch

Dieses Handbuch beschreibt LLM Store aus der Perspektive eines Käufers, technischen Künstlers, Blueprint-Entwicklers oder Tools-Programmierers. Es erklärt die Editor-Workflows und verweist bei Bedarf auf tiefere technische Referenzen.

## Ziel des Plugins

LLM Store ist eine zentrale KI-Steuerungsschicht für Unreal Engine-Projekte. Andere Plugins und Tools müssen nicht wissen, ob ein Prompt an Ollama, llama.cpp, OpenAI, Claude, Gemini, Azure OpenAI, Mistral, OpenRouter oder ein Mock geht. Sie rufen eine stabile Aufgaben-Route auf, wie z. B.:

```text
docs.summarize
asset.explain
naming.review
rag.embed
agent.patch
```

Die Route entscheidet über Provider, Modell, Fallback, Richtlinie, Kostenregel und Geheimnis-Backend.

## Editor öffnen

Öffnen:

```text
Tiny Tools -> LLM Store
```

Die Registerkarte ist für den täglichen Gebrauch konzipiert. Sie zeigt nicht nur rohe Einstellungen an; sie führt durch Einrichtung, Routen, Status, Hilfe, Agenten, Kosten und Governance.

## Erste Einrichtung

### Quick-Start-Karte (schnellster Weg)

1. Öffnen Sie `Tiny Tools -> LLM Store`.
2. Gehen Sie zu `Setup`. Der Bereich **Quick Start — get running in one click** befindet sich ganz oben.
3. Wählen Sie eine Option:
   - **Just try it (Mock)** — vollständig offline; kein API-Schlüssel; ideal für CI und ersten Kontakt.
   - **Local (Ollama)** — erstellt `quickstart_ollama` unter `localhost:11434`; starten Sie Ollama vor dem Testen.
   - **Create OpenAI** oder **Create Anthropic** — fügen Sie einen API-Schlüssel in das Passwortfeld ein und klicken Sie auf die Schaltfläche des Herstellers. Der Schlüssel wird nur im Geheimnis-Backend gespeichert.
4. Lesen Sie die Statuszeile unter den Schaltflächen und das Bereitschaftsbanner über den Registerkarten.
5. Wenn die Bereitschaft grün ist, klappen Sie den Quick-Start-Bereich nur dann wieder auf, wenn Sie einen weiteren Starter-Stack benötigen (bestehende `quickstart_*`-Einträge werden nicht dupliziert; Ihre eigene `default`-Route wird niemals überschrieben).

Starter-Stacks verwenden stabile IDs (`quickstart_mock`, `quickstart_ollama`, `quickstart_openai`, `quickstart_anthropic`) und verdrahten immer eine `default`-Aufgabenroute, sofern Sie nicht bereits eine definiert haben.

### Manuelle Einrichtung (volle Kontrolle)

1. Öffnen Sie `Tiny Tools -> LLM Store`.
2. Gehen Sie zu `Setup` (unterhalb der Quick-Start-Karte).
3. Erstellen Sie einen Provider, z. B. `ollama`, `llamacpp`, `openai` oder `anthropic`.
4. Bestätigen Sie, dass die voreingestellte Basis-URL angemessen ist.
5. Erstellen Sie ein Modell für den Provider.
6. Gehen Sie zu `Routes`.
7. Erstellen Sie eine Route, z. B. `docs.summarize`.
8. Wählen Sie das bevorzugte Modell.
9. Klicken Sie auf `Test Route`.
10. Prüfen Sie `Status` auf Warnungen oder Blocker.

## Provider-Einrichtung

Ein Provider beschreibt den technischen Dienst, nicht das Modell selbst.

| Feld | Bedeutung |
| --- | --- |
| `Id` | Stabile projektlokale ID, z. B. `local-ollama`. |
| `DisplayName` | Lesbarer Name in UI und Berichten. |
| `Type` | Provider-Typ wie `ollama`, `llamacpp` oder `openai`. |
| `BaseUrl` | HTTP-Endpunkt. Bekannte Provider erhalten nützliche Standardwerte. |
| `Enabled` | Deaktiviert den Provider, ohne seine Einstellungen zu löschen. |
| `RetryCount` | Wiederholungsversuche bei vorübergehenden Fehlern. |
| `TimeoutSeconds` | Provider-spezifisches Zeitlimit. |
| `CircuitBreaker...` | Schutz vor wiederholten Fehlern oder hängenden Servern. |

Lokale Provider benötigen normalerweise keinen Schlüssel. Cloud-Provider benötigen normalerweise einen Schlüssel im Geheimnis-Speicher.

## Bekannte Provider

| Provider-Typ | Standard-Basis-URL | Typische Nutzung |
| --- | --- | --- |
| `ollama` | `http://localhost:11434` | Lokale Modelle über Ollama. |
| `llamacpp` | `http://localhost:8080` | Lokale llama.cpp-Server-Inferenz. |
| `lmstudio` | `http://localhost:1234/v1` | Lokale LM Studio-Modelle. |
| `vllm` | `http://localhost:8000/v1` | Hochleistungs-Inferenz lokal oder auf Servern. |
| `tgi` | `http://localhost:8080` | Hugging Face Text Generation Inference. |
| `openai` | `https://api.openai.com/v1` | OpenAI API. |
| `anthropic` | `https://api.anthropic.com` | Claude API. |
| `gemini` | `https://generativelanguage.googleapis.com/v1beta` | Google Gemini API. |
| `azure-openai` | projektspezifisch | Azure-Endpunkt und Deployment-Logik. |
| `mistral` | `https://api.mistral.ai/v1` | Mistral API. |
| `openrouter` | `https://openrouter.ai/api/v1` | Router für viele Cloud-Modelle. |
| `mock` | leer | Tests, UI-Entwicklung, CI und Offline-Arbeit. |

## Modelle

Ein Modell gehört zu genau einem Provider.

| Feld | Bedeutung |
| --- | --- |
| `Id` | Stabile projektlokale Modell-ID. |
| `Name` | Drahtname des Providers, z. B. `llama3.1:8b` oder `gpt-4o-mini`. |
| `ProviderId` | Provider, der das Modell bereitstellt. |
| `Role` | Optionale Rolle wie `fast`, `reasoning`, `embedding` oder `local`. |
| `Structured` | Markiert Modelle, von denen erwartet wird, dass sie JSON/Schema-Ausgaben gut handhaben. |
| `TimeoutSeconds` | Modell-spezifisches Zeitlimit. |
| `Enabled` | Deaktiviert das Modell, ohne Routen zu löschen. |

## Routen

Routen sind das wichtigste Konzept des Stores. Eine Funktion fordert eine Aufgabe an, kein Modell.

Beispiel:

```text
TaskKind: docs.summarize
PreferredModelId: local-fast
FallbackModelIds:
  - cloud-reasoning
  - mock-docs
Policy: local-only for shipping
```

Vorteile:

- Funktionen bleiben stabil, wenn sich Modelle ändern
- Richtlinien können pro Aufgabe angewendet werden
- Fallback-Ketten können lokale, Cloud- und Mock-Modelle mischen
- Kosten können nach Aufgabe analysiert werden
- CI kann Routenrichtlinien validieren, ohne jedes Tool zu kennen

## Route testen

Verwenden Sie `Test Route` auf der Registerkarte `Routes`. Der Test prüft:

- Existiert die Route?
- Ist die Route aktiviert?
- Existiert das Modell?
- Existiert der Provider?
- Ist der Provider aktiviert?
- Existiert der erforderliche Schlüssel?
- Antwortet der Provider auf eine kleine Anfrage?

Fehler erscheinen im Statusbereich und im Provider-Health-Dashboard.

## Richtlinien (Policies)

Richtlinien entscheiden, ob eine Route verwendet werden darf.

Typische Regeln:

- Cloud für sensible Daten verbieten
- Nur lokale Modelle für Shipping zulassen
- Maximales Kontextbudget festlegen
- Maximale Kosten pro Anfrage festlegen
- Spezifische Provider-Typen erlauben oder verweigern

Richtlinien gehören in den LLM Store. Ein anderes Plugin kann Kontext liefern oder eine Route aufrufen, aber die zentrale Governance-Entscheidung verbleibt im Store.

## Agenten

Die Registerkarte `Agents` zeigt optionale Adapter wie Codex, Claude, Cursor oder benutzerdefinierte Studio-Tools.

| Status | Bedeutung |
| --- | --- |
| `NotInstalled` | Tool wurde nicht gefunden. |
| `Installed` | Tool existiert, Authentifizierung ist unklar oder fehlt. |
| `AuthRequired` | Authentifizierung muss abgeschlossen werden. |
| `Available` | Tool ist nutzbar. |
| `Disabled` | Adapter ist deaktiviert. |
| `Error` | Adapter meldet einen Fehler. |

Die Schaltfläche `Authenticate...` öffnet einen Dialog mit Befehl, Anweisungen, Hilfe-Link und Kopieraktion für die manuelle Terminalnutzung. LLM Store speichert keine Zugangsdaten externer Tools.

## Kostenanalyse

Die Registerkarte `Costs` sammelt und analysiert das Kostenbuch (Cost Ledger).

Sie zeigt:

- Gesamtereignisse
- Erfolgreiche Ereignisse
- Cache-Treffer
- Prompt-Tokens
- Completion-Tokens
- Geschätzte Kosten
- Aufschlüsselung nach Provider, Modell und Route
- CSV-Export

Kosten sind nur so genau wie die Nutzungsdaten des Providers und die konfigurierten Kostenregeln. Lokale Modelle können kostenlos sein oder mit internen Hardwarekosten angesetzt werden.

## Geheimnis-Speicher (Secret Store)

API-Schlüssel gehören nicht in `Config/LLMStore.json`.

Unterstützte Backends:

- Verschlüsselte lokale Datei
- Windows Credential Manager
- macOS Keychain
- 1Password CLI
- Azure Key Vault über Azure CLI

Umgebungsvariablen haben Vorrang:

```text
LLMSTORE_<PROVIDER_ID>_KEY
```

Beispiel:

```text
LLMSTORE_OPENAI_MAIN_KEY
```

## Registerkarte Status

Die Registerkarte `Status` beantwortet: „Ist mein Store jetzt einsatzbereit?“

Sie zeigt:

- Globale Bereitschaft
- Blocker
- Warnungen
- Provider-Inventar
- Fehlende Schlüssel
- Deaktivierte Provider oder Modelle
- Routenprobleme

Verwenden Sie diese Registerkarte, bevor Sie Einstellungen mit einem Team teilen, CI ausführen oder ein Release paketieren.

## Setup-JSON-Export, Validierung und Import

Die Registerkarte `Governance` enthält Setup-JSON-Aktionen zum Teilen oder Verschieben vollständiger LLM Store-Setups.

Verfügbare Aktionen:

| Aktion | Zweck |
| --- | --- |
| `Export Setup JSON` | Wählen Sie einen beliebigen Ordner und Dateinamen und schreiben Sie das aktuelle Setup als JSON. Geheimnisse sind nicht enthalten. |
| `Validate JSON` | Wählen Sie eine JSON-Datei und validieren Sie Schema, Provider-IDs, Modellreferenzen, Routen und Warnungen, ohne sie anzuwenden. |
| `Import JSON` | Wählen Sie eine JSON-Datei, validieren Sie sie und wenden Sie sie nur an, wenn die Validierung erfolgreich war. |

Der Importer akzeptiert sowohl das verpackte LLM Store-Setup-Format als auch ein rohes `FLLMStoreConfig`-JSON-Objekt. Dies macht ihn geeignet für Voreinstellungen, Sicherungen, Team-Übergabedateien und manuell geprüfte Konfigurations-Snapshots.

## Registerkarte Hilfe

Die Registerkarte `Help` erklärt direkt im Editor:

- Was ein Provider ist
- Was ein Modell ist
- Warum Routen anstelle direkter Modellnamen verwendet werden
- Wie lokale und Cloud-Provider zusammenarbeiten
- Wie Richtlinien und Build-Regeln angewendet werden
- Was die Kostenverfolgung misst
- Wie Agenten verbunden werden

Der Hilfebereich ist im Plugin enthalten, damit Käufer für grundlegende Konzepte nicht zwischen einer Website, README und der Editor-UI hin und her springen müssen.

## Blueprint-Nutzung

Wichtige Integrationspunkte sind in Blueprints verfügbar.

| Klasse | Zweck |
| --- | --- |
| `ULLMBlueprintProviderAddOn` | Einen Provider aus Blueprint verbinden. |
| `ULLMBlueprintEmbeddingProviderAddOn` | Einen Embedding-Provider aus Blueprint verbinden. |
| `ULLMBlueprintContractAddOn` | Modellverträge validieren. |
| `ULLMBlueprintPolicyAddOn` | Routen zur Laufzeit erlauben oder ablehnen. |
| `ULLMBlueprintTestAddOn` | Setup- oder Statustests hinzufügen. |
| `ULLMBlueprintContextProviderAddOn` | Projektkontext als Kontextpakete bereitstellen. |
| `ULLMBlueprintAgentAddOn` | Externe CLIs oder Editor-Assistenten verbinden. |

## C++-Nutzung

C++-Benutzer erhalten den Store über das Engine-Subsystem:

```cpp
ULLMStoreSubsystem* Store = GEngine->GetEngineSubsystem<ULLMStoreSubsystem>();
```

Anschließend können Routen aufgelöst, Anfragen ausgeführt, Kontextpakete gebaut, Agenten aufgerufen und Kostenberichte gelesen werden.

Siehe [INTEGRATION.md](INTEGRATION.md) und [CodeDocumentation.md](CodeDocumentation.md).

## Empfohlene Workflows

### Lokale Entwicklung

1. Erstellen Sie einen `ollama`- oder `llamacpp`-Provider.
2. Fügen Sie ein lokales Modell hinzu.
3. Weisen Sie Routen dem lokalen Modell zu.
4. Deaktivieren Sie Cloud über Richtlinien.
5. Behalten Sie einen `mock`-Pfad für Tests bei.

### Hybride Entwicklung

1. Verwenden Sie lokale Modelle für schnelle Aufgaben.
2. Fügen Sie Cloud-Fallback für schwerere Aufgaben hinzu.
3. Setzen Sie Kostengrenzen.
4. Überprüfen Sie die Kostenverfolgung regelmäßig.
5. Halten Sie Shipping-Build-Regeln rein lokal/mock.

### Team-Einrichtung

1. Committen Sie `Config/LLMStore.json`.
2. Committen Sie keine Schlüssel.
3. Dokumentieren Sie das Geheimnis-Backend.
4. Exportieren Sie ein Preset.
5. Prüfen Sie die Registerkarte `Status`.
6. Aktivieren Sie CI-Richtlinienprüfungen.

## Grenzen

LLM Store ist kein fertiges Asset-Erklärungs-Tool, Blueprint-Review-Tool oder RAG-Produkt. Es bietet Routen, Provider, Richtlinien, Kostenverfolgung, Geheimnisse und Schnittstellen. Konkrete Funktions-Tools können sich damit verbinden, ohne dass LLM Store von diesen Tools abhängt.

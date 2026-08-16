<!-- doc-provenance: AKDB:plugins/LLMStore/architecture.md; docs/architecture/plugins/LLMStore/product-facts.yml; reconciled 2026-06-20 -->
# Schnellstart

Diese Anleitung führt Sie durch die erste funktionierende LLM Store-Route.

## 1. Öffnen Sie die Editor-Registerkarte

Öffnen:

```text
Tiny Tools -> LLM Store
```

Der obere Bereich fasst geladene Provider, Modelle, Routen, Embedding-Routen, Bereitschaftsstatus und geschätzte Kosteninformationen zusammen.

## 2. Verwenden Sie die Quick-Start-Karte (empfohlen für den ersten Start)

Auf der Registerkarte **Setup** wird die Karte **Quick Start** über den Provider- und Modellbereichen angezeigt. Wählen Sie einen Pfad:

| Schaltfläche | Was wird erstellt | API-Schlüssel |
| --- | --- | --- |
| **Just try it (Mock)** | Offline-Mock-Provider, Modell und `default`-Route | Keiner |
| **Local (Ollama)** | Ollama unter `http://localhost:11434`, Standardmodell `llama3`, `default`-Route | Keiner (Ollama muss laufen) |
| **Create OpenAI** | OpenAI-Provider, `gpt-4o-mini`-Modell, `default`-Route | Schlüssel im Feld einfügen (wird nur im Secret Store gespeichert) |
| **Create Anthropic** | Anthropic-Provider, `claude-3-5-haiku-latest`-Modell, `default`-Route | Schlüssel im Feld einfügen (wird nur im Secret Store gespeichert) |

Nachdem Sie auf eine Schaltfläche geklickt haben, führt LLM Store Folgendes aus:

1. Wendet den Starter-Stack idempotent an (stabile `quickstart_*`-IDs; überschreibt niemals Ihre bestehenden Provider oder eine von Ihnen bereits konfigurierte `default`-Route).
2. Speichert einen Cloud-API-Schlüssel über `SetProviderKey`, wenn Sie einen angegeben haben (wird niemals in `Config/LLMStore.json` geschrieben).
3. Führt **Test Connection** aus und aktualisiert das Bereitschaftsbanner.

Wenn die Bereitschaft bereits grün ist, wird die Karte eingeklappt mit einem kurzen Titel „ready — expand to run Quick-Start again“ angezeigt.

Für benutzerdefinierte URLs, zusätzliche Modelle oder aufgabenspezifische Routen fahren Sie mit den manuellen Schritten unten fort.

## 3. Erstellen Sie einen lokalen Provider (manuell)

Ein lokaler Provider ist der einfachste erste Test, da kein API-Schlüssel erforderlich ist.

### Option A: Ollama

1. Starten Sie Ollama lokal.
2. Laden Sie ein Modell herunter:

```text
ollama pull llama3.1
```

3. Erstellen Sie unter `Setup` einen Provider:

```text
Id: ollama-local
DisplayName: Ollama Local
Type: ollama
BaseUrl: http://127.0.0.1:11434
Enabled: true
```

4. Erstellen Sie ein Modell:

```text
Id: local-chat
Name: llama3.1
DisplayName: Local Chat
ProviderId: ollama-local
Role: fast
Enabled: true
```

### Option B: llama.cpp

Starten Sie einen lokalen llama.cpp-Server:

```text
llama-server -m C:\Models\model.gguf --host 127.0.0.1 --port 8080
```

Erstellen Sie dann:

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

## 4. Erstellen Sie einen Cloud-Provider (manuell)

Cloud-Provider benötigen normalerweise einen API-Schlüssel. Der Schlüssel wird im Geheimnis-Backend gespeichert, nicht in `Config/LLMStore.json`.

Beispiel:

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

Setzen Sie dann den Schlüssel im Provider-Bereich oder über eine Umgebungsvariable:

```text
LLMSTORE_OPENAI_MAIN_KEY
```

## 5. Erstellen Sie eine Route

Erstellen Sie eine Route auf der Registerkarte `Routes`:

```text
TaskKind: docs.summarize
PreferredModelId: local-chat
FallbackModelIds:
  - openai-fast
MockModelId: mock-docs
bUseMock: false
```

Wenn Sie mit llama.cpp begonnen haben, verwenden Sie `local-llamacpp` als bevorzugtes Modell.

## 6. Fügen Sie eine Richtlinie (Policy) hinzu

Für eine sichere, lokal bevorzugte Route:

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

Für eine hybride Entwicklungsroute erlauben Sie Cloud und fügen Sie eine Kostengrenze hinzu:

```text
bAllowCloud: true
bLocalOnly: false
MaxEstimatedCost: 0.05
```

## 7. Testen Sie Provider, Modell und Route

Verwenden Sie die Test-Schaltflächen im Editor.

Wenn die Route nicht aufgelöst wird, prüfen Sie:

- Ist der Provider aktiviert?
- Ist das Modell aktiviert?
- Verweist das Modell auf den richtigen Provider?
- Verwendet die Route die richtige Modell-ID?
- Ist der API-Schlüssel für den Cloud-Provider gesetzt?
- Läuft der lokale Server?
- Erlaubt die Richtlinie den ausgewählten Provider-Typ?

## 8. Fügen Sie Kostenregeln hinzu

Die Registerkarte `Costs` wird nützlich, sobald Preisregeln existieren.

Beispiel:

```text
ProviderType: openai
ModelId: openai-fast
InputCostPer1KTokens: 0.00015
OutputCostPer1KTokens: 0.00060
Currency: USD
```

Lokale Provider können bei `0` bleiben oder ein internes Kostenmodell verwenden.

## 9. Führen Sie eine Anfrage aus

Nach einer Anfrage zeigt die Registerkarte `Costs`:

- Ereignisanzahl
- Erfolgsanzahl
- Cache-Treffer
- Prompt-Tokens
- Completion-Tokens
- Geschätzte Kosten
- Aufschlüsselung nach Provider/Modell/Aufgabe
- Jüngste Ereignisse

Verwenden Sie `Export CSV`, um Berichte zu schreiben nach:

```text
Saved/LLMStore/CostReports
```

## 10. Prüfen Sie den Status

Öffnen Sie die Registerkarte `Status`. Der wichtigste Bereich ist `Attention`, da er fehlende Schlüssel, fehlerhafte Routen, deaktivierte Provider und Richtlinienprobleme anzeigt.

## 11. Optionale Agenten-Einrichtung

So verbinden Sie Codex, Claude, Cursor oder einen benutzerdefinierten Agenten:

1. Öffnen Sie die Registerkarte `Agents`.
2. Wählen Sie einen Agenten aus.
3. Klicken Sie auf `Authenticate...`.
4. Verwenden Sie `Copy Command` und führen Sie den Befehl manuell in Ihrem Terminal aus.
5. Aktualisieren Sie den Status.

Beispiele:

```text
codex login
claude auth login
```

LLM Store speichert keine Agenten-Zugangsdaten.

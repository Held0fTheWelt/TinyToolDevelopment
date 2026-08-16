<!-- doc-provenance: AKDB:plugins/LLMStore/architecture.md; docs/architecture/plugins/LLMStore/product-facts.yml; reconciled 2026-06-20 -->
# LLM Store

LLM Store ist ein Unreal Engine-Plugin zur zentralen Verwaltung von AI-Providern, Modellen, Aufgaben-Routen (Task Routes), Richtlinien (Policies), Kosten, Geheimnissen (Secrets) und optionalen externen Agenten. Es ist als Infrastruktur-Plugin konzipiert: Editor-Tools und Runtime-Systeme müssen nicht wissen, ob eine Anfrage von Ollama, llama.cpp, OpenAI, Claude, Gemini, Azure OpenAI, Mistral, OpenRouter oder einem Mock-Provider bedient wird. Sie rufen eine stabile Route wie `asset.explain`, `docs.summarize` oder `naming.review` auf.

## Für wen ist es gedacht?

LLM Store ist nützlich, wenn ein Projekt mehr als eine KI-Funktion hat und diese Funktionen keine Provider-Zugangsdaten, Modellnamen, Cloud-Regeln oder Kostenlogik hartkodieren sollen.

Typische Anwendungsfälle:

- Vergewissern Sie sich lokaler Modelle für Entwicklung, Tests, CI oder versandnahe Workflows
- Erlauben Sie Cloud-Modelle in der Entwicklung, aber blockieren Sie diese für Shipping-Builds
- Leiten Sie KI-Aufgaben über stabile Aufgabennamen statt über direkte Modellnamen
- Bewerten Sie Kosten nach Provider, Modell und Route
- Halten Sie API-Schlüssel aus der committeten Projektkonfiguration fern
- Bieten Sie C++- und Blueprint-Teams dieselbe Integrationsfläche
- Verbinden Sie optionale Agenten wie Codex, Claude, Cursor oder studiospezifische Tools
- Lassen Sie projektspezifische Plugins Kontext bereitstellen, ohne dass LLM Store von ihnen abhängt
- Stellen Sie die Editor-Jobhistorie über UCM-Routen bereit, ohne vom Unified MCP Server abzuhängen

## Module

| Modul | Zweck |
| --- | --- |
| `LLMStoreInterface` | Öffentliche Strukts, Fassaden-Schnittstelle, Provider-Verträge, Add-On-Verträge und Blueprint-Basisklassen. |
| `LLMStore` | Engine-Subsystem, Routing, Ausführung, Governance, Geheimnisse, Kostenbuch (Cost Ledger) und Agent-Bridge. |
| `LLMStoreEditor` | Editor-Registerkarte für Einrichtung, Routen, Status, Hilfe, Agenten, Kosten und Governance. |

## Kernkonzepte

| Konzept | Bedeutung |
| --- | --- |
| Provider | Technischer Dienst oder lokaler Server, z. B. `ollama`, `llamacpp` oder `openai`. |
| Modell | Ein konkretes Modell, das von einem Provider bereitgestellt wird. |
| Route | Stabiler Aufgabenname, der zu einem Modell, einer Fallback-Kette und einer Richtlinie aufgelöst wird. |
| Richtlinie (Policy) | Regel für Cloud-Zugriff, rein lokales Verhalten, Kontextbudget, Provider-Positiv-/Negativlisten und Kostengrenzen. |
| Kostenregel (Cost Rule) | Preisregel zur Schätzung der Anfragekosten aus Prompt- und Completion-Tokens. |
| Agent | Optionaler Adapter zu einem externen Tool wie Codex, Claude, Cursor oder einem Studio-Assistenten. |
| Kontext-Provider | Add-On, das neutrale Kontextpakete aus Projektquellen, Assets, Doku oder anderen Systemen bereitstellt. |

## Editor-Benutzeroberfläche

Öffnen Sie das Plugin über:

```text
Tiny Tools -> LLM Store
```

Hauptregisterkarten:

- `Setup`: **Quick-Start** mit einem Klick für den ersten Start (Mock / Ollama / Cloud), dann Erstellung von Providern und Modellen, Bearbeitung von Basis-URLs, Festlegung von Schlüsseln und Verbindungstest.
- `Routes`: Konfiguration von Aufgaben-Routen, Fallback-Ketten, Mock-Modellen, Prompt-Vorlagen und Richtlinien.
- `Agents`: Inspektion von Codex-, Claude-, Cursor- und benutzerdefinierten Agenten-Adaptern; Öffnen von Authentifizierungsdialogen.
- `Costs`: Analyse von Anfragen, Tokens, geschätzten Kosten, Cache-Treffern und Export von CSV-Berichten.
- `Governance`: Inspektion von Status, Audit-Ereignissen, Voreinstellungen (Presets), Cache-Zustand und Build-Richtlinien.
- `Status`: Lesen des aktuellen Einstellungsstatus, von Warnungen, Blockern und dem Inventar.
- `Help`: Editor-interne Erklärung von Konzepten und vorgesehenen Workflows.
- `Advanced`: Optionale Benutzeroberflächenbereiche, die von Add-Ons beigesteuert werden.

## Schnellstart

1. Öffnen Sie `Tiny Tools -> LLM Store`.
2. Verwenden Sie unter **Setup** die Karte **Quick-Start** (Mock, Lokales Ollama oder Cloud OpenAI/Anthropic), um mit einem Klick eine funktionierende `default`-Route zu erhalten.
3. Oder erstellen Sie manuell einen Provider und ein Modell und fügen Sie dann Routen auf der Registerkarte `Routes` hinzu.
4. Testen Sie Provider, Modell und Route; bestätigen Sie, dass das Bereitschaftsbanner grün wird.
5. Fügen Sie Kostenregeln hinzu, falls Cloud- oder Budgetanalysen wichtig sind.
6. Führen Sie eine Anfrage aus und prüfen Sie die Registerkarten `Costs` und `Status`.

Siehe [QUICKSTART.md](QUICKSTART.md) für schrittweise Details (Quick-Start-Karte und manuelle Einrichtung).

## Lokale Provider

Unterstützte lokale oder selbst gehostete Provider-Typen:

- `ollama`
- `llamacpp`
- `lmstudio`
- `vllm`
- `tgi`
- `mock`

Diese Provider benötigen standardmäßig keine API-Schlüssel.

## Cloud-Provider

Unterstützte Cloud-Provider-Typen:

- `openai`
- `anthropic`
- `gemini`
- `azure-openai`
- `mistral`
- `openrouter`

Cloud-Provider benötigen normalerweise API-Schlüssel. Schlüssel werden im konfigurierten Geheimnis-Backend gespeichert, niemals in `Config/LLMStore.json`.

## Blueprint und C++

Konsumentenseitige Funktionalität ist sowohl über C++ als auch über Blueprints verfügbar.

Blueprint-Basisklassen:

- `ULLMBlueprintProviderAddOn`
- `ULLMBlueprintEmbeddingProviderAddOn`
- `ULLMBlueprintContractAddOn`
- `ULLMBlueprintPolicyAddOn`
- `ULLMBlueprintTestAddOn`
- `ULLMBlueprintContextProviderAddOn`
- `ULLMBlueprintAgentAddOn`

Siehe [INTEGRATION.md](INTEGRATION.md) und [CodeDocumentation.md](CodeDocumentation.md).

Streaming- und Nicht-Streaming-Routenausführung teilen sich eine nebenläufigkeitsgesteuerte Warteschlange. Verwenden Sie `EnqueueRoute` für lange lokale Jobs; `ExecuteRouteStreaming` folgt demselben aktiven Anfrage-Schutz und gibt Stream-Chunks über seine Callback-API zurück.

## Agenten-Authentifizierung

Die Registerkarte `Agents` kann eine Schaltfläche `Authenticate...` für jeden Agenten anzeigen. Der Dialog zeigt den Anmeldebefehl, Anweisungen, den Hilfe-Link und Aktionen zum Ausführen oder Kopieren des Befehls. Die Zugangsdaten verbleiben beim externen Tool; LLM Store speichert nur Status und Anweisungen.

Siehe [AGENT_AUTHENTICATION.md](AGENT_AUTHENTICATION.md).

## Kostenverfolgung

LLM Store schätzt Kosten ab aus:

- Vom Provider gemeldeten oder vom Store geschätzten Prompt-Tokens
- Vom Provider gemeldeten oder vom Store geschätzten Completion-Tokens
- Passenden `FLLMCostRule`-Einträgen

Das Kostenbuch (Cost Ledger) wird gespeichert unter:

```text
Saved/LLMStore/CostLedger.json
```

CSV-Exporte verwenden standardmäßig:

```text
Saved/LLMStore/CostReports/LLMStoreCostReport.csv
```

Siehe [COST_TRACKING.md](COST_TRACKING.md).

## Datenschutz und Sicherheit

- API-Schlüssel gehören nicht in `Config/LLMStore.json`.
- Lokale Provider sind der bevorzugte Standard für sensible Projektdaten.
- Richtlinien können die Cloud-Nutzung pro Route einschränken.
- Build-Regeln können Cloud-Provider für Shipping-Builds blockieren.
- Die Agenten-Ausführung erfolgt explizit und wird durch Anfrage-Flags gesteuert.

Siehe [SECRET_BACKENDS.md](SECRET_BACKENDS.md) für verschlüsselte lokale Dateien, Windows Credential Manager, macOS Keychain, 1Password und Azure Key Vault.

## Starten Sie hier

- [BUYER_GUIDE.md](BUYER_GUIDE.md): Käuferfreundliche Übersicht, Wertversprechen und praktische Workflows.
- [QUICKSTART.md](QUICKSTART.md): Erste funktionierende Provider/Modell/Routen-Einrichtung.
- [UserManual.md](UserManual.md): Vollständiger Editor-Workflow und Benutzung der Benutzeroberfläche.
- [FAQ.md](FAQ.md): Fab-fertige Fragen und Antworten für Käufer.

## Referenz

- [SettingsReference.md](SettingsReference.md): Konfigurationsfelder, Standardwerte, Setup-JSON-Dateien und empfohlene Baselines.
- [ProviderReference.md](ProviderReference.md): Unterstützte lokale/Cloud-Providertypen, Basis-URLs und Hinweise.
- [RoutePolicyReference.md](RoutePolicyReference.md): Routenrichtlinien, Cloud/Lokal-Einschränkungen, Budgetregeln und Build-Richtlinien.
- [COST_TRACKING.md](COST_TRACKING.md): Kostenbuch, Kostenregeln, CSV-Export und Analyse-Workflow.
- [SECRET_BACKENDS.md](SECRET_BACKENDS.md): Verschlüsselter lokaler Speicher und Verhalten externer Geheimnis-Backends.
- [AGENT_AUTHENTICATION.md](AGENT_AUTHENTICATION.md): Codex/Claude/Cursor-artige Agenten-Adapter und Verhalten von Authentifizierungsdialogen.
- [INTEGRATION.md](INTEGRATION.md): C++- und Blueprint-Integrationsmuster für andere Plugins.
- [TROUBLESHOOTING.md](TROUBLESHOOTING.md): Häufige Probleme und Behebungen.
- [TechnicalOverview.md](TechnicalOverview.md): Architekturübersicht auf Entwicklerebene.

## Enthaltene Assets

- [Screenshots/](Screenshots): Dokumentations-Screenshots und visuelle Workflow-Diagramme.

## Visuelle Übersichten

- [Screenshots/01-workflow-overview.svg](Screenshots/01-workflow-overview.svg)
- [Screenshots/02-editor-tabs.svg](Screenshots/02-editor-tabs.svg)
- [Screenshots/03-agent-cost-governance.svg](Screenshots/03-agent-cost-governance.svg)

## Schneller Setup-JSON-Workflow

1. Öffnen Sie `Tiny Tools -> LLM Store`.
2. Konfigurieren Sie Provider, Modelle, Routen, Richtlinien und Kostenregeln.
3. Öffnen Sie `Governance`.
4. Verwenden Sie `Export Setup JSON`, um das aktuelle Setup in eine beliebige gewählte Datei zu schreiben.
5. Verwenden Sie `Validate JSON`, um eine Setup-Datei zu prüfen, ohne sie anzuwenden.
6. Verwenden Sie `Import JSON` erst, wenn die Validierung erfolgreich war.

Geheimnisse werden niemals in die Setup-JSON geschrieben. Verbinden Sie Provider-Schlüssel nach dem Importieren eines geteilten Setups über das Geheimnis-Backend oder Umgebungsvariablen neu.

## UCM-Jobsichtbarkeit

LLM Store veröffentlicht eine schreibgeschützte Editor-Jobhistorie über `llmstore.editor.jobs.list.v1` und `llmstore.editor.jobs.status.v1`, wenn Unreal Capability Mesh aktiviert ist. Unified MCP Server kann diese Routen über `jobs_list` / `jobs_status` aggregieren; LLM Store selbst bleibt autark und benötigt keine Kompilierzeit-Abhängigkeit zu UMCP.

## Commandlet

Führen Sie die CI-Richtlinienprüfungen über ein lokales Terminal oder einen Automatisierungs-Runner aus:

```powershell
<UnrealEditorCommand> "D:\PluginProjectGit\PluginProject.uproject" -run=LLMStoreCIPolicy -unattended -nop4 -nosplash -NoShaderCompile
```

`<UnrealEditorCommand>` ist das Befehlszeilen-UnrealEditor-Ziel für Ihre lokale Engine-Installation.

Das Commandlet prüft konfigurierte Provider, Modelle, Routen, Richtlinien und Build-Regeln. Es ist für das Release-Management gedacht, nicht für Live-Provider-Benchmarking.

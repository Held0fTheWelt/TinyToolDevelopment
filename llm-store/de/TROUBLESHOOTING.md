<!-- doc-provenance: AKDB:plugins/LLMStore/architecture.md; docs/architecture/plugins/LLMStore/product-facts.yml; reconciled 2026-06-20 -->
# Fehlerbehebung

Diese Anleitung listet häufige Einrichtung-, Laufzeit-, UI-, Richtlinien- und Build-Probleme von LLM Store auf.

## Der LLM Store-Menüeintrag fehlt

Prüfen Sie:

- Das Plugin ist aktiviert.
- Der Editor wurde nach der Aktivierung des Plugins neu gestartet.
- Das Modul `LLMStoreEditor` ist kompiliert.
- Sie führen den Unreal Editor aus, nicht einen gekochten (cooked) Runtime-Build.

Erwarteter Ort:

```text
Tiny Tools -> LLM Store
```

## Provider ist nicht erreichbar

Prüfen Sie:

- Der Provider ist aktiviert
- Die Basis-URL ist korrekt
- Der lokale Server läuft
- Firewall oder Proxy blockieren die Anfrage nicht
- Das Zeitlimit ist lang genug
- Der Provider-Typ passt zum Server

Häufige lokale Standardwerte:

| Provider | Standard |
| --- | --- |
| `ollama` | `http://127.0.0.1:11434` |
| `llamacpp` | `http://127.0.0.1:8080` |
| `lmstudio` | `http://127.0.0.1:1234/v1` |
| `vllm` | `http://127.0.0.1:8000/v1` |
| `tgi` | `http://127.0.0.1:8080/v1` |

Verwenden Sie zuerst `Test Provider`, dann `Test Model`, dann `Test Route`.

## Route wird nicht aufgelöst

Prüfen Sie:

- Route `TaskKind` ist exakt so geschrieben wie angefordert
- Route ist aktiviert
- Bevorzugtes Modell existiert
- Modell ist aktiviert
- Modell verweist auf einen existierenden Provider
- Provider ist aktiviert
- Cloud-Schlüssel existiert, falls erforderlich
- Routenrichtlinie erlaubt den Provider-Typ
- Build-/Laufzeitmodus lehnt die Route nicht ab

Wenn `bUseMock` aktiviert ist, prüfen Sie, ob `MockModelId` existiert.

## Fehlender API-Schlüssel

Schlüssel werden nicht in `Config/LLMStore.json` gespeichert.

Verwenden Sie eine der folgenden Optionen:

- Provider-Schlüsselfeld im Editor
- Übersteuerung per Umgebungsvariable
- Konfiguriertes Geheimnis-Backend

Format der Umgebungsvariablen:

```text
LLMSTORE_<PROVIDER_ID>_KEY
```

Beispiel:

```text
ProviderId: openai-main
Variable: LLMSTORE_OPENAI_MAIN_KEY
```

## Umgebungsvariable wird ignoriert

Prüfen Sie:

- Variablenname verwendet die normalisierte Provider-ID
- Editor-Prozess wurde nach dem Setzen neu gestartet
- Die Variable ist für den Prozess sichtbar, der Unreal startet
- Es gibt keine versteckten Leerzeichen im Wert

Unter Windows erfordern Umgebungsänderungen über Systemeinstellungen oft den Neustart des Launchers oder Terminals.

## Windows Credential Manager funktioniert nicht

Prüfen Sie:

- Ausführung unter Windows
- `Advapi32` ist vom Plugin-Build verlinkt
- Der Zielname der Anmeldeinformationen passt zum generierten Geheimnis-Namen des Providers
- Benutzerkonto hat Berechtigung
- Provider-ID hat sich nicht geändert

Im Zweifelsfall setzen Sie eine temporäre Umgebungsvariable, um den Rest des Provider-Setups zu bestätigen.

## macOS Keychain funktioniert nicht

Prüfen Sie:

- Der Befehl `security` ist verfügbar
- Der Schlüsselbund ist entsperrt
- Der Prozess hat die Berechtigung, das Element zu lesen
- Der generierte Geheimnis-Name passt zum erwarteten Wert

## 1Password-Backend funktioniert nicht

Prüfen Sie:

- `op` CLI ist installiert
- `op whoami` ist im selben Terminalkontext erfolgreich
- `Vault` ist gesetzt oder `SecretBackend.Meta` enthält eine vollständige `op://...`-Referenz
- Provider-spezifische Überschreibung zeigt auf das richtige Element und Feld

## Azure Key Vault-Backend funktioniert nicht

Prüfen Sie:

- `az` CLI ist installiert
- `az account show` ist erfolgreich
- `Vault` ist der korrekte Key Vault-Name
- Die aktuelle Identität verfügt über Lese-/Schreib-/Löschberechtigungen für Geheimnisse
- Provider-spezifische Überschreibung passt zum Geheimnis-Namen

## Cloud-Provider schlägt fehl, aber lokaler Provider funktioniert

Prüfen Sie:

- API-Schlüssel ist vorhanden
- Basis-URL passt zur Provider-Dokumentation
- Provider-Modellname ist korrekt
- Konto hat Zugriff auf das Modell
- Anfrage wird nicht durch Richtlinien der Organisation blockiert
- Routen-Kostenrichtlinie lehnt die Anfrage nicht ab

Prüfen Sie die Provider-Gesundheit und das neueste Audit-Ereignis.

## llama.cpp antwortet nicht

Prüfen Sie:

- `llama-server` läuft
- Host und Port passen zu `BaseUrl`
- Server stellt einen OpenAI-kompatiblen Endpunkt bereit
- Modell ist geladen
- Zeitlimit der Anfrage ist lang genug

Typischer Start:

```text
llama-server -m C:\Models\model.gguf --host 127.0.0.1 --port 8080
```

Provider:

```text
Type: llamacpp
BaseUrl: http://127.0.0.1:8080
```

## Ollama antwortet nicht

Prüfen Sie:

```text
ollama list
ollama serve
```

Stellen Sie sicher, dass das Modell in `FLLMModelConfig.Name` in Ollama existiert.

## Strukturiertes JSON ist ungültig

Prüfen Sie:

- Route verwendet ein Modell, das für strukturierte Ausgaben geeignet ist
- `bStructured` ist am Modell gesetzt, falls Ihr Workflow dies erfordert
- `FLLMStructuredOutputSpec.bRequireJson` ist nur dann wahr, wenn nötig
- Schema ist gültiges JSON
- Prompt bittet nicht um Prosa um das JSON herum

Einige lokale Modelle benötigen strengere Prompts, um gültiges JSON zu erzeugen.

## Werkzeugaufrufe (Tool Calls) fehlen

Prüfen Sie:

- Provider unterstützt Aufrufe von Werkzeugen
- `FLLMToolSpec.ParametersJsonSchema` ist gültig
- Modell unterstützt Werkzeuge
- Provider-Adapter mappt Werkzeugspezifikationen auf das Drahtformat des Providers

## Streaming gibt nur einen Chunk aus

Einige Provider unterstützen kein natives Streaming oder der aktuelle Adapter parst möglicherweise nur vollständige Antworten. Dies ist zulässig. Die Streaming-API gibt weiterhin einen finalen Chunk aus, sodass Aufrufer einen einzigen Codepfad verwenden können.

## Kosten sind null

Prüfen Sie:

- Kostenregeln existieren
- Provider-Typ passt zur Regel
- Modell-ID passt zur Regel oder die Modell-ID der Regel ist leer
- Provider meldet Nutzung oder Token-Schätzung ist aktiviert
- Anfrage wurde nicht vollständig von einem kostenlosen lokalen Modell bedient

## Kostenbericht sieht zu hoch aus

Prüfen Sie:

- Kosteneinheiten gelten pro 1000 Tokens
- Eingabe- und Ausgabewerte wurden nicht vertauscht
- Währung ist konsistent
- Modellspezifische Regel wird nicht durch eine breitere Regel dupliziert
- Nutzungsdaten des Providers sind nicht bereits in einer anderen Einheit

## Agent ist nicht installiert

Prüfen Sie:

- CLI oder IDE ist installiert
- Werkzeugbefehl befindet sich im `PATH`
- Unreal wurde aus einer Umgebung gestartet, die den Werkzeugbefehl sehen kann
- Adapter-Statusprüfung kennt den richtigen Befehlsnamen

Verwenden Sie den Dialog `Authenticate...` für Einrichtungsanweisungen.

## Agenten-Authentifizierung funktioniert nicht

Versuchen Sie:

1. Klicken Sie auf `Copy Command`.
2. Führen Sie den Befehl in einem normalen Terminal aus.
3. Schließen Sie die Anmeldung ab.
4. Starten Sie Unreal neu oder aktualisieren Sie den Agenten-Status.

LLM Store speichert die Zugangsdaten nicht. Es zeigt nur den externen Anmeldebefehl an und kopiert ihn.

## Agent verweigert Dateischreibzugriffe

Prüfen Sie `FLLMAgentRequest`:

```text
bAllowFileWrites
bAllowShellExecution
bRequireDiffPreview
```

Adapter sollten Schreibzugriffe oder Shell-Befehle ablehnen, wenn die Anfrage sie nicht erlaubt.

## Shipping-Richtlinie schlägt fehl

Prüfen Sie:

- `BuildRules` für `Shipping`
- Routenrichtlinien
- Nutzung von Cloud-Providern
- Verfügbarkeit lokaler oder Mock-Fallbacks
- Positivlisten von Providern

Führen Sie das Commandlet lokal aus:

```text
<UnrealEditorCommand> Project.uproject -run=LLMStoreCIPolicy -Config=Shipping -Unattended -NoSplash -NoSound
```

## Einstellungsstatus ist unklar

Öffnen Sie die Registerkarte `Status`. Sie fasst Provider, Modelle, Routen, Blocker, Warnungen, fehlende Schlüssel und das Inventar zusammen.

Wenn der Status veraltet aussieht:

- Klicken Sie auf Neuladen, falls verfügbar
- Schließen Sie die Registerkarte und öffnen Sie sie erneut
- Starten Sie den Editor neu
- Prüfen Sie, ob `Config/LLMStore.json` manuell bearbeitet wurde

## Build schlägt fehl, weil Live Coding aktiv ist

Unreal Live Coding kann einen vollständigen externen Build blockieren, während der Editor läuft. Schließen Sie den Editor oder deaktivieren Sie Live Coding vor einem vollständigen Befehlszeilen-Build.

Dies beeinträchtigt nicht die normale UI-Nutzung, kann jedoch CI-artige Builds oder UHT-Validierungen blockieren.

## Nützliche Referenzen

- Erste Einrichtung: [QUICKSTART.md](QUICKSTART.md)
- Provider-Details: [ProviderReference.md](ProviderReference.md)
- Routenrichtlinien: [RoutePolicyReference.md](RoutePolicyReference.md)
- Geheimnisse: [SECRET_BACKENDS.md](SECRET_BACKENDS.md)
- Kosten: [COST_TRACKING.md](COST_TRACKING.md)
- Integration: [INTEGRATION.md](INTEGRATION.md)
- CI: [CommandletAndCI.md](CommandletAndCI.md)

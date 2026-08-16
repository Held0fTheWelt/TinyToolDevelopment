<!-- doc-provenance: AKDB:plugins/LLMStore/architecture.md; docs/architecture/plugins/LLMStore/product-facts.yml; reconciled 2026-06-20 -->
# Einstellungsreferenz

Diese Referenz beschreibt die wichtigsten Konfigurationsdaten, die von LLM Store verwendet werden.

Projekt-Konfigurationspfad:

```text
Config/LLMStore.json
```

Geheimnisse werden nicht in dieser Datei gespeichert.

## Setup-JSON-Dateien

Die Governance-UI kann Setup-JSON-Dateien aus jedem ausgewählten Ordner exportieren, validieren und importieren.

Das exportierte Wrapper-Format enthält:

| Feld | Bedeutung |
| --- | --- |
| `Format` | `LLMStoreSetup`. |
| `FormatVersion` | Setup-JSON-Formatversion. |
| `SetupName` | Lesbarer Name des Setups. |
| `ExportedUtc` | UTC-Exportzeitstempel. |
| `Config` | Verschachteltes `FLLMStoreConfig`-Objekt. |

Der Import akzeptiert zur Kompatibilität auch ein rohes `FLLMStoreConfig`-JSON-Objekt.

## FLLMStoreConfig

| Feld | Typ | Bedeutung |
| --- | --- | --- |
| `Providers` | `TArray<FLLMProviderConfig>` | Bekannte Provider. |
| `Models` | `TArray<FLLMModelConfig>` | Von Providern bereitgestellte Modelle. |
| `Routes` | `TArray<FLLMTaskRoute>` | Chat/Tool/Rerank-Aufgabenrouten. |
| `EmbeddingRoutes` | `TArray<FLLMStoreEmbeddingRoute>` | Embedding-spezifische Routen. |
| `RoutePolicies` | `TArray<FLLMRoutePolicy>` | Globale oder aufgabenspezifische Richtlinien. |
| `PromptTemplates` | `TArray<FLLMPromptTemplate>` | Wiederverwendbare Prompt-Vorlagen. |
| `CostRules` | `TArray<FLLMCostRule>` | Preisregeln für die Kostenverfolgung. |
| `BuildRules` | `TArray<FLLMBuildConfigRule>` | Governance pro Build-Konfiguration. |
| `SecretBackend` | `FLLMSecretBackendConfig` | Aktives Geheimnis-Backend. |
| `Modes` | `FLLMRuntimeModes` | Laufzeitprofil-Bezeichnungen. |

## FLLMProviderConfig

| Feld | Bedeutung |
| --- | --- |
| `Id` | Stabile projektlokale Provider-Taste. |
| `DisplayName` | Lesbarer Name in UI/Berichten. |
| `Type` | Provider-Typ wie `openai`, `ollama` oder `llamacpp`. |
| `BaseUrl` | Server- oder API-Endpunkt. |
| `bEnabled` | Deaktiviert Provider, ohne ihn zu löschen. |
| `Meta` | Provider-spezifische Metadaten, z. B. Azure-Deployment-Namen. |
| `RetryCount` | Wiederholungen bei vorübergehenden Fehlern. |
| `TimeoutSeconds` | Provider-spezifisches Zeitlimit; `0` verwendet Standardwerte. |
| `CircuitBreakerFailureThreshold` | Fehleranzahl, bevor der Schutzschalter öffnet. |
| `CircuitBreakerCooldownSeconds` | Abkühlzeit vor erneutem Versuch nach Öffnen des Schalters. |

## FLLMModelConfig

| Feld | Bedeutung |
| --- | --- |
| `Id` | Stabile projektlokale Modell-Taste. |
| `Name` | Provider-seitiger Modellname. |
| `DisplayName` | Lesbarer Name in der Benutzeroberfläche. |
| `ProviderId` | Verweis auf `FLLMProviderConfig.Id`. |
| `Role` | Optionale Rolle wie `fast`, `reasoning`, `local` oder `embedding`. |
| `bStructured` | Vom Modell wird erwartet, dass es strukturierte JSON-Ausgaben gut verarbeitet. |
| `TimeoutSeconds` | Modell-spezifisches Zeitlimit. |
| `bEnabled` | Deaktiviert Modell, ohne es zu löschen. |

## FLLMTaskRoute

| Feld | Bedeutung |
| --- | --- |
| `TaskKind` | Stabiler Aufgabenname, z. B. `docs.summarize`. |
| `PreferredModelId` | Erstes von dieser Route versuchtes Modell. |
| `FallbackModelId` | Veralteter einzelner Fallback. |
| `FallbackModelIds` | Geordnete Fallback-Kette. |
| `MockModelId` | Modell, das für den Mock-Modus verwendet wird. |
| `bUseMock` | Erzwingt die Verwendung des Mocks. |
| `WorkflowScope` | Optionaler Bereich wie `Editor`, `CI` oder `Runtime`. |
| `PromptTemplateId` | Standardvorlage für diese Route. |
| `Policy` | Routen-spezifische Richtlinie. |
| `bEnabled` | Deaktiviert die Route. |

## FLLMRoutePolicy

| Feld | Bedeutung |
| --- | --- |
| `TaskKind` | Leer kann von Tooling als global verwendet werden; ansonsten aufgabenspezifisch. |
| `bAllowCloud` | Cloud-Provider-Typen dürfen verwendet werden. |
| `bLocalOnly` | Nur lokale oder Mock-Provider sind erlaubt. |
| `MaxContextTokens` | Maximales Kontextbudget; `0` deaktiviert das Limit. |
| `MaxEstimatedCost` | Maximale geschätzte Anfragekosten; `0` deaktiviert das Limit. |
| `AllowedProviderTypes` | Positivliste von Provider-Typen. |
| `DeniedProviderTypes` | Negativliste von Provider-Typen. |

## FLLMStoreEmbeddingRoute

| Feld | Bedeutung |
| --- | --- |
| `RouteId` | Stabile Embedding-Routen-ID. |
| `TaskKind` | Aufgabe, z. B. `docs.embed`. |
| `ProviderId` | Embedding-Provider. |
| `ModelId` | Embedding-Modell. |
| `Dimensions` | Erwartete Vektordimension; `0` bedeutet Provider-Standard. |
| `bEnabled` | Route ist aktiv. |
| `bLocalOnly` | Lokale Ausführung bevorzugen oder verlangen. |
| `bAllowFallback` | Fallback-Routen dürfen verwendet werden. |
| `FallbackRouteIds` | Embedding-Fallback-Routen. |
| `AllowedRuntimeModes` | Optionale Positivliste für Laufzeitprofile. |

## FLLMCostRule

| Feld | Bedeutung |
| --- | --- |
| `ProviderType` | Von der Regel abgedeckter Provider-Typ. |
| `ModelId` | Optionale Modell-ID; leer gilt breit gefächert. |
| `InputCostPer1KTokens` | Preis pro 1000 Prompt-Tokens. |
| `OutputCostPer1KTokens` | Preis pro 1000 Completion-Tokens. |
| `Currency` | Währungsbezeichnung, Standard `USD`. |

## FLLMSecretBackendConfig

| Feld | Bedeutung |
| --- | --- |
| `Backend` | `EncryptedFile`, `WindowsCredentialManager`, `MacOSKeychain`, `OnePassword` oder `AzureKeyVault`. |
| `Vault` | Backend-spezifischer Tresor-, Schlüsselbund- oder Namensraum-Name. |
| `KeyPrefix` | Präfix für generierte Geheimnis-Namen. |
| `Meta` | Backend-spezifische Provider-Überschreibungen. |

## FLLMBuildConfigRule

| Feld | Bedeutung |
| --- | --- |
| `BuildConfiguration` | Unreal-Konfiguration wie `Development`, `Test` oder `Shipping`. |
| `bAllowCloud` | Cloud-Provider sind in dieser Konfiguration erlaubt. |
| `bRequireLocalOrMock` | Jede Route muss einen lokalen oder Mock-Pfad haben. |
| `AllowedProviderTypes` | In dieser Konfiguration erlaubte Provider-Typen. |

## FLLMRuntimeModes

| Feld | Bedeutung |
| --- | --- |
| `GenerationMode` | Freie Bezeichnung wie `Local`, `Hybrid` oder `Cloud`. |
| `RetrievalMode` | Freie Bezeichnung für Retrieval/RAG-Verhalten. |
| `ValidationMode` | Freie Bezeichnung für Validierungs-/Prüfverhalten. |
| `RuntimeProfile` | Gesamtes Profil wie `LocalOnly`, `OpenAICloud` oder `Hybrid`. |

## FLLMPromptTemplate

| Feld | Bedeutung |
| --- | --- |
| `Id` | Vorlagen-Schlüssel. |
| `Description` | Beschreibung für UI und Teammitglieder. |
| `Template` | Prompt-Text mit Variablen. |
| `Variables` | Erwartete Variablennamen. |

## Empfehlungen für Teams

- Committen Sie `Config/LLMStore.json`.
- Committen Sie keine API-Schlüssel.
- Verwenden Sie `SecretBackend`, um Team-Erwartungen sichtbar zu machen.
- Verwenden Sie `BuildRules`, um Shipping-Fehler frühzeitig zu erkennen.
- Fügen Sie `CostRules` vor produktiver Cloud-Nutzung hinzu.
- Dokumentieren Sie jede Produktionsroute mit Eigentümer, Zweck und Datenklasse.

## Editor-Entwicklereinstellungen

Editor-spezifische Einstellungen befinden sich unter **Editor Settings -> Plugins -> LLM Store** und werden getrennt von `Config/LLMStore.json` gespeichert.

| Feld | Standardwert | Bedeutung |
| --- | --- | --- |
| `MaxJobHistoryCount` | `50` | Maximale Anzahl an Panel-/Job-Einträgen, die für die Editor-Historie und UCM-Job-Endpunkte aufbewahrt werden. |
| `DefaultPanelPage` | `Setup` | Beim Öffnen des LLM Store angezeigte Panel-Seite. |
| `bAutoOpenPanelOnStartup` | `false` | Öffnet das Panel automatisch, wenn das Editor-Modul startet. |
| `bRunValidationOnReload` | `false` | Führt die Validierungsbereitschaftsprüfung nach dem Neuladen der Konfiguration aus. |

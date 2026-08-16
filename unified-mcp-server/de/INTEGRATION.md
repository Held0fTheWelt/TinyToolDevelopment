# Integrationsleitfaden

Verwenden Sie diesen Leitfaden, wenn ein anderes Plugin Tools über den Unified MCP Server verfügbar machen soll.

## Abhängigkeit hinzufügen

Fügen Sie in der `.Build.cs`-Datei des Provider-Plugins folgende Abhängigkeit hinzu:

```csharp
PrivateDependencyModuleNames.AddRange(new string[]
{
    "UnifiedMcpServerInterface"
});
```

Verwenden Sie eine öffentliche Abhängigkeit nur, wenn Ihre öffentlichen Header UMCP-Typen exponieren.

## `IUmcpToolProvider` implementieren

```cpp
class FMyToolProvider : public IUmcpToolProvider
{
public:
    virtual FString GetProviderId() const override { return TEXT("myplugin"); }
    virtual FString GetProviderDisplayName() const override { return TEXT("My Plugin"); }
    virtual void GetToolDescriptors(TArray<FUmcpToolDescriptor>& OutTools) const override;
    virtual void InvokeTool(const FUmcpToolInvocation& Invocation, FUmcpToolResult& OutResult) override;
};
```

Provider-IDs dürfen keine Unterstriche enthalten. Tools werden wie folgt exponiert:

```text
myplugin_<descriptor.Name>
```

## Provider registrieren

Registrieren Sie den Provider während des Modulstarts:

```cpp
IModularFeatures::Get().RegisterModularFeature(
    IUmcpToolProvider::GetModularFeatureName(),
    Provider.Get());
```

Heben Sie die Registrierung während des Herunterfahrens auf:

```cpp
IModularFeatures::Get().UnregisterModularFeature(
    IUmcpToolProvider::GetModularFeatureName(),
    Provider.Get());
```

Speichern Sie den Provider in einem stabilen Objekt, z. B. `TUniquePtr<FMyToolProvider>`, das vom Modul besessen wird.

## Tool-Deskriptoren

Jeder Deskriptor enthält:

| Feld | Bedeutung |
| --- | --- |
| `Name` | Provider-lokaler Tool-Name. |
| `Description` | Benutzersichtbare Tool-Beschreibung für MCP-Clients. |
| `InputSchemaJson` | JSON-Schema-Objekt, serialisiert als String. |
| `OutputSchemaJson` | Optionales JSON-Schema-Objekt für `structuredContent`, serialisiert als String. |
| `AnnotationsJson` | Optionales MCP-Tool-Annotations-Objekt, serialisiert als String. |

Wenn `InputSchemaJson` leer ist, fällt der Server auf ein Objekt-Schema zurück. Wenn in den UMCP-Einstellungen „Tool-Argumente validieren“ aktiviert ist, führt das Registry eine leichte Validierung auf oberster Ebene durch, bevor der Provider aufgerufen wird: erforderliche Felder, unbekannte Felder bei `additionalProperties:false`, primitive JSON-Typen und Enum-Werte.

Die UMCP-Zugriffskontrolle wird angewendet, nachdem Deskriptoren gesammelt wurden und bevor die MCP-Exponierung oder der Aufruf erfolgt. Deaktivierte Provider-IDs, Zugriffsprofile, erlaubte/verbotene Tool-Muster und erlaubte/verbotene aus Annotationen abgeleitete Gruppen können Tools vor `tools/list` verbergen und `tool_access_denied` für direkte `tools/call`-Anfragen zurückgeben, ohne den Provider aufzurufen.

## JSON-Grenzwert-Adapter

`FUmcpJsonAdapter` (`UnifiedMcpServerInterface/Public/UmcpJsonAdapter.h`) ist der gemeinsame Hilfscode für typisierte JSON-Daten am Anbieter-Grenzwert. Lassen Sie die `IUmcpToolProvider`-Stringfelder unverändert; parsen Sie sie einmal an der Spitze von `InvokeTool` und serialisieren Sie die Ergebnisse zurück in Text.

| Hilfscode | Zweck |
| --- | --- |
| `ParseArgs(ArgumentsJson, Out, OutError)` | Parsen Sie `FUmcpToolInvocation::ArgumentsJson` einmal. Leere Eingabe wird zu `{}`. Ungültiges JSON setzt `OutError` mit `ErrorCode = invalid_arguments_json`. |
| `ParseObject(Json, OutObject)` | Tieferes Parsen, das von `ParseArgs` verwendet wird; leere Eingabe wird zu einem leeren Objekt. |
| `Ok(ResultJson)` | Erstellen Sie ein erfolgreiches `FUmcpToolResult` mit `Status = Ok`. |

Beispielmuster:

```cpp
void FMyToolProvider::InvokeTool(const FUmcpToolInvocation& Invocation, FUmcpToolResult& OutResult)
{
    TSharedPtr<FJsonObject> Args;
    if (!FUmcpJsonAdapter::ParseArgs(Invocation.ArgumentsJson, Args, OutResult))
    {
        return;
    }

    // Lesen Sie typisierte Felder aus Args, führen Sie die Tool-Logik aus, dann:
    OutResult = FUmcpJsonAdapter::Ok(ResultObjectJson);
}
```

Parsen Sie `ArgumentsJson` nicht tiefer im Aufrufstapel erneut. Ändern Sie nicht die Struktur von `FUmcpToolInvocation` oder `FUmcpToolResult`.

## Aufruf

`InvokeTool` empfängt:

| Feld | Bedeutung |
| --- | --- |
| `ToolName` | Anbieter-lokaler Tool-Name, ohne Anbieter-Präfix. |
| `ArgumentsJson` | JSON-Objekt der Argumente, serialisiert als Text. |

Geben Sie `FUmcpToolResult` zurück:

| Feld | Bedeutung |
| --- | --- |
| `Status` | `Ok` oder `Error`. |
| `ResultJson` | JSON-Wert, serialisiert als Text. |
| `ErrorCode` | Stabiler Anbieter-Fehlercode. |
| `ErrorMessage` | Menschenlesbare Fehlermeldung. |

Wenn `ResultJson` ein JSON-Objekt ist, gibt `tools/call` es sowohl als Textinhalt als auch als MCP `structuredContent` zurück. Anbieter sollten erfolgreiche Ergebnisse, wenn möglich, objektgestaltet halten, damit Clients über Felder statt über Prosa reasoning betreiben können.

## Capability-Mesh-Anbieter

`UnifiedMcpServerEditor` enthält einen weichen Anbieter für Unreal Capability Mesh. Es löst das Mesh-Gateway durch Reflexion auf und stellt `mesh_*`-Tools bereit, wenn das Gateway verfügbar ist. Bevorzugen Sie diesen Pfad für setup-deklarierte cross-plugin-Workflows. Abgeflachte `mesh_route_*`-Tools erhalten route-abgeleitete `inputSchema`, `outputSchema` und Annotationen vom UCM-Gateway. Der Anbieter stellt auch `mesh_configure_experimental_self_approval` bereit; dieses Tool ist explizit **EXPERIMENTELL**, erfordert eine Risikoanerkennung beim Aktivieren und ist nur für eigene-Risiko-Test-Workflows gedacht.

Im UMCP-Steuerfeld erscheinen generische Mesh-Host-Tools unter **Unreal Capability Mesh**. Abgeflachte Route-Tools sind nach dem besitzenden Plugin aus UCM-Fähigkeitsmetadaten (`provider_id`, `display_name`) gruppiert, was damit übereinstimmt, wie Routen in der Projektkonfiguration deklariert werden, anstatt jede Route unter dem Mesh-Host aufzulisten.

## Editor-Jobverlauf (UCM-Routen)

Fab-Tool-Plugins (IIS, LLMStore, SCD und ähnliche) dürfen **nicht** von `UnifiedMcpServerInterface` abhängen, um den Jobverlauf bereitzustellen. Jedes Plugin veröffentlicht eine schreibgeschützte Liste/Status der Editor-Jobs über statische `UFUNCTION`-JSON-Endpunkte, die in UCM-Manifests gebunden sind, z. B.:

| Routen-ID | Zweck |
| --- | --- |
| `iis.editor.jobs.list.v1` | Aktuelle IIS-Jobs (Panel-Cache + optionale Zusammenführung mit SQLite-Speicher) |
| `iis.editor.jobs.status.v1` | Einzelne IIS-Job-Suche |
| `scd.editor.jobs.list.v1` | Aktuelle SCD-Jobs |
| `llmstore.editor.jobs.list.v1` | Aktuelle LLMStore-Jobs |
| `umcp.editor.jobs.list.v1` | Aktuelle UMCP-Panel-Jobs |

Agents können diese direkt als flache `mesh_route_*`-Tools aufrufen, wenn UCM aktiviert ist.

UMCP stellt außerdem aggregierte **`jobs_list`**- und **`jobs_status`**-MCP-Tools bereit. Der Host `FUmcpJobsToolProvider` ruft das UCM-Gateway (`ExecuteRouteJson`) für die oben genannte feste Routentabelle auf, fusioniert die JSON-Ergebnisse und sendet dieselbe Drahtform (`source_provider_id`, Job-Felder). Dies hält Fab-Plugins autark und bewahrt gleichzeitig die beobachtbarkeit über Plugins hinweg bei einem einzelnen Aufruf, wenn Unreal Capability Mesh vorhanden ist.

Implementieren Sie `IUmcpJobStatusProvider` **nicht** in Tool-Plugins – diese Schnittstelle ist veraltet und wird nur zur Abwärtskompatibilität beibehalten.

## Beispiel für direkten Provider

Direkte Provider-Plugins können weiterhin `IUmcpToolProvider` für produktspezifische Tools implementieren. Halten Sie diese Provider eng gefasst und vermeiden Sie die Duplizierung von Verhalten, das bereits als UCM-Route vorhanden ist.

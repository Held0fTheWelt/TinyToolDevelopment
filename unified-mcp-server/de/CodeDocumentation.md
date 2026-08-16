# Code-Dokumentation

## Quellstruktur

```text
Source/UnifiedMcpServerInterface
Source/UnifiedMcpServerEditor
```

## Schnittstellenmodul

### `IUmcpToolProvider.h`

Definiert den Vertrag für das modulare Feature, den Anbieter-Plugins implementieren.

Wichtige Methoden:

| Methode | Zweck |
| --- | --- |
| `GetProviderId` | Stabiles Präfix, das in den exponierten Tool-Namen verwendet wird. |
| `GetProviderDisplayName` | Menschenlesbarer Anbietername. |
| `GetToolDescriptors` | Liefert anbieterlokale Tool-Metadaten und Schemata. |
| `InvokeTool` | Führt ein einzelnes anbieterlokales Tool aus. |
| `IsReady` | Optionales Bereitschaftssignal. |

### `UmcpToolTypes.h`

Definiert:

- `FUmcpToolDescriptor`
- `FUmcpToolInvocation`
- `FUmcpToolResult`
- `EUmcpToolStatus`

`FUmcpToolDescriptor` enthält den anbieterlokalen Namen, die Beschreibung, `InputSchemaJson`, optionales `OutputSchemaJson` und optionale MCP `AnnotationsJson`.

## Editor-Modul

### `UmcpServer`

Verwaltet die HTTP-Routen, die JSON-RPC-Methodenbehandlung, die gültigkeitsbereichsspezifische Bearer-Token-Validierung, die Handshake-Datei und das Anforderungsprotokoll.

### `UmcpProviderRegistry`

Sammlt alle registrierten `IUmcpToolProvider`-Modulfunktionen. Es erstellt die MCP-Tool-Liste, wendet die UMCP-Anbieter-/Tool-Zugriffsrichtlinie an, löst statisch den freigegebenen Tool-Zugriff vor der Ausführung auf und leitet Aufrufe nach freigegebenem Tool-Namen weiter.

### `UmcpServerManager`

Verwaltet die aktuelle Serverinstanz, den runtime Access Guard und das Access Journal. Stellt Start-, Stopp-, Neustart-, Token-Rotation, Status, jüngste Zugriffseinträge und runtime-Blockaktionen bereit.

### `UmcpAccessGuard`

In-Memory-Runtime-Blockierungsschicht. Blöcke können global oder auf eine Sitzungs-Token-ID beschränkt sein. Der Guard wird sowohl für die `tools/list`-Filterung als auch für `tools/call` vor der Anbieteraufrufprüfung überprüft. Das Stoppen des Servers löscht alle runtime-Blöcke.

### `UmcpAccessJournal` und `UmcpAccessRedaction`

`UmcpAccessJournal` hält einen begrenzten In-Memory-Ring für Editor-Diagnosen bereit und schreibt rotierte JSONL-Daten in `Saved/UnifiedMcpServer/logs/access_audit.jsonl`. `UmcpAccessRedaction` entfernt geheimnisartig wirkende Schlüssel, begrenzt rotierte Festplattenspeicherstrings und begrenzt bereinigte RAM-Argument-JSONs.

### `UnifiedMcpServerEditorModule`

Startet den Server, wenn die Einstellungen dies zulassen, registriert die Menüeinträge **Tiny Tools -> AI -> Universal MCP** und fährt den Server während des Modul-Entladens herunter.

### `SUmcpControlPanel`

Editor-Status- und Lebenszyklus-Panel, das über **Tiny Tools -> AI -> Universal MCP -> Control Panel öffnen** geöffnet wird.

| Bereich | Implementierungshinweise |
| --- | --- |
| Status | Live-Server-Snapshot von `FUmcpServerManager`. |
| Registerkarte „Zugriffsaktivität“ | Jüngste `tools/call`-Einträge von `FUmcpAccessJournal` sowie explizite Steuerelemente zum Blockieren, Aufheben der Blockierung, Aktualisieren und Löschen von Token-/Tool-Blöcken und runtime-Blöcken. |
| Verbundene Funktionen | Plugin-gruppierte Baumstruktur, die aus `FUmcpProviderRegistry` sowie Capability-Mesh-Gateway-JSON (`list_capabilities`, `list_routes`) erstellt wird. Zeigt freigegebene, blockierte, ausgeblendete und nicht verfügbare Funktionen an, einschließlich Hinweise zu Annotationen für schreibgeschützt/zerstörend/idempotent/offene Welt und abgeleitete Tool-Gruppen, wenn Anbieter diese veröffentlichen. |
| Erweitern/Einklappen | `ExpandedToolPlugins` und `ExpandedToolRows` speichern den UI-Status; nur betroffene Widgets werden aktualisiert. |
| Caching | Snapshot-Fingerabdruck, Mesh-JSON-Cache und parsierter Schema-Cache vermeiden redundante Gateway-Aufrufe und Schema-Parsing. |
| UCM-Routengruppierung | `ApplyMeshRouteMetadata` weist abgeflachten `mesh_route_*`-Reihen über die primäre Fähigkeit `provider_id` der Route dem jeweiligen Anbieter-Plugin zu. |

### `FCapabilityMeshUmcpToolProvider`

Soft Capability Mesh-Anbieter, der durch Reflexion aufgelöst wird. `GetProviderDisplayName()` gibt **Unreal Capability Mesh** für generische Mesh-Host-Tools zurück. Abgeflachte Routen-Tools erben Anbietermetadaten von UCM-Fähigkeiten während der Zusammenstellung der Control-Panel-Reihen.

### `UmcpSettings`

Definiert Editor-Einstellungen für Aktivieren/Deaktivieren, Portauswahl, optionale Tool-Argumentvalidierung, Zugriffsprofil, deaktivierte Anbieter-IDs, erlaubte/blockierte Tool-Namen und erlaubte/blockierte Tool-Gruppen.

### `UUmcpEditorBlueprintLibrary`

Optionale, nur für den Editor bestimmte Blueprint-Oberfläche für Lebenszyklus und Diagnosen. Sie stellt **keine** MCP-Tool-Registrierung oder -Aufrufbereitstellung bereit.

| Funktion | Zweck |
| --- | --- |
| `IsUnifiedMcpEnabledByConfig` | Liest die Projekteinstellung, ohne den Server zu starten. |
| `StartUnifiedMcpServer` / `StopUnifiedMcpServer` | Gleiches Verhalten wie die Menüeinträge **Tiny Tools -> AI -> Universal MCP**. |
| `RotateUnifiedMcpToken` | Rotiert gültigkeitsbereichsspezifische Bearer-Tokens, wenn der Server läuft. |
| `IsUnifiedMcpServerRunning` | True, wenn die Loopback-HTTP-Route aktiv ist. |
| `GetUnifiedMcpProviderCount` | Anzahl der angehängten `IUmcpToolProvider`-Modulfunktionen. |
| `GetUnifiedMcpRecentAccessEntries` | Gibt jüngste, geheimrotierte Zugriffsjournal-Einträge zurück. |
| `BlockUnifiedMcpTool` / `UnblockUnifiedMcpTool` | Wendet einen runtime-Guard-Block für ein Tool an oder hebt ihn auf. |
| `ClearUnifiedMcpRuntimeBlocks` | Löscht alle runtime-Guard-Blöcke. |
| `GetUnifiedMcpConfiguredPort` | Port aus den Editor-Einstellungen. |
| `GetUnifiedMcpHandshakeFilePath` | Absoluter Pfad zu `Saved/UnifiedMcpServer/agent/mcp_endpoint.json`. |
| `GetUnifiedMcpEndpointJson` | Liest den Handshake-JSON, wenn vorhanden. |
| `GetUnifiedMcpServerStatus` | Gibt `FUmcpServerBlueprintStatus` zurück. |

Produktregel: UMCP bleibt ein C++-Host plus `IUmcpToolProvider`. Blueprint dient ausschließlich dem Server-Lebenszyklus/Diagnosen, niemals der Tool-Implementierung oder Anbieterregistrierung.

## Anforderungsfluss

1. Der Client sendet ein JSON-RPC an `/mcp`.
2. Der Server extrahiert `Authorization: Bearer <token>`.
3. Der Server löst das Token in die Standardsitzung oder eine scoped Profil-Überschreibung auf.
4. Die JSON-RPC-Methode wird analysiert.
5. Die Tool-Liste/-Aufrufe werden über `FUmcpProviderRegistry` aufgelöst.
6. Die statische Provider-/Tool-Zugriffsrichtlinie wird angewendet, ohne den Provider aufzurufen. Versteckte Tools werden aus `tools/list` ausgelassen; blockierte Aufrufe geben `tool_access_denied` zurück.
7. Runtime Access Guard-Blöcke werden angewendet. Laufzeitblockierte Aufrufe geben `runtime_access_denied` zurück.
8. Wenn aktiviert, werden Argumente gegen das ausgewählte Deskriptor-`inputSchema` validiert.
9. Provider-JSON-Ergebnisse werden als Textinhalt und für JSON-Objekte als `structuredContent` zurückgegeben.
10. Anforderungsmetadaten werden an JSONL angehängt, und `tools/call`-Zugriffsdiagnosen werden über die Redaktionsschicht angehängt.
11. Die Antwort wird als JSON zurückgegeben.

## Fehlerbehandlung

- Fehlendes oder falsches Bearer-Token gibt HTTP 401 mit JSON-RPC-Fehler zurück.
- Ungültiges JSON gibt einen Parse-Fehler zurück.
- Unbekannte JSON-RPC-Methoden geben method-not-found zurück.
- Unbekannte Tool-Namen geben ein `tools/call`-Ergebnis mit `isError: true` zurück.
- Durch die Zugriffsrichtlinie blockierte Tools geben ein `tools/call`-Ergebnis mit `isError: true` und `tool_access_denied` zurück.
- Durch den Runtime Guard blockierte Tools geben ein `tools/call`-Ergebnis mit `isError: true` und `runtime_access_denied` zurück.

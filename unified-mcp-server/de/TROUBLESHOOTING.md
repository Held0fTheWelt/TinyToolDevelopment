<!-- doc-provenance: AKDB:plugins/UnifiedMcpServer/architecture.md; docs/architecture/plugins/UnifiedMcpServer/product-facts.yml; reconciled 2026-07-04 -->
# Fehlerbehebung

## Client erhält 401 Unauthorized

Prüfen Sie, ob der Client Folgendes sendet:

```text
Authorization: Bearer <token>
```

Lesen Sie das aktuelle Kompatibilitäts-Token oder das bereichsbezogene Token aus:

```text
Saved/UnifiedMcpServer/agent/mcp_endpoint.json
```

Falls Token rotiert wurden, aktualisieren Sie die Client-Konfiguration.

## Statusantwort würde Token offenlegen

Lebenszyklus- und Statusantworten melden nur Handshake-Vorhandensein, Pfad, Port und Token-Anzahl. Sie dürfen niemals rohe Handshake-JSON- oder Bearer-Token-Werte zurückgeben. Verwenden Sie die lokale Handshake-Datei für eine autorisierte Client-Konfiguration, anstatt Geheimnisse über Diagnosen zu kopieren.

## Handshake-Datei fehlt

Mögliche Ursachen:

- Server läuft nicht
- Server konnte den konfigurierten Port nicht binden
- Plugin ist deaktiviert
- Editor hat das Modul noch nicht gestartet

Starten Sie den Server über:

```text
Tiny Tools -> AI -> Universal MCP -> Start Unified MCP Server
```

## Port wird bereits verwendet

Ändern Sie den Port unter:

```text
Edit -> Editor Settings -> Plugins -> Unified MCP Server
```

Starten Sie den Server anschließend neu.

## `tools/list` gibt keine Werkzeuge zurück

Unified MCP Server ist nur der Host. Aktivieren Sie Unreal Capability Mesh für generische `mesh_*`-Werkzeuge, oder aktivieren Sie ein anderes Anbieter-Plugin. Prüfen Sie zudem, ob der Anbieter Bereitschaft meldet und sein Modular-Feature registriert hat.

Prüfen Sie die Zugriffskontrolle in den Editor-Einstellungen und im Kontrollfeld. Deaktivierte Anbieter-IDs, restriktive Zugriffsprofile, nicht-leere Positivlisten, blockierte Werkzeugmuster oder blockierte Werkzeuggruppen verbergen passende Werkzeuge bewusst vor `tools/list`.

Falls generische `mesh_*`-Werkzeuge erscheinen, aber keine `mesh_route_*`-Werkzeuge, führen Sie `mesh_reload_setup` aus oder klicken Sie im Capability-Mesh-Panel auf **Reload Setup**, und aktualisieren Sie anschließend den MCP-Client. Routenwerkzeuge werden aus den aktiven Routenmanifesten in `Config/UnrealCapabilityMesh` generiert.

Falls `mesh_configure_experimental_self_approval` erscheint, behandeln Sie es als **EXPERIMENTELLES** Testwerkzeug auf eigene Gefahr. Die Aktivierung erfordert `acknowledge_experimental_risk: true` und ändert das Freigabeverhalten von Capability Mesh für ausgewählte oder alle freigabepflichtigen Routen.

Falls die automatische Selbstfreigabe in der UCM-Routen-UI geändert wurde, der MCP-Client aber noch alte Routenbeschreibungen anzeigt, rufen Sie `tools/list` erneut auf oder verbinden/aktualisieren Sie den Client neu. UMCP lädt das UCM-Setup vor dem Auflisten der Routenwerkzeuge neu, und `mesh_list_routes` gibt den aktuellen Status `experimental_self_approval_*` direkt zurück.

## Connected Functions wirken im Kontrollfeld veraltet

Das Kontrollfeld speichert Werkzeugmetadaten für schnellere wiederholte Aufrufe im Zwischenspeicher. Nach Änderungen am UCM-Setup, dem Hinzufügen von Anbietern oder dem Neuladen von Routen klicken Sie im Kontrollfeld auf **Refresh**, um ein vollständiges Neu Laden der verbundenen Funktionen zu erzwingen. Start/Stopp und Ein-/Ausklappen nutzen den Zwischenspeicher wieder, wenn der zugrundeliegende Schnappschuss unverändert ist.

## Stdio-Client kann sich nicht direkt verbinden

Das Plugin stellt einen HTTP-Transport bereit. Clients, die ausschließlich Stdio unterstützen, benötigen eine vom Benutzer installierte Brücke wie `mcp-remote`.

## Werkzeugaufruf gibt unbekanntes Werkzeug zurück

Prüfen Sie den offengelegten Namen aus `tools/list`. Verwenden Sie den Namen mit Präfix:

```text
<providerId>_<toolName>
```

Rufen Sie anbieterspezifische lokale Namen nicht direkt auf.

## Werkzeugaufruf gibt `tool_access_denied` zurück

Der Werkzeugname existiert, aber die Zugriffskontrolle von UMCP hat ihn blockiert. Prüfen Sie `AccessProfile`, entfernen Sie die Anbieter-ID aus `DisabledProviderIds`, passen Sie `AllowedToolNames` oder `AllowedToolGroups` an, oder entfernen Sie den passenden Eintrag aus `BlockedToolNames` oder `BlockedToolGroups`.

## Build schlägt unter UE 5.6 mit C++-Standardfehlern fehl

Stellen Sie sicher, dass die UMCP-Module und abhängige Brückenmodule mit C++20 kompiliert werden. Engine-Header von UE 5.6 nutzen C++20-Syntax in den Kern-Headern.

## Ort des Anfragen-Protokolls

Anfragen-Metadaten werden geschrieben nach:

```text
Saved/UnifiedMcpServer/logs/mcp_requests.jsonl
```

Nutzen Sie diese Datei, um Methodennamen, Statuscodes, Latenz und Fehlercodes zu untersuchen.

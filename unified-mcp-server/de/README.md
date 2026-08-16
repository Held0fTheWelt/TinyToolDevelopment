<!-- doc-provenance: AKDB:plugins/UnifiedMcpServer/architecture.md; docs/architecture/plugins/UnifiedMcpServer/product-facts.yml; reconciled 2026-07-04 -->
# Unified MCP Server

Unified MCP Server ist ein Editor-Plugin für Unreal Engine, das einen zentralen lokalen Model Context Protocol (MCP)-Endpunkt für das gesamte Projekt bereitstellt. Andere Plugins binden Werkzeuge über eine kleine modulare Schnittstelle an, sodass der Server neue Funktionen bereitstellen kann, ohne direkt von diesen Plugins abzuhängen.

Das Plugin ist bewusst rein infrastrukturell ausgelegt. Es enthält keine externen Ausführungsdateien, kein Node-Paket und keine Python-Laufzeitumgebung. Es hostet einen Loopback-JSON-RPC 2.0-MCP-Endpunkt innerhalb des Editors und ermöglicht es Anbietern, Werkzeuge zur Laufzeit zu registrieren.

## Module

| Modul | Zweck |
| --- | --- |
| `UnifiedMcpServerInterface` | Öffentlicher `IUmcpToolProvider`-Vertrag sowie Typen für Werkzeugbeschreibungen und Ergebnisse. |
| `UnifiedMcpServerEditor` | Editor-Host für den Server, Einstellungen, Token-Handling, Anbieter-Registrierungsstelle, Status-Kontrollfeld und Menüeinträge unter Tiny Tools. |

## Hauptarbeitsablauf

1. Aktivieren Sie das Plugin im Projekt.
2. Öffnen Sie `Edit -> Editor Settings -> Plugins -> Unified MCP Server`.
3. Aktivieren Sie den lokalen Server und wählen Sie einen Port, oder behalten Sie den Standardport `8732` bei.
4. Verwenden Sie `Tiny Tools -> AI -> Universal MCP -> Open Control Panel` für Status, Lebenszyklus-Schaltflächen und den nach Plugins gruppierten Baum verbundener Funktionen.
5. Starten Sie den Server über das Kontrollfeld oder über `Tiny Tools -> AI -> Universal MCP -> Start Unified MCP Server`.
6. Lesen Sie die Verbindungsdaten aus `Saved/UnifiedMcpServer/agent/mcp_endpoint.json`.
7. Konfigurieren Sie einen MCP-Client so, dass er `http://127.0.0.1:8732/mcp` mit `Authorization: Bearer <token>` aufruft.

## Werkzeuganbieter (Tool Providers)

Anbieter-Plugins implementieren `IUmcpToolProvider` und registrieren dies als Unreal-Modular-Feature. Offengelegte Werkzeugnamen verwenden das Schema:

```text
<providerId>_<toolName>
```

Wenn Unreal Capability Mesh geladen ist, stellt der integrierte Mesh-Anbieter generische Werkzeuge wie `mesh_list_capabilities`, `mesh_list_routes`, `mesh_configure_experimental_self_approval`, `mesh_dry_run_route` und `mesh_execute_route` bereit. Er flacht zudem per Setup deklarierte UCM-Routen in direkte `mesh_route_*`-MCP-Werkzeuge ab. Diese Routenwerkzeuge veröffentlichen aus den Routen abgeleitete MCP-Typen `inputSchema`, `outputSchema` und Werkzeugannotationen, sodass Clients Parameter und Risikohinweise vor dem Aufruf prüfen können. `mesh_configure_experimental_self_approval` ist **EXPERIMENTELL** und erfolgt **auf eigene Gefahr**; die Aktivierung erfordert eine explizite Risikobestätigung. Ältere direkte Anbieterbrücken können weiterhin produktspezifische Werkzeugnamen registrieren, UCM-Routen bilden jedoch den bevorzugten Einrichtungspfad im Projekt.

`tools/call` gibt Anbieter-JSON als Textinhalt und, wenn das Ergebnis ein JSON-Objekt ist, als strukturierten MCP-Inhalt (`structuredContent`) zurück. `initialize` kündigt `tools.listChanged` an, und `tools/list` enthält einen Wert `_meta.toolsRevision`, sodass Clients zwischengespeicherte Werkzeugbeschreibungen nach Änderungen am UCM-Setup aktualisieren können.

UMCP 1.0.3 ergänzt die Zugriffskontrolle über den einzelnen Endpunkt. Anbieter-IDs können deaktiviert werden, und offengelegte Werkzeugnamen können über exakte Namen oder Platzhaltermuster erlaubt oder blockiert werden. UMCP 1.0.4 führt Profile ein (`Default`, `Read Only`, `Automation`, `Experimental`) sowie aus Annotationen abgeleitete Werkzeuggruppen. UMCP 1.0.5 ergänzt bereichsbezogene Sitzungs-Token, sodass verschiedene Clients die Zugriffe `default`, `read_only`, `automation` oder `experimental_admin` über denselben `/mcp`-Endpunkt nutzen können. UMCP 1.0.6 bietet Laufzeit-Access-Guard-Sperren und ein geheimnissicheres Access Journal für Diagnosen der letzten `tools/call`-Aufrufe. Dieselbe Richtlinie gilt sowohl für `tools/list` als auch für `tools/call`. Das Kontrollfeld zeigt an, ob verbundene Funktionen offengelegt, blockiert, verborgen oder nicht verfügbar sind.

## Sicherheit

- Der Server bindet ausschließlich an `127.0.0.1`.
- Der Server ist standardmäßig deaktiviert.
- Anfragen erfordern ein Bearer-Token aus der Handshake-Datei.
- Die Anbieter-/Werkzeug-Zugriffskontrolle kann Werkzeuge in `tools/list` verbergen und die direkte Ausführung über `tools/call` blockieren.
- Laufzeit-Access-Guard-Sperren existieren nur im Arbeitsspeicher und werden beim Stoppen des Servers gelöscht.
- Token können über **Tiny Tools -> AI -> Universal MCP** rotiert werden.
- Die Handshake-Datei wird entfernt, wenn der Server stoppt.
- Anfragemetadaten werden in `Saved/UnifiedMcpServer/logs/mcp_requests.jsonl` protokolliert.
- Zugriffsdiagnosen werden in `Saved/UnifiedMcpServer/logs/access_audit.jsonl` protokolliert, wobei wie Geheimnisse aussehende Argument-Schlüssel ausgelassen werden.

## Dokumentation

| Dokument | Zweck |
| --- | --- |
| [BUYER_GUIDE.md](BUYER_GUIDE.md) | Produktübersicht, Anwendungsfälle und Grenzen. |
| [QUICKSTART.md](QUICKSTART.md) | Erste Einrichtung und Client-Verbindung. |
| [UserManual.md](UserManual.md) | Tägliches Arbeiten im Editor. |
| [TechnicalOverview.md](TechnicalOverview.md) | Architektur und Protokollverhalten. |
| [INTEGRATION.md](INTEGRATION.md) | Wie Anbieter-Plugins Werkzeuge anbinden. |
| [SettingsReference.md](SettingsReference.md) | Einstellungen und gespeicherte Dateien. |
| [CodeDocumentation.md](CodeDocumentation.md) | Quellcode-Layout und Verträge. |
| [FAQ.md](FAQ.md) | Häufige Fragen von Käufern. |
| [TROUBLESHOOTING.md](TROUBLESHOOTING.md) | Häufige Fehler und Behebungen. |
| [ReleaseChecklist.md](ReleaseChecklist.md) | Checkliste für Veröffentlichungen und das Fab-Paketieren. |

## Paketierung

`Config/FilterPlugin.ini` schließt `/Documentation/...` und `/CHANGELOG.md` ein, damit Fab-Pakete diese Dokumentation enthalten.

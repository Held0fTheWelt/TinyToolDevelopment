<!-- doc-provenance: AKDB:plugins/UnifiedMcpServer/architecture.md; docs/architecture/plugins/UnifiedMcpServer/product-facts.yml; reconciled 2026-07-04 -->
# Schnellstart

## 1. Plugin aktivieren

Aktivieren Sie `Unified MCP Server` im Plugins-Browser und starten Sie den Editor neu, falls Unreal dies anfordert.

## 2. Server aktivieren

Öffnen Sie:

```text
Bearbeiten -> Editor-Einstellungen -> Plugins -> Unified MCP Server
```

Schalten Sie **MCP Server aktivieren** ein. Behalten Sie den Standardport `8732` bei, es sei denn, ein anderer lokaler Dienst verwendet ihn bereits.

## 3. Server starten

Verwenden Sie:

```text
Tiny Tools -> AI -> Universal MCP -> Unified MCP Server starten
```

Für Status, Lebenszyklus-Schaltflächen und den plugin-gruppieren verbundenen Funktionsbaum verwenden Sie:

```text
Tiny Tools -> AI -> Universal MCP -> Steuerpanel öffnen
```

Der Bereich „Verbundene Funktionen“ gruppiert Tools nach Plugin, unterstützt die verzögerte Schemaerweiterung und zwischenspeichert unveränderte Metadaten zwischen den Besuchen. Verwenden Sie **Aktualisieren**, nachdem Sie UCM-Einstellungen geändert haben, um einen vollständigen Neuladen zu erzwingen.

In UMCP 1.0.3 und später zeigt das Steuerpanel auch den Zugriffsstatus an. Deaktivieren Sie eine einzelne Anbietergruppe, um deren Tools vor `tools/list` zu verbergen und die direkte Ausführung von `tools/call` zu blockieren.

Wenn die Einstellung vor dem Start des Editors aktiviert ist, versucht der Server auch beim Laden des Editor-Moduls zu starten.

## 4. Handshake-Datei lesen

Nach dem Start schreibt der Editor:

```text
Saved/UnifiedMcpServer/agent/mcp_endpoint.json
```

Beispielstruktur:

```json
{
  "host": "127.0.0.1",
  "port": 8732,
  "token": "<default-token>",
  "tokens": {
    "default": {"token": "<default-token>", "scope": "default", "profile": "Project Settings"},
    "read_only": {"token": "<read-only-token>", "scope": "read_only", "profile": "Read Only"},
    "automation": {"token": "<automation-token>", "scope": "automation", "profile": "Automation"},
    "experimental_admin": {"token": "<experimental-token>", "scope": "experimental_admin", "profile": "Experimental"}
  }
}
```

Verwenden Sie das Kompatibilitätsfeld `token` oder wählen Sie ein Token aus `tokens` als:

```text
Authorization: Bearer <selected-token>
```

## 5. Client verbinden

HTTP-fähige MCP-Clients können aufrufen:

```text
http://127.0.0.1:8732/mcp
```

Wenn der Server läuft, öffnen Sie das Steuerpanel und klicken Sie auf **MCP-Client-Konfiguration kopieren**.
Dies kopiert einen einfügbaren `mcp.json`-Ausschnitt mit der aktuellen Endpunkt-URL und dem
aktuellen standardmäßigen Bearer-Token. Fügen Sie ihn in die Konfigurationsdatei Ihres MCP-Clients ein.
Nach **Token rotieren** kopieren Sie den Ausschnitt erneut, da sich das Bearer-Token geändert hat.

Bei `initialize` aushandelt UMCP `protocolVersion`: Wenn Ihr Client eine unterstützte Version anfordert (`2025-06-18`, `2025-03-26` oder `2024-11-05`), spiegelt der Server diese Version wider; andernfalls antwortet er mit `2024-11-05`. Ein Client-Test von `GET /mcp` gibt HTTP 405 zurück, da UMCP die Streamable-HTTP JSON-Antwort-Teilmenge verwendet und keinen Server-zu-Client-SSE-Stream hostet.

Nur-Stdio-Clients benötigen eine vom Benutzer installierte Bridge wie `mcp-remote`. Diese Bridge ist nicht mit diesem Plugin enthalten.

## 6. Tools hinzufügen (Optional)

Der Server läuft eigenständig; dieser Schritt fügt Tools hinzu, die Clients aufrufen können. Sie haben zwei unabhängige
Optionen, und Sie benötigen nur das, was zu Ihrem Projekt passt:

- **Ihr eigenes (oder jedes andere) Plugin:** Registrieren Sie ein `IUmcpToolProvider`-Modulfeature, und seine Tools
  erscheinen automatisch als `<providerId>_<toolName>`. Kein Katalog-Plugin ist erforderlich. Siehe
  [INTEGRATION.md](INTEGRATION.md).
- **Optional — Unreal Capability Mesh (UCM):** Wenn Sie auch Unreal Capability Mesh besitzen, fügt das Aktivieren von ihm
  setup-deklarierte `mesh_*`-Tools hinzu, sodass Aufrufer konfigurierte UCM-Routen (z. B. IIS
  Context-Pack, PRS-Platzierung, SCD-Migrationsberatung und DataAsset/DataTable-Verwaltung) über
  `mesh_execute_route` oder die generierten direkten `mesh_route_*`-Tools ausführen können. Es wird auch
  `mesh_configure_experimental_self_approval` freigegeben; dieses Tool ist **EXPERIMENTELL**, erfordert eine explizite
  Risikobestätigung beim Aktivieren und ist nur für eigene-Risiko-Test-Workflows gedacht.

Beide sind optional — der Server, der Handshake und die Client-Verbindung (Schritte 1–5) funktionieren ohne installierten Anbieter.

## 7. Stoppen oder Rotieren

Verwenden Sie das Tiny-Tools-Menü:

```text
Tiny Tools -> AI -> Universal MCP -> Unified MCP Server stoppen
Tiny Tools -> AI -> Universal MCP -> MCP-Token rotieren
```

Das Stoppen entfernt die Handshake-Datei. Das Rotieren schreibt sie mit frischen, bereichsbezogenen Tokens neu. Beide Aktionen sind auch über das Steuerpanel verfügbar.

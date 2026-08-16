<!-- doc-provenance: AKDB:plugins/UnifiedMcpServer/architecture.md; docs/architecture/plugins/UnifiedMcpServer/product-facts.yml; reconciled 2026-07-04 -->
# Benutzerhandbuch

## Öffnen der Einstellungen

Unified MCP Server wird unter folgender Adresse konfiguriert:

```text
Edit -> Editor Settings -> Plugins -> Unified MCP Server
```

Einstellungen:

| Einstellung | Standard | Bedeutung |
| --- | --- | --- |
| Enable MCP Server | aus | Erlaubt dem Editor-Modul das Ausführen des lokalen MCP-Servers. |
| Server Port | 8732 | Auf `127.0.0.1` verwendeter TCP-Port. |
| Validate Tool Arguments | aus | Validiert optional Argumente von `tools/call` gegen das `inputSchema` jedes Werkzeugs vor dem Anbieteraufruf. |
| Access Profile | Default | Übergeordneter Freigabemodus: Default, Read Only, Automation oder Experimental. |
| Disabled Provider IDs | leer | Verbirgt und blockiert jedes Werkzeug übereinstimmender Anbieter-IDs. |
| Allowed Tool Names | leer | Optionale Positivliste offengelegter Werkzeugnamen oder Platzhaltermuster. Leer bedeutet, dass alle Werkzeuge erlaubt sind, sofern sie nicht blockiert sind. |
| Blocked Tool Names | leer | Verbirgt und blockiert offengelegte Werkzeugnamen oder Platzhaltermuster. |
| Allowed Tool Groups | leer | Optionale Positivliste aus Annotationen abgeleiteter Gruppen wie `read_only`, `non_destructive` oder `idempotent`. |
| Blocked Tool Groups | leer | Verbirgt und blockiert aus Annotationen abgeleitete Gruppen wie `risky`, `destructive` oder `open_world`. |
| Enable Access Journal | ein | Schreibt geheimnissichere Zugriffsdiagnosen für `tools/call`. |
| Access Journal Ring Capacity | 500 | Im Arbeitsspeicher gehaltene Einträge für das Kontrollfeld und Blueprint-Diagnosen. |
| Access Journal Max File Bytes | 5242880 | Maximale Größe von `access_audit.jsonl` vor einer Datei-Rotation. |

## Menü Tiny Tools

Der Editor ergänzt Lebenszyklus- und Statusaktionen unter **Tiny Tools -> AI -> Universal MCP**:

| Aktion | Ergebnis |
| --- | --- |
| Open Control Panel | Öffnet das UMCP-Kontrollfeld mit Lebenszyklus-Schaltflächen und dem nach Plugins gruppierten Baum verbundener Funktionen. |
| Start Unified MCP Server | Startet den Loopback-HTTP-Endpunkt. |
| Stop Unified MCP Server | Stoppt den Endpunkt und entfernt die Handshake-Datei. |
| Rotate MCP Token | Generiert neue bereichsbezogene Bearer-Token und schreibt die Handshake-Datei neu. |

Der Bereich **AI** gruppiert Unified MCP Server mit anderen AI-Plugins aus Tiny Tool Development wie dem Internal Index Service.

## Kontrollfeld (Control Panel)

Das Kontrollfeld zeigt:

| Bereich | Details |
| --- | --- |
| Status | Status Laufend/Gestoppt, Start-Einstellung, Endpunkt-URL, Token-Vorhandensein/Anzahl, Anfragenzahl, Anbieteranzahl, Werkzeuganzahl und Pfad der Handshake-Datei. |
| Aktionen | Starten, Stoppen, Token rotieren, Agent-Ordner öffnen und Aktualisieren. |
| Tabs | Connected Functions für Anbieter/Werkzeuge/Schemas und Access Activity für letzte Werkzeugaufrufe und Laufzeit-Sperren. |
| Connected Functions | Aufklappbare Plugin-Gruppen mit Anbieter-Umschaltern, Werkzeugzeilen, Zugriffs-/Bereitschaftsstatus, MCP-Werkzeugnamen, Beschreibungen und verzögert geladenen Eingabe-/Ausgabe-Schematabellen. |
| Access Activity | Letzte Werkzeugaufrufe mit Details zu Token/Client/Ergebnis, Anzahl der Laufzeit-Sperren, Aktualisieren, Token/Werkzeug sperren/entsperren und Laufzeit-Sperren aufheben. |

### Layout von Connected Functions

Connected Functions verwendet einen hierarchischen Baum ähnlich dem Routenkatalog von Capability Mesh:

1. **Plugin-Gruppe** — eine Zeile pro Plugin mit Schnittstellenanzahl und, wenn die Gruppe einem einzelnen Anbieter entspricht, einer Schaltfläche zum Aktivieren/Deaktivieren des Zugriffs. Klicken Sie auf den Pfeil, um die Werkzeuge dieses Plugins ein- oder auszublenden.
2. **Werkzeugzeile** — eine Zeile pro angebundenem MCP-Werkzeug oder per Setup deklarierter UCM-Funktion. Klicken Sie auf den Pfeil, um Eingabe-/Ausgabe-Schematabellen für dieses Werkzeug ein- oder auszublenden.

Das Spaltenlayout hängt vom Einklappstatus **innerhalb jeder Plugin-Gruppe** ab:

| Status | Spalten |
| --- | --- |
| Alle Werkzeuge eingeklappt | `Provider`, `Ready`, `Tool`, `Description` (breit) |
| Beliebiges Werkzeug ausgeklappt | `Provider`, `Ready`, `Tool`, `Input`, `Output`, `Description` |
| **Anbietergruppierung:** Direkte Anbieterwerkzeuge erscheinen unter ihrem `GetProviderDisplayName()`. Abgeflachte UCM-Routenwerkzeuge (`mesh_route_*`) erscheinen unter dem **besitzenden Plugin** aus den Capability-Mesh-Metadaten (zum Beispiel Internal Index Service oder SmartContentDiet) und nicht unter dem Mesh-Host-Eintrag. Generische Mesh-Host-Werkzeuge wie `mesh_list_routes` und `mesh_reload_setup` verbleiben unter **Unreal Capability Mesh**.

**Performance:** Das Panel lädt Werkzeugmetadaten asynchron. Unveränderte Daten werden bei wiederholtem Öffnen, Start/Stopp und Ein-/Ausklappen aus dem Zwischenspeicher geladen. Verwenden Sie **Refresh**, um ein vollständiges Neu Laden nach Änderungen am UCM-Setup zu erzwingen.

Zeilen mit der Markierung `Needs approval` sind freigabepflichtige UCM-Funktionen. Ihr Tooltip verweist auf den **EXPERIMENTELLEN** automatischen Selbstfreigabepfad in UCM-Routen oder `mesh_configure_experimental_self_approval`; verwenden Sie diesen nur für Tests auf eigene Gefahr.

Zeilen mit der Markierung `Blocked` oder `Hidden` werden MCP-Clients nicht offengelegt. UMCP entfernt sie aus `tools/list` und gibt `tool_access_denied` zurück, falls ein Client den Werkzeugnamen dennoch direkt aufruft.

Laufzeit-Sperren aus dem Tab **Access Activity** sind temporäre Sperren der Editor-Sitzung. Sie schreiben nicht in die Editor-Einstellungen, verbergen das Werkzeug in `tools/list` für das betroffene Token, lehnen direkte Aufrufe mit `runtime_access_denied` ab und werden beim Stoppen des Servers gelöscht.

Werkzeugbeschreibungen enthalten MCP-Annotationen, sofern Anbieter diese veröffentlichen, beispielsweise nur lesendes, destruktives, idempotentes oder Open-World-Verhalten. Das Panel zeigt auch abgeleitete Gruppen, die von Profilen und Gruppenzugriffsrichtlinien verwendet werden.

## Verbindungsdateien

Handshake-Datei:

```text
Saved/UnifiedMcpServer/agent/mcp_endpoint.json
```

Anfragen-Protokoll:

```text
Saved/UnifiedMcpServer/logs/mcp_requests.jsonl
```

Access Journal:

```text
Saved/UnifiedMcpServer/logs/access_audit.jsonl
```

Die Handshake-Datei enthält den lokalen Host, den Port, das Kompatibilitäts-`token` und bereichsbezogene `tokens`. Behandeln Sie sie wie eine lokale Anmeldeinformation.

Das Access Journal lässt wie Geheimnisse aussehende Argument-Schlüssel wie token, secret, password, API-Key, authorization und bearer weg.

## Unterstützte MCP-Aufrufe

Der Server verarbeitet diese JSON-RPC-Methoden:

| Methode | Verhalten |
| --- | --- |
| `initialize` | Gibt Protokollversion, Werkzeugfunktionen und Serverinformationen zurück. |
| `notifications/initialized` | Bestätigt die Client-Initialisierung. |
| `ping` | Gibt ein leeres Ergebnis zurück. |
| `tools/list` | Gibt alle Werkzeuge registrierter Anbieter zurück, einschließlich `inputSchema`, optionalem `outputSchema`, optionalen `annotations` und `_meta.toolsRevision`. |
| `tools/call` | Leitet einen mit Präfix versehenen Anbieter-Werkzeugnamen an dessen Anbieter weiter und gibt JSON-Ergebnisse als Text sowie nach Möglichkeit als `structuredContent` zurück. |

Unbekannte Methoden geben einen JSON-RPC-Fehler "Method not found" zurück.

## Editor-Job-Werkzeuge

UMCP stellt lesende Job-Aggregationswerkzeuge bereit, wenn Unreal Capability Mesh verfügbar ist:

| Werkzeug | Zweck |
| --- | --- |
| `jobs_list` | Führt letzte Jobs aus festen UCM-Routen für IIS, SmartContentDiet, LLM Store und UMCP zusammen. Optionale Argumente `provider_id` und `max_count` schränken das Ergebnis ein. |
| `jobs_status` | Sucht eine Job-ID in derselben Routentabelle und gibt die zugehörige Quell-Anbieter-ID zurück. |

Die Quell-Plugins veröffentlichen ihre eigene Editor-Jobliste/ihren Status über UCM-Routen und hängen nicht von UMCP ab. Ist UCM oder eine Route nicht verfügbar, überspringt die Aggregation diese Route und gibt weiterhin Jobs von verfügbaren Anbietern zurück.

## Arbeiten mit Anbietern

Unified MCP Server enthält selbst keine Projektwerkzeuge. Anbieter fügen diese hinzu. Ein Anbieter liefert Beschreibungen, Eingabeschemas und Ausführungsloigk über `IUmcpToolProvider`.

Wenn ein Anbieter installiert ist, erscheinen Werkzeuge im Format:

```text
provider_tool
```

Zum Beispiel:

```text
mesh_route_iis_agent_search_v1_<hash>
```

Wenn Unreal Capability Mesh geladen ist, stellt UMCP generische Mesh-Werkzeuge bereit:

```text
mesh_reload_setup
mesh_list_capabilities
mesh_list_routes
mesh_configure_experimental_self_approval
mesh_dry_run_route
mesh_execute_route
mesh_invoke_endpoint
```

UMCP veröffentlicht zudem jede deklarierte Capability-Mesh-Route als abgeflachtes MCP-Werkzeug:

```text
mesh_route_<sanitized_route_id>_<hash>
```

Abgeflachte Routenwerkzeuge akzeptieren `mode: "execute"` oder `mode: "dry_run"`. Wird `input` oder `input_json` weggelassen, werden verbleibende Argumente als Routeneingabeobjekt behandelt. Für Routen, die intern ein serialisiertes `request_json` binden, spiegelt UMCP abgeflachte Argumente automatisch nach `request_json`. Jedes abgeflachte Routenwerkzeug veröffentlicht ein aus der Route abgeleitetes MCP-`inputSchema`, `outputSchema` und Annotationen wie `readOnlyHint`, `destructiveHint` und `openWorldHint`. Verändernde Routen durchlaufen weiterhin die Richtlinien- und Freigabeprüfungen von Capability Mesh.

Verwenden Sie `mesh_execute_route` für verändernde Operationen, damit Routenrichtlinien und Freigabeprüfungen von Capability Mesh aktiv bleiben.

`mesh_configure_experimental_self_approval` ist ausdrücklich **EXPERIMENTELL** und erfolgt **auf eigene Gefahr**. Es kann automatische Selbstfreigaben von Capability Mesh global oder für ausgewählte Routen-IDs lesen oder ändern. Die Aktivierung erfordert `acknowledge_experimental_risk: true`.

## Betriebshinweise

- Verwenden Sie einen eindeutigen Port pro Editor-Instanz.
- Rotieren Sie die Token nach dem Teilen von Protokollen oder Screenshots, die die Handshake-Datei zeigen könnten.
- Stoppen Sie den Server, wenn ein externer Agent keinen Zugriff mehr benötigt.
- Wenn keine Anbieter-Plugins aktiviert sind, kann `tools/list` berechtigterweise eine leere Liste zurückgeben.

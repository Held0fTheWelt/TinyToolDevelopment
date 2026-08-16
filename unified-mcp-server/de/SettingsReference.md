<!-- doc-provenance: AKDB:plugins/UnifiedMcpServer/architecture.md; docs/architecture/plugins/UnifiedMcpServer/product-facts.yml; reconciled 2026-07-04 -->
# Einstellungsreferenz

Die Einstellungen befinden sich in `UUmcpSettings` und werden in der Editor-Konfiguration gespeichert.

Öffnen Sie:

```text
Edit -> Editor Settings -> Plugins -> Unified MCP Server
```

## Server

| Einstellung | Konfigurationsfeld | Standard | Hinweise |
| --- | --- | --- | --- |
| Enable MCP Server | `bEnableServer` | `false` | Standardmäßig aus. Wenn wahr, versucht das Editor-Modul den Server beim Starten zu starten. |
| Server Port | `ServerPort` | `8732` | Lokaler TCP-Port für den Loopback-Endpunkt. Gültiger Bereich: 1-65535. |

## Werkzeuge (Tools)

| Einstellung | Konfigurationsfeld | Standard | Hinweise |
| --- | --- | --- | --- |
| Validate Tool Arguments | `bValidateToolArguments` | `false` | Wenn aktiviert, validiert UMCP eingehende Argumente von `tools/call` gegen das `inputSchema` jedes Werkzeugs vor dem Anbieteraufruf. Die Validierung ist leichtgewichtig: erforderliche Felder, unbekannte Felder bei `additionalProperties:false`, primitive Typen und Enums. |

## Zugriffskontrolle (Access Control)

| Einstellung | Konfigurationsfeld | Standard | Hinweise |
| --- | --- | --- | --- |
| Access Profile | `AccessProfile` | `Default` | Übergeordneter Freigabemodus. `Default` behält bisheriges Verhalten bei, `Read Only` legt nur als nur-lesend annotierte Werkzeuge offen, `Automation` verbirgt risikoreiche/destruktive/open-world/unklassifizierte Werkzeuge, und `Experimental` erlaubt risikoreiche Werkzeuge bewusst, sofern sie nicht manuell blockiert wurden. |
| Disabled Provider IDs | `DisabledProviderIds` | leer | Anbieter-IDs, die vor `tools/list` verborgen und zum Zeitpunkt von `tools/call` blockiert werden. Das Kontrollfeld kann Gruppen einzelner Anbieter in diese Liste schalten. |
| Allowed Tool Names | `AllowedToolNames` | leer | Optionale Positivliste offengelegter MCP-Werkzeugnamen oder Platzhaltermuster wie `iis_search` oder `mesh_route_*`. Leer bedeutet, dass alle Werkzeuge erlaubt sind, außer wenn deaktiviert oder blockiert. |
| Blocked Tool Names | `BlockedToolNames` | leer | Offengelegte MCP-Werkzeugnamen oder Platzhaltermuster, die vor `tools/list` verborgen und bei `tools/call` blockiert werden. |
| Allowed Tool Groups | `AllowedToolGroups` | leer | Optionale Positivliste aus Annotationen abgeleiteter Gruppen wie `read_only`, `non_destructive`, `idempotent`, `risky`, `destructive`, `open_world` oder `unclassified`. |
| Blocked Tool Groups | `BlockedToolGroups` | leer | Aus Annotationen abgeleitete Gruppen, die vor `tools/list` verborgen und bei `tools/call` blockiert werden. |

Die Reihenfolge der Richtlinienprüfung lautet: Anbieter deaktiviert, explizite Werkzeugsperre, Zugriffsprofil, blockierte Gruppe, optionale Werkzeug-/Gruppen-Positivlisten, dann offengelegt. Wenn eine Positivliste Einträge enthält, wird ein Werkzeug offengelegt, wenn sein Name oder mindestens eine Gruppe übereinstimmt. Dieselbe Richtlinie wird für `tools/list` und `tools/call` angewendet.

Über das Kontrollfeld oder Blueprint-Helfer erstellte Laufzeit-Access-Guard-Sperren gelten nur für die Sitzung und greifen nach der dauerhaften Richtlinie. Sie verbergen übereinstimmende Werkzeuge vor `tools/list`, lehnen direkte Aufrufe von `tools/call` ab und werden beim Stoppen des Servers gelöscht.

Job-Aggregationswerkzeuge sind nur lesend, durchlaufen jedoch dieselbe Anbieter-/Werkzeug-/Profil-Richtlinie wie jedes andere MCP-Werkzeug. Das Blockieren von `jobs_*` oder des Anbieters `jobs` verbirgt sowohl `jobs_list` als auch `jobs_status`.

## Access Journal

| Einstellung | Konfigurationsfeld | Standard | Hinweise |
| --- | --- | --- | --- |
| Enable Access Journal | `bEnableAccessJournal` | `true` | Schreibt semantische `tools/call`-Zugriffsdiagnosen. |
| Access Journal Ring Capacity | `AccessJournalRingCapacity` | `500` | Letzte Einträge im RAM für das Kontrollfeld und Blueprint-Diagnosen. |
| Access Journal Max File Bytes | `AccessJournalMaxFileBytes` | `5242880` | Maximale Größe von `access_audit.jsonl` vor einer Datei-Rotation. |
| Access Journal Redacted String Limit | `AccessJournalRedactedStringLimit` | `128` | Maximale String-Länge in geschwärzten JSONL-Argumenten. |
| Access Journal Max RAM Entry Bytes | `AccessJournalMaxRamEntryBytes` | `8192` | Maximale im Speicher behaltene bereinigte Argument-JSON pro Eintrag. Wie Geheimnisse aussehende Schlüssel werden ausgelassen. |

## Generierte Dateien

| Datei | Zweck |
| --- | --- |
| `Saved/UnifiedMcpServer/agent/mcp_endpoint.json` | Verbindungs-Handshake mit Host, Port, Kompatibilitäts-Token und bereichsbezogenen Sitzungs-Token. |
| `Saved/UnifiedMcpServer/logs/mcp_requests.jsonl` | Anfragen-Metadatenprotokoll. |
| `Saved/UnifiedMcpServer/logs/access_audit.jsonl` | Geheimnissicheres semantisches Access Journal für `tools/call`. |

## Sicherheitsstandards

- Server standardmäßig deaktiviert.
- Nur Loopback-Host.
- Bearer-Token erforderlich.
- Token können über **Tiny Tools -> AI -> Universal MCP** rotiert werden.
- Die Handshake-Datei wird gelöscht, wenn der Server stoppt.
- UMCP 1.0.5 schreibt die Sitzungs-Token `default`, `read_only`, `automation` und `experimental_admin`. Das legacy `token`-Feld bleibt aus Kompatibilitätsgründen als Standard-Token erhalten.
- UMCP 1.0.6 lässt wie Geheimnisse aussehende Argument-Schlüssel aus Zugriffsdiagnosen aus, darunter token, secret, password, API-Key, authorization und bearer.

## Portauswahl

Verwenden Sie einen anderen Port, wenn:

- eine andere Editor-Instanz bereits `8732` nutzt
- ein lokaler Dienst an denselben Port gebunden ist
- separate Projekte separate MCP-Endpunkte benötigen

Die Client-URL lautet:

```text
http://127.0.0.1:<ServerPort>/mcp
```

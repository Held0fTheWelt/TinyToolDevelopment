<!-- doc-provenance: AKDB:plugins/UnifiedMcpServer/architecture.md; docs/architecture/plugins/UnifiedMcpServer/product-facts.yml; reconciled 2026-07-04 -->
# FAQ

## Enthält dieses Plugin ein KI-Modell?

Nein. Der Unified MCP Server ist eine Verbindungsinfrastruktur. Er stellt Tools von Provider-Plugins für lokale MCP-Clients bereit.

## Enthält es eine eigenständige ausführbare Datei?

Nein. Der Server läuft innerhalb der Unreal-Editor und liefert keine externe ausführbare Datei aus.

## Enthält es Node.js, Python oder mcp-remote?

Nein. Stdio-only-Clients benötigen möglicherweise eine vom Benutzer installierte Bridge wie `mcp-remote`, diese ist jedoch nicht gebündelt.

## Ist der Server standardmäßig aktiviert?

Nein. Er ist standardmäßig deaktiviert und muss in den Editor-Einstellungen aktiviert oder manuell über **Tiny Tools -> AI -> Universal MCP** gestartet werden.

## Hört der Server auf das Netzwerk?

Nein. Er bindet an `127.0.0.1`.

## Wie werden Anfragen authentifiziert?

Der Server generiert beim Start umgrenzte Bearer-Tokens. Clients lesen diese aus `Saved/UnifiedMcpServer/agent/mcp_endpoint.json` und senden ein Token im `Authorization`-Header.

## Unterstützt es mehrere umgrenzte Tokens?

Ja. UMCP 1.0.5 schreibt `default`, `read_only`, `automation` und `experimental_admin` Sitzungs-Tokens in die Handshake-Datei. Alle Tokens verwenden denselben lokalen `/mcp`-Endpunkt; die Umgrenzung bestimmt, welches Zugriffsprofil für `tools/list` und `tools/call` erzwungen wird.

## Warum ist meine Tool-Liste leer?

Der Basis-Server ist Infrastruktur. Aktivieren Sie Unreal Capability Mesh, um den generischen `mesh_*`-Provider zu erhalten, oder aktivieren Sie ein anderes Plugin, das einen `IUmcpToolProvider` registriert. Überprüfen Sie auch die UMCP-Zugriffskontrolle: Deaktivierte Provider, restriktive Profile, aktive Allowlists, blockierte Tool-Muster oder blockierte Tool-Gruppen können Tools absichtlich vor `tools/list` verbergen.

## Kann ich bestimmte Provider und Tools ausblenden oder blockieren?

Ja. UMCP verwaltet einen lokalen Endpunkt und wendet die Zugriffskontrolle an, bevor Tools MCP-Clients erreichen. Deaktivieren Sie Provider-IDs, wählen Sie ein Zugriffsprofil, fügen Sie genaue oder Wildcard-Tool-Namen oder -Gruppen zu Allow-/Block-Listen hinzu oder verwenden Sie den Provider-Toggle im Control Panel für einzelne Provider-Gruppen. Dieselbe Richtlinie wird für sowohl `tools/list` als auch `tools/call` durchgesetzt.

## Kann ich ein Tool während einer Sitzung temporär blockieren?

Ja. UMCP 1.0.6 fügt Laufzeit-Zugriffsschutz-Blöcke aus dem Control Panel und Blueprint-Diagnosen hinzu. Laufzeit-Blöcke können ein Tool für ein umgrenztes Token oder global ausblenden, direkte Aufrufe mit `runtime_access_denied` ablehnen und werden gelöscht, wenn der Server stoppt.

## Speichert das Access Journal Geheimnisse?

Es ist für geheimnis-sichere Diagnosen konzipiert. Geheimnis-ähnliche Argument-Schlüssel wie Token, Secret, Passwort, API-Schlüssel, Autorisierung und Bearer-Felder werden aus dem im Speicher befindlichen und JSONL-Access-Journal ausgelassen. Redigierte Strings und bereinigte RAM-Einträge werden durch Einstellungen begrenzt.

## Was ist `mesh_configure_experimental_self_approval`?

Es ist ein Capability Mesh-Provider-Tool für **EXPERIMENTAL** selbstständige automatische Genehmigung. Es kann ändern, ob genehmigungs-gesteuerte UCM-Routen global oder nach Routen-ID selbst genehmigen. Das Aktivieren erfordert `acknowledge_experimental_risk: true` und ist nur für eigene Risiko-Test-Workflows gedacht.

## Können mehrere Plugins Tools hinzufügen?

Ja. Jedes Plugin kann einen `IUmcpToolProvider` registrieren. Tool-Namen werden durch die Provider-ID präfixiert.

## Können Clients Tool-Parameter und Risiko sehen?

Ja. `tools/list` enthält jedes Tool `inputSchema`, optionales `outputSchema` und optionale Tool-Annotationen. UCM-Routen-Tools leiten diese aus Routen-Bindungen, Schema-Manifesten, Richtlinien und Seiteneffekten ab.

## Wie untersuche ich angehängte Tools im Editor?

Öffnen Sie **Tiny Tools -> AI -> Universal MCP -> Open Control Panel**. Der Bereich „Connected Functions“ gruppiert Tools nach Plugin, unterstützt verzögertes Ein-/Ausgabe-Schema-Expansion und zwischenspeichert unveränderte Metadaten zwischen Besuchen. Klicken Sie nach Änderungen an der UCM-Einrichtung auf **Refresh**, um einen vollständigen Neuladen zu erzwingen.

## Warum hat UMCP meine Tool-Argumente abgelehnt, bevor der Provider ausgeführt wurde?

Die Einstellung `Validate Tool Arguments` ist aktiviert. UMCP prüft dann eingehende Argumente gegen das ausgewählte Tool `inputSchema` und gibt `invalid_tool_arguments` zurück für fehlende erforderliche Felder, unbekannte Felder, wo nicht erlaubt, Typinkonsistenzen oder Enum-Inkonsistenzen.

## Welche Unreal Engine-Versionen werden angesprochen?

Das Plugin wurde für Unreal Engine 5.x Code-Plugins entwickelt und verwendet C++20 für aktuelle UE 5.6-Kompatibilität.

## Ist dies für verpackte Spiele gedacht?

Nein. Der aktuelle Server ist Editor-Infrastruktur für lokale Tools und Agenten.

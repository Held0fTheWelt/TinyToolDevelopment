# Käuferleitfaden

Der Unified MCP Server ist für Unreal-Projekte gedacht, die einen lokalen MCP-Endpunkt anstelle eines separaten Servers pro Feature-Plugin wünschen.

## Was es tut

- Bietet einen Loopback-MCP-Endpunkt innerhalb des Unreal-Editors an.
- Verwendet JSON-RPC 2.0 über HTTP unter `/mcp`.
- Erfordert für jede Anfrage eine Bearer-Token-Authentifizierung.
- Ermöglicht anderen Plugins, Tools über `IUmcpToolProvider` zu registrieren.
- Namespace-basierte Benennung von Tools als `<providerId>_<tool>`.
- Wendet Provider-/Tool-Zugriffskontrollen auf denselben Endpunkt an.
- Stellt scoped Session-Tokens für Standard-, Nur-Lese-, Automatisierungs- und Experimental/Admin-Clients bereit.
- Schreibt eine Handshake-Datei für die lokale Agentenkonfiguration.
- Wird ohne gebündelte Drittanbieter-Exekutivdateien ausgeliefert.
- Bietet ein Editor-Steuerfeld mit einem plugin-gruppierten Baum „Connected Functions“ zur Inspektion angehängter MCP-Tools, Schemata und Zugriffsstatus.

## Was es nicht tut

- Es enthält kein KI-Modell oder LLM-Anbieter.
- Es bindet `mcp-remote`, Node.js, Python oder eine eigenständige Server-Binärdatei nicht ein.
- Es stellt keine Projekttools allein bereit; Provider-Plugins oder Unreal Capability Mesh liefern die Tools.
- Es ist Editor-Infrastruktur, kein Gameplay-Laufzeit-Netzwerk.

## Typische Anwendungsfälle

- Lokale KI-Agenten mit Unreal-Editor-Tools über einen einzigen Endpunkt verbinden.
- Mehreren Plugins ermöglichen, einen MCP-Server mit richtlinienbasierten Auth-Tokens zu teilen.
- Tool-Provider hinzufügen oder entfernen, ohne das Server-Plugin zu ändern.
- Ausgewählte Provider/Tools ausblenden oder blockieren, ohne Clients auf mehrere Ports aufzuteilen.
- Agent-seitige Tools lokal auf der Entwicklermaschine halten.

## Empfohlene Begleit-Plugins

Das empfohlene Begleit-Plugin ist Unreal Capability Mesh. Es stellt einrichtungsdeklarierte Routen über generische `mesh_*` MCP-Tools bereit, sodass Projekte DataAssets/DataTables verwalten und konfigurierte IIS-, PRS-, SCD-, UII- und LLM-Store-Workflows ausführen können, ohne optionale no-UCM Freebie Bridges zu aktivieren. Sein Tool `mesh_configure_experimental_self_approval` ist explizit **EXPERIMENTAL** und nur für eigene Risiko-Test-Workflows gedacht.

## Technische Zusammenfassung für Fab

Editor-only Loopback-MCP-Host. Bietet ein Runtime-Interface-Modul für Provider-Verträge und ein Editor-Modul, das MCP-kompatible JSON-RPC über HTTP auf `127.0.0.1` bereitstellt. Tools werden von anderen Plugins als Unreal-modulare Features registriert, nach Provider-/Tool-Zugriffsrichtlinie gefiltert und über präfixierte Namen exponiert. Die Authentifizierung verwendet generierte scoped Bearer-Tokens, die in einer projektlokalen Handshake-Datei unter `Saved/UnifiedMcpServer/agent` geschrieben werden.

<!-- doc-provenance: SAD architecture.md sections 6,8,10,11; facts product-facts.yml; reconciled 2026-07-16 -->
# Fehlerbehebung

## Build schlägt auf UE 5.6 mit Engine-Header-Fehlern fehl

Stellen Sie sicher, dass IIS-Module mit C++20 kompilieren. UE 5.6-Engine-Header verwenden C++20-Syntax. Die IIS `.Build.cs`-Dateien sollten Folgendes enthalten:

```csharp
CppStandard = CppStandardVersion.Cpp20;
```

## Suche liefert keine Ergebnisse

Prüfen Sie:

- Ob vorbereitete Chunks importiert wurden
- Ob der Katalog neu aufgebaut wurde
- Ob der Abfragetext nicht leer ist
- Ob der Lebenszyklusstatus aktiv ist
- Ob das Index-Stammverzeichnis auf den erwarteten Projektordner zeigt

## Vektorsuche liefert keine Ergebnisse

Prüfen Sie:

- Ob Embedding-Jobs erstellt wurden
- Ob Embedding-Jobs erfolgreich ausgeführt wurden
- Ob die LLM Store Route/Executor registriert ist
- Ob die Vector Backend-Einstellung zu den gespeicherten Artefakten passt

## Import schlägt fehl

Überprüfen Sie, ob die vorbereitete Chunks-JSONL-Datei vorhanden und lesbar ist. Prüfen Sie die Importberichte im IIS-Saved-Ordner auf Validierungswarnungen und abgewiesene Datensätze.

## HNSW-Index kann nicht geladen werden oder erzeugt Backend-Warnungen

Wenn das HNSW-Backend nicht geladen werden kann oder nach einer Änderung der Vektorspeichereinstellungen Backend-Warnungen erscheinen, wechseln Sie vorübergehend zu `jsonl_bruteforce`, um Vektordatenprobleme von Backend-spezifischen Indizierungsproblemen zu trennen. Lassen Sie **Rebuild On Vector Format Mismatch** aktiviert, damit inkompatible persistierte HNSW-Partitionen aus den Quellvektoren neu aufgebaut werden, anstatt mit dem falschen Byte-Layout gelesen zu werden.

Bestätigen Sie, dass `Source/ThirdParty/hnswlib` im Paket enthalten ist, und bauen Sie Vektorartefakte nach Änderungen an **Vector Storage Format** neu auf.

## Runtime-Feinabstimmung oder Index-Aktionsbefehl gibt "Disabled" zurück

Überprüfen Sie **Enable Runtime Control Mutations** in den Projekteinstellungen. Wenn dies deaktiviert ist, funktionieren Lesebefehle wie `iis.control.state` weiterhin, aber tune-, act-, persist- und reset-Befehle geben konstruktionsbedingt eine Deaktiviert-Antwort zurück.

Aktivieren Sie die Einstellung wieder für verändernde Steuerungsbefehle oder fahren Sie mit schreibgeschützten Status- und Diagnosebefehlen fort.

## Agenten-Werkzeuge fehlen im MCP-Client

Prüfen Sie:

- Ob Unified MCP Server aktiviert ist und läuft
- Ob Unreal Capability Mesh aktiviert ist
- Ob das Projekt-Setup IIS-Agentenrouten-Manifeste (`iis.agent.*.v1`) enthält
- Rufen Sie `mesh_list_routes` oder `mesh_reload_setup` auf und aktualisieren Sie den MCP-Client
- Ob IIS Agenten-Werkzeugverträge schreiben kann
- Ob der MCP-Client mit dem UMCP-Endpunkt verbunden ist und nicht mit einem veralteten MCP-Server pro Plugin

Aktualisieren Sie das Capability Mesh-Setup und verbinden Sie den MCP-Client neu oder aktualisieren Sie ihn nach Routenänderungen.

## Agenten-Werkzeug gibt Schutzhinweis für reine Lesezugriffe zurück

Das wird erwartet. IIS-Antworten geben bewusst an, dass Projektänderungen nicht erlaubt sind.

## Perf-Selbstprüfung meldet eine Abweichung

Überprüfen Sie das neueste Ergebnis aus `iis.perf.last` oder führen Sie `iis.perf.run` erneut aus. Abweichungen bedeuten gewöhnlich, dass die aktuelle Vektor-Workload, das Backend oder die Abstimmung die konfigurierten Budgets überschreiten.

Verringern Sie zuerst die Abfragebreite oder die Vektor-Workload. Aktualisieren Sie Budgets erst nach repräsentativer Validierung auf der Zielmaschine/dem Zielprojektprofil.

## Wo nach Berichten gesucht werden muss

Standard:

```text
Saved/InternalIndexService/reports
Saved/InternalIndexService/imports
Saved/InternalIndexService/agent_contracts
```

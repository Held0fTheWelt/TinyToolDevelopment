<!-- doc-provenance: SAD architecture.md sections 2,8,10; facts product-facts.yml; reconciled 2026-07-16 -->
# Einstellungsreferenz

IIS-Einstellungen werden in `UIISSettings` gespeichert.

Öffnen:

```text
Edit -> Project Settings -> Plugins -> Internal Index Service
```

## Felder

| Einstellung | Standardwert | Bedeutung |
| --- | --- | --- |
| Vector Backend | `jsonl_bruteforce` | Wählt das lokale Vektorsuch-Backend aus. Unterstützte Werte sind `jsonl_bruteforce` und `hnsw`. Bei `jsonl_bruteforce` wechselt IIS oberhalb des Brute-Force-Datensatzlimits automatisch zu HNSW. |
| Index Root | leer | Optionale Überschreibung für generierte IIS-Daten. Leer verwendet `Saved/InternalIndexService`. |
| Brute Force Max Records | `10000` | Bis zu dieser Datensatzanzahl wird eine exakte Brute-Force-Suche verwendet; darüber HNSW. |
| Embedding Executor Id | leer | Bevorzugte IIS-Embedding-Executor-ID. Leer verwendet die normale Erkennung; die optionale IIS LLM Store Bridge setzt dies beim Laden auf `llmstore`. |
| Vector Storage Format | `Int8 Per-Vector Scale` | HNSW-Vektorspeicherrichtlinie. `Int8 Per-Vector Scale` ist die unterstützte kompakte Standardeinstellung; `Float32` ist nützlich für High-Fidelity-/Debug-Läufe; `Experimental Global Scale` ist gegatete und nur für Messungen gedacht. |
| Allow Experimental Vector Formats | `false` | Aktiviert experimentelle HNSW-Speicherformate. Wenn deaktiviert, fallen experimentelle Auswahlen auf `Int8 Per-Vector Scale` zurück. |
| Rebuild On Vector Format Mismatch | `true` | Löscht inkompatible persistierte HNSW-Partitionen, damit sie aus den Quellvektoren neu aufgebaut werden können, anstatt mit dem falschen Byte-Layout gelesen zu werden. |
| Quantization Recall Gate | `0.7` | Mindest-Recall-Ziel für automatisierte Tests quantisierter Vektorspeicher. Erhöhen Sie diesen Wert erst nach Validierung mit repräsentativen Projekt-Embeddings. |
| HNSW M | `16` | HNSW-Graphenkonnektivität. Höhere Werte verbessern den Recall auf Kosten von Speicher und Erstellungszeit. Gilt für neu erstellte Indizes. |
| HNSW efConstruction | `200` | Kandidatenlistengröße beim Erstellen. Höhere Werte verbessern Graphenqualität und Recall auf Kosten der Erstellungszeit. Gilt für neu erstellte Indizes. |
| HNSW efSearch | `64` | Kandidatenlistengröße bei Abfragen. Höhere Werte verbessern den Recall auf Kosten der Abfragelatenz. Wird beim Laden und Neuerstellen angewendet. |
| Enable Runtime Control Mutations | `true` | Hauptschalter für die Runtime-Steuerungsoberfläche. Wenn ausgeschaltet, werden Konsolen- und API-Befehle für tune/act/persist abgelehnt; Lesezugriffe funktionieren weiterhin. |
| Retain Recent Diagnostics | `false` | Wenn aktiviert, hält IIS einen begrenzten In-Memory-Ringspeicher der jüngsten Abfrage-Diagnosen für `diagnostics.recent` / Konsolenprüfung bereit. |
| Recent Diagnostics Max Count | `64` | Maximale Anzahl gespeicherter Diagnosen, wenn Retain Recent Diagnostics aktiviert ist. |
| Estimate Recall By Default | `false` | Wenn aktiviert, schätzen Suchen recall@K, sofern die Abfrage dies nicht explizit abwählt. Ergänzt einen exakten Referenzscan (SYN-1). |

> HNSW-Indizes werden standardmäßig mit int8-Skalarquantisierung gespeichert (Skalierung pro Vektor), was den Recall hoch hält und gleichzeitig den Speicherbedarf für Index und Festplatte reduziert. Float32 ist als High-Fidelity-/Debug-Richtlinie verfügbar. Experimentelles globales int8 ist bewusst gegatete, da es bei normalisierten hochdimensionalen Embeddings die meisten int8-Stufen verschwenden kann. Indizes, die mit einer anderen Speicherrichtlinie erstellt wurden, werden erkannt und standardmäßig automatisch neu aufgebaut.

## Generierte Pfade

Standard-Stammverzeichnis:

```text
Saved/InternalIndexService
```

Wichtige generierte Bereiche:

| Pfad | Zweck |
| --- | --- |
| `chunks.jsonl` | Speicher für importierte Chunks. |
| `imports/` | Import-Manifeste und Berichte. |
| `reports/` | Katalog-, Embedding- und Diagnoseberichte. |
| `agent_contracts/` | Agentenwerkzeug-Verträge und MCP-Manifeste für Bridges. |
| `vectors/` oder Backend-spezifische Dateien | Persistierte Embedding-/Vektordaten. |

Exakte Dateinamen können je nach Workflow und Backend variieren.

## MCP-Einstellungen

MCP-Server-Einstellungen befinden sich nicht in IIS. Konfigurieren Sie diese unter:

```text
Edit -> Editor Settings -> Plugins -> Unified MCP Server
```

Der IIS-Agentenzugriff wird über Capability Mesh-Routen des Projekts wie `iis.agent.search.v1` veröffentlicht.

## Geheimnis-Handhabung (Secrets)

IIS speichert keine Provider-Geheimnisse. Zugangsdaten für Embedding-Provider gehören in LLM Store oder die Provider-Umgebung.

## Empfohlene Standardwerte

| Szenario | Vector Backend | Vector Storage Format | Experimental Formats | Index Root |
| --- | --- | --- | --- | --- |
| Ersteinrichtung | `jsonl_bruteforce` | `Int8 Per-Vector Scale` | deaktiviert | leer |
| Größerer lokaler Index | `hnsw` | `Int8 Per-Vector Scale` | deaktiviert | leer oder projektlokaler benutzerdefinierter Pfad |
| High-Fidelity-Debugging | `hnsw` | `Float32` | deaktiviert | temporärer Workspace-Pfad |
| Recall-Experiment | `hnsw` | `Experimental Global Scale` | aktiviert | temporärer Workspace-Pfad |
| Gemeinsame CI-Validierung | `jsonl_bruteforce` | `Int8 Per-Vector Scale` | deaktiviert | temporärer Workspace-Pfad |

<!-- doc-provenance: SAD architecture.md sections 1,3,6,7,8; facts product-facts.yml; reconciled 2026-07-16 -->
# Schnellstart

## 1. Plugin aktivieren

Aktivieren Sie `Internal Index Service` im Plugins-Browser. Starten Sie den Editor neu, falls Unreal darum bittet.

## 2. Steuerfenster öffnen

Verwenden Sie:

```text
Tiny Tools -> AI -> Internal Index Service -> Open Internal Index Service
```

Das Steuerfenster öffnet sich auf dem Dashboard.

## 3. Einstellungen konfigurieren

Öffnen Sie:

```text
Edit -> Project Settings -> Plugins -> Internal Index Service
```

Empfohlene Ersteinrichtung:

| Einstellung | Wert |
| --- | --- |
| Vector Backend | `jsonl_bruteforce` |
| Vector Storage Format | `Int8 Per-Vector Scale` |
| Allow Experimental Vector Formats | `false` |
| Index Root | leer |

Ein leeres `Index Root` bedeutet, dass IIS Folgendes verwendet:

```text
Saved/InternalIndexService
```

Die Standard-Speicherrichtlinie verwendet eine int8-Skalierung pro Vektor für HNSW-Partitionen. Dies ist der normale kompakte Modus. `Float32` steht für High-Fidelity-/Debug-Läufe zur Verfügung; `Experimental Global Scale` sollte deaktiviert bleiben, außer Sie messen bewusst Genauigkeits-Abwägungen.

## 4. Vorbereitete Chunks importieren

Verwenden Sie die Registerkarte "Imports" im Steuerfenster oder rufen Sie die Service-API mit einer vorbereiteten Chunks-JSONL-Datei auf. Vorbereitete Chunks stammen normalerweise aus einer begleitenden Extraktions-Pipeline wie Unreal Integration Intelligence.

Der Import schreibt Berichte im IIS-Saved-Ordner und aktualisiert den Chunk-Speicher.

## 5. Katalog erstellen

Verwenden Sie die Aktion **Rebuild** auf dem Dashboard oder die Registerkarte "Catalog". IIS liest importierte Chunks, normalisiert den Lebenszyklusstatus und schreibt einen Katalog-Erstellungsbericht.

## 6. Suchen

Verwenden Sie die Registerkarte "Search":

- Die lexikalische Suche funktioniert über den lokalen Katalog
- Die Vektorsuche erfordert Embeddings
- Die Hybridsuche kombiniert beides, wenn Vektoren vorhanden sind

## 7. Embeddings erstellen (Optional – ergänzt Vektorsuche, erfordert LLM Store)

Die lexikalische Suche (Schritte 1–6) funktioniert eigenständig ohne ein weiteres Plugin. Vektor- und Hybridsuche sind eine optionale Erweiterung: Konfigurieren Sie zuerst das **LLM Store**-Plugin, danach fragt IIS die Embedding-Executor-Registrierung nach einer Route ab, erstellt Jobs und schreibt Embedding-Berichte. Führen Sie Jobs von der Registerkarte "Embeddings" aus. Ohne LLM Store importiert, baut und sucht IIS weiterhin lexikalisch.

## 8. Agenten-Werkzeuge bereitstellen (Optional – erfordert Unified MCP Server + Capability Mesh)

Dieser Schritt ist optional und wird nur benötigt, wenn KI-Agenten IIS aufrufen sollen. Installieren und aktivieren Sie:

- Unified MCP Server
- Unreal Capability Mesh

Stellen Sie sicher, dass das Capability Mesh-Profil des Projekts die IIS-Agentenrouten enthält (zum Beispiel `iis.agent.search.v1`). Starten Sie dann Unified MCP Server. Jede IIS-Agentenfunktion wird als eigene autonome UCM-Route bereitgestellt und zu einem `mesh_route_*` MCP-Tool verflacht, wie zum Beispiel:

```text
mesh_route_iis_agent_search_v1_<hash>
mesh_route_iis_agent_get_context_pack_v1_<hash>
mesh_route_iis_agent_get_chunk_v1_<hash>
mesh_route_iis_agent_get_source_references_v1_<hash>
mesh_route_iis_agent_find_usages_v1_<hash>
mesh_route_iis_agent_explain_blueprint_v1_<hash>
```

Alternativ rufen Sie `mesh_execute_route` auf, wobei `route_id` auf die Routen-ID gesetzt ist (zum Beispiel `iis.agent.search.v1`).

## 9. Runtime-Feinabstimmung (Optional – keine zusätzlichen Plugins erforderlich)

Die mitgelieferte Runtime-Steuerungsoberfläche ist **autark**: Kein UCM oder UMCP erforderlich.

Öffnen Sie die Editor-Ausgabeprotokollkonsole und führen Sie aus:

```text
iis.control.state
```

Beispiel für eine Antwort (Standard `efSearch` ist 64):

```json
{"ok":true,"errorCode":"","errorMessage":"","efSearch":64,...}
```

Erhöhen Sie `efSearch` für Abfragen live:

```text
iis.control.tune {"efSearch":128}
```

Bestätigen Sie die Änderung:

```text
iis.control.state
```

Beispiel nach der Feinabstimmung:

```json
{"ok":true,"errorCode":"","errorMessage":"","efSearch":128,...}
```

Überschreibungen sind **flüchtig** (transient), bis Sie `iis.control.persist` ausführen. Verwenden Sie `iis.control.reset`, um die Konfiguration neu zu laden. Siehe `UserManual.md` für die vollständige Konsolenbefehlsliste und Blueprint-API.

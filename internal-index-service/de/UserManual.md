<!-- doc-provenance: SAD architecture.md sections 1,5,6,8; facts product-facts.yml; reconciled 2026-07-16 -->
# Benutzerhandbuch

## Haupt-Workflow

IIS folgt einem schreibgeschützten Retrieval-Workflow:

1. Vorbereitete Evidenz importieren.
2. Lokalen Katalog erstellen oder aktualisieren.
3. Embeddings erstellen, wenn Vektorsuche benötigt wird.
4. Suchen oder Kontextpakete erstellen.
5. Die gleichen schreibgeschützten Werkzeuge für Agenten über UMCP bereitstellen.

IIS wendet keine Projektänderungen (Mutations) an.

## Produkt-Funktionsübersicht

| Funktion laut Datenblatt | Benutzeroberfläche für Käufer |
| --- | --- |
| `ImportPreparedChunks` | Importiert vorbereitete Chunk-JSONL über die Registerkarte "Imports" im Steuerfenster oder die Service-API. |
| `Search` | Führt lexikalisches, Vektor- oder Hybrid-Retrieval über die Registerkarte "Search" und die Service-API aus. |
| `BuildContextPack` | Erstellt evidenzbasierte Kontextpakete aus einer Abfrage oder ausgewählten Ergebnissen. |
| `RunPerfSelfCheck` | Führt die mitgelieferte synthetische Performance-Selbstprüfung über Blueprint/API und Konsolenoberflächen aus. |
| `RuntimeControlDispatch` | Steuert die Befehle observe, tune, act, persist und reset über die Runtime-Steuerungsoberfläche. |
| `AgentRetrievalTools` | Bietet schreibgeschützte Agenten-Retrieval-Operationen über lokale Verträge und optionale UCM/UMCP-Routen. |

## Steuerfenster

Öffnen:

```text
Tiny Tools -> AI -> Internal Index Service -> Open Internal Index Service
```

Registerkarten:

| Registerkarte | Nutzung |
| --- | --- |
| Dashboard | Index-Status, Integrations-Status, Tastenkürzel für Katalogneuerstellung und Suche. |
| Index | Importe, Katalogaufbau, Erstellung/Ausführung von Embedding-Jobs. |
| Use | Suche in lokaler Evidenz. |
| Agents | Agentenverträge und UMCP-Bridge-Status. |
| Governance | Status für reine Lesezugriffe, lokale Pfade, Sichtbarkeit von Bridges und Werkzeugen. |
| Diagnostics | Berichte, Übersicht und Speicherorte generierter Artefakte. |
| Settings | Anzeige von `UIISSettings` im Panel. |

## Import-Verhalten

Der Import verarbeitet vorbereitete Chunk-JSONL-Dateien. Jeder Chunk enthält IDs, Inhalt, Quellreferenzen, Asset-/Symbol-Metadaten und Lebenszyklusstatus. IIS validiert die Eingabe, fügt akzeptierte Chunks an und schreibt Importberichte.

Wichtige Dateien:

```text
Saved/InternalIndexService/chunks.jsonl
Saved/InternalIndexService/imports/
Saved/InternalIndexService/reports/
```

## Katalogaufbau

Der Katalogaufbau liest gespeicherte Chunks und erzeugt durchsuchbare lokale Strukturen. Er filtert inaktive Chunk-Lebenszykluszustände und schreibt einen Bericht, damit Benutzer Warnungen überprüfen können.

## Suche

Suchabfragefelder umfassen Abfragetext, Suchmodus, maximale Ergebnisse, Filter und Optionen für Kontextpakete. Ergebnisse enthalten Chunk-IDs, Score-Informationen, Ausschnitte (Snippets) und Quellreferenzen.

Suchmodi:

| Modus | Bedeutung |
| --- | --- |
| Lexical | Verwendet lokales Text-Matching über den Chunk-Katalog. |
| Vector | Verwendet persistierte Embeddings und das konfigurierte Vektor-Backend. |
| Hybrid | Kombiniert lexikalische und Vektor-Kandidaten. |

## Runtime-Steuerungsoberfläche

IIS bietet eine **autarke** Runtime-Steuerungsoberfläche für observe → tune → act ohne Neustart des Editors. Sie verändert das aktive `UIISSettings`-Objekt im Arbeitsspeicher (standardmäßig flüchtig) und wendet gecachte Stellschrauben wie HNSW `efSearch` sowie den aktiven int8-Kernel sofort an.

**Keine UCM- oder UMCP-Abhängigkeit** – die Oberfläche funktioniert eigenständig in Blueprint, C++ und der Editor-Konsole.

### Typisierte Blueprint-API (`UIISSubsystem`)

| Methode | Zweck |
| --- | --- |
| `GetControlState` | Momentaufnahme der wirksamen Stellschrauben und des Mutations-Gate-Status. |
| `SetTuning` | Anwenden optionaler feldweiser Abstimmungsänderungen (`FIISTuningRequest`). |
| `PersistTuning` | Aktuelle Überschreibungen in die Konfiguration schreiben (`SaveConfig`). |
| `ResetTuning` | Konfiguration neu laden und flüchtige Überschreibungen zurücksetzen. |
| `RunPerfSelfCheck` | SYN-2-Performance-Workloads gegen konfigurierte Budgets ausführen. |

### Konsolenbefehle

| Befehl | Zweck |
| --- | --- |
| `iis.control.state` | Wirksamen Steuerungsstatus als JSON ausgeben. |
| `iis.control.tune {json}` | Flüchtige Abstimmung (z. B. `{"efSearch":128}`). |
| `iis.control.persist` | Überschreibungen in Konfiguration speichern. |
| `iis.control.reset` | Konfiguration neu laden / Überschreibungen zurücksetzen. |
| `iis.control.diagnostics.recent` | Jüngste Abfrage-Diagnosen (wenn Speicherung aktiviert ist). |
| `iis.perf.run` / `iis.perf.last` | Performance-Selbstprüfung ausführen oder letzte Abfrage lesen. |
| `iis.index.sync` / `iis.index.rebuild` / `iis.index.import` | Aktionsbefehle zur Indexwartung. |

Verändernde Befehle berücksichtigen **Enable Runtime Control Mutations** in den Projekteinstellungen (standardmäßig aktiviert).

## Embeddings

IIS verwaltet keine Provider-Anmeldedaten. Die Ermittlung und Ausführung von Embedding-Routen wird über `FIISEmbeddingDiscovery` (`IIISEmbeddingRouteExecutor` via `IModularFeatures`) delegiert, was normalerweise von einer LLM Store Bridge bereitgestellt wird, die sich in `StartupModule` registriert und in `ShutdownModule` abmeldet.

Der Embedding-Ablauf:

1. Erstellen von Jobs für Chunks, die Vektoren benötigen.
2. Ermitteln einer Embedding-Route.
3. Ausführen der Jobs über den registrierten Executor.
4. Speichern der Vektordatensätze.
5. Aktualisieren der Berichte.

## Agenten-Werkzeuge

Agenten-Werkzeuge sind schreibgeschützt und liefern strukturiertes JSON zurück. IIS definiert sechs autonome Retrieval-Operationen. Lokale Vertragsnamen bleiben für den Aufruf in der Engine und über JSON-Dateien verfügbar:

| Lokaler Vertrag | UCM-Routen-ID | Zweck |
| --- | --- | --- |
| `iis_search` | `iis.agent.search.v1` | Indizierte Chunks durchsuchen (inline JSON-Payload plus Artefaktpfad). |
| `iis_get_context_pack` | `iis.agent.get_context_pack.v1` | Kompaktes Kontextpaket aus Suchergebnissen erstellen (inline JSON-Payload plus Artefaktpfad). |
| `iis_get_chunk` | `iis.agent.get_chunk.v1` | Einzelnen Chunk nach ID abrufen. |
| `iis_get_source_references` | `iis.agent.get_source_references.v1` | Quellreferenzen für einen Chunk zurückgeben. |
| `iis_find_usages` | `iis.agent.find_usages.v1` | Verwendungsdatensätze nachschlagen. |
| `iis_explain_blueprint` | `iis.agent.explain_blueprint.v1` | Indizierte Blueprint-Evidenz zusammenfassen (inline JSON-Payload plus Artefaktpfad). |

`iis.index.status.v1` meldet zusätzlich `catalog_exists`, `chunk_store_records` und `vector_records`, sodass Agenten überprüfen können, ob der Index gefüllt wurde, ohne Dateien lesen zu müssen.

Der MCP-Transport liegt in der Verantwortung des Unified MCP Servers. IIS registriert selbst keine MCP-Tools; das Capability Mesh des Projekts deklariert eine Route pro Agenten-Operation und UMCP veröffentlicht diese als generische `mesh_route_*`-Tools. Es ist kein Bridge-Plugin erforderlich.

## Daten und Datenschutz

IIS speichert generierte Indizes standardmäßig im `Saved`-Ordner des Projekts. Wenn ein benutzerdefiniertes Index-Stammverzeichnis festgelegt ist, verwenden Sie einen lokalen/privaten Pfad, außer Ihr Team teilt generierte Evidenz bewusst.

Cloud-Zugriffe erfolgen nur, wenn eine Embedding-Executor-Route in LLM Store einen Cloud-Provider verwendet.

<!-- doc-provenance: SAD architecture.md sections 1,2,7,8; facts product-facts.yml; reconciled 2026-07-16 -->
# Internal Index Service

Internal Index Service (IIS) ist ein Unreal Engine-Plugin für **lokale** Indizierung, Retrieval, Kontextpakete und agentenseitige Suche. Es ist reine Lese-Kategorie (retrieval-only): Es verändert weder Projektinhalte noch generiert es Patches.

## Module

| Modul | Zweck |
| --- | --- |
| `InternalIndexServiceInterface` | Öffentliche Verträge für Chunks, Suche, Importe, Embeddings und Agentenzugriff. |
| `InternalIndexService` | Runtime-Engine-Subsystem, Chunk-Katalog, Vektor-Backends, Embedding-Jobs, inkrementelle Indizierung. |
| `InternalIndexServiceEditor` | Editor-Steuerfenster, Python-Bridge und Tiny Tools-Menüeinträge. |

## Steuerfenster öffnen

```text
Tiny Tools -> AI -> Internal Index Service -> Open Internal Index Service
```

Oder verwenden Sie die Nomad-Registerkarte **Internal Index Service**, falls Ihre Benutzeroberfläche diese bereits anzeigt.

Das Steuerfenster ist wie folgt aufgebaut:

| Registerkarte | Zweck |
| --- | --- |
| **Dashboard** | Statuskarten für Index und Integrationen; Schnellaktionen (Katalog neu erstellen). |
| **Overview** | Dienstversion, Index-Stammverzeichnis, Katalog-/Vektor-Präsenz. |
| **Imports** | UII-Übergabe und Importbericht-Zusammenfassungen. |
| **Catalog** | Katalog erstellen und die Runtime-Katalogzusammenfassung unter `Saved/InternalIndexService/reports` anzeigen. |
| **Embeddings** | Erstellen und Ausführen persistierter Embedding-Jobs über einen erkannten `IIISEmbeddingRouteExecutor`. |
| **Search** | Lokale lexikalische / Vektor- / Hybrid-Suche im lokalen Index. |
| **Agent/MCP** | Agentenverträge, UCM-Routen-IDs und MCP-Zugriffsanleitung über den Unified MCP Server. |
| **Reports** | Ordner-Tastenkürzel für Berichte und Protokolle. |

Die Kopfzeile zeigt den Projektnamen, eine Markierung für reine Lesezugriffe, eine **Settings**-Schaltfläche und eine **Refresh**-Schaltfläche. Aktualisieren bringt alle Registerkarten-Zusammenfassungen auf den neuesten Stand, erzwingt ein Update der Dashboard-Karten und aktualisiert das Governance-Panel.

Dashboard-Karten werden beim Öffnen, durch explizites **Refresh** sowie nach Dashboard-Aktionen wie **Rebuild** aktualisiert. Das Fenster baut die Karten nicht über einen regelmäßigen Timer neu auf, was die Benutzeroberfläche beim Bearbeiten oder Prüfen stabil hält.

## Projekteinstellungen

Konfigurieren Sie IIS unter:

```text
Edit -> Project Settings -> Plugins -> Internal Index Service
```

| Einstellung | Standardwert | Bedeutung |
| --- | --- | --- |
| **Vector Backend** | `jsonl_bruteforce` | Lokale Vektorindex-Implementierung (`jsonl_bruteforce` oder `hnsw`) mit automatischer Brute-Force/HNSW-Routenauswahl nach Datensatzanzahl. |
| **Index Root (optional)** | *(leer)* | Überschreibung für das Index-Stammverzeichnis auf der Festplatte; leer verwendet `Saved/InternalIndexService`. |
| **Brute Force Max Records** | `10000` | Exakter Suchschwellenwert, ab dem HNSW verwendet wird. |
| **Embedding Executor Id** | *(leer)* | Bevorzugter Embedding-Executor. Leer verwendet die normale IIS-Erkennung; die optionale IIS LLM Store Bridge setzt dies beim Laden auf `llmstore`. |
| **Vector Storage Format** | `Int8 Per-Vector Scale` | HNSW-Speicherrichtlinie. Belassen Sie die kompakte Per-Vektor-int8-Standardeinstellung für die normale Nutzung; verwenden Sie `Float32` für High-Fidelity-/Debug-Läufe; verwenden Sie `Experimental Global Scale` nur hinter dem experimentellen Gate. |
| **Allow Experimental Vector Formats** | `false` | Aktiviert reine Messungs-Vektorlayouts, die die Genauigkeit (Recall) verringern können. |
| **Rebuild On Vector Format Mismatch** | `true` | Baut inkompatible persistierte HNSW-Partitionen neu auf, anstatt sie mit dem falschen Byte-Layout zu laden. |
| **Quantization Recall Gate** | `0.7` | Recall-Untergrenze für Quantisierungs-Automatisierungstests; erhöhen Sie diese nach repräsentativer Projektvalidierung. |
| **HNSW M / efConstruction / efSearch** | `16` / `200` / `64` | HNSW-Recall-, Erstellungszeit-, Speicher- und Abfragelatenz-Feinabstimmung. |

Der MCP-Zugriff wird vom Unified MCP Server über Capability Mesh-Routen des Projekts bereitgestellt. IIS liefert keine eigene dedizierte IIS-UMCP-Bridge mehr aus und erfordert diese auch nicht.

## Integrationen

Die Embedding-Ausführung wird über `FIISEmbeddingDiscovery` (`IModularFeatures` / `IIISEmbeddingRouteExecutor`) delegiert. Bridge-Plugins registrieren sich in `StartupModule` und melden sich in `ShutdownModule` ab. `FIISEmbeddingRouteExecutorRegistry` ist ein veralteter Adapter für Legacy-Aufrufer.

Die Dashboard-Karte **Integrations** listet Executor-IDs aus `FIISEmbeddingDiscovery::GetExecutorIds()` auf und zeigt, ob jede Integration aktiv ist.

Die Editor-Jobhistorie wird über UCM-Routen (`iis.editor.jobs.list.v1`, `iis.editor.jobs.status.v1`) anstelle eines UMCP-Kompilierzeit-Providers bereitgestellt. Die Listenroute führt die Panel-Historie mit den jüngsten SQLite-Embedding-Jobzeilen zusammen.

## Verwandte Dokumentation

| Dokument | Zielgruppe |
| --- | --- |
| [QUICKSTART.md](QUICKSTART.md) | Erste Einrichtung, Import, Indexaufbau und Suche. |
| [UserManual.md](UserManual.md) | Vollständiger Editor-Workflow und betriebliches Verhalten. |
| [SettingsReference.md](SettingsReference.md) | Einstellungen, generierte Dateien und Speicherpfade. |
| [TechnicalOverview.md](TechnicalOverview.md) | Architektur und Datenfluss auf Entwicklerebene. |
| [CodeDocumentation.md](CodeDocumentation.md) | C++ Source Map, Kernklassen und Ausführungspfade. |
| [INTEGRATION.md](INTEGRATION.md) | Anbindung von UII, LLM Store und UMCP an IIS. |
| [FAQ.md](FAQ.md) | Häufige Fragen von Käufern und Prüfern. |
| [TROUBLESHOOTING.md](TROUBLESHOOTING.md) | Häufige Fehler und Behebungen. |
| [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md) | Details zur Drittanbieter-Quellcode-Deklaration für die Fab-Einreichung. |
| [../CHANGELOG.md](../CHANGELOG.md) | Versionshinweise. |

## Paketierung

`Config/FilterPlugin.ini` enthält `/Documentation/...`, damit Käufer diesen Ordner in Fab-Builds erhalten.
Ebenfalls bleiben von BuildPlugin generierte Vorkompilierungs-Metadaten in der gepackten Ausgabe enthalten. Wenn IIS in einer Unreal Engine-Installation installiert wird, verwenden Sie ein für diese Engine-Version erstelltes Paket und halten Sie dessen generierte Binärdateien und Metadaten intakt.

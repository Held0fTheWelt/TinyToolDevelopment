<!-- doc-provenance: SAD architecture.md sections 1,2,7,8; facts product-facts.yml; reconciled 2026-07-16 -->
# FAQ (Häufig gestellte Fragen)

## Verändert IIS mein Projekt?

Nein. IIS ist reine Lese-Kategorie (retrieval-only). Es schreibt generierte Index-/Berichtsdateien, wendet aber keine Quellcode-, Blueprint-, Asset- oder Konfigurationsänderungen als Agentenaktion an.

## Enthält IIS einen MCP-Server?

Nein, nicht in aktuellen Releases. Der MCP-Transport wird vom Unified MCP Server bereitgestellt. IIS-Agentenoperationen werden über Capability Mesh-Routen des Projekts bereitgestellt, nicht über einen IIS-eigenen MCP-Server oder ein Bridge-Plugin.

## Wo werden die Daten abgelegt?

Standardmäßig:

```text
Saved/InternalIndexService
```

Sie können das Stammverzeichnis in den Projekteinstellungen überschreiben.

## Sendet IIS Projektdaten in die Cloud?

Nur wenn eine Embedding-Executor-Route in LLM Store einen Cloud-Provider verwendet. Suche, Katalog, Import und Berichtsdateien sind lokal.

## Warum gibt es keine Vektorergebnisse?

Die Vektorsuche erfordert Embeddings. Erstellen und führen Sie Embedding-Jobs aus, nachdem Sie eine Embedding-Route über LLM Store konfiguriert haben.

## Wofür wird hnswlib verwendet?

hnswlib treibt das optionale `hnsw` Approximate Nearest-Neighbor Vektor-Backend an. Es ist als Quellcode unter `Source/ThirdParty/hnswlib` beigelegt.

## Warum fehlen IIS-Werkzeuge in meiner MCP-Werkzeugliste?

Stellen Sie sicher, dass folgende Plugins aktiviert sind:

- Internal Index Service
- Unified MCP Server
- Unreal Capability Mesh

Stellen Sie sicher, dass das Capability Mesh-Profil des Projekts IIS-Agentenrouten (`iis.agent.*.v1`) auflistet, schreiben/aktualisieren Sie dann die IIS-Agentenverträge und rufen Sie `mesh_reload_setup` auf oder aktualisieren Sie den MCP-Client.

## Kann ich IIS aus C++ aufrufen?

Ja. Verwenden Sie `FInternalIndexServiceModule::Get().GetService()` und die Schnittstelle `IInternalIndexService`.

## Kann ich IIS aus Blueprint aufrufen?

IIS stellt in erster Linie Editor-UI und C++-Dienste bereit. Agentenseitige Pfade und Integrationspfade sind C++/JSON-basiert.

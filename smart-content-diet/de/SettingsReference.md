<!-- doc-provenance: AKDB:plugins/SmartContentDiet/architecture.md; docs/architecture/plugins/SmartContentDiet/product-facts.yml; reconciled 2026-07-16 -->
# Einstellungsreferenz

## Rolle / Zielgruppe

Wird in den **Einstellungen** oder der Zielgruppenauswahl im Header festgelegt. Steuert Erklärungstiefe und Tab-Sichtbarkeit:

- **Anfänger** — Übersicht, Optimieren, Ergebnisse, Einstellungen.
- **Ingenieur / Producer (erweitert)** — fügt Preset und Governance (Trend, Schulden, Budget, Eigentümerschaft, Deep Scan) hinzu; Redundanz erscheint nur, wenn ein externer Ähnlichkeitsanbieter registriert ist.

## Scan-Tiefe (Header)

| Tiefe | Lädt Assets? | Hinweise |
| --- | --- | --- |
| `Quick Safe` (Standard) | Nein | Registry/Metadaten-Pfad; schneller erster Durchgang. |
| `Full` | Ja | Vollständige Analyzer-Pipeline; handlungsrelevante Mesh-/Textur-/Material-Ergebnisse. |
| `Deep` | Ja | Tiefe Material-/Static-Mesh-Metriken; nutzt Governance → Deep Scan; am langsamsten. |

Die ausgewählte Tiefe wird von jedem Analyzer-Lauf berücksichtigt (Editor und Commandlet).

Quick Safe ist der AssetRegistry-zuerst-Pfad: Breite Scans vermeiden das harte Laden von Assets, außer ein Kandidat übersteht günstige Metadatenprüfungen. Full und Deep können Assets für detaillierte Analyzer-Details laden.

## Ausgabe-Pfade

```text
Saved/SmartContentDiet/OptimizationQueue/<timestamp>/   ← Anwendungsberichte der sicheren Warteschlange
```

## Genehmigung / Sicherheit

Verändernde Funktionen (`scd.optimize.apply_safe`, `scd.optimize.apply_fix`) sind **standardmäßig genehmigungsgeschützt**. Destruktive Korrekturen erfordern ein explizites `allow_destructive: true`. Führen Sie Mutationen nur in einem gesicherten, quellcodeverwalteten und wegwerfbaren Workspace aus.

## Commandlet (CI / headless)

Schalter: `-QuickSafe`, `-FullScan`, `-DeepScan`, `-OptimizationQueueReport`, `-ApplySafeQueue`, `-Path=`, `-Limit=`, `-NoFail`, plus die Standard-Schalter `-unattended -nop4 -nosplash`. Anwendungsschalter sollten nur auf gesicherte Projekte angewendet werden.

## Optionale Ökosystem-Routen

Wenn **Unreal Capability Mesh (UCM)** aktiviert ist, stellt SCD schreibgeschützte Provider-Funktionen und zwei genehmigungsgeschützte verändernde Optimierungsrouten über JSON-deklarierte UCM-Routen bereit. SCD verlinkt niemals ein Peer-Plugin im Code; diese Integration ist vollständig optional. Siehe den [Dokumentationsindex](README.md) und [../Resources/SMART_ANALYSIS_ARCHITECTURE.md](../Resources/SMART_ANALYSIS_ARCHITECTURE.md).

SCD stellt auch schreibgeschützte Editor-Auftragsrouten (`scd.editor.jobs.list.v1`, `scd.editor.jobs.status.v1`) für die UMCP-Aggregation über UCM bereit.

Für tiefere Analyzer-/Preset-/Governance-Einstellungen siehe [../Resources/SMART_ANALYSIS_ARCHITECTURE.md](../Resources/SMART_ANALYSIS_ARCHITECTURE.md).

<!-- doc-provenance: AKDB:plugins/UnrealCapabilityMesh/architecture.md; docs/architecture/plugins/UnrealCapabilityMesh/product-facts.yml; reconciled 2026-07-19 -->
# Dokumentation zu Unreal Capability Mesh

Dieser Ordner dokumentiert das Unreal Capability Mesh Plugin für Unreal Engine 5.4+, die Projekteinrichtung, Integration und Orientierung im Quellcode.

Fab-Produktseite: https://www.fab.com/listings/fd186d26-cdcf-4c4f-93d4-50e437b7673e

## Hier beginnen

| Dokument | Zweck |
| --- | --- |
| [BUYER_GUIDE.md](BUYER_GUIDE.md) | Produktumfang, enthaltene Module, was UCM leistet und was nicht. |
| [QUICKSTART.md](QUICKSTART.md) | Minimaler Einrichtungsablauf von Manifesten bis zu generierten Berichten. |
| [UserManual.md](UserManual.md) | Control-Panel-Workflow und normaler Betriebsablauf. |
| [TechnicalOverview.md](TechnicalOverview.md) | Architektur, Datenfluss, Speicherorte und Diagnosen. |
| [CodeDocumentation.md](CodeDocumentation.md) | C++ Quellcode-Leitfaden nach Modulen und Klassen. |
| [SettingsReference.md](SettingsReference.md) | Manifest-Ordnerstruktur, Projektprofil-Felder, Richtlinien-Felder, Ausgabepfade. |
| [INTEGRATION.md](INTEGRATION.md) | Anbindung eines anderen Plugins über Manifeste oder Adapter. |
| [TROUBLESHOOTING.md](TROUBLESHOOTING.md) | Häufige Probleme bei Validierung, Discovery, Routen und Aufrufen. |
| [FAQ.md](FAQ.md) | Kurze Antworten für Käufer und Prüfer. |
| [ReleaseChecklist.md](ReleaseChecklist.md) | Fab-Compliance- und Paketierungs-Checkliste. |
| [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md) | Erklärung zu Drittanbieter-Software. |

## Kernkonzept

UCM ist ein neutraler Hub. Es kennt keine spezifischen Partner-Plugins im C++-Code. UCM selbst, aktivierte Provider-Plugins und das Projekt können jeweils Capabilities, Endpunkte, Schemata, Regeln, Routen, Transformationen und Adapter in JSON beschreiben. Der Loader führt diese Setup-Roots in Prioritätsreihenfolge zusammen, baut Registries auf, bewertet Sicherheitsregeln und schreibt Berichte.

Das aktuelle Projekt-Setup nutzt UCM als primäre Integrationsschicht zwischen Tiny Tool Development Produkten. Produktspezifisches Verhalten verbleibt im besitzenden Plugin als per JSON aufrufbare Endpunkte oder Dateiverträge; UCM lädt nur das Setup, das sie verbindet. Freebie Bridges sind optionale Fallback-/Referenz-Plugins für Teams ohne UCM, nicht das Standard-Verbindungsmodell.

## Wichtige Pfade

```text
<EnabledPlugin>/Config/UnrealCapabilityMesh/  ← vom Provider besitzende, schreibgeschützte Manifeste
Config/UnrealCapabilityMesh/                   ← optionale projekt-eigene Overrides und zusammengesetzte Routen
Saved/UnrealCapabilityMesh/                    ← generierte Berichte und Routen-Ausgaben
```

Kopieren Sie Manifeste eines Providers nicht nur in das Projekt, um dessen Routen offenzulegen. Aktivieren Sie das Provider-Plugin und laden Sie das Setup neu. Erstellen Sie ein Projekt-Override nur, wenn das Projekt Profilfelder bewusst ändert oder eine zusammengesetzte Route besitzt.

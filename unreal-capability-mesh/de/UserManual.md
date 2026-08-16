<!-- doc-provenance: AKDB:plugins/UnrealCapabilityMesh/architecture.md; docs/architecture/plugins/UnrealCapabilityMesh/product-facts.yml; reconciled 2026-07-19 -->
# Benutzerhandbuch

## Control Panel

Öffnen Sie das Panel über:

```text
Tools -> Unreal Capability Mesh
```

Das Panel ist eine technische Betriebs-Ansicht für manifestgesteuerte Interoperabilität. Es nutzt ein Statusbanner und fokussierte Seiten, anstatt alle Werkzeuge in einer langen Ansicht zu stapeln.

Seiten:

- `Overview`: aktives Profil, Inventar-Zähler, Verfügbarkeits-Zähler, Setup-Ablauf und MCP-Vertrag.
- `Capabilities`: geladene Capability-IDs, Endpunkte, Seiteneffekte, Verfügbarkeit, Warnungen und Quellmanifeste.
- `Routes`: Routenkatalog plus Dry-Run- und Ausführungs-Eingabe/Ausgabe.
- `Governance`: aktives Vokabular für Seiteneffekte und Regelentscheidungen.
- `Tiny Tools`: Setup-Paketschalter für Inhalte der Tiny Tool Development.
- `Setup Editor`: typ-bewusster JSON-Editor für Projekt-Setup-Manifeste, schreibgeschützte Referenzbeispiele und die unverbindliche Spielwiese (Playground-Sandbox).
- `Config Admin`: freigegebene Konfigurationsziele und Routen-Presets für Auflist-, Lese- und Schreiboperationen.
- `Diagnostics`: Setup-Validierungs-, Discovery- und Reload-Meldungen.
- `Adapter`: Starter-Manifest-Generator zum Hinzufügen setup-deklarierter Capabilities ohne Bridge-Abhängigkeit.

## Tiny Tools

Die Seite `Tiny Tools` wird durch Katalogmanifeste gesteuert unter:

```text
Config/UnrealCapabilityMesh/tool_catalogs/
```

Der erste Schalter beantwortet, ob das Projekt Setup-Inhalte der Tiny Tool Development nutzen soll. Wenn er ausgeschaltet ist, werden alle dem Katalog gehörenden Setup-Einträge aus dem aktiven Profil entfernt. Einzelne Werkzeugschalter aktivieren oder deaktivieren dann die vom Katalog deklarierten Paketeinträge:

- Capability-Manifeste
- Endpunkt-Manifeste
- Schema-Manifeste
- Regel-Manifeste
- Routen-Manifeste
- Transformations-Manifeste
- Adapter-Manifeste
- Konfigurationsziel-IDs

Dies ist ein Deaktivierungsmodell, keine Dateilöschung. Manifestdateien verbleiben im Projekt und können später wieder aktiviert werden.

Tiny-Tool-Pakete sind bewusst nach Eigentümerschaft aufgeteilt. IIS, LLM Store und UII können unabhängig voneinander aktiviert werden. Plugin-übergreifende Workflows sind separate Routenschalter, sodass ein Projekt IIS alleine, LLM Store alleine, UII+IIS oder IIS+LLM Store nutzen kann, ohne den gesamten Stack zu besitzen.

Das Profilfeld `enabled_config_target_ids` beschränkt, welche Konfigurationsziele für Config Admin sichtbar sind. Wenn das Feld fehlt, behält Config Admin das alte Verhalten bei und scannt jedes Zielmanifest.

## Setup Editor

Die Seite `Setup Editor` bearbeitet projekt-lokale Manifeste unter `Config/UnrealCapabilityMesh` mit typ-bewussten Feldern:

- Booleans für Richtlinien- und Profilschalter
- String-Arrays für `enabled_*_manifests`
- Enum-Felder wie `invocation_mode` und `side_effects`
- verschachtelte Objekte und Objekt-Arrays aus Routen-, Capability- und Endpunkt-Manifesten

Der linke Baum hat drei Wurzeln:

1. `Project Setup` — editierbare Projekt-Manifeste, einschließlich `project_profile.json`.
2. `Playground Sandbox` — editierbare Sandbox-Manifeste unter `playground/` ohne reale Plugin-Bindung. Verwenden Sie `Add playground to profile`, um Aktivierungsfehler zu testen, oder aktivieren Sie den Katalogeintrag `Setup Editor Playground` unter `Tiny Tools`.
3. `Reference Samples` — schreibgeschützte gebündelte Tiny-Tool-Manifeste, gruppiert nach Katalog-Plugin, plus UCM-Kernbeispiele. Verwenden Sie `Copy to project`, um ein Referenz-Manifest in die Projektkonfiguration zu duplizieren.

Aktionen der Symbolleiste:

- `Save` / `Revert` — aktive Manifestdatei schreiben oder verwerfen.
- `Validate file` — `FCapabilityMeshSetupLoader::ValidateManifestFile` auf die ausgewählte Datei anwenden.
- `Reload Setup` — aktives Mesh nach Profil- oder Manifeständerungen neu laden.
- `Open source folder` — den zugeordneten C++ Plugin-Pfad aus `editor/plugin_source_hints.json` öffnen, wenn ein Referenz-Plugin-Knoten ausgewählt ist.

Regeln zur Feldtypisierung liegen in `editor/manifest_field_schema.json`.

## Reload Setup

`Reload Setup` ruft `FCapabilityMeshService::ReloadSetup` auf.

Es führt folgende Sequenz aus:

1. Löscht vorherige Registries und Berichte.
2. Ermittelt das gebündelte UCM-Setup, plugin-lokale Setup-Roots von aktivierten Plugins und das optionale Projekt-Override.
3. Führt deren `project_profile.json`-Dateien in Prioritätsreihenfolge zusammen.
4. Lädt Capabilities, Endpunkte, Schemata, Regeln, Routen, Transformationen und Adapter.
5. Registriert geladene Definitionen.
6. Schreibt Setup- und Registry-Diagnosen.
7. Führt die Discovery aus.
8. Schreibt Discovery- und Kompatibilitätsberichte.

Vom Provider besessene Manifeste sollten im Ordner `Config/UnrealCapabilityMesh/` des Provider-Plugins verbleiben. Projekt-lokale Manifeste haben höhere Priorität und dienen bewussten Overrides oder projekt-eigenen zusammengesetzten Routen. Das Duplizieren von Provider-Definitionen in das Projekt kann Override-Warnungen erzeugen und die Eigentümerschaft verschleiern.

Wenn die optionale Tiny Tool Execution Integration Bridge aktiviert ist, ruft ihr Editor-Modul `ReloadSetup` auf, bevor projizierte UCM-Werkzeuge registriert und ermittelt werden. UCM besitzt weiterhin die resultierenden Routendefinitionen und jede Richtlinienentscheidung.

## Discovered Capabilities

Die Ermittlungsansicht listet Capability-ID, Provider-ID, Interop-Modus und Verfügbarkeit auf. Verfügbarkeit kann verfügbar, nicht verfügbar, unsicher, fehlendes Schema, Genehmigung erforderlich oder Plugin nicht geladen sein.

## Diagnostics

Die Diagnoseansicht zeigt Setup-Validierungsfehler und -Warnungen plus Meldungen, die vom Neuladen/Discovery zurückgegeben wurden. Nutzen Sie diese zuerst, wenn eine Route oder ein Endpunkt nicht erscheint.

## Routes

Geben Sie eine Routen-ID ein und führen Sie einen Dry Run aus. UCM löst Routenschritte auf, prüft die Verfügbarkeit von Capabilities, aggregiert Seiteneffekte, bewertet Regeln und schreibt einen Routenbericht.

Geben Sie Routen-JSON-Eingaben ein und führen Sie eine Route aus, wenn der Dry Run sauber ist. UCM plant die Route zuerst, blockiert Richtlinienverstöße und Routen, die einen Dry Run erfordern, und ruft dann jeden Endpunkt in Schrittreihenfolge auf. Routen, die eine Genehmigung erfordern, müssen `approval_granted: true` oder `approval: "granted"` in der Routeneingabe enthalten, bevor sie ausgeführt werden, außer die explizit als **EXPERIMENTELL** markierte automatische Selbstgenehmigung ist für diese Route aktiv. Schrittausgaben und Routenausgabe werden nach `Saved/UnrealCapabilityMesh/route_execution_reports/` geschrieben.

### Route Catalog

Der **Route Catalog** auf der Seite "Routes" listet jede geladene Route aus Setup-Manifesten in einer nach Plugins gruppierten Tabelle auf:

| Spalte | Inhalt |
| --- | --- |
| Plugin / Route | Aufklappbare Plugin-Gruppen und Routenzeilen mit Richtlinien, Schritten, Endpunkten, Seiteneffekten und Quell-Manifest-Details |
| Approve all at own risk | Steuerungen für die **EXPERIMENTELLE** automatische Selbstgenehmigung |

Spaltenkopf:

- **Approve all at own risk** — globaler Schalter für jede genehmigungspflichtige Route im aktiven Profil. Wenn aktiviert, sind pro-Route-Kontrollkästchen deaktiviert, da alle genehmigungspflichtigen Routen den Override erben.

Plugin-Zeilen:

- Aufklapppfeil, Plugin-Anzeigename, Routenanzahl und ein pro-Plugin-Genehmigungskontrollkästchen, wenn dieses Plugin genehmigungspflichtige Routen besitzt.

Routenzeilen:

- Aufklapppfeil, Routen-ID und Routendetailtext aus dem Dry-Run-Plan.
- Genehmigungspflichtige Routen: pro-Route-Kontrollkästchen (außer **Approve all** ist aktiv).
- Routen, die keine Genehmigung erfordern: `n/a` mit einem Tooltip, der erklärt, dass kein Genehmigungstor gilt.

Eine orangefarbene Warnung über dem Katalog weist darauf hin, dass die automatische Selbstgenehmigung eine breite Richtlinienumgehung aktiviert. Passende Deny-Regeln, Routen-Asset/Projektmutation-Prüfungen, Genehmigungsanforderungen und Dry-Run-Anforderungen werden übersprungen; aktivierte Routen können daher den Editorzustand ohne diese Schutzmaßnahmen ändern.

Dieselben Einstellungen bleiben in `project_profile.json` (`experimental_self_approval_all_routes`, `experimental_self_approved_route_ids`) bestehen und können über MCP mit `mesh_configure_experimental_self_approval` gelesen oder geändert werden; das Aktivieren über MCP erfordert `acknowledge_experimental_risk: true`. Halten Sie die automatische Selbstgenehmigung für den normalen Produktionsbetrieb deaktiviert.

Die Seite `Config Admin` kann die Standard-Config-Admin-Routen-IDs und JSON-Hüllen im Routenrunner vorbereiten. Dies hält MCP, Editor-Benutzer und Automatisierung auf demselben Routenvertrag.

## Administration von DataAsset und DataTable

`UCapabilityMeshAssetAdminSubsystem` legt per JSON aufrufbare Operationen für die DataAsset/DataTable-Verwaltung offen:

- `ExportAdminSurfaceJson`: exportiert ein DataAsset oder eine DataTable in eine portable Admin-Hülle und kann diese unter `Saved/UnrealCapabilityMesh/asset_admin` schreiben.
- `ImportAdminSurfaceJson`: importiert eine zuvor exportierte Hülle in ein bestehendes DataAsset oder eine DataTable.
- `SyncAdminSurfaceJson`: kopiert editierbare Felder aus einem DataAsset in eine DataTable-Zeile oder aus einer DataTable-Zeile zurück in ein DataAsset.

Zusammengesetzte DataTables (Composite DataTables) sind sichere Exportquellen. Direkte Schreibzugriffe auf eine Composite DataTable werden blockiert; zielen Sie auf die konkrete untergeordnete DataTable ab, die die Zeile besitzen soll.

Beispiel für eine Routeneingabe für eine mutierende Sync-Route:

```json
{
  "approval_granted": true,
  "request_json": "{\"source_object_path\":\"/Game/Config/DA_Settings.DA_Settings\",\"target_object_path\":\"/Game/Config/DT_Settings.DT_Settings\",\"mode\":\"data_asset_to_data_table\",\"row_name\":\"Default\"}"
}
```

## Konfigurations-Administration

`UCapabilityMeshConfigAdminSubsystem` legt freigegebene Konfigurationsziele offen. Dies ist die Standard-MCP-Route für Plugin-Einstellungen und Projekt-Konfigurationsdateien.

Ziele werden deklariert unter:

```text
Config/UnrealCapabilityMesh/config_targets/
```

Gängige Routen:

- `capability_mesh.config_admin.list_targets.v1`
- `capability_mesh.config_admin.read_target.v1`
- `capability_mesh.config_admin.write_target.v1`

Lesebeispiel:

```json
{
  "request_json": "{\"target_id\":\"example_plugin.settings\"}"
}
```

Schreibbeispiel:

```json
{
  "approval_granted": true,
  "request_json": "{\"target_id\":\"example_plugin.settings\",\"fields\":{\"bEnabled\":true}}"
}
```

Objekt-Instanz-Ziele, wie z. B. ein asset-gesichertes Konfigurationsobjekt, erfordern zusätzlich `object_path` im Anfrage-JSON. JSON-Datei-Ziele akzeptieren `payload` oder `payload_json`.

## MCP-Zugriff

`UCapabilityMeshMcpGatewaySubsystem` legt das Neuladen des Setups, die Auflistung von Capabilities, den Routen-Dry-Run, die Routenausführung und den Endpunktaufruf als per JSON aufrufbare Funktionen offen. Der Unified MCP Server verbindet sich mit diesem Gateway über den generischen Provider `mesh`, wenn beide Plugins geladen sind.

Gängige UMCP-Werkzeugnamen:

- `mesh_reload_setup`
- `mesh_list_capabilities`
- `mesh_list_routes`
- `mesh_configure_experimental_self_approval`
- `mesh_dry_run_route`
- `mesh_execute_route`
- `mesh_invoke_endpoint`

Unified MCP Server flacht deklarierte Routen auch in direkte MCP-Werkzeuge namens `mesh_route_<sanitized_route_id>_<hash>` ab. Diese Werkzeuge akzeptieren `mode: "dry_run"` zur Analyse oder `mode: "execute"` zur Ausführung. Wenn kein Feld `input` oder `input_json` angegeben ist, werden die verbleibenden Argumente zum Routeneingabe-Objekt. UCM exportiert routen-abgeleitete `input_schema`, `output_schema` und `tool_annotations` über `mesh_list_routes`; UMCP veröffentlicht diese als MCP `inputSchema`, `outputSchema` und Anmerkungen für jedes `mesh_route_*`-Werkzeug. Für gängige Routen, die an `request_json` binden, spiegelt UMCP auch abgeflachte Argumente in dieses serialisierte Anfragefeld, damit die KI Werkzeuge mit verständlichen benannten Parametern aufrufen kann.

Verwenden Sie `mesh_execute_route` für DataAsset/DataTable-Import, -Synchronisation und Konfigurationsschreibzugriffe, damit Routenrichtlinien und Genehmigungsprüfungen aktiv bleiben. Verwenden Sie `mesh_configure_experimental_self_approval` nur für **EXPERIMENTELLE** Test- oder Eigenrisiko-Workflows; es kann die breite Richtlinienumgehung global oder für ausgewählte Routen-IDs aktivieren. Verwenden Sie `mesh_list_routes`, um den aktuellen MCP-sichtbaren Status zu überprüfen; es meldet das globale experimentelle Flag, ausgewählte Routen-Overrides und den effektiven pro-Route umgangenen Plan.

## Primäre UCM-Integration

Das aktive Projektprofil verbindet Produkte der Tiny Tool Development mit setup-deklarierten Routen. Nutzen Sie diesen UCM-Pfad als normales Integrationsmodell. Freebie Bridges dienen nur Teams ohne UCM oder Entwicklern, die direkte Adapterbeispiele wünschen.

- `uii_to_iis_context_pack.v1`: UII-Evidenz -> IIS-Import/Suche/Kontextpaket-Ablauf, mit Ausführung von LLM Store Einbettungsrouten, wo konfiguriert.
- `prs.build_asset_move_plan.v1`, `prs.preview_plan.v1`, `prs.apply_plan.v1`, `prs.rollback.v1`: PRS-Platzierungsworkflows über UCM-Routenrichtlinie und Genehmigung.
- `scd.migration_advice_from_handoff.v1`: UII-Übergabevertrag/Hülle -> SmartContentDiet beratende Migrationsergebnisse über UCM.
- `capability_mesh.asset_admin.export.v1`, `capability_mesh.asset_admin.import.v1`, `capability_mesh.asset_admin.sync.v1`: DataAsset/DataTable-Administration über das Mesh.
- `capability_mesh.config_admin.list_targets.v1`, `capability_mesh.config_admin.read_target.v1`, `capability_mesh.config_admin.write_target.v1`: freigegebene Einstellungen und Konfigurationsdateiverwaltung über das Mesh.

Projekt- oder Asset-Mutationsrouten erfordern weiterhin eine explizite Routengenehmigung, außer der explizit als **EXPERIMENTELL** markierte Override für die automatische Selbstgenehmigung ist für diese Route aktiv.

## Regeln

Regeln entscheiden, ob eine Route zulässig ist, eine Genehmigung erfordert, einen Dry Run erfordert oder blockiert ist. Regeln sind nach Priorität geordnet und werden in JSON deklariert.

## Adapter Editor

Der Adapter Editor schreibt ein einfaches Adapter-Manifest unter `Config/UnrealCapabilityMesh/adapters`. Er ist als Ausgangspunkt gedacht, um ein anderes Plugin in UCM einzubinden, ohne direkte C++ Abhängigkeiten zum Hub hinzuzufügen.

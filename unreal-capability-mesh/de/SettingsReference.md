<!-- doc-provenance: AKDB:plugins/UnrealCapabilityMesh/architecture.md; docs/architecture/plugins/UnrealCapabilityMesh/product-facts.yml; reconciled 2026-07-19 -->
# Referenz für Manifeste und Einstellungen

UCM bietet keine Seite unter `UDeveloperSettings`. Die Konfiguration erfolgt über JSON, das aus drei Setup-Root-Klassen geladen wird:

1. UCMs gebündeltes Standard-Setup.
2. Ordner `Config/UnrealCapabilityMesh`, die von aktivierten Provider-Plugins mitgeliefert werden.
3. Das optionale Projekt-Override unter `Config/UnrealCapabilityMesh`.

Profile werden in dieser Reihenfolge zusammengeführt, wobei das Projekt-Override Vorrang hat. Ein projekt-lokales Profil ist für den Ersteinsatz oder für Routen eines aktivierten Provider-Plugins nicht erforderlich. Erstellen Sie nur dann eines, wenn das Projekt das Setup bewusst überschreibt oder zusammengesetzte Routen besitzt.

## `project_profile.json`

| Feld | Zweck |
| --- | --- |
| `schema_version` | Muss mit `capability_mesh.project_profile` beginnen. |
| `profile_id` | Stabile ID für das aktive Profil. |
| `display_name` | Menschenlesbarer Profilname. |
| `enable_knowledge_store` | Schreibt den Aufrufverlauf, wenn wahr. |
| `experimental_self_approval_all_routes` | **EXPERIMENTELL, Verwendung auf eigene Gefahr.** Wenn wahr, nutzen konfigurierte Routen die unten beschriebene breite Richtlinienumgehung. Für den normalen Gebrauch auf false halten. |
| `experimental_self_approved_route_ids` | **EXPERIMENTELL, Verwendung auf eigene Gefahr.** Routen-IDs, die die breite Richtlinienumgehung nutzen, wenn `experimental_self_approval_all_routes` false ist. |
| `active_ruleset_id` | Name des Regelsets, das als aktiv behandelt werden soll. |
| `enabled_capability_manifests` | Pfade zu Capability-Manifesten. |
| `enabled_endpoint_manifests` | Pfade zu Endpunkt-Manifesten. |
| `enabled_schema_manifests` | Pfade zu Schema-Manifesten. |
| `enabled_rule_manifests` | Pfade zu Regel-Manifesten. |
| `enabled_route_manifests` | Pfade zu Routen-Manifesten. |
| `enabled_transform_manifests` | Pfade zu Transformations-Manifesten. |
| `enabled_adapter_manifests` | Pfade zu Adapter-Manifesten. |
| `enabled_config_target_ids` | Optionale Freigabeliste für Config-Admin-Ziele. Wenn nicht vorhanden, werden alle Zielmanifeste gescannt. |
| `tiny_tool_development_plugins_enabled` | UI-verwalteter Opt-in-Schalter für den Tiny Tool Development Katalog. |
| `reflection_metadata_keys` | Metadaten-Schlüssel, die beim Scannen von über Reflexion offengelegten Capabilities verwendet werden. |
| `optional_scan_paths` | Zusätzliche Ordner oder Dateien, die nach JSON-Manifesten gescannt werden. |
| `setup_editor_playground_enabled` | UI-verwalteter Opt-in-Schalter für den Katalogeintrag der Spielwiese im Setup Editor. |
| `setup_editor_show_cpp_source_hints` | Optionales Profil-Flag zum Anzeigen von C++ Quellcode-Hinweisen im Referenzbaum des Setup Editors. |

Relative Manifest-Einträge werden relativ zum Setup-Root aufgelöst, dem das Profil gehört, gegebenenfalls mit Rückfalloptionen auf Projekt- und Projekt-Root. Kopieren Sie zur Anpassung nur das Profil oder die Manifeste, die das Projekt überschreiben möchte. Das Belassen von Provider-Definitionen beim Plugin hält die Eigentümerschaft von Routen klar und vermeidet Warnungen vor doppelten Definitionen.

## Setup-Editor-Assets

| Pfad | Zweck |
| --- | --- |
| `editor/manifest_field_schema.json` | Mappt JSON-Feldpfade auf Editor-Widget-Typen (`bool`, `enum`, `string_array` und ähnliche). |
| `editor/plugin_source_hints.json` | Mappt Katalog-`item_id`-Werte auf C++ Plugin-Quellordner für das schreibgeschützte Durchsuchen von Referenzen. |
| `playground/` | Editierbare Sandbox-Manifeste ohne reale Plugin-Bindung. |
| `tool_catalogs/setup_editor_playground.json` | Katalogeintrag, der Spielwiesen-Manifeste zu `project_profile.json` hinzufügt. |

## Capability Manifest

Capabilities deklarieren, was ein Provider tun kann. Jede Capability hat eine ID, einen Titel, eine Kategorie, Seiteneffekte, Eingabe-Ports, Ausgabe-Ports und eine Endpunkt-ID.

## Endpoint Manifest

Endpunkte deklarieren, wie eine Capability aufgerufen wird. Wichtige Felder:

- `endpoint_id`
- `invocation_mode`
- `target`
- `parameters`
- `availability`

Unterstützte Aufrufmodi umfassen Reflexionsfunktionen, Dateiverträge, modulare Feature-Provider, Python-Bridge, Commandlet und externe Prozesserklärungen. Reflexion, Dateivertrag und UCM-Endpunkt-Provider modularer Features werden direkt ausgeführt; Python-Bridge, Commandlet und externe Prozesserklärungen dienen nur der Discovery, bis ihre generischen Aufrufer implementiert sind.

## Schema Manifest

Schemata beschreiben die erwartete Form von Eingabe- und Ausgabe-Ports. UCM verwendet Schema-IDs zur Kompatibilitätsprüfung.

## Rule Manifest

Regeln entscheiden, ob eine Route zulässig ist. Häufige Seiteneffekte:

- `read_only`
- `saved_folder_write`
- `project_config_write`
- `asset_mutation`
- `project_mutation`
- `network`
- `ai_completion`

## Route Manifest

Routen definieren geordnete Schritte. Jeder Schritt verweist auf eine Capability-ID und deklariert Eingabe/Ausgabe-Bindungen.

Mutierende Routen sollten `allow_asset_mutation` oder `allow_project_mutation` nur setzen, wenn die Operation beabsichtigt ist. Der Executor erfordert normalerweise eine Genehmigung zur Laufzeit; geben Sie `approval_granted: true`, `approvalGranted: true` oder `approval: "granted"` in der Routeneingabe an, außer der unten beschriebene **EXPERIMENTELLE** Override für die automatische Selbstgenehmigung ist bewusst aktiv.

### Experimentelle automatische Selbstgenehmigung

`experimental_self_approval_all_routes` und `experimental_self_approved_route_ids` sind explizit experimentelle Notausstiege für Tests und lokale Workflows auf eigene Gefahr. Wenn aktiviert, übergibt UCM `bExperimentalPolicyBypass=true` bei der Routenplanung und -ausführung. Passende Regeln mit `allow=false` blockieren die Route nicht mehr, regelbasierte Genehmigungs- und Dry-Run-Anforderungen werden ignoriert, Prüfungen auf Asset-/Projektmutationen auf Routenebene werden übersprungen und der finale Plan hebt sowohl Genehmigungs- als auch Dry-Run-Anforderungen auf.

Halten Sie beide Einstellungen für normale und Produktions-Workflows ausgeschaltet. Der Route Catalog des Editors kennzeichnet diese Schalter als **EXPERIMENTELL** und weist auf den vollen Umfang der Umgehung hin. MCP-Hosts können dieselben Einstellungen über `mesh_configure_experimental_self_approval` lesen oder ändern; das Aktivieren über MCP erfordert `acknowledge_experimental_risk: true`.

## Transform Manifest

Transformationen mappen Quell-JSON auf Ziel-JSON. Sie werden verwendet, um Ausgaben einer Capability in Eingaben für eine andere anzupassen.

## Adapter Manifest

Adapter mappen Funktionen von Drittanbieter-Plugins in UCM, ohne eine direkte C++ Abhängigkeit zum Hub hinzuzufügen.

## Einrichtung der Asset-Administration

Das gebündelte Setup unter UCMs eigenem `Config/UnrealCapabilityMesh` deklariert Capabilities für die DataAsset/DataTable-Administration:

- `capability_mesh.asset_admin.export`
- `capability_mesh.asset_admin.import`
- `capability_mesh.asset_admin.sync`

Alle drei rufen `UCapabilityMeshAssetAdminSubsystem` über `reflection_subsystem_function`-Endpunkte auf. MCP-Hosts sollten über diese Deklarationen routen, anstatt produktspezifischen Bridge-Code aufzurufen.

## Konfigurationsziel-Manifest

Ziele der Konfigurations-Administration werden getrennt von Routen-Manifesten in einer Freigabeliste deklariert unter:

```text
Config/UnrealCapabilityMesh/config_targets/*.json
```

Ziel-Manifeste nutzen:

```json
{
  "schema_version": "capability_mesh.config_target_manifest.v1",
  "targets": [
    {
      "target_id": "example_plugin.settings",
      "display_name": "Example Plugin Settings",
      "description": "Explains what the target controls and when it should be edited.",
      "kind": "uobject_config",
      "class_path": "/Script/ExamplePlugin.ExamplePluginSettings",
      "required_plugin_names": ["ExamplePlugin"]
    }
  ]
}
```

Unterstützte `kind`-Werte:

- `uobject_config`: liest und schreibt Konfigurationseigenschaften auf einem Klassenstandardobjekt (CDO) und speichert die Konfiguration.
- `uobject_instance`: liest und schreibt editierbare Felder auf einer freigegebenen Objektklasse. Anfragen müssen `object_path` enthalten.
- `json_file`: liest und schreibt eine deklarierte JSON-Datei unter einem erlaubten Basisverzeichnis.

Jedes Ziel sollte eine nicht-leere `description` enthalten; Config Admin hebt fehlende Beschreibungen als Manifest-Warnungen hervor, da Benutzer vor dem Lesen oder Schreiben eines Ziels Kontext benötigen.

Die Standardrouten sind `capability_mesh.config_admin.list_targets.v1`, `capability_mesh.config_admin.read_target.v1` und `capability_mesh.config_admin.write_target.v1`. Schreibrouten deklarieren `project_config_write` und `asset_mutation`, sodass Konfigurationsdateien, Konfigurationsobjekte, DataAssets und editierbare Objektinstanzen alle denselben Pfad für Genehmigung und Dry Run durchlaufen.

## Werkzeugkatalog-Manifest

Werkzeugkataloge liegen unter:

```text
Config/UnrealCapabilityMesh/tool_catalogs/*.json
```

Sie gruppieren Setup-Einträge in per UI schaltbare Pakete. Ein Paket kann Pfade für Capability-, Endpunkt-, Schema-, Regel-, Routen-, Transformations- und Adapter-Manifeste sowie Konfigurationsziel-IDs deklarieren. Die UI deaktiviert Pakete, indem sie diese Einträge aus `project_profile.json` entfernt; sie löscht keine Manifestdateien.

Katalogpakete sollten so klein wie die Eigentumsgrenze bleiben. Ein Plugin-Paket sollte nur die eigenen Capabilities, Endpunkte, Schemata und Konfigurationsziele dieses Plugins hinzufügen. Plugin-übergreifende Workflows sollten separate Routenpakete sein, die auf bereits aktivierte Bausteine verweisen. Dies hält reine IIS-, reine LLM Store-, UII+IIS- und IIS+LLM Store-Setups gültig, ohne jedes Plugin von Tiny Tool Development zu erfordern.

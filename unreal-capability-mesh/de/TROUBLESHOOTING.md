<!-- doc-provenance: AKDB:plugins/UnrealCapabilityMesh/architecture.md; docs/architecture/plugins/UnrealCapabilityMesh/product-facts.yml; reconciled 2026-07-19 -->
# Fehlerbehebung

## Setup-Laden schlägt fehl

Überprüfen Sie `Saved/UnrealCapabilityMesh/setup_validation_report.json`.

Häufige Ursachen:

- kein `project_profile.json` in den gebündelten, Plugin- oder Projekt-Setup-Roots
- ungültige `schema_version`
- Tippfehler im Manifestpfad
- fehlerhaftes JSON
- fehlende erforderliche Arrays wie `capabilities` oder `endpoints`

Für die Erstnutzung ist ein projekt-lokales Profil optional. UCM führt sein gebündeltes Standardprofil mit Profilen zusammen, die von aktivierten Plugins mitgeliefert werden. Erstellen Sie ein Projektprofil nur für bewusste Overrides oder projekt-eigene Routen, und klicken Sie dann auf `Reload Setup`.

## Capability wird nicht ermittelt

Überprüfen Sie:

- Capability-Manifest wird vom Profil in dessen besitzendem Setup-Root referenziert
- Capability hat eine nicht-leere `capability_id`
- Endpunkt-ID existiert
- erforderliche Plugin-Namen sind geladen
- erforderliche Schemata existieren

Wenn die Capability zu einem anderen Plugin gehört, stellen Sie sicher, dass dieses Plugin aktiviert ist und dessen Paket `Config/UnrealCapabilityMesh/project_profile.json` enthält. Kopieren Sie die Provider-Definition nicht als Workaround in das Projekt; laden Sie das Setup neu und prüfen Sie, welche Setup-Roots ermittelt wurden.

## Projekt meldet Warnungen wegen doppelter Definitionen

Dieselbe vom Provider besessene Capability, derselbe Endpunkt, dasselbe Schema oder dieselbe Route existiert sehr wahrscheinlich sowohl in einem plugin-lokalen Profil als auch im Projekt-Override.

Entfernen Sie die doppelte Projektkopie, außer das Projekt überschreibt diese Definition bewusst. Projektprofile sollten normalerweise projekt-eigene Richtlinienänderungen oder zusammengesetzte Routen enthalten, während Provider-Verträge plugin-lokal bleiben.

## TTER zeigt nach dem Start keine gültige UCM-Route an

Bestätigen Sie, dass die optionale Tiny Tool Execution Integration Bridge aktiviert ist. Ihr Editor-Modul lädt das UCM-Setup vor der TTER-Discovery neu. Klicken Sie nach dem Aktivieren eines neuen Providers oder dem Bearbeiten des Setups auf `Reload Setup` und aktualisieren Sie die Werkzeugermittlung.

## Route ist blockiert

Öffnen Sie den Routenbericht unter `Saved/UnrealCapabilityMesh/route_reports`. Der Routenplaner zeichnet Erklärungen und Blockierungsgründe auf.

Häufige Ursachen:

- keine Regel erlaubt die aggregierten Seiteneffekte
- Route nutzt `project_mutation` und die Standardregel blockiert dies
- Asset-Mutation erfordert Genehmigung oder Dry Run
- Eingabe- und Ausgabeschemata sind inkompatibel

Wenn die **EXPERIMENTELLE** automatische Selbstgenehmigung in der Spalte für die Kataloggenehmigung oder im Profil aktiviert ist, deaktivieren Sie diese, bevor Sie Governance-Verhalten untersuchen. Der breite Override überspringt passende Deny-Regeln, Routen-Asset/Projektmutation-Prüfungen, Genehmigungsanforderungen und Dry-Run-Anforderungen, sodass er jedes dieser Richtlinienergebnisse verschleiern kann.

## Endpunktaufruf schlägt fehl

Überprüfen Sie `Saved/UnrealCapabilityMesh/invocation_reports`.

Häufige Ursachen:

- Klassenpfad lässt sich nicht auflösen
- Funktionsname ist falsch
- Parameterbindung passt nicht zum Funktionsparameter
- Aufrufmodus ist deklariert, aber noch kein generischer Aufrufer unterstützt ihn
- Provider-Plugin ist nicht geladen

## Berichte sind leer

Klicken Sie erneut auf `Reload Setup`. Das Panel lädt Manifeste neu und generiert die Diagnosen neu. Bestätigen Sie auch, dass der Projektkonfigurationspfad das aktive Projekt ist und kein Engine- oder Beispielordner.

## Quellcode-Validierung meldet Hardcoding

Die Quellcodevalidierung kann Partner-Pluginnamen oder produktspezifische Capability-IDs im UCM-Code melden. Verschieben Sie integrationsspezifische Zeichenketten in Setup-JSON, anstatt C++ Abzweigungen hinzuzufügen.

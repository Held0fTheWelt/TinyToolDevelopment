<!-- doc-provenance: AKDB:plugins/UnrealCapabilityMesh/architecture.md; docs/architecture/plugins/UnrealCapabilityMesh/product-facts.yml; reconciled 2026-07-19 -->
# FAQ

## Ist UCM ein KI-Modell oder Agent?

Nein. UCM ist ein Interoperabilitäts-Hub. Es kann KI-bezogene Capabilities beschreiben, enthält jedoch keine Modelle, Prompts, Provider oder Agenten-Runtimes.

## Verändert UCM Assets?

Nicht von sich aus. Es lädt nur Manifeste, plant Routen, ruft deklarierte Endpunkte auf und schreibt Diagnosen. Asset-Mutationen müssen von einem Provider-Endpunkt ausgeführt und durch die Richtlinie erlaubt werden.

## Kann die Genehmigung umgangen werden?

Nur über die explizit gekennzeichneten Steuerungen für die **EXPERIMENTELLE** automatische Selbstgenehmigung in der Spalte "Route Catalog" auf der Seite "Routes", die entsprechenden Felder in `project_profile.json` oder das MCP-Werkzeug `mesh_configure_experimental_self_approval`. Dies ist eine breite Richtlinienumgehung: Deny-Regeln, Routen-Asset/Projektmutation-Prüfungen, Genehmigungs- und Dry-Run-Anforderungen werden übersprungen. Sie dient nur zu Testzwecken oder für eigene Risikoworkflows; lassen Sie **Approve all at own risk** und alle routenspezifischen Schalter für den normalen Gebrauch deaktiviert.

## Warum Manifeste statt direkter C++ Abhängigkeiten verwenden?

Manifeste ermöglichen es Projekten, Werkzeuge zu verbinden, ohne Aufruf-Abhängigkeitsketten zur Kompilierzeit zwischen Plugins zu erstellen. Das hält den Hub neutral und einfacher zu paketieren.

## Wo werden Berichte geschrieben?

Berichte werden unter `Saved/UnrealCapabilityMesh` geschrieben.

## Wo werden Projektmanifeste gespeichert?

Projektmanifeste werden unter `Config/UnrealCapabilityMesh` gespeichert.

## Kann UCM Marketplace-Plugins von Drittanbietern integrieren?

Ja, wenn diese Plugins aufrufbare Funktionen, Dateiverträge oder modulare Features offenlegen, die durch Manifeste oder Adapter beschrieben werden können.

## Bündelt UCM Quellcode von Drittanbietern?

Das Plugin enthält keinen gebündelten Quellcode oder Laufzeitabhängigkeiten von Drittanbietern.

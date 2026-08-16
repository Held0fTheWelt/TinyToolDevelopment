<!-- doc-provenance: product-facts.yml reconciled 2026-07-01; source AKDB:plugins/AssetLoaderStudio/architecture.md -->
# FAQ

## Ist Asset Loader Studio eigenständig lauffähig?

Ja. Der Editor-Workspace, das Runtime-Subsystem, die Blueprint-Bibliothek, Beispiele, Governance-Profile und die Käuferdokumentation funktionieren ohne UCM, UMCP, MCP oder andere Tiny Tool-Plugins.

## Ersetzt es den Asset Manager von Unreal?

Nein. Es baut auf Unreal-Assetpfaden, primären Asset-IDs, Tabellen, Paketen und der Asset Registry auf. Es ergänzt strukturierte Ladejobs, Diagnosen, Tabellen-Snapshots, Abhängigkeitsgraphen, Vorschauen und Governance.

## Kann es Projekt-Assets verändern?

Ja, aber Mutationen erfolgen nach dem Vorschau-Prinzips. Erstellungs-, Duplizierungs-, Umbenennungs-, Retargeting-, Reparatur-, Speicher-, Rollback- und Löschoperationen müssen Prüfungen des Berechtigungsprofils bestehen und sollten vor dem Anwenden überprüft werden.

## Wo werden Audit-Aufzeichnungen gespeichert?

Das Standard-Audit-Verzeichnis ist `Saved/AssetLoaderStudio/Audit`. Der Pfad kann über die Governance-Einstellungen angepasst werden.

## Sind Automatisierungsrouten erforderlich?

Nein. Optionale UCM-/MCP-Dateien stellen dieselben Dienste für verwaltete Automatisierung bereit, aber das Kernprodukt bleibt ohne diese nutzbar.

## Ist Asset Loader Studio live auf Fab?

Der aktuelle Paketstatus lautet "In Publishment" (In Veröffentlichung). Betrachten Sie es als für die Fab-Übergabe vorbereitet, aber nicht als live, bis der Eintrag im Fab-Portal selbst veröffentlicht ist.

<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/LogLevelEditor/architecture.md -->
# FAQ (Häufig gestellte Fragen)

## Ändert LogLevelEditor meine C++-Log-Kategoriendeklarationen?

Nein. Es schreibt keinen Quellcode um. Es entdeckt Kategorien und nutzt das Konsolenbefehlssystem von Unreal, um die aktive Ausführlichkeit zu ändern.

## Sind Änderungen dauerhaft?

Nur beabsichtigte Überschreibungen, die im konfigurierten `ULogLevelDataAsset` gespeichert sind, sind dauerhaft. Runtime-Konsolenänderungen ohne DataAsset-Aktualisierung sind temporär.

## Warum ist eine Kategorie aus der Liste verschwunden?

Sie ist möglicherweise durch die permanente oder temporäre Ausblendliste verborgen, durch Suchtext gefiltert oder im aktuellen Scan-Umfang nicht enthalten.

## Warum fehlt ein Standard-Level?

Der Scanner erkennt gängige Unreal-Makros. Wenn ein Projekt benutzerdefinierte Wrapper-Makros oder sehr ungewöhnliche Formatierungen nutzt, kann die Kategorie zwar gefunden, der Standard-Level jedoch nicht abgeleitet werden.

## Kann ich Engine-Log-Kategorien einschließen?

Ja. Aktivieren Sie das Scannen von Engine-Plugins und/oder Engine-Quellcode in den Einstellungen.

## Funktioniert dies in paketierten Spielen?

Nein. LogLevelEditor ist ein Editor-Plugin für Entwicklungs-Workflows.

## Kann ich ein Logging-Setup mit meinem Team teilen?

Ja. Speichern Sie beabsichtigte Überschreibungen im DataAsset und verwalten Sie es gemeinsam in der Quellcodeverwaltung Ihres Projekts.

## Warum wiederholt das Plugin das Anwenden gespeicherter Level beim Start?

Unreal-Editor-Module können starten, bevor die Engine bereit ist, Konsolenbefehle zu verarbeiten. Die Wiederholungslogik verhindert den Verlust gespeicherter Überschreibungen beim frühen Start.

## Was passiert, wenn ein Konsolenbefehl fehlschlägt?

Die Benutzeroberfläche und das DataAsset werden nicht so aktualisiert, als ob der Befehl erfolgreich gewesen wäre. Der Fehler wird protokolliert.

## Kann ich eine Kategorie vollständig stummschalten?

Verwenden Sie `NoLogging`, aber denken Sie daran, dass die Regelungen zur Kompilierzeit- und Runtime-Verbosity von Unreal weiterhin gelten.

## Unterstützt es benutzerdefinierte Verbosity-Namen?

Nein. Es unterstützt die Standard-Verbosity-Namen von Unreal.

## Ist das DataAsset erforderlich?

Die Benutzeroberfläche kann Runtime-Änderungen prüfen und anwenden, aber die dauerhafte Wiederherstellung beim Start erfordert ein konfiguriertes DataAsset.

## Kann das Plugin Kategorien aus Plugins erkennen?

Ja. Projekt-Plugins gehören zum normalen Scan-Pfad. Engine-Plugins sind optional.

## Ist es sicher für die Quellcodeverwaltung?

Ja, bei beabsichtigter Nutzung. Das Hauptartefakt ist das DataAsset mit dauerhaften Überschreibungen.

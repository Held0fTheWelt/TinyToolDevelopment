<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/CodeCopyrightEditor/architecture.md -->
# FAQ (Häufig gestellte Fragen)

## Wofür wird der Code Copyright Editor verwendet?

Code Copyright Editor hilft Unreal Engine-Entwicklern, konsistente Urheberrechtshinweise über Project Settings und Quelldateien hinweg zu verwalten. Er kann Quellcode-Header in einem Workflow scannen, der Vorschau anzeigen, aktualisieren und melden.

## Beeinträchtigt das Plugin den Runtime-Gameplay-Code?

Nein. Code Copyright Editor ist ein reines Editor-Tool. Es ist für Entwicklungs-, Überprüfungs-, Dokumentations- und CI-Workflows gedacht.

## Kann es eine gesamte Codebasis automatisch aktualisieren?

Ja, aber erst nach dem Scannen und Überprüfen. Der Editor zeigt an, welche Dateien geändert werden können, welche geschützt sind und wie der vorgeschlagene Ersatz vor dem Anwenden aussieht.

## Schützt es Hinweise von Drittanbietern oder Epic?

Ja. Der Scanner ist so konzipiert, dass er fremde, Epic- und Drittanbieter-Hinweise vor automatischem Umschreiben schützt. Geschützte und Konflikt-Dateien sollten manuell überprüft werden.

## Kann ich die Urheberrechtsvorlage anpassen?

Ja. Du kannst die Vorlage für Quelldatei-Hinweise und die Vorlage für Projekthinweise bearbeiten. Token wie Produktname, Dateipfad, Jahr, Lizenzkennung und dateibezogene Beschreibung können automatisch gerendert werden.

## Unterstützt es SPDX- oder REUSE-Workflows?

Das Plugin bietet REUSE/SPDX-orientierte Vorlagen und Berichte. Diese Berichte dienen der Unterstützung von Überprüfungs- und CI-Workflows, stellen jedoch keine rechtliche Zertifizierung dar.

## Gibt es ein Commandlet für CI?

Ja. Das enthaltene `CodeCopyrightCheck`-Commandlet kann das Projekt scannen, optional änderbare Dateien korrigieren, Berichte schreiben und die CI fehlschlagen lassen, wenn Urheberrechtshinweise nicht synchron sind.

## Ersetzt es eine Rechtsberatung?

Nein. Es hilft dabei, Hinweistexte konsistent anzuwenden und zu überprüfen. Es entscheidet nicht über Eigentumsrechte, validiert keine Drittanbieter-Lizenzen und bietet keine Rechtsberatung.

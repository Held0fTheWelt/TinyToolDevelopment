<!-- doc-provenance: product-facts.yml reconciled 2026-07-19; source AKDB:plugins/BestPracticesJournal/architecture.md; release 1.1.2 -->
# Benutzerhandbuch

Best Practices Journal ist eine Editor-Workbench für evidenzbasierte Verwaltung technischer Praktiken. Es dient der Entscheidungsunterstützung und dem Review-Gedächtnis, ist jedoch kein Patch-Planer, Quellcode-Editor, KI-Ausführer oder Asset-Mutationswerkzeug.

## Kern-Workflow

1. Erfassen Sie eine Praxis oder einen Kandidaten aus einer manuellen Notiz, einer Nachweisreferenz oder einem optionalen Provider.
2. Füge Sie Anwendbarkeit, Kompromisse, Fehlermodi, Provenienz, Rechtehinweise und Review-Metadaten hinzu.
3. Validieren Sie den Datensatz vor dem Akzeptieren oder Exportieren.
4. Suchen Sie nach Praktiken, wenn Sie Richtlinien für eine Aufgabe oder ein Review auswählen.
5. Erstellen Sie einen Anwendungs-Brief für eine überprüfte Praxis oder einen expliziten Kandidaten.
6. Übergeben Sie den Brief an einen menschlichen Workflow, UCI, PRS oder einen anderen genehmigten Ausführer.
7. Importieren Sie Implementierungsergebnis-Berichte, um festzuhalten, ob die Praxis bestätigt, geschwächt, widerlegt, spezialisiert oder ersetzt wurde.

## Qualität von Praxiseinträgen

Nutzen Sie BPJ für Praktiken, die eine Überprüfung überstehen können. Ein nützlicher Datensatz umfasst:

- Ein konkretes Problem und einen Zielkontext.
- Eine Lösung, die als wiederverwendbare Richtlinie formuliert ist, nicht als kopierter Code.
- Warum die Richtlinie funktioniert, wo sie anwendbar ist und wo sie fehlschlägt.
- Kompromisse, Vorbedingungen, Anpassungsregeln und Fehlermodi.
- Nachweisreferenzen, Provenienz, Rechtehinweise, Vertrauen und Review-Status.

Wenn diese Felder unbekannt sind, belassen Sie den Eintrag als Kandidat oder Entwurf. Befördern Sie ihn nicht zu einer akzeptierten Richtlinie, nur weil die Zusammenfassung plausibel klingt.

## Öffentliche Operationen

- **Create practice record** speichert eine überprüfte oder entwurfsmäßige Praxis mit Nachweisen, Kontext, Kompromissen und Review-Status.
- **Create practice candidate** speichert einen Entwurf oder vom Provider stammenden Vorschlag, bis er explizit überprüft wurde.
- **Attach evidence** verknüpft lokale/manuelle/Provider-Beweise, ohne geschützten Implementierungscode zu kopieren.
- **Search practices** liefert passende Praxiseinträge aus dem BPJ-eigenen Artefaktspeicher zurück.
- **Create application brief** exportiert eine reine Absichts-Übergabe für einen spezifischen Zielkontext.
- **Import implementation outcome** schließt die Schleife nach der Implementierung oder Ablehnung.

## Anwendungs-Briefs (Application Briefs)

Ein Brief sollte einem anderen Workflow dabei helfen, sicher zu planen. Er kann Zielprojekt/-modul/-umfang, empfohlene Anpassung, Begründung, Einschränkungen, erlaubte und verbotene Aktionskategorien, Validierungsanforderungen, erwartete Ausgaben, Nachweisreferenzen, Genehmigungsstatus und Kompatibilitätshinweise enthalten.

Ein Brief darf nicht als Berechtigung für BPJ dienen, Dateien zu verändern. Wenn das nachgelagerte Tool Änderungen anwendet, muss es selbst die Auflösung des Umfangs, die Dry-Run-Planung, Genehmigungen, Schranken für Mutationen, Validierung, Rollback und seinen eigenen Ergebnisbericht besitzen.

## Ergebnis-Importe (Outcome Imports)

Importieren Sie jedes bedeutsame Ergebnis, einschließlich fehlgeschlagener, abgelehnter, partieller und No-Op-Ergebnisse. Ergebnisse aktualisieren die Praxis-Historie, das Vertrauen, Review-Notizen und Entwicklungslinks. Sie schreiben die ursprüngliche Praxis nicht als universell korrekt um.

Nutzen Sie Ergebnisfelder für Referenzen auf geänderte Dateien, Pfade zu Validierungsberichten, gewonnene Erkenntnisse, empfohlene Journal-Aktualisierungen, Warnungen, Fehler und Links zu externen Plänen oder Berichten.

## Optionale Provider

Optionale Nachweis-, Kandidaten-, Ergebnis-, Übergabe-, Indexierungs-, Routen- oder Implementierungs-Provider können BPJ bereichern. Sie müssen austauschbar bleiben. Wenn ein Provider fehlt, fahren Sie mit manuellen Einträgen, lokalen Nachweisen, JSON/Markdown-Artefakten und der BPJ-Validierung fort.

## Capability Mesh (MCP)

Agenten ohne Dateizugriff können den Review-First-Lebenszyklus des Journals über UMCP schließen:

- `bpj.gather_candidates.v1` — durchsucht Provider-Eingangsordner (einschließlich `project_intelligence_orchestrator` aus der PIO-Übergabe).
- `bpj.repository.list.v1` — listet IDs für Praktiken, Kandidaten, Nachweise, Briefs und Ergebnisse auf.
- `bpj.practice.read.v1` — liest einen serialisierten Datensatz direkt aus.
- `bpj.candidate.promote.v1` — befördert einen überprüften Kandidaten (erfordert Benutzergenehmigung auf der Route).
- `bpj.import_artifacts.v1` — importiert PIO-Kandidatenhüllen (`schema` / `schema_version` beginnend mit `bpj.implementation_intent_candidates.`).

Ordner des Provider-Eingangs: `Saved/BestPracticesJournal/provider_inbox/candidates/<provider_id>/`.

## Commandlets

Commandlets sind nützlich für Validierung, Artefaktimport und Beispiel-Export, aber sie sind keine zwingenden Schritte bei der Erstnutzung. Nutzen Sie gespeicherte Berichte in `Saved/BestPracticesJournal/reports/` als dauerhafte Nachweise für die Automatisierung. Protokolle fassen zusammen, was passiert ist; gespeicherte Artefakte bleiben der maßgebliche Nachweis.

## Grenzen

BPJ erfasst Wissen und Absichten. Es verändert keine Quellcode-Dateien, Assets, Build.cs-Dateien, Projektbeschreibungen oder externen Plugin-Code. Nachgelagerte Ausführungsverantwortliche müssen ihre eigenen Vorschau-, Genehmigungs-, Validierungs- und Rollback-Schranken ausführen.

## Lokale Nachweise und Logs

BPJ speichert dauerhafte Review-Nachweise unter `Saved/BestPracticesJournal/`. Nutzen Sie die JSON/Markdown-Dateien in `reports`, `application_briefs`, `implementation_outcomes` und `schemas`, wenn Sie einen Workflow teilen oder auditieren. Die Unreal-Log-Kategorie `LogBestPracticesJournal` dient der Betreiberdiagnose und Commandlet-Zusammenfassungen; sie ist nicht der maßgebliche Nachweis für akzeptierte Praktiken.

<!-- doc-provenance: product-facts.yml reconciled 2026-07-19; source AKDB:plugins/BestPracticesJournal/architecture.md; release 1.1.2 -->
# FAQ

## Ist BPJ ein allgemeines Notiz-Werkzeug?

Nein. BPJ dient evidenzbasierten technischen Praktiken mit Anwendbarkeit, Kompromissen, Fehlermodi, Provenienz, Überprüfungsstatus und Ergebnishistorie.

## Wann sollte etwas ein Kandidat bleiben?

Belassen Sie es als Kandidat, wenn Nachweise, Anwendbarkeit, Kompromisse, Fehlermodi, Provenienz oder der Überprüfungsstatus unvollständig sind. Kandidaten können nützlich sein, sollten jedoch nicht als akzeptierte Richtlinie behandelt werden.

## Ändert BPJ Projektdateien?

Nein. BPJ kann Anwendungs-Briefs erstellen und Ergebnisse importieren, aber die Projektmutation gehört genehmigten nachgelagerten Werkzeugen oder menschlichen Workflows.

## Was gehört in einen Anwendungs-Brief?

Nutzen Sie einen Brief für Zielkontext, empfohlene Anpassung, Einschränkungen, Nachweisreferenzen, erforderliche Validierung und den Genehmigungsstatus. Nutzen Sie ihn nicht als Patch-Plan oder Mutationsbefehl.

## Benötigt BPJ IIS, SDA, UCI, PRS, UCM oder LLM Store?

Nein. BPJ ist eigenständig. Optionale Tiny Tool-Plugins können Nachweise, Indexierung, Dokumentation, Implementierung oder Routen-Workflows bereitstellen, sind aber für die Kernnutzung nicht erforderlich.

## Kann BPJ KI aufrufen oder Implementierungsschritte entscheiden?

Nein. BPJ kann Nachweise oder Absichten speichern, die von einem anderen überprüften Workflow erstellt wurden, aber es besitzt keine KI-Ausführung, keinen Abruf, keine Patch-Planung, Anwendung, Rollback oder finale Validierung.

## Wo werden Daten gespeichert?

Das Standardprofil nutzt projekt-lokale JSON-Artefakte unter dem BPJ-Speicher-Stammverzeichnis. Optionale SQLite- oder externe Studio-Profile können für größere Workflows konfiguriert werden.

## Welche Daten können sensibel sein?

Praxiseinträge, Nachweise, Briefs, Ergebnisse und Berichte können lokale Pfade, Projektnamen, Review-Notizen, Validierungsausgaben, Rechtehinweise oder Provider-Diagnosen enthalten. Überprüfen und schwärzen Sie Exporte vor dem Teilen.

## Wo finde ich Logs und Berichte?

Berichte werden unter `Saved/BestPracticesJournal/reports/` gespeichert. Runtime-, Editor- und Commandlet-Diagnosen nutzen `LogBestPracticesJournal` im Unreal-Log. Gespeicherte Artefakte bleiben der dauerhafte Nachweis.

## Kann ich Praktiken mit einem Team teilen?

Ja, nach der Überprüfung. Behandeln Sie Exporte als projekt-lokal, bis sie von privaten Pfaden, vertraulichen Notizen und rechtesensiblen Nachweisen bereinigt wurden.

## Können fehlende optionale Provider das Journal beschädigen?

Nein. Fehlende Provider sollten nur als Status oder Diagnose erscheinen. Manuelle Einträge, lokale Nachweise, Validierung, Export und Ergebnisimport müssen verfügbar bleiben.

## Sollten fehlgeschlagene Ergebnisse importiert werden?

Ja. Fehlgeschlagene, abgelehnte, partielle und No-Op-Ergebnisse sind wichtig, da sie die Praxis schwächen, widerlegen, spezialisieren oder ersetzen können. Sie zu verbergen, macht das Journal weniger vertrauenswürdig.

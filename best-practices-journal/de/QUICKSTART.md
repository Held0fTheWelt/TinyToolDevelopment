<!-- doc-provenance: product-facts.yml reconciled 2026-07-19; source AKDB:plugins/BestPracticesJournal/architecture.md; release 1.1.2 -->
# Schnellstart

## Ziel

Ein eigenständiges, projekt-lokales Praxis-Journal erstellen, Nachweise erfassen, eine Praxis überprüfen, einen Implementierungsabsichts-Brief exportieren und ein Ergebnis importieren, ohne Quellcode oder Assets des Projekts zu verändern.

## Erster Start

1. Aktivieren Sie **Best Practices Journal** im Plugin-Browser des Unreal Editors.
2. Starten Sie den Editor neu, wenn Sie dazu aufgefordert werden.
3. Öffnen Sie **Tools > Best Practices Journal**.
4. Erstellen Sie zuerst einen Praxis-Kandidaten, wenn die Richtlinie noch nicht überprüft ist.
5. Füllen Sie Problem, Kontext, Lösung, Anwendbarkeit, Kompromisse, Vorbedingungen und Fehlermodi aus.
6. Füge Sie lokale Nachweise oder eine manuelle Nachweisnotiz mit Provenienz und Rechtehinweisen bei.
7. Validieren Sie den Datensatz und fügen Sie Prüferhinweise hinzu, bevor Sie ihn als akzeptierte Richtlinie behandeln.
8. Nutzen Sie **Search practices**, um den Datensatz nach Thema, Tag oder Nachweisnotiz wiederzufinden.
9. Erstellen Sie einen Anwendungs-Brief für ein bestimmtes Ziel und überprüfen Sie den JSON/Markdown-Export.
10. Importieren Sie ein Implementierungsergebnis, nachdem nachgelagerte Arbeiten abgeschlossen sind.

BPJ läuft eigenständig: Optionale Nachweis-Provider, UCM-Routen, IIS, SDA, UCI oder PRS können den Workflow bereichern, aber das Kern-Journal, die Überprüfung, der Export und die Ergebnis-Schleife funktionieren ohne jedes andere Tiny Tool-Plugin.

## Ergebnis überprüfen

Überprüfen Sie nach dem ersten Start die gespeicherten Artefakte unter `Saved/BestPracticesJournal/`:

- `practices/` enthält Praxiseinträge.
- `application_briefs/` enthält reine Absichts-Übergabedateien.
- `implementation_outcomes/` enthält importierte Ergebnisdatensätze.
- `reports/` enthält Validierungs-, Import- und Betreiberberichte.

Diese Dateien sind die dauerhaften Nachweise für Überprüfung und Übergabe. Die Log-Ausgabe von Unreal ist nützlich für Diagnosen, bildet jedoch nicht den amtlichen Nachweis.

## Prüfung der Grenzen

Ein Anwendungs-Brief sollte Absicht, Zielkontext, Einschränkungen, erforderliche Validierung und den Genehmigungsstatus beschreiben. Er sollte keinen kopierten Implementierungscode, keine Patch-Anweisungen, keine Rollback-Schritte und keine Berechtigung für BPJ zur Änderung von Projektdateien enthalten.

## Erste gute Praxis

Beginnen Sie mit einer kleinen Praxis, die reale Nachweise hat, wie etwa eine projektspezifische Protokollierungskonvention oder eine Review-Checkliste. Vermeiden Sie es, pauschale Regeln wie "schreibe besseren Code" zu verfassen, es sei denn, Sie können Kontext, Fehlermodi, konkrete Nachweisbeispiele und Validierungsanforderungen angeben.

## Das erste gute Ergebnis

Nachdem ein nachgelagerter Workflow den Brief ausprobiert hat, importieren Sie ein Ergebnis, selbst wenn sich nichts geändert hat. Die Ergebnisse `rejected`, `failed`, `partial` und `no_op` sind nützlich, da sie verhindern, dass BPJ eine übergeneralisierte Praxis als bewiesen darstellt.

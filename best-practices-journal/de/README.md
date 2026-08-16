<!-- doc-provenance: product-facts.yml reconciled 2026-07-19; source AKDB:plugins/BestPracticesJournal/architecture.md; release 1.1.2 -->
# Dokumentation zum Best Practices Journal

Das Best Practices Journal hilft Teams dabei, wiederverwendbare technische Praktiken direkt im Unreal Editor zu verwalten. Es speichert Praxiswissen, Provenienz, Überprüfungsstatus, Implementierungsabsichten und Ergebnis-Historien unter einem BPJ-eigenen lokalen Artefakt-Stammverzeichnis.

Version 1.1.2 unterstützt Unreal Engine 5.4 und neuer. Importierte Nachweise und Provider-Ausgaben bleiben überprüfbare Kandidaten bis zur expliziten menschlichen Freigabe; kein externer Erzeuger kann eine Praxis eigenständig akzeptieren.

BPJ läuft eigenständig. Optionale Ökosystem-Provider können Nachweise, Kandidaten, Ergebnisse oder Übergabeziele bereitstellen, aber das Journal, die Validierung, die Suche, der Export und die Ergebnis-Schleife bleiben voll nutzbar, wenn alle optionalen Provider fehlen.

## Hauptkonzepte

- Praxiseinträge (Practice records) beschreiben wiederverwendbare technische Richtlinien, Kontext, Kompromisse, Anwendbarkeit, Fehlermodi und den Überprüfungsstatus.
- Praxiskandidaten (Practice candidates) sind Entwürfe oder von Providern abgeleitete Vorschläge, die noch überprüft werden müssen.
- Nachweise (Evidence records) verbinden Praktiken mit projekt-lokalen Beweisen, Provenienz, Rechtehinweisen und Vertraulichkeit/Vertrauen.
- Anwendungs-Briefs (Application briefs) beschreiben die Absicht zur Anpassung einer überprüften Praxis an ein bestimmtes Ziel.
- Ergebnis-Importe (Outcome imports) erfassen, ob nachfolgende Arbeiten eine Praxis bestätigt, geschwächt, widerlegt, spezialisiert oder ersetzt haben.
- Schwärzungs- und Schutzrichtlinien halten geteilte Datensätze bewusst kontrolliert.
- Speicher-Backends ermöglichen den Betrieb von BPJ als JSON-Artefakte, lokales SQLite oder als Postgres-gestütztes Studio-Profil.

## Produktgrenzen

BPJ besitzt Praxiseinträge, Kandidaten, Nachweisreferenzen, Überprüfungsstatus, Anwendungs-Briefs, Implementierungsergebnis-Importe, deterministische Exporte, Schema-Validierung, Schwärzung, Schutzplanken und lokale Berichte. Es besitzt keine Patch-Planung, Dry-Run/Apply, Rollback, finale Implementierungsvalidierung, KI-Ausführung oder Quellcode-/Asset-Mutation.

Anwendungs-Briefs sind reine Absichts-Übergabeartefakte. Nachgelagerte Werkzeuge oder menschliche Workflows müssen weiterhin ihre eigenen Schritte für Planung, Genehmigung, Mutation, Validierung und Rollback ausführen.

## Akzeptanzvertrag

Eine akzeptierte Praxis sollte nicht nur ein Slogan sein. Vor der Akzeptanz oder breiten Wiederverwendung sollten folgende Punkte erfasst werden:

- Problem, Kontext und Lösung.
- Warum es funktioniert und wo es anwendbar ist.
- Vorbedingungen, Anpassungsregeln, Kompromisse und Fehlermodi.
- Nachweisreferenzen, Provenienz, Rechtehinweise und Vertrauenswürdigkeit.
- Überprüfungsstatus, Prüferhinweise und Ergebnishistorie, sofern verfügbar.

Schwache oder fehlende Felder sollten als Validierungsbefunde behandelt werden, nicht als harmlose Formatierungsfehler.

## Brief- und Ergebnisvertrag

Anwendungs-Briefs können Praxis-Identität, Ziel-Kontext, empfohlene Anpassung, Einschränkungen, erlaubte und verbotene Aktionskategorien, Validierungsanforderungen, erwartete Ausgaben, Nachweisreferenzen, Genehmigungsstatus und Kompatibilitätshinweise enthalten. Sie dürfen keinen kopierten Implementierungscode enthalten oder Mutationsrechte gewähren.

Ergebnis-Importe aktualisieren die Historie und das Vertrauen in eine Praxis. Ein fehlgeschlagenes oder abgelehntes Ergebnis ist ein wertvoller Datensatz: Es sollte importiert statt verborgen werden, da es die ursprüngliche Praxis schwächen, widerlegen, spezialisieren oder ersetzen kann.

## Lokale Artefakte und Protokollierung

BPJ schreibt projekt-lokale Artefakte unter `Saved/BestPracticesJournal/`, einschließlich `practices`, `candidates`, `evidence`, `application_briefs`, `implementation_outcomes`, `reports`, `schemas`, `logs` und `provider_inbox`. Unreal-Diagnosen nutzen `LogBestPracticesJournal`; dauerhafte Betreibernachweise sollten aus den gespeicherten JSON/Markdown-Artefakten entnommen werden und nicht aus flüchtigen Protokollzeilen.

## Dokumente für Käufer

- [Schnellstart](QUICKSTART.md)
- [Benutzerhandbuch](UserManual.md)
- [Einstellungsreferenz](SettingsReference.md)
- [Fehlerbehebung](TROUBLESHOOTING.md)
- [FAQ](FAQ.md)
- [Drittanbieter-Software](THIRD_PARTY_SOFTWARE.md)
- [Storage Backends](StorageBackends.md)

## Betreiberoberflächen

- Editor-Workbench: Erstellen, Überprüfen, Suchen, Erstellen von Briefs, Importieren von Ergebnissen und Prüfen des Integrationsstatus.
- Gespeicherte Artefakte: JSON/Markdown-Einträge unter `Saved/BestPracticesJournal/`.
- Commandlets: Validierung, Artefakt-Import und Beispiel-Export für Automatisierungs- und Release-Prüfungen.
- Optionale Routen/Provider: Austauschbare Integrationsflächen, die keine Voraussetzung für die Erstnutzung sein dürfen.

## Workflows

1. Öffnen Sie `Tools > Best Practices Journal`.
2. Erstellen oder importieren Sie Praxiseinträge.
3. Füge Sie Nachweise und den Überprüfungsstatus bei.
4. Validieren und überprüfen Sie den Datensatz vor der Akzeptanz.
5. Erstellen Sie einen reinen Absichts-Anwendungs-Brief, wenn der Implementierungskontext bekannt ist.
6. Importieren Sie Ergebnisse, nachdem nachgelagerte Arbeiten abgeschlossen sind.

## Verwandte Dateien

- [../README.md](../README.md): Schnellstart.
- [../CHANGELOG.md](../CHANGELOG.md): Versionshistorie.
- [StorageBackends.md](StorageBackends.md): JSON-, SQLite- und Postgres-Speichermodi.

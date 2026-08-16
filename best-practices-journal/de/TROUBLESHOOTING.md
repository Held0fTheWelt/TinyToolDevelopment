<!-- doc-provenance: product-facts.yml reconciled 2026-07-19; source AKDB:plugins/BestPracticesJournal/architecture.md; release 1.1.2 -->
# Fehlerbehebung

## Praxis-Validierung fehlgeschlagen

**Ursache:** Dem Datensatz fehlen erforderlicher Kontext, Anwendbarkeit, Nachweise, Kompromisse, Fehlermodi, Provenienz, Überprüfungsstatus oder Rechtehinweise.

**Lösung:** Öffnen Sie die Praxis, vervollständigen Sie die fehlenden Felder und validieren Sie sie erneut, bevor Sie sie akzeptieren oder exportieren.

## Die Praxis wirkt zu generisch

**Ursache:** Der Datensatz ist wie ein Slogan oder eine Stilpräferenz geschrieben statt als wiederverwendbare Praxis mit Kontext und Nachweisen.

**Lösung:** Füge Sie das Problem, den Zielkontext, warum es funktioniert, wo es nicht gilt, Kompromisse, Vorbedingungen, Fehlermodi, Nachweisreferenzen und Validierungsanforderungen hinzu. Belassen Sie es als Kandidaten, bis diese Felder klar sind.

## Schutzplanke des Briefs abgelehnt

**Ursache:** Der Anwendungs-Brief sieht wie ein Ausführungsplan aus, hat keine überprüfte Quellpraxis, enthält kopierten Implementierungscode oder versucht, Mutationsrechte zu erteilen.

**Lösung:** Schreiben Sie den Brief als reine Absicht um. Füge Sie Zielkontext, empfohlene Anpassung, Einschränkungen, erforderliche Validierung und den Genehmigungsstatus hinzu, und lassen Sie den nachgelagerten Ausführer seinen eigenen Plan erstellen.

## Ergebnisimport reduzierte das Vertrauen

**Ursache:** Das importierte Ergebnis meldete einen Fehler, eine Regression, eine Ablehnung, einen Teilerfolg oder Erkenntnisse, die der ursprünglichen Praxis widersprechen.

**Lösung:** Behalten Sie das Ergebnis. Aktualisieren Sie Review-Notizen, fügen Sie bei Bedarf eine Spezialisierung oder eine ersetzende Praxis hinzu und vermeiden Sie es, negative Nachweise zu löschen, nur um die ursprüngliche Empfehlung sauber aussehen zu lassen.

## Provider fehlt

**Ursache:** Optionale Kandidaten-, Nachweis-, Implementierungsergebnis- oder Übergabe-Provider fehlen oder sind deaktiviert.

**Lösung:** Fahren Sie mit manuellen/lokalen Datensätzen fort oder aktivieren Sie den optionalen Provider. Das Fehlen eines Providers ist für den eigenständigen Journal-Workflow nicht fatal.

## Provider-Bericht wirkt schwärzt

**Ursache:** BPJ schwärzt Provider-Diagnosen vor dem Schreiben von Integrationsberichten, damit Prompts, Token, Pfade und geheimnisähnliche Felder nicht über gemeinsam genutzte Artefakte durchsickern.

**Lösung:** Nutzen Sie den geschwärzten Bericht zum Teilen. Prüfen Sie lokale Provider-Werkzeuge nur dann, wenn Sie berechtigt sind, die Rohdiagnosen zu handhaben.

## Speicher-Backend nicht verfügbar

**Ursache:** Das gewählte Speicher-Backend kann den konfigurierten Pfad oder das externe Profil nicht öffnen.

**Lösung:** Kehren Sie zu `JsonArtifacts` zurück, überprüfen Sie lokale Pfade oder korrigieren Sie das externe Datenbankprofil außerhalb des ausgelieferten Plugin-Pakets.

## Commandlet-Ausgabe ist schwer zu finden

**Ursache:** Das Commandlet-Protokoll fasst die Operation nur zusammen; der gespeicherte Bericht ist das dauerhafte Ergebnis.

**Lösung:** Durchsuchen Sie `Saved/BestPracticesJournal/reports/` nach Validierungs- und Importberichten. Filtern Sie Unreal-Logs nach `LogBestPracticesJournal`, wenn Sie umgebende Diagnosen benötigen.

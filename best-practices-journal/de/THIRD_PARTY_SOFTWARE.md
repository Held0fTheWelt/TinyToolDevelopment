<!-- doc-provenance: product-facts.yml reconciled 2026-07-19; source AKDB:plugins/BestPracticesJournal/architecture.md; release 1.1.2 -->
# Drittanbieter-Software

Best Practices Journal bündelt keine Laufzeitbibliotheken von Drittanbietern, Modell-Provider, Datenbank-Server oder externe ausführbare Dateien.

Optionale SQLite- oder Postgres-Workflows sind Speicherprofile und externe Umgebungswahlen. Sie werden nicht als gebündelte Drittanbieter-Software im Plugin-Paket ausgeliefert.

Wenn ein Projekt SQLite, Postgres, IIS, UCM, UCI, PRS oder eine andere optionale Ökosystem-Komponente nutzt, bleibt diese Komponente eine externe Projekt- oder Studio-Wahl. Das ausgelieferte Paket von BPJ muss weiterhin JSON-Artefakte ohne diese Komponenten öffnen, validieren, importieren, exportieren und überprüfen.

Optionale Provider und Konsumenten sind Integrationsflächen, keine gebündelte Software. Ihr Fehlen sollte als Status oder Diagnose erscheinen, nicht als Start- oder Erstnutzungs-Fehler von BPJ.

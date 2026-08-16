<!-- doc-provenance: product-facts.yml reconciled 2026-07-19; source AKDB:plugins/BestPracticesJournal/architecture.md; release 1.1.2 -->
# Einstellungsreferenz

Die Einstellungen des BPJ wählen aus, wo projekt-lokale Praxis-Artefakte liegen und wie sich optionale Speicher-Projektionen verhalten.

| Einstellung | Typ | Standard | Wirkung |
| --- | --- | --- | --- |
| `StorageBackend` | enum | `JsonArtifacts` | Wählt JSON-Artefakte, den lokalen SQLite-Modus oder ein Postgres-gestütztes Studio-Profil aus. |
| `StorageScope` | enum | `ProjectSaved` | Wählt Projekt-, Benutzer-, Workspace- oder benutzerdefinierten Speicherumfang. |
| `StorageRootOverride` | path | leer | Überschreibt das lokale Artefakt-Stammverzeichnis, wenn ein benutzerdefinierter Ort erforderlich ist. |
| `WorkspaceStorageRoot` | path | leer | Weist BPJ auf ein gemeinsames Workspace-Artefakt-Stammverzeichnis hin. |
| `SQLiteDatabasePathOverride` | path | leer | Überschreibt den Pfad zur SQLite-Datenbankdatei für den lokalen Profi-Modus. |
| `SQLiteDatabaseFileName` | string | `bpj.sqlite` | Benennt die standardmäßige lokale SQLite-Datenbankdatei. |
| `PostgresConnectionProfileName` | string | profildefiniert | Benennt das externe Bridge-Profil, das von einem Studio-Postgres-Setup verwendet wird. |
| `PostgresDsnEnvironmentVariable` | string | `BPJ_POSTGRES_DSN` | Benennt die Umgebungsvariable, die von externen Bridge-Werkzeugen verwendet wird. |
| `bEnableJsonCompatibilityExport` | boolean | true | Hält portable JSON-Exporte verfügbar, selbst wenn ein anderer Speichermodus gewählt ist. |
| `bEnableMarkdownProjection` | boolean | true | Schreibt lesbare Markdown-Projektionen für Überprüfung und Übergabe. |
| `bEnableIisDerivedIndex` | boolean | true | Erlaubt abgeleitete IIS-Abruf-Exporte, wenn ein optionaler Indexierungs-Workflow vorhanden ist. |
| `JournalSourceFolders` | path array | leer | Wählt lokale Verzeichnisse aus, die Projekt- oder Einzeldatei-Journale enthalten, die BPJ erkennt und an Ort und Stelle anzeigt. |

Halten Sie Geheimnisse außerhalb verteilbarer Plugin-Dateien. BPJ liefert keinen Datenbank-Server aus und speichert keine Provider-Anmeldeinformationen dauerhaft.

## Speichersicherheit

Das Standard-Backend `JsonArtifacts` hält BPJ käuferfreundlich und überprüfbar, indem es portable Dateien unterhalb des gewählten Speicher-Stammverzeichnisses schreibt. SQLite- und Postgres-Profile sind optionale Speicheroptionen für lokale Profi- oder Studio-Workflows; sie machen einen Datenbank-Server nicht zum Teil des Plugin-Pakets.

Halten Sie `bEnableJsonCompatibilityExport` aktiviert, wenn nachgelagerte Werkzeuge, Prüfer oder CI stabile JSON-Artefakte benötigen. Halten Sie `bEnableMarkdownProjection` aktiviert, wenn Menschen lesbare Review- und Übergabedateien benötigen.

## Empfohlene Standardwerte

- Verwenden Sie `JsonArtifacts` und `ProjectSaved` für die Erstnutzung und Fab-sichere Paketvalidierung.
- Setzen Sie `StorageRootOverride` nur dann, wenn das Projekt eine überprüfte lokale Artefakt-Richtlinie hat.
- Halten Sie die Markdown-Projektion für die Überprüfung von Briefs und Ergebnissen aktiviert.
- Halten Sie den JSON-Kompatibilitätsexport aktiviert, wenn SQLite oder Postgres ausgewählt ist.
- Betrachten Sie IIS-abgeleitete Indizes als optionale abgeleitete Ausgaben, nicht als den kanonischen BPJ-Speicher.

## Datenhandhabung

Das gewählte Speicher-Stammverzeichnis kann Projektpfade, Review-Notizen, Nachweisbeschreibungen, Details zu Implementierungsergebnissen, Pfade zu Validierungsberichten und Provenienz-Metadaten enthalten. Überprüfen Sie Exporte, bevor Sie sie nach außerhalb des Projekts senden.

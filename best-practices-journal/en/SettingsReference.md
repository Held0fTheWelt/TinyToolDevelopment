<!-- doc-provenance: product-facts.yml reconciled 2026-07-19; source AKDB:plugins/BestPracticesJournal/architecture.md; release 1.1.2 -->
# Settings Reference

BPJ settings choose where project-local practice artifacts live and how optional storage projections behave.

| Setting | Type | Default | Effect |
| --- | --- | --- | --- |
| `StorageBackend` | enum | `JsonArtifacts` | Selects JSON artifacts, SQLite local mode, or a Postgres-backed studio profile. |
| `StorageScope` | enum | `ProjectSaved` | Chooses project, user, workspace, or custom storage scope. |
| `StorageRootOverride` | path | empty | Overrides the local artifact root when a custom location is required. |
| `WorkspaceStorageRoot` | path | empty | Points BPJ at a shared workspace artifact root. |
| `SQLiteDatabasePathOverride` | path | empty | Overrides the SQLite database file path for local professional mode. |
| `SQLiteDatabaseFileName` | string | `bpj.sqlite` | Names the default local SQLite database file. |
| `PostgresConnectionProfileName` | string | profile-defined | Names the external bridge profile used by a studio Postgres setup. |
| `PostgresDsnEnvironmentVariable` | string | `BPJ_POSTGRES_DSN` | Names the environment variable used by external bridge tooling. |
| `bEnableJsonCompatibilityExport` | boolean | true | Keeps portable JSON exports available even when another storage mode is selected. |
| `bEnableMarkdownProjection` | boolean | true | Writes readable Markdown projections for review and handoff. |
| `bEnableIisDerivedIndex` | boolean | true | Allows derived IIS retrieval exports when an optional indexing workflow is present. |
| `JournalSourceFolders` | path array | empty | Selects local directories containing project or single-file journals that BPJ recognizes and displays in place. |

Keep secrets outside distributable plugin files. BPJ does not ship a database server or persist provider credentials.

## Storage Safety

The default `JsonArtifacts` backend keeps BPJ buyer-friendly and reviewable by writing portable files
below the selected storage root. SQLite and Postgres profiles are optional storage choices for local
professional or studio workflows; they do not make a database server part of the plugin package.

Keep `bEnableJsonCompatibilityExport` enabled when downstream tools, reviewers, or CI need stable
JSON artifacts. Keep `bEnableMarkdownProjection` enabled when humans need readable review and handoff
files.

## Recommended Defaults

- Use `JsonArtifacts` and `ProjectSaved` for first use and Fab-safe package validation.
- Set `StorageRootOverride` only when the project has a reviewed local artifact policy.
- Keep Markdown projection enabled for brief and outcome review.
- Keep JSON compatibility export enabled when SQLite or Postgres is selected.
- Treat IIS-derived indexes as optional derived outputs, not as the canonical BPJ store.

## Data Handling

The selected storage root may contain project paths, review notes, evidence descriptions,
implementation outcome details, validation report paths, and provenance metadata. Review exports
before sending them outside the project.

# BPJ Storage Backends

Best Practices Journal offers three storage modes so the plugin can stay easy
to sell and install while still supporting a serious project knowledge base.

## Modes

### JSON Artifacts

`JsonArtifacts` is the compatibility mode. BPJ stores portable JSON artifacts
and optional Markdown journal projections under the configured BPJ artifact
root. This mode is simple, reviewable, and suitable for a Fab-friendly plugin
package because no customer database is shipped with the plugin.

Use it for:

- Fab-safe default behavior.
- Schema examples and interchange payloads.
- Small teams that want file-based review first.
- Export/import bridges.

This is the recommended first-use mode because it proves the standalone BPJ workflow without any
database server or optional ecosystem plugin.

### SQLite

`SQLite` is the local professional mode. The canonical BPJ store can live in a
project-local or user-local database file while JSON and Markdown projections
remain available as compatibility artifacts.

Use it for:

- Single-machine professional work.
- Fast local queries.
- Full-text search and structured technique records.
- Offline work without a database server.

Default local path:

```text
<Project>/Saved/BestPracticesJournal/database/bpj.sqlite
```

SQLite changes the local storage mechanism; it does not remove the need for JSON/Markdown
compatibility exports when reviewers or downstream tools need stable files.

### Postgres

`Postgres` is the studio mode. BPJ keeps the local artifact root for reports,
projections, and bridge metadata, while a Postgres profile names the canonical
studio database connection used by external BPJ tool bridges or project-specific
integrations.

Use it for:

- Shared studio knowledge bases.
- Multiple tools and users.
- Strong relational querying with `jsonb`, full-text search, and optional
  vector extension support.
- Centralized review and audit workflows.

Keep secrets outside distributable plugin files. The default bridge convention
is the environment variable:

```text
BPJ_POSTGRES_DSN
```

Postgres is a studio profile. It should be treated as an external environment choice, not as a
dependency that every BPJ buyer must install.

## Settings

The editor settings expose:

- `StorageBackend`: `JsonArtifacts`, `SQLite`, or `Postgres`.
- `StorageScope`: `ProjectSaved`, `UserLocal`, `Workspace`, or `Custom`.
- `StorageRootOverride`: explicit local artifact root.
- `WorkspaceStorageRoot`: shared workspace artifact root.
- `SQLiteDatabasePathOverride`: explicit SQLite file path.
- `SQLiteDatabaseFileName`: default `bpj.sqlite`.
- `PostgresConnectionProfileName`: named bridge profile.
- `PostgresDsnEnvironmentVariable`: default `BPJ_POSTGRES_DSN`.
- `bEnableJsonCompatibilityExport`: keep JSON artifacts available.
- `bEnableMarkdownProjection`: keep readable journal notes available.
- `bEnableIisDerivedIndex`: allow derived IIS retrieval exports.

## External Administration

BPJ buyer workflows do not require a bundled database server or project-specific admin helper.
Project teams that choose SQLite or Postgres should use their normal studio database and backup
tooling to create, migrate, back up, and restore the selected store. Keep credentials in the local
environment or in your studio secret-management system, never in distributable plugin files.

## Database JSON Import/Export

SQLite and Postgres use the same database JSON bundle format:
`bpj.database_json.v1`.

This format is meant for backup, migration, tool bridges, and Fab-safe exchange.
It uses logical BPJ field names, so SQLite text columns such as
`metadata_json` and Postgres `jsonb` columns such as `metadata` round-trip
through the same JSON field.

SQLite export/import:

```powershell
<your-bpj-admin-tool> --backend sqlite --sqlite-db Saved\BestPracticesJournal\database\bpj.sqlite --export-json Saved\BestPracticesJournal\database_exports\bpj_database.json
<your-bpj-admin-tool> --backend sqlite --sqlite-db Saved\BestPracticesJournal\database\bpj.sqlite --import-json Saved\BestPracticesJournal\database_exports\bpj_database.json --conflict-mode replace
```

Postgres export/import:

```powershell
$env:BPJ_POSTGRES_DSN='postgresql://user:password@host:5432/bpj'
<your-bpj-admin-tool> --backend postgres --export-json Saved\BestPracticesJournal\database_exports\bpj_database.json
<your-bpj-admin-tool> --backend postgres --import-json Saved\BestPracticesJournal\database_exports\bpj_database.json --conflict-mode replace
```

Supported import conflict modes:

- `replace`: upsert incoming rows by primary key.
- `skip`: keep existing rows and insert only missing rows.
- `fail`: let the database reject duplicate primary keys.

The UCM route `bpj.describe_storage.v1` resolves the active storage profile for
automation and MCP bridges. It reports the backend, local roots, SQLite database
path, Postgres profile name, and compatibility export flags.

## Data Model

The professional schemas are organized around explicit reusable techniques:

- `sources`
- `source_snapshots`
- `journal_entries`
- `techniques`
- `technique_steps`
- `required_signals`
- `applicability_rules`
- `failure_modes`
- `acceptance_checks`
- `evidence_links`
- `relationships`
- `journal_events`
- `artifact_exports`
- `search_documents`

This keeps BPJ focused on the concrete "how": required techniques, procedure,
code signals, evidence, review state, and acceptance checks.

## Evidence Boundary

Storage mode changes where BPJ records live; it does not change BPJ's product boundary. BPJ still
records practice knowledge, intent-only briefs, and outcomes. It does not apply changes to source,
assets, descriptors, Build.cs files, or external plugins.

The canonical review questions are the same in every mode: is the practice evidenced, reviewed,
rights-safe, applicable, and outcome-aware?

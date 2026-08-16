<!-- doc-provenance: product-facts.yml reconciled 2026-07-01; source AKDB:plugins/AssetLoaderStudio/architecture.md -->
# Settings Reference

Asset Loader Studio settings are centered on governance profiles, allowed roots/classes, audit policy, and route overrides.

## Governance Settings

| Setting | Type | Default | Effect |
| --- | --- | --- | --- |
| `DefaultProfileId` | string | `guided_safe` | Selects the default permission profile when no route or request profile is supplied. |
| `ProfileDirectories` | array | `Config/AssetLoaderStudio/Governance/Profiles` | Lists folders scanned for permission profile JSON. |
| `AllowedRoots` | array | `/Game`, `/Engine` | Limits mutation targets to approved Unreal roots. |
| `AllowedClasses` | array | package default | Restricts mutation targets to approved class paths when configured. |
| `AuditRetentionDays` | integer | `30` | Controls how long audit logs are retained before pruning. |
| `AuditLogDirectory` | string | `Saved/AssetLoaderStudio/Audit` | Stores persisted audit entries for preview and apply operations. |
| `bAuditPreviewOperations` | boolean | `true` | Writes audit entries for operation previews. |
| `bAuditApplyOperations` | boolean | `true` | Writes audit entries for apply operations. |

## Permission Profile Fields

Permission profiles define `profile_id`, allowed actions, maximum affected assets/rows, allowed roots/classes, read-only mode, dry-run mode, apply confirmation, destructive approval, and audit retention. Use `read_only` for inspection, `guided_safe` for normal reviewed edits, and `expert` only for trusted bulk work.

## Route Overrides

Optional route overrides can map a UCM route to a stricter or looser profile. Route overrides do not replace local preview/apply checks; they only select the profile used by those checks.

## Practical Defaults

- Start with `guided_safe` for reviewed editor work.
- Keep `read_only` for discovery, validation, table export, and automated checks that should not mutate assets.
- Use `expert` only for trusted bulk work, and keep destructive approval explicit.
- Keep audit retention high enough to cover your normal release-review window.

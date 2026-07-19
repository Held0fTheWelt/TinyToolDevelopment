# Unreal Blueprint Integrator

> Not a verbatim copy of shipped docs. This page is a public overview and ecosystem routing surface.

Unreal Blueprint Integrator (UBI) turns Blueprint assets into deterministic local evidence and offers
a separately governed mutation path for reviewed automation. Inventory, export, analysis, reports,
indexes, and comparisons remain read-only. Mutation requires preview, permission, backup, apply, save,
and audit evidence.

The current public release line is 1.2.4. Its behavior is implemented for Unreal Engine 5.4 and
later; the descriptor mirrored by this documentation belongs to the UE 5.8 build line.

## Current Capabilities

- Blueprint and AnimBlueprint inventory plus deterministic graph export.
- Scoped compiler status, counts, and tokenized diagnostics without saving Blueprint packages.
- Local structural analysis with evidence references, reports, and output indexes.
- Comparison artifacts for added, removed, and changed Blueprint evidence.
- Approval-gated mutations for adding Blueprint variables, setting supported class-default properties,
  and creating or updating DataAssets.
- Rollback from backups, including removal of a newly created asset when the backup records that it
  did not exist before apply.

## Operating Boundary

- Engine baseline: Unreal Engine 5.4+.
- Current descriptor/build target: Unreal Engine 5.8.
- A mutation target must be the project open in the current Unreal Editor.
- Preview tokens are content-addressed and must match the requested change at apply time.
- Preview accepts only the mutation-preview or mutation-apply profile. Apply and rollback require the
  mutation-apply profile with asset mutation and user approval enabled; missing flags fail closed.
- Unsupported types or properties fail validation instead of being guessed.
- UBI does not decide which composition should be built; it materializes explicitly reviewed
  instructions.

UBI participates in the
[cross-project composition workflow](../../workflows/cross-project-composition.md) as the owner of
Blueprint and DataAsset mutation.

## Status

- Version: 1.2.4
- Status: In Publishment
- Fab: In publishment; not live until Fab shows the listing as Live

<!-- doc-provenance: product-facts.yml reconciled 2026-07-01; source AKDB:plugins/AssetLoaderStudio/architecture.md -->
# FAQ

## Is Asset Loader Studio standalone?

Yes. The editor workspace, runtime subsystem, Blueprint library, examples, governance profiles, and buyer docs work without UCM, UMCP, MCP, or other Tiny Tool plugins.

## Does it replace Unreal's Asset Manager?

No. It builds on Unreal asset paths, primary asset ids, tables, packages, and the Asset Registry. It adds structured load jobs, diagnostics, table snapshots, dependency graphs, previews, and governance.

## Can it mutate project assets?

Yes, but mutation is preview-first. Create, duplicate, rename, retarget, repair, save, rollback, and delete operations must pass permission profile checks and should be reviewed before apply.

## Where are audit records stored?

The default audit directory is `Saved/AssetLoaderStudio/Audit`. The path can be adjusted through governance settings.

## Are automation routes required?

No. Optional UCM/MCP files expose the same services for governed automation, but the core product remains usable without them.

## Is Asset Loader Studio live on Fab?

The current package state is In Publishment. Treat it as prepared for Fab handoff, not live, until
the Fab portal listing itself is published.

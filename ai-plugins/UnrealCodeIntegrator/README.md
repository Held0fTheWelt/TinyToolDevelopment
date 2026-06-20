# Unreal Code Integrator

> Not a verbatim copy of shipped docs. This online page is an overview and routing surface; shipped buyer docs stay in the plugin package.

Unreal Code Integrator is an advanced-preview Unreal Engine plugin for controlled request intake, deterministic integration planning, policy checks, report writing, and approved low-risk project changes with rollback evidence.

## What It Does

- Imports or creates reviewed implementation requests.
- Builds deterministic integration plans and affected-artifact reports.
- Keeps execution dry-run/reportable first and requires explicit approval before mutation.
- Writes apply reports, backups, history records, and rollback manifests for reviewed jobs.
- Provides local file-contract tooling without granting autonomous mutation authority.

## Product Boundary

UCI is a review-first integrator. It does not replace UII as an evidence producer, IIS as a retrieval/index layer, PRS as a dedicated restructure executor, or LLM Store as a provider-policy owner. Optional companion plugins can provide approved intent or route governance, while UCI keeps local policy gates and apply approval.

## Status

- Category: AI Plugins
- Status: Advanced Preview
- Fab: Not listed yet
- Current focus: deterministic planning, approval gates, report writing, approved file/config changes, and rollback manifests

## Package Docs

Buyer docs ship inside the plugin package as `Documentation/QUICKSTART.md`, `Documentation/UserManual.md`, `Documentation/SettingsReference.md`, `Documentation/TROUBLESHOOTING.md`, `Documentation/FAQ.md`, and `Documentation/THIRD_PARTY_SOFTWARE.md`.

## Support

For questions, setup help, and product support:

https://discord.gg/HycgjVkK4J

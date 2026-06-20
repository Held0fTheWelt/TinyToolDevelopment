# IIS LLM Store Bridge

> Not a verbatim copy of shipped docs. This online page is an overview and routing surface; shipped buyer docs stay in the plugin package.

IIS LLM Store Bridge is a free companion bridge for projects that use both **Internal Index Service** and **LLM Store**. It registers the IIS embedding executor id `llmstore` and adapts IIS embedding route requests to LLM Store embedding routes without moving provider governance into IIS.

## What It Does

- Connects IIS embedding jobs with LLM Store routes and governance.
- Keeps IIS responsible for indexing, vector storage, retrieval, context packs, and evidence access.
- Keeps LLM Store responsible for providers, models, secrets, runtime modes, fallback policy, costs, and route governance.
- Exposes small Blueprint diagnostics for executor registration, route resolution, and embedding smoke checks.
- Restores the previous IIS executor setting when the bridge unloads or the editor exits.

## Product Boundary

The bridge connects systems without blurring the ownership boundaries of the core plugins. It is not a replacement for IIS, LLM Store, or UCM, and it is not a standalone embedding product.

## Status

- Category: Bridge Plugins
- Status: Free companion
- Fab: Public docs/routing page, package docs ship with the bridge
- Current focus: direct IIS embedding executor adapter for LLM Store embedding routes

## Synergies

- **Internal Index Service** uses the bridge only for embedding executor handoff; lexical search and context packs remain IIS-owned.
- **LLM Store** remains the governed provider and route owner for embedding execution.
- **Unreal Capability Mesh** remains the preferred broader orchestration layer when a project needs cross-product workflow policy.

## Package Docs

Buyer docs ship inside the plugin package as `Documentation/QUICKSTART.md`, `Documentation/UserManual.md`, `Documentation/SettingsReference.md`, `Documentation/TROUBLESHOOTING.md`, `Documentation/FAQ.md`, `Documentation/THIRD_PARTY_SOFTWARE.md`, and `Documentation/SOURCE_OVERVIEW.md`.

## Media

The public media folder contains overview and route-ownership visuals for the bridge.

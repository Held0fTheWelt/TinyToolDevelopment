# Unreal Capability Mesh

> Not a verbatim copy of shipped docs. This page is an online overview and routing surface; install and day-to-day buyer docs stay in the shipped plugin package.

## Overview

Unreal Capability Mesh (UCM) is a setup-driven interoperability hub for Unreal plugins. It reads JSON manifests for capabilities, endpoints, schemas, rules, routes, transforms, and adapters so plugins can cooperate without hard compile-time dependencies.

UCM owns setup, route planning, approval and dry-run gates, generic invocation, diagnostics, and local reports. Product plugins keep their own data truth, settings, and mutation authority.

Provider-owned manifests can ship inside each provider plugin under
`Config/UnrealCapabilityMesh/`. That makes the provider's routes discoverable when a packaged
plugin is installed into another Unreal project or as an engine plugin. Project-local manifests are
reserved for deliberate overrides and project-specific compositions; they are not required copies
of every provider route.

## Get It / Routing

- Fab: [Unreal Capability Mesh](https://www.fab.com/listings/fd186d26-cdcf-4c4f-93d4-50e437b7673e)
- Category: Foundation Plugins
- Engine baseline: Unreal Engine 5.4+
- Start here: shipped `Documentation/QUICKSTART.md` for enabling the plugin, reloading setup, dry-running a route, and reading reports
- Package docs include setup reference, integration notes, route catalog behavior, settings, troubleshooting, and third-party declaration

## Synergies & Bridges

- Unified MCP Server can expose generic `mesh_*` tools and setup-declared route tools over the local MCP endpoint.
- Tiny Tool Execution can project those routes into a transport-neutral tool catalogue through its
  optional editor integration bridge. The bridge reloads UCM setup before discovery so packaged
  provider manifests are visible at startup.
- Product plugins declare their capabilities through manifests instead of linking directly to each other.
- Approval-gated routes should stay explicit: dry-run first, inspect side effects, then execute only with the required approval state.
- The [cross-project composition workflow](../../workflows/cross-project-composition.md) is an
  example of UCM retaining route and approval authority while APM, PIO, UBI, and other owners keep
  their domain behavior.

## Media

The public media folder shows the setup flow, route catalog, governance, diagnostics, settings, and config administration surfaces.

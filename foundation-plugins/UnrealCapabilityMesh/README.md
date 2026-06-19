# Unreal Capability Mesh

> Not a verbatim copy of shipped docs. This page is an online overview and routing surface; install and day-to-day buyer docs stay in the shipped plugin package.

## Overview

Unreal Capability Mesh (UCM) is a setup-driven interoperability hub for Unreal plugins. It reads JSON manifests for capabilities, endpoints, schemas, rules, routes, transforms, and adapters so plugins can cooperate without hard compile-time dependencies.

UCM owns setup, route planning, approval and dry-run gates, generic invocation, diagnostics, and local reports. Product plugins keep their own data truth, settings, and mutation authority.

## Get It / Routing

- Fab: [Unreal Capability Mesh](https://www.fab.com/listings/fd186d26-cdcf-4c4f-93d4-50e437b7673e)
- Category: Foundation Plugins
- Start here: shipped `Documentation/QUICKSTART.md` for enabling the plugin, reloading setup, dry-running a route, and reading reports
- Package docs include setup reference, integration notes, route catalog behavior, settings, troubleshooting, and third-party declaration

## Synergies & Bridges

- Unified MCP Server can expose generic `mesh_*` tools and setup-declared route tools over the local MCP endpoint.
- Product plugins declare their capabilities through manifests instead of linking directly to each other.
- Approval-gated routes should stay explicit: dry-run first, inspect side effects, then execute only with the required approval state.

## Media

The public media folder shows the setup flow, route catalog, governance, diagnostics, settings, and config administration surfaces.

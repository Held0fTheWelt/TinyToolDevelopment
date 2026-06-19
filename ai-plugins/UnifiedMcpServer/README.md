# Unified MCP Server

> Not a verbatim copy of shipped docs (Documentation Supply Chain SAD / FAB section 11.2). This online page is an overview and routing surface; install, setup, and day-to-day buyer docs stay in the shipped plugin package.

## Overview

Unified MCP Server is an Unreal Engine editor plugin that hosts one local Model Context Protocol
endpoint for a project. It provides an editor-owned loopback server, bearer-token handshake,
provider registry, and status/control surface without shipping an external executable, Node package,
or Python runtime.

The product is intentionally infrastructure-first: it gives local agents one endpoint to call, while
the actual product capabilities still belong to their provider plugins.

## Get It / Routing

- Fab: [Unified MCP Server](https://www.fab.com/listings/f5ded18c-38b5-4e12-88cb-120f484e282f)
- Category: AI Plugins
- Editor menu: `Tools -> AI -> Universal MCP`
- Default local endpoint: `http://127.0.0.1:8732/mcp`
- Package docs: included with the Fab/plugin package for installation, settings, troubleshooting,
  and provider integration details.

## Synergies & Bridges

Unreal Capability Mesh is the preferred route layer for normal Tiny Tool Development setups. When
UCM is present, Unified MCP Server exposes mesh discovery, route dry runs, route execution, and
setup-declared `mesh_route_*` tools through the same local MCP endpoint.

Provider plugins can also register direct tools through the UMCP provider interface. That direct path
is useful for independent providers, reference adapters, and no-UCM projects. Optional bridge plugins
may publish product-specific tool names for compatibility, but UCM routes remain the preferred setup
for cross-product workflows.

Useful pairings:

- Internal Index Service: agent search and context-pack retrieval through UCM routes.
- LLM Store: model/provider policy surfaces that can be reached by local agents through routed tools.
- Smart Content Diet and Project Restructure Service: reviewed analysis and apply workflows surfaced
  through shared editor-job contracts.

## Media

The public slide set in [Media](Media/) shows the product boundary, provider aggregation model,
settings surface, access guard, and intended scope.

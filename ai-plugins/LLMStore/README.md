# LLM Store

> Not a verbatim copy of shipped docs. This page is an online overview and routing surface; install and day-to-day buyer docs stay in the shipped plugin package.

## Overview

LLM Store is the Tiny Tool control point for AI provider configuration, model routes, embedding routes, policy, costs, secrets, and optional local-agent access. Feature plugins call stable task kinds instead of hard-coding provider names, API keys, fallback behavior, or route policy.

The product is available on Fab and is useful when a project needs governed access to local or cloud models without letting every feature own provider setup and secret handling.

## Get It / Routing

- Fab: [LLM Store](https://www.fab.com/listings/4e9c6062-e3e7-4113-93d1-f08d6e276020)
- Category: AI Plugins
- Start here: shipped `Documentation/QUICKSTART.md` for first provider, model, secret backend, and route setup
- Package docs include provider reference, route policy reference, cost tracking, secret backends, integration notes, troubleshooting, and third-party declaration

## Synergies & Bridges

- Internal Index Service can use LLM Store embedding routes through the IIS/LLM Store bridge while IIS remains the index owner.
- Unified MCP Server and Unreal Capability Mesh can expose governed routes to local agents through setup-declared tools.
- Feature plugins should call stable `TaskKind` routes and leave provider/model/key policy to LLM Store.

## Media

The public media folder contains workflow and governance visuals. Buyer setup and operational details remain in the shipped package docs.

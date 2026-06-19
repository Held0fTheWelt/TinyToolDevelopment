# Buyer Guide

Internal Index Service (IIS) is a local retrieval and context-pack plugin for Unreal Engine projects. It turns prepared project evidence into searchable chunks, builds local lexical and vector indexes, and exposes read-only agent tools for search, context, references, usage lookup, and Blueprint explanation.

## What It Does

- Imports prepared chunk JSONL produced by companion tooling.
- Stores searchable project evidence under the project `Saved` directory.
- Builds a local chunk catalog and search index.
- Supports lexical, vector, and hybrid search.
- Builds context packs from search results.
- Queues embedding jobs and delegates model execution to LLM Store.
- Provides read-only agent tool contracts.
- Integrates with Unified MCP Server through project Capability Mesh routes when UMCP and UCM are enabled.

## What It Does Not Do

- It does not generate patches.
- It does not modify assets, Blueprints, source files, or project settings as an agent action.
- It does not store API keys.
- It does not include an embedded MCP server in current releases.
- It does not extract Unreal evidence by itself; extraction is owned by tools such as Unreal Integration Intelligence.

## Who It Is For

IIS is useful for teams that need local, auditable retrieval over Unreal project evidence:

- code and asset search from an editor tool
- AI-agent context grounded in local project data
- Blueprint graph explanations from indexed evidence
- usage lookup for symbols, assets, and references
- retrieval-only governance for sensitive projects

## Typical Companion Plugins

| Plugin | Role |
| --- | --- |
| Unreal Integration Intelligence | Produces prepared Unreal evidence for IIS import. |
| LLM Store | Resolves and executes embedding routes. |
| Unified MCP Server | Hosts the local MCP endpoint. |
| Unreal Capability Mesh | Declares autonomous IIS agent routes consumed by UMCP. |

## Storage Model

By default, IIS writes project-local artifacts under:

```text
Saved/InternalIndexService
```

The index root can be overridden in Project Settings. IIS keeps generated data local to the project unless a user explicitly routes embeddings through a cloud provider in LLM Store.

## Fab Scope

This is a C++ code plugin with Runtime, Interface, and Editor modules. It includes bundled third-party hnswlib source under `Source/ThirdParty/hnswlib`, declared in `THIRD_PARTY_SOFTWARE.md`.

# Procedural Generated Structures

> Not a verbatim copy of shipped docs. This page is an online overview and routing surface; install and day-to-day buyer docs stay in the shipped plugin package.

## Overview

Procedural Generated Structures is a scene tool for capturing named instanced-static-mesh components into a data asset and rebuilding them as reusable structures. It is useful when a level designer or technical artist wants repeatable structures from explicit captured transforms plus optional row-based generation.

The plugin stays focused on instanced static mesh structure authoring. It does not own procedural mesh generation, navmesh, lighting builds, or arbitrary actor mutation outside the mapped components.

## Get It / Routing

- Fab: Not listed yet
- Category: Scene Tools
- Start here: shipped `Documentation/QUICKSTART.md` for install, actor placement, capture, and rebuild
- Buyer docs in package: quick start, user manual, settings reference, troubleshooting, FAQ, and third-party declaration

## Synergies & Bridges

- Core use is standalone: place `AAsyncProceduralGeneratedActor`, assign `UProceduralStructureDataAsset`, capture, rebuild, and iterate.
- Optional Unreal Capability Mesh routes can expose read, validate, preview, apply, async-status, and job-style actions for teams that already use UCM.
- Generated structures remain project content. Review DataAssets before publishing or sharing because they can reveal level layout and asset paths.

## Media

Product media is pending. Use the shipped package docs for the current package-real walkthrough and expected visible rebuild result.

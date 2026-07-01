# Visual Fidelity Director

> Not a verbatim copy of shipped docs. This page is an online overview and routing surface; install and day-to-day buyer docs stay in the shipped plugin package.

## Overview

Visual Fidelity Director is an Unreal Editor tool for visual-quality snapshots, recipe dry-runs, scanner reports, before/after comparison metadata, and cinematic recommendation exports. It helps teams reason about rendering intent without claiming to replace Unreal rendering systems or guarantee universal best settings.

Version 1.0.0 is in publishment.

The current product boundary is dry-run-first. Snapshot, recipe evaluation, scanner, comparison, cinematic, schema, diagnostics, and productization workflows write local reports. The preview apply path is limited to supported editor-session console variables and rolls them back after the report.

## Get It / Routing

- Status: In Publishment
- Fab: In publishment; not live until Fab shows the listing as Live
- Category: Editor Tools
- Start here: shipped `Documentation/QUICKSTART.md` for control panel, first snapshot, and recipe dry-run
- Buyer docs in package: quick start, user manual, settings reference, troubleshooting, FAQ, and third-party declaration

## Synergies & Bridges

- Core use is standalone and does not require UCM, UMCP, LLM Store, IIS, Smart Documentation Assistant, Smart Content Diet, or cloud AI.
- VFD outputs are local/private by default under `Saved/VisualFidelityDirector`.
- Future automation can route snapshot and recipe evidence through explicit contracts, but those integrations are not required for first-use value.

## Media

Product media now derives from the ProductImages slide set and local VFD report artifacts. The shipped buyer documentation remains the source for expected report names and safety boundaries.

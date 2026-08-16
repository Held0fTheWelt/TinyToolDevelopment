# Buyer Guide

Naming Convention Utility helps Unreal Engine users bring Content Browser assets closer to a consistent naming standard. It is aimed at teams that want repeatable asset-prefix cleanup without writing one-off editor scripts.

## Who It Is For

The plugin is useful for:

- Solo developers cleaning Marketplace imports.
- Technical artists standardizing content folders.
- Pipeline teams enforcing studio prefixes.
- Asset managers reviewing project hygiene before delivery.
- Marketplace sellers preparing example projects.

## Core Value

The plugin focuses on three practical tasks:

1. Define conventions per Unreal asset type.
2. Preview a recursive rename plan with compliance, skip reasons, and selectable rows.
3. Apply safe Unreal asset renames with collision checks, stale-plan guarding, and audit reports.

## Why A DataAsset

The naming rules live in `UNamingConventionsDataAsset` so the policy is visible, editable, and versionable.

Advantages:

- No code change required for common prefix edits.
- Project teams can review convention changes in source control.
- A DataTable can be converted into the DataAsset for spreadsheet-driven workflows.
- The asset can be duplicated for project-specific presets.
- The Workbench can copy a built-in profile into the DataAsset and edit selected rules inline.

## Typical Buyer Scenarios

### Marketplace Import Cleanup

A user imports a pack with mixed naming styles and applies consistent prefixes to textures, materials, meshes, widgets, sounds, and effects.

### Studio Naming Standard

A team starts from **Epic Recommended**, **Tiny Legacy**, or its own **Project Custom** DataAsset, then applies the same convention across feature folders.

### Before Project Delivery

A seller or contractor runs the tool before packaging a sample project to make asset names easier to inspect.

### Pipeline Migration

An older project uses legacy prefixes. The `NamingsToRemove` list strips old fragments before applying the new prefix and suffix.

### Naming Audit

A technical artist scans a folder, exports the JSON/Markdown report, and reviews compliance before applying selected renames.

## What Makes It Different

- It uses Unreal's asset rename tools rather than raw file operations.
- It builds a validated rename plan before changing assets.
- It gives a dockable Workbench with profile selection, compliance, preview rows, skip reasons, and selected-row apply.
- It ships Epic Recommended and Tiny Legacy profile references without silently rewriting project rules.
- It writes audit reports for preview/apply reviews.
- It shares one naming core between the main tool and legacy utility object path.
- It can import DataTable rows into the DataAsset with confirmation and undo support.

## Before You Buy

The plugin is editor-only and intended for Content Browser asset renaming.

It does not:

- Rename C++ symbols.
- Rename folders.
- Rename external DCC source files.
- Guarantee texture purpose from pixels.
- Replace a full studio pipeline validator.

## Recommended Price Positioning

This is a focused asset-management productivity plugin.

Suggested Fab positioning:

- Personal launch price: USD 9.99 to 14.99.
- Professional launch price: USD 24.99 to 39.99.
- Bundle fit: pairs well with logging, copyright, or content-cleanup tools.

## Buyer-Facing Summary

Use Naming Convention Utility when you need a transparent, editor-native way to apply Unreal asset naming rules across folders while keeping control through preview, validation, and editable DataAsset rules.

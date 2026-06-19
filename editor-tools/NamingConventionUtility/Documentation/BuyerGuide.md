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
2. Preview a recursive rename plan for selected folders.
3. Apply safe Unreal asset renames with collision checks.

## Why A DataAsset

The naming rules live in `UNamingConventionsDataAsset` so the policy is visible, editable, and versionable.

Advantages:

- No code change required for common prefix edits.
- Project teams can review convention changes in source control.
- A DataTable can be converted into the DataAsset for spreadsheet-driven workflows.
- The asset can be duplicated for project-specific presets.

## Typical Buyer Scenarios

### Marketplace Import Cleanup

A user imports a pack with mixed naming styles and applies consistent prefixes to textures, materials, meshes, widgets, sounds, and effects.

### Studio Naming Standard

A team edits the default DataAsset to match its internal rules, then applies the same convention across feature folders.

### Before Project Delivery

A seller or contractor runs the tool before packaging a sample project to make asset names easier to inspect.

### Pipeline Migration

An older project uses legacy prefixes. The `NamingsToRemove` list strips old fragments before applying the new prefix and suffix.

## What Makes It Different

- It uses Unreal's asset rename tools rather than raw file operations.
- It builds a validated rename plan before changing assets.
- It gives a user-facing preview and skip reasons.
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

## Buyer-Facing Summary

Use Naming Convention Utility when you need a transparent, editor-native way to apply Unreal asset naming rules across folders while keeping control through preview, validation, and editable DataAsset rules.

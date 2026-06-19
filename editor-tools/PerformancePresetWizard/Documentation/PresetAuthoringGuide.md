# Preset Authoring Guide

This guide explains how to create performance presets that are useful, readable, and safe for a team to share.

## Authoring Principles

Good presets are specific. A preset called `High` is less useful than `Desktop High End 1440p`. A preset should answer:

- Which hardware or workflow is this for?
- Which frame-rate or quality target does it support?
- Which renderer assumptions does it make?
- Which CVars are project-specific and why?

## Start With Scalability

Use Unreal's scalability buckets before reaching for CVars. Scalability is more stable across engine versions and easier for artists to understand.

Available buckets:

- View Distance
- Anti-Aliasing
- Shadows
- Global Illumination
- Reflections
- Post Process
- Textures
- Effects
- Foliage
- Shading
- Landscape

Levels:

- `0`: Low
- `1`: Medium
- `2`: High
- `3`: Epic
- `4`: Cinematic

Use Cinematic sparingly. It is useful for capture and high-quality review, but it can hide performance problems when used as a general editor default.

## Then Add CVars

Add CVar overrides when a target requires behavior that scalability does not express clearly. Examples:

```text
r.ScreenPercentage=85
r.Nanite=1
r.Lumen.Reflections.Allow=0
r.Shadow.Virtual.Enable=1
```

Prefer short, intentional override lists. A preset with dozens of unannotated CVars becomes difficult to trust.

## CVar Line Format

The bulk editor uses a line-oriented format:

```text
Name=Value
Name=Value,editor
```

Examples:

```text
# Lower internal resolution for laptop editor work.
r.ScreenPercentage=80

// Editor-only debug cost toggle.
r.ProfileGPU.ShowUI=0,editor
```

Rules:

- The first `=` separates name from value.
- Whitespace around name and value is trimmed.
- `,editor` at the end marks an override as editor-only.
- Empty lines and comment lines are ignored.
- Unknown CVar names are reported so the author can catch typos.

## Editor-Only Overrides

Mark an override editor-only when it exists only to make editor work easier or to disable editor-side debug/visualization cost. Do not mark an override editor-only if it must also apply during runtime preview, standalone testing, or packaged scenarios.

Examples that may be editor-only:

```text
r.ProfileGPU.ShowUI=0,editor
```

Examples that usually should not be editor-only:

```text
r.ScreenPercentage=85
r.Nanite=1
```

## Target Platform Field

`TargetPlatform` is a classification hint. It does not prevent users from applying the preset on another platform. Use it for grouping, sorting, and communication.

Recommended usage:

- Use built-in entries for common targets.
- Use `Custom 1..5` for studio-specific tiers.
- Document the meaning of custom tiers in the preset description or team wiki.

## Description Field

The description is part of the preset's contract. A good description includes:

- Target hardware or use case.
- Intended resolution or frame-rate assumption.
- Important renderer assumptions.
- Any risky CVar overrides.

Example:

```text
Laptop development preset for open-world editing. Keeps foliage, shadows, GI, and reflections lower to reduce thermal throttling. Not intended for visual approval.
```

## Suggested Preset Set

For most projects, start with five shared presets:

- `Laptop Dev`: low-cost editor default.
- `Desktop Mid Range`: general review profile.
- `Console Like`: fixed-budget validation profile.
- `VR Target`: headset-safe profile with strict effects, shadows, and post-processing.
- `Cinematic Capture`: high-quality offline or marketing capture profile.

Add more only when a real workflow needs them.

## Validation Checklist For A Preset

- Display name is clear and not duplicated accidentally.
- Description explains target and assumptions.
- Scalability fields are within `0..4`.
- CVar names are spelled exactly as Unreal registers them.
- Editor-only flags are intentional.
- Unknown CVars were reviewed, not ignored blindly.
- The preset was tested in a representative map.
- Restore Previous was tested after applying the preset.
- Startup application was tested if the preset is used as a startup default.

## Compatibility Notes

CVars can appear, disappear, or change behavior between engine versions. Performance Preset Wizard reports unknown CVars and continues applying the rest of the preset because partial application is usually more useful than failing the entire profile. Treat unknown CVar warnings as authoring feedback.

